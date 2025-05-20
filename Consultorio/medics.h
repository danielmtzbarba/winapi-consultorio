#pragma once

#include "utils.h"


class MedicNode {
public:
	std::string id;
	std::string fname;
	std::string lname1;
	std::string lname2;
	std::string email;
	std::string phone;
	std::string spec;
	std::string userid;

	MedicNode* next;
	MedicNode* prev;

	MedicNode(const std::string& id,
		const std::string& fname,
		const std::string& lname1,
		const std::string& lname2,
		const std::string& email,
		const std::string& phone,
		const std::string& spec,
		const std::string& userid)
		: id(id), fname(fname), lname1(lname1), lname2(lname2),
		email(email), phone(phone), spec(spec), userid(userid),
		next(nullptr), prev(nullptr) {
	}
};

class MedicList {
public:
    MedicNode* head;
    MedicNode* tail;

    MedicList() : head(nullptr), tail(nullptr) {}

    void append(MedicNode* newNode) {
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
        MedicNode* current = head;
        while (current) {
            MedicNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addMedic(const std::string& id,
        const std::string& fname,
        const std::string& lname1,
        const std::string& lname2,
        const std::string& email,
        const std::string& phone,
        const std::string& spec,
        const std::string& userid) {
        MedicNode* newNode = new MedicNode(id, fname, lname1, lname2, email, phone, spec, userid);
        if (isDuplicate(id)) {
            return;
        }
        append(newNode);
        saveToFile();
        return;
    }

    bool isDuplicate(const std::string& id) {
        MedicNode* current = head;
        while (current) {
            if (current->id == id) {
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool updateMedicById(const std::string& id,
        const std::string& newFname,
        const std::string& newLname1,
        const std::string& newLname2,
        const std::string& newEmail,
        const std::string& newPhone,
        const std::string& newSpec,
        const std::string& newUserid) {
        MedicNode* current = head;
        while (current) {
            if (current->id == id) {
                current->fname = newFname;
                current->lname1 = newLname1;
                current->lname2 = newLname2;
                current->email = newEmail;
                current->phone = newPhone;
                current->spec = newSpec;
                current->userid = newUserid;
                saveToFile();
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }
    
    std::string getMedicNameById(const std::string id) {
        std::string name;
        MedicNode* current = head;
        while (current) {
            if (current->id == id) {
                name = current->lname1 + " " + current->lname2 + " " + current->fname;
                return name;
            }
            current = current->next;
        }
        return name; // not found
    }

    std::vector<std::string> getMedicIdsBySpec(const std::string& spec) const {
        std::vector<std::string> ids;
        MedicNode* current = head;
        while (current) {
            if (current->spec == spec) {
                ids.push_back(current->id);
            }
            current = current->next;
        }
        return ids;
    }

    bool removeMedicById(const std::string& id) {
        MedicNode* current = head;
        while (current) {
            if (current->id == id) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;

                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;

                delete current;
                saveToFile();
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    void saveToFile() const {
        const std::string& filename = "database/medics.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        MedicNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->fname);
            writeString(outFile, current->lname1);
            writeString(outFile, current->lname2);
            writeString(outFile, current->email);
            writeString(outFile, current->phone);
            writeString(outFile, current->spec);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "database/medics.bin";
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
            std::string spec = readString(inFile);
            std::string userid = readString(inFile);

            MedicNode* newNode = new MedicNode(id, fname, lname1, lname2, email, phone, spec, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<MedicNode*> toVector() {
        std::vector<MedicNode*> nodes;
        MedicNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }

    static void swapData(MedicNode* a, MedicNode* b) {
        std::swap(a->id, b->id);
        std::swap(a->fname, b->fname);
        std::swap(a->lname1, b->lname1);
        std::swap(a->lname2, b->lname2);
        std::swap(a->email, b->email);
        std::swap(a->phone, b->phone);
        std::swap(a->spec, b->spec);
        std::swap(a->userid, b->userid);
    }
};
