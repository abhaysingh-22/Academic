#include <iostream>
using namespace std;

#define SIZE 5  // fixed size of circular queue

class CircularQueue {
private:
    int items[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    // ---------- CHECK IF FULL ----------
    bool isFull() {
        return (front == 0 && rear == SIZE - 1) || (rear == (front - 1) % (SIZE - 1));
    }

    // ---------- CHECK IF EMPTY ----------
    bool isEmpty() {
        return (front == -1);
    }

    // ---------- ENQUEUE OPERATION ----------
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is FULL! Cannot insert " << value << endl;
            return;
        }

        if (front == -1) { // first element
            front = 0;
            rear = 0;
            items[rear] = value;
        }
        else if (rear == SIZE - 1 && front != 0) {
            rear = 0;
            items[rear] = value;
        }
        else {
            rear++;
            items[rear] = value;
        }

        cout << value << " inserted into the queue.\n";
    }

    // ---------- DEQUEUE OPERATION ----------
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is EMPTY! Cannot delete.\n";
            return -1;
        }

        int data = items[front];
        items[front] = -1; // optional, for clarity

        if (front == rear) { // only one element
            front = -1;
            rear = -1;
        }
        else if (front == SIZE - 1)
            front = 0;
        else
            front++;

        cout << "Deleted element: " << data << endl;
        return data;
    }

    // ---------- DISPLAY OPERATION ----------
    void display() {
        if (isEmpty()) {
            cout << "Queue is EMPTY!\n";
            return;
        }

        cout << "Queue elements are: ";

        if (rear >= front) {
            for (int i = front; i <= rear; i++)
                cout << items[i] << " ";
        } else {
            for (int i = front; i < SIZE; i++)
                cout << items[i] << " ";
            for (int i = 0; i <= rear; i++)
                cout << items[i] << " ";
        }
        cout << endl;
    }
};

// ---------- MAIN FUNCTION ----------
int main() {
    CircularQueue q;
    int choice, value;

    while (true) {
        cout << "\n--- CIRCULAR QUEUE USING ARRAY ---\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                q.enqueue(value);
                break;

            case 2:
                q.dequeue();
                break;

            case 3:
                q.display();
                break;

            case 0:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
