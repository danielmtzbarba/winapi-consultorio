#pragma once
#include "data.h"
#include "sort.h"

// GENERIC **BINARY SEARCH** FOR A VECTOR OF NODEPOINTERS**
template<typename NodeType, typename KeyType, typename Compare, typename Extractor>
std::vector<NodeType*> binarySearchNodes(
    const std::vector<NodeType*>& sortedList,
    const KeyType& target,
    Compare comp,
    Extractor extract
) {
    std::vector<NodeType*> result;

    int left = 0;
    int right = static_cast<int>(sortedList.size()) - 1;
    int foundIndex = -1;

    // Binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        KeyType midVal = extract(sortedList[mid]);

        if (!comp(midVal, target) && !comp(target, midVal)) {
            foundIndex = mid;
            break;
        }
        else if (comp(midVal, target)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (foundIndex == -1) return result;

    // Expand left
    int i = foundIndex;
    while (i >= 0 && !comp(extract(sortedList[i]), target) && !comp(target, extract(sortedList[i]))) {
        result.push_back(sortedList[i]);
        i--;
    }

    // Expand right
    i = foundIndex + 1;
    while (i < sortedList.size() && !comp(extract(sortedList[i]), target) && !comp(target, extract(sortedList[i]))) {
        result.push_back(sortedList[i]);
        i++;
    }

    return result;
}

// SEARCHES

// SEARCH USER FOR LOGIN
inline bool userLogin(std::string userid, std::string pass) {
    //SORT
    sortUsers();

    // SEARCH
    auto found = binarySearchNodes<UserNode, std::string>(
        AppData::Instance().user_list.toVector(),                   // Vector of sorted AppointmentNode*
        userid,                                   // Target name
        std::less<>(),                        // Default string comparator
        [](UserNode* node) {           // Field extractor
            return node->id;
        }
    );

    if (found.empty()) {
        //USER NOT FOUND
        return false;
    }

    //LOGIN
    if (found[0]->id == userid && found[0]->password == pass)
        return true;

    return false;
}

// SEARCH MEDIC
inline MedicNode* searchMedic(std::string id) {

}

