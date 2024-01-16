#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits> // Include for input validation

using namespace std;

// Constants
const int NUM_BIO_STREAM_CLASSES = 3;
const int NUM_MATH_STREAM_CLASSES = 5;
const int STUDENTS_PER_CLASS = 40;

// Function to represent a student
struct Student {
    string name;
    int bioMarks[3];  // Biology, Physics, Chemistry
    int mathMarks[3]; // Combined Maths, Physics, Chemistry
    int totalMarks;
    int schoolRank;
    int classRank;
};

// Function prototypes
void getInputFromUser(vector<Student>& students);
void calculateTotalMarks(vector<Student>& students);
void rankStudents(vector<Student>& students);
void printResults(const vector<Student>& students);
void writeResultsToFile(const vector<Student>& students);
void handleFileError(const ofstream& file, const string& filename);
void printStudentDetails(const Student& student);

int main() {
    vector<Student> students;

    // Input data manually
    getInputFromUser(students);

    // Calculate total marks and rank students
    calculateTotalMarks(students);
    rankStudents(students);

    // Print and write results to a file
    printResults(students);
    writeResultsToFile(students);

    return 0;
}

void getInputFromUser(vector<Student>& students) {
    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;

    for (int i = 0; i < numStudents; ++i) {
        Student student;

        cout << "Enter name for student " << i + 1 << ": ";
        cin >> student.name;

        // Input validation for subject-wise marks
        cout << "Enter Biology marks (3 subjects): ";
        for (int j = 0; j < 3; ++j) {
            cin >> student.bioMarks[j];
            if (cin.fail()) {
                cout << "Invalid input. Please enter numeric values for marks." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                j--; // Re-enter the same mark
            }
        }

        cout << "Enter Math marks (3 subjects): ";
        for (int j = 0; j < 3; ++j) {
            cin >> student.mathMarks[j];
            if (cin.fail()) {
                cout << "Invalid input. Please enter numeric values for marks." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                j--; // Re-enter the same mark
            }
        }

        students.push_back(student);
    }
}

void calculateTotalMarks(vector<Student>& students) {
    for (auto& student : students) {
        student.totalMarks = 0;
        for (int i = 0; i < 3; ++i) {
            student.totalMarks += student.bioMarks[i];
        }
        for (int i = 0; i < 3; ++i) {
            student.totalMarks += student.mathMarks[i];
        }
    }
}

void rankStudents(vector<Student>& students) {
    // Sort students based on total marks in descending order
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    // Assign school rank
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].schoolRank = static_cast<int>(i) + 1;
    }

    // Assign class rank for each student in their stream
    int classIndex = 0;
    int classRank = 1;

    for (size_t i = 0; i < students.size(); ++i) {
        students[i].classRank = classRank;

        if ((i + 1) % STUDENTS_PER_CLASS == 0) {
            // Move to the next class
            classIndex++;
            classRank = 1;
        } else {
            classRank++;
        }
    }
}

void printResults(const vector<Student>& students) {
    // Print headers
    cout << "Name\t\t\tBiology\tPhysics\tChemistry\tCombined Maths\tPhysics\tChemistry\tTotal Marks\tSchool Rank\tClass Rank" << endl;

    // Print student details
    for (const auto& student : students) {
        printStudentDetails(student);
    }
}

void writeResultsToFile(const vector<Student>& students) {
    ofstream outputFile("C:\\Users\\Insha\\OneDrive\\Desktop\\SLASSCOM\\Future Career Bridge Challenges\\Software Development Challenges\\Challenge 16 - C++ Programming Basics\\rank_results.txt");

    handleFileError(outputFile, "rank_results.txt");

    // Write headers to file
    outputFile << "Name\t\t\tBiology\tPhysics\tChemistry\tCombined Maths\tPhysics\tChemistry\tTotal Marks\tSchool Rank\tClass Rank" << endl;

    // Write student details to file
    for (const auto& student : students) {
        printStudentDetails(student);
    }

    outputFile.close();
}

void handleFileError(const ofstream& file, const string& filename) {
    if (!file) {
        cerr << "Error opening output file '" << filename << "'." << endl;
        exit(1);
    }
}

void printStudentDetails(const Student& student) {
    cout << "Name: " << student.name << "\n"
         << "Biology: " << student.bioMarks[0] << ", " << student.bioMarks[1] << ", " << student.bioMarks[2] << "\n"
         << "Math: " << student.mathMarks[0] << ", " << student.mathMarks[1] << ", " << student.mathMarks[2] << "\n"
         << "Total Marks: " << student.totalMarks << "\n"
         << "School Rank: " << student.schoolRank << "\n"
         << "Class Rank: " << student.classRank << "\n\n";
}

