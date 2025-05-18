#pragma once

#include "utils.h"


class UserNode {
public:
	std::string id;
	std::string fname;
	std::string lname1;
	std::string lname2;
	std::string email;
	std::string password;
	std::string date;

	UserNode* next;
	UserNode* prev;

	UserNode(const std::string& id,
		const std::string& fname,
		const std::string& lname1,
		const std::string& lname2,
		const std::string& email,
		const std::string& password, 
        const std::string& date)
		: id(id), fname(fname), lname1(lname1), lname2(lname2),
		email(email), password(password), date(date),
		next(nullptr), prev(nullptr) {
	}
};

class UserList {
public:
    UserNode* head;
    UserNode* tail;

    UserList() : head(nullptr), tail(nullptr) {}

    void append(UserNode* newNode) {
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
        UserNode* current = head;
        while (current) {
            UserNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addUser(const std::string& id,
        const std::string& fname,
        const std::string& lname1,
        const std::string& lname2,
        const std::string& email,
        const std::string& password,
        const std::string& date) {
        UserNode* newNode = new UserNode(id, fname, lname1, lname2, email, password, date);
        append(newNode);
        saveToFile();
    }

    bool updateUserById(const std::string& id,
        const std::string& newFname,
        const std::string& newLname1,
        const std::string& newLname2,
        const std::string& newEmail,
        const std::string& newPassword,
        const std::string& newDate) {
        UserNode* current = head;
        while (current) {
            if (current->id == id) {
                current->fname = newFname;
                current->lname1 = newLname1;
                current->lname2 = newLname2;
                current->email = newEmail;
                current->password = newPassword;
                current->date = newDate;
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool UserLoginById(const std::string& id, const std::string& password) {
        UserNode* current = head;
        while (current) {
            if (current->id == id && current->password == password) {
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool removeUserById(const std::string& id) {
        UserNode* current = head;
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
        const std::string& filename = "database/users.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        UserNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->fname);
            writeString(outFile, current->lname1);
            writeString(outFile, current->lname2);
            writeString(outFile, current->email);
            writeString(outFile, current->password);
            writeString(outFile, current->date);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "database/users.bin";
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
            std::string password = readString(inFile);
            std::string date = readString(inFile);

            UserNode* newNode = new UserNode(id, fname, lname1, lname2, email, password, date);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<UserNode*> extractToVector() {
        std::vector<UserNode*> nodes;
        UserNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }

    void printList() const {
        UserNode* current = head;
        while (current) {
            std::ofstream log("log.txt", std::ios::app);
            log << "ID: " << current->id << " "
                << current->password << "\n";

            current = current->next;
        }
    }
};
