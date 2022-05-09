
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<windows.h>
#include "sqlite3.h"

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int printResults(void*, int numColumns, char** values, char** columns)
{
    for (int i = 0; i < numColumns; ++i)
        cout << "   " << values[i];
    cout << std::endl;

    return 0;
}

int ShowDb() {
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("employee.db", &DB);
    string data("CALLBACK FUNCTION");

    system("CLS");
    cout << "##########################################################################################################";
    cout << "#########################################################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t   EMPLOYEE DETAILS " << endl;
    cout << "##########################################################################################################";
    cout << "#########################################################################################################\n\n" << endl;

    cout << "\tEmpID " << " Employee  Name   " << "   Email Id    " << "   Mobile no.   " << "  Age  " << "   Address   " << "  Hire date   " << " Designation " << "Basic Salary" <<"   HRA   "<<"    DA    "<<"   Salary  "<<endl;
    cout << "##########################################################################################################";
    cout << "#########################################################################################################" << endl;
    string sql("SELECT * FROM Employee;");
    cout << "\n\n\n";
    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        return (-1);
    }
    int rc = sqlite3_exec(DB, sql.c_str(), &printResults, (void*)data.c_str(), NULL);

    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    //    else {
    //        cout << "Operation OK!" << endl;
    //    }

    sqlite3_close(DB);
}

void InsertDb(int empid, string first_name, string last_name, string email, string mobile_no, int age, string address, string date, string designation,int basic, int hra , int da, int salary)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("employee.db", &DB);
    string query = "SELECT * FROM Employee;";

    /*   cout << "STATE OF TABLE BEFORE INSERT" << endl;

        sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); */
    string sql("INSERT INTO Employee VALUES(null, " + to_string(empid) + " ,'" +     first_name + "','" + last_name + "','" + email + "','" + mobile_no + "'," + to_string(age) + " ,'" + address + "' , '" + date + "' , '" + designation + "' ," + to_string(basic) + "," + to_string(hra) + "," + to_string(da) + "," + to_string(salary) + ")");


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        cerr << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
    {
        system("CLS");
        cout << "Records created Successfully!" << endl;
    }

    sqlite3_close(DB);
}


int CreateTable() {
    sqlite3* DB;
    char* messaggeError;

    string sql = "CREATE TABLE IF NOT EXISTS Employee ("
        "id	INTEGER,"
        "emp_id	INTEGER,"
        "emp_fname	TEXT,"
        "emp_lname	TEXT,"
        "emp_email	TEXT,"
        "emp_mob_no	TEXT,"
        "emp_age	NUMERIC,"
        "emp_address	TEXT,"
        "emp_hire_date	DATE,"
        "emp_designation	TEXT,"
        "emp_basic_sal INTEGER,"
        "emp_hra INTEGER,"
        "emp_da INTEGER,"
        "emp_salary	INTEGER,"
        "PRIMARY KEY(id AUTOINCREMENT));";
    int exit = 0;
    exit = sqlite3_open("employee.db", &DB);
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messaggeError);
    }
    //    else
      //      cout << "Table created Successfully" << std::endl;
    sqlite3_close(DB);
    return 0;
}

void deleteTable(int id) {
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("employee.db", &DB);

    string sql("DELETE FROM Employee WHERE emp_id = " + to_string(id) + ";");


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error DELETE" << std::endl;
        cerr << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        system("CLS");
        cout << "Record deleted Successfully!" << std::endl;
}

void updateTable(int empid, string first_name, string last_name, string email, string mobile_no, int age, string address, string date, string designation, int basic , int hra , int da, int salary)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("employee.db", &DB);

  
    string sql("UPDATE Employee SET emp_fname ='" + first_name + "',emp_lname ='" + last_name + "' ,emp_email ='" + email + "' , emp_mob_no ='" + mobile_no + "', emp_age =" + to_string(age) + ", emp_address ='" + address + "',emp_hire_date ='" + date + "', emp_designation ='" + designation + "', emp_basic_sal ='" + to_string(basic) + "', emp_hra ='" + to_string(hra) + "',emp_da ='" + to_string(da) + "', emp_salary =" + to_string(salary) + " WHERE emp_id = " + to_string(empid) + ";");

   

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error UPDATE" << std::endl;
        cerr << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        system("CLS");
        cout << "Record Updated Successfully!" << std::endl;
}


void truncateTable() {
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("employee.db", &DB);
    string sql("DELETE FROM Employee;");
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error DELETE" << std::endl;
        cerr << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        system("CLS");
        cout << "All Record deleted Successfully!" << std::endl;
}


int main()
{

    int user_input;
    int empid = 0;
    int employee_id = 0;
    string emp_fname;
    string emp_lname;
    string emp_email;
    string emp_mob_no;
    int age;
    string emp_address;
    string emp_hire_date;
    string emp_designation;
    int emp_basic, emp_hra , emp_da , emp_salary;
    string usrn,pswd;
    string username = "admin";
    string password = "pass@123";


start:
    cout << "##########################################################################################################";
    cout << "#########################################################################################################" << endl;
    cout << "                                 \t\t\t\t\t\tWelcome Employee Management System" << endl;
    cout << "##########################################################################################################";
    cout << "#########################################################################################################\n\n\n" << endl;
    cout << "**************************************************************************************************";
    cout<<" LOGIN * ****************************************************************************************************\n\n\n\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t*********************************"<<endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  Enter username: ";
    cin >> usrn;
    cout << "\t\t\t\t\t\t\t\t\t\t  Enter password: ";
    cin >> pswd;
    cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t  loading ........: ";

    if (usrn == username && pswd == password)
    {
        system("CLS");
        CreateTable();
        cout << "##########################################################################################################";
        cout << "#########################################################################################################" << endl;
        cout << "                                 \t\t\t\t\t\tWelcome Employee Management System" << endl;
        cout << "##########################################################################################################";
        cout << "#########################################################################################################\n\n\n" << endl;
        while (1) {
            
        cout << "##########################################################################################################";
        cout << "#########################################################################################################" << endl;
        cout << "Menu:" << endl;
        cout << "       0 - Exit" << endl;
        cout << "       1 - View Employee Table" << endl;
        cout << "       2 - Insert Employee Entry" << endl;
        cout << "       3 - Update Employee Entry" << endl;
        cout << "       4 - Delete Employee Entry" << endl;
        cout << "       5 - Truncate Table" << endl;
        cout << "       6 - View Menu" << endl;
        cout << "##########################################################################################################";
        cout << "#########################################################################################################" << endl;
        
            cout << endl;
            cout << "Enter Your choice Here: ";
            cin >> user_input;
            cout << endl;
            switch (user_input) {
            case 0:
                exit(0);
            case 1:
                ShowDb();
                break;
            case 2:
                system("CLS");
                cout << "Enter Employee Id: ";
                cin >> empid;
                cout << endl;
                cout << "Enter Employee First Name: ";
                cin >> emp_fname;
                cout << endl;
                cout << "Enter Employee Last Name: ";
                cin >> emp_lname;
                cout << endl;
                cout << "Enter Employee Email: ";
                cin >> emp_email;
                cout << endl;
                cout << "Enter Employee Mobile No: ";
                cin >> emp_mob_no;
                cout << endl;
                cout << "Enter Employee age: ";
                cin >> age;
                cout << endl;
                cout << "Enter Employee Address: ";
                cin >> emp_address;
                cout << endl;
                cout << "Enter Employee Hire Date('YYYY-MM-DD'): ";
                cin >> emp_hire_date;
                cout << endl;
                cout << "Enter Employee Designation: ";
                cin >> emp_designation;
                cout << endl;
                cout << "Enter Employee's basic salary: ";
                cin >> emp_basic;
                cout << "Enter Employee's HRA: ";
                cin >> emp_hra;
                cout << "Enter Employee's DA: ";
                cin >> emp_da;

                emp_salary = emp_basic + emp_hra + emp_da;
                cout << endl;
                InsertDb(empid, emp_fname, emp_lname, emp_email, emp_mob_no, age, emp_address, emp_hire_date, emp_designation, emp_basic, emp_hra, emp_da, emp_salary);
                break;
            case 3:
                system("CLS");

                cout << "FOR UPDATE ";
                cout << "Enter Employee Id: ";
                cin >> empid;
                cout << endl;
                cout << "Enter Employee First Name: ";
                cin >> emp_fname;
                cout << endl;
                cout << "Enter Employee Last Name: ";
                cin >> emp_lname;
                cout << endl;
                cout << "Enter Employee Email: ";
                cin >> emp_email;
                cout << endl;
                cout << "Enter Employee Mobile No: ";
                cin >> emp_mob_no;
                cout << endl;
                cout << "Enter Employee age: ";
                cin >> age;
                cout << endl;
                cout << "Enter Employee Address: ";
                cin >> emp_address;
                cout << endl;
                cout << "Enter Employee Hire Date('YYYY-MM-DD'): ";
                cin >> emp_hire_date;
                cout << endl;
                cout << "Enter Employee Designation: ";
                cin >> emp_designation;
                cout << endl;
                cout << "Enter Employee's basic salary: ";
                cin >> emp_basic;
                cout << "Enter Employee's HRA: ";
                cin >> emp_hra;
                cout << "Enter Employee's DA: ";
                cin >> emp_da;

                emp_salary = emp_basic + emp_hra + emp_da;
                cout << endl;
                updateTable(empid, emp_fname, emp_lname, emp_email, emp_mob_no, age, emp_address, emp_hire_date, emp_designation, emp_basic, emp_hra, emp_da, emp_salary);
                break;
            case 4:
                cout << "Enter Employee Id: ";
                cin >> empid;
                cout << endl;
                deleteTable(empid);
                break;
            case 5:
                truncateTable();
                break;
            /*case 6:
                cout << "Menu:" << endl;
                cout << "       0 - Exit" << endl;
                cout << "       1 - View Employee Table" << endl;
                cout << "       2 - Insert Employee Entry" << endl;
                cout << "       3 - Update Employee Entry" << endl;
                cout << "       4 - Delete Employee Entry" << endl;
                cout << "       5 - Truncate Table" << endl;
                cout << "       6 - View Menu" << endl;
                break;
                */
            default:
                system("CLS");
                cout << "\t\t\t\t\t\t\t\t  Enter the correct choice " << endl;
                /*
                cout << "Menu:" << endl;
                cout << "       0 - Exit" << endl;
                cout << "       1 - View Employee Table" << endl;
                cout << "       2 - Insert Employee Entry" << endl;
                cout << "       3 - Update Employee Entry" << endl;
                cout << "       4 - Delete Employee Entry" << endl;
                cout << "       5 - Truncate Table" << endl;
                cout << "       6 - View Menu" << endl;
                // code block
                */
            }
        }

    }
    else if (usrn != username)
    {
    cout << "\t\t\t\t\aInvalid username please try again"<<endl;
    Sleep(3000);
    system("CLS");
    goto start;
    }
    else if (pswd != password)
    {
    cout << "\t\t\t\t\aInvalid password please try again"<<endl;
    Sleep(3000);
    system("CLS");
    goto start;
    }
    else {
    cout << "\t\t\t\t\aInvalid username and password";
    Sleep(3000);
    system("CLS");
    goto start;
    }
    return (0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

