#include <iostream>
#include <string>
using namespace std;


// declare variables

const int maxrow = 100;

string CourseID[maxrow];
string CourseName[maxrow];
string Subject[maxrow];
double CourseFee[maxrow];


// ========================================
// TEACHER FUNCTIONS
// ========================================


// 1. Add Course

void AddCourse()
{
    string id;
    string name;
    string subject;
    double fee;

    cin.ignore();

    cout << "Course ID: ";
    getline(cin, id);

    cout << "Course Name: ";
    getline(cin, name);

    cout << "Subject: ";
    getline(cin, subject);

    cout << "Course Fee: RM ";
    cin >> fee;

    for (int x = 0; x < maxrow; x++)
    {
        if (CourseID[x] == "")
        {
            CourseID[x] = id;
            CourseName[x] = name;
            Subject[x] = subject;
            CourseFee[x] = fee;

            cout << "Course added successfully!" << endl;
            break;
        }
    }
}


// 2. Update Course

void UpdateCourse(string search)
{
    int counter = 0;

    for (int x = 0; x < maxrow; x++)
    {
        if (CourseID[x] == search)
        {
            counter++;

            cin.ignore();

            cout << "New Course Name: ";
            getline(cin, CourseName[x]);

            cout << "New Subject: ";
            getline(cin, Subject[x]);

            cout << "New Course Fee: RM ";
            cin >> CourseFee[x];

            cout << "Update Successful!" << endl;

            break;
        }
    }

    if (counter == 0)
    {
        cout << "Course ID does not exist!" << endl;
    }
}


// 3. Delete Course

void DeleteCourse(string search)
{
    int counter = 0;

    for (int x = 0; x < maxrow; x++)
    {
        if (CourseID[x] == search)
        {
            counter++;

            CourseID[x] = "";
            CourseName[x] = "";
            Subject[x] = "";
            CourseFee[x] = 0;

            cout << "Successfully Deleted!" << endl;

            break;
        }
    }

    if (counter == 0)
    {
        cout << "Course ID does not exist!" << endl;
    }
}


// ========================================
// STUDENT 2 FUNCTIONS
// ========================================


// 4. Search Course
// Student enters a specific Course ID

void SearchCourse()
{
    string searchID;
    int counter = 0;

    cout << endl;
    cout << "Search Course" << endl;
    cout << "================================" << endl;

    // Student enters Course ID
    cout << "Enter Course ID: ";
    cin >> searchID;

    // Search Course ID
    for (int x = 0; x < maxrow; x++)
    {
        if (CourseID[x] == searchID)
        {
            counter++;

            // Display matching course details
            cout << endl;
            cout << "Course Found!" << endl;
            cout << "Course ID: " << CourseID[x] << endl;
            cout << "Course Name: " << CourseName[x] << endl;
            cout << "Subject: " << Subject[x] << endl;
            cout << "Course Fee: RM " << CourseFee[x] << endl;

            break;
        }
    }

    // Course ID not found
    if (counter == 0)
    {
        cout << endl;
        cout << "Course ID does not exist!" << endl;
    }

    cout << "================================" << endl;
}


// 5. Display Course

void ListCourse()
{
    int counter = 0;

    cout << endl;
    cout << "Current Course(s)" << endl;
    cout << "================================" << endl;

    for (int x = 0; x < maxrow; x++)
    {
        if (CourseID[x] != "")
        {
            counter++;

            cout << "No. " << counter << endl;
            cout << "Course ID: " << CourseID[x] << endl;
            cout << "Course Name: " << CourseName[x] << endl;
            cout << "Subject: " << Subject[x] << endl;
            cout << "Course Fee: RM " << CourseFee[x] << endl;

            cout << "--------------------------------" << endl;
        }
    }

    if (counter == 0)
    {
        cout << "No courses found!" << endl;
    }
}


// ========================================
// TEACHER MENU
// ========================================

void TeacherMenu()
{
    int option;
    string searchID;

    do
    {
        cout << endl;
        cout << "================================" << endl;
        cout << "          TEACHER MENU" << endl;
        cout << "================================" << endl;

        cout << "1 - Add Course" << endl;
        cout << "2 - Update Course" << endl;
        cout << "3 - Delete Course" << endl;
        cout << "4 - Search Course" << endl;
        cout << "5 - Display Course" << endl;
        cout << "6 - Exit" << endl;

        cout << "================================" << endl;

        cout << "Select option >> ";
        cin >> option;

        switch (option)
        {
        case 1:
            AddCourse();
            break;

        case 2:
            cout << "Enter Course ID to update: ";
            cin >> searchID;
            UpdateCourse(searchID);
            break;

        case 3:
            cout << "Enter Course ID to delete: ";
            cin >> searchID;
            DeleteCourse(searchID);
            break;

        case 4:
            SearchCourse();
            break;

        case 5:
            ListCourse();
            break;

        case 6:
            cout << "Exit Teacher Menu." << endl;
            break;

        default:
            cout << "Invalid option!" << endl;
        }

    } while (option != 6);
}


// ========================================
// STUDENT MENU
// ONLY SEARCH AND DISPLAY
// ========================================

void StudentMenu()
{
    int option;

    do
    {
        cout << endl;
        cout << "================================" << endl;
        cout << "          STUDENT MENU" << endl;
        cout << "================================" << endl;

        cout << "1 - Search Course" << endl;
        cout << "2 - Display Course" << endl;
        cout << "3 - Exit" << endl;

        cout << "================================" << endl;

        cout << "Select option >> ";
        cin >> option;

        switch (option)
        {
        case 1:

            // Student searches by specific Course ID
            SearchCourse();

            break;

        case 2:

            // Display all courses
            ListCourse();

            break;

        case 3:

            cout << "Exit Student Menu." << endl;

            break;

        default:

            cout << "Invalid option!" << endl;
        }

    } while (option != 3);
}


// ========================================
// MAIN
// ========================================

int main()
{
    int option;

    do
    {
        cout << endl;
        cout << "================================" << endl;
        cout << "  TUITION CENTRE MANAGEMENT" << endl;
        cout << "================================" << endl;

        cout << "1 - Teacher Menu" << endl;
        cout << "2 - Student Menu" << endl;
        cout << "3 - Exit" << endl;

        cout << "================================" << endl;

        cout << "Select option >> ";
        cin >> option;

        switch (option)
        {
        case 1:

            TeacherMenu();

            break;

        case 2:

            StudentMenu();

            break;

        case 3:

            cout << "Thank you!" << endl;

            break;

        default:

            cout << "Invalid option!" << endl;
        }

    } while (option != 3);

    return 0;
}