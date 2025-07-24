import easygopigo3 as easy
import time
import sys
import tty
import termios
import logging
import threading
import atexit
import signal
import curses

# --- Setup logging ---
logging.basicConfig(
    filename='robot_navigation.log', 
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger()
console_handler = logging.StreamHandler(sys.stdout)
console_handler.setFormatter(logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'))
logger.addHandler(console_handler)

# --- Terminal restore on exit ---
original_termios = termios.tcgetattr(sys.stdin.fileno())
atexit.register(lambda: termios.tcsetattr(sys.stdin.fileno(), termios.TCSADRAIN, original_termios))
signal.signal(signal.SIGINT, lambda signum, frame: sys.exit(0))
signal.signal(signal.SIGTERM, lambda signum, frame: sys.exit(0))

# --- Robot initialization ---
gpg = easy.EasyGoPiGo3()
distance_sensor = gpg.init_distance_sensor()
servo = gpg.init_servo("SERVO1")
servo2 = gpg.init_servo("SERVO2")
servo2.rotate_servo(90)

# --- Constants ---
SAFE_DISTANCE = 40
OBJECT_GRAB_DISTANCE = 8
FORWARD_SPEED = 150
SCAN_ANGLES = [0, 60, 90, 120, 180]
NAV_HISTORY_LIMIT = 5
GRID_SIZE = 10
TURN_ANGLE = 30
SERVO_STEP = 5
SLEEP_TIME = 0.05

# --- Navigation state ---
navigation_history = []
path_history = []
manual_stop = False
manual_mode = False
position_history = []

# --- Dynamic grid map ---
grid_map = [[0]]
map_origin = [0, 0]
current_position = (0, 0)

# --- Helper functions ---

def wait_for_key():
    print("Press any key to start...")
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

def listen_for_keys():
    global manual_stop, manual_mode
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setcbreak(fd)
        while True:
            key = sys.stdin.read(1)
            if key == ' ':
                manual_stop = True
                logger.info("Manual stop triggered by spacebar")
                break
            elif key == 'm':
                manual_mode = True
                logger.info("Switched to manual mode")
                print("[MANUAL MODE ACTIVATED]")
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

def record_position(action, position):
    position_history.append((action, position))

def record_movement(action):
    path_history.append(action)

def go_forward(cm=15):
    gpg.drive_cm(cm)
    logger.info(f"Moved forward {cm} cm")
    record_movement("forward")
    record_position("forward", current_position)

def stop():
    gpg.stop()
    logger.info("Stopped")

def turn(degrees):
    gpg.turn_degrees(degrees)
    logger.info(f"Turned {degrees} degrees")
    record_movement(f"turn_{degrees}")
    record_position(f"turn_{degrees}", current_position)

def reverse(cm=5):
    gpg.drive_cm(-cm)
    logger.info(f"Reversed {cm} cm")
    record_movement("reverse")
    record_position("reverse", current_position)

def grab_object():
    print("Grabbing object...")
    servo.rotate_servo(20)
    time.sleep(1)
    servo.rotate_servo(90)
    time.sleep(1)
    logger.info("Object grabbed")

def scan_surroundings():
    distances = {}
    for angle in SCAN_ANGLES:
        servo.rotate_servo(angle)
        time.sleep(0.2)
        distances[angle] = distance_sensor.read()
    servo.rotate_servo(90)
    logger.info(f"Scanned surroundings: {distances}")
    return distances

def remember_decision(decision):
    navigation_history.append(decision)
    if len(navigation_history) > NAV_HISTORY_LIMIT:
        navigation_history.pop(0)
    logger.info(f"Decision remembered: {decision}")

def retrace_exact_path():
    print("Retracing path step-by-step (reverse)...")
    logger.info("Retracing path step-by-step (reverse)...")

    reverse_actions = list(reversed(path_history))

    for action in reverse_actions:
        if action == "forward":
            reverse(15)
        elif action == "reverse":
            go_forward(15)
        elif action.startswith("turn_"):
            degrees = int(action.split("_")[1])
            turn(-degrees)
        else:
            logger.warning(f"Unknown action in path_history: {action}")

    logger.info("Retrace complete — back to start position")

def expand_grid_if_needed(x, y):
    global grid_map, map_origin

    gx, gy = x + map_origin[0], y + map_origin[1]
    expanded = False

    while gx < 0:
        grid_map.insert(0, [0] * len(grid_map[0]))
        map_origin[0] += 1
        gx += 1
        expanded = True

    while gx >= len(grid_map):
        grid_map.append([0] * len(grid_map[0]))
        expanded = True

    while gy < 0:
        for row in grid_map:
            row.insert(0, 0)
        map_origin[1] += 1
        gy += 1
        expanded = True

    while gy >= len(grid_map[0]):
        for row in grid_map:
            row.append(0)
        expanded = True

    if expanded:
        logger.info(f"Expanded grid to size {len(grid_map)}x{len(grid_map[0])}")

    return gx, gy

def update_grid_map():
    global current_position
    distance = distance_sensor.read()

    if distance < SAFE_DISTANCE:
        x, y = current_position
        gx, gy = expand_grid_if_needed(x, y)
        grid_map[gx][gy] = 1

def avoid_obstacle():
    global current_position

    start_x, start_y = current_position
    total_detour_angle = 0
    surroundings = scan_surroundings()
    front_dist = surroundings.get(90, 0)

    while front_dist < SAFE_DISTANCE:
        left_dist = surroundings.get(60, 0)
        right_dist = surroundings.get(120, 0)

        logger.info(f"Obstacle detected ahead! Left: {left_dist} cm, Right: {right_dist} cm")

        if (left_dist - SAFE_DISTANCE) > (right_dist - SAFE_DISTANCE):
            turn_angle = TURN_ANGLE
            direction_delta = (-1, 0)
            chosen_dir = 'left'
        else:
            turn_angle = -TURN_ANGLE
            direction_delta = (1, 0)
            chosen_dir = 'right'

        turn(turn_angle)
        total_detour_angle += turn_angle
        remember_decision(f"avoid_{chosen_dir}")

        go_forward(20)
        remember_decision("detour_forward")

        current_position = (current_position[0] + direction_delta[0], current_position[1])
        expand_grid_if_needed(*current_position)

        surroundings = scan_surroundings()
        front_dist = surroundings.get(90, 0)

    if total_detour_angle != 0:
        turn(-total_detour_angle)
        remember_decision("recenter")

    delta_x = current_position[0] - start_x
    if delta_x != 0:
        logger.info(f"Returning sideways to original X: {start_x} from X: {current_position[0]}")
        direction = -1 if delta_x > 0 else 1

        turn_angle = 90 * direction
        turn(turn_angle)
        remember_decision("side_correct_turn")

        for _ in range(abs(delta_x)):
            go_forward(GRID_SIZE)
            remember_decision("side_correct_forward")
            current_position = (current_position[0] - direction, current_position[1])
            expand_grid_if_needed(*current_position)

        turn(-turn_angle)
        remember_decision("side_correct_recenter")

    go_forward(15)
    remember_decision("resume_forward")
    current_position = (current_position[0], current_position[1] + 1)
    expand_grid_if_needed(*current_position)

def manual_control():
    global current_position, manual_mode, manual_stop

    h2_turn = 90
    servo2.rotate_servo(h2_turn)

    stdscr = curses.initscr()
    curses.noecho()
    curses.cbreak()
    stdscr.keypad(True)

    stdscr.addstr(0, 0, "[Manual mode] WASD=Move | I/K=Servo2 | Space=Stop | n=Go Home | Ctrl+C=Exit")
    stdscr.refresh()

    try:
        while manual_mode and not manual_stop:
            key = stdscr.getch()

            if key == ord('w'):
                go_forward()
                logger.info("User command received: Move forward (W)")
                current_position = (current_position[0], current_position[1] + 1)
            elif key == ord('s'):
                reverse()
                logger.info("User command received: Move backward (S)")
                current_position = (current_position[0], current_position[1] - 1)
            elif key == ord('a'):
                turn(-TURN_ANGLE)
                logger.info("User command received: Turn left (A)")
            elif key == ord('d'):
                turn(TURN_ANGLE)
                logger.info("User command received: Turn right (D)")
            elif key == ord('i'):
                h2_turn = min(180, h2_turn + SERVO_STEP)
                servo2.rotate_servo(h2_turn)
                logger.info("User command received: Raise servo2 (I)")
            elif key == ord('k'):
                h2_turn = max(0, h2_turn - SERVO_STEP)
                servo2.rotate_servo(h2_turn)
                logger.info("User command received: Lower servo2 (K)")
            elif key == 32:
                stop()
                logger.info("User command received: Stop (Space)")
            elif key == ord('n'):
                manual_mode = False
                logger.info("Manual mode exit — retracing path home")
                print("\n[RETRACE MODE] Returning to start position...")
                retrace_exact_path()
                stop()
                print("[Returned to start. Exiting manual mode.]")
                logger.info("Retrace complete after manual control")
                manual_stop = True
                break

            record_movement("manual_move")
            expand_grid_if_needed(*current_position)
            time.sleep(SLEEP_TIME)

    finally:
        curses.nocbreak()
        stdscr.keypad(False)
        curses.echo()
        curses.endwin()

# --- MAIN LOOP ---
def main():
    wait_for_key()
    print("Robot started...")
    logger.info("Robot started")
    threading.Thread(target=listen_for_keys, daemon=True).start()

    global current_position

    while not manual_stop:
        if manual_mode:
            manual_control()
            continue

        dist = distance_sensor.read()
        print(f"Front Distance: {dist} cm")
        logger.info(f"Front Distance: {dist} cm")

        update_grid_map()

        if dist < OBJECT_GRAB_DISTANCE:
            stop()
            grab_object()
            retrace_exact_path()
            stop()
            print("Task Completed!")
            logger.info("Object grabbed and returned to start")
            break

        if dist < SAFE_DISTANCE:
            avoid_obstacle()
        else:
            go_forward()
            remember_decision("forward")
            current_position = (current_position[0], current_position[1] + 1)
            expand_grid_if_needed(*current_position)

        time.sleep(SLEEP_TIME)

    stop()
    print("\nManual stop activated. Exiting...")
    logger.info("Manual stop activated. Exiting program")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nProgram stopped by user.")
        logger.info("Program interrupted by user")
    finally:
        stop()
        logger.info("Motors stopped in final cleanup")
