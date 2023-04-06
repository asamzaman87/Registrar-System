/*
  Asam Zaman
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    explicit Course(const string& courseName);
    const string& getName() const;
    size_t getStudentsSize() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    explicit Student(const string& name);
    const string& getName() const;
    size_t getCoursesSize() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

// Methods for Registrar Class Below

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

// Methods for Course Class

Course::Course(const string& courseName): name(courseName){} // Constructor
const string& Course:: getName() const {return name;}
size_t Course:: getStudentsSize() const {return students.size();}
// Checks to see if student already exists within the course's vector of pointers as the condition
//before adding the student to the course
bool Course::addStudent(Student* student_pntr){
    for (Student* currStudent:students){
        if (currStudent == student_pntr){
            return false;
        }
    }
    students.push_back(student_pntr);
    return true;
}

//Output operator for Course (outputs the students' names enrolled in the course(s)
ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ":";
    if(rhs.getStudentsSize() == 0){cout << " No Students" << endl;}
    else{
        for(const Student* pointer: rhs.students){
            cout << " " << pointer -> getName() << " ";
        }
        cout << endl;
    }
    return os;
}

//removes student from course
void Course::removeStudentsFromCourse(){
    for (Student* student: students){
        student -> removedFromCourse(this);
    }
}



// Methods for Student Class

Student:: Student(const string& name): name(name){} //Constructor
const string& Student:: getName() const{return name;}
size_t Student:: getCoursesSize() const {return courses.size();}

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
void Student:: removedFromCourse(Course* coursePtr){
    for (size_t ndx = 0; ndx < courses.size(); ++ndx){
        if (courses[ndx] == coursePtr){
            courses[ndx] = courses[courses.size() - 1];
        }
    }
    courses.pop_back();
}


