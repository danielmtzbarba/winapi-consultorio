#pragma once

#include "utils.h"


class PatientNode {
public:
	std::string id;
	std::string fname;
	std::string lname1;
	std::string lname2;
	std::string email;
	std::string phone;
    std::string gender;
    std::string age;
	std::string userid;

	PatientNode* next;
	PatientNode* prev;

	PatientNode(const std::string& id,
		const std::string& fname,
		const std::string& lname1,
		const std::string& lname2,
		const std::string& email,
		const std::string& phone,
		const std::string& gender,
        const std::string& age,
		const std::string& userid)
		: id(id), fname(fname), lname1(lname1), lname2(lname2),
		email(email), phone(phone), gender(gender), age(age), userid(userid),
		next(nullptr), prev(nullptr) {
	}
};

class PatientList {
public:
    PatientNode* head;
    PatientNode* tail;

    PatientList() : head(nullptr), tail(nullptr) {}

    void append(PatientNode* newNode) {
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void clear() {
        PatientNode* current = head;
        while (current) {
            PatientNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addPatient(const std::string& id,
        const std::string& fname,
        const std::string& lname1,
        const std::string& lname2,
        const std::string& email,
        const std::string& phone,
        const std::string& gender,
        const std::string& age,
        const std::string& userid) {
        PatientNode* newNode = new PatientNode(id, fname, lname1, lname2, email, phone, gender, age, userid);
        append(newNode);
        saveToFile();
    }

    bool updatePatientById(const std::string& id,
        const std::string& newFname,
        const std::string& newLname1,
        const std::string& newLname2,
        const std::string& newEmail,
        const std::string& newPhone,
        const std::string& newGender,
        const std::string& newAge,
        const std::string& newUserid) {
        PatientNode* current = head;
        while (current) {
            if (current->id == id) {
                current->fname = newFname;
                current->lname1 = newLname1;
                current->lname2 = newLname2;
                current->email = newEmail;
                current->phone = newPhone;
                current->gender = newGender;
                current->age = newAge;
                current->userid = newUserid;
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool removePatientById(const std::string& id) {
        PatientNode* current = head;
        while (current) {
            if (current->id == id) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;

                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;

                delete current;
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    void saveToFile() const {
        const std::string& filename = "database/patients.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        PatientNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->fname);
            writeString(outFile, current->lname1);
            writeString(outFile, current->lname2);
            writeString(outFile, current->email);
            writeString(outFile, current->phone);
            writeString(outFile, current->gender);
            writeString(outFile, current->age);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "database/patients.bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        clear(); // make sure list is empty

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string fname = readString(inFile);
            std::string lname1 = readString(inFile);
            std::string lname2 = readString(inFile);
            std::string email = readString(inFile);
            std::string phone = readString(inFile);
            std::string gender = readString(inFile);
            std::string age = readString(inFile);
            std::string userid = readString(inFile);

            PatientNode* newNode = new PatientNode(id, fname, lname1, lname2, email, phone, gender, age, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<PatientNode*> extractToVector() {
        std::vector<PatientNode*> nodes;
        PatientNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }

    void printList() const {
        PatientNode* current = head;
        while (current) {
            std::ofstream log("log.txt", std::ios::app);
            log << "ID: " << current->id << ", Name: "
                << current->fname << " " << current->lname1 << " " << current->lname2
                << ", Email: " << current->email
                << ", Phone: " << current->phone << "\n";
            current = current->next;
        }
    }
};
