#include <bits/stdc++.h>
using namespace std;

struct Student
{
    int id;
    char name[50];
    float cgpa;
};

Student *addStudent(Student *students, int &size, int &capacity)
{
    if (size == capacity)
    {
        capacity *= 2;
        students = (Student*)realloc(students, capacity * sizeof(Student));
        if (!students)
        {
            cout << "Memory reallocation failed";
            exit(1);
        }
    }

    cout << "Enter student ID: ";
    cin >> students[size].id;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(students[size].name, 50);
    cout << "Enter student CGPA: ";
    cin >> students[size].cgpa;
    size++;

    return students;
}

void LinearSearch(Student* students, int size, int key){
    bool found = false;

    for(int i = 0; i< size; i++){
        if(students[i].id == key){
            cout << "Found(Linear): " << students[i].id << " | " << students[i].name << " | " << students[i].cgpa << endl;
            found = true;
            break;
        }
    }
    if(!found) cout << "Record not found(Linear)";
}

void binarySearch(Student* students, int size, int key){
    int low = 0, high = size - 1, mid;
    bool found = false;
    while(low <= high){
        mid = (low + high) / 2;
        if(students[mid].id == key){
            cout << "Found: " << students[mid].id << " | " << students[mid].name << " | " << students[mid].cgpa << endl;
            found = true;
            break;
        }else if(students[mid].id < key){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    if(found){
        cout << "Student not found in the record" << endl;
    }
}

void bubbleSortByName(Student* students, int size){
    
}
