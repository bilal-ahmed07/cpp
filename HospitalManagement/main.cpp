#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

class Patient {
private:
    int id;
    string name;
    string contact;
    string dob;
    double totalBill;
    double paidAmount;

public:
    Patient(int i, string n, string c, string d) : 
        id(i), name(n), contact(c), dob(d), paidAmount(0) {
        totalBill = 1000 + (rand() % 9001);  // Random bill between 1000 and 10000
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getContact() const { return contact; }
    string getDob() const { return dob; }
    double getTotalBill() const { return totalBill; }
    double getPaidAmount() const { return paidAmount; }
    double getDueAmount() const { return totalBill - paidAmount; }
    
    void makePayment(double amount) {
        paidAmount += amount;
    }
};

class HospitalManagement {
private:
    vector<Patient> patients;
    int nextId;

public:
    HospitalManagement() : nextId(1) {
        srand(time(0));
    }

    void addPatient() {
        string name, contact, dob;

        cout << "\nEnter Patient Details\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Contact Number: ";
        getline(cin, contact);
        cout << "Date of Birth (DD/MM/YYYY): ";
        getline(cin, dob);

        Patient newPatient(nextId, name, contact, dob);
        patients.push_back(newPatient);
        cout << "Patient added successfully! ID: " << nextId << "\n";
        cout << "Total Bill Generated: " << newPatient.getTotalBill() << "\n";
        nextId++;
    }

    void searchPatient() {
        int searchId;
        cout << "Enter Patient ID to search: ";
        cin >> searchId;

        for (const Patient& p : patients) {
            if (p.getId() == searchId) {
                displayPatientDetails(p);
                return;
            }
        }
        cout << "Patient not found!\n";
    }

    void makePayment() {
        int searchId;
        double amount;
        
        cout << "Enter Patient ID: ";
        cin >> searchId;
        
        for (Patient& p : patients) {
            if (p.getId() == searchId) {
                cout << "Current due amount: " << p.getDueAmount() << endl;
                cout << "Enter payment amount: ";
                cin >> amount;
                
                if (amount <= p.getDueAmount()) {
                    p.makePayment(amount);
                    cout << "Payment processed successfully!\n";
                } else {
                    cout << "Error: Payment amount exceeds due amount!\n";
                }
                return;
            }
        }
        cout << "Patient not found!\n";
    }

    void displayAllPatients() {
        if (patients.empty()) {
            cout << "No patients registered!\n";
            return;
        }

        cout << "\nPatient List:\n";
        cout << "ID\tName\tContact\t\tDOB\t\tTotal Bill\tPaid\n";
        
        for (const Patient& patient : patients) {
            cout << patient.getId() << "\t"
                 << patient.getName() << "\t"
                 << patient.getContact() << "\t"
                 << patient.getDob() << "\t"
                 << patient.getTotalBill() << "\t\t"
                 << patient.getPaidAmount() << "\n";
        }
    }

    void displayPatientDetails(const Patient& patient) {
        cout << "\nPatient Details:\n";
        cout << "ID: " << patient.getId() << endl;
        cout << "Name: " << patient.getName() << endl;
        cout << "Contact: " << patient.getContact() << endl;
        cout << "DOB: " << patient.getDob() << endl;
        cout << "Total Bill: " << patient.getTotalBill() << endl;
        cout << "Paid Amount: " << patient.getPaidAmount() << endl;
        cout << "Due Amount: " << patient.getDueAmount() << endl;
    }
};

int main() {
    HospitalManagement hospital;
    int choice;

    while (true) {
        cout << "\nHospital Management System\n";
        cout << "1. Add New Patient\n";
        cout << "2. Search Patient\n";
        cout << "3. Make Payment\n";
        cout << "4. Display All Patients\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hospital.addPatient();
                break;
            case 2:
                hospital.searchPatient();
                break;
            case 3:
                hospital.makePayment();
                break;
            case 4:
                hospital.displayAllPatients();
                break;
            case 5:
                cout << "Thank you for using Hospital Management System!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}