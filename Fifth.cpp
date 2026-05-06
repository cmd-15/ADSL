#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Employee{
    public:
        int id;
        char name[20];
        char designation[20];
        float salary;

        void readData(){
            cout << "Enter the Employee name: ";
            cin >> name;

            cout << "Enter the Id: ";
            cin >> id;

            cout << "Enter the Designation: ";
            cin >> designation;

            cout << "Enter the salary: ";
            cin >> salary;
        }

        void printData(){
            cout << id << "\t";
            cout << name << "\t";
            cout << designation << "\t";
            cout << salary << "\t" << endl;
        }
};

void addEmployee(){
    Employee E;


    fstream out;
    out.open("employee.txt", ios::app | ios::binary);
    E.readData();
    out.write((char *)&E, sizeof(E));
    out.close();
    cout << "record Added successfully\n";
}

void DisplayEm(){
    Employee E;

    fstream in;
    in.open("employee.txt", ios::in | ios::binary);

    while(in.read((char*)&E, sizeof(E))){
        E.printData();
    }
    cout << endl;
    in.close();
}

void search(char* name){
    Employee E;
    fstream in;
    int found = 0;

    in.open("employee.txt", ios::in | ios::binary);

    while(in.read((char*)&E, sizeof(E))){
        if(strcmp(E.name,name)==0){
            cout << "record found";
            E.printData();
            found = 1;
        }
    }
    
    if(found==0){
    cout << "\nRecord not found";
    }

    in.close();
}

void UpdateEm(char* key, char* Newname){
    Employee E;
    fstream inout;

    inout.open("employee.txt", ios::in | ios::out | ios::binary);

    while(inout.read((char*)&E,sizeof(E))){
        if(strcmp(E.name,key)==0){
            strcpy(E.name, Newname);

            inout.seekp(-sizeof(E), ios::cur);
            inout.write((char *)&E, sizeof(E));

            cout << "Record Updated Successfully\n";
            inout.close();
            return;
         }
     }
    cout << "no name found to update";
    inout.close();
}

void deleteEm(char* name){
    Employee E;
    fstream in;
    in.open("employee.txt", ios::in | ios::binary);
    fstream out;
    out.open("temp.txt", ios::out | ios::binary);   

    while(in.read((char*)&E,sizeof(E))){
    if(strcmp(E.name,name)!=0){
        out.write((char *)&E, sizeof(E));
    }
  }
  in.close();
  out.close();
  remove("employee.txt");
  rename("temp.txt","employee.txt");
}

int main(){

    ofstream clearfile("employee.txt", ios::trunc);
    clearfile.close();

    Employee E;
    char name[20];
    char key[20];
    char Newname[20];

    int choice;

    do{
        cout << "File Operations Menu\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee Details\n";
        cout << "3. Search Employee Details\n";
        cout << "4. Update Employee name\n";
        cout << "5. Delete Employee Details\n";
        cout << "6. Exit\n";

        cout << "enter the choice: ";
        cin>> choice;

        switch (choice){
            case 1:
                addEmployee();
                break;

            case 2:
                DisplayEm();
                break;

            case 3:
                cout << "enter the employee you want to search: ";
                cin >> name;
                search(name);
                break;
            
            case 4:
                cout << "Enter the Employee you want to update: ";
                cin >> key;

                cout << "Enter the New Employee: ";
                cin >> Newname;

                UpdateEm(key,Newname);
                break;

            case 5:
                cout << "Enter the detail you want to delete: ";
                cin >> name;
                deleteEm(name);
                break;

            case 6:
                cout << "Exiting....";
                break;

            default:
                cout << "invalid choice\n";

        }
    } while (choice != 6);
    return 0;
}

