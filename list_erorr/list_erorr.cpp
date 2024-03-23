#include <iostream>
#include <stdexcept>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void remove(int value) {
        if (!head)
            throw out_of_range("List is empty");

        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    head = head->next;
                    if (head)
                        head->prev = nullptr;
                    else
                        tail = nullptr; 
                }
                else if (current == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
        throw out_of_range("Value not found in the list");
    }
};

int main() {
    try {
        DoublyLinkedList list;
        list.append(1);
        list.append(2);
        list.append(3);
        list.remove(2);
        list.remove(3);
        list.remove(1);
        list.remove(0); // має бути виняток
    }
    catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << std::endl;
    }
    return 0;
}

