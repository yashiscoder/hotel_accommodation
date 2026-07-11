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
    string getName(){
        return Name;
    }
    int getBed(){
        return Bed;
    }
    int getFees(){
        return Fees;
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

    Hotel h("Project Hostel", 10, 10000);

    int intB = h.getBed();
    stringstream ss;
    ss<<intB;
    string strB = ss.str();

    int intF = h.getFees();
    stringstream as;
    as<<intF;
    string strf = as.str();
    string insert = "INSERT INTO hostel (Name, Bed, Fees) VALUES ('"+h.getName()+"', '"+strB+"','"+strF"')";
    if(mysql_query(conn, insert.c_str())){
        cout<<"Error: "<<mysql_error(conn)<<endl;
    }
    else{
        cout<<"Data Inserted"<<endl;
    }

    bool exit = false;

    while(!exit){
        system("cls");
        cout<<"Welcome to Project Hostel Management"<<endl;
        cout<<" "<<endl;
        cout<<"1. Reserve Bed: "<<end;
        cout<<"2. Exit: "<<endl;
        cout<<"Enter Your Choice: ";
        int val;
        cin>>val;

        if(val==1){
            string n;
            cout<<"Enter Student name: ";
            cin>>n;
            int total;
            string check = "SELECT Bed FROM hostel Name = '"h.getName()"'";
            if(mysql_query(conn, check.c_str())){
                cout<<"Error: "<<mysql_error(conn)<<endl;
            }
            else{
                MYSQL_RES* res;
                res = mysql_store_reslut(conn);
                if (res){
                    MYSQL_ROW row = mysql_fetch_row(res);
                    if(row){
                        total = atoi(row[0]);
                    }
                }
            }
            if(total > 0){
                total--;
                stringstream zs;
                zs<<total;
                string strT = zs.str();

                string update = "UPDATE hostel SET BED = '"+strT+"', WHERE Name ='"+h.getName()+"'";
            }
        }
    }
    return 0;
}
