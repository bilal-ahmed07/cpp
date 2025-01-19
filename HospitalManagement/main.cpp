#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;


class Patient;
class Department;
class Doctor;


struct HistoryNode {
    string date;
    string treatment;
    HistoryNode* next;
    
    HistoryNode(string d, string t) : date(d), treatment(t), next(nullptr) {}
};


class Patient {
private:
    int id;
    string name;
    string contact;
    string dob;
    double totalBill;
    double paidAmount;
    int emergencyLevel; 
    HistoryNode* historyHead;
    
public:
    Patient(int i, string n, string c, string d, int e = 1) : 
        id(i), name(n), contact(c), dob(d), paidAmount(0), emergencyLevel(e), historyHead(nullptr) {
        totalBill = 1000 + (rand() % 9001);
    }
    
    int getId() const { return id; }
    string getName() const { return name; }
    string getContact() const { return contact; }
    string getDob() const { return dob; }
    int getEmergencyLevel() const { return emergencyLevel; }
    double getTotalBill() const { return totalBill; }
    double getPaidAmount() const { return paidAmount; }
    double getDueAmount() const { return totalBill - paidAmount; }
    
    void addHistory(string date, string treatment) {
        HistoryNode* newNode = new HistoryNode(date, treatment);
        newNode->next = historyHead;
        historyHead = newNode;
    }
    
    void displayHistory() {
        HistoryNode* current = historyHead;
        cout << "\nMedical History for " << name << ":\n";
        while (current != nullptr) {
            cout << "Date: " << current->date << " - Treatment: " << current->treatment << endl;
            current = current->next;
        }
    }
    
    void makePayment(double amount) {
        paidAmount += amount;
    }
};

class Department {
private:
    string name;
    vector<Department*> connectedDepts;
    vector<int> distances;
    
public:
    Department(string n) : name(n) {}
    
    void addConnection(Department* dept, int distance) {
        connectedDepts.push_back(dept);
        distances.push_back(distance);
    }
    
    string getName() const { return name; }
    vector<Department*> getConnections() const { return connectedDepts; }
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


class EmergencyQueue {
private:
    vector<Patient*> heap;
    
    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap[parent]->getEmergencyLevel() < heap[index]->getEmergencyLevel()) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }
    
    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < heap.size() && 
            heap[left]->getEmergencyLevel() > heap[largest]->getEmergencyLevel())
            largest = left;
            
        if (right < heap.size() && 
            heap[right]->getEmergencyLevel() > heap[largest]->getEmergencyLevel())
            largest = right;
            
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }
    
public:
    void addPatient(Patient* patient) {
        heap.push_back(patient);
        heapifyUp(heap.size() - 1);
    }
    
    Patient* getNextEmergencyPatient() {
        if (heap.empty()) return nullptr;
        
        Patient* patient = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
            
        return patient;
    }

    bool isEmpty() const {
        return heap.empty();
    }
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
    vector<Department*> departments;
    EmergencyQueue emergencyQueue;
    DoctorDutySystem doctorDutySystem;
    vector<Doctor*> doctors;
    int nextPatientId;
    int nextDoctorId;

public:
    HospitalManagement() : nextPatientId(1), nextDoctorId(1) {
        srand(time(0));
        initializeDepartments();
    }
    
    void initializeDepartments() {
        Department* emergency = new Department("Emergency");
        Department* surgery = new Department("Surgery");
        Department* icu = new Department("ICU");
        Department* general = new Department("General");
        
        emergency->addConnection(icu, 1);
        emergency->addConnection(surgery, 2);
        icu->addConnection(surgery, 1);
        general->addConnection(emergency, 3);
        
        departments.push_back(emergency);
        departments.push_back(surgery);
        departments.push_back(icu);
        departments.push_back(general);
    }

    void addPatient(bool isEmergency = false) {
        string name, contact, dob;
        int emergencyLevel = 1;

        cout << "\nEnter Patient Details\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Contact Number: ";
        getline(cin, contact);
        cout << "Date of Birth (DD/MM/YYYY): ";
        getline(cin, dob);
        
        if (isEmergency) {
            cout << "Emergency Level (1-5): ";
            cin >> emergencyLevel;
        }

        Patient* newPatient = new Patient(nextPatientId++, name, contact, dob, emergencyLevel);
        patients.push_back(newPatient);
        
        if (isEmergency) {
            emergencyQueue.addPatient(newPatient);
            cout << "Patient added to emergency queue!\n";
        }
        
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

    void processNextEmergency() {
        if (doctorDutySystem.isEmpty()) {
            cout << "No doctors available on duty!\n";
            return;
        }

        Patient* patient = emergencyQueue.getNextEmergencyPatient();
        if (patient) {
            cout << "Processing emergency patient: " << patient->getName() 
                 << " (Emergency Level: " << patient->getEmergencyLevel() << ")\n";
            cout << "Attending Doctor: " << doctorDutySystem.getCurrentDoctor()->getName() << "\n";
        } else {
            cout << "No emergency patients in queue!\n";
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
        cout << "1. Add Regular Patient\n";
        cout << "2. Add Emergency Patient\n";
        cout << "3. Add Doctor\n";
        cout << "4. Manage Doctor Duty\n";
        cout << "5. Process Next Emergency\n";
        cout << "6. Make Payment\n";
        cout << "7. Display All Patients\n";
        cout << "8. Exit\n";
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
                hospital.addPatient(false);  // Regular patient
                break;
                
            case 2:
                hospital.addPatient(true);   // Emergency patient
                break;
                
            case 3:
                hospital.addDoctor();
                break;
                
            case 4:
                hospital.manageDoctorDuty();
                break;
                
            case 5:
                hospital.processNextEmergency();
                break;
                
            case 6:
                hospital.makePayment();
                break;
                
            case 7:
                hospital.displayPatients();
                break;
                
            case 8:
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