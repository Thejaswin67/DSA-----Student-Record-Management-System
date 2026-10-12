#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

// ============================================================
// STUDENT STRUCTURE
// ============================================================

struct Student {
    int id;
    int age;
    string name;
    string dept;
    string phone;
    float marks;
};

// ============================================================
// LINKED LIST NODE
// ============================================================

struct Node {
    Student data;
    Node* next;
};

// ============================================================
// GLOBAL VARIABLES
// ============================================================

Node* head = nullptr;
int cnt = 0;

// ============================================================
// GET GRADE
// RANGES:
// F : 0 - <50  (includes marks below 40)
// C : 50 - <70
// B : 70 - <90
// A : 90 - 100
// ============================================================

char getGrade(float marks) {
    if (marks < 50)
        return 'F';
    else if (marks < 70)
        return 'C';
    else if (marks < 90)
        return 'B';
    else
        return 'A';
}

// ============================================================
// GET MARKS RANGE
// ============================================================

string getMarksRange(float marks) {
    if (marks < 50)
        return "Below 50";
    else if (marks < 70)
        return "50 - <70";
    else if (marks < 90)
        return "70 - <90";
    else
        return "90 - 100";
}

// ============================================================
// GET RANGE VALUE FOR SORTING
// F < C < B < A
// ============================================================

int getGradeValue(float marks) {
    if (marks >= 90)
        return 4;
    else if (marks >= 70)
        return 3;
    else if (marks >= 50)
        return 2;
    else
        return 1;
}

// ============================================================
// CREATE NODE
// ============================================================

Node* makeNode(Student s) {
    Node* n = new Node;
    n->data = s;
    n->next = nullptr;
    return n;
}

// ============================================================
// DISPLAY ONE STUDENT
// ============================================================

void show(Student s) {
    cout << left
         << setw(8)  << s.id
         << setw(20) << s.name
         << setw(5)  << s.age
         << setw(25) << s.dept
         << setw(9)  << fixed << setprecision(1) << s.marks
         << setw(8)  << getGrade(s.marks)
         << setw(13) << getMarksRange(s.marks)
         << setw(14) << s.phone
         << "\n";
}

// ============================================================
// DISPLAY HEADER
// ============================================================

void displayHeader() {
    cout << left
         << setw(8)  << "ID"
         << setw(20) << "NAME"
         << setw(5)  << "AGE"
         << setw(25) << "DEPT"
         << setw(9)  << "MARKS"
         << setw(8)  << "GRADE"
         << setw(13) << "RANGE"
         << setw(14) << "PHONE"
         << "\n";

    cout << string(102, '-') << "\n";
}

// ============================================================
// FIND STUDENT
// ============================================================

Node* findStudent(int id) {
    Node* t = head;

    while (t != nullptr) {
        if (t->data.id == id)
            return t;

        t = t->next;
    }

    return nullptr;
}

// ============================================================
// ADD STUDENT
// ============================================================

void addStudent() {
    Student s;

    cout << "\nID: ";
    cin >> s.id;
    cin.ignore();

    if (findStudent(s.id) != nullptr) {
        cout << "[ERROR] ID already exists!\n";
        return;
    }

    cout << "Name: ";
    getline(cin, s.name);

    cout << "Age: ";
    cin >> s.age;
    cin.ignore();

    if (s.age <= 0) {
        cout << "[ERROR] Invalid age!\n";
        return;
    }

    cout << "Dept: ";
    getline(cin, s.dept);

    cout << "Marks: ";
    cin >> s.marks;
    cin.ignore();

    if (s.marks < 0 || s.marks > 100) {
        cout << "[ERROR] Marks must be between 0 and 100!\n";
        return;
    }

    cout << "Phone: ";
    getline(cin, s.phone);

    Node* n = makeNode(s);

    if (head == nullptr)
        head = n;
    else {
        n->next = head;
        head = n;
    }

    cnt++;

    cout << "[OK] Student added successfully!\n";
    cout << "Grade: " << getGrade(s.marks)
         << " | Range: " << getMarksRange(s.marks) << "\n";
}

// ============================================================
// DISPLAY ALL STUDENTS
// ============================================================

void displayStudents() {
    if (head == nullptr) {
        cout << "[INFO] No students found!\n";
        return;
    }

    cout << "\n=== ALL STUDENTS ===\n";
    cout << "Total: " << cnt << "\n\n";

    displayHeader();

    Node* t = head;

    while (t != nullptr) {
        show(t->data);
        t = t->next;
    }

    cout << string(102, '=') << "\n";
}

// ============================================================
// SEARCH STUDENT
// ============================================================

void searchStudent() {
    int id;

    cout << "\nEnter ID: ";
    cin >> id;
    cin.ignore();

    Node* s = findStudent(id);

    if (s != nullptr) {
        cout << "\n[FOUND]\n\n";
        displayHeader();
        show(s->data);

        cout << "\nGrade : " << getGrade(s->data.marks) << "\n";
        cout << "Range : " << getMarksRange(s->data.marks) << "\n";
    }
    else {
        cout << "[NOT FOUND] Student does not exist!\n";
    }
}

// ============================================================
// UPDATE STUDENT
// ============================================================

void updateStudent() {
    int id;

    cout << "\nEnter ID: ";
    cin >> id;
    cin.ignore();

    Node* s = findStudent(id);

    if (s == nullptr) {
        cout << "[NOT FOUND] Student does not exist!\n";
        return;
    }

    cout << "\n1. Name\n";
    cout << "2. Age\n";
    cout << "3. Department\n";
    cout << "4. Marks\n";
    cout << "5. Phone\n";
    cout << "Choice: ";

    int ch;
    cin >> ch;
    cin.ignore();

    switch (ch) {
        case 1:
            cout << "New Name: ";
            getline(cin, s->data.name);
            break;

        case 2:
            cout << "New Age: ";
            cin >> s->data.age;
            cin.ignore();

            if (s->data.age <= 0) {
                cout << "[ERROR] Invalid age!\n";
                return;
            }
            break;

        case 3:
            cout << "New Department: ";
            getline(cin, s->data.dept);
            break;

        case 4:
            cout << "New Marks: ";
            cin >> s->data.marks;
            cin.ignore();

            if (s->data.marks < 0 || s->data.marks > 100) {
                cout << "[ERROR] Marks must be between 0 and 100!\n";
                return;
            }

            cout << "New Grade: " << getGrade(s->data.marks)
                 << " | New Range: " << getMarksRange(s->data.marks) << "\n";
            break;

        case 5:
            cout << "New Phone: ";
            getline(cin, s->data.phone);
            break;

        default:
            cout << "[ERROR] Invalid choice!\n";
            return;
    }

    cout << "[OK] Student updated successfully!\n";
}

// ============================================================
// DELETE STUDENT
// ============================================================

void deleteStudent() {
    int id;

    cout << "\nEnter ID: ";
    cin >> id;
    cin.ignore();

    if (head == nullptr) {
        cout << "[NOT FOUND] No students available!\n";
        return;
    }

    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cnt--;

        cout << "[OK] Student deleted successfully!\n";
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.id == id) {
            previous->next = current->next;
            delete current;
            cnt--;

            cout << "[OK] Student deleted successfully!\n";
            return;
        }

        previous = current;
        current = current->next;
    }

    cout << "[NOT FOUND] Student does not exist!\n";
}

// ============================================================
// GRADE STATISTICS
// ============================================================

void gradeCounts() {
    int gradeA = 0;
    int gradeB = 0;
    int gradeC = 0;
    int gradeF = 0;

    Node* t = head;

    while (t != nullptr) {
        char grade = getGrade(t->data.marks);

        if (grade == 'A')
            gradeA++;
        else if (grade == 'B')
            gradeB++;
        else if (grade == 'C')
            gradeC++;
        else
            gradeF++;

        t = t->next;
    }

    cout << "\n====================================\n";
    cout << "          GRADE SUMMARY\n";
    cout << "====================================\n";
    cout << "A Rank (90-100) : " << gradeA << " student(s)\n";
    cout << "B Rank (70-<90) : " << gradeB << " student(s)\n";
    cout << "C Rank (50-<70) : " << gradeC << " student(s)\n";
    cout << "F Rank (Below 50): " << gradeF << " student(s)\n";
    cout << "====================================\n";
}

// ============================================================
// DISPLAY STUDENTS OF ONE GRADE
// ============================================================

void displayGradeStudents(char selectedGrade) {
    if (head == nullptr) {
        cout << "[INFO] No students available!\n";
        return;
    }

    int count = 0;
    Node* t = head;

    while (t != nullptr) {
        if (getGrade(t->data.marks) == selectedGrade)
            count++;

        t = t->next;
    }

    cout << "\n====================================\n";
    cout << "          " << selectedGrade << " RANK STUDENTS\n";
    cout << "====================================\n";
    cout << "Total: " << count << " student(s)\n\n";

    if (count == 0) {
        cout << "[INFO] No students found in " << selectedGrade << " Rank.\n";
        cout << "====================================\n";
        return;
    }

    displayHeader();

    t = head;

    while (t != nullptr) {
        if (getGrade(t->data.marks) == selectedGrade)
            show(t->data);

        t = t->next;
    }

    cout << string(102, '=') << "\n";
}

// ============================================================
// SEARCH STUDENTS BY GRADE
// ============================================================

void searchByGrade() {
    cout << "\n=========== GRADE SEARCH ===========\n";
    cout << "1. F Rank (Below 50)\n";
    cout << "2. C Rank (50 - <70)\n";
    cout << "3. B Rank (70 - <90)\n";
    cout << "4. A Rank (90 - 100)\n";
    cout << "====================================\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    char grade;

    switch (choice) {
        case 1:
            grade = 'F';
            break;

        case 2:
            grade = 'C';
            break;

        case 3:
            grade = 'B';
            break;

        case 4:
            grade = 'A';
            break;

        default:
            cout << "[ERROR] Invalid grade choice!\n";
            return;
    }

    displayGradeStudents(grade);
}

// ============================================================
// SORT STUDENTS
// ============================================================

void sortStudents() {
    if (head == nullptr) {
        cout << "[INFO] No students available!\n";
        return;
    }

    Student* arr = new Student[cnt];

    Node* t = head;

    for (int i = 0; i < cnt; i++) {
        arr[i] = t->data;
        t = t->next;
    }

    cout << "\n=========== SORT MENU ===========\n";
    cout << "1. Marks Descending\n";
    cout << "2. Marks Ascending\n";
    cout << "3. ID Ascending\n";
    cout << "4. ID Descending\n";
    cout << "5. Name A-Z\n";
    cout << "6. Name Z-A\n";
    cout << "7. Grade Descending (A to F)\n";
    cout << "8. Grade Ascending (F to A)\n";
    cout << "9. Marks Range Descending (A to F)\n";
    cout << "10. Marks Range Ascending (F to A)\n";
    cout << "=================================\n";
    cout << "Choice: ";

    int type;
    cin >> type;
    cin.ignore();

    if (type < 1 || type > 10) {
        cout << "[ERROR] Invalid sorting choice!\n";
        delete[] arr;
        return;
    }

    // Bubble Sort
    for (int i = 0; i < cnt - 1; i++) {
        for (int j = 0; j < cnt - i - 1; j++) {
            bool swapRequired = false;

            if (type == 1)
                swapRequired = arr[j].marks < arr[j + 1].marks;

            else if (type == 2)
                swapRequired = arr[j].marks > arr[j + 1].marks;

            else if (type == 3)
                swapRequired = arr[j].id > arr[j + 1].id;

            else if (type == 4)
                swapRequired = arr[j].id < arr[j + 1].id;

            else if (type == 5)
                swapRequired = arr[j].name > arr[j + 1].name;

            else if (type == 6)
                swapRequired = arr[j].name < arr[j + 1].name;

            else if (type == 7 || type == 9) {
                int range1 = getGradeValue(arr[j].marks);
                int range2 = getGradeValue(arr[j + 1].marks);

                // Higher grade/range first: A -> B -> C -> F
                if (range1 < range2)
                    swapRequired = true;
                else if (range1 == range2 &&
                         arr[j].marks < arr[j + 1].marks)
                    swapRequired = true;
            }

            else if (type == 8 || type == 10) {
                int range1 = getGradeValue(arr[j].marks);
                int range2 = getGradeValue(arr[j + 1].marks);

                // Lower grade/range first: F -> C -> B -> A
                if (range1 > range2)
                    swapRequired = true;
                else if (range1 == range2 &&
                         arr[j].marks > arr[j + 1].marks)
                    swapRequired = true;
            }

            if (swapRequired) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    cout << "\n=== SORTED STUDENTS ===\n";
    cout << "A : 90 - 100\n";
    cout << "B : 70 - <90\n";
    cout << "C : 50 - <70\n";
    cout << "F : Below 50\n\n";

    displayHeader();

    for (int i = 0; i < cnt; i++)
        show(arr[i]);

    cout << string(102, '=') << "\n";

    delete[] arr;
}

// ============================================================
// SAVE STUDENTS TO CSV
// ============================================================

void saveStudents() {
    if (head == nullptr) {
        cout << "[INFO] No students to save!\n";
        return;
    }

    ofstream file("students.csv");

    if (!file.is_open()) {
        cout << "[ERROR] Could not open students.csv!\n";
        return;
    }

    file << "ID,Name,Age,Dept,Marks,Grade,Phone\n";

    Node* t = head;

    while (t != nullptr) {
        file << t->data.id << ","
             << t->data.name << ","
             << t->data.age << ","
             << t->data.dept << ","
             << t->data.marks << ","
             << getGrade(t->data.marks) << ","
             << t->data.phone << "\n";

        t = t->next;
    }

    file.close();

    cout << "[OK] Data saved to students.csv!\n";
}

// ============================================================
// LOAD STUDENTS FROM CSV
// Supports both old 6-column and new 7-column CSV files.
// ============================================================

void loadStudents() {
    ifstream file("students.csv");

    if (!file.is_open()) {
        cout << "[INFO] No existing file. Starting fresh.\n";
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        string token;
        Student s;

        try {
            if (!getline(ss, token, ','))
                continue;
            s.id = stoi(token);

            if (!getline(ss, s.name, ','))
                continue;

            if (!getline(ss, token, ','))
                continue;
            s.age = stoi(token);

            if (!getline(ss, s.dept, ','))
                continue;

            if (!getline(ss, token, ','))
                continue;
            s.marks = stof(token);

            if (s.marks < 0 || s.marks > 100)
                continue;

            // The new CSV has Grade before Phone.
            // Old CSV has Phone directly after Marks.
            if (!getline(ss, token, ','))
                continue;

            if (token == "A" || token == "B" ||
                token == "C" || token == "F") {
                getline(ss, s.phone);
            }
            else {
                s.phone = token;
            }

            if (findStudent(s.id) != nullptr)
                continue;

            Node* n = makeNode(s);

            if (head == nullptr)
                head = n;
            else {
                n->next = head;
                head = n;
            }

            cnt++;
        }
        catch (...) {
            cout << "[WARNING] Invalid record skipped.\n";
        }
    }

    file.close();

    cout << "[OK] Student data loaded!\n";
}

// ============================================================
// GENERATE REPORT
// ============================================================

void generateReport() {
    if (head == nullptr) {
        cout << "[INFO] No students available!\n";
        return;
    }

    ofstream file("students_report.txt");

    if (!file.is_open()) {
        cout << "[ERROR] Could not create report!\n";
        return;
    }

    file << "====================================\n";
    file << "       STUDENT RECORD REPORT\n";
    file << "====================================\n";
    file << "Total Students: " << cnt << "\n\n";

    int record = 1;
    Node* t = head;

    while (t != nullptr) {
        file << "Record " << record++ << "\n";
        file << "ID: " << t->data.id << "\n";
        file << "Name: " << t->data.name << "\n";
        file << "Age: " << t->data.age << "\n";
        file << "Department: " << t->data.dept << "\n";
        file << "Marks: " << fixed << setprecision(1)
             << t->data.marks << "\n";
        file << "Grade: " << getGrade(t->data.marks) << "\n";
        file << "Marks Range: " << getMarksRange(t->data.marks) << "\n";
        file << "Phone: " << t->data.phone << "\n";
        file << "------------------------------------\n\n";

        t = t->next;
    }

    file.close();

    cout << "[OK] Report exported to students_report.txt!\n";
}

// ============================================================
// STATISTICS
// ============================================================

void statistics() {
    if (head == nullptr) {
        cout << "[INFO] No students available!\n";
        return;
    }

    float totalMarks = 0;
    float highest = -1;
    float lowest = 101;
    int totalAge = 0;

    int gradeA = 0;
    int gradeB = 0;
    int gradeC = 0;
    int gradeF = 0;

    Node* t = head;

    while (t != nullptr) {
        totalMarks += t->data.marks;
        totalAge += t->data.age;

        if (t->data.marks > highest)
            highest = t->data.marks;

        if (t->data.marks < lowest)
            lowest = t->data.marks;

        char grade = getGrade(t->data.marks);

        if (grade == 'A')
            gradeA++;
        else if (grade == 'B')
            gradeB++;
        else if (grade == 'C')
            gradeC++;
        else
            gradeF++;

        t = t->next;
    }

    cout << "\n=============================\n";
    cout << "          STATISTICS\n";
    cout << "=============================\n";
    cout << "Total Students : " << cnt << "\n";
    cout << "Average Marks  : " << fixed << setprecision(2)
         << totalMarks / cnt << "\n";
    cout << "Average Age    : "
         << static_cast<float>(totalAge) / cnt << "\n";
    cout << "Highest Marks  : " << highest << "\n";
    cout << "Lowest Marks   : " << lowest << "\n";
    cout << "Marks Range    : " << highest - lowest << "\n\n";

    cout << "Grade A (90-100) : " << gradeA << "\n";
    cout << "Grade B (70-<90) : " << gradeB << "\n";
    cout << "Grade C (50-<70) : " << gradeC << "\n";
    cout << "Grade F (<50)    : " << gradeF << "\n";
    cout << "=============================\n";
}

// ============================================================
// FREE MEMORY
// ============================================================

void clearMemory() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    cnt = 0;
}

// ============================================================
// MAIN
// ============================================================

int main() {
    cout << "====================================\n";
    cout << "   STUDENT RECORD MANAGEMENT SYSTEM\n";
    cout << "          Team: Formula 4\n";
    cout << "====================================\n";

    loadStudents();

    while (true) {
        cout << "\n============ MENU ============\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Students\n";
        cout << "7. Save Students\n";
        cout << "8. Generate Report\n";
        cout << "9. Statistics\n";
        cout << "10. Exit\n";
        cout << "==============================\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                sortStudents();
                break;

            case 7:
                saveStudents();
                break;

            case 8:
                generateReport();
                break;

            case 9:
                statistics();
                break;

            case 10:
                gradeCounts();
                break;

            case 11:
                searchByGrade();
                break;

            case 12:
                saveStudents();
                clearMemory();
                cout << "[EXIT] Program closed successfully.\n";
                return 0;

            default:
                cout << "[ERROR] Invalid menu choice!\n";
        }
    }

    return 0;
}
