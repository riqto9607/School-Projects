# IoT-Based Smart Office Monitoring System

## Overview
This project is an IoT-based office monitoring system designed to enhance workplace efficiency, comfort, and automation. It simulates real-time monitoring and control of environmental parameters (temperature, humidity, pressure, smoke levels) and office equipment (lighting, air conditioning, CCTV, etc.) across three zones: Reception, Workshop, and Meeting Room. The system leverages Node-RED, InfluxDB, MQTT, and Telegram to create a scalable, modular, and user-friendly solution.

---

## Features
- **Real-time Monitoring**: Tracks environmental data (temperature, humidity, pressure, smoke) and equipment status.
- **Automated Controls**: Adjusts air conditioning, lighting, and alarms based on sensor readings.
- **Multi-Platform Access**: Interfaces include Node-RED dashboards, MQTT panels, and Telegram bots for remote control.
- **Scalability**: Handles increasing data loads efficiently, ensuring consistent performance.
- **Historical Data Storage**: Uses InfluxDB to store and analyze historical sensor data.
- **Notifications**: Alerts users via Telegram for critical events or system updates.

---

## System Architecture
The system is built using the following components:
1. **Node-RED**: 
   - Generates simulated sensor data.
   - Manages workflows and automation.
   - Hosts user interfaces for control and visualization.
2. **InfluxDB**: 
   - Stores historical sensor data for analysis.
3. **MQTT Broker**: 
   - Facilitates real-time communication between components.
4. **Telegram Bot**: 
   - Provides remote access for monitoring and control.
5. **Virtual Sensors**: 
   - Simulate environmental data for testing and development.

---

## How It Works
### 1. **Reception**
- **Door Sensors**: Automatically open/close based on simulated worker movement.
- **CCTV**: Activates upon worker entry; manual control via MQTT.
- **Access Control**: Validates worker entry via UI form; grants/denies access with MQTT notifications.

### 2. **Workshop**
- **Environmental Sensors**: Simulate temperature, humidity, pressure, and smoke levels (updates every 10 seconds).
- **Equipment Control**: Automatically adjusts air conditioning, humidifier, and alarms based on sensor data.
- **Manual Controls**: Workers can adjust lighting, Wi-Fi, computers, and printers via Node-RED or MQTT.
- **Telegram Integration**: Retrieve sensor data or control equipment remotely using Telegram commands.

### 3. **Meeting Room**
- **Sensors**: Monitor temperature and sound levels.
- **Automation**: Adjusts air conditioning and soundproofing based on sensor readings.
- **Remote Control**: Manage lighting, TV, and video calls via MQTT or Telegram.

---

## Setup Instructions
### Prerequisites
- Node-RED installed locally or on a server.
- InfluxDB set up with a configured bucket for data storage.
- MQTT broker (e.g., IoT MQTT Panel) for real-time communication.
- Telegram bot created via BotFather for notifications and remote control.

### Installation Steps
1. **Node-RED Setup**:
   - Install necessary nodes (`node-red-dashboard`, `node-red-contrib-influxdb`, `node-red-contrib-telegrambot`).
   - Import project flows for Reception, Workshop, and Meeting Room.

2. **InfluxDB Configuration**:
   - Create a bucket for sensor data with a retention policy.
   - Generate an API token for Node-RED integration.

3. **MQTT Broker**:
   - Configure the broker address and port in Node-RED.
   - Design dashboards for real-time monitoring.

4. **Telegram Bot**:
   - Use the token from BotFather to integrate with Node-RED.
   - Test commands like `/meetroom_sensor` or `/light_control`.

5. **Virtual Sensors**:
   - Simulate data using Node-RED function nodes for testing.

---

## Performance Metrics
- **Data Latency**: <2 seconds for updates across platforms (Node-RED, MQTT, Telegram).
- **Consistency**: Uniform sensor data displayed on all interfaces.
- **Scalability**: Handles 30+ data points every 5 minutes without performance degradation.

---

## Conclusion
This project demonstrates the potential of IoT in creating smart, responsive office environments. By integrating real-time monitoring, automation, and remote control, it offers a practical solution for enhancing workplace comfort and efficiency. The modular design ensures scalability, making it adaptable for future enhancements or integration with additional office systems.

For more details, refer to the full project report or explore the Node-RED flows and dashboards. 
