#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name, division, address;

    void input() {
        cout << "Enter Roll Number: ";
        while (!(cin >> roll)) {
            cout << "Invalid input! Enter a number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(); // Clear newline

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Division: ";
        getline(cin, division);

        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() {
        cout << "Roll No: " << roll << "\nName: " << name
             << "\nDivision: " << division << "\nAddress: " << address << "\n";
    }

    int getRoll() {
        return roll;
    }
};

void addStudent() {
    ofstream fout("students.txt", ios::app);
    if (!fout) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    Student s;
    s.input();
    fout << s.roll << "\n" << s.name << "\n" << s.division << "\n" << s.address << "\n";
    fout.close();
    cout << "Record added successfully.\n";
}

void displayStudent(int rno) {
    ifstream fin("students.txt");
    if (!fin) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    Student s;
    bool found = false;

    while (fin >> s.roll) {
        fin.ignore(); // Ignore newline
        getline(fin, s.name);
        getline(fin, s.division);
        getline(fin, s.address);

        if (s.getRoll() == rno) {
            cout << "Record Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    fin.close();

    if (!found)
        cout << "Record not found.\n";
}

void deleteStudent(int rno) {
    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    if (!fin || !temp) {
        cerr << "Error opening file.\n";
        return;
    }

    Student s;
    bool found = false;

    while (fin >> s.roll) {
        fin.ignore();
        getline(fin, s.name);
        getline(fin, s.division);
        getline(fin, s.address);

        if (s.getRoll() == rno) {
            found = true;
        } else {
            temp << s.roll << "\n" << s.name << "\n" << s.division << "\n" << s.address << "\n";
        }
    }

    fin.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

int main() {
    int choice, rollno;

    do {
        cout << "\n*** Student Information System ***\n";
        cout << "1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll No to delete: ";
                cin >> rollno;
                deleteStudent(rollno);
                break;
            case 3:
                cout << "Enter Roll No to display: ";
                cin >> rollno;
                displayStudent(rollno);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                cin.clear();
                cin.ignore(1000, '\n');
        }
    } while (choice != 4);

    return 0;
}