#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

using namespace std;

const int maxCourses = 50;

string courseID[maxCourses];
string courseName[maxCourses];
string courseCategory[maxCourses];
double courseFee[maxCourses];
int courseCount = 0;

void OpenCourseFile();
void SaveCourseFile();
bool AddCourse();
bool ModifyCourse(string searchID);
bool DeleteCourse(string searchID);
bool SearchCourse(string searchID);
bool DisplayCourses(string filterCategory = "ALL");

void clearScreen();
void displayLogo();
void Backtomenu();
void teacher_course_menu();
void student_course_menu();

int main() {
    remove("courses.txt");
    OpenCourseFile();

    char role;
    do {
        clearScreen();
        displayLogo();
        cout << "Welcome to Tuition Centre Course Management System\n";
        cout << "--------------------------------------------------\n";
        cout << "Please select your role:\n";
        cout << "[T] Teacher (Register, Modify, Delete, Search, Display)\n";
        cout << "[S] Student (Search, Display Primary/Secondary Courses)\n";
        cout << "[E] Exit Program\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> role;
        role = toupper(role);

        if (role == 'T') {
            teacher_course_menu();
        }
        else if (role == 'S') {
            student_course_menu();
        }
        else if (role != 'E') {
            cout << "[ERROR] Invalid option! Press Enter to try again...";
            cin.ignore();
            cin.get();
        }
    } while (role != 'E');

    clearScreen();
    cout << "Thank you for using Tuition Centre System. Goodbye!\n";
    return 0;
}


void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void displayLogo() {
    cout << "========================================\n";
    cout << "    TUITION CENTRE COURSE MANAGEMENT    \n";
    cout << "========================================\n";
}

void Backtomenu() {
    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}

void OpenCourseFile() {
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
    }
    else {
        courseID[0] = "P101"; courseName[0] = "Science"; courseCategory[0] = "Primary";   courseFee[0] = 90.00;
        courseID[1] = "P102"; courseName[1] = "Maths";   courseCategory[1] = "Primary";   courseFee[1] = 90.00;
        courseID[2] = "P103"; courseName[2] = "Chinese"; courseCategory[2] = "Primary";   courseFee[2] = 85.00;
        courseID[3] = "P104"; courseName[3] = "Malay";   courseCategory[3] = "Primary";   courseFee[3] = 85.00;
        courseID[4] = "P105"; courseName[4] = "English"; courseCategory[4] = "Primary";   courseFee[4] = 85.00;
        courseID[5] = "S201"; courseName[5] = "Add Maths"; courseCategory[5] = "Secondary"; courseFee[5] = 130.00;
        courseID[6] = "S202"; courseName[6] = "Physics";   courseCategory[6] = "Secondary"; courseFee[6] = 150.00;
        courseID[7] = "S203"; courseName[7] = "Account";   courseCategory[7] = "Secondary"; courseFee[7] = 150.00;
        courseID[8] = "S204"; courseName[8] = "Ekonomi";   courseCategory[8] = "Secondary"; courseFee[8] = 150.00;
        courseID[9] = "S205"; courseName[9] = "Geografi";  courseCategory[9] = "Secondary"; courseFee[9] = 130.00;
        courseID[10] = "S206"; courseName[10] = "Sejarah"; courseCategory[10] = "Secondary"; courseFee[10] = 130.00;
        courseID[11] = "S207"; courseName[11] = "Science"; courseCategory[11] = "Secondary"; courseFee[11] = 130.00;
        courseID[12] = "S208"; courseName[12] = "Maths"; courseCategory[12] = "Secondary"; courseFee[12] = 130.00;
        courseID[13] = "S209"; courseName[13] = "English"; courseCategory[13] = "Secondary"; courseFee[13] = 130.00;
        courseID[14] = "S210"; courseName[14] = "Malay"; courseCategory[14] = "Secondary"; courseFee[14] = 130.00;
        courseCount = 15;
        SaveCourseFile();
    }
}

void SaveCourseFile() {
    ofstream myfile("courses.txt");
    if (!myfile.is_open()) {
        cout << "[ERROR] Could not open courses.txt for saving!\n";
        return;
    }

    for (int i = 0; i < courseCount; i++) {
        if (!courseID[i].empty()) {
            myfile << courseID[i] << ","
                << courseName[i] << ","
                << courseCategory[i] << ","
                << fixed << setprecision(2) << courseFee[i] << endl;
        }
    }
    myfile.close();
}

bool AddCourse() {
    if (courseCount >= maxCourses) {
        cout << "[ERROR] Storage full! Cannot add more courses.\n";
        return false;
    }

    string id, name;
    int catChoice;
    double fee;

    cin.ignore();
    cout << "\n--- Add New Course ---\n";
    cout << "Enter Course ID (e.g., P103 / S203): ";
    getline(cin, id);

    for (int i = 0; i < courseCount; i++) {
        if (courseID[i] == id) {
            cout << "[ERROR] Duplicate Course ID! Registration failed.\n";
            return false;
        }
    }

    cout << "Enter Course Name (e.g., Form 3 English): ";
    getline(cin, name);

    cout << "Select Level:\n";
    cout << "  1. Primary (小学)\n";
    cout << "  2. Secondary (中学)\n";
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

bool ModifyCourse(string searchID) {
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

    cin.ignore();
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

bool DeleteCourse(string searchID) {
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

bool SearchCourse(string searchID) {
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

    if (!found) {
        cout << " [ERROR] No course record found matching ID '" << searchID << "'.\n";
    }
    cout << "========================================================\n";
    return found;
}

bool DisplayCourses(string filterCategory) {
    clearScreen();
    cout << "========================================================================\n";
    if (filterCategory == "Primary") {
        cout << "                   PRIMARY SCHOOL COURSES                            \n";
    }
    else if (filterCategory == "Secondary") {
        cout << "                  SECONDARY SCHOOL COURSES                           \n";
    }
    else {
        cout << "                      ALL TUITION COURSES                               \n";
    }
    cout << "========================================================================\n";
    cout << " No. | Course ID | Course Name         | Category   | Fee (RM)          \n";
    cout << "------------------------------------------------------------------------\n";

    int displayedCount = 0;
    for (int i = 0; i < courseCount; i++) {
        if (filterCategory == "ALL" || courseCategory[i] == filterCategory) {
            displayedCount++;
            cout << " " << setw(2) << displayedCount << "  | "
                << setw(9) << left << courseID[i] << " | "
                << setw(19) << left << courseName[i] << " | "
                << setw(10) << left << courseCategory[i] << " | RM "
                << setw(7) << right << fixed << setprecision(2) << courseFee[i] << endl;
        }
    }

    if (displayedCount == 0) {
        cout << " No courses found under this section.\n";
    }
    cout << "========================================================================\n";
    return displayedCount > 0;
}

void teacher_course_menu() {
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

void student_course_menu() {
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
        cout << "5. Back to Role Selection\n";
        cout << "-------------------------------------------\n";
        cout << "Select Option (1-5): ";

        while (!(cin >> option) || option < 1 || option > 5) {
            cout << "[ERROR] Invalid option! Enter 1-5 only: ";
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
            cout << "Returning to previous menu...\n";
            break;
        }
    } while (option != 5);
}
