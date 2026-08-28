
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <windows.h>
using namespace std;

const int MAX_BOOKINGS = 100;
int bookingCount = 0;
string bookingID[MAX_BOOKINGS];
string bookingStudentID[MAX_BOOKINGS];
string bookingCourseID[MAX_BOOKINGS];
string bookingDate[MAX_BOOKINGS];
string bookingStatus[MAX_BOOKINGS];

// Function declarations
void createBooking();
void modifyBooking();
void modifyBookingCourseId(int bookingIndex);
void modifyBookingDate(int bookingIndex);
void cancelBooking();
void searchBooking();
void displayBookingSumm();
void displayBookStatus();

bool studentIdExists(string studentID);
bool courseIdExists(string courseId);
bool isValidBookingDate(string bookingDate);
int findBookingIndex(string bookingId);
void clearScreen();

// Fake information for testing function
const int TEST_STUDENT_COUNT = 3;
const int TEST_COURSE_COUNT = 3;

string testStudentIds[TEST_STUDENT_COUNT] = { "S001", "S002", "S003" };
string testCourseIds[TEST_COURSE_COUNT] = { "C001", "C002", "C003" };


// MAIN FUNCTION 
int main() {
    int choice;

    // Module C Menu
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
        cin >> choice;

        switch (choice) {
        case 1: createBooking(); break;
        case 2: modifyBooking(); break;
        case 3: cancelBooking(); break;
        case 4: searchBooking(); break;
        case 5: displayBookingSumm(); break;
        case 6: displayBookStatus(); break;
        case 7:
            cout << "Exiting Program...byeeeee\n";
            break;
        default:
            cout << "Invalid Choice. Please Try Again...\n";
            cout << "Press Enter to Continue\n";
            cin.ignore();
            cin.get();
            break;
        }
    } while (choice != 7);

    return 0;
}

// CLEAR SCREEN FUNCTION
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Create Booking Function
void createBooking() {
    if (bookingCount >= MAX_BOOKINGS) {
        cout << "Booking record is full. Unable to create a new booking." << endl;
        return;
    }

    bookingID[bookingCount] = "B" + to_string(bookingCount + 1);
    cout << "Generated Booking ID\t\t: " << bookingID[bookingCount] << endl;

    bool validStudentId;
    do {
        cout << "Enter Student ID\t\t: ";
        cin >> bookingStudentID[bookingCount];
        validStudentId = studentIdExists(bookingStudentID[bookingCount]);
        if (!validStudentId) {
            cout << "Student ID does not exist. Please enter a valid Student ID." << endl << endl;
        }
    } while (!validStudentId);

    bool validCourseId;
    do {
        cout << "Enter Course ID\t\t\t: ";
        cin >> bookingCourseID[bookingCount];
        validCourseId = courseIdExists(bookingCourseID[bookingCount]);
        if (!validCourseId) {
            cout << "Course ID does not exist. Please enter a valid Course ID." << endl << endl;
        }
    } while (!validCourseId);

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
}

bool studentIdExists(string studentId) {
    for (int i = 0; i < TEST_STUDENT_COUNT; i++) {
        if (studentId == testStudentIds[i]) {
            return true;
        }
    }
    return false;
}

bool courseIdExists(string courseId) {
    for (int i = 0; i < TEST_COURSE_COUNT; i++) {
        if (courseId == testCourseIds[i]) {
            return true;
        }
    }
    return false;
}

bool isValidBookingDate(string bookingDate) {
    if (bookingDate.length() != 10) return false;
    if (bookingDate[2] != '/' || bookingDate[5] != '/') return false;

    for (int i = 0; i < bookingDate.length(); i++) {
        if (i != 2 && i != 5 && !isdigit(bookingDate[i])) {
            return false;
        }
    }

    int day = stoi(bookingDate.substr(0, 2));
    int month = stoi(bookingDate.substr(3, 2));

    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }
    return true;
}

int findBookingIndex(string bookingId) {
    for (int i = 0; i < bookingCount; i++) {
        if (bookingId == bookingID[i]) {
            return i;
        }
    }
    return -1;
}

//MODIFY BOOKING
void modifyBooking() {
    string bookingId;
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

        if (modificationSelection < 1 || modificationSelection > 3) {
            cout << "Invalid selection. Please enter 1, 2, or 3." << endl;
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
    do {
        cout << endl;
        cout << "Enter new Course ID: ";
        cin >> bookingCourseID[bookingIndex];
        validCourseId = courseIdExists(bookingCourseID[bookingIndex]);
        if (!validCourseId) {
            cout << "Course ID does not exist. Please enter a valid Course ID." << endl;
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
        validBookingDate = isValidBookingDate(bookingDate[bookingIndex]);
        if (!validBookingDate) {
            cout << "Invalid date format. Please use DD/MM/YYYY." << endl;
        }
    } while (!validBookingDate);
    cout << "Booking Date updated successfully." << endl;
}

// CANCEL BOOKING
void cancelBooking() {
    string bookingId;
    int bookingIndex;

    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;

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
    cout << "Booking ID\t: " << bookingID[bookingIndex] << endl;
    cout << "Course ID\t: " << bookingCourseID[bookingIndex] << endl;
    cout << "Booking Date\t: " << bookingDate[bookingIndex] << endl;

    char cancellationConfirmation;
    do {
        cout << "\nConfirm cancellation? (Y/N): ";
        cin >> cancellationConfirmation;
        cancellationConfirmation = toupper(cancellationConfirmation);
        if (cancellationConfirmation != 'Y' && cancellationConfirmation != 'N') {
            cout << "Invalid input. Please enter Y or N." << endl;
        }
    } while (cancellationConfirmation != 'Y' && cancellationConfirmation != 'N');

    if (cancellationConfirmation == 'Y') {
        bookingStatus[bookingIndex] = "Cancelled";
        cout << "Booking cancelled successfully.\n" << endl;
    }
    else {
        cout << "Booking cancellation aborted." << endl;
    }
}

// SEARCH BOOKING
void searchBooking() {
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

    if (searchChoice == 6) {
        return;
    }
    if (searchChoice < 1 || searchChoice > 6) {
        cout << "Invalid choice. Please Try Again...\n";
        return;
    }
    cout << "Enter Search Term...: ";
    cin >> searchTerm;
    cout << "\n==========================>>||<<=========================\n";
    cout << "                          RESULTS \n";
    cout << "===========================>>===<<===========================\n";
    cout << left << setw(12) << "Booking ID"
        << left << setw(12) << "Student ID"
        << left << setw(12) << "Course ID"
        << left << setw(12) << "Date"
        << left << setw(12) << "Status" << endl;
    cout << "=================================================================\n";

    for (int i = 0; i < bookingCount; i++) {
        bool match = false;

        switch (searchChoice) {
        case 1: // Booking ID
            if (bookingID[i] == searchTerm) match = true;
            break;
        case 2: // Student ID
            if (bookingStudentID[i] == searchTerm) match = true;
            break;
        case 3: // Course ID
            if (bookingCourseID[i] == searchTerm) match = true;
            break;
        case 4: // Date
            if (bookingDate[i] == searchTerm) match = true;
            break;
        case 5: // Status
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
                << left << setw(12) << bookingStudentID[i]
                << left << setw(12) << bookingCourseID[i]
                << left << setw(12) << bookingDate[i]
                << left << setw(12) << bookingStatus[i] << endl;
        }
    }

    if (!found) {
        cout << " No Bookings Found That Matches Your Search.\n";
    }
    cout << "\n><><>><><><><><><><><><><<><><><><><><><><><><>\n";
    cout << " Press Enter to Continue...";
    cin.ignore();
    cin.get();
}

// DISPLAY BOOKING SUMMARY
void displayBookingSumm() {
    clearScreen();

    cout << "\n============================<<||>>==============================\n";
    cout << "            Booking Summary \n";
    cout << "============================<<===>>===============================\n";

    if (bookingCount == 0) {
        cout << "No Bookings Found...\n";
        cout << "Press Enter to Continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << left << setw(5) << "No."
        << left << setw(12) << "Booking ID"
        << left << setw(12) << "Student ID"
        << left << setw(12) << "Course ID"
        << left << setw(12) << "Date"
        << left << setw(12) << "Status" << endl;
    cout << "================================================================\n";

    for (int i = 0; i < bookingCount; i++) {
        cout << left << setw(5) << (i + 1)
            << left << setw(12) << bookingID[i]
            << left << setw(12) << bookingStudentID[i]
            << left << setw(12) << bookingCourseID[i]
            << left << setw(12) << bookingDate[i]
            << left << setw(12) << bookingStatus[i] << endl;
    }

    cout << "===============================================================\n";
    cout << "Total Bookings: " << bookingCount << endl;
    cout << "Press Enter to Continue...";
    cin.ignore();
    cin.get();
}

// DISPLAY BOOKINGS BY STATUS
void displayBookStatus() { 
    int statChoice;
    string statusFilter;

    clearScreen();
    cout << "\n==========================<<||>>=========================\n";
    cout << "                    Display Booking Status\n";
    cout << "============================================================\n";
    cout << " 1. Active Bookings\n";
    cout << " 2. Cancelled Bookings\n";
    cout << " 3. Return\n";
    cout << "Enter Your Choice...: ";
    cin >> statChoice;

    if (statChoice == 3) {
        return;
    }
    if (statChoice == 1) {
        statusFilter = "Active";
    }
    else if (statChoice == 2) {
        statusFilter = "Cancelled";  // ✅ Fixed spelling (was "Cancelled!")
    }
    else {
        cout << "Invalid choice!!!\n";
        return;
    }

    clearScreen();
    cout << "\n=====================================\n";
    cout << "  " << statusFilter << " Bookings     \n";
    cout << "-------------------------------------\n";

    bool found = false;

    cout << left << setw(5) << "No."
        << left << setw(12) << "Booking ID"
        << left << setw(12) << "Student ID"
        << left << setw(12) << "Course ID"
        << left << setw(12) << "Date"
        << left << setw(12) << "Status" << endl;
    cout << "><><><><><><>>>><><><><>><><><>>><><><>>><\n";

    int counter = 1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookingStatus[i] == statusFilter) {
            found = true;
            cout << left << setw(5) << counter
                << left << setw(12) << bookingID[i]
                << left << setw(12) << bookingStudentID[i]
                << left << setw(12) << bookingCourseID[i]
                << left << setw(12) << bookingDate[i]
                << left << setw(12) << bookingStatus[i] << endl;
            counter++;
        }
    }

    if (!found) {
        cout << "No " << statusFilter << " bookings found...\n";
    }
    cout << "====================================================================\n";
    cout << "Total " << statusFilter << " Bookings: " << (counter - 1) << endl;
    cout << "Press Enter to Continue...";
    cin.ignore();
    cin.get();
}
