#pragma once

#include "utils.h"

class AppointmentNode {
public:
    std::string id;
    std::string date;
    std::string hour;
    std::string spec;
    std::string roomid;
    std::string medicid;
    std::string patientid;
    std::string status;
    std::string diagnosis;
    std::string userid;

    AppointmentNode* next;
    AppointmentNode* prev;

    AppointmentNode(const std::string& id,
        const std::string& date,
        const std::string& hour,
        const std::string& spec,
        const std::string& roomid,
        const std::string& medicid,
        const std::string& patientid,
        const std::string& status,
        const std::string& diagnosis,
        const std::string& userid)
        : id(id), date(date), hour(hour), spec(spec), roomid(roomid),
        medicid(medicid), patientid(patientid), status(status),
        diagnosis(diagnosis), userid(userid), next(nullptr), prev(nullptr) {
    }
};

class AppointmentList {
public:
    AppointmentNode* head;
    AppointmentNode* tail;

    AppointmentList() : head(nullptr), tail(nullptr) {}

    void append(AppointmentNode* newNode) {
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
        AppointmentNode* current = head;
        while (current) {
            AppointmentNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addAppointment(const std::string& id,
        const std::string& date,
        const std::string& hour,
        const std::string& spec,
        const std::string& roomid,
        const std::string& medicid,
        const std::string& patientid,
        const std::string& status,
        const std::string& diagnosis,
        const std::string& userid) {
        AppointmentNode* newNode = new AppointmentNode(id, date, hour, spec, roomid,
            medicid, patientid, status,
            diagnosis, userid);
        append(newNode);
        saveToFile();
    }

    bool updateAppointmentById(const std::string& id,
        const std::string& newDate,
        const std::string& newHour,
        const std::string& newSpec,
        const std::string& newRoomid,
        const std::string& newMedicid,
        const std::string& newPatientid,
        const std::string& newStatus,
        const std::string& newDiagnosis,
        const std::string& newUserid) {
        AppointmentNode* current = head;
        while (current) {
            if (current->id == id) {
                current->date = newDate;
                current->hour = newHour;
                current->spec = newSpec;
                current->roomid = newRoomid;
                current->medicid = newMedicid;
                current->patientid = newPatientid;
                current->status = newStatus;
                current->diagnosis = newDiagnosis;
                current->userid = newUserid;
                saveToFile();
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool removeAppointmentById(const std::string& id) {
        AppointmentNode* current = head;
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
   
    // SEARCH
    std::vector<std::string> getAppointmentsByMedic(const std::string& medicid) const {
        std::vector<std::string> ids;
        AppointmentNode* current = head;
        while (current) {
            if (current->medicid == medicid &&
                current->status == "DISPONIBLE") {
                ids.push_back(current->hour);
            }
            current = current->next;
        }
        return ids;
    }

    std::vector<std::string> getAppointmentsByPatient(const std::string& patientid) const {
        std::vector<std::string> ids;
        AppointmentNode* current = head;
        while (current) {
            if (current->patientid == patientid &&
                current->status == "RESERVADA") {
                ids.push_back(current->id);
            }
            current = current->next;
        }
        return ids;
    }

    AppointmentNode* getAppointmentPtr(const std::string medicid,
        const std::string date, const std::string hour 
    ) {
        AppointmentNode* result(nullptr);
        AppointmentNode* current = head;
        while (current) {
            if (current->medicid == medicid &&
                current->date == date &&
                current->hour == hour
                ) {
                result = current;
                return result;
            }
            current = current->next;
        }
        return result; // not found
    }

    AppointmentNode* getAppointmentById(const std::string aptid){
        AppointmentNode* result(nullptr);
        AppointmentNode* current = head;
        while (current) {
            if (current->id == aptid) {
                result = current;
                return result;
            }
            current = current->next;
        }
        return result; // not found
    }
    
    std::vector<AppointmentNode*> getAppointmentsByDates(
        const std::string& medicid,
        const std::string& date1,
        const std::string& date2
    ) const {

        std::vector<AppointmentNode*> ids;
        std::tuple<int, int, int> date_current, d1, d2;

        d1 = dateStrToIntTuple(date1);
        d2 = dateStrToIntTuple(date2);

        AppointmentNode* current = head;
        while (current) {
            date_current = dateStrToIntTuple(current->date);
            if (current->medicid == medicid &&
                current->status != "DISPONIBLE" &&
                date_current >= d1 &&
                date_current <= d2
                ) {
                ids.push_back(current);
            }
            current = current->next;
        }
        return ids;
    }

    // I/O BINARY FILES
    void saveToFile() const {
        const std::string& filename = "database/appointments.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        AppointmentNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->date);
            writeString(outFile, current->hour);
            writeString(outFile, current->spec);
            writeString(outFile, current->roomid);
            writeString(outFile, current->medicid);
            writeString(outFile, current->patientid);
            writeString(outFile, current->status);
            writeString(outFile, current->diagnosis);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }
    
    void loadFromFile() {
        const std::string& filename = "database/appointments.bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        clear();

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string date = readString(inFile);
            std::string hour = readString(inFile);
            std::string spec = readString(inFile);
            std::string roomid = readString(inFile);
            std::string medicid = readString(inFile);
            std::string patientid = readString(inFile);
            std::string status = readString(inFile);
            std::string diagnosis = readString(inFile);
            std::string userid = readString(inFile);

            AppointmentNode* newNode = new AppointmentNode(id, date, hour, spec, roomid,
                medicid, patientid, status,
                diagnosis, userid);
            append(newNode);
        }

        inFile.close();
    }


    //DEBUG
    void printList() const {
        AppointmentNode* current = head;
        while (current) {
            std::ofstream log("log.txt", std::ios::app);
            log << "ID: " << current->id << "\n";
            current = current->next;
        }
    }

};
