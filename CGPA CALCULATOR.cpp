#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

class Course {
public:
    std::string name;
    int creditHours;
    char grade;
    double gradePoint;

    Course(std::string n, int ch, char g) : name(n), creditHours(ch), grade(g) {
        gradePoint = calculateGradePoint(grade);
    }

    double calculateGradePoint(char grade) {
        switch (grade) {
            case 'A': return 4.0;
            case 'B': return 3.0;
            case 'C': return 2.0;
            case 'D': return 1.0;
            case 'F': return 0.0;
            default: return 0.0;
        }
    }
};

class CGPACalculator {
public:
    std::vector<Course> courses;

    void addCourse() {
        std::string name;
        int creditHours;
        char grade;

        std::cout << "Enter Course Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter Credit Hours: ";
        std::cin >> creditHours;
        std::cout << "Enter Grade (A/B/C/D/F): ";
        std::cin >> grade;

        courses.push_back(Course(name, creditHours, grade));
        std::cout << "Course added successfully.\n";
    }

    double calculateTotalCredits() {
        double totalCredits = 0;
        for (const auto &course : courses) {
            totalCredits += course.creditHours;
        }
        return totalCredits;
    }

    double calculateTotalGradePoints() {
        double totalGradePoints = 0;
        for (const auto &course : courses) {
            totalGradePoints += course.creditHours * course.gradePoint;
        }
        return totalGradePoints;
    }

    double calculateGPA() {
        double totalCredits = calculateTotalCredits();
        if (totalCredits == 0) return 0;
        return calculateTotalGradePoints() / totalCredits;
    }

    void displayCourseInfo() {
        std::cout << "\nCourse Information:\n";
        std::cout << std::left << std::setw(20) << "Course Name" 
                  << std::setw(15) << "Credit Hours" 
                  << std::setw(10) << "Grade" 
                  << std::setw(15) << "Grade Point" << "\n";
        std::cout << "------------------------------------------------------------\n";
        for (const auto &course : courses) {
            std::cout << std::left << std::setw(20) << course.name 
                      << std::setw(15) << course.creditHours 
                      << std::setw(10) << course.grade 
                      << std::setw(15) << course.gradePoint << "\n";
        }
    }

    void displayCGPA() {
        std::cout << "\nCGPA Summary:\n";
        std::cout << "Total Credits: " << calculateTotalCredits() 
                  << "\nTotal Grade Points: " << calculateTotalGradePoints() 
                  << "\nGPA for the Semester: " << calculateGPA() 
                  << "\nCumulative GPA (CGPA): " << calculateGPA() << "\n";
    }
};

void clearScreen() {
    system(CLEAR);
}

int main() {
    CGPACalculator calculator;
    int numCourses, choice;

    std::cout << "Enter the number of courses: ";
    std::cin >> numCourses;

    for (int i = 0; i < numCourses; ++i) {
        clearScreen();
        std::cout << "\nEntering details for Course " << (i + 1) << ":\n";
        calculator.addCourse();
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    while (true) {
        clearScreen();
        std::cout << "\nCGPA Calculator Menu:\n";
        std::cout << "1. Add another course\n";
        std::cout << "2. Display course information\n";
        std::cout << "3. Display CGPA\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        clearScreen();

        switch (choice) {
            case 1:
                calculator.addCourse();
                break;
            case 2:
                calculator.displayCourseInfo();
                break;
            case 3:
                calculator.displayCGPA();
                break;
            case 4:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
