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
template<typename NodeType, typename Compare, typename SwapFunc>
void heapify(NodeType* arr[], int n, int i, Compare comp, SwapFunc swapData) {
    int largest = i;      // Assume root is largest
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2;// Right child

    if (left < n && comp(arr[largest], arr[left]))
        largest = left;

    if (right < n && comp(arr[largest], arr[right]))
        largest = right;

    if (largest != i) {
        swapData(arr[i], arr[largest]);
        heapify(arr, n, largest, comp, swapData);
    }
}

template<typename NodeType, typename Compare, typename SwapFunc>
void heapSort(NodeType* head, NodeType* tail, Compare comp, SwapFunc swapData) {
    // Convert linked list to array of pointers
    std::vector<NodeType*> nodes;
    for (NodeType* curr = head; curr != nullptr; curr = curr->next) {
        nodes.push_back(curr);
    }

    int n = nodes.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nodes.data(), n, i, comp, swapData);
    }

    // Extract elements from heap
    for (int i = n - 1; i >= 0; i--) {
        swapData(nodes[0], nodes[i]);
        heapify(nodes.data(), i, 0, comp, swapData);
    }
}

// SEARCH FUNCTIONS FOR PROGRAM

// QUICKSORT
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
// HEAPSORT
inline void sortAppointmentsByDateHeap() {
    heapSort<AppointmentNode>(
        AppData::Instance().app_list.head,
        AppData::Instance().app_list.tail,
        [](AppointmentNode* a, AppointmentNode* b) {
            return dateStrToIntTuple(a->date) < dateStrToIntTuple(b->date);
        },
        AppData::Instance().app_list.swapData
    );
}

inline void sortAppointmentsByDateHeap() {
    heapSort<AppointmentNode>(
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
