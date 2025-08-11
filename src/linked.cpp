#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    // Constructor
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

Node* insert_beginning(Node* head, int data) {
    // Create a pointer, that allocates data to the heap.
    // The object needs to persist beyond the function scope.
    Node* node = new Node(data);

    // Set the next pointer of the node to the current head.
    node->next = head;
    
    // Move the head to point to the new node.
    head = node;

    // Return node, so we can inspect it further.
    return node;
}

// Here we are passing a copy of a pointer, not the real list.
// The modification won't reflect on the outside. The fix is to pass the address
// of the pointer with reference with Node*& head

// Other fix would be to return the updated head and assign it in main.
void insert_back(Node* head, int data) {
    // Create new node
    Node* node = new Node(data);

    // Check if list is empty. If list is empty, the new node is now the head.
    if (head == nullptr) {
        head = node;
    }

    // and if not, traverse the list until last node is reached.
    while (head->next != nullptr) {
        head = head->next;
    }

    // cout << "DEBUG - Last node was: " << head->data << endl;
    
    // Link the new node by setting the last node's next pointer to the new node.
    head->next = node;
    
    // cout << "DEBUG - Inserted (head->data): " << head->data << endl;
}

void insert_position(Node* head, int data, int position) {

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

    // Otherwise, traverse the list starting from head.
    // Stop just before the desired position.
    for (int i = 0; i < position - 1; i++) {
        head = head->next;
    }

    // cout << "The current node that we want to alter is at: " << head->data << endl;
    // cout << "The next node is at: " << head->next->data << endl;

    // Insert new node at the position
    node->next = head->next; // Point the new node's next to the next node of current
    // cout << "The data after the new node is: " << node->next->data << endl;

    head->next = node; // Update previous node's next to the new node
    // cout << "The data in the next node of previous is: " << head->next->data << endl;

    return;

}

Node* delete_beginning(Node* head) {
    // Return null if list is empty
    if (head == nullptr) {
        return nullptr;
    }

    // Store the current head to a temporary node
    Node* temp = head;

    // Move the head pointer to the next node
    head = head->next;

    // Remove the temporary variable from memory
    delete temp;

    // Return the new head
    return head;

}

Node* delete_back(Node* head) {
    // Check if list is empty
    if (head == nullptr) {
        return nullptr;
    }

    // Check if there is only one node in the list
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }

    // Traverse the list to find the second last node
    Node* second_last = head; // *create another "temp" node*
    while (second_last->next->next != nullptr) {
        second_last = second_last->next;
    }

    // Delete the last node and set the next from the second last to null
    delete second_last->next;
    second_last->next = nullptr;

    return head;
}

Node* delete_position(Node* head, int position) {
    if (head == nullptr) {
        return head;
    }

    // Delete the head and return it
    if (position == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    // Traverse to the node before the position
    int listLength = length_of_list(head);
    Node* temporary = head;
    for (int i = 0; i < position - 1; i++) {
        if (position > listLength) {
            cout << "Cannot delete a node outside the bounds of the list" << endl;
            return head;
        }

        temporary = temporary->next;

    }

    temporary->next = temporary->next->next;
    delete temporary;

    return head;

}

bool find_node(Node* head, int data) {
    // Start from the head of the linked list
    
    // Repeat until the end null is reached
    while (head != nullptr) {
        // Check each node's data
        if (head->data == data) {
            // cout << "Data found, returning true." << endl;
            return true;
        } else {
            head = head->next;
            // cout << "Moving to the next node." << endl;
        }
    }

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

    // Print the current list starting from the head.
    cout << "Initial list: ";
    traverse(head);
    cout << endl;

    // Print length
    cout << "The length of the initial list: " << length_of_list(head) << endl;
    cout << endl;

    // Insert front
    cout << "Inserting 0 to front: " << endl;
    head = insert_beginning(head, 0);
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
    int search = 100;
    bool result = find_node(head, search);
    if (result) {
        cout << "The searched data " << search << " was found!" << endl;
    } else {
        cout << "The searched data " << search << " was not found." << endl;
    }

    cout << endl;

    // Delete front
    cout << "Deleting front: " << endl;
    head = delete_beginning(head);
    traverse(head);
    cout << endl;

    // Delete back
    cout << "Deleting back: " << endl;
    head = delete_back(head);
    traverse(head);
    cout << endl;

    // Delete at given position
    cout << "Delete at position 4: " << endl;
    head = delete_position(head, 4);
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

    return 0;
}