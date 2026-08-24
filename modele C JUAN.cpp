#include <iomanip>
#include <iostream>
#include <string>
#include <cctype>
#include <windows.h> 


using namespace std;


// array student table
const int MAX_BOOKINGS = 100;
int bookingCount = 0;
string bookingID[MAX_BOOKINGS];
string bookingStudentID[MAX_BOOKINGS];
string bookingCourseID[MAX_BOOKINGS];
string bookingDate[MAX_BOOKINGS];
string bookingStatus[MAX_BOOKINGS];

// fake information for testing function
const int TEST_STUDENT_COUNT = 3;
const int TEST_COURSE_COUNT = 3;


string testStudentIds[TEST_STUDENT_COUNT] ={"S001","S002","S003"};
string testCourseIds[TEST_COURSE_COUNT] ={"C001","C002","C003"};

// untill here above are fake information




// function declaration 
void createBooking(); // need a course menu, student register functon
void modifyBooking(); // for modify
void modifyBookingCourseId(int bookingIndex);
void modifyBookingDate(int bookingIndex);
void cancelBooking();

bool studentIdExists(string studentId); // for checking student ID validation
bool courseIdExists(string courseId); // for checking the course ID validation
bool isValidBookingDate(string bookingDate); // check for the validation of date

int findBookingIndex(string bookingId); // find where the user id is
void clearScreen(); // clear screen




// register course function
void createBooking() {

    // avoid exceed the maximun of table
    if (bookingCount >= MAX_BOOKINGS)
    {
        cout << "Booking record is full. "
            << "Unable to create a new booking." << endl;

        // if this statament execute, then return user to where he is
        return;
    }

   
    bookingID[bookingCount] = "B" + to_string(bookingCount + 1);
    cout << "Generated Booking ID\t\t: " << bookingID[bookingCount] << endl;

       // check for student validation
    bool validStudentId;

    do
    {
        cout << "Enter Student ID\t\t: ";
        cin >> bookingStudentID[bookingCount];

        validStudentId = studentIdExists(bookingStudentID[bookingCount]);

           
        if (!validStudentId)
        {
            cout << "Student ID does not exist. "
                << "Please enter a valid Student ID." << endl << endl;
        }

    } while (!validStudentId);


    // check for the validation of the course ID
    bool validCourseId;

    do
    {
        cout << "Enter Course ID\t\t\t: ";
        cin >> bookingCourseID[bookingCount];

        validCourseId =
            courseIdExists(bookingCourseID[bookingCount]);

        if (!validCourseId)
        {
            cout << "Course ID does not exist. "
                << "Please enter a valid Course ID." << endl << endl;
        }

    } while (!validCourseId);



    // check for the vaidation of date format
    bool validBookingDate;

    do
    {
        cout << "Enter Booking Date (DD/MM/YYYY) : ";
        cin >> bookingDate[bookingCount];

        validBookingDate = isValidBookingDate(bookingDate[bookingCount]);
           

        if (!validBookingDate)
        {
            cout << "Invalid date format. " << "Please use DD/MM/YYYY." << endl << endl;
                
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

}

// need to change the condition name to match the table of module A ·
bool studentIdExists(string studentId)
{
    for (int studentIndex = 0; studentIndex < TEST_STUDENT_COUNT;  studentIndex++) {

        if (studentId == testStudentIds[studentIndex]){
            return true;
        }
    }

    return false;
}

// need to change the condition name to match 
bool courseIdExists(string courseId)
{
    for (int courseIndex = 0; courseIndex < TEST_COURSE_COUNT; courseIndex++) {

        if (courseId == testCourseIds[courseIndex])
        {
            return true;
        }
    }

    return false;
}



// check for the validation of date
bool isValidBookingDate(string bookingDate)
{
    if (bookingDate.length() != 10)
    {
        return false;
    }

    if (bookingDate[2] != '/' ||
        bookingDate[5] != '/')
    {
        return false;
    }

    for (int characterIndex = 0;
        characterIndex < bookingDate.length();
        characterIndex++)
    {
        if (characterIndex != 2 &&
            characterIndex != 5 &&
            !isdigit(bookingDate[characterIndex]))
        {
            return false;
        }
    }

    int bookingDay =
        stoi(bookingDate.substr(0, 2));

    int bookingMonth =
        stoi(bookingDate.substr(3, 2));

    if (bookingDay < 1 || bookingDay > 31 || bookingMonth < 1 || bookingMonth > 12) {
        return false;
    }

    return true;
}

// =======================================
//  for modify and cancel part
//=====================================
int findBookingIndex(string bookingId){


    // find every single record from index 1 till found it
    for (int recordIndex = 0; recordIndex < bookingCount; recordIndex++){

        // check if the record we found match the user ID
        if (bookingId == bookingID[recordIndex]){

            return recordIndex;
        }
    }
    // if cant find it then return -1, cuz array dont have -1 position
    return -1;
}


void modifyBooking()
{
    string bookingId; // user ID 
    int bookingIndex; 

    cout << "Enter Booking ID to modify: ";
    cin >> bookingId;

    bookingIndex = findBookingIndex(bookingId);

    if (bookingIndex == -1) {

        cout << "Booking ID does not exist." << endl;

        return;
    }

    if (bookingStatus[bookingIndex] == "Cancelled") {

        cout << "Cancelled booking cannot be modified." << endl;

        return;
    }
    

    cout << "\nCurrent Booking Details" << endl;
    cout << "Booking ID\t: "
        << bookingID[bookingIndex] << endl;
    cout << "Student ID\t: "
        << bookingStudentID[bookingIndex] << endl;
    cout << "Course ID\t: "
        << bookingCourseID[bookingIndex] << endl;
    cout << "Booking Date\t: "
        << bookingDate[bookingIndex] << endl;
    cout << "Booking Status\t: "
        << bookingStatus[bookingIndex] << endl;

    int modificationSelection;

    do
    {
        cout << "\nWhat would you like to modify?" << endl;
        cout << "1. Course ID" << endl;
        cout << "2. Booking Date" << endl;
        cout << "3. Back" << endl;
        cout << "Enter your selection: ";
        cin >> modificationSelection;

        if (modificationSelection < 1 || modificationSelection > 3){
            
            cout << "Invalid selection. "
                << "Please enter 1, 2, or 3." << endl;
        }

    } while (modificationSelection < 1 || modificationSelection > 3);

    if (modificationSelection == 1) {
        modifyBookingCourseId(bookingIndex);
    }
    else if (modificationSelection == 2) {

        modifyBookingDate(bookingIndex);
    }
    else {
        cout << "No changes were made." << endl;
    }
       
}



void modifyBookingCourseId(int bookingIndex) {

   
        bool validCourseId;

        do
        {
            cout << endl;
            cout << "Enter new Course ID: ";
            cin >> bookingCourseID[bookingIndex];

            validCourseId = courseIdExists(bookingCourseID[bookingIndex]);

            if (!validCourseId) {

                cout << "Course ID does not exist. "
                    << "Please enter a valid Course ID." << endl;
            }

        } while (!validCourseId);

        cout << "Course ID updated successfully." << endl;
  
}

void modifyBookingDate(int bookingIndex) {

    bool validBookingDate;

    do {
        cout << endl;
        cout << "Enter new Booking Date (DD/MM/YYYY): ";
        cin >> bookingDate[bookingIndex];

        validBookingDate =
            isValidBookingDate(bookingDate[bookingIndex]);

        if (!validBookingDate) {

            cout << "Invalid date format. "
                << "Please use DD/MM/YYYY." << endl;
        }

    } while (!validBookingDate);

    cout << "Booking Date updated successfully." << endl;
}


void cancelBooking() {
    string bookingId;
    int bookingIndex;

    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;

    // find where the user record is
    bookingIndex = findBookingIndex(bookingId);

    if (bookingIndex == -1) {
        cout << "Booking ID does not exist." << endl;

        return;
    }

    if (bookingStatus[bookingIndex] == "Cancelled") {
        cout << "This booking has already been cancelled." << endl;

        return;
    }

    cout << "\nBooking Found" << endl;
    cout << "Booking ID\t: "
        << bookingID[bookingIndex] << endl;
    cout << "Course ID\t: "
        << bookingCourseID[bookingIndex] << endl;
    cout << "Booking Date\t: "
        << bookingDate[bookingIndex] << endl;


    // cancel comfirmation
    char cancellationConfirmation;

    do {
        cout << "\nConfirm cancellation? (Y/N): ";
        cin >> cancellationConfirmation;
        cancellationConfirmation = toupper(cancellationConfirmation);

        if (cancellationConfirmation != 'Y' && cancellationConfirmation != 'N') {
           
            cout << "Invalid input. "
                << "Please enter Y or N." << endl;
        }

    } while (cancellationConfirmation != 'Y' && cancellationConfirmation != 'N');

    if (cancellationConfirmation == 'Y') {
      
        bookingStatus[bookingIndex] = "Cancelled";

        cout << "Booking cancelled successfully.\n" << endl;
    }
    else
    {
        cout << "Booking cancellation aborted." << endl; 
    }

}

int main() {

    createBooking();
    

	return 0;
}