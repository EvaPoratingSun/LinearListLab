#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList();
    LinkedList(const std::vector<int>& numbers);
    ~LinkedList();
    
    void addElement(int value);
    void deleteElement(int value);
    void printList() const;
    Node* findNode(int c) const;
    std::pair<LinkedList, LinkedList> splitList(int c) const;
};

#endif
