// ============================================================
//                 STUDENT D - REPORTING MODULE
//                  TUITION CENTRE SYSTEM
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// FUNCTION PROTOTYPES
void ReportingMenu();
void generateSummaryReport();
void generateDetailedReport();
void calculateStatistics();
void sortRecords();
void displayAnalysis();

// REPORTING MENU
void ReportingMenu()
{
    int choice;

    do
    {
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

        switch (choice)
        {
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
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingStatus[i] == "Active")
        {
            activeBookings++;
        }
        else if (bookingStatus[i] == "Cancelled")
        {
            cancelledBookings++;
        }
    }


    // Calculate total course fee
    for (int i = 0; i < courseCount; i++)
    {
        totalFee += CourseFee[i];
    }


    // Calculate average course fee
    if (courseCount > 0)
    {
        averageFee = totalFee / courseCount;
    }

    // Display summary report
    cout << "\n";
    cout << "==================================================\n";
    cout << "                 SUMMARY REPORT\n";
    cout << "==================================================\n";

    cout << left;
    cout << setw(25) << "Total Students"
        << ": " << studentCount << endl;

    cout << setw(25) << "Total Courses"
        << ": " << courseCount << endl;

    cout << setw(25) << "Total Bookings"
        << ": " << bookingCount << endl;

    cout << setw(25) << "Active Bookings"
        << ": " << activeBookings << endl;

    cout << setw(25) << "Cancelled Bookings"
        << ": " << cancelledBookings << endl;

    cout << setw(25) << "Average Course Fee"
        << ": RM "
        << fixed << setprecision(2)
        << averageFee << endl;

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
    if (bookingCount == 0)
    {
        cout << "No booking records available.\n";
        cout << "============================================================\n";
        return;
    }


    // Process each booking
    for (int i = 0; i < bookingCount; i++)
    {
        string studentName = "Unknown";
        string courseName = "Unknown";
        string subject = "Unknown";

        double courseFee = 0.0;

        // ----------------------------------------------------
        // Search for student's name
        // ----------------------------------------------------

        for (int j = 0; j < studentCount; j++)
        {
            if (StuID[j] == bookingStudentID[i])
            {
                studentName = StuName[j];
                break;
            }
        }

        // ----------------------------------------------------
        // Search for course information
        // ----------------------------------------------------

        for (int j = 0; j < courseCount; j++)
        {
            if (CourseID[j] == bookingCourseID[i])
            {
                courseName = CourseName[j];
                subject = Subject[j];
                courseFee = CourseFee[j];

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
        cout << "Course Name  : " << courseName << endl;
        cout << "Subject      : " << subject << endl;

        cout << "Course Fee   : RM "
            << fixed << setprecision(2)
            << courseFee << endl;

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

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingStatus[i] == "Active")
        {
            activeBookings++;
        }
        else if (bookingStatus[i] == "Cancelled")
        {
            cancelledBookings++;
        }
    }


    // --------------------------------------------------------
    // Calculate course fee statistics
    // --------------------------------------------------------

    if (courseCount > 0)
    {
        highestFee = CourseFee[0];
        lowestFee = CourseFee[0];


        for (int i = 0; i < courseCount; i++)
        {
            totalFee += CourseFee[i];


            if (CourseFee[i] > highestFee)
            {
                highestFee = CourseFee[i];
            }


            if (CourseFee[i] < lowestFee)
            {
                lowestFee = CourseFee[i];
            }
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

    cout << "Total Students       : "
        << studentCount << endl;

    cout << "Total Courses        : "
        << courseCount << endl;

    cout << "Total Bookings       : "
        << bookingCount << endl;

    cout << "Active Bookings      : "
        << activeBookings << endl;

    cout << "Cancelled Bookings   : "
        << cancelledBookings << endl;


    if (courseCount > 0)
    {
        cout << fixed << setprecision(2);

        cout << "Highest Course Fee   : RM "
            << highestFee << endl;

        cout << "Lowest Course Fee    : RM "
            << lowestFee << endl;

        cout << "Average Course Fee   : RM "
            << averageFee << endl;
    }
    else
    {
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
    if (courseCount == 0)
    {
        cout << "\nNo course records available.\n";
        return;
    }

    // --------------------------------------------------------
    // Selection Sort
    // Sort Course Fee from Lowest to Highest
    // --------------------------------------------------------

    for (int i = 0; i < courseCount - 1; i++)
    {
        int minIndex = i;


        for (int j = i + 1; j < courseCount; j++)
        {
            if (CourseFee[j] < CourseFee[minIndex])
            {
                minIndex = j;
            }
        }


        // Swap course information
        if (minIndex != i)
        {
            swap(CourseID[i],
                CourseID[minIndex]);

            swap(CourseName[i],
                CourseName[minIndex]);

            swap(Subject[i],
                Subject[minIndex]);

            swap(CourseFee[i],
                CourseFee[minIndex]);
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


    for (int i = 0; i < courseCount; i++)
    {
        cout << left
            << setw(12) << CourseID[i]
            << setw(25) << CourseName[i]
            << setw(20) << Subject[i]
            << "RM "
            << fixed << setprecision(2)
            << CourseFee[i]
            << endl;
    }


    cout << "============================================================\n";
}
// ============================================================
// 5. DISPLAY ANALYSIS
// ============================================================

void displayAnalysis()
{
    if (courseCount == 0)
    {
        cout << "\nNo course data available for analysis.\n";
        return;
    }


    // --------------------------------------------------------
    // Find most expensive and cheapest course
    // --------------------------------------------------------

    int highestIndex = 0;
    int lowestIndex = 0;


    for (int i = 1; i < courseCount; i++)
    {
        if (CourseFee[i] > CourseFee[highestIndex])
        {
            highestIndex = i;
        }


        if (CourseFee[i] < CourseFee[lowestIndex])
        {
            lowestIndex = i;
        }
    }


    // --------------------------------------------------------
    // Count booking status
    // --------------------------------------------------------

    int activeBookings = 0;
    int cancelledBookings = 0;


    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingStatus[i] == "Active")
        {
            activeBookings++;
        }
        else if (bookingStatus[i] == "Cancelled")
        {
            cancelledBookings++;
        }
    }


    // --------------------------------------------------------
    // Calculate active booking rate
    // --------------------------------------------------------

    double activeRate = 0.0;


    if (bookingCount > 0)
    {
        activeRate =
            (double)activeBookings / bookingCount * 100;
    }


    // --------------------------------------------------------
    // Display analysis
    // --------------------------------------------------------

    cout << "\n";
    cout << "==================================================\n";
    cout << "                 CENTRE ANALYSIS\n";
    cout << "==================================================\n";


    cout << "\n[Course Fee Analysis]\n";

    cout << "Most Expensive Course : "
        << CourseName[highestIndex] << endl;

    cout << "Course ID             : "
        << CourseID[highestIndex] << endl;

    cout << "Fee                   : RM "
        << fixed << setprecision(2)
        << CourseFee[highestIndex] << endl;


    cout << "\nCheapest Course       : "
        << CourseName[lowestIndex] << endl;

    cout << "Course ID             : "
        << CourseID[lowestIndex] << endl;

    cout << "Fee                   : RM "
        << fixed << setprecision(2)
        << CourseFee[lowestIndex] << endl;


    cout << "\n[Booking Analysis]\n";

    cout << "Active Bookings       : "
        << activeBookings << endl;

    cout << "Cancelled Bookings    : "
        << cancelledBookings << endl;

    cout << "Active Booking Rate   : "
        << fixed << setprecision(2)
        << activeRate << "%" << endl;


    cout << "==================================================\n";
}
