#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Student {
    int id;
    char name[50];
    float cgpa;
};

// Function prototypes
void addStudent(Student *&students, int &count, int &capacity);
void displayStudents(Student *students, int count);
int linearSearch(Student *students, int count, int id);
int binarySearch(Student *students, int count, int id);
void bubbleSortByName(Student *students, int count);
void selectionSortByCGPA(Student *students, int count, bool ascending);
void analyzeSearch(Student *students, int count, int id);

// ------------------ MAIN ------------------
int main() {
    int capacity = 2;   // initial capacity
    int count = 0;      // number of students
    Student *students = new Student[capacity];

    int choice;
    while (true) {
        cout << "\n---- STUDENT DATABASE MENU ----\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Linear Search by ID\n";
        cout << "4. Binary Search by ID\n";
        cout << "5. Sort by Name (Bubble Sort)\n";
        cout << "6. Sort by CGPA (Selection Sort)\n";
        cout << "7. Analyze Search Performance\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, count, capacity);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3: {
                int id;
                cout << "Enter Student ID to search: ";
                cin >> id;
                int pos = linearSearch(students, count, id);
                if (pos != -1)
                    cout << "Found: " << students[pos].name << " (CGPA: " << students[pos].cgpa << ")\n";
                else
                    cout << "Student not found.\n";
                break;
            }

            case 4: {
                int id;
                cout << "Enter Student ID to search: ";
                cin >> id;
                int pos = binarySearch(students, count, id);
                if (pos != -1)
                    cout << "Found: " << students[pos].name << " (CGPA: " << students[pos].cgpa << ")\n";
                else
                    cout << "Student not found (ensure list is sorted by ID before using binary search).\n";
                break;
            }

            case 5:
                bubbleSortByName(students, count);
                cout << "Sorted by Name (Alphabetically).\n";
                break;

            case 6: {
                int order;
                cout << "1. Ascending\n2. Descending\nEnter choice: ";
                cin >> order;
                selectionSortByCGPA(students, count, order == 1);
                cout << "Sorted by CGPA.\n";
                break;
            }

            case 7: {
                int id;
                cout << "Enter Student ID to analyze search performance: ";
                cin >> id;
                analyzeSearch(students, count, id);
                break;
            }

            case 0:
                cout << "Exiting...\n";
                delete[] students;
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

// ------------------ FUNCTIONS ------------------

void addStudent(Student *&students, int &count, int &capacity) {
    if (count == capacity) {
        capacity *= 2;
        Student *temp = new Student[capacity];
        for (int i = 0; i < count; i++)
            temp[i] = students[i];
        delete[] students;
        students = temp;
        cout << "(List expanded using realloc logic)\n";
    }

    cout << "Enter Student ID: ";
    cin >> students[count].id;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(students[count].name, 50);
    cout << "Enter CGPA: ";
    cin >> students[count].cgpa;
    count++;

    cout << "Student added successfully!\n";
}

void displayStudents(Student *students, int count) {
    cout << "\n--- STUDENT LIST ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << "CGPA\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << students[i].id
             << setw(20) << students[i].name
             << students[i].cgpa << endl;
    }
}

int linearSearch(Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

int binarySearch(Student *students, int count, int id) {
    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].id == id)
            return mid;
        else if (students[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void bubbleSortByName(Student *students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0)
                swap(students[j], students[j + 1]);
        }
    }
}

void selectionSortByCGPA(Student *students, int count, bool ascending) {
    for (int i = 0; i < count - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < count; j++) {
            if (ascending ? (students[j].cgpa < students[idx].cgpa)
                          : (students[j].cgpa > students[idx].cgpa))
                idx = j;
        }
        swap(students[i], students[idx]);
    }
}

void analyzeSearch(Student *students, int count, int id) {
    cout << "\n--- Search Performance Analysis ---\n";

    // Linear search before sorting
    int pos1 = linearSearch(students, count, id);
    cout << "Linear Search Result: ";
    if (pos1 != -1)
        cout << students[pos1].name << " found.\n";
    else
        cout << "Not found.\n";

    // Sort by ID (for binary search)
    sort(students, students + count, [](Student a, Student b) {
        return a.id < b.id;
    });

    int pos2 = binarySearch(students, count, id);
    cout << "Binary Search Result (after sorting): ";
    if (pos2 != -1)
        cout << students[pos2].name << " found.\n";
    else
        cout << "Not found.\n";
}
