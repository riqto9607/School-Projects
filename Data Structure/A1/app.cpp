#include	<iostream>
#include	<iomanip>
#include	<cstdlib> 
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;
int choice;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

int CalculateJulianDay(Date);
int calculateDueDay(Date);
bool RedundantStudent(List, LibStudent);				//check function definition for comment on functionaities on each functions
bool DuplicateBook(LibStudent, LibBook);
void AddBookToStudentRec(LibBook&, LibBook&, int);
bool printf(List* list);

int main() {

	LibStudent s;
	char* id = s.id;
	int source, detail;
	char* callNum = s.book->callNum;
	List* list_stu = new List();
	List* type1 = new List(),
		* type2 = new List();

	//menu
	do {
		menu();
		switch (choice) {

		case 1:
			cout << "\n\n\nREAD FILE\n\n\n";
			if (!ReadFile("student.txt", list_stu))
				cout << "Read file failed." << endl;
			break;

		case 2:
			cout << "\n\n\nDELETE STUDENT RECORD\n\n";

			cout << "Please enter the student ID that you would like to delete:";
			cin >> s.id;

			if (DeleteRecord(list_stu, id))
				cout << "\n" << "The student has been successfully deleted.\n\n\n";

			else
				cout << "\n" << "Sorry,the student cannot be found.\n\n\n";
			break;

		case 3:
			cout << "\n\n\nSEARCH STUDENT\n\n";

			cout << "Please enter the student ID that you would like to search:";
			cin >> s.id;

			if (SearchStudent(list_stu, id, s)) {
				cout << "\n" << "The informations of the student are shown below:";
				s.print(cout);
				cout << "\n" << "The student has successfully searched.\n\n\n";
			}
			else
				cout << "\n" << "Sorry,the student cannot be found.\n\n\n";
			break;

		case 4:
			cout << "\n\n\nINSERT BOOK\n\n";
			if (InsertBook("book.txt", list_stu));
			break;

		case 5:
			cout << "\n\n\nDISPLAY OUTPUT\n\n\n";

			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;

			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;

			if (!Display(list_stu, source, detail))
				cout << "Cannot display student list.\n\n\n";
			break;

		case 6:
			cout << "\n\n\nCOMPUTE AND DISPLAY STUDENTS' STATISTICS\n\n\n";
			if (computeAndDisplayStatistics(list_stu));
			break;
		case 7:
			cout << "\n\n\nDISPLAY STUDENT WITH SAME BOOK\n\n\n";
			cout << "Please enter the book Call Number:";
			cin >> callNum;
			printStuWithSameBook(list_stu, callNum);
			break;
		case 8:
			cout << "\n\n\nDISPLAY WARNED STUDENT\n\n";
			if (!displayWarnedStudent(list_stu, type1, type2))
				cout << "Cannot display any student in WARNING.\n\n\n";
			else
				cout << "Successfully display warning student.\n\n\n";
			break;
		case 9:
			break;
		default:
			cout << "\n\n\nInvalid Choice. Please Choose the Task Again.\n\n\n";
		}
		cout << "\n\n";
	} while (choice != 9);
	cout << "\n\n";
	system("pause");
	return 0;
}

int menu() {

	cout << "Menu\n\n";

	cout << "1. Read file.\n";
	cout << "2. Delete record.\n";
	cout << "3. Search student.\n";
	cout << "4. Insert book.\n";
	cout << "5. Display output\n";
	cout << "6. Compute and Display Statistics\n";
	cout << "7. Student with Same Book\n";
	cout << "8. Diplay Warned Student\n";
	cout << "9. Exit.\n";
	cout << "Enter your choice: ";
	cin >> choice;

	return choice;
}

bool ReadFile(string filename, List* list) {

	ifstream in;
	in.open(filename);

	if (!in) {
		cout << "Unable to open file.\n";
		return false;
	}
	else {
		char s[256];
		LibStudent temp;

		while (in >> s) {
			for (int i = 0; i < 2; i++) {
				in >> s;
			}
			in >> temp.id;
			for (int i = 0; i < 2; i++) {
				in >> s;
			}
			in >> temp.name;				//getting student name
			in.getline(s, 256);			//getting the rest 
			strcat(temp.name, s);				//combine 
			for (int i = 0; i < 2; i++) {
				in >> s;
			}
			in >> temp.course;
			for (int i = 0; i < 3; i++) {
				in >> s;
			}
			in >> temp.phone_no;

			if (!RedundantStudent(*list, temp))
				list->insert(temp);
			else
				cout << "Duplicated record found: " << temp.name << endl;
		}
		cout << "\n" << list->size() << " records have been successfully read.\n";
		return true;
	}
	return false;
}

bool DeleteRecord(List* list, char* id) {

	Node* cur = list->head;
	int dlCount = 1;

	// Traverse the linked list to find the student with the given ID
	while (cur != NULL) {
		if (strcmp(cur->item.id, id) == 0) {
			// Found the student with the given ID

			list->remove(dlCount);
			return true; // Deletion successful
		}
		cur = cur->next;
		dlCount++;
	}

	return false; // Student with input ID not found

}

bool SearchStudent(List* list, char* id, LibStudent& stu) {

	Node* cur = list->head;

	while (cur != NULL) {
		if (strcmp(cur->item.id, id) == 0) {
			// Found the student with the given ID
			stu = cur->item; // Copy student information to the provided LibStudent struct
			return true; // Search successful
		}
		cur = cur->next;
	}
	return false; // Student with input ID not found
}

bool InsertBook(string filename, List* list) {
	ifstream in;
	LibBook tmp_book;			//maximum number of borrowed books is 15
	char tmp_id[10];			//7-digit student id
	char tmp_author[100];

	in.open(filename);			//checking if file is opened

	if (!in)
	{
		cout << "Unable to open file.\n";
		return false;
	}
	else //if file is opened
	{
		if (list->empty())
		{
			cout << "List is empty.\n";
			return false;
		}


		while (in >> tmp_id) {					//reading all the data
			in >> tmp_author >> tmp_book.title >> tmp_book.publisher >> tmp_book.ISBN >> tmp_book.yearPublished >> tmp_book.callNum;

			//date format in book.txt: DD/MM/YYYY
			//reading borrow date
			in >> tmp_book.borrow.day;
			in.ignore();					//ignore '/'
			in >> tmp_book.borrow.month;
			in.ignore();
			in >> tmp_book.borrow.year;

			//reading due date
			in >> tmp_book.due.day;
			in.ignore();
			in >> tmp_book.due.month;
			in.ignore();
			in >> tmp_book.due.year;

			//reading authors' name
			int num_author = 0;			//number of authors
			int index = 0;				//cstring index or position
			tmp_book.author[num_author] = new char[100];
			for (int i = 0; i <= strlen(tmp_author); i++)
			{
				if (tmp_author[i] == '_')										//special case: replace '_' with space
				{
					tmp_book.author[num_author][index] = ' ';
					index++;
				}
				else if (i == strlen(tmp_author)) {								//special case: already reached the end
					tmp_book.author[num_author][index] = '\0';
					break;
				}
				else if (tmp_author[i] == '/')									//special case: meets new author
				{
					tmp_book.author[num_author][index] = '\0';					//end the current cstring
					index = 0;
					num_author++;
					tmp_book.author[num_author] = new char[100];				//space for new author
				}
				else {
					tmp_book.author[num_author][index] = tmp_author[i];			//normal case: insert author's name 
					index++;
				}
			}

			//Eg: Data_Structures_and_Other_Objects_Using_C++ 
			for (int i = 0; i < strlen(tmp_book.title); i++)
			{
				if (tmp_book.title[i] == '_')
					tmp_book.title[i] = ' ';					//Replace with space
			}

			//Eg: Prentice_Hall
			for (int i = 0; i < strlen(tmp_book.publisher); i++)
			{
				if (tmp_book.publisher[i] == '_')
					tmp_book.publisher[i] = ' ';				//Replace with space
			}

			if (calculateDueDay(tmp_book.due) <= 0)
				tmp_book.fine = 0;
			else
				tmp_book.fine = calculateDueDay(tmp_book.due) * 0.50;		//overdue fine RM0.50 per day

			Node* cur = list->head;
			for (int i = 0; i < list->size(); i++)
			{
				if (strcmp(cur->item.id, tmp_id) == 0)
				{
					if (!DuplicateBook(cur->item, tmp_book))
					{
						//Copy the data from tmp_book to student list
						AddBookToStudentRec(cur->item.book[cur->item.totalbook], tmp_book, num_author);
						cur->item.totalbook++;
						cur->item.calculateTotalFine();
						break;
					}
				}
				cur = cur->next;
			}
			if (cur == NULL)
				cout << "Student not found.\n";				//cannot find the student id in the list
		}
		cout << "\n\nBooks inserted successfully to student list.\n\n";
		return true;
	}
	return false;
}

bool Display(List* list, int source, int detail) {

	Node* cur = list->head;

	switch (source) {
		//file
	case 1:

		if (detail == 1) {
			if (cur == NULL) {
				cout << "This list is empty" << endl;
				return false;
			}
			else {
				ofstream Myfile("student_booklist.txt");

				int i = 1;

				while (cur != NULL) {
					Myfile << "Student" << i << endl;
					cur->item.print(Myfile);
					for (int a = 0; a < cur->item.totalbook; a++) {

						cur->item.book[a].print(Myfile); //  the info  will be displayed into the student_booklist file
					}

					Myfile << "***************************" << endl;
					i = i + 1;
					cur = cur->next;
				}

				cout << " \n\nSuccessfully display output to student_booklist.txt\n\n";
				cout << " Successfully display output" << endl;

				Myfile.close();

				return true;
			}
		}

		else if (detail == 2) {
			if (cur == NULL) {
				cout << "This list is empty" << endl;
				return false;
			}

			ofstream Myfile("student_info.txt");

			int i = 1;
			while (cur != NULL) {
				Myfile << "Student" << i << endl;
				cur->item.print(Myfile); // the info will be print into the student_info.txt file
				Myfile << " *************************** " << endl;
				i = i + 1;
				cur = cur->next;
			}
			cout << "\n\nSuccessfully display output to student_info.txt\n\n";
			cout << "Successfully display output" << endl;
			Myfile.close();
			return true;
		}

		else cout << "Wrong output" << endl;

		break;

	case 2:
		//screen
		if (detail == 1) {
			if (cur == NULL) {
				cout << "This list is empty" << endl;
				return false;
			}
			int i = 1;
			while (cur != NULL) {
				cout << "Student" << i << endl;
				cur->item.print(cout);
				for (int a = 0; a < cur->item.totalbook; a++) {
					cur->item.book[a].print(cout); // the info from student_booklist will be shown on the screen
				}
				cout << "***************************" << endl;
				i = i + 1;
				cur = cur->next;
			}
			cout << "Successfully display output" << endl;
			return true;
		}
		else if (detail == 2) {
			if (cur == NULL) {
				cout << "This list is empty" << endl;
				return false;
			}
			int i = 1;
			while (cur != NULL) {

				cout << "Student" << i << endl;
				cur->item.print(cout); //the info from student_list  will be shown on the screen
				cout << "***************************" << endl;
				i = i + 1;
				cur = cur->next;
			}
			cout << "Successfully display output" << endl;
			return true;
		}
		else
			cout << "Wrong Input" << endl;
		break;

	default:
		cout << "Wrong Input " << endl;
		break;
	}
	return true;
}

bool computeAndDisplayStatistics(List* list) {
	Node* cur = list->head;
	int count = 0;
	if (cur == NULL) {
		cout << "\n\nList is an empty list.\n\n";
		return false;
	}
	cout << left << setw(8) << "Course" << setw(20) << "Number of Students" << setw(25)
		<< "Total Books Borrowed" << setw(25) << "Total Overdued Books" << setw(25)
		<< "Total Fine (RM)" << endl;
	while (cur != NULL) {
		type temp;
		int	no_student = 0, total_book = 0, total_overdue = 0;
		double total_fine = 0.0;
		bool check = false;
		if (cur == list->head) {					//when cur point to head of list 
			for (int i = 1; i <= list->size(); i++) {			//traverse list to compare their course
				list->get(i, temp);
				if (strcmp(temp.course, cur->item.course) == 0) {		//if there is course same with current list course
					no_student++;
					total_book += temp.totalbook;						//calculation
					total_fine += temp.total_fine;
					for (int k = 0; k < temp.totalbook; k++) {
						if (temp.book[k].fine > 0.0) {
							total_overdue++;
						}
					}
				}
			}
			cout << left << setw(15) << cur->item.course << setw(23) << no_student << setw(25)
				<< total_book << setw(20) << total_overdue << setw(20) << fixed << setprecision(2)
				<< total_fine << endl;
		}
		else {
			Node* cmp = list->head;
			for (int j = 0; j < count; j++) {			//to check whether the course already process or not
				if (strcmp(cmp->item.course, cur->item.course) == 0) {
					check = true;
					break;
				}
				cmp = cmp->next;
			}
			if (!check) {			//course not yet process
				for (int i = 1; i <= list->size(); i++) {		//same with above
					list->get(i, temp);
					if (strcmp(temp.course, cur->item.course) == 0) {
						no_student++;
						total_book += temp.totalbook;
						total_fine += temp.total_fine;
						for (int k = 0; k < temp.totalbook; k++) {
							if (temp.book[k].fine > 0.0) {
								total_overdue++;
							}
						}
					}
				}
				cout << left << setw(15) << cur->item.course << setw(23) << no_student << setw(25)
					<< total_book << setw(20) << total_overdue << setw(20) << fixed << setprecision(2)
					<< total_fine << endl;
			}
		}
		cur = cur->next;
		count++;
	}
	return true;
}

bool printStuWithSameBook(List* list, char* callNum) {

	Node* cur = list->head;
	List* templist = new List();
	int count = 0;

	if (cur == NULL) { // No one has borrowed the book which has the entered call Number
		cout << "\n\nThis list is an empty list.\n\n";
		return false;

	}
	while (cur != NULL) {

		for (int i = 0; i < cur->item.totalbook; i++) {

			if (strcmp(callNum, cur->item.book[i].callNum) == 0) {
				templist->insert(cur->item);
				count++;
			}
		}
		cur = cur->next;
	}

	if (templist == NULL) { // The entered call Number is wrong or does not exist
		cout << "Invalid callNum. Cannot find the book.\n\n";
		return false;
	}

	cout << "There are " << count << " students that borrow the book with call number " << callNum << " as shown below:\n\n";
	if (printf(templist)); // shows the total number of people who has borrowed the book with the entered call Number
	else
		cout << "No student with same book.\n\n";

	return true;

}

bool displayWarnedStudent(List* list, List* type1, List* type2) {

	Node* cur = list->head;

	//special case 1
	if (cur == NULL) {
		cout << "\n\nList is an empty list.\n\n";											//haven't read file yet to store student info inside the linked list
		return false;
	}

	//list traversal
	while (cur != NULL) {

		int type1_bookoverdue = 0;
		int type2_bookoverdue = 0;

		for (int i = 0; i < cur->item.totalbook; i++) {

			//type1
			int dueDay = calculateDueDay(cur->item.book[i].due);

			if (dueDay >= 10)																//student book overdue more than or equal to 10
				type1_bookoverdue++;														//no of book overdue

			if (type1_bookoverdue > 2) {													//more than 2 books that overdue >= 10
				if (!RedundantStudent(*type1, cur->item))									//if display the second time, make sure no redundant student display
					type1->insert(cur->item);
			}

			//type2
			if (dueDay > 0)
				type2_bookoverdue++;

			if (cur->item.total_fine > 50 && type2_bookoverdue == cur->item.totalbook) {	//student total fine more than RM50 and every book are overdue
				if (!RedundantStudent(*type2, cur->item))									//if display the second time, make sure no redundant student display
					type2->insert(cur->item);
			}
		}
		cur = cur->next;
	}

	//special case 2
	if (type1->head == NULL && type2->head == NULL) {										//no warning student in type1 and type2
		cout << "\n\nNo Warning Student.\n\n\n";
		return false;
	}

	Node* tmp1;
	tmp1 = type1->head;
	int stutype1_count = 1;

	if (tmp1 == NULL)
		cout << "\n\nNo student have borrowed more than 2 books that are overdue for >= 10 days.\n\n\n";

	//type1 display
	else {
		cout << "\n***************************TYPE 1 STUDENT LIST*******************************\n\n";
		while (tmp1 != NULL) {																//traverse list to print student info and book list
			cout << "\nStudent " << stutype1_count << "\n";
			tmp1->item.print(cout);
			for (int i = 0; i < tmp1->item.totalbook; i++) {
				cout << "\n\nBook " << i + 1 << "\n\n";
				tmp1->item.book[i].print(cout);
			}
			tmp1 = tmp1->next;
			stutype1_count++;
			cout << "\n\n*****************************************************************************\n\n";
		}
	}
	Node* tmp2;
	tmp2 = type2->head;
	int stutype2_count = 1;

	if (tmp2 == NULL)
		cout << "\n\nNo student owe a total fine of RM50 and every book borrowed are overdue.\n\n\n";

	//type2 display
	else {
		cout << "\n***************************TYPE 2 STUDENT LIST*******************************\n\n";
		while (tmp2 != NULL) {																//traverse list to print student info and book list
			cout << "\nStudent " << stutype2_count << "\n";
			tmp2->item.print(cout);
			for (int i = 0; i < tmp2->item.totalbook; i++) {
				cout << "\n\nBook " << i + 1 << "\n\n";
				tmp2->item.book[i].print(cout);
			}
			tmp2 = tmp2->next;
			stutype2_count++;
			cout << "\n\n*****************************************************************************\n\n";
		}
	}
	return true;
}

bool RedundantStudent(List list, LibStudent item)
{
	LibStudent temp;
	if (list.empty())
		return false;
	for (int i = 1; i <= list.size(); i++)
	{
		if (list.get(i, temp))
		{
			if (temp.compareName2(item))
				return true;
		}
	}
	return false;
}

int calculateDueDay(Date duedate) {

	//current date is 29/3/2020
	//one day delayed - RM0.50

	Date currentdate;
	currentdate.day = 29, currentdate.month = 3, currentdate.year = 2020;

	int duedate_julianDay = CalculateJulianDay(duedate);
	int currentdate_julianDay = CalculateJulianDay(currentdate);

	int dueDay = currentdate_julianDay - duedate_julianDay;

	return dueDay;
}

int CalculateJulianDay(Date date) {							//the format of julian day

	int a = (14 - date.month) / 12;
	int y = date.year + 4800 - a;
	int m = date.month + 12 * a - 3;
	return date.day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

}

bool DuplicateBook(LibStudent stud, LibBook book) {
	LibBook temp;

	if (stud.totalbook == 0)		//empty
		return false;

	for (int i = 0; i < stud.totalbook; i++)
	{
		if (stud.book[i].compareCallNum(book))		//if same callNum then return true
			return true;
	}
	return false;		//not duplicate
}

void AddBookToStudentRec(LibBook& book1, LibBook& book2, int num_author) {			//copy tmp_book items into list
	strcpy(book1.title, book2.title);
	strcpy(book1.publisher, book2.publisher);
	strcpy(book1.ISBN, book2.ISBN);
	book1.yearPublished = book2.yearPublished;
	strcpy(book1.callNum, book2.callNum);
	book1.borrow.day = book2.borrow.day;
	book1.borrow.month = book2.borrow.month;
	book1.borrow.year = book2.borrow.year;
	book1.due.day = book2.due.day;
	book1.due.month = book2.due.month;
	book1.due.year = book2.due.year;
	book1.fine = book2.fine;

	for (int i = 0; i <= num_author; i++)		//using for-loop to insert author
	{
		book1.author[i] = book2.author[i];
	}
}

bool printf(List* list) {
	Node* tmp = list->head;
	if (tmp == NULL)
		return false;
	while (tmp != NULL) {
		cout << "Student Id = " << tmp->item.id << endl;
		cout << "Name = " << tmp->item.name << endl;
		cout << "Course = " << tmp->item.course << endl;
		cout << "Phone Number = " << tmp->item.phone_no << endl;
		cout << "Borrow Date: ";
		tmp->item.book->borrow.print(cout);
		cout << endl;
		cout << "Due Date: ";
		tmp->item.book->due.print(cout);
		cout << "\n\n";
		tmp = tmp->next;
	}
	return true;
}