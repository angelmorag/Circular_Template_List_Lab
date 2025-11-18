//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_LINKEDLIST_H
#define CIRCULARTEMPLATEDLIST_LINKEDLIST_H

#include "Media.h"
#include <iostream>

template<typename T>
struct Node {
	T* data;      // Pointer to the data of type T
	Node<T>* next; // Pointer to the next node in the list

	Node(T* obj) : data(obj), next(nullptr) {}
};

// === 5. Hard-coded LinkedList Class (Singly, Circular) ===
template<typename T>
class LinkedList {
private:
    Node<T>* head;
	Node<T>* tail;
	Node<T>* current; // Pointer for playNext functionality

public:
    // Constructor: Initializes an empty list
    LinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Destructor: Cleans up all nodes and the Media objects they point to.
    ~LinkedList() {
        if (!head) return;

        Node<T>* temp = head;
        Node<T>* next_node = nullptr;

        do {
            next_node = temp->next;
            delete temp->data; // Delete the Media object
            delete temp;       // Delete the node itself
            temp = next_node;
        } while (temp != head);

        head = tail = current = nullptr;
        std::cout << "\n[Playlist cleanup complete. All memory deallocated.]" << std::endl;
    }

	// Insert at end: Maintains circular nature of the list.
    void insert(T* newData) {
        Node<T>* newNode = new Node<T>(newData);

        if (!head) {
			head = tail = newNode;
			newNode->next = head; // Circular link
        } else {
            // Case 2: Traverse to the end and link the new node.
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // Maintain circular link
        }

        if (!current) {
            current = head; // Initialize current if it's the first node
		}
    }

    // Traversal: Displays all media items in the list.
    void displayList() const {
        if (!head) {
            std::cout << "\n[Playlist is empty.]" << std::endl;
            return;
        }

        std::cout << "\n--- Current Playlist ---" << std::endl;
        Node<T>* temp = head;
        int index = 1;
        do {
            std::cout << index++ << ". " << temp->data->toString() << std::endl;
            temp = temp->next;
        } while (temp != head);
        std::cout << "------------------------" << std::endl;
    }
    // Simple play method for demonstration (students will expand this later)
    void playCurrent() const {
        if (current) {
            current->data->play(); // Calls the virtual play() method
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }

    void playNext() {
        if (!current) return;

        current = current->next; // Move to the next node
        current->data->play();   // Play the current media
    }
};

#endif //CIRCULARTEMPLATEDLIST_LINKEDLIST_H