#include "Sequence.h"
#include <cstdlib>
#include <iostream>
#include <exception>

using namespace std;

// Creates an empty sequence (num == 0) or a sequence of num items
// indexed from 0 ... (num). Not num - 1. just num
// I know it SHOULD be num - 1 but when we were making the constructor
// we set it up so that index 0 was num 1. I didn't think to fix that
// before making all the functions that require num, and now I don't know what
// it will break if I do (I assume everything).
Sequence::Sequence(size_t sz) {
    head = nullptr;
    tail = nullptr;
    num = 0;

    if (sz != 0) {
        SequenceNode *newNode = new SequenceNode("0");
        head = newNode;
        tail = newNode;
        num++;
        if (sz > 1) {
            while (num < sz) {
                newNode = new SequenceNode(to_string(num));
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
                num++;
            }
        }
    }
}

// Creates a (deep) copy of sequence s
Sequence::Sequence(const Sequence& s) {
    head = nullptr;
    tail = nullptr;
    num = 0;

    SequenceNode* copier = s.head;

    while (copier) {
        push_back(copier->item);
        copier = copier->next;
    }
}

// Destroys all items in the sequence and release the memory
// associated with the sequence
Sequence::~Sequence() {
    clear();
}

// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;).
Sequence& Sequence::operator=(const Sequence& s) {
    clear();

    SequenceNode* copier = s.head;

    while (copier) {
        push_back(copier->item);
        copier = copier->next;
    }

    return *this;
}

// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence
std::string& Sequence::operator[](size_t position) {
    if (position > num) {
        throw exception();
    }
    SequenceNode *finder = head;
    for (int i = 0; i < position; i++) {
        finder = finder->next;
    }
    return finder->item;
}

// The value of item is appended to the sequence.
void Sequence::push_back(std::string item) {
    if (num == 0) {
        SequenceNode *newNode = new SequenceNode(item);
        head = newNode;
        tail = newNode;
        num++;
        return;
    }
    SequenceNode *newNode = new SequenceNode(item);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    num++;
}

// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    if (num == 0) {
        throw exception();
    }
    SequenceNode* current = tail;
    SequenceNode* toBeTail = current->prev;
    delete current;
    tail = toBeTail;
    tail->next = nullptr;
    num--;
}

// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exception if the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {
    // For when you try to insert out of bounds
    if (position > num) {
        throw exception();
    }
    SequenceNode* inserter = new SequenceNode(item);
    // For when we are inserting at the head
    if (position == 0) {
        // Empty sequence, it is both head and tail
        if (num == 0) {
            head = inserter;
            tail = inserter;
        }
        // Not empty, but it is at the head
        else {
            inserter->next = head;
            head->prev = inserter;
            head = inserter;
        }
    }
    // For when we are inserting at the tail
    else if (position == num) {
            tail->next = inserter;
            inserter->prev = tail;
            tail = inserter;
        }
    // For when we are inserting at literally anywhere else
    else {
        SequenceNode* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        inserter->prev = current->prev;
        inserter->next = current;
        current->prev->next = inserter;
        current->prev = inserter;
    }
    // Increase num by 1
    num++;
}

// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    if (num == 0) {
        throw exception();
    }
    return head->item;
}

// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    if (num == 0) {
        throw exception();
    }
    return tail->item;
}

// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {
    if (num == 0) {
        return true;
    }
    return false;
}

// Return the number of elements in the sequence.
size_t Sequence::size() const {
    return this->num;
}

// All items in the sequence are deleted and the memory associated with the
// sequence is released, resetting the sequence to an empty state that can have
// items re-inserted.
void Sequence::clear() {
    SequenceNode* current = head;
    while (current != nullptr) {
        SequenceNode* toBeDeleted = current->next;
        delete current;
        current = toBeDeleted;
    }
    head = nullptr;
    tail = nullptr;
    num = 0;
}

// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
void Sequence::erase(size_t position) {
    // For when you try to delete out of bounds
    if (position >= num) {
        throw exception();
    }
    SequenceNode* current = head;
    // Move to the position in the list
    for (size_t i = 0; i < position; i++) {
        current = current->next;
    }
    // For when we are deleting the head
    if (position == 0) {
        // For when the head is the only item in the list
        if (num == 1) {
            delete current;
            head = nullptr;
            tail = nullptr;
        }
        // Not empty after deletion, move head forward
        else {
            head = current->next;
            head->prev = nullptr;
            delete current;
        }
    }
    // For when we are deleting the tail
    else if (position == num - 1) {
        tail = current->prev;
        tail->next = nullptr;
        delete current;
    }
    // For when we are deleting literally anywhere else
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
    // Decrease num by 1
    num--;
}

/*
// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
void Sequence::erase(size_t position, size_t count) {

}
*/
// Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
// stream. This is *not* a method of the Sequence class, but instead it is a
// friend function
ostream& operator<<(ostream& os, const Sequence& s) {
    SequenceNode *printer = s.head;
    for (int i = 0; i < s.num; i++) {
        cout << printer->item << " ";
        printer = printer->next;
    }
    return os;
}