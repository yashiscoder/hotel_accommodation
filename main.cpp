#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <sstream>

using namespace std;

// Database Credentials
const char* HOST = "localhost";
const char* USER = "root";
const char* PW   = "";          // Enter your MySQL password here
const char* DB   = "mydb";

// Hostel Class
class Hostel
{
private:
    string Name;
    int Bed;
    int Fees;

public:
    Hostel(string name, int bed, int fees)
    {
        Name = name;
        Bed = bed;
        Fees = fees;
    }

    string getName()
    {
        return Name;
    }

    int getBed()
    {
        return Bed;
    }

    int getFees()
    {
        return Fees;
    }
};

int main()
{
    MYSQL* conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0))
    {
        cout << "Connection Failed!" << endl;
        cout << "Error : " << mysql_error(conn) << endl;
        return 1;
    }

    cout << "Database Connected Successfully!" << endl;

    Sleep(2000);

    Hostel h("Project Hostel", 10, 10000);

    string strBed = to_string(h.getBed());
    string strFees = to_string(h.getFees());

    // Insert Hostel Record
    string insert =
        "INSERT INTO hostel(Name, Bed, Fees) VALUES('" +
        h.getName() + "', '" +
        strBed + "', '" +
        strFees + "')";

    if (mysql_query(conn, insert.c_str()))
    {
        cout << "Insert Error : " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Hostel Added Successfully." << endl;
    }

    Sleep(2000);

    bool Exit = false;

    while (!Exit)
    {
        system("cls");

        cout << "=====================================" << endl;
        cout << "   PROJECT HOSTEL MANAGEMENT SYSTEM" << endl;
        cout << "=====================================" << endl;

        cout << "1. Reserve Bed" << endl;
        cout << "2. Exit" << endl;

        cout << "\nEnter Choice : ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string student;

            cout << "\nEnter Student Name : ";
            cin.ignore();
            getline(cin, student);

            int totalBed = 0;

            string check =
                "SELECT Bed FROM hostel WHERE Name='" +
                h.getName() + "'";

            if (mysql_query(conn, check.c_str()))
            {
                cout << mysql_error(conn) << endl;
                Sleep(3000);
                continue;
            }

            MYSQL_RES* res = mysql_store_result(conn);

            if (res != NULL)
            {
                MYSQL_ROW row = mysql_fetch_row(res);

                if (row != NULL)
                {
                    totalBed = atoi(row[0]);
                }

                mysql_free_result(res);
            }

            if (totalBed > 0)
            {
                totalBed--;

                string strTotal = to_string(totalBed);

                string update =
                    "UPDATE hostel SET Bed='" +
                    strTotal +
                    "' WHERE Name='" +
                    h.getName() + "'";

                if (mysql_query(conn, update.c_str()))
                {
                    cout << mysql_error(conn) << endl;
                }
                else
                {
                    cout << "\nBed Reserved Successfully!" << endl;
                    cout << "Student : " << student << endl;
                    cout << "Hostel  : " << h.getName() << endl;
                    cout << "Fees    : Rs. " << h.getFees() << endl;
                    cout << "Beds Left : " << totalBed << endl;
                }
            }
            else
            {
                cout << "\nSorry! No Beds Available." << endl;
            }

            Sleep(4000);
        }

        else if (choice == 2)
        {
            Exit = true;
            cout << "\nThank You!" << endl;
            Sleep(2000);
        }

        else
        {
            cout << "\nInvalid Choice!" << endl;
            Sleep(2000);
        }
    }

    mysql_close(conn);

    return 0;
}