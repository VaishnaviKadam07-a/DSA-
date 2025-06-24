#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Employee {
public:
    int id;
    string name, designation;
    float salary;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Designation: ";
        getline(cin, designation);
        cout << "Enter Salary: ";
        cin >> salary;
    }

    void display() const {
        cout << "ID: " << id << "\nName: " << name
             << "\nDesignation: " << designation << "\nSalary: " << salary << endl;
    }

    int getID() const {
        return id;
    }
};

// Add new employee (sorted insert)
void addEmployee() {
    vector<Employee> list;
    Employee e;
    e.input();

    ifstream fin("employee.dat", ios::binary);
    Employee temp;

    // Read all existing employees
    while (fin.read((char*)&temp, sizeof(temp))) {
        if (temp.getID() != -1)
            list.push_back(temp);
    }
    fin.close();

    // Add new and sort
    list.push_back(e);
    sort(list.begin(), list.end(), [](Employee a, Employee b) {
        return a.getID() < b.getID();
    });

    // Write back
    ofstream fout("employee.dat", ios::binary | ios::trunc);
    for (auto &emp : list) {
        fout.write((char*)&emp, sizeof(emp));
    }
    fout.close();

    cout << "Employee added successfully.\n";
}

// Search using index sequential method
void searchEmployee(int id) {
    ifstream fin("employee.dat", ios::binary);
    Employee e;
    bool found = false;

    while (fin.read((char*)&e, sizeof(e))) {
        if (e.getID() == id) {
            cout << "Employee Found:\n";
            e.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Employee with ID " << id << " not found.\n";

    fin.close();
}

// Delete (logical deletion)
void deleteEmployee(int id) {
    fstream file("employee.dat", ios::in | ios::out | ios::binary);
    Employee e;
    bool found = false;

    while (file.read((char*)&e, sizeof(e))) {
        if (e.getID() == id) {
            int pos = file.tellg() - sizeof(e);
            e.id = -1;  // mark as deleted
            file.seekp(pos);
            file.write((char*)&e, sizeof(e));
            found = true;
            break;
        }
    }

    file.close();

    if (found)
        cout << "Employee deleted (logically).\n";
    else
        cout << "Employee not found.\n";
}

int main() {
    int choice, empID;

    do {
        cout << "\n=== Employee Management System ===\n";
        cout << "1. Add Employee\n2. Delete Employee\n3. Search Employee\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2:
                cout << "Enter Employee ID to delete: ";
                cin >> empID;
                deleteEmployee(empID);
                break;
            case 3:
                cout << "Enter Employee ID to search: ";
                cin >> empID;
                searchEmployee(empID);
                break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

