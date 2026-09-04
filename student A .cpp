#include <iostream>
#include <string>
#include <fstream>
#include <cctype>   
#include <cstdlib>  
#include <limits>
using namespace std;

const int maxrow = 10;
const int maxUsers = 10;


const int maxCourses = 10;
const int maxEnrollments = 50;


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
bool AddRecord();
bool UpdateRecord();
bool DeleteRecord();
bool SearchRecord();
bool ListRecord();
bool LoadCourses();
void SaveCourses();
void LoadEnrollments();
void SaveEnrollments();
bool listcourse();
bool RegisterCourse(string studentID);
void clearScreen() { system("CLS"); }

// Course records
string courseID[maxCourses];
string courseName[maxCourses];
int courseCount = 0;

// Enrollment records (which student registered for which course)
string enrollStudentID[maxEnrollments];
string enrollCourseID[maxEnrollments];
int enrollCount = 0;

string currentStudentID = "";

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
		studentrecord();
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

// ---------- ID validation ----------
string validateID(string prompt) {
	string id;
	bool valid;

	do {
		valid = true;
		cout << prompt;
		cin >> id;

		if (id.length() != 5) {
			cout << "[ERROR] ID must be exactly 5 digits.\n";
			valid = false;
		}
		else {
			for (char c : id) {
				if (!isdigit(c)) {
					cout << "[ERROR] ID must contain numbers only.\n";
					valid = false;
					break;
				}
			}
		}
	} while (!valid);

	return id;
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
bool AddRecord() {
	char name[50];
	char stuID[5];
	cin.ignore();

	cout << "Student ID.";
	cin.getline(stuID, 5);
	cout << "Student Name.";
	cin.getline(name, 50);

	for (int x = 0; x < maxrow; x++)
	{
		if (StuID[x] == "\0")
		{
			StuID[x] = stuID;
			StuName[x] = name;
			return true;
		}
	}

	cout << "[ERROR] Student record list is full!" << endl;
	return false;
}




// Display all student records
bool ListRecord()
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

	if (counter == 0) {
		cout << "No records found!" << endl;
		return false;
	}
	return true;
}


// Search for a student record by ID
bool SearchRecord(string search) {
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
	return counter > 0;
}


// Update a student record by ID
bool UpdateRecord(string search)
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
	return counter > 0;
}



// ---------- Course handling ----------


bool LoadCourses() {
	string line;
	ifstream myfile("courses.txt");
	if (myfile.is_open())
	{
		while (courseCount < maxCourses && getline(myfile, line))
		{
			auto commaPos = line.find(',');
			if (commaPos == string::npos) continue;
			courseID[courseCount] = line.substr(0, commaPos);
			courseName[courseCount] = line.substr(commaPos + 1);
			courseCount++;
		}
		myfile.close();
		return true;
	}
	else
	{
		// Seed with default courses on first run
		string defaultIDs[] = { "C001", "C002", "C003", "C004" };
		string defaultNames[] = { "Mathematics", "Computer Science", "English", "Physics" };
		for (int i = 0; i < 4 && courseCount < maxCourses; i++) {
			courseID[courseCount] = defaultIDs[i];
			courseName[courseCount] = defaultNames[i];
			courseCount++;
		}
		SaveCourses();
		return false;
	}
}


// Save course list to file
void SaveCourses() {
	ofstream myfile;
	myfile.open("courses.txt");
	if (!myfile.is_open())
	{
		cout << "Could not open file for saving courses!" << endl;
		return;
	}
	for (int x = 0; x < courseCount; x++)
	{
		myfile << courseID[x] + "," + courseName[x] << endl;
	}
}

// Load enrollment records from file
void LoadEnrollments() {
	string line;
	ifstream myfile("enrollments.txt");
	if (myfile.is_open())
	{
		while (enrollCount < maxEnrollments && getline(myfile, line))
		{
			auto commaPos = line.find(',');
			if (commaPos == string::npos) continue;
			enrollStudentID[enrollCount] = line.substr(0, commaPos);
			enrollCourseID[enrollCount] = line.substr(commaPos + 1);
			enrollCount++;
		}
		myfile.close();
	}
}

// Save enrollment records to file
void SaveEnrollments() {
	ofstream myfile;
	myfile.open("enrollments.txt");
	if (!myfile.is_open())
	{
		cout << "Could not open file for saving enrollments!" << endl;
		return;
	}
	for (int x = 0; x < enrollCount; x++)
	{
		myfile << enrollStudentID[x] + "," + enrollCourseID[x] << endl;
	}
}

// Display all available courses
bool listcourse() {
	system("CLS");
	cout << "Available Course(s)" << endl;
	cout << "================================" << endl;
	if (courseCount == 0) {
		cout << "No courses available." << endl;
		return false;
	}
	cout << " No. |   Course ID   |   Course Name" << endl << "--------------------------------" << endl;
	for (int x = 0; x < courseCount; x++)
	{
		cout << " " << (x + 1) << "    " << courseID[x] << "        " << courseName[x] << endl;
	}
	cout << "================================" << endl;
	return true;
}


// Let a student register for one of the listed courses
bool RegisterCourse(string studentID) {
	if (courseCount == 0) {
		cout << "No courses available to register for." << endl;
		return false;
	}

	if (enrollCount >= maxEnrollments) {
		cout << "[ERROR] Enrollment list is full!" << endl;
		return false;
	}

	cout << "Enter the Course ID you want to register for: ";
	string chosenCourseID;
	cin >> chosenCourseID;

	// Confirm the course ID exists
	bool found = false;
	for (int x = 0; x < courseCount; x++) {
		if (courseID[x] == chosenCourseID) {
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "[ERROR] Course ID not found." << endl;
		return false;
	}

	// Prevent double registration for the same course
	for (int x = 0; x < enrollCount; x++) {
		if (enrollStudentID[x] == studentID && enrollCourseID[x] == chosenCourseID) {
			cout << "You are already registered for this course." << endl;
			return false;
		}
	}

	enrollStudentID[enrollCount] = studentID;
	enrollCourseID[enrollCount] = chosenCourseID;
	enrollCount++;

	SaveEnrollments();
	cout << "[OK] Successfully registered for course " << chosenCourseID << "!" << endl;
	return true;
}

// Delete a student record by ID
bool DeleteRecord(string search)
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
		cout << "ID Number does not exist" << endl;
	}
	return counter > 0;
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
void studentrecord() {
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
		cout << "3 Display All Course " << endl;
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

		case 3:listcourse();
			char wantsToRegister;
			cout << "Do you want to register for a course? (Y/N): ";
			cin >> wantsToRegister;
			wantsToRegister = toupper(wantsToRegister);
			while (wantsToRegister != 'Y' && wantsToRegister != 'N')
			if (wantsToRegister == 'Y') RegisterCourse(currentStudentID);
			Backtomenu();
			break;
				
			
		default:
			cout << "Invalid option. Please try again." << endl;
		}
		break;

	} while (option != 3);

	cout << "Exit... Saving to file!" << endl;



	}


void teachermenu(){
int reply;




cout << "1. student record." << endl;
cout << " 2. course record." << endl;
cin >> reply;


if (reply == 1) {
	studentrecord();


}
else {
	
	
}



};



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
