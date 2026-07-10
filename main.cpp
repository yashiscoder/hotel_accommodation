#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>

using namespace std;

const char* HOST = "localhost";
const char* USER ="root";
const char* PW =" ";
const char* DB = "mydb";

class Hostel{
    private:
    string Name;
    int Bed, Fees;
    public:
    Hostel(string name, int bed, int fees){
        Name = name;
        Bed = bed;
        Fees = fees;
    }
}
int main(){
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)){
        cout<<"Error: "<<mysql_error(conn)<<endl;
    }
    else{
        cout<<"Connection success."<<endl;
    }
    Sleep(3000)

    return 0;
}
