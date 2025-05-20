#pragma once
#include "data.h"

inline void swapAppointmentData(AppointmentNode* a, AppointmentNode* b) {
	std::swap(a->id, b->id);
	std::swap(a->date, b->date);
	std::swap(a->hour, b->hour);
	std::swap(a->spec, b->spec);
	std::swap(a->roomid, b->roomid);
	std::swap(a->medicid, b->medicid);
	std::swap(a->patientid, b->patientid);
	std::swap(a->status, b->status);
	std::swap(a->diagnosis, b->diagnosis);
	std::swap(a->userid, b->userid);
}

template<typename NodeType, typename Compare>
NodeType* partition(NodeType* low, NodeType* high, Compare comp) {
    auto pivot = high;
    NodeType* i = low->prev;

    for (NodeType* j = low; j != high; j = j->next) {
        if (comp(j, pivot)) {
			if (i == nullptr)
				i = low;
			else
				i = i->next;
            swapAppointmentData(static_cast<AppointmentNode*>(i), static_cast<AppointmentNode*>(j));
        }
    }

    if (i == nullptr)
        i = low;
    else
        i = i->next;
    swapAppointmentData(static_cast<AppointmentNode*>(i), static_cast<AppointmentNode*>(high));

    return i;
}

template<typename NodeType, typename Compare>
void quickSort(NodeType* low, NodeType* high, Compare comp) {
    if (high != nullptr && low != high && low != high->next) {
        NodeType* p = partition(low, high, comp);
        if (p == nullptr) return;  // prevent crash

        // Log the recursive ranges
        quickSort(low, p->prev, comp);
        quickSort(p->next, high, comp);
    }
}

inline void sortByDate() {
    quickSort(AppData::Instance().app_list.head, AppData::Instance().app_list.tail,
        [](AppointmentNode* a, AppointmentNode* b) {
            return dateStrToIntTuple(a->date) < dateStrToIntTuple(b->date);
        }
    );
}


