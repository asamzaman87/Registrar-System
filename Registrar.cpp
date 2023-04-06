// Registrar Methods

#include <iostream>
#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <string>
#include <vector>
using namespace std;

namespace Tandon{

    // Methods for Registrar Class Below
    Registrar::Registrar(){};
// Create new student, but first checks to make sure student doesn't already exist
    bool Registrar::addStudent(const string& studentName){
        if (findStudent(studentName) < students.size()){
            return false;
        }
        students.push_back(new Student(studentName));
        return true;
    }

// Creates new course, but first checks to make sure course doesn't already exist
    bool Registrar::addCourse(const string& courseName){
        if (findCourse(courseName) < courses.size()){
            return false;
        }
        courses.push_back(new Course(courseName));
        return true;
    }

// Student is added to vector of pointers, along with the course
// Student and Course have to exist for the student to enroll in the course
    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
        size_t student_ndx = findStudent(studentName);
        size_t course_ndx = findCourse(courseName);
        if (student_ndx < students.size() && course_ndx < courses.size()){
            students[student_ndx] -> addCourse(courses[course_ndx]);
            courses[course_ndx] -> addStudent(students[student_ndx]);
            return true;
        }
        return false;
    }

// Frees up memory to avoid memory leak and clears the vectors
    void Registrar::purge() {
        for (Course* course: courses){
            delete course;
        }
        for (Student* student: students){
            delete student;
        }
        courses.clear();
        students.clear();
    }

// Student is removed from course's vector; the same happens to the course object
    bool Registrar::cancelCourse(const string& courseName){
        size_t course_ndx = findCourse(courseName);
        if (course_ndx > courses.size()){
            return false;
        }
        courses[course_ndx] -> removeStudentsFromCourse();
        courses[course_ndx] = courses[courses.size()-1];
        delete courses[course_ndx];
        courses.pop_back();
        return true;
    }

// Returns the index of the course in question
    size_t Registrar::findCourse(const string& courseName) const{
        for (size_t i = 0; i < courses.size(); ++i){
            if (courses[i] -> getName() == courseName){
                return i;
            }
        }
        return courses.size();
    }


// Returns the index of the student name passed in the param...
    size_t Registrar::findStudent(const string& studentName) const{
        for (size_t i = 0; i < students.size(); ++i){
            if (students[i]->getName() == studentName){
                return i;
            }
        }
        return students.size();
    }

// Output operator for Registrar
    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's report" << endl;
        os << "Courses:" << endl;
        for (Course* currCourse: rhs.courses){
            os << *currCourse;
        }
        os << "Students:" << endl;
        for (Student* currStudent: rhs.students){
            os << *currStudent;
        }
        return os;
    }

}
