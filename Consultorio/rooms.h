#pragma once

#include "utils.h"

class RoomNode {
public:
    std::string id;
    std::string spec;
    std::string userid;

    RoomNode* next;
    RoomNode* prev;

    RoomNode(const std::string& id,
        const std::string& spec,
        const std::string& userid)
        : id(id), spec(spec), userid(userid),
        next(nullptr), prev(nullptr) {
    }
};

class RoomList {
public:
    RoomNode* head;
    RoomNode* tail;

    RoomList() : head(nullptr), tail(nullptr) {}

    void append(RoomNode* newNode) {
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
        RoomNode* current = head;
        while (current) {
            RoomNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addRoom(const std::string& id,
        const std::string& spec,
        const std::string& userid) {
        RoomNode* newNode = new RoomNode(id, spec, userid);
        if (isDuplicate(id)) {
            return;
        }
        append(newNode);
        saveToFile();
        return;
    }

    bool isDuplicate(const std::string& id) {
        RoomNode* current = head;
        while (current) {
            if (current->id == id) {
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool updateRoomById(const std::string& id,
        const std::string& newSpec,
        const std::string& newUserid) {
        RoomNode* current = head;
        while (current) {
            if (current->id == id) {
                current->spec = newSpec;
                current->userid = newUserid;
                saveToFile();
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool removeRoomById(const std::string& id) {
        RoomNode* current = head;
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
        return false;
    }

    void saveToFile() const {
        const std::string& filename = "database/rooms.bin";
        std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        RoomNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->spec);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "database/rooms.bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        clear();

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string spec = readString(inFile);
            std::string userid = readString(inFile);

            RoomNode* newNode = new RoomNode(id, spec, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<std::string> getRoomIdsBySpec(const std::string& spec) const {
        std::vector<std::string> ids;
        RoomNode* current = head;
        while (current) {
            if (current->spec == spec) {
                ids.push_back(current->id);
            }
            current = current->next;
        }
        return ids;
    }
};
