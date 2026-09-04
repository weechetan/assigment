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

	//function
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

	void clearScreen();

    // fake information for testing function
    const int TEST_STUDENT_COUNT = 3;
    const int TEST_COURSE_COUNT = 3;


    string testStudentIds[TEST_STUDENT_COUNT] = { "S001","S002","S003" };
    string testCourseIds[TEST_COURSE_COUNT] = { "C001","C002","C003" };


    //moduleC Menu
    int menuCdisplay() {
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
            cin >> choice;

            return choice;

            choice = menuCdisplay();

            switch (choice) {
            case 1: createBooking();
                break;
            case 2: modifyBooking();
                break;
            case 3: cancelBooking();
                break;
            case 4: searchBooking();
                break;
            case 5: displayBookingSumm();
                break;
            case 6: displayBookStatus();
                break;
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
    }

//search booking
	bool searchBooking() {
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
		} if (searchChoice < 1 || searchChoice > 6) {
			cout << "Invalid choice. Please Try Again...\n";
			return;
		}
		cout << "Enter Search Team...:";
		cin >> searchTerm;
		cout << "\n=============>>||<<==============\n";
		cout << "               RESULTS \n";
		cout << "==============>>===<<===============\n";
		cout << left << setw(10) << "Booking ID" << left << setw(10) << "Student ID" << left << setw(10) << "Date" << left << setw(10) << "Status" << endl;
		cout << " ><><><>>><><><><>><><><><><>><>><><><><>\n";

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
			} break;

			}
			if (match) {
				found = true;
				cout << left << setw(10) << bookingID[i] << left << setw(10) << bookingStudentID[i] << left << setw(10) << bookingCourseID[i]
					<< left << setw(10) << bookingDate[i] << left << setw(10) << bookingStatus[i] << endl;
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

//DISPLAY booking summary
	bool displayBookingSumm() {
		clearScreen();

		cout << "\n================<<||>>==================\n";
		cout <<             "Booking Summary\n";
		cout << "================<<===>>================\n";

		if (bookingCount == 0) {
			cout << "No Bookings Found...\n";
			cout << "Press Enter to Continue...";
			cin.ignore();
			cin.get();
			return;
		}
		cout << left << setw(5) << "No. " << left << setw(10) << "Booking ID" << left << setw(10) << "Student ID"
			<< left << setw(10) << "Course ID" << left << setw(10) << "Date" << left << setw(10) << "Status" << endl;
		cout << "___________________________________________\n";

		for (int i = 0; i < bookingCount; i++) {
			cout << left << setw(5) << (i + 1) << left << setw(10) << bookingID[i] << left << setw(10) << bookingStudentID[i]
				<< left << setw(10) << bookingCourseID[i] << left << setw(10) << bookingDate[i] << left << setw(10) << bookingStatus[i] << endl;
		}
		cout << "__________________________________________\n";
		cout << "Total Bookings: " << bookingCount << endl;
		cout << "Press Enter to Continue...";
		cin.ignore();
		cin.get();
	}

// DISPLAY booking status
	int displayBookStatus() {
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

		if (statChoice == 3) {
			return;
		} if (statChoice == 1) {
			statusFilter = "Active";
		}
		else if (statChoice == 2) {
			statusFilter = "Cancelled";
		}
		else {
			cout << "Invalid choice!!!\n";
			return;
		}
		clearScreen();
		cout << "\n============================================================\n";
		cout << "  " << statusFilter << " Bookings     \n";
		cout << "--------------------------------------------------------------\n";
		bool found = false;

		cout << left << setw(5) << "No." << left << setw(10) << "Booking ID" << left << setw(10) << "Student ID"
			<< left << setw(10) << "Course ID" << left << setw(10) << "Date" << left << setw(10) << "Status" << endl;
		cout << "><><><><><><>>>><><><><>><><><>>><><><>><><><><><><><><><><>><\n";

		int counter = 1;
		for (int i = 0; i < bookingCount; i++) {
			if (bookingStatus[i] == statusFilter) {
				found = true;
				cout << left << setw(5) << counter << left << setw(10) << bookingID[i] << left << setw(10) << bookingStudentID[i]
					<< left << setw(10) << bookingCourseID[i] << left << setw(10) << bookingDate[i] << left << setw(10) << bookingStatus[i] << endl;
				counter++;
			}
		}
		if (!found) {
			cout << "No." << statusFilter << "bookings found...\n";
		}
		cout << "=========================================\n";
		cout << "Total" << statusFilter << "Bookings :" << (counter - 1) << endl;
		cout << "Press Enter to Continue...";
		cin.ignore();
		cin.get();
	}

//Juan Codes
    // register course function
    bool createBooking() {

        // avoid exceed the maximun of table
        if (bookingCount >= MAX_BOOKINGS)
        {
            cout << "Booking record is full. "
                << "Unable to create a new booking." << endl;

            // if this statament execute, then return user to where he is
            return false;
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

        return true; // create sucessfully
    }

    // need to change the condition name to match the table of module A ·
    bool studentIdExists(string studentId)
    {
        for (int studentIndex = 0; studentIndex < TEST_STUDENT_COUNT; studentIndex++) {

            if (studentId == testStudentIds[studentIndex]) {
                return true;
            }
        }

        return false;
    }

    // need to change the condition name to match 
    bool courseIdExists(string courseId)
    {
        for (int courseIndex = 0; courseIndex < TEST_COURSE_COUNT; courseIndex++) {

            if (courseId == testCourseIds[courseIndex]) {
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
    int findBookingIndex(string bookingId) {


        // find every single record from index 1 till found it
        for (int recordIndex = 0; recordIndex < bookingCount; recordIndex++) {

            // check if the record we found match the user ID
            if (bookingId == bookingID[recordIndex]) {

                return recordIndex;
            }
        }
        // if cant find it then return -1, cuz array dont have -1 position
        return -1;
    }


    bool modifyBooking() {

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

            if (modificationSelection < 1 || modificationSelection > 3) {

                cout << "Invalid selection. "
                    << "Please enter 1, 2, or 3." << endl;
            }

        } while (modificationSelection < 1 || modificationSelection > 3);

        if (modificationSelection == 1) {
            modifyBookingCourseId(bookingIndex);
            return  modifyBookingCourseId;
        }
        else if (modificationSelection == 2) {
            modifyBookingDate(bookingIndex);
            return  modifyBookingDate;
        }
        else {
            cout << "No changes were made." << endl;
            return false;
        }


    }



    bool modifyBookingCourseId(int bookingIndex) {


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

        return true;
    }



    bool modifyBookingDate(int bookingIndex) {

        bool validBookingDate;

        do {
            cout << endl;
            cout << "Enter new Booking Date (DD/MM/YYYY): ";
            cin >> bookingDate[bookingIndex];

            validBookingDate = isValidBookingDate(bookingDate[bookingIndex]);

            if (!validBookingDate) {

                cout << "Invalid date format. "
                    << "Please use DD/MM/YYYY." << endl;
            }

        } while (!validBookingDate);


        cout << "Booking Date updated successfully." << endl;

        return true;
    }


    bool cancelBooking() {
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

            return true;
        }
        else {
            cout << "Booking cancellation aborted." << endl;
            return false;
        }

    }

    int main() {

        createBooking();
        modifyBooking();
        modifyBooking();
        menuCdisplay();


        return 0;
    }
