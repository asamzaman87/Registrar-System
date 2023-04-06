// Student METHODS

#include <iostream>
#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <string>
#include <vector>
using namespace std;

namespace Tandon{

    Student:: Student(const string& name): name(name){} //Constructor
    const string& Student:: getName() const{return name;}
    size_t Student::getCoursesSize() const {return courses.size();}
    // Checks if course is already assigned to student before enrolling student in the course.
    bool Student::addCourse(Course* course_pntr){
        for (Course* currCourse:courses){
            if (currCourse == course_pntr){
                return false;
            }
        }
        courses.push_back(course_pntr);
        return true;
    }

//Output operator for Student
    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.name << ":";
        if(rhs.getCoursesSize() == 0){cout << " No Courses" << endl;}
        else{
            for(const Course* pointer: rhs.courses){
                cout << " " << pointer -> getName() << " ";
            }
            cout << endl;
        }
        return os;
    }

// Removes course from student's overall courses
    void Student::removedFromCourse(Course* coursePtr){
        for (size_t ndx = 0; ndx < courses.size(); ++ndx){
            if (courses[ndx] == coursePtr){
                courses[ndx] = courses[courses.size() - 1];
            }
        }
        courses.pop_back();
    }

}
