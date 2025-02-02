/*Hospital Management System with Scheduling and Billing*/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <unistd.h> 
#include<bits/stdc++.h>
using namespace std;
class Person {
protected:
    string id;
    string name;
public:
    Person()
    {
        id = "unknown";
        name = "unknown";
    }

    Person(string person_id, string person_name)
    {
        id = person_id;
        name = person_name;
    }

    virtual void displayInfo() const
    {
        cout << "ID: " << id << ", Name: " << name << endl;
    }

    string getName() const 
    {
        return name;
    }

    string getId() const
    {
        return id;
    }
};

class Doctor : public Person 
{
protected:
    string specialization;
    double consultationFee;

public:
    Doctor(string doctor_id, string doctor_name, string doctor_specialization, double fee)
        : Person(doctor_id, doctor_name) {
        specialization = doctor_specialization;
        consultationFee = fee;
    }

    void displayInfo() const override 
    {
        cout << "Doctor Details::" << endl;
        Person::displayInfo();
        cout << "Specialization: " << specialization << endl;
        cout << fixed << setprecision(2) << " Consultation Fee: $" << consultationFee << endl;
    }

    string getSpecialization() const
    {
        return specialization;
    }

    double getConsultationFee() const
    {
        return consultationFee;
    }
};

class Patient : public Person 
{
protected:
    int age;
    double weight;
    double height;
    string ailment;
    string chronicDisease;
    bool visitedBefore;
    string phone_number;
    string address;

public:
    Patient(string patient_id, string patient_name, string patient_ailment,
            int patient_age, double patient_weight, double patient_height,
            string chronic_disease = "", bool visited_before = false, string pn = "", string add = "")
        : Person(patient_id, patient_name) {
        ailment = patient_ailment;
        age = patient_age;
        weight = patient_weight;
        height = patient_height;
        chronicDisease = chronic_disease;
        visitedBefore = visited_before;
        phone_number = pn;
        address = add;
    }

    double calculateBMI() const {
        return weight / (height * height);
    }

    string getAilment() const {
        return ailment;
    } 

    bool hasVisitedBefore() const {
        return visitedBefore;
    }

    void displayInfo() const override {
        cout << "Patient Details::" << endl;
        Person::displayInfo();
        cout << "Ailment: " << ailment << endl;
        cout << "Age: " << age << endl;
        cout << "Weight: " << weight << "kg," << endl;
        cout << "Height: " << height << "m\n";
        cout << "BMI: " << calculateBMI() << endl;
        cout << "Chronic Disease: " << (chronicDisease.empty() ? "None" : chronicDisease) << endl;
        cout << "Visited Before: " << (visitedBefore ? "Yes" : "No") << endl;
    }
};

class Appointment {
public:
    Doctor* doctor; 
    Patient* patient; 
    string date;
    string time;

    Appointment(Doctor* doc, Patient* pat, string app_date, string app_time) {
        doctor = doc;
        patient = pat;
        date = app_date;
        time = app_time;
    }

    void displayInfo() const {
        cout << "Appointment Date: " << date << ", Time: " << time << endl;
        cout << "Doctor: " << doctor->getName() << ", Specialization: " << doctor->getSpecialization() << endl;
        cout << "Patient: " << patient->getName() << ", Ailment: " << patient->getAilment() << endl;
    }
};
class Billing {
public:
    Patient* patient;
    double amount;

    Billing(Patient* pat, double amt) : patient(pat), amount(amt) {}

    void displayBill() const 
    {
        cout << "Billing Information:\n";
        patient->displayInfo();
        cout << "Total Amount Due: $" << amount << endl;
    }
};
class HospitalManagementSystem {
private:
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
     vector<Billing> patientBillings;  
public:
    HospitalManagementSystem()
    {
        doctors.push_back(Doctor("D1", "Dr. KLN Sir", "Cardiology", 100));
        doctors.push_back(Doctor("D2", "Dr. Praveen Ramisetti", "Neurology", 900));
        doctors.push_back(Doctor("D3", "Dr. Charan", "Dermatology", 500));
        doctors.push_back(Doctor("D4", "Dr. Taylor Swift", "Orthopedics", 400));
        doctors.push_back(Doctor("D5", "Dr. Justin Biber", "Gastroenterology", 300));
        doctors.push_back(Doctor("D6", "Dr. Nandini", "Gynecologist", 800));
        doctors.push_back(Doctor("D7", "Dr. Maganti Srinivas Rao", "General", 200));
        doctors.push_back(Doctor("D8", "Dr. Dharma Teja", "Endocrinologist", 300));
        cout << "Doctors initialized successfully.\n";
    }

    void addPatient(string id, string name, string ailment, int age, double weight, double height, string chronicDisease = "", bool visitedBefore = false, string phone_number = "", string address = "") 
    {
        for (auto& patient : patients) 
        {
            if (patient.getId() == id)
            {
                cout << "Error: Patient ID '" << id << "' already exists.\n";
                return;
            }
        }
        patients.push_back(Patient(id, name, ailment, age, weight, height, chronicDisease, visitedBefore, phone_number, address));
        cout << "Patient added successfully.\n";
    }

    void scheduleAppointment(string patient_id, string date, string time) {
        Patient* patient = nullptr;
        Doctor* doctor = nullptr;
        for (auto& p : patients) 
        {
            if (p.getId() == patient_id)
            {
                patient = &p;
                break;
            }
        }
        if (patient == nullptr)
        {
            cout << "Error: Patient ID not found.\n";
            return;
        }
        cout << "Available doctors for ailment '" << patient->getAilment() << "':\n";
        string requiredSpecialization = mapAilmentToSpecialization(patient->getAilment());
        vector<Doctor*> availableDoctors;

        for (auto& doc : doctors)
        {
          if (doc.getSpecialization() == requiredSpecialization) 
            {
                availableDoctors.push_back(&doc);
            }
        }

        if (availableDoctors.empty()) 
        {
           cout << "No specialized doctor available for " << patient->getAilment() << ". Assigning General Physician.\n";
            doctor = &doctors[6]; 
        } 
        else 
        {
            for (auto& doc : availableDoctors) 
            {
                doc->displayInfo();
            }
    cout << "Enter the Doctor ID you want to consult: for fixing appointment";
            string doctor_id;
            cin >> doctor_id;

            for (auto& doc : doctors) 
            {
                if (doc.getId() == doctor_id)
                {
                    doctor = &doc;
                    break;
                }
            }
        }

        if (doctor != nullptr) 
        {
            appointments.push_back(Appointment(doctor, patient, date, time));
            cout << "Appointment scheduled successfully with " << doctor->getName() << ".\n";
        }
        else
        {
            cout << "Error: Doctor ID not found.\n";
        }
    }

    void generateBill(string patient_id, double additionalCharges)
    {
        Patient* patient = nullptr;
        try {
            for (auto& p : patients) 
            {
                if (p.getId() == patient_id) 
                {
                    patient = &p;
                    break;
                }
            }

            if (patient == nullptr)
                throw invalid_argument("Patient ID not found.\n");

            double consultationFee = 0;
            for (const auto& appointment : appointments) 
            {
                if (appointment.patient->getId() == patient_id) 
                {
    consultationFee = appointment.doctor->getConsultationFee();
                    break;
                }
            }

            double discount = (patient->hasVisitedBefore()) ? 0.10 * consultationFee : 0.0;
            double totalAmount = consultationFee - discount + additionalCharges;
         Billing bill(patient, totalAmount);
            bill.displayBill();

            // Store the bill in the vector
            patientBillings.push_back(bill);
            cout << "Consultation Fee: $" << consultationFee;
            if (discount > 0)
            {
                cout << " (10% returning patient discount: -$" << discount << ")";
            }
    cout << "\nAdditional Charges(including the test charges and medices::): $" << additionalCharges << "\n";
     cout << "Total Amount: $" << totalAmount << endl;
     cout << "Please pay the payment using any UPI methods." << endl;
    cout << "Redirecting to payment...." << endl;
        sleep(5);
        cout << "Payment  of" <<totalAmount <<"Successful" << endl;
        
        }
        catch (const invalid_argument& e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
    void displayAppointments() const
    {
        if (appointments.empty()) 
        {
            cout << "No appointments scheduled.\n";
        } 
        else 
        {
            for (const auto& app : appointments)
            {
                app.displayInfo();
            }
        }
    }

    void displayDoctors() const 
    {
        for (const auto& doc : doctors)
        {
            doc.displayInfo();
        }
    }

    void displayPatients() const
    {
        for (const auto& patient : patients)
        {
            patient.displayInfo();
        }
    }
private:
    string mapAilmentToSpecialization(const string& ailment) 
    {
        if (ailment == "Heart Problem")
        {
            return "Cardiology";
        } 
        else if (ailment == "Skin Issue") 
        {
            return "Dermatology";
        }
        else if (ailment == "Stomach Pain") 
        {
            return "Gastroenterology";
        }
        else if (ailment == "Pregnancy") 
        {
            return "Gynecologist";
        }
        else if (ailment == "Headache")
        {
            return "Neurology";
        }
        else 
        {
            return "General"; 
        }
    }
    public:
    void displayBillingSummary(const string& patient_id) const
    {
        bool found = false;
        for (const auto& bill : patientBillings) 
        {
            if (bill.patient->getId() == patient_id)
            {
                cout << "Billing Summary for Patient ID " << patient_id << ":\n";
                bill.displayBill();
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Error: Billing information not found for Patient ID " << patient_id << ".\n";
        }
    }
};
bool isValidPhoneNumber(const string& phone)
{
    if (phone.length() != 10) return false;
    if (phone[0] == '0') return false;
    for (char digit : phone) 
    {
        if (!isdigit(digit)) return false;
    }
    return true;
}
int main() {
    HospitalManagementSystem hms;
    int choice;
    string id, name, ailment, date, time;
    double additionalCharges;
    int age;
    double weight;
    double height;
    string chronicDisease;
    bool visitedBefore;
    string phone_number;
    string address;
   cout << "WELCOME TO SRMAP MULTI-SPECIALITY HOSPITAL ☤🏥!" << endl;
    do {
        cout << "\n===============================\n";
        cout << " Hospital Management System  \n";
        cout << "===============================\n";
        cout << "1. Add Patient\n";
        cout << "2. Schedule Appointment\n";
        cout << "3. Display Appointments\n";
        cout << "4. Display Doctors\n";
        cout << "5. Display Patients\n";
        cout << "6. Generate Bill\n";
        cout << "7. Show Billing Summary\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Patient Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Patient Ailment: ";
                getline(cin, ailment);
                cout << "Enter Patient Age: ";
                cin >> age;
                cout << "Enter Patient Weight (kg): ";
                cin >> weight;
                cout << "Enter Patient Height (m): ";
                cin >> height;
                cout << "Enter any Chronic Disease (or 'None'): ";
                cin.ignore();
                getline(cin, chronicDisease);
                chronicDisease = (chronicDisease == "None") ? "" : chronicDisease;
                cout << "Is this a returning patient? (1 for Yes, 0 for No): ";
                cin >> visitedBefore;
     do 
    {
        cout << "Enter Patient Phone number: ";
        cin >> phone_number;
        if (!isValidPhoneNumber(phone_number))
        {
            cout << "Invalid phone number. Please try again.\n";
        }
    } 
    while (!isValidPhoneNumber(phone_number));
                cout << "Enter the Patient Living Address: ";
                cin.ignore();
                getline(cin, address);

 hms.addPatient(id, name, ailment, age, weight, height, chronicDisease, visitedBefore, phone_number, address);
                break;
            case 2:
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Appointment Date (DD-MM-YYYY): ";
                cin >> date;
                cout << "Enter Appointment Time (HH:MM): ";
                cin >> time;
                hms.scheduleAppointment(id, date, time);
                break;
            case 3:
                hms.displayAppointments();
                break;
            case 4:
                hms.displayDoctors();
                break;
            case 5:
                hms.displayPatients();
                break;
            case 6:
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Additional Charges: ";
                cin >> additionalCharges;
                hms.generateBill(id, additionalCharges);
                break;
                case 7:
         cout << "Show Display Summary!\n";
          hms.displayBillingSummary(id);
                break;
            case 8:
         cout << "Exiting Hospital Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    while (choice != 8);
    return 0;
}