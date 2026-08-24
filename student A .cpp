#include <iostream>
#include <string>
#include<fstream>
#include <cctype>   
#include <cstdlib>  
#include <limits>
using namespace std;

const int maxrow = 10;
const int maxUsers = 10;



string StuName[maxrow] = {};
string StuID[maxrow] = {};

string teacherID[maxUsers];
string teacherPassword[maxUsers];
int teacherCount = 0;

string studentUserID[maxUsers];
string studentUserPassword[maxUsers];
int studentCount = 0;
void displayLogo();
bool teacherRegister();
bool teacherLogin();
void teacher_menu();
bool studentRegister();
bool studentLogin();
void student_menu();
void OpenFile();
void SaveToFile();
void SaveAccounts();

void clearScreen() { system("CLS"); }



string validateString(string message) {
	string input;
	do {
		cout << message;
		getline(cin, input);
		if (input.empty())
			cout << "[ERROR] Input cannot be empty. Please enter again.\n";
	} while (input.empty());
	return input;
}

int checkNumSelection(int num, int maxSelection) {
	while (num <= 0 || num > maxSelection) {
		cout << "[ERROR] Invalid input! Please enter 1-" << maxSelection << " only: ";
		cin >> num;
	}
	return num;
}


char checkRole() {
	char role;
	cout << "Welcome to Student Record Management\n";
	cout << "Please enter your role (T-Teacher, S-Student, E-Exit): ";
	cin >> role;
	role = toupper(role);

	while (role != 'T' && role != 'S' && role != 'E') {
		cout << "[ERROR] Invalid input! Please enter T, S, or E: ";
		cin >> role;
		role = toupper(role);
	}

	return role;
}


// Check if the user wants to login or register
char checkAction() {
	char action;
	cout << "Do you want to (L)Login or (R)Register? ";
	cin >> action;
	action = toupper(action);

	while (action != 'L' && action != 'R') {
		cout << "[ERROR] Invalid input! Please enter L or R: ";
		cin >> action;
		action = toupper(action);
	}
	return action;
}


// Teacher selection function
void teacherSelection() {
	char action = checkAction();
	bool loginStatus = false;

	if (action == 'R') {
		teacherRegister();
		cout << "Please login with your new account.\n";
		loginStatus = teacherLogin();
	}
	else {
		loginStatus = teacherLogin();
	}

	if (loginStatus) {
		teacher_menu();
	}
}


// Student selection function
void studentSelection() {
	char action = checkAction();
	bool loginStatus = false;

	if (action == 'R') {
		studentRegister();
		cout << "Please login with your new account.\n";
		loginStatus = studentLogin();
	}
	else {
		loginStatus = studentLogin();
	}

	if (loginStatus) {
		student_menu();
	}
}

// logo
void displayLogo() {


	cout << "==============================\n";
	cout << "  Student Record Management   \n";
	cout << "============================== \n";
	cout << "								   \n";
	cout << "								   \n";
	cout << "     /\\________________/\\\n";
	cout << "    /                    \\\n";
	cout << "   /______________________\\\n";
	cout << "   |   |    |    |    |   |\n";
	cout << "   |   |    |    |    |   |\n";
	cout << "   |   |    |    |    |   |\n";
	cout << "   |   |    |    |    |   |\n";
	cout << "   |   |    |    |    |   |\n";
	cout << "   |   |    |    |    |   |\n";
	cout << "   |___|____|____|____|___|\n";
	cout << "   |______________________|\n";

	cout << "        L I B R A R Y\n";
	cout << "       KNOWLEDGE FOR ALL\n";




}
// teacher register function
bool teacherRegister() {
	if (teacherCount >= maxUsers) {
		cout << "[ERROR] Teacher account list is full!\n";
		return false;
	}

	string id, password;
	cin.ignore();
	id = validateString("Create Teacher ID: ");

	for (int i = 0; i < teacherCount; i++) {
		if (teacherID[i] == id) {
			cout << "[ERROR] This ID is already registered!\n";
			return false;
		}
	}

	password = validateString("Create Password: ");

	teacherID[teacherCount] = id;
	teacherPassword[teacherCount] = password;
	teacherCount++;

	SaveAccounts();
	cout << "[OK] Teacher account registered successfully!\n";
	return true;
}



// teacher login function
bool teacherLogin() {
	string id, password;

	clearScreen();
	displayLogo();
	cout << "=========================================\n";
	cout << "Teacher Login Screen\n";
	cout << "=========================================\n";
	cout << "Enter ID: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Password: ";
	getline(cin, password);

	for (int i = 0; i < teacherCount; i++) {
		if (id == teacherID[i] && password == teacherPassword[i]) {
			cout << "[OK] Login Successful.\n";
			system("pause");
			return true;
		}
	}

	cout << "[ERROR] Wrong ID or Password.\n";
	system("pause");
	return false;
}

// ---------- student register / login ----------
bool studentRegister() {
	if (studentCount >= maxUsers) {
		cout << "[ERROR] Student account list is full!\n";
		return false;
	}

	string id, password;
	cin.ignore();
	id = validateString("Create Student Login ID: ");

	for (int i = 0; i < studentCount; i++) {
		if (studentUserID[i] == id) {
			cout << "[ERROR] This ID is already registered!\n";
			return false;
		}
	}

	password = validateString("Create Password: ");

	studentUserID[studentCount] = id;
	studentUserPassword[studentCount] = password;
	studentCount++;

	SaveAccounts();
	cout << "[OK] Student account registered successfully!\n";
	return true;
}

// student login function
bool studentLogin() {
	string id, password;

	clearScreen();
	displayLogo();
	cout << "=========================================\n";
	cout << "Student Login Screen\n";
	cout << "=========================================\n";
	cout << "Enter ID: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Password: ";
	getline(cin, password);

	for (int i = 0; i < studentCount; i++) {
		if (id == studentUserID[i] && password == studentUserPassword[i]) {
			cout << "[OK] Login Successful.\n";
			system("pause");
			return true;
		}
	}

	cout << "[ERROR] Wrong ID or Password.\n";
	system("pause");
	return false;
}




void OpenFile() {

	string line;
	ifstream myfile("student.txt");
	if (myfile.is_open())
	{
		int x = 0;
		while (x < maxrow && getline(myfile, line))
		{
			auto commaPos = line.find(',');
			StuID[x] = line.substr(0, commaPos);
			StuName[x] = line.substr(commaPos + 1);
			x++;
		}
	}
	else
	{
		cout << "Enable to open the fail!" << endl;
	}
}

// Add a new student record
void AddRecord() {
	char name[50];
	char stuID[5];
	cin.ignore();

	cout << "Student ID.";
	cin.getline(stuID, 5);
	cout << "Student Name.";
	cin.getline(name, 50);

	for (int x = 0; x < maxrow;x++)
	{
		if (StuID[x] == "\0")

		{
			StuID[x] = stuID;
			StuName[x] = name;

			break;
		}



	}
}




// Display all student records
void ListRecord()
{
	system("CLS");
	cout << "current recode(s)" << endl;
	cout << "================================" << endl;
	int counter = 0;
	cout << " No. |        student ID |        student Name" << endl << "--------------------------------" << endl;
	for (int x = 0; x < maxrow; x++)
	{
		if (StuID[x] != "\0") {
			counter++;
			cout << " " << counter << "   " << StuID[x] << "             " << StuName[x] << endl;
		}
	}


}


// Search for a student record by ID
void SearchRecord(string search) {
	system("CLS");
	cout << "Current Record(s)" << endl;
	cout << "================================" << endl;

	int counter = 0;
	cout << " No. |        student ID |        student Name" << endl << "--------------------------------" << endl;
	for (int x = 0; x < maxrow; x++)
	{
		if (StuID[x] != "") {
			if (StuID[x] == search) {
				counter++;
				cout << " " << counter << "   " << StuID[x] << "             " << StuName[x] << endl;
				break;
			}
		}
	}

	if (counter == 0) {
		cout << "No records found!" << endl;
	}
	cout << "================================" << endl;
}


// Update a student record by ID
void UpdateRecord(string search)
{
	char name[50];

	int counter = 0;

	for (int x = 0; x < maxrow; x++)
		if (StuID[x] == search)
		{
			counter++;

			cout << "Student Name: ";
			cin.getline(name, 50);

			StuName[x] = name;

			cout << "Update Successful!" << endl;
			break;
		}

	if (counter == 0)
	{
		cout << "No Student ID Found !" << endl;
	}
}


// Delete a student record by ID
void DeleteRecord(string search)
{
	int counter = 0;
	for (int x = 0; x < maxrow; x++)
	{
		if (StuID[x] == search)
		{
			counter++;

			StuName[x] = "";
			StuID[x] = "";

			cout << "Succesfully Deleted !" << endl;
			break;
		}
	}

	if (counter == 0)
	{
		cout << "ID Number does not exist";
	}

}

// Save all student records to a file
void SaveToFile()
{
	ofstream myfile;
	myfile.open("student.txt");
	if (!myfile.is_open())
	{
		cout << "Could not open file for saving!" << endl;
		return;
	}
	for (int x = 0; x < maxrow; x++)
	{
		if (StuID[x] == "\0")
		{
			break;
		}
		else
		{
			myfile << StuID[x] + "," + StuName[x] << endl;
		}
	}
	cout << "Saved successfully!" << endl;
}

// Save all accounts to a file
void SaveAccounts()
{
	ofstream myfile;
	myfile.open("id.txt");
	if (!myfile.is_open())
	{
		cout << "Could not open file for saving accounts!" << endl;
		return;
	}

	for (int x = 0; x < teacherCount; x++)
	{
		myfile << "T," << teacherID[x] << "," << teacherPassword[x] << endl;
	}
	for (int x = 0; x < studentCount; x++)
	{
		myfile << "S," << studentUserID[x] << "," << studentUserPassword[x] << endl;
	}

	cout << "Accounts saved successfully!" << endl;
}
// Load accounts from file
void RegisterAccounts() {

	string line;
	ifstream myfile("id.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			auto firstComma = line.find(',');
			auto secondComma = line.find(',', firstComma + 1);
			if (firstComma == string::npos || secondComma == string::npos) continue;

			string type = line.substr(0, firstComma);
			string id = line.substr(firstComma + 1, secondComma - firstComma - 1);
			string password = line.substr(secondComma + 1);

			if (type == "T" && teacherCount < maxUsers) {
				teacherID[teacherCount] = id;
				teacherPassword[teacherCount] = password;
				teacherCount++;
			}
			else if (type == "S" && studentCount < maxUsers) {
				studentUserID [studentCount] = id;
				studentUserPassword [studentCount] = password;
				studentCount++;
			}
		}
		myfile.close();
	}
	else
	{
		cout << "No existing account file found. Starting fresh." << endl;
	}
}
// Return to the main menu
void Backtomenu() {
	cout << "Press any key to return to menu...";
	cin.ignore();
	cin.get();
	system("CLS");
}

// Teacher menu
void teacher_menu() {
	int option;
	string searchID;
	
	

	do {
		clearScreen();
		displayLogo();
		cout << "================================" << endl;
		cout << "teacher menu\n";
		cout << "================================" << endl;
		cout << "1-Create Student Records" << endl;
		cout << "2-Update Student Records" << endl;
		cout << "3-Delete Student Records" << endl;
		cout << "4-Search Student Records" << endl;
		cout << "5-Display all Student Records" << endl;
		cout << "6-Exit and Save to Textfile" << endl;
		cout << "================================" << endl;


		cout << "select option >>";
		cin >> option;

		switch (option) {

		case 1: AddRecord();
			SaveToFile();
			cout << "Record Added!" << endl;
			Backtomenu();
			system("CLS");
			break;
		case 2:
			cin.ignore();
			cout << "Enter Student ID to update: ";
			getline(cin, searchID);
			UpdateRecord(searchID);
			SaveToFile();
			Backtomenu();
			break;

		case 3:
			cin.ignore();
			cout << "Delete By ID" << endl;
			getline(cin, searchID);
			DeleteRecord(searchID);
			Backtomenu();
			cin.ignore();
			system("CLS");
			SaveToFile();
			break;

		case 4:
			cout << "Search By ID" << endl;
			cin.ignore();
			getline(cin, searchID);
			SearchRecord(searchID);
			Backtomenu();
			break;

		case 5: ListRecord();
			Backtomenu();
			break;


		}



	} while (option != 6);

	SaveToFile();
	cout << "Exit... Saving to file!" << endl;



}

// Student menu
void student_menu() {
	int option;
	string searchID;
	do {
		clearScreen();
		displayLogo();
		cout << "================================" << endl;
		cout << "student menu\n";
		cout << "================================" << endl;
		cout << "1-Search Student Records" << endl;
		cout << "2-Display all Student Records" << endl;
		cout << "3-Exit" << endl;
		cout << "================================" << endl;

		cout << "select option";
		cin >> option;

		switch (option) {

		case 1:
			cin.ignore();
			cout << "Search By ID" << endl;
			getline(cin, searchID);
			SearchRecord(searchID);
			Backtomenu();
			break;

		case 2: ListRecord();
			Backtomenu();
			break;

		default:
			cout << "Invalid option. Please try again." << endl;
		}
		break;

	} while (option != 3);

	cout << "Exit... Saving to file!" << endl;



	}


// Exit the program
void quit() {
	cout << "Exiting the program..." << endl;
	exit(0);
}


// Main function
int main() {
	char role;
	OpenFile();
	RegisterAccounts();
	do {
		clearScreen();
		displayLogo();
		role = checkRole();

		if (role == 'T') {
			teacherSelection();
		}
		else if (role == 'S') {
			studentSelection();
		}
	} while (role != 'E');

	quit();

	return 0;

}
