#include <bits/stdc++.h>

using namespace std;

struct Course
{
    string name;
    string id;
    Course(string courseName, string courseId) : name(courseName), id(courseId) {}
};

struct Student
{
    string name;
    string id;
    string courseId;
    string grade;
    Student(string studentName, string studentId, string course, string studentGrade)
        : name(studentName), id(studentId), courseId(course), grade(studentGrade) {}
};

class Admin
{
private:
    list<Course> courses;
    map<string, list<Student>> courseRegistrations;

public:
    map<string, list<Student>> &getCourseRegistrations()
    {
        return courseRegistrations;
    }

    void addCourse(string courseName, string courseId)
    {
        courses.push_back(Course(courseName, courseId));
        cout << "\n[INFO] Course \"" << courseName << "\" with Course ID: " << courseId
             << " has been successfully added to the system.\n";
    }

    void deleteCourse(string courseId)
    {
        bool found = false;
        list<Course>::iterator it;
        for (it = courses.begin(); it != courses.end(); ++it)
        {
            if (it->id == courseId)
            {
                courses.erase(it);
                courseRegistrations.erase(courseId);
                cout << "\n[INFO] Course with Course ID: " << courseId << " has been successfully deleted.\n";
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "\n[ERROR] Course ID: " << courseId << " not found in the system.\n";
        }
    }

    void viewCourses()
    {
        cout << "\n[INFO] Available Courses:\n";
        if (courses.empty())
        {
            cout << "[INFO] No courses are available at the moment.\n";
        }
        else
        {
            for (auto &course : courses)
            {
                cout << "Course Name: " << course.name << ", Course ID: " << course.id << endl;
            }
        }
    }

    bool isCourseExists(string courseId)
    {
        for (auto &course : courses)
        {
            if (course.id == courseId)
            {
                return true;
            }
        }
        return false;
    }

    void registerStudentForCourse(string studentName, string studentId, string courseId, string grade)
    {
        if (isCourseExists(courseId))
        {
            courseRegistrations[courseId].push_back(Student(studentName, studentId, courseId, grade));
            cout << "\n[INFO] Student ID: " << studentId
                 << " has been successfully registered for Course ID: " << courseId
                 << " with Grade: " << grade << ".\n";
        }
        else
        {
            cout << "\n[ERROR] Course ID: " << courseId << " does not exist.\n";
        }
    }

    void viewTopPerformingStudents(string courseId)
    {
        if (courseRegistrations.find(courseId) != courseRegistrations.end())
        {
            cout << "\n[INFO] Top Performing Students in Course ID: " << courseId << ":\n";
            list<Student> students = courseRegistrations[courseId];
            if (students.empty())
            {
                cout << "[INFO] No students have registered for this course yet.\n";
                return;
            }

            string topGrade = "";
            for (auto &student : students)
            {
                if (student.grade > topGrade)
                {
                    topGrade = student.grade;
                }
            }

            bool foundTopStudent = false;
            for (auto &student : students)
            {
                if (student.grade == topGrade)
                {
                    cout << "Student ID: " << student.id << ", Grade: " << student.grade << endl;
                    foundTopStudent = true;
                }
            }

            if (!foundTopStudent)
            {
                cout << "[INFO] No top-performing students found for this course.\n";
            }
        }
        else
        {
            cout << "\n[ERROR] No students found for Course ID: " << courseId << ".\n";
        }
    }

    void generateAdvisorFiles()
    {
        map<int, string> advisorAssignments = {
            {1, "640155"}, {101, "640511"}, {201, "640411"}, {301, "640123"}, {401, "640789"}, {501, "640325"}, {601, "640412"}, {701, "640913"}, {801, "640515"}, {901, "640627"}};

        for (int i = 1; i <= 1000; i++)
        {
            string advisorID = "";
            for (auto &pair : advisorAssignments)
            {
                if (i >= pair.first && i < pair.first + 100)
                {
                    advisorID = pair.second;
                    break;
                }
            }

            ofstream file(advisorID + ".txt", ios::app);
            if (file.is_open())
            {
                file << "Student ID: " << i << endl;
                file.close();
            }
        }

        cout << "\n[INFO] Advisor assignment files have been successfully generated.\n";
    }

    void viewAdvisor(string studentId)
    {
        int id = stoi(studentId);
        string advisorId;

        if (id >= 1 && id <= 100)
            advisorId = "640155";
        else if (id >= 101 && id <= 200)
            advisorId = "640511";
        else if (id >= 201 && id <= 300)
            advisorId = "640411";
        else if (id >= 301 && id <= 400)
            advisorId = "640123";
        else if (id >= 401 && id <= 500)
            advisorId = "640789";
        else if (id >= 501 && id <= 600)
            advisorId = "640325";
        else if (id >= 601 && id <= 700)
            advisorId = "640412";
        else if (id >= 701 && id <= 800)
            advisorId = "640913";
        else if (id >= 801 && id <= 900)
            advisorId = "640515";
        else if (id >= 901 && id <= 1000)
            advisorId = "640627";

        cout << "[INFO] Your Advisor's ID: " << advisorId << endl;
    }
};

class StudentPortal
{
private:
    Admin &admin;

public:
    StudentPortal(Admin &adminRef) : admin(adminRef) {}

    void enrollInCourse(string studentName, string studentId, string courseId)
    {
        string grade;
        if (admin.isCourseExists(courseId))
        {
            cout << "[INFO] Enter Grade for Student: ";
            getline(cin, grade);
            admin.registerStudentForCourse(studentName, studentId, courseId, grade);
        }
        else
        {
            cout << "\n[ERROR] Course ID: " << courseId << " does not exist.\n";
        }
    }

    void viewEnrolledCourses(string studentId)
    {
        cout << "\n[INFO] Courses Enrolled by Student ID: " << studentId << ":\n";
        bool found = false;
        for (auto &course : admin.getCourseRegistrations())
        {
            for (auto &student : course.second)
            {
                if (student.id == studentId)
                {
                    cout << "Course ID: " << student.courseId << ", Grade: " << student.grade << "\n";
                    found = true;
                }
            }
        }
        if (!found)
        {
            cout << "[INFO] No courses found for the given Student ID.\n";
        }
    }

    void viewTopPerformingStudentsInCourse(string courseId)
    {
        admin.viewTopPerformingStudents(courseId);
    }

    void viewAdvisor(string studentId)
    {
        admin.viewAdvisor(studentId);
    }
};

bool adminLogin()
{
    string username, password;
    cout << "\n[INFO] Admin Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    return username == "admin" && password == "admin123";
}

int main()
{
    Admin admin;
    StudentPortal studentPortal(admin);
    int choice;

    while (true)
    {
        cout << "\n=== Welcome to the Student Database Management System ===\n";
        cout << "1. Admin Section\n2. Student Section\n3. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            if (!adminLogin())
            {
                cout << "\n[ERROR] Invalid credentials. Please try again.\n";
                continue;
            }

            int adminChoice;
            while (true)
            {
                cout << "\n=== Admin Portal ===\n";
                cout << "1. Add Course\n2. Delete Course\n3. View All Courses\n4. Register Student for Course\n5. View Top Performing Students\n6. Generate Advisor Files\n7. View Advisor\n8. Logout\nEnter your choice: ";
                cin >> adminChoice;
                cin.ignore();

                if (adminChoice == 1)
                {
                    string name, id;
                    cout << "Enter Course Name: ";
                    getline(cin, name);
                    cout << "Enter Course ID: ";
                    getline(cin, id);
                    admin.addCourse(name, id);
                }
                else if (adminChoice == 2)
                {
                    string courseId;
                    cout << "Enter Course ID to Delete: ";
                    getline(cin, courseId);
                    admin.deleteCourse(courseId);
                }
                else if (adminChoice == 3)
                {
                    admin.viewCourses();
                }
                else if (adminChoice == 4)
                {
                    string studentName, studentId, courseId, grade;
                    cout << "Enter Student Name: ";
                    getline(cin, studentName);
                    cout << "Enter Student ID: ";
                    getline(cin, studentId);
                    cout << "Enter Course ID: ";
                    getline(cin, courseId);
                    cout << "Enter Grade: ";
                    getline(cin, grade);
                    admin.registerStudentForCourse(studentName, studentId, courseId, grade);
                }
                else if (adminChoice == 5)
                {
                    string courseId;
                    cout << "Enter Course ID: ";
                    getline(cin, courseId);
                    admin.viewTopPerformingStudents(courseId);
                }
                else if (adminChoice == 6)
                {
                    admin.generateAdvisorFiles();
                }
                else if (adminChoice == 7)
                {
                    string studentId;
                    cout << "Enter Student ID: ";
                    getline(cin, studentId);
                    admin.viewAdvisor(studentId);
                }
                else if (adminChoice == 8)
                {
                    break;
                }
                else
                {
                    cout << "[ERROR] Invalid choice. Please try again.\n";
                }
            }
        }
        else if (choice == 2)
        {
            string studentName, studentId;
            cout << "[INFO] Student Portal\n";
            cout << "Enter your Name: ";
            getline(cin, studentName);
            cout << "Enter your Student ID: ";
            getline(cin, studentId);

            int studentChoice;
            while (true)
            {
                cout << "\n=== Student Portal ===\n";
                cout << "1. Enroll in Course\n2. View Enrolled Courses\n3. View Top Performing Students in Course\n4. View Advisor\n5. Exit\nEnter your choice: ";
                cin >> studentChoice;
                cin.ignore();

                if (studentChoice == 1)
                {
                    string courseId;
                    cout << "Enter Course ID to Enroll in: ";
                    getline(cin, courseId);
                    studentPortal.enrollInCourse(studentName, studentId, courseId);
                }
                else if (studentChoice == 2)
                {
                    studentPortal.viewEnrolledCourses(studentId);
                }
                else if (studentChoice == 3)
                {
                    string courseId;
                    cout << "Enter Course ID: ";
                    getline(cin, courseId);
                    studentPortal.viewTopPerformingStudentsInCourse(courseId);
                }
                else if (studentChoice == 4)
                {
                    studentPortal.viewAdvisor(studentId);
                }
                else if (studentChoice == 5)
                {
                    break;
                }
                else
                {
                    cout << "[ERROR] Invalid choice. Please try again.\n";
                }
            }
        }
        else if (choice == 3)
        {
            cout << "\n[INFO] Exiting the system. Goodbye!\n";
            break;
        }
        else
        {
            cout << "[ERROR] Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
