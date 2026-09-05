#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <limits>
using namespace std;

// ============================================================
//                 STUDENT A - STUDENT MODULE
// ============================================================

const int maxrow = 10;
const int maxUsers = 10;
const int maxCourses = 50;
const int maxEnrollments = 50;

string StuName[maxrow] = {};
string StuID[maxrow] = {};

string teacherID[maxUsers];
string teacherPassword[maxUsers];
int teacherCount = 0;

string studentUserID[maxUsers];
string studentUserPassword[maxUsers];
int studentCount = 0;

// Course records
string courseID[maxCourses];
string courseName[maxCourses];
string courseCategory[maxCourses];
double courseFee[maxCourses];
int courseCount = 0;

// Enrollment records (which student registered for which course)
string enrollStudentID[maxEnrollments];
string enrollCourseID[maxEnrollments];
int enrollCount = 0;

string currentStudentID = "";

// ============================================================
//                 STUDENT C - BOOKING MODULE
// ============================================================

const int MAX_BOOKINGS = 100;
int bookingCount = 0;
string bookingID[MAX_BOOKINGS];
string bookingStudentID[MAX_BOOKINGS];
string bookingCourseID[MAX_BOOKINGS];
string bookingDate[MAX_BOOKINGS];
string bookingStatus[MAX_BOOKINGS];

// ============================================================
//                 FUNCTION PROTOTYPES
// ============================================================

void displayLogo();
bool teacherRegister();
bool teacherLogin();
void teacher_menu();
bool studentRegister();
bool studentLogin();
void studentrecord();
void student_menu();
void OpenFile();
void SaveToFile();
void SaveAccounts();
void LoadAccounts();
bool AddRecord();
bool UpdateRecord(string search);
bool DeleteRecord(string search);
bool ListRecord();
bool SearchRecord(string search);
bool LoadCourses();
void SaveCourses();
void LoadEnrollments();
void SaveEnrollments();
bool listcourse();
bool RegisterCourse(string studentID);

string validateString(string message);
int checkNumSelection(int num, int maxSelection);
char checkRole();
char checkAction();
void teacherSelection();
void studentSelection();
string validateID(string prompt);
void Backtomenu();
void clearScreen();

void OpenCourseFile();
void SaveCourseFile();
bool AddCourse();
bool ModifyCourse(string searchID);
bool DeleteCourse(string searchID);
bool SearchCourse(string searchID);
bool DisplayCourses(string filterCategory = "ALL");
void teacher_course_menu();
void student_course_menu();

bool createBooking(); // need a course menu, student register functon
bool modifyBooking(); // for modify
bool modifyBookingCourseId(int bookingIndex);
bool modifyBookingDate(int bookingIndex);
bool cancelBooking();

bool studentIdExists(string studentId); // for checking student ID validation
bool courseIdExists(string courseId); // for checking the course ID validation
bool isValidBookingDate(string bookingDate); // check for the validation of date
int findBookingIndex(string bookingId); // find where the user id is
bool searchBooking();
bool displayBookingSumm(); //display bookings made
int displayBookStatus(); //display cancelled or active bookings
int menuCdisplay(); //moduleC Menu

void ReportingMenu();
void generateSummaryReport();
void generateDetailedReport();
void calculateStatistics();
void sortRecords();
void displayAnalysis();

// ============================================================
//                 GENERAL FUNCTIONS
// ============================================================

void clearScreen()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void Backtomenu()
{
    cout << "\nPress Enter to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Check if input is not empty
string validateString(string message)
{
    string input;
    do {
        cout << message;
        getline(cin, input);
        if (input.empty())
            cout << "[ERROR] Input cannot be empty. Please enter again.\n";
    } while (input.empty());
    return input;
}

int checkNumSelection(int num, int maxSelection)
{
    while (num <= 0 || num > maxSelection) {
        cout << "[ERROR] Invalid input! Please enter 1-" << maxSelection << " only: ";
        cin >> num;
    }
    return num;
}

char checkRole()
{
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
char checkAction()
{
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

// logo
void displayLogo()
{
    cout << "========================================\n";
    cout << "       TUITION CENTRE SYSTEM\n";
    cout << "========================================\n";
}

// ---------- ID validation ----------
string validateID(string prompt)
{
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
                if (!isdigit(static_cast<unsigned char>(c))) {
                    cout << "[ERROR] ID must contain numbers only.\n";
                    valid = false;
                    break;
                }
            }
        }
    } while (!valid);

    return id;
}

// ============================================================
//                 STUDENT A - ACCOUNT FUNCTIONS
// ============================================================

// teacher register function
bool teacherRegister()
{
    if (teacherCount >= maxUsers) {
        cout << "[ERROR] Teacher account list is full!\n";
        return false;
    }

    string id, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
bool teacherLogin()
{
    string id, password;

    clearScreen();
    displayLogo();
    cout << "=========================================\n";
    cout << "Teacher Login Screen\n";
    cout << "=========================================\n";
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Password: ";
    getline(cin, password);

    for (int i = 0; i < teacherCount; i++) {
        if (id == teacherID[i] && password == teacherPassword[i]) {
            cout << "[OK] Login Successful.\n";
            return true;
        }
    }

    cout << "[ERROR] Wrong ID or Password.\n";
    return false;
}

// ---------- student register / login ----------
bool studentRegister()
{
    if (studentCount >= maxUsers) {
        cout << "[ERROR] Student account list is full!\n";
        return false;
    }

    string id, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
bool studentLogin()
{
    string id, password;

    clearScreen();
    displayLogo();
    cout << "=========================================\n";
    cout << "Student Login Screen\n";
    cout << "=========================================\n";
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Password: ";
    getline(cin, password);

    for (int i = 0; i < studentCount; i++) {
        if (id == studentUserID[i] && password == studentUserPassword[i]) {
            currentStudentID = id;
            cout << "[OK] Login Successful.\n";
            return true;
        }
    }

    cout << "[ERROR] Wrong ID or Password.\n";
    return false;
}

// ============================================================
//                 STUDENT A - STUDENT RECORD
// ============================================================

void OpenFile()
{
    string line;
    ifstream myfile("student.txt");

    if (myfile.is_open()) {
        int x = 0;
        while (x < maxrow && getline(myfile, line)) {
            auto commaPos = line.find(',');
            if (commaPos == string::npos) continue;
            StuID[x] = line.substr(0, commaPos);
            StuName[x] = line.substr(commaPos + 1);
            x++;
        }
        myfile.close();
    }
}

// Add a new student record
bool AddRecord()
{
    char name[50];
    char stuID[6];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Student ID: ";
    cin.getline(stuID, 6);

    // FIX: reject duplicate Student IDs before asking for the name
    for (int x = 0; x < maxrow; x++) {
        if (!StuID[x].empty() && StuID[x] == string(stuID)) {
            cout << "[ERROR] This Student ID is already registered!\n";
            return false;
        }
    }

    cout << "Student Name: ";
    cin.getline(name, 50);

    for (int x = 0; x < maxrow; x++) {
        if (StuID[x].empty()) {
            StuID[x] = stuID;
            StuName[x] = name;
            cout << "Student record added successfully!\n";
            return true;
        }
    }

    cout << "[ERROR] Student record list is full!" << endl;
    return false;
}

// Display all student records
bool ListRecord()
{
    clearScreen();
    cout << "Current record(s)" << endl;
    cout << "================================" << endl;

    int counter = 0;
    cout << " No. |        student ID |        student Name" << endl;
    cout << "--------------------------------" << endl;

    for (int x = 0; x < maxrow; x++) {
        if (!StuID[x].empty()) {
            counter++;
            cout << " " << counter << "   " << StuID[x]
                << "             " << StuName[x] << endl;
        }
    }

    if (counter == 0) {
        cout << "No records found!" << endl;
        return false;
    }
    return true;
}

// Search for a student record by ID
bool SearchRecord(string search)
{
    clearScreen();
    cout << "Current Record(s)" << endl;
    cout << "================================" << endl;

    int counter = 0;
    cout << " No. |        student ID |        student Name" << endl;
    cout << "--------------------------------" << endl;

    for (int x = 0; x < maxrow; x++) {
        if (!StuID[x].empty() && StuID[x] == search) {
            counter++;
            cout << " " << counter << "   " << StuID[x]
                << "             " << StuName[x] << endl;
            break;
        }
    }

    if (counter == 0)
        cout << "No records found!" << endl;

    cout << "================================" << endl;
    return counter > 0;
}

// Update a student record by ID
bool UpdateRecord(string search)
{
    char name[50];
    int counter = 0;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int x = 0; x < maxrow; x++) {
        if (StuID[x] == search) {
            counter++;
            cout << "Student Name: ";
            cin.getline(name, 50);
            StuName[x] = name;
            cout << "Update Successful!" << endl;
            break;
        }
    }

    if (counter == 0)
        cout << "No Student ID Found !" << endl;

    return counter > 0;
}

bool DeleteRecord(string search)
{
    for (int x = 0; x < maxrow; x++) {
        if (StuID[x] == search) {
            StuID[x].clear();
            StuName[x].clear();
            cout << "Delete Successful!" << endl;
            return true;
        }
    }

    cout << "No Student ID Found !" << endl;
    return false;
}

void SaveToFile()
{
    ofstream myfile("student.txt");

    if (!myfile.is_open()) {
        cout << "Unable to open the file!" << endl;
        return;
    }

    for (int x = 0; x < maxrow; x++) {
        if (!StuID[x].empty())
            myfile << StuID[x] << "," << StuName[x] << endl;
    }
    myfile.close();
}

void SaveAccounts()
{
    ofstream teacherFile("teacher_accounts.txt");
    for (int i = 0; i < teacherCount; i++)
        teacherFile << teacherID[i] << "," << teacherPassword[i] << endl;
    teacherFile.close();

    ofstream studentFile("student_accounts.txt");
    for (int i = 0; i < studentCount; i++)
        studentFile << studentUserID[i] << "," << studentUserPassword[i] << endl;
    studentFile.close();
}

void LoadAccounts()
{
    string line;

    ifstream teacherFile("teacher_accounts.txt");
    teacherCount = 0;
    if (teacherFile.is_open()) {
        while (teacherCount < maxUsers && getline(teacherFile, line)) {
            auto commaPos = line.find(',');
            if (commaPos == string::npos) continue;
            teacherID[teacherCount] = line.substr(0, commaPos);
            teacherPassword[teacherCount] = line.substr(commaPos + 1);
            teacherCount++;
        }
        teacherFile.close();
    }

    ifstream studentFile("student_accounts.txt");
    studentCount = 0;
    if (studentFile.is_open()) {
        while (studentCount < maxUsers && getline(studentFile, line)) {
            auto commaPos = line.find(',');
            if (commaPos == string::npos) continue;
            studentUserID[studentCount] = line.substr(0, commaPos);
            studentUserPassword[studentCount] = line.substr(commaPos + 1);
            studentCount++;
        }
        studentFile.close();
    }
}
void studentrecord()
{
    int choice;
    do {
        clearScreen();
        displayLogo();
        cout << "----------- STUDENT RECORD MENU -----------\n";
        cout << "1. Add Student Record\n";
        cout << "2. Update Student Record\n";
        cout << "3. Delete Student Record\n";
        cout << "4. List Student Records\n";
        cout << "5. Search Student Record\n";
        cout << "6. Course Management\n";
        cout << "7. Booking Management\n";
        cout << "8. Reporting Module\n";
        cout << "9. Back to Main Menu\n";
        cout << "--------------------------------------------\n";
        cout << "Select Option (1-9): ";

        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cout << "[ERROR] Invalid option! Enter 1-9 only: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        string search;
        switch (choice) {
        case 1:
            AddRecord();
            SaveToFile();
            Backtomenu();
            break;
        case 2:
            cin.ignore();
            cout << "Enter Student ID to update: ";
            getline(cin, search);
            UpdateRecord(search);
            SaveToFile();
            Backtomenu();
            break;
        case 3:
            cin.ignore();
            cout << "Enter Student ID to delete: ";
            getline(cin, search);
            DeleteRecord(search);
            SaveToFile();
            Backtomenu();
            break;
        case 4:
            ListRecord();
            Backtomenu();
            break;
        case 5:
            cin.ignore();
            cout << "Enter Student ID to search: ";
            getline(cin, search);
            SearchRecord(search);
            Backtomenu();
            break;
        case 6:
            teacher_course_menu();
            break;
        case 7:
            menuCdisplay();
            break;
        case 8:
            ReportingMenu();
            break;
        case 9:
            cout << "Returning to Main Menu...\n";
            break;
        }
    } while (choice != 9);
}

void student_menu()
{
    int choice;

    do {
        clearScreen();
        displayLogo();
        cout << "----------- STUDENT MENU -----------\n";
        cout << "1. Display My Student Record\n";
        cout << "2. Course Management\n";
        cout << "3. Booking Management\n";
        cout << "4. Reporting Module\n";
        cout << "5. Exit Student Menu\n";
        cout << "------------------------------------\n";
        cout << "Select Option (1-5): ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "[ERROR] Invalid option! Enter 1-5 only: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice) {
        case 1:
            SearchRecord(currentStudentID);
            Backtomenu();
            break;
        case 2:
            student_course_menu();
            break;
        case 3:
            menuCdisplay();
            break;
        case 4:
            ReportingMenu();
            break;
        case 5:
            break;
        }
    } while (choice != 5);
}

void teacher_menu()
{
    studentrecord();
}

void teacherSelection()
{
    char action = checkAction();
    bool loginStatus = false;

    if (action == 'R') {
        if (teacherRegister()) {
            cout << "Please login with your new account.\n";
            loginStatus = teacherLogin();
        }
    }
    else {
        loginStatus = teacherLogin();
    }

    if (loginStatus)
        teacher_menu();
}

void studentSelection()
{
    char action = checkAction();
    bool loginStatus = false;

    if (action == 'R') {
        if (studentRegister()) {
            cout << "Please login with your new account.\n";
            loginStatus = studentLogin();
        }
    }
    else {
        loginStatus = studentLogin();
    }

    if (loginStatus)
        student_menu();
}

// ============================================================
//                 STUDENT B - COURSE MANAGEMENT
// ============================================================

bool LoadCourses()
{
    string line;
    ifstream myfile("courses.txt");
    courseCount = 0;

    if (myfile.is_open()) {
        while (courseCount < maxCourses && getline(myfile, line)) {
            if (line.empty()) continue;

            size_t c1 = line.find(',');
            size_t c2 = line.find(',', c1 + 1);
            size_t c3 = line.find(',', c2 + 1);

            if (c1 != string::npos && c2 != string::npos && c3 != string::npos) {
                courseID[courseCount] = line.substr(0, c1);
                courseName[courseCount] = line.substr(c1 + 1, c2 - c1 - 1);
                courseCategory[courseCount] = line.substr(c2 + 1, c3 - c2 - 1);
                courseFee[courseCount] = stod(line.substr(c3 + 1));
                courseCount++;
            }
        }
        myfile.close();
        return true;
    }

    // Seed with default courses on first run
    string defaultIDs[] = {
        "P101","P102","P103","P104","P105",
        "S201","S202","S203","S204","S205",
        "S206","S207","S208","S209","S210"
    };
    string defaultNames[] = {
        "Science","Maths","Chinese","Malay","English",
        "Add Maths","Physics","Account","Ekonomi","Geografi",
        "Sejarah","Science","Maths","English","Malay"
    };
    string defaultCategories[] = {
        "Primary","Primary","Primary","Primary","Primary",
        "Secondary","Secondary","Secondary","Secondary","Secondary",
        "Secondary","Secondary","Secondary","Secondary","Secondary"
    };
    double defaultFees[] = {
        90,90,85,85,85,
        130,150,150,150,130,
        130,130,130,130,130
    };

    for (int i = 0; i < 15 && courseCount < maxCourses; i++) {
        courseID[courseCount] = defaultIDs[i];
        courseName[courseCount] = defaultNames[i];
        courseCategory[courseCount] = defaultCategories[i];
        courseFee[courseCount] = defaultFees[i];
        courseCount++;
    }

    SaveCourses();
    return false;
}

void SaveCourses()
{
    ofstream myfile("courses.txt");
    if (!myfile.is_open()) {
        cout << "Could not open file for saving courses!" << endl;
        return;
    }

    for (int x = 0; x < courseCount; x++) {
        myfile << courseID[x] << ","
            << courseName[x] << ","
            << courseCategory[x] << ","
            << fixed << setprecision(2)
            << courseFee[x] << endl;
    }
    myfile.close();
}

// Save course list to file
void SaveCourseFile()
{
    SaveCourses();
}

void OpenCourseFile()
{
    LoadCourses();
}

bool AddCourse()
{
    if (courseCount >= maxCourses) {
        cout << "[ERROR] Storage full! Cannot add more courses.\n";
        return false;
    }

    string id, name;
    int catChoice;
    double fee;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n--- Add New Course ---\n";
    cout << "Enter Course ID (e.g., P103 / S203): ";
    getline(cin, id);

    for (int i = 0; i < courseCount; i++) {
        if (courseID[i] == id) {
            cout << "[ERROR] Duplicate Course ID! Registration failed.\n";
            return false;
        }
    }

    cout << "Enter Course Name (e.g., English): ";
    getline(cin, name);

    cout << "Select Level:\n";
    cout << "  1. Primary\n";
    cout << "  2. Secondary\n";
    cout << "Select choice (1 or 2): ";

    while (!(cin >> catChoice) || (catChoice != 1 && catChoice != 2)) {
        cout << "[ERROR] Invalid choice! Enter 1 for Primary or 2 for Secondary: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    string cat = (catChoice == 1) ? "Primary" : "Secondary";

    cout << "Enter Course Fee (RM): ";
    while (!(cin >> fee) || fee < 0) {
        cout << "[ERROR] Invalid input! Enter a positive fee: RM ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    courseID[courseCount] = id;
    courseName[courseCount] = name;
    courseCategory[courseCount] = cat;
    courseFee[courseCount] = fee;
    courseCount++;

    SaveCourseFile();
    cout << "[SUCCESS] Course added successfully under [" << cat << "] category!\n";
    return true;
}

bool ModifyCourse(string searchID)
{
    int index = -1;
    for (int i = 0; i < courseCount; i++) {
        if (courseID[i] == searchID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "[ERROR] Course ID '" << searchID << "' not found!\n";
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n--- Modifying Course [" << courseID[index] << "] ---\n";
    cout << "Current Name: " << courseName[index] << endl;
    cout << "Enter New Course Name: ";
    getline(cin, courseName[index]);

    int catChoice;
    cout << "Current Level: " << courseCategory[index] << endl;
    cout << "Select New Level (1. Primary, 2. Secondary): ";

    while (!(cin >> catChoice) || (catChoice != 1 && catChoice != 2)) {
        cout << "[ERROR] Invalid choice! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    courseCategory[index] = (catChoice == 1) ? "Primary" : "Secondary";

    cout << "Current Fee: RM " << fixed << setprecision(2) << courseFee[index] << endl;
    cout << "Enter New Course Fee (RM): ";

    while (!(cin >> courseFee[index]) || courseFee[index] < 0) {
        cout << "[ERROR] Invalid fee! Enter a positive number: RM ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    SaveCourseFile();
    cout << "[SUCCESS] Course updated successfully!\n";
    return true;
}

bool DeleteCourse(string searchID)
{
    int index = -1;
    for (int i = 0; i < courseCount; i++) {
        if (courseID[i] == searchID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "[ERROR] Course ID '" << searchID << "' not found!\n";
        return false;
    }

    for (int i = index; i < courseCount - 1; i++) {
        courseID[i] = courseID[i + 1];
        courseName[i] = courseName[i + 1];
        courseCategory[i] = courseCategory[i + 1];
        courseFee[i] = courseFee[i + 1];
    }

    courseCount--;
    SaveCourseFile();
    cout << "[SUCCESS] Course deleted successfully!\n";
    return true;
}

bool SearchCourse(string searchID)
{
    clearScreen();
    cout << "========================================================\n";
    cout << "                    SEARCH RESULT                       \n";
    cout << "========================================================\n";

    bool found = false;

    for (int i = 0; i < courseCount; i++) {
        if (courseID[i] == searchID) {
            cout << " Course ID       : " << courseID[i] << endl;
            cout << " Course Name     : " << courseName[i] << endl;
            cout << " Level Category  : " << courseCategory[i] << endl;
            cout << " Course Fee      : RM " << fixed << setprecision(2) << courseFee[i] << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << " [ERROR] No course record found matching ID '" << searchID << "'.\n";

    cout << "========================================================\n";
    return found;
}

bool DisplayCourses(string filterCategory)
{
    clearScreen();
    cout << "========================================================================\n";

    if (filterCategory == "Primary")
        cout << "                   PRIMARY SCHOOL COURSES\n";
    else if (filterCategory == "Secondary")
        cout << "                  SECONDARY SCHOOL COURSES\n";
    else
        cout << "                      ALL TUITION COURSES\n";

    cout << "========================================================================\n";
    cout << " No. | Course ID | Course Name         | Category   | Fee (RM)\n";
    cout << "------------------------------------------------------------------------\n";

    int displayedCount = 0;

    for (int i = 0; i < courseCount; i++) {
        if (filterCategory == "ALL" || courseCategory[i] == filterCategory) {
            displayedCount++;
            cout << " " << setw(2) << displayedCount << "  | "
                << setw(9) << left << courseID[i] << " | "
                << setw(19) << left << courseName[i] << " | "
                << setw(10) << left << courseCategory[i] << " | RM "
                << setw(7) << right << fixed << setprecision(2)
                << courseFee[i] << endl;
        }
    }

    if (displayedCount == 0)
        cout << " No courses found under this section.\n";

    cout << "========================================================================\n";
    return displayedCount > 0;
}

bool listcourse()
{
    return DisplayCourses("ALL");
}

bool RegisterCourse(string studentID)
{
    if (enrollCount >= maxEnrollments) {
        cout << "[ERROR] Enrollment record is full!\n";
        return false;
    }

    string selectedCourse;
    cout << "Enter Course ID to register: ";
    cin >> selectedCourse;

    bool found = false;
    for (int i = 0; i < courseCount; i++) {
        if (courseID[i] == selectedCourse) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "[ERROR] Course ID does not exist.\n";
        return false;
    }

    for (int i = 0; i < enrollCount; i++) {
        if (enrollStudentID[i] == studentID &&
            enrollCourseID[i] == selectedCourse) {
            cout << "[ERROR] Student already registered for this course.\n";
            return false;
        }
    }

    enrollStudentID[enrollCount] = studentID;
    enrollCourseID[enrollCount] = selectedCourse;
    enrollCount++;

    SaveEnrollments();
    cout << "[SUCCESS] Course registered successfully!\n";
    return true;
}

void LoadEnrollments()
{
    string line;
    ifstream myfile("enrollments.txt");

    if (myfile.is_open()) {
        while (enrollCount < maxEnrollments && getline(myfile, line)) {
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
void SaveEnrollments()
{
    ofstream myfile("enrollments.txt");

    if (!myfile.is_open()) {
        cout << "Could not open file for saving enrollments!" << endl;
        return;
    }

    for (int i = 0; i < enrollCount; i++)
        myfile << enrollStudentID[i] << "," << enrollCourseID[i] << endl;

    myfile.close();
}

void teacher_course_menu()
{
    int option;
    string searchID;

    do {
        clearScreen();
        displayLogo();
        cout << "----------- TEACHER COURSE MENU -----------\n";
        cout << "1. Register (Add) New Course\n";
        cout << "2. Modify Course Record\n";
        cout << "3. Delete Course Record\n";
        cout << "4. Search Course by ID\n";
        cout << "5. Display All Courses\n";
        cout << "6. Display Primary Courses Only\n";
        cout << "7. Display Secondary Courses Only\n";
        cout << "8. Back to Role Selection\n";
        cout << "-------------------------------------------\n";
        cout << "Select Option (1-8): ";

        while (!(cin >> option) || option < 1 || option > 8) {
            cout << "[ERROR] Invalid option! Enter 1-8 only: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (option) {
        case 1:
            AddCourse();
            Backtomenu();
            break;
        case 2:
            cin.ignore();
            cout << "Enter Course ID to modify: ";
            getline(cin, searchID);
            ModifyCourse(searchID);
            Backtomenu();
            break;
        case 3:
            cin.ignore();
            cout << "Enter Course ID to delete: ";
            getline(cin, searchID);
            DeleteCourse(searchID);
            Backtomenu();
            break;
        case 4:
            cin.ignore();
            cout << "Enter Course ID to search: ";
            getline(cin, searchID);
            SearchCourse(searchID);
            Backtomenu();
            break;
        case 5:
            DisplayCourses("ALL");
            Backtomenu();
            break;
        case 6:
            DisplayCourses("Primary");
            Backtomenu();
            break;
        case 7:
            DisplayCourses("Secondary");
            Backtomenu();
            break;
        case 8:
            cout << "Returning to previous menu...\n";
            break;
        }
    } while (option != 8);
}

void student_course_menu()
{
    int option;
    string searchID;

    do {
        clearScreen();
        displayLogo();
        cout << "----------- STUDENT COURSE MENU -----------\n";
        cout << "1. Search Course by ID\n";
        cout << "2. Display All Courses\n";
        cout << "3. Display Primary Courses Only\n";
        cout << "4. Display Secondary Courses Only\n";
        cout << "5. Register Course\n";
        cout << "6. Back to Role Selection\n";
        cout << "-------------------------------------------\n";
        cout << "Select Option (1-6): ";

        while (!(cin >> option) || option < 1 || option > 6) {
            cout << "[ERROR] Invalid option! Enter 1-6 only: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (option) {
        case 1:
            cin.ignore();
            cout << "Enter Course ID to search: ";
            getline(cin, searchID);
            SearchCourse(searchID);
            Backtomenu();
            break;
        case 2:
            DisplayCourses("ALL");
            Backtomenu();
            break;
        case 3:
            DisplayCourses("Primary");
            Backtomenu();
            break;
        case 4:
            DisplayCourses("Secondary");
            Backtomenu();
            break;
        case 5:
            RegisterCourse(currentStudentID);
            Backtomenu();
            break;
        case 6:
            cout << "Returning to previous menu...\n";
            break;
        }
    } while (option != 6);
}

// ============================================================
//                 STUDENT C - BOOKING MODULE
// ============================================================

//moduleC Menu
int menuCdisplay()
{
    int choice;

    do {
        clearScreen();
        cout << "\n===============<<||>>=================\n";
        cout << "       BOOKING MANAGEMENT SYSTEM\n";
        cout << "===============<<===>>=================\n";
        cout << " 1. Create Booking\n";
        cout << " 2. Modify Booking\n";
        cout << " 3. Cancel Booking\n";
        cout << " 4. Search Booking\n";
        cout << " 5. Display Booking Summary\n";
        cout << " 6. Display by Status\n";
        cout << " 7. Exit\n";
        cout << "\n<><><>><><><><><><><><><><><><><><><><\n";
        cout << "Enter Your Choice...: ";

        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid Choice. Please Try Again...\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter Your Choice...: ";
        }

        switch (choice) {
        case 1: createBooking(); break;
        case 2: modifyBooking(); break;
        case 3: cancelBooking(); break;
        case 4: searchBooking(); break;
        case 5: displayBookingSumm(); break;
        case 6: displayBookStatus(); break;
        case 7:
            cout << "Returning to previous menu...\n";
            break;
        }
    } while (choice != 7);

    return choice;
}

//search booking
bool searchBooking()
{
    int searchChoice;
    string searchTerm;
    bool found = false;

    clearScreen();
    cout << "\n==============<<||>>==============\n";
    cout << "          SEARCH BOOKING \n";
    cout << "==============<<===>>==============\n";
    cout << " 1. Search by Booking Id\n";
    cout << " 2. Search by Student Id\n";
    cout << " 3. Search by Course Id\n";
    cout << " 4. Search by Date\n";
    cout << " 5. Search by Status\n";
    cout << " 6. Back to Menu\n";
    cout << "<><><><><><><><>>><><><><><><><><><\n";
    cout << "Enter Your Choice...:";
    cin >> searchChoice;

    if (searchChoice == 6) return false;

    if (searchChoice < 1 || searchChoice > 6) {
        cout << "Invalid choice. Please Try Again...\n";
        return false;
    }

    cout << "Enter Search Term...:";
    cin >> searchTerm;

    cout << "\n=============>>||<<==============\n";
    cout << "               RESULTS \n";
    cout << "==============>>===<<===============\n";
    cout << left << setw(12) << "Booking ID"
        << setw(12) << "Student ID"
        << setw(12) << "Course ID"
        << setw(12) << "Date"
        << setw(12) << "Status" << endl;

    for (int i = 0; i < bookingCount; i++) {
        bool match = false;

        switch (searchChoice) {
        case 1: //BookingID
            if (bookingID[i] == searchTerm) match = true;
            break;
        case 2: //StudentID
            if (bookingStudentID[i] == searchTerm) match = true;
            break;
        case 3: //CourseID
            if (bookingCourseID[i] == searchTerm) match = true;
            break;
        case 4: //Date
            if (bookingDate[i] == searchTerm) match = true;
            break;
        case 5: //status
        {
            string status = bookingStatus[i];
            for (char& c : status) c = toupper(c);
            string searchUpper = searchTerm;
            for (char& c : searchUpper) c = toupper(c);
            if (status == searchUpper) match = true;
        }
        break;
        }

        if (match) {
            found = true;
            cout << left << setw(12) << bookingID[i]
                << setw(12) << bookingStudentID[i]
                << setw(12) << bookingCourseID[i]
                << setw(12) << bookingDate[i]
                << setw(12) << bookingStatus[i] << endl;
        }
    }

    if (!found)
        cout << " No Bookings Found That Matches Your Search.\n";

    Backtomenu();
    return found;
}

//DISPLAY booking summary
bool displayBookingSumm()
{
    clearScreen();

    cout << "\n================<<||>>==================\n";
    cout << "             Booking Summary\n";
    cout << "================<<===>>================\n";

    if (bookingCount == 0) {
        cout << "No Bookings Found...\n";
        Backtomenu();
        return false;
    }

    cout << left << setw(5) << "No."
        << setw(12) << "Booking ID"
        << setw(12) << "Student ID"
        << setw(12) << "Course ID"
        << setw(12) << "Date"
        << setw(12) << "Status" << endl;

    for (int i = 0; i < bookingCount; i++) {
        cout << left << setw(5) << (i + 1)
            << setw(12) << bookingID[i]
            << setw(12) << bookingStudentID[i]
            << setw(12) << bookingCourseID[i]
            << setw(12) << bookingDate[i]
            << setw(12) << bookingStatus[i] << endl;
    }

    cout << "__________________________________________\n";
    cout << "Total Bookings: " << bookingCount << endl;
    Backtomenu();
    return true;
}

// DISPLAY booking status
int displayBookStatus()
{
    int statChoice;
    string statusFilter;

    clearScreen();
    cout << "\n==============<<||>>==============\n";
    cout << "       Display Booking Status\n";
    cout << "==================================\n";
    cout << " 1. Active Bookings\n";
    cout << " 2. Cencelled Bookings\n";
    cout << " 3. Return\n";
    cout << "Enter Your Choice...";
    cin >> statChoice;

    if (statChoice == 3) return 3;

    if (statChoice == 1)
        statusFilter = "Active";
    else if (statChoice == 2)
        statusFilter = "Cancelled";
    else {
        cout << "Invalid choice!!!\n";
        return 0;
    }

    clearScreen();
    cout << "\n============================================================\n";
    cout << "  " << statusFilter << " Bookings\n";
    cout << "--------------------------------------------------------------\n";

    bool found = false;
    int counter = 1;

    for (int i = 0; i < bookingCount; i++) {
        if (bookingStatus[i] == statusFilter) {
            found = true;
            cout << left << setw(5) << counter
                << setw(12) << bookingID[i]
                << setw(12) << bookingStudentID[i]
                << setw(12) << bookingCourseID[i]
                << setw(12) << bookingDate[i]
                << setw(12) << bookingStatus[i] << endl;
            counter++;
        }
    }

    if (!found)
        cout << "No " << statusFilter << " bookings found...\n";

    cout << "=========================================\n";
    cout << "Total " << statusFilter << " Bookings : " << (counter - 1) << endl;
    Backtomenu();
    return counter - 1;
}

// register course function
bool createBooking()
{
    // avoid exceed the maximun of table
    if (bookingCount >= MAX_BOOKINGS) {
        cout << "Booking record is full. Unable to create a new booking." << endl;

        // if this statament execute, then return user to where he is
        return false;
    }

    bookingID[bookingCount] = "B" + to_string(bookingCount + 1);
    cout << "Generated Booking ID\t\t: " << bookingID[bookingCount] << endl;

    // check for student validation
    bool validStudentId;
    do {
        cout << "Enter Student ID\t\t: ";
        cin >> bookingStudentID[bookingCount];

        validStudentId = studentIdExists(bookingStudentID[bookingCount]);

        if (!validStudentId) {
            cout << "Student ID does not exist. Please enter a valid Student ID." << endl << endl;
        }
    } while (!validStudentId);

    // check for the validation of the course ID
    bool validCourseId;
    do {
        cout << "Enter Course ID\t\t\t: ";
        cin >> bookingCourseID[bookingCount];

        validCourseId = courseIdExists(bookingCourseID[bookingCount]);

        if (!validCourseId) {
            cout << "Course ID does not exist. Please enter a valid Course ID." << endl << endl;
        }
    } while (!validCourseId);

    // check for the vaidation of date format
    bool validBookingDate;
    do {
        cout << "Enter Booking Date (DD/MM/YYYY) : ";
        cin >> bookingDate[bookingCount];

        validBookingDate = isValidBookingDate(bookingDate[bookingCount]);

        if (!validBookingDate) {
            cout << "Invalid date format. Please use DD/MM/YYYY." << endl << endl;
        }
    } while (!validBookingDate);

    bookingStatus[bookingCount] = "Active";

    clearScreen();
    cout << "Booking Created Successfully!" << endl;
    cout << "Booking ID\t\t: " << bookingID[bookingCount] << endl;
    cout << "Student ID\t\t: " << bookingStudentID[bookingCount] << endl;
    cout << "Course ID\t\t: " << bookingCourseID[bookingCount] << endl;
    cout << "Date\t\t\t: " << bookingDate[bookingCount] << endl;
    cout << "Status\t\t\t: " << bookingStatus[bookingCount] << endl << endl;

    bookingCount++;
    return true; // create sucessfully
}

// need to change the condition name to match the table of module A
bool studentIdExists(string studentId)
{
    for (int studentIndex = 0; studentIndex < maxrow; studentIndex++) {
        if (StuID[studentIndex] == studentId)
            return true;
    }
    return false;
}

// need to change the condition name to match
bool courseIdExists(string courseIdInput)
{
    for (int courseIndex = 0; courseIndex < courseCount; courseIndex++) {
        if (courseID[courseIndex] == courseIdInput)
            return true;
    }
    return false;
}

// check for the validation of date
bool isValidBookingDate(string bookingDateInput)
{
    if (bookingDateInput.length() != 10)
        return false;

    if (bookingDateInput[2] != '/' || bookingDateInput[5] != '/')
        return false;

    for (int characterIndex = 0;
        characterIndex < static_cast<int>(bookingDateInput.length());
        characterIndex++) {
        if (characterIndex != 2 &&
            characterIndex != 5 &&
            !isdigit(static_cast<unsigned char>(bookingDateInput[characterIndex])))
            return false;
    }

    int bookingDay = stoi(bookingDateInput.substr(0, 2));
    int bookingMonth = stoi(bookingDateInput.substr(3, 2));

    if (bookingDay < 1 || bookingDay > 31 ||
        bookingMonth < 1 || bookingMonth > 12)
        return false;

    return true;
}

// =======================================
//  for modify and cancel part
//=====================================
int findBookingIndex(string bookingId)
{
    // find every single record from index 1 till found it
    for (int recordIndex = 0; recordIndex < bookingCount; recordIndex++) {
        // check if the record we found match the user ID
        if (bookingId == bookingID[recordIndex])
            return recordIndex;
    }

    // if cant find it then return -1, cuz array dont have -1 position
    return -1;
}

bool modifyBooking()
{
    string bookingId; // user ID
    int bookingIndex;

    cout << "Enter Booking ID to modify: ";
    cin >> bookingId;

    bookingIndex = findBookingIndex(bookingId);

    if (bookingIndex == -1) {
        cout << "Booking ID does not exist." << endl;
        return false;
    }

    if (bookingStatus[bookingIndex] == "Cancelled") {
        cout << "Cancelled booking cannot be modified." << endl;
        return false;
    }

    cout << "\nCurrent Booking Details" << endl;
    cout << "Booking ID\t: " << bookingID[bookingIndex] << endl;
    cout << "Student ID\t: " << bookingStudentID[bookingIndex] << endl;
    cout << "Course ID\t: " << bookingCourseID[bookingIndex] << endl;
    cout << "Booking Date\t: " << bookingDate[bookingIndex] << endl;
    cout << "Booking Status\t: " << bookingStatus[bookingIndex] << endl;

    int modificationSelection;
    do {
        cout << "\nWhat would you like to modify?" << endl;
        cout << "1. Course ID" << endl;
        cout << "2. Booking Date" << endl;
        cout << "3. Back" << endl;
        cout << "Enter your selection: ";
        cin >> modificationSelection;

        if (modificationSelection < 1 || modificationSelection > 3)
            cout << "Invalid selection. Please enter 1, 2, or 3." << endl;

    } while (modificationSelection < 1 || modificationSelection > 3);

    if (modificationSelection == 1)
        return modifyBookingCourseId(bookingIndex);
    else if (modificationSelection == 2)
        return modifyBookingDate(bookingIndex);
    else {
        cout << "No changes were made." << endl;
        return false;
    }
}

bool modifyBookingCourseId(int bookingIndex)
{
    bool validCourseId;

    do {
        cout << endl;
        cout << "Enter new Course ID: ";
        cin >> bookingCourseID[bookingIndex];

        validCourseId = courseIdExists(bookingCourseID[bookingIndex]);

        if (!validCourseId)
            cout << "Course ID does not exist. Please enter a valid Course ID." << endl;

    } while (!validCourseId);

    cout << "Course ID updated successfully." << endl;
    return true;
}

bool modifyBookingDate(int bookingIndex)
{
    bool validBookingDate;

    do {
        cout << endl;
        cout << "Enter new Booking Date (DD/MM/YYYY): ";
        cin >> bookingDate[bookingIndex];

        validBookingDate = isValidBookingDate(bookingDate[bookingIndex]);

        if (!validBookingDate)
            cout << "Invalid date format. Please use DD/MM/YYYY." << endl;

    } while (!validBookingDate);

    cout << "Booking Date updated successfully." << endl;
    return true;
}

bool cancelBooking()
{
    string bookingId;
    int bookingIndex;

    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;

    // find where the user record is
    bookingIndex = findBookingIndex(bookingId);

    if (bookingIndex == -1) {
        cout << "Booking ID does not exist." << endl;
        return false;
    }

    if (bookingStatus[bookingIndex] == "Cancelled") {
        cout << "This booking has already been cancelled." << endl;
        return false;
    }

    cout << "\nBooking Found" << endl;
    cout << "Booking ID\t: " << bookingID[bookingIndex] << endl;
    cout << "Course ID\t: " << bookingCourseID[bookingIndex] << endl;
    cout << "Booking Date\t: " << bookingDate[bookingIndex] << endl;

    // cancel comfirmation
    char cancellationConfirmation;

    do {
        cout << "\nConfirm cancellation? (Y/N): ";
        cin >> cancellationConfirmation;
        cancellationConfirmation = toupper(cancellationConfirmation);

        if (cancellationConfirmation != 'Y' && cancellationConfirmation != 'N')
            cout << "Invalid input. Please enter Y or N." << endl;

    } while (cancellationConfirmation != 'Y' && cancellationConfirmation != 'N');

    if (cancellationConfirmation == 'Y') {
        bookingStatus[bookingIndex] = "Cancelled";
        cout << "Booking cancelled successfully.\n" << endl;
        return true;
    }
    else {
        cout << "Booking cancellation aborted." << endl;
        return false;
    }
}

// ============================================================
//                 STUDENT D - REPORTING MODULE
// ============================================================

// ============================================================
// REPORTING MENU
// ============================================================

void ReportingMenu()
{
    int choice;

    do {
        cout << "\n";
        cout << "==================================================\n";
        cout << "                REPORTING MODULE\n";
        cout << "==================================================\n";
        cout << "1. Generate Summary Report\n";
        cout << "2. Generate Detailed Report\n";
        cout << "3. Calculate Statistics\n";
        cout << "4. Sort Records\n";
        cout << "5. Display Analysis\n";
        cout << "6. Back to Main Menu\n";
        cout << "==================================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            generateSummaryReport();
            break;

        case 2:
            generateDetailedReport();
            break;

        case 3:
            calculateStatistics();
            break;

        case 4:
            sortRecords();
            break;

        case 5:
            displayAnalysis();
            break;

        case 6:
            cout << "\nReturning to Main Menu...\n";
            break;

        default:
            cout << "\nInvalid choice. Please enter 1 - 6.\n";
        }
    } while (choice != 6);
}

// ============================================================
// 1. GENERATE SUMMARY REPORT
// ============================================================

void generateSummaryReport()
{
    int activeBookings = 0;
    int cancelledBookings = 0;

    double totalFee = 0.0;
    double averageFee = 0.0;

    // Count booking status
    for (int i = 0; i < bookingCount; i++) {
        if (bookingStatus[i] == "Active")
            activeBookings++;
        else if (bookingStatus[i] == "Cancelled")
            cancelledBookings++;
    }

    // Calculate total course fee
    for (int i = 0; i < courseCount; i++)
        totalFee += courseFee[i];

    // Calculate average course fee
    if (courseCount > 0)
        averageFee = totalFee / courseCount;

    // Display summary report
    cout << "\n";
    cout << "==================================================\n";
    cout << "                 SUMMARY REPORT\n";
    cout << "==================================================\n";

    cout << left;
    cout << setw(25) << "Total Students" << ": " << studentCount << endl;
    cout << setw(25) << "Total Courses" << ": " << courseCount << endl;
    cout << setw(25) << "Total Bookings" << ": " << bookingCount << endl;
    cout << setw(25) << "Active Bookings" << ": " << activeBookings << endl;
    cout << setw(25) << "Cancelled Bookings" << ": " << cancelledBookings << endl;
    cout << setw(25) << "Average Course Fee" << ": RM "
        << fixed << setprecision(2) << averageFee << endl;

    cout << "==================================================\n";
}

// ============================================================
// 2. GENERATE DETAILED REPORT
// ============================================================

void generateDetailedReport()
{
    cout << "\n";
    cout << "============================================================\n";
    cout << "                    DETAILED REPORT\n";
    cout << "============================================================\n";

    // Check whether booking records exist
    if (bookingCount == 0) {
        cout << "No booking records available.\n";
        cout << "============================================================\n";
        return;
    }

    // Process each booking
    for (int i = 0; i < bookingCount; i++) {
        string studentName = "Unknown";
        string courseNameReport = "Unknown";
        string subject = "Unknown";
        double courseFeeReport = 0.0;

        // ----------------------------------------------------
        // Search for student's name
        // ----------------------------------------------------
        for (int j = 0; j < maxrow; j++) {
            if (StuID[j] == bookingStudentID[i]) {
                studentName = StuName[j];
                break;
            }
        }

        // ----------------------------------------------------
        // Search for course information
        // ----------------------------------------------------
        for (int j = 0; j < courseCount; j++) {
            if (courseID[j] == bookingCourseID[i]) {
                courseNameReport = courseName[j];
                subject = courseCategory[j];
                courseFeeReport = courseFee[j];
                break;
            }
        }

        // ----------------------------------------------------
        // Display detailed information
        // ----------------------------------------------------
        cout << "\n";
        cout << "Booking ID   : " << bookingID[i] << endl;
        cout << "Student ID   : " << bookingStudentID[i] << endl;
        cout << "Student Name : " << studentName << endl;
        cout << "Course ID    : " << bookingCourseID[i] << endl;
        cout << "Course Name  : " << courseNameReport << endl;
        cout << "Subject      : " << subject << endl;
        cout << "Course Fee   : RM " << fixed << setprecision(2)
            << courseFeeReport << endl;
        cout << "Booking Date : " << bookingDate[i] << endl;
        cout << "Status       : " << bookingStatus[i] << endl;
        cout << "------------------------------------------------------------\n";
    }

    cout << "============================================================\n";
}

// ============================================================
// 3. CALCULATE STATISTICS
// ============================================================

void calculateStatistics()
{
    int activeBookings = 0;
    int cancelledBookings = 0;

    double totalFee = 0.0;
    double averageFee = 0.0;
    double highestFee = 0.0;
    double lowestFee = 0.0;

    // --------------------------------------------------------
    // Count active and cancelled bookings
    // --------------------------------------------------------
    for (int i = 0; i < bookingCount; i++) {
        if (bookingStatus[i] == "Active")
            activeBookings++;
        else if (bookingStatus[i] == "Cancelled")
            cancelledBookings++;
    }

    // --------------------------------------------------------
    // Calculate course fee statistics
    // --------------------------------------------------------
    if (courseCount > 0) {
        highestFee = courseFee[0];
        lowestFee = courseFee[0];

        for (int i = 0; i < courseCount; i++) {
            totalFee += courseFee[i];

            if (courseFee[i] > highestFee)
                highestFee = courseFee[i];

            if (courseFee[i] < lowestFee)
                lowestFee = courseFee[i];
        }

        averageFee = totalFee / courseCount;
    }

    // --------------------------------------------------------
    // Display statistics
    // --------------------------------------------------------
    cout << "\n";
    cout << "==================================================\n";
    cout << "                 STATISTICS\n";
    cout << "==================================================\n";

    cout << "Total Students       : " << studentCount << endl;
    cout << "Total Courses        : " << courseCount << endl;
    cout << "Total Bookings       : " << bookingCount << endl;
    cout << "Active Bookings      : " << activeBookings << endl;
    cout << "Cancelled Bookings   : " << cancelledBookings << endl;

    if (courseCount > 0) {
        cout << fixed << setprecision(2);
        cout << "Highest Course Fee   : RM " << highestFee << endl;
        cout << "Lowest Course Fee    : RM " << lowestFee << endl;
        cout << "Average Course Fee   : RM " << averageFee << endl;
    }
    else {
        cout << "No course fee data available.\n";
    }

    cout << "==================================================\n";
}

// ============================================================
// 4. SORT RECORDS
//    SELECTION SORT
//    Sort courses according to Course Fee
// ============================================================

void sortRecords()
{
    if (courseCount == 0) {
        cout << "\nNo course records available.\n";
        return;
    }

    // --------------------------------------------------------
    // Selection Sort
    // Sort Course Fee from Lowest to Highest
    // --------------------------------------------------------

    for (int i = 0; i < courseCount - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < courseCount; j++) {
            if (courseFee[j] < courseFee[minIndex])
                minIndex = j;
        }

        // Swap course information
        if (minIndex != i) {
            swap(courseID[i], courseID[minIndex]);
            swap(courseName[i], courseName[minIndex]);
            swap(courseCategory[i], courseCategory[minIndex]);
            swap(courseFee[i], courseFee[minIndex]);
        }
    }

    // --------------------------------------------------------
    // Display sorted records
    // --------------------------------------------------------

    cout << "\n";
    cout << "============================================================\n";
    cout << "                SORTED COURSE RECORDS\n";
    cout << "                Fee: Lowest to Highest\n";
    cout << "============================================================\n";

    cout << left
        << setw(12) << "Course ID"
        << setw(25) << "Course Name"
        << setw(20) << "Subject"
        << setw(12) << "Fee"
        << endl;

    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < courseCount; i++) {
        cout << left
            << setw(12) << courseID[i]
            << setw(25) << courseName[i]
            << setw(20) << courseCategory[i]
            << "RM "
            << fixed << setprecision(2)
            << courseFee[i] << endl;
    }

    cout << "============================================================\n";
}

// ============================================================
// 5. DISPLAY ANALYSIS
// ============================================================

void displayAnalysis()
{
    if (courseCount == 0) {
        cout << "\nNo course data available for analysis.\n";
        return;
    }

    // --------------------------------------------------------
    // Find most expensive and cheapest course
    // --------------------------------------------------------

    int highestIndex = 0;
    int lowestIndex = 0;

    for (int i = 1; i < courseCount; i++) {
        if (courseFee[i] > courseFee[highestIndex])
            highestIndex = i;

        if (courseFee[i] < courseFee[lowestIndex])
            lowestIndex = i;
    }

    // --------------------------------------------------------
    // Count booking status
    // --------------------------------------------------------

    int activeBookings = 0;
    int cancelledBookings = 0;

    for (int i = 0; i < bookingCount; i++) {
        if (bookingStatus[i] == "Active")
            activeBookings++;
        else if (bookingStatus[i] == "Cancelled")
            cancelledBookings++;
    }

    // --------------------------------------------------------
    // Calculate active booking rate
    // --------------------------------------------------------

    double activeRate = 0.0;

    if (bookingCount > 0)
        activeRate = (double)activeBookings / bookingCount * 100;

    // --------------------------------------------------------
    // Display analysis
    // --------------------------------------------------------

    cout << "\n";
    cout << "==================================================\n";
    cout << "                 CENTRE ANALYSIS\n";
    cout << "==================================================\n";

    cout << "\n[Course Fee Analysis]\n";

    cout << "Most Expensive Course : " << courseName[highestIndex] << endl;
    cout << "Course ID             : " << courseID[highestIndex] << endl;
    cout << "Fee                   : RM "
        << fixed << setprecision(2)
        << courseFee[highestIndex] << endl;

    cout << "\nCheapest Course       : " << courseName[lowestIndex] << endl;
    cout << "Course ID             : " << courseID[lowestIndex] << endl;
    cout << "Fee                   : RM "
        << fixed << setprecision(2)
        << courseFee[lowestIndex] << endl;

    cout << "\n[Booking Analysis]\n";
    cout << "Active Bookings       : " << activeBookings << endl;
    cout << "Cancelled Bookings    : " << cancelledBookings << endl;
    cout << "Active Booking Rate   : "
        << fixed << setprecision(2)
        << activeRate << "%" << endl;

    cout << "==================================================\n";
}

// ============================================================
//                 MAIN PROGRAM
// ============================================================

int main()
{
    OpenFile();
    LoadAccounts();
    LoadCourses();
    LoadEnrollments();


    char role;

    do {
        clearScreen();
        displayLogo();

        role = checkRole();

        if (role == 'T')
            teacherSelection();
        else if (role == 'S')
            studentSelection();

        if (role != 'E') {
            SaveToFile();
            SaveCourses();
            SaveEnrollments();

        }

    } while (role != 'E');

    SaveToFile();
    SaveCourses();
    SaveEnrollments();


    cout << "\nThank you for using Tuition Centre System. Goodbye!\n";
    return 0;
}
