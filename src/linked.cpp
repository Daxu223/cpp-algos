#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }

};

int length_of_list(Node* head) {
    int counter = 0;
    Node* current = head;
    while (current != nullptr) {
        counter++;
        current = current->next;
    }

    return counter;
}

// Return void because the changes are from the original address of head.
void insert_beginning(Node*& head, int data) {
    // Create a pointer, that allocates data to the heap.
    // The object needs to persist beyond the function scope.
    Node* node = new Node(data);

    // Set the next pointer of the node to the current head.
    node->next = head;
    
    // Replace the original head with the new node that was just created.
    head = node;
}

void insert_back(Node*& head, int data) {

    // Check if list is empty
    if (head == nullptr) {
        head = new Node(data); // Creates a new head pointer 
        return;
    }

    // and if not, traverse the list until last node is reached.
    Node* current = head; // Make a temporary traversal node, so that the real head is not replaced.
    while (current->next != nullptr) {
        current = current->next;
    }

    // cout << "DEBUG - Last node was: " << current->data << endl;
    
    // At this point, we point the new node to after the last item in the linked list.
    // We can now discard the copy of the pointer and the contents in memory are still changed.
    current->next = new Node(data);
    
    // cout << "DEBUG - Inserted ([last item]->data): " << current->data << endl;
    return;

}

void insert_position(Node*& head, int data, int position) {

    // Check if insertion is possible before
    int listLength = length_of_list(head);
    if (position > listLength) {
        cout << "Insertion not possible because position exceeds list length." << endl;
        return;
    }

    // Create a new node
    Node* node = new Node(data);

    // Normal insertion at beginning.
    if (position == 0) {
        node->next = head;
        head = node;
        return;
    }

    // Create a copy pointer from head: original linked list must not change during traversal.
    Node* current = head;


    // Otherwise, traverse the list starting from head.
    // Stop just before the desired position.
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    // cout << "The current node that we want to alter is at: " << current->data << endl;
    // cout << "The next node is at: " << current->next->data << endl;

    // Insert new node at the position
    node->next = current->next; // Point the new node's next to the next node of current
    // cout << "The data after the new node is: " << node->next->data << endl;

    current->next = node; // Update previous node's next to the new node
    // cout << "The data in the next node of previous is: " << current->next->data << endl;

    return;

}

void delete_beginning(Node*& head) {
    if (head == nullptr) {
        return;
    }

    // Store the current head to a temporary node
    Node* current = head;

    // Move the head pointer to the next node
    head = current->next;

    // Remove the temporary variable from memory
    delete current;

    return;
}

void delete_back(Node*& head) {
    if (head == nullptr) {
        return;
    }

    // Check if there is only one node in the list
    if (head->next == nullptr) {
        delete head;
        return;
    }

    // Traverse the list to find the second last node
    Node* second_last = head;
    while (second_last->next->next != nullptr) {
        second_last = second_last->next;
    }

    // Delete the last node and set the next from the second last to null
    delete second_last->next;
    second_last->next = nullptr;

    return;
}

void delete_position(Node*& head, int position) {
    if (head == nullptr) {
        return;
    }

    // If first position, delete the head and make the next one the head.
    if (position == 0) {
        Node* currentHead = head;
        head = head->next;
        delete currentHead;
        return;
    }

    // Check if the deletion is valid.
    int listLength = length_of_list(head);
    if (position > listLength) {
        cout << "Cannot delete a node outside the bounds of the list" << endl;
        return;
    }
    
    // Traverse to the node before the desired position to delete.
    Node* current = head; // Temporary traversal pointer
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    // cout << "Node before the desired position: " << current->data << endl;

    // Save node because current->next is not accessible after reassigning (see below)
    Node* nodeToDelete = current->next;

    // "Skip" the next of the deletable item to point to the the next item in list.
    current->next = nodeToDelete->next;

    delete nodeToDelete; // Delete the skipped item.

    return;

}

bool find_node(Node* head, int data) {
    // Start from the head of the linked list
    
    // Repeat until the end null is reached
    while (head != nullptr) {
        // Check each node's data
        if (head->data == data) {
            cout << "Data " << data << " found, returning true." << endl;
            return true;
        } else {
            head = head->next;
            // cout << "Moving to the next node." << endl;
        }
    }

    cout << "Data " << data << " was not found, returning false" << endl;
    return false;
}

void modify(Node* head, int data, int position) {
    int listLength = length_of_list(head);
    
    if (position < 0 || position >= listLength) {
        cout << "Position out of bounds." << endl;
        return;
    }
    
    // Make a copy of the head, so that we don't directly change the head in between operations.
    Node* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    current->data = data;
}

void traverse(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }

    cout << endl;
}

void reverse(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // New head is the last node.
    head = prev;
}

void free_list(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next; 
        delete temp;
    }

    cout << "Nodes freed." << endl;
    return;
}

int main() {
    // TODO: allocating new nodes but these are never freed when the program ends.
    // TODO: Make the functions handle the original addresses of the pointers, not copies (&*Node)
    // TODO: Test edge cases like empty lists and out of bounds positions.

    // Initialize list
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
    head->next->next->next->next = new Node(50);

    // Print length
    cout << "The length of the initial list: " << length_of_list(head) << endl;

    // Print the current list starting from the head.
    cout << "Initial list: ";
    traverse(head);
    cout << endl;

    // Insert front
    cout << "Inserting 0 to front: " << endl;
    insert_beginning(head, 0);
    traverse(head);
    cout << endl;

    // Insert back
    cout << "Inserting 60 to back: " << endl;
    insert_back(head, 60);
    traverse(head);
    cout << endl;
    
    // Insert at position
    // Note: Position 0 is the first.
    cout << "Inserting 100 at position 4: " << endl;
    insert_position(head, 100, 4);
    traverse(head);
    cout << endl;

    // Search the linked list and try to find a node.
    cout << "Searching data: " << endl;
    int search = 100;
    bool result = find_node(head, search);
    cout << endl;

    // Delete front
    cout << "Deleting front: " << endl;
    delete_beginning(head);
    traverse(head);
    cout << endl;

    // Delete back
    cout << "Deleting back: " << endl;
    delete_back(head);
    traverse(head);
    cout << endl;

    // Delete at given position
    cout << "Delete at position 4: " << endl;
    delete_position(head, 4);
    traverse(head);
    cout << endl;

    // Modify a single value at a given position
    cout << "Modify at position 3: " << endl;
    modify(head, 123, 3);
    traverse(head);
    cout << endl;

    // Lastly, reverse a linked list.
    cout << "Reversing the linked list: " << endl;
    reverse(head);
    traverse(head);
    cout << endl;

    
    // Check if the list was deleted
    cout << "Free list from existing with head = " << head->data << endl;
    free_list(head);

    return 0;
}