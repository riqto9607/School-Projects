#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include    <queue>
#include	"BST.h"
#include    "Student.h"


using namespace std;
int choice;

bool readFile(const char*, BST*);
bool redundantStudent(BTNode*, Student);

int menu();

int main() {

	char file[] = "student.txt";
	BST list;
	BST t2;
	Student stu;
	int order, source;


	//menu
	do {
		menu();
		switch (choice) {

		case 1:
			//Question a
			cout << "\n\nREAD STUDENT FILE\n\n";
			if (readFile(file, &list));
			break;

		case 2:
			//Question b
			cout << "\n\nPRINT STUDENT IN DEEPEST NODES\n\n";
			if (!list.deepestNodes());
			break;

		case 3:
			//Question c
			cout << "\n\nPRINT STUDENT INFORMATION\n\n";

			cout << "Order to print (1 = ascending, 2 = descending) :";
			cin >> order;
			cout << "Source to print (1 = screen, 2 = file) :";
			cin >> source;

			if (list.display(order, source))
				break;
			else
				break;

		case 4:
			//Question d
			cout << "Please enter student ID: ";
			cin >> stu.id;
			cout << "\n\nCLONE SUBTREE\n\n";
			if (t2.CloneSubtree(list, stu));
			break;

		case 5:
			//Question e
			cout << "\n\nPRINT STUDENT IN LEVEL NODES\n\n";

			if (!list.printLevelNodes());
			break;

		case 6:
			//Question f
			cout << "\n\nPRINT PATH\n\n";
			if (!list.printPath())
				break;
			else 
				break;

		case 7:
			//Exit
			cout << "Exit Successful!";
			break;

		default:
			cout << "\n\nInvalid Choice. Please Choose the Task Again.\n\n";
		}
		cout << "\n\n";
	} while (choice != 7);
	cout << "\n\n";
	system("pause");
	return 0;
}

int menu() {

	cout << "Menu\n\n";

	cout << "(1) Read data to BST\n";
	cout << "(2) Print deepest nodes\n";
	cout << "(3) Display student\n";
	cout << "(4) Clone subtree\n";
	cout << "(5) Print Level Nodes\n";
	cout << "(6) Print Path\n";
	cout << "(7) Exit\n";

	cout << "Enter your choice: ";
	cin >> choice;

	return choice;
}


bool readFile(const char* filename, BST* t1) {

	ifstream in(filename);
	Student stu;

	if (!in) {
		cout << "Fail to open file " << filename << "!\n";
		return false;
	}

	else {

		char s[200];

		while (in >> s) {

			for (int i = 0; i < 2; i++)
				in >> s;
			in >> stu.id;				//get student id

			for (int i = 0; i < 2; i++)
				in >> s;
			in.ignore();
			in.getline(stu.name, 30);   //get student name

			for (int i = 0; i < 2; i++)
				in >> s;
			in.ignore();
			in.getline(stu.address, 100);	//get student address

			for (int i = 0; i < 2; i++)
				in >> s;
			in >> stu.DOB;				//get student birthday 

			for (int i = 0; i < 3; i++)
				in >> s;
			in >> stu.phone_no;				//get student phone number

			for (int i = 0; i < 2; i++)
				in >> s;
			in >> stu.course;				//get student course

			for (int i = 0; i < 2; i++)
				in >> s;
			in >> stu.cgpa;					//get student cgpa

			BTNode* temp = t1->root;

			if (!redundantStudent(temp, stu))		//check redundant 
				t1->insert(stu);
			else
				cout << "Duplicated record found: " << stu.name << endl;
		}


		cout << t1->size() << " number of student records have been successfully read.\n";
		in.close();
		return true;
	}

}

bool redundantStudent(BTNode* cur, Student stu) {

	// stu - student information to check
	// cur - traverse node

	while (cur != NULL) {

		if (cur->item.compare2(stu))
			return true; // Redundant student found

		if (stu.id < cur->item.id)
			cur = cur->left;
		else
			cur = cur->right;

	}

	return false; // No redundant student found
}
