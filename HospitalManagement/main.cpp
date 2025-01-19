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
        totalBill = 1000 + (rand() % 9001);
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

class Doctor {
private:
    int id;
    string name;
    bool onDuty;

public:
    Doctor(int i, string n) : id(i), name(n), onDuty(false) {}

    int getId() const { return id; }
    string getName() const { return name; }
    bool isOnDuty() const { return onDuty; }
    void setDuty(bool status) { onDuty = status; }
};

class DoctorDutySystem {
private:
    vector<Doctor*> dutyStack;

public:
    void pushDoctor(Doctor* doctor) {
        doctor->setDuty(true);
        dutyStack.push_back(doctor);
    }

    Doctor* popDoctor() {
        if (dutyStack.empty()) return nullptr;
        Doctor* doctor = dutyStack.back();
        doctor->setDuty(false);
        dutyStack.pop_back();
        return doctor;
    }

    Doctor* getCurrentDoctor() {
        return dutyStack.empty() ? nullptr : dutyStack.back();
    }

    bool isEmpty() const {
        return dutyStack.empty();
    }
};

class HospitalManagement {
private:
    vector<Patient*> patients;
    DoctorDutySystem doctorDutySystem;
    vector<Doctor*> doctors;
    int nextPatientId;
    int nextDoctorId;

public:
    HospitalManagement() : nextPatientId(1), nextDoctorId(1) {
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

        Patient* newPatient = new Patient(nextPatientId++, name, contact, dob);
        patients.push_back(newPatient);
        cout << "Patient added successfully! ID: " << newPatient->getId() << endl;
    }

    void addDoctor() {
        string name;
        cout << "Enter Doctor Name: ";
        cin.ignore();
        getline(cin, name);

        Doctor* newDoctor = new Doctor(nextDoctorId++, name);
        doctors.push_back(newDoctor);
        cout << "Doctor added successfully! ID: " << newDoctor->getId() << "\n";
    }

    void manageDoctorDuty() {
        int choice;
        cout << "1. Add doctor to duty\n";
        cout << "2. Remove doctor from duty\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int doctorId;
            cout << "Enter Doctor ID: ";
            cin >> doctorId;
            Doctor* doctor = findDoctor(doctorId);
            if (doctor && !doctor->isOnDuty()) {
                doctorDutySystem.pushDoctor(doctor);
                cout << "Doctor added to duty!\n";
            } else {
                cout << "Invalid doctor ID or doctor already on duty!\n";
            }
        } else if (choice == 2) {
            Doctor* doctor = doctorDutySystem.popDoctor();
            if (doctor) {
                cout << "Doctor " << doctor->getName() << " removed from duty!\n";
            } else {
                cout << "No doctors on duty!\n";
            }
        }
    }

    void makePayment() {
        int patientId;
        double amount;

        cout << "Enter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);
        if (patient) {
            cout << "Current due amount: " << patient->getDueAmount() << endl;
            cout << "Enter payment amount: ";
            cin >> amount;

            if (amount <= patient->getDueAmount()) {
                patient->makePayment(amount);
                cout << "Payment processed successfully!\n";
            } else {
                cout << "Error: Payment amount exceeds due amount!\n";
            }
        } else {
            cout << "Patient not found!\n";
        }
    }

    void displayPatients() {
        if (patients.empty()) {
            cout << "No patients registered!\n";
            return;
        }

        cout << "\nPatient List:\n";
        cout << "ID\tName\tContact\t\tDOB\tTotal Bill\tPaid\n";
        for (const Patient* patient : patients) {
            cout << patient->getId() << "\t"
                 << patient->getName() << "\t"
                 << patient->getContact() << "\t\t"
                 << patient->getDob() << "\t"
                 << patient->getTotalBill() << "\t\t"
                 << patient->getPaidAmount() << "\n";
        }
    }

    Patient* findPatient(int id) {
        for (Patient* p : patients) {
            if (p->getId() == id) return p;
        }
        return nullptr;
    }

    Doctor* findDoctor(int id) {
        for (Doctor* d : doctors) {
            if (d->getId() == id) return d;
        }
        return nullptr;
    }

    void displayMenu() {
        cout << "\nHospital Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Manage Doctor Duty\n";
        cout << "4. Make Payment\n";
        cout << "5. Display All Patients\n";
        cout << "6. Exit\n";
    }
};

int main() {
    HospitalManagement hospital;
    int choice;

    while (true) {
        hospital.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hospital.addPatient();
                break;

            case 2:
                hospital.addDoctor();
                break;

            case 3:
                hospital.manageDoctorDuty();
                break;

            case 4:
                hospital.makePayment();
                break;

            case 5:
                hospital.displayPatients();
                break;

            case 6:
                cout << "Thank you for using Hospital Management System!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
