#include <iostream>
#include <stdexcept>
#include <fstream>
#include <limits>
using namespace std;

//terrible code by Viacrusis, Sean Matthew | TN22

struct Node {
    Node* next;
    int floorlvl;
    int wantFloor;
    bool goingUp; // 0 is down, 1 is up
    Node(int curr, int want, bool goingUp) : next(nullptr), floorlvl(curr), wantFloor(want), goingUp(goingUp) {}
};
int UDF_abs(int value) {
    return value < 0 ? -value : value;
}

class LinkedList {
private:
    Node* ll_head;
    Node* ll_tail;

public:
    LinkedList() : ll_head(nullptr), ll_tail(nullptr) {}

    ~LinkedList() {
        Node* current = ll_head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void pushFront(int curr, int want, bool goingUp) {
        Node* newNode = new Node(curr, want, goingUp);
        newNode->next = ll_head;
        ll_head = newNode;
        if (!ll_tail) ll_tail = newNode;
    }

    void pushBack(int curr, int want, bool goingUp) {
        Node* newNode = new Node(curr, want, goingUp);
        if (!ll_head) {
            ll_head = ll_tail = newNode;
        } else {
            ll_tail->next = newNode;
            ll_tail = newNode;
        }
    }

    Node* popFront() {
        if (!ll_head) return nullptr;
        Node* temp = ll_head;
        ll_head = ll_head->next;
        if (!ll_head) ll_tail = nullptr;
        temp->next = nullptr;
        return temp;
    }

    Node* front() const {
        return ll_head;
    }

    bool isEmpty() const {
        return ll_head == nullptr;
    }
};


//USE LINKED LIST TO MAKE A QUEUE FIFO
class Queue {
private:
    LinkedList ll_Queue;

public:
    void enqueue(int curr, int want, bool goingUp) {
        ll_Queue.pushBack(curr, want, goingUp);
    }

    Node* dequeue() {
        return ll_Queue.popFront();
    }

    Node* front() const {
        return ll_Queue.front();
    }

    bool isEmpty() const {
        return ll_Queue.isEmpty();
    }
};

//USE LINKED LIST TO MAKE A STACK LIFO
class Stack {
private:
    LinkedList ll_Stack;

public:
    void push(int curr, int want, bool goingUp) {
        ll_Stack.pushFront(curr, want, goingUp);
    }

    void pop() {
        delete ll_Stack.popFront();
    }

    Node* top() const {
        return ll_Stack.front();
    }

    bool isEmpty() const {
        return ll_Stack.isEmpty();
    }

    void recordLogs() {
        ofstream MyFile("Elevator Path Logs.txt", ios::app);
        if (!MyFile.is_open()) {
            cerr << "Failed to open file for writing." << endl;
            return;
        }

        Node* current = ll_Stack.front();
        while (current) {
            MyFile << current->floorlvl << " " << (current->goingUp ? "Up" : "Down") << endl;
            current = current->next;
        }
        MyFile.close();
        cout << "Logs recorded." << endl;
    }
};


//Used Priority queue (insertion sort) instead of heap because heap needs a dynamic array while i'm using a linked list o(n)
class PriorityQueue {
private:
    LinkedList ll_Prio;
    bool elevatorDirection;
    int currentFloor;

    // Prioritize requests in current direction, then closest floor
    bool compare(Node* a, Node* b) const {
        // Check if nodes are in the current direction
        bool aInDir = (a->floorlvl >= currentFloor) == elevatorDirection;
        bool bInDir = (b->floorlvl >= currentFloor) == elevatorDirection;

        // prio nodes in same direction
        if (aInDir != bInDir) return aInDir;

        // Within the same direction, sort by proximity
        return elevatorDirection ?
            (a->floorlvl < b->floorlvl) : // Up: ascending order
            (a->floorlvl > b->floorlvl);   // Down: descending order
    }

    void insertSorted(Node* newNode) {
        if (ll_Prio.isEmpty()) {
            ll_Prio.pushBack(newNode->floorlvl, newNode->wantFloor, newNode->goingUp);
            delete newNode;
            return;
        }

        Node dummy(0, 0, false);
        dummy.next = ll_Prio.front();
        Node* prev = &dummy;
        Node* curr = dummy.next;

        while (curr && !compare(newNode, curr)) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = newNode;
        newNode->next = curr;

        ll_Prio.popFront();
        ll_Prio.pushFront(dummy.next->floorlvl, dummy.next->wantFloor, dummy.next->goingUp);
    }

public:
    PriorityQueue() : elevatorDirection(true), currentFloor(1) {}



    Node* front(){
        return ll_Prio.front();
    }
    void setElevatorState(bool direction, int floor) {
        elevatorDirection = direction;
        currentFloor = floor;
    }

    void enqueue(int floor) {
        bool goingUp = (floor > currentFloor); //dynamically change direction
        Node* newNode = new Node(floor, -1, goingUp);
        insertSorted(newNode);
    }
    Node* dequeue() {
        return ll_Prio.popFront();
    }

    bool isEmpty() const {
        return ll_Prio.isEmpty();
    }
    void reSortQueue() {
        LinkedList tempList;
        while (!ll_Prio.isEmpty()) {
            Node* node = ll_Prio.popFront();
            tempList.pushBack(node->floorlvl, node->wantFloor, node->goingUp);
            delete node;
        }
        while (!tempList.isEmpty()) {
            Node* node = tempList.popFront();
            enqueue(node->floorlvl); // Reinsert with updated direction
            delete node;
        }
    }
};
class Elevator {
private:
    Queue Users;
    PriorityQueue Movement;
    Stack Records;
    int currentFloor;
    bool isGoingUp;

public:
    Elevator() : currentFloor(1), isGoingUp(true) {}

    void printRequests() const {
        if (Users.isEmpty()) {
            cout << "No pending requests." << endl;
            return;
        }

        cout << "Elevator is currently at floor " << currentFloor
             << ", going " << (isGoingUp ? "Up" : "Down") << ".\n";
        cout << "+---------------------+\n"
             << "| Floor | Requests    |\n"
             << "+---------------------+\n";

        for (int floor = 9; floor >= 1; --floor) {
            cout << "|  " << floor << "   |"
                 << (floor == currentFloor ? " [E] " : "     ");

            bool hasRequest = false;
            Node* current = Users.front();
            while (current) {
                if (current->floorlvl == floor) {
                    hasRequest = true;
                    break;
                }
                current = current->next;
            }
            cout << (hasRequest ? " [R] " : "     ") << "|\n";
        }
        cout << "+---------------------+" << endl;
    }


    void requestFloor(int currFloor, int wantFloor) {
        // Add user request with current floor, destination floor, and direction
        Users.enqueue(currFloor, wantFloor, (currFloor < wantFloor));
    }
    void printTraversal(int targetFloor) {
        // Display the elevator's traversal
        cout << "+---------------------+" << endl;
        cout << "| Elevator Traversal  |" << endl;
        cout << "+---------------------+" << endl;
        cout << "| Floor | Status      |" << endl;
        cout << "+---------------------+" << endl;

        for (int floor = 9; floor >= 1; --floor) {
            // Start the row
            cout << "|  " << floor << "   |";

            // Add status based on currentFloor and targetFloor
            if (floor == currentFloor) {
                cout << " [E]"; // Elevator's current position
            } else {
                cout << "     "; // Empty space for other floors
            }

            if (floor == targetFloor) {
                cout << " [T]"; // Target floor
            } else {
                cout << "     "; // Empty space for non-target floors
            }

            // End the row
            cout << " |" << endl;
        }

        cout << "+---------------------+" << endl;
    }


void move() {
    bool moved; //if movement is needed
    do {
        moved = false;

        // adds destination from current floor users
        Queue tempQueue;
        while (!Users.isEmpty()) {
            Node* user = Users.dequeue(); //point to queue's front
            if (user->floorlvl == currentFloor) { //if the queue is the current level
                Movement.enqueue(user->wantFloor); //add it to the priority queue
                Records.push(user->floorlvl, user->wantFloor, user->goingUp); //record it to the stack
                delete user; //delete the pointer
                moved = true; // New target added
            } else {
                tempQueue.enqueue(user->floorlvl, user->wantFloor, user->goingUp); //if not in current floor, go closer to the next target
            }
        }
        // get what's remaining from tempQueue and add it back to the old UserQueue
        while (!tempQueue.isEmpty()) {
            Node* user = tempQueue.dequeue();
            Users.enqueue(user->floorlvl, user->wantFloor, user->goingUp);
            delete user;
        }

        // Check if Movement (priority queue) is empty
        if (Movement.isEmpty()) {
                //move to next location
            if (!Users.isEmpty()) {
                Node* nextUser = Users.front();
                Movement.enqueue(nextUser->floorlvl);
                moved = true; // Enqueued new target
            } else {
                // No targets, exit loop
                break;
            }
        }
        //create a target location based on priority queue
        Node* targetNode = Movement.front();
        int targetFloor = targetNode->floorlvl;

        // Determine direction and move one floor
        if (targetFloor > currentFloor) {
            currentFloor++;
            isGoingUp = true;
            moved = true;
        } else if (targetFloor < currentFloor) {
            currentFloor--;
            isGoingUp = false;
            moved = true;
        } else {
            // Reached target floor
            delete Movement.dequeue();
            Records.push(currentFloor, targetFloor, isGoingUp);
            moved = true; // Target processed, continue loop to check for more
            continue;
        }

        // Update elevator state and re-sort Movement
        Movement.setElevatorState(isGoingUp, currentFloor);
        Movement.reSortQueue();

        // Print traversal
        printTraversal(targetFloor);

    } while (moved);
}

    void SaveLogs() {
        Records.recordLogs();
    }

    void printElevatorStatus() const {
        cout << "+---------------------+\n"
             << "| Elevator Status     |\n"
             << "+---------------------+\n"
             << "| Current Floor: " << currentFloor << "   |\n"
             << "| Direction: " << (isGoingUp ? "Up" : "Down") << "         |\n"
             << "+---------------------+" << endl;
    }
};

template <typename T>
T sanitize(T input) {
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
        cin >> input;
    }
    return input;
}

void menuSys() {
    Elevator elevator;
    int choice;

    do {
        cout << "+------------WAITING FOR ELEVATOR---------------------+\n"
             << "[1] Request Elevator\n"
             << "[2] Move The Elevator\n"
             << "[3] Print Status\n"
             << "[4] Save & Exit\n"
             << "+-----------------------------------------------------+\n";
        elevator.printRequests();
        cout << "Enter choice: ";
        cin >> choice;
        choice = sanitize(choice);

        switch (choice) {
            case 1: {
                int curr, want;
                cout << "Current floor (1-9): ";
                cin >> curr;
                curr = sanitize(curr);
                while (curr < 1 || curr > 9) {
                    cout << "Invalid floor! Try again: ";
                    cin >> curr;
                    curr = sanitize(curr);
                }

                cout << "Destination floor (1-9): ";
                cin >> want;
                want = sanitize(want);
                while (want < 1 || want > 9 || want == curr) {
                    cout << "Invalid destination! Try again: ";
                    cin >> want;
                    want = sanitize(want);
                }
                elevator.requestFloor(curr, want);
                break;
            }
            case 2:
                elevator.move();
                cout << "Operation completed. Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 3:
                elevator.printElevatorStatus();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 4:
                elevator.SaveLogs();
                cout << "Logs saved. Exiting...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        system("cls");
    } while (true);
}

int main() {
    menuSys();
    return 0;
}
