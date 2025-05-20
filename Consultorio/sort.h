#pragma once

#include "data.h"


// GENERIC **QUICKSORT** FOR **DOUBLYLINKEDLIST**
template<typename NodeType, typename Compare, typename SwapFunc>
NodeType* partition(NodeType* low, NodeType* high, Compare comp, SwapFunc swapData) {
    NodeType* pivot = high;
    NodeType* i = low->prev;

    for (NodeType* j = low; j != high; j = j->next) {
        if (comp(j, pivot)) {
			if (i == nullptr)
				i = low;
			else
				i = i->next;

            swapData(i, j);
        }
    }

    if (i == nullptr)
        i = low;
    else
        i = i->next;
    swapData(i, high);
    return i;
}

template<typename NodeType, typename Compare, typename SwapFunc>
void quickSort(NodeType* low, NodeType* high, Compare comp, SwapFunc swapData) {
    if (high != nullptr && low != high && low != high->next) {
        NodeType* p = partition(low, high, comp, swapData);
        if (p == nullptr) return;  // prevent crash
        quickSort(low, p->prev, comp, swapData);
        quickSort(p->next, high, comp, swapData);
    }
}

// GENERIC **HEAP SORT** FOR **DOUBLYLINKEDLIST**







// SEARCH FUNCTIONS FOR PROGRAM
inline void sortByDate() {
    quickSort<AppointmentNode>(
        AppData::Instance().app_list.head,
        AppData::Instance().app_list.tail,
        [](AppointmentNode* a, AppointmentNode* b) {
            return dateStrToIntTuple(a->date) < dateStrToIntTuple(b->date);
        },
        AppData::Instance().app_list.swapData
    );
}

inline void sortUsers() {
    quickSort<UserNode>(
        AppData::Instance().user_list.head,
        AppData::Instance().user_list.tail,
        [](UserNode* a, UserNode* b) {
            return a->id < b->id;
        },
        AppData::Instance().user_list.swapData
    );
}

inline void sortMedics() {
    quickSort<MedicNode>(
        AppData::Instance().medic_list.head,
        AppData::Instance().medic_list.tail,
        [](MedicNode* a, MedicNode* b) {
            return a->fname < b->fname;
        },
        AppData::Instance().medic_list.swapData
    );
}
