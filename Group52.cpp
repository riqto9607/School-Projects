#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cctype>
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS //VS secure version to use strcpy function
using namespace std;

//global variable
const int arraySize = 1000;
const int pwSize = 9;

const int rows = 10;
const int columns = 20;
int seats[rows][columns] = { 0 };

struct movieType {
    string name;
    double price;
};

struct memberSign {
    string name;
    char password[pwSize];
};

//function prototype
void admb();
void admMenu(int&);
void read();
void add();
void dlt();
void mbMenu();
void mbSignup();
bool testNum(char [], int);
void mbLogin(int&);
void mbLoginMenu(int&);
void mbbuyticket(int, int, double&);
void print_seating_chart();
double calculate_total_cost(int, int);
bool reserve_seat(int, int);
void mbwallet(double&);
void mbcancelacc(int, bool&);

int main() {

    admb();

    cin.get();
    return 0;
}

//big menu
void admb() {

    int choiceA, num;
    bool choice = false;
    char quitChoice;

    do {
        system("color 0d");
        cout << "\t|-----------------|" << endl;
        cout << "\t|  YSLL Cinema    |" << endl;
        cout << "\t|-----------------|" << endl;
        cout << "\t|1. Admin Mode    |" << endl;
        cout << "\t|2. Member Mode   |" << endl;
        cout << "\t|3. Quit          |" << endl;
        cout << "\t|-----------------|" << endl;
        cout << "     Please input a selection: ";
        cin >> choiceA;

        if (choiceA == 1) { //admin mode
            do {
                system("cls");
                admMenu(num);
                if (num == 1) { //movie list
                    read();
                }
                else if (num == 2) { //add movie
                    add();
                }
                else if (num == 3) { //delete movie
                    dlt();
                }
                else if (num > 4 || num < 0) { //num invalid
                    cout << "   Invalid input. Please press ENTER to select again!" << endl;
                    cin.get();
                    cin.get();
                }
                else if (num == 4) //back
                    choice = false;
            } while (num > 0 && num != 4);
            system("cls");
        }

        else if (choiceA == 2) { //member mode
            system("cls");
            mbMenu();
        }
        else if (choiceA == 3) { //quit
            cout << "Confirm to QUIT the system?(Y/N): ";
            cin >> quitChoice;
            while (quitChoice != 'Y' && quitChoice != 'y' && quitChoice != 'n' && quitChoice != 'N') { //only accept Y|y or N|n
                cout << "Invalid input. Please re-type again! (Y-Yes, N-No): ";
                cin >> quitChoice;
            }
            if(quitChoice == 'Y' || quitChoice == 'y') //confirm to quit system
                choice = true;
            system("cls");
        }
        else { //choiceA invalid
            cout << "     Invalid input. Please press ENTER to select again!";
            cin.get();
            cin.get();
            system("cls");
        }
    } while (!choice);
}

//member sign in OR sign up
void mbMenu() {

    int choiceB, a; //'a' value will initialize in mbLogin function
    bool choice = false;

    do {
        system("color 0b");
        cout << "\t|--------------------------------------|" << endl;
        cout << "\t|  YSLL Cinema - NEW USER OR EXIST?    |" << endl;
        cout << "\t|--------------------------------------|" << endl;
        cout << "\t|1. New Register                       |" << endl;
        cout << "\t|2. User Login                         |" << endl;
        cout << "\t|--------------------------------------|" << endl;

        cout << "    Please input a selection: ";
        cin >> choiceB;

        if (choiceB == 1) { //register
            system("cls");
            mbSignup();
            system("cls");
        }

        else if (choiceB == 2) { //user login
            system("cls");
            mbLogin(a); //'a' value return by reference in mbLogin function
            mbLoginMenu(a); //'a' value bring into mbLoginMenu function
            choice = true;
        }

        else { //choiceB invalid
            cout << "Invalid input. Please press ENTER to select again!" << endl;
            cin.get();
            cin.get();
            system("cls");
        }

    } while (!choice);

}

//member sign up
void mbSignup() {

    int i = 0;
    bool valid = false;
    memberSign member[arraySize];
    ofstream outfile("member.txt", ios::app);
    ifstream infile("member.txt", ios::app); 
    
    while (!infile.eof()) { //read in member file
        getline(infile, member[i].name);
        infile.getline(member[i].password, pwSize);
        i++;
    }
    infile.close();
    //'i' now updated to the new array position

    system("color 0b");
    cout << "  ---------------------------------------------------------------------------------------------" << endl;
    cout << "            ___    _______       ______________         ________                ________    " << endl;
    cout << "           /      /      /      /             /         /      /                /      /    " << endl;
    cout << "          /      /      /      /             /         /      /                /      /     " << endl;
    cout << "         /      /      /      /      --------         /      /                /      /      " << endl;
    cout << "        /      /      /      /     /                 /      /                /      /       " << endl;
    cout << "       /             /      /      ----------       /      /                /      /        " << endl;
    cout << "      |_______      /                       /      /      /                /      /          " << endl;
    cout << "            /      /            -----      /      /      /                /      /           " << endl;
    cout << "         __/      /                 /     /      /       _________       /       _________   " << endl;
    cout << "      _/         /        ---------      /      /                /      /                /   " << endl;
    cout << "    /           /      /                /      /                /      /                /    " << endl;
    cout << "   |___________/        _______________       /________________/      /________________/     " << endl;
    cout << "  ______________________________________________________________________________________________" << endl;
    cout << endl;
    cout << "\t\t\t\t\tWelcome To YSLL Cinema!" << endl;
    cout << "\t\t\t\t\t  New Member Sign Up" << endl;
    cout << "\t\t   \033[31m*Please ensure that you set the PASSWORD should be memorable!*\033[0m" << endl;
    cout << endl;

    bool usernamevalid = false;
    int a;

    cout << "\t\t\t\t\tUsername: ";
    cin.ignore();
    getline(cin, member[i].name); //input username

    do{
        for (a = 0; a < i; a++) { //check username not repeat then proceed to set password
            if (member[i].name != member[a].name)
                usernamevalid = true;
        }

        for (a = 0; a < i; a++) { //check username repeat or not, if repeat, cannot use second time

            if(member[i].name == member[a].name) { //a=3 i=4
                cout << "\t\t\t   \033[031mThis username has been created by other user.\033[0m" << endl;
                cout << "\t\t\t\t\033[031mPlease re-type other username!\033[0m" << endl;
                cout << endl;
                cout << "\t\t\t\t\tUsername: ";
                getline(cin, member[i].name);
                cin.ignore();
                usernamevalid = false;
            }
        }
    } while (!usernamevalid);

    outfile << endl;
    outfile << member[i].name << endl; //username save in file
    cout << endl;
    do {
        cout << "\t\t\t\t\t\033[34m*L-Letter; N-Number*\033[0m" << endl;
        cout << "\t\t\t\t\t\033[34m(Format - LLLLNNNN)\033[0m" << endl;
        cout << "\t\t\t\t\tPassword: ";
        cin.getline(member[i].password, pwSize); //input password

        if (testNum(member[i].password, pwSize)) { //identify password format using bool function
            outfile << member[i].password; //password save in file
            cout << endl;
            cout << "\t\t\tMember sucessfully created! Your member ID is " << "\033[32m" << member[i].name << "0" << i+1 << "\033[0m" << "." << endl;
            cout << "\t\t\t\t  Press ENTER to return back to menu.";
            cin.get();
            valid = true;
        }
        else { //wrong password format
            cout << endl;
            cout << "\t\t\t\033[031mFormat incorrect! Please set the PASSWORD again.\033[0m" << endl;
        }
    } while (!valid);

    outfile.close();
}

//identify password format
bool testNum(char memberpw[], int pwSize) {
    
    int count;

    for (count = 0; count < 4; count++) {
        if (!isalpha(memberpw[count]))
            return false;
    }

    for (count = 4; count < pwSize - 1; count++) {
        if (!isdigit(memberpw[count]))
            return false;
    }

    return true;
}

//member login
void mbLogin(int& a) { //initialize 'a' same as the variable 'lgno' (member login)

    a = 0; //'a' define as the array location of current user login
    int i = 0, lgno = 0;
    bool valid = false;
    memberSign member[arraySize], loginmb[arraySize];
    ifstream infile("member.txt", ios::app);

    while (!infile.eof()) {
        getline(infile, member[i].name);
        infile.getline(member[i].password, pwSize);
        i++; //'i' can define as the total of existing member
    }
    infile.close();

    do {
        system("color 0b");
        cout << "  ---------------------------------------------------------------------------------------------" << endl;
        cout << "            ___    _______       ______________         ________                ________    " << endl;
        cout << "           /      /      /      /             /         /      /                /      /    " << endl;
        cout << "          /      /      /      /             /         /      /                /      /     " << endl;
        cout << "         /      /      /      /      --------         /      /                /      /      " << endl;
        cout << "        /      /      /      /     /                 /      /                /      /       " << endl;
        cout << "       /             /      /      ----------       /      /                /      /        " << endl;
        cout << "      |_______      /                       /      /      /                /      /          " << endl;
        cout << "            /      /            -----      /      /      /                /      /           " << endl;
        cout << "         __/      /                 /     /      /       _________       /       _________   " << endl;
        cout << "      _/         /        ---------      /      /                /      /                /   " << endl;
        cout << "    /           /      /                /      /                /      /                /    " << endl;
        cout << "   |___________/        _______________       /________________/      /________________/     " << endl;
        cout << "  ______________________________________________________________________________________________" << endl;
        cout << endl;
        cout << "\t\t\t\t     Welcome To YSLL Cinema!" << endl;
        cout << "\t\t\t\t\t  Member Sign In" << endl;
        cout << endl;
        cin.ignore();
        cout << "\t\t\t\t\tUsername: ";
        getline(cin, loginmb[lgno].name); //input login name
        cout << endl;
        cout << "\t\t\t\t\tPassword: ";
        cin.getline(loginmb[lgno].password, pwSize); //input login password

        for (a = 0; a < i; a++) { //identify whether the login name and password exist inside the member file or not 

            if ((member[a].name == loginmb[lgno].name) && (strcmp(member[a].password, loginmb[lgno].password) == 0)) { //name and password also same, exist acc
                cout << "\t\t\tYou're successfully log in! Press ENTER to MEMBER MENU." << endl;
                cin.get();
                system("cls");
                valid = true;
                break; //once find the exist acc, get inside IF function, need to stop the FOR loop to invoid execute a++
            }

        }
        if ((member[a].name != loginmb[lgno].name) || (strcmp(member[a].password, loginmb[lgno].password) == -1)) { //invalid account
            cout << "\t\t\t    \033[31mNOT existing account, press ENTER to sign in again.\033[0m" << endl;
            cin.get();
            system("cls");
        }
    } while (!valid);

}


//member login menu
void mbLoginMenu(int& a) {

    int choiceC, current_idno = a; //'current_idno' initialize to 'a'
    double balance = 0; //declare member wallet balance
    movieType movie[arraySize];
    bool loginChoice = false, auto_logout = false, buyticketChoice = false;
    
    do {
        system("color 0b");
        cout << "\t|--------------------------------------|" << endl;
        cout << "\t|  YSLL Cinema - Member Login Menu     |" << endl;
        cout << "\t|--------------------------------------|" << endl;
        cout << "\t|1. Movie List                         |" << endl;
        cout << "\t|2. Buy Ticket                         |" << endl;
        cout << "\t|3. Wallet                             |" << endl;
        cout << "\t|4. Delete Account                     |" << endl;
        cout << "\t|5. Logout                             |" << endl;
        cout << "\t|--------------------------------------|" << endl;
        cout << "\tPlease input a selection: ";
        cin >> choiceC;
        cout << endl;

        if (choiceC == 1) { //movie list
            read();
        }

        else if (choiceC == 2) { //buy ticket
            do {
                system("cls");
                ifstream infile("cinema.txt", ios::app);
                int i = 0, movieNo;

                cout << "\t1. Buy Ticket" << endl;
                cout << "\t|-------------------------------------------------------|" << endl;
                cout << "\t|\t\t\tMovie List\t\t\t|" << endl;
                cout << "\t|-------------------------------------------------------|" << endl;
                cout << "\t| Name\t\t\t\t\t      | Price   |" << endl;
                cout << "\t|-------------------------------------------------------|" << endl;

                if (infile.is_open()) {
                    while (!infile.eof()) { //read in file
                        getline(infile, movie[i].name);
                        infile >> movie[i].price;
                        cout << "\t| " << i + 1 << ". " << movie[i].name << endl;
                        cout << fixed << setprecision(2);
                        cout << "\t|\t\t\t\t\t      | RM" << movie[i].price << " |" << endl;
                        i++; //total movie number
                        infile.ignore();
                    }
                    cout << "\t|-------------------------------------------------------|" << endl;
                    infile.close();
                }
                
                cout << "\tChoose a movie: ";
                cin >> movieNo;

                if (movieNo <= i) { //choose movieNo within the movie number
                    mbbuyticket(movieNo, i, balance); //balance renew
                    system("cls");
                    buyticketChoice = true;
                }
                else { //movieNo chosen out of bound
                    cout << "\tInvalid input. Press ENTER to re-select again!" << endl;
                    cin.get();
                    cin.get();
                }
            } while (!buyticketChoice);

        }
        else if (choiceC == 3) { //wallet
            mbwallet(balance);
            system("cls");
        }
        else if (choiceC == 4) { //delete account
            mbcancelacc(current_idno, auto_logout); //'current_idno' = 'a' value bring into mbcancelacc function
            system("cls");
            if (auto_logout) //'auto_logout' value takeout from mbcancelacc function to do IF function
                loginChoice = true; //quit from this whole loop
        }
        else if (choiceC == 5) { //logout
            cout << "\tThank for your support to our YSLL Cinema!" << endl;
            cout << "\tPress ENTER to proceed logout." << endl;
            cin.get();
            cin.get();
            system("cls");
            loginChoice = true;
        }

    } while(!loginChoice);
}

//member buy ticket
void mbbuyticket(int movieNo, int i, double& balance) { //i = total movie number

    movieType movie[arraySize];
    system("cls");
    system("color 0d");

    int date, time, numSeats = 0;
    double payment, totalPayment, change;

    while (true) {
        cout << "\t------------------------------" << endl;
        cout << "\t|       Date Available        |" << endl;
        cout << "\t------------------------------" << endl;
        cout << "\t|        1.16/4/2023          |" << endl;
        cout << "\t|        2.17/4/2023          |" << endl;
        cout << "\t|        3.18/4/2023          |" << endl;
        cout << "\t|        4.19/4/2023          |" << endl;
        cout << "\t|        5.20/4/2023          |" << endl;
        cout << "\t------------------------------" << endl;
        cout << "\tSelect a date: ";
        cin >> date;

        if (date >= 1 && date <= 5) {
            break;
        }
        else {
            cout << "Please enter a number between 1 to 5 only\n\n";
        }
    }
    cout << endl;
    system("CLS");

    while (true) {
        cout << "You have selected the date" << date << "." << endl;
        switch (date) {
        case 1:
            cout << "16/4/2023";
            break;
        case 2:
            cout << "17/4/2023";
            break;
        case 3:
            cout << "18/4/2023";
            break;
        case 4:
            cout << "19/4/2023";
        case 5:
            cout << "20/4/2023";
            break;
        }
        cout << endl;

        cout << "Do you want to change your selection? (Y/N): ";
        char choice;
        cin >> choice;
        system("CLS");

        if (choice == 'Y' || choice == 'y') {
            while (true) {
                cout << "\t------------------------------" << endl;
                cout << "\t|       Date Available        |" << endl;
                cout << "\t------------------------------" << endl;
                cout << "\t|        1.16/4/2023          |" << endl;
                cout << "\t|        2.17/4/2023          |" << endl;
                cout << "\t|        3.18/4/2023          |" << endl;
                cout << "\t|        4.19/4/2023          |" << endl;
                cout << "\t|        5.20/4/2023          |" << endl;
                cout << "\t-------------------------------" << endl;
                cout << "\tSelect a date: ";
                cin >> date;

                if (date >= 1 && date <= 5) {
                    break;
                }
                else {
                    cout << "Please enter a number between 1 to 5 only" << endl << endl;
                }
            }
            cout << endl;
            system("CLS");
        }
        else if (choice == 'N' || choice == 'n') {
            break;
        }
        else {
            cout << "Invalid input. Please enter Y or N only." << endl << endl;
        }
    }

    cout << "You have selected date " << date << "." << endl;
    switch (date) {
    case 1:
        cout << "16/4/2023";
        break;
    case 2:
        cout << "17/4/2023";
        break;
    case 3:
        cout << "18/4/2023";
        break;
    case 4:
        cout << "19/4/2023";
    case 5:
        cout << "20/4/2023";
        break;
    }
    cout << endl;
    system("CLS");

    //Choosing time section
    system("color 0e");
    while (true) {
        cout << "\t------------------------------" << endl;
        cout << "\t|         Time available     |" << endl;
        cout << "\t------------------------------" << endl;
        cout << "\t|         1. 10:00 AM        |" << endl;
        cout << "\t|         2. 01:15 PM        |" << endl;
        cout << "\t|         3. 01:45 PM        |" << endl;
        cout << "\t|         4. 03:45 PM        |" << endl;
        cout << "\t|         5. 04:15 PM        |" << endl;
        cout << "\t|         6. 06:45 PM        |" << endl;
        cout << "\t|         7. 09:15 PM        |" << endl;
        cout << "\t------------------------------" << endl;
        cout << "\tSelect a time: ";
        cin >> time;
        if (time >= 1 && time <= 7) {
            break;
        }
        else {
            cout << "Please enter a number between 1 to 7 only\n\n";
        }
    }
    cout << endl;
    system("CLS");

    while (true) {
        cout << "You have selected the time" << time << "." << endl;
        switch (time) {
        case 1:
            cout << "10:00 AM";
            break;
        case 2:
            cout << "01:15 PM";
            break;
        case 3:
            cout << "01:45 PM";
            break;
        case 4:
            cout << "03:45 PM";
            break;
        case 5:
            cout << "04:15 PM";
            break;
        case 6:
            cout << "06:45 PM";
            break;
        case 7:
            cout << "09:15 PM";
            break;
        }
        cout << endl;

        cout << "Do you want to change your selection? (Y/N): ";
        char choice;
        cin >> choice;
        system("CLS");

        if (choice == 'Y' || choice == 'y') {
            while (true) {
                cout << "\t------------------------------" << endl;
                cout << "\t|         Time available     |" << endl;
                cout << "\t------------------------------" << endl;
                cout << "\t|         1. 10:00 AM        |" << endl;
                cout << "\t|         2. 01:15 PM        |" << endl;
                cout << "\t|         3. 01:45 PM        |" << endl;
                cout << "\t|         4. 03:45 PM        |" << endl;
                cout << "\t|         5. 04:15 PM        |" << endl;
                cout << "\t|         6. 06:45 PM        |" << endl;
                cout << "\t|         7. 09:15 PM        |" << endl;
                cout << "\t------------------------------" << endl;
                cout << "\tSelect a time: ";
                cin >> time;

                if (time >= 1 && time <= 7) {
                    break;
                }
                else {
                    cout << "Please enter a number between 1 to 7 only" << endl << endl;
                }
            }
            cout << endl;
            system("CLS");
        }
        else if (choice == 'N' || choice == 'n') {
            break;
        }
        else {
            cout << "Invalid input. Please enter Y or N only." << endl << endl;
        }
    }

    cout << "You have selected time " << time << "." << endl;
    switch (time) {
    case 1:
        cout << "10.00 AM";
        break;
    case 2:
        cout << "01:15 PM";
        break;
    case 3:
        cout << "01:45 PM";
        break;
    case 4:
        cout << "03:45 PM";
        break;
    case 5:
        cout << "04:15 PM";
        break;
    case 6:
        cout << "06:45 PM";
        break;
    case 7:
        cout << "09:15 PM";
        break;
    }
    cout << endl;
    system("CLS");

    cout << endl;

    char choice = 'y';
    do {
        // print seating chart
        system("color 0e");
        cout << "\t\t----------------------------------------" << endl;
        cout << "\t\t|                                      |" << endl;
        cout << "\t\t----------------------------------------" << endl;
        cout << "\t\t\t\tSCREEN\n" << endl;

        print_seating_chart();

        // get user input
        cout << endl;
        cout << "\t\tEnter column number (1-" << columns << "): ";
        int seat;
        cin >> seat;
        cout << "\t\tEnter row number (1-" << rows << "): ";
        int row;
        cin >> row;

        // validate input
        if (row < 1 || row > rows || seat < 1 || seat > columns) {
            cout << "\t\tInvalid input. Press ENTER to select again." << endl;
            cin.get();
            cin.get();
            system("cls");
            continue; //skip below and loop again
        }

        // reserve seat
        bool reserved = reserve_seat(row, seat);
        if (reserved) {
            cout << "\t\tSeat reserved." << endl;
            numSeats++;
        }
        else {
            cout << "\t\tSeat is already reserved. Press ENTER to select again!" << endl;
            cout << endl;
            cin.get();
            cin.get();
            system("cls");
            continue;
        }

        // ask whether the user wants to reserve more seats or not
        cout << "\t\tDo you want to reserve more seats? (Y/N): ";
        cin >> choice;
        system("cls");
    } while (choice == 'Y' || choice == 'y');



    // calculate total cost
    totalPayment = calculate_total_cost(numSeats, movieNo);

    // display the total payment for the user 
    cout << endl << endl;
    cout << "\t\tTotal price is: RM" << totalPayment << endl;
    cout << "\t\tWallet balance is: RM" << balance << endl;

    // calculate change for the extra payment
    change = balance - totalPayment;
    bool payment_successful = true;

    // output change of extra payment or error message
    if (change >= 0) {
        balance = change;
        cout << "\t\tChange: RM" << change << endl;
        cout << "\t\tThank you for purchasing and have a good day :)!" << endl;
        cout << endl;
    }
    else {
        cout << "\t\t\033[31mError: Insufficient amount.\033[0m" << endl;
        cout << "\t\t\033[31mPayment Unsuccessful, please top up WALLET before transaction.\033[0m" << endl;
        cout << "\t\t\033[31mPress ENTER return back to Member Menu.\033[0m" << endl;
        cin.get();
        cin.get();
        payment_successful = false;
    }

    cout << endl;


    while (payment_successful) {
        cout << "\t\t-------------------------------------------------" << endl;
        cout << "\t\t*              YSLL Cinema Receipt              *" << endl;
        cout << "\t\t-------------------------------------------------" << endl;
        cout << "\t\t*Movie Title: ";

        ifstream infile("cinema.txt");
        while (!infile.eof()) {
            for (int a = 0; a < i; a++) {
                getline(infile, movie[a].name);
                infile >> movie[a].price;
                infile.ignore();
            }
        }
        infile.close();

        cout << movie[movieNo - 1].name;

        cout << endl;

        cout << "\t\t*Movie Date: ";
        switch (date) {
        case 1:
            cout << "16/4/2023";
            break;
        case 2:
            cout << "17/4/2023";
            break;
        case 3:
            cout << "18/4/2023";
            break;
        case 4:
            cout << "19/4/2023";
        case 5:
            cout << "20/4/2023";
            break;
        }
        cout << endl;

        cout << "\t\t*Movie Time: ";
        switch (time) {
        case 1:
            cout << "10.00 AM";
            break;
        case 2:
            cout << "01:15 PM";
            break;
        case 3:
            cout << "01:45 PM";
            break;
        case 4:
            cout << "03:45 PM";
            break;
        case 5:
            cout << "04:15 PM";
            break;
        case 6:
            cout << "06:45 PM";
            break;
        case 7:
            cout << "09:15 PM";
            break;
        }
        cout << endl;

        cout << "\t\t|\t\t\t\t\t\t|" << endl;
        cout << "\t\t|" << "Total payment:RM" << totalPayment << "\t\t\t\t|" << endl;
        cout << "\t\t|\t\t\t\t\t\t|" << endl;
        cout << "\t\t|Show this ticket to the counter to clarify\t| " << endl;
        cout << "\t\t|the ticket validity due to security reason\t|" << endl;
        cout << "\t\t|then only assign according to the seating\t|" << endl;
        cout << "\t\t|postion. Sorry for problem caused.\t\t|" << endl;
        cout << "\t\t|\t\t\t\t\t\t|" << endl;
        cout << "\t\t|\t\t\t\t\t\t|" << endl;
        cout << "\t\t|Have a great day! :)\t\tQR CODE\t\t|" << endl;
        cout << "\t\t|\t\t\t\t*********\t|" << endl;
        cout << "\t\t|\t\t\t\t*\t*\t|" << endl;
        cout << "\t\t|\t\t\t\t*\t*\t|" << endl;
        cout << "\t\t|\t\t\t\t*********\t|" << endl;
        cout << "\t\t|\t\t\t\t\t\t|" << endl;
        cout << "\t\t-------------------------------------------------" << endl;

        cin.get();
        cin.get();
        payment_successful = false;
    }
}

//choose cinema seat
void print_seating_chart() {

    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t";
        for (int j = 0; j < columns; j++) {
            if (seats[i][j] == 0) {
                cout << "O ";
            }
            else {
                cout << "X ";
            }
        }
        cout << endl;
    }
}

//calculate total payment of the chosen movie with chosen how many seats
double calculate_total_cost(int numSeats, int movieNo) {
    movieType movie[arraySize];
    ifstream infile("cinema.txt");
    int i = 0;
    while (!infile.eof()) {
        infile.ignore();
        getline(infile, movie[i].name);
        infile >> movie[i].price;
        i++;
    }
    return numSeats * movie[movieNo-1].price;
}

//chosen seat reserved
bool reserve_seat(int row, int seat) {
    if (seats[row - 1][seat - 1] == 0) {
        seats[row - 1][seat - 1] = 1;
        return true;
    }
    else {
        return false;
    }
}

//member wallet
void mbwallet(double& balance) {

    int topup;
    char topupChoice;
    bool topupexit = false;

    system("cls");
    cout << "\t|-----------------------------|" << endl;
    cout << "\t|           Wallet            |" << endl;
    cout << "\t|-----------------------------|" << endl;
    cout << fixed << setprecision(2);
    cout << "\t     Balance = RM" << balance << endl;
    cout << "\t|-----------------------------|" << endl;
    cout << "\tWould you like to top up your wallet?(Y/N): ";
    cin >> topupChoice;

    while (topupChoice != 'Y' && topupChoice != 'y' && topupChoice != 'N' && topupChoice != 'n'){
        cout << "\tInvalid input. Please re-type again! (Y-Yes, N-No): ";
        cin >> topupChoice;
    }

    if (topupChoice == 'Y' || topupChoice == 'y') {

        system("cls");
        cout << "\t|----------------|" << endl;
        cout << "\t| Top Up Service |" << endl;
        cout << "\t|----------------|" << endl;
        cout << "\t|      RM10      |" << endl;
        cout << "\t|      RM20      |" << endl;
        cout << "\t|      RM50      |" << endl;
        cout << "\t|      RM100     |" << endl;
        cout << "\t|----------------|" << endl;
        do {
            cout << endl;
            cout << "\tPlease key in a value to TOPUP: ";
            cin >> topup;

            switch (topup) {
            case 10: {
                balance += topup;
                break;
            }
            case 20: {
                balance += topup;
                break;
            }
            case 50: {
                balance += topup;
                break;
            }
            case 100: {
                balance += topup;
                break;
            }
            default: {
                cout << "\tInvalid input. Please re-type TOPUP value!" << endl;
                continue;
            }
            }

            cout << "\tWould you like to TOP UP again? (Y/N): ";
            cin >> topupChoice;

            while (topupChoice != 'Y' && topupChoice != 'y' && topupChoice != 'N' && topupChoice != 'n') {
                cout << "\tInvalid input. Please re-type again! (Y-Yes, N-No): ";
                cin >> topupChoice;
            }
            //if (topupChoice == 'Y' || topupChoice == 'y') loop again

            if (topupChoice == 'N' || topupChoice == 'n') {
                cout << "\tPress ENTER to return back to Member MENU." << endl;
                cin.get();
                cin.get();
                topupexit = true;
            }

        } while (!topupexit);

    }

    else if (topupChoice == 'N' || topupChoice == 'n') {
        cout << "\tPress ENTER to return back to Member MENU." << endl;
        cin.get();
        cin.get();
    }
}

//member delete account
void mbcancelacc(int current_idno, bool& auto_logout) { //'current_idno' come from 'a'
    
    int i = 0;
    char deleteChoice;
    memberSign member[arraySize];
    ifstream infile("member.txt", ios::app);

    while (!infile.eof()) {
        getline(infile, member[i].name);
        infile.getline(member[i].password, pwSize);
        i++;
    }
    infile.close();

    cout << "\tDo you want to delete your current account? (Y/N): ";
    cin >> deleteChoice;

    while (deleteChoice != 'Y' && deleteChoice != 'y' && deleteChoice != 'N' && deleteChoice != 'n') {
        cout << "\t\033[031mInvalid input. Please re-type again! (Y-Yes, N-No): \033[0m";
        cin >> deleteChoice;
    }

    if (deleteChoice == 'Y' || deleteChoice == 'y') {

        ofstream outfile("member.txt", ios::trunc); //rewrite the file

        for (int a = 0; a < i-1; a++) {
            if ((member[a].name == member[current_idno].name) && (strcmp(member[a].password,member[current_idno].password) == 0)) {
                
                member[a].name = member[a + 1].name; //replace
                strcpy_s(member[a].password, member[a + 1].password); //replace

                if (a != 0)
                    outfile << endl;
                outfile << member[a].name << endl; //write in file
                outfile << member[a].password; //write in file
            }
            
            else if ((member[a].name != member[current_idno].name) || (strcmp(member[a].password, member[current_idno].password) == -1)) {

                if (a != 0)
                    outfile << endl;
                outfile << member[a].name << endl; //write back to file
                outfile << member[a].password; //write back to file
            }
        }
        outfile.close();
        cout << "\tAccount deleted. Press ENTER auto logout..." << endl;
        cin.get();
        cin.get();
        auto_logout = true;
    }
    else if (deleteChoice == 'N' || deleteChoice == 'n') {
        cout << "\tPress ENTER return back to Member MENU." << endl;
        cin.get();
        cin.get();
    }


}

//admin menu
void admMenu(int& choice) {

    system("color 0a");
    cout << "\t|--------------------------------------|" << endl;
    cout << "\t|  YSLL Cinema - Admin Operating Menu  |" << endl;
    cout << "\t|--------------------------------------|" << endl;
    cout << "\t|1. Movie List                         |" << endl;
    cout << "\t|2. Add Movie                          |" << endl;
    cout << "\t|3. Delete Movie                       |" << endl;
    cout << "\t|4. Back                               |" << endl;
    cout << "\t|--------------------------------------|" << endl;
    cout << "\t    Please input a selection: ";
    cin >> choice;
}

//view movie
void read() {

    ifstream infile("cinema.txt", ios::app);
    movieType movie[arraySize];
    int i = 0;

    system("cls");
    cout << "\t|-------------------------------------------------------|" << endl;
    cout << "\t|\t\t\tMovie List\t\t\t|" << endl;
    cout << "\t|-------------------------------------------------------|" << endl;
    cout << "\t| Name\t\t\t\t\t      | Price   |" << endl;
    cout << "\t|-------------------------------------------------------|" << endl;

    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile, movie[i].name);
            infile >> movie[i].price;
            cout << "\t| " << i+1 << ". " << movie[i].name << endl;
            cout << fixed << setprecision(2);
            cout << "\t|\t\t\t\t\t      | RM" << movie[i].price << " |" << endl;
            i++;
            infile.ignore();
        }
        cout << "\t|-------------------------------------------------------|" << endl;
        infile.close();
    }
    else
        cout << "\tUnable to open storing file!" << endl;

    cout << "\tPress ENTER to return back to Operating Menu." << endl;
    cin.get();
    cin.get();
    system("cls");
}

//add movie
void add() {

    ifstream infile("cinema.txt", ios::app);
    ofstream outfile("cinema.txt", ios::app);
    movieType movie[arraySize];
    char addMovie;

    do {
        int i = 0;
        while (!infile.eof()) {
            getline(infile, movie[i].name);
            infile >> movie[i].price;
            i++;
            infile.ignore();
        }
        cout << endl;
        cout << "\tAdd Movie" << endl;
        cout << "\tName: ";
        outfile << endl;
        cin.ignore();
        getline(cin, movie[i].name);
        outfile << movie[i].name << endl;
        cout << "\tPrice: ";
        cin >> movie[i].price;
        outfile << movie[i].price;

        cout << "\tDo you want to add more movie?(Y/N): ";
        cin >> addMovie;

        while (addMovie != 'Y' && addMovie != 'y' && addMovie != 'N' && addMovie != 'n') {
            cout << "\tInvalid input. Please type again (Y-Yes, N-No): ";
            cin >> addMovie;
        }

    } while (addMovie == 'Y' || addMovie == 'y');

    infile.close();
    outfile.close();

    cout << endl;
    cout << "\tPress ENTER to return back to Operating Menu." << endl;
    cin.get();
    cin.get();
    system("cls");
}

//delete movie
void dlt() {
    movieType movie[arraySize];
    int i, a = 0, dlno;
    bool choice = false;

    do {
        ifstream infile("cinema.txt", ios::app);
        i = 0;
        system("cls");

        cout << "\tPlease choose a movie to delete." << endl;
        cout << "\t|-------------------------------------------------------|" << endl;
        cout << "\t|\t\t\tMovie List\t\t\t|" << endl;
        cout << "\t|-------------------------------------------------------|" << endl;
        cout << "\t| Name\t\t\t\t\t      | Price   |" << endl;
        cout << "\t|-------------------------------------------------------|" << endl;

        if (infile.is_open()) {
            while (!infile.eof()) {
                getline(infile, movie[i].name);
                infile >> movie[i].price;
                cout << "\t| " << i + 1 << ". " << movie[i].name << endl;
                cout << fixed << setprecision(2);
                cout << "\t|\t\t\t\t\t      | RM" << movie[i].price << " |" << endl;
                i++;
                infile.ignore();
            }
            cout << "\t|-------------------------------------------------------|" << endl;
            cout << endl;
            infile.close();
        }
        else
            cout << "Unable to open storing file!" << endl;
        //i is the total number of movie
        //i - 1 is the index of last movie
        cout << "\tWhich one you want to delete? (Type MovieNo to Delete) : ";
        cin >> dlno;

        if (dlno <= i && dlno > 0)
            choice = true;

        else if (dlno > i || dlno <= 0) {
            cout << "\tInvalid input. Press ENTER to select again!" << endl;
            cin.get();
            cin.get();
        }
    } while (!choice);

    dlno -= 1; //dlno array or index position

    ofstream outfile("cinema.txt", ios::trunc); //rewrite the file

    while (a < i - 1) { //delete movie will be deducted from file, index also -1

        int pos = movie[a].name.find(movie[dlno].name, 0);

        if (pos != string::npos) {

            while (a < i - 1) {

                movie[a].name = movie[a + 1].name;
                movie[a].price = movie[a + 1].price;

                if (a != 0)
                    outfile << endl;
                outfile << movie[a].name << endl;
                outfile << movie[a].price;
                pos = movie[a].name.find(movie[dlno].name, pos + movie[dlno].name.length());
                a++;
            }
        }

        else if (pos == string::npos && (a != i - 1)) {
            if (a != 0)
                outfile << endl;
            outfile << movie[a].name << endl;
            outfile << movie[a].price;
            a++;
        }
    }

    outfile.close();
    cout << "\tPress ENTER to return back to Operating Menu." << endl;
    cin.get();
    cin.get();
    system("cls");
}