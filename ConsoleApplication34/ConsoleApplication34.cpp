#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum Specialization {
    ComputerScience,
    Mathematics,
    Physics,
    Biology,
    Chemistry,
    UnknownSpecialization
};

class Date {
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(1900) {}

    void SetDay(int day) {
        this->day = day;
    }

    int GetDay() const {
        return day;
    }

    void SetMonth(int month) {
        this->month = month;
    }

    int GetMonth() const {
        return month;
    }

    void SetYear(int year) {
        this->year = year;
    }

    int GetYear() const {
        return year;
    }
};

class Student {
    string last_name;
    string first_name;
    string middle_name;
    Date birth_date;
    string home_address;
    string phone_number;
    int* grades_math;
    int* grades_physical_education;
    int* grades_chemistry;
    int num_grades_math;
    int num_grades_physical_education;
    int num_grades_chemistry;

public:
    Student(string first, string last) : first_name(first), last_name(last),
        grades_math(nullptr), grades_physical_education(nullptr), grades_chemistry(nullptr),
        num_grades_math(0), num_grades_physical_education(0), num_grades_chemistry(0) {}

    void SetBirthDate(const Date& date) {
        birth_date = date;
    }

    Date GetBirthDate() const {
        return birth_date;
    }

    void SetHomeAddress(const string& address) {
        home_address = address;
    }

    string GetHomeAddress() const {
        return home_address;
    }

    void SetPhoneNumber(const string& phone) {
        phone_number = phone;
    }

    string GetPhoneNumber() const {
        return phone_number;
    }

    void SetLastName(const string& last) {
        last_name = last;
    }

    string GetLastName() const {
        return last_name;
    }

    void SetFirstName(const string& first) {
        first_name = first;
    }

    string GetFirstName() const {
        return first_name;
    }

    void AddMathGrade(int grade) {
        if (grades_math == nullptr) {
            grades_math = new int[100];
        }
        grades_math[num_grades_math++] = grade;
    }

    int GetMathGrade(int subject_index) const {
        return grades_math[subject_index];
    }

    void AddPhysicalEducationGrade(int grade) {
        if (grades_physical_education == nullptr) {
            grades_physical_education = new int[100];
        }
        grades_physical_education[num_grades_physical_education++] = grade;
    }

    int GetPhysicalEducationGrade(int subject_index) const {
        return grades_physical_education[subject_index];
    }

    void AddChemistryGrade(int grade) {
        if (grades_chemistry == nullptr) {
            grades_chemistry = new int[100];
        }
        grades_chemistry[num_grades_chemistry++] = grade;
    }

    int GetChemistryGrade(int subject_index) const {
        return grades_chemistry[subject_index];
    }

    ~Student() {
        delete[] grades_math;
        delete[] grades_physical_education;
        delete[] grades_chemistry;
    }
};

class Group {
    vector<Student*> students;
    int num_students;
    string group_name;
    Specialization specialization;
    int course_number;

public:
    Group() : num_students(0), group_name("unknown"), specialization(UnknownSpecialization), course_number(0) {}

    Group(const Group& other) {
        this->num_students = other.num_students;
        this->group_name = other.group_name;
        this->specialization = other.specialization;
        this->course_number = other.course_number;

        for (int i = 0; i < num_students; ++i) {
            Student* new_student = new Student(*(other.students[i]));
            students.push_back(new_student);
        }
    }

    Student* GetStudent(int index) const {
        if (index >= 0 && index < num_students) {
            return students[index];
        }
        else {
            return nullptr;
        }
    }

    int GetNumStudents() const {
        return num_students;
    }

    string GetGroupName() const {
        return group_name;
    }

    void SetGroupName(const string& name) {
        group_name = name;
    }

    string GetSpecialization() const {
        switch (specialization) {
        case ComputerScience:
            return "Computer Science";
        case Mathematics:
            return "Mathematics";
        case Physics:
            return "Physics";
        case Biology:
            return "Biology";
        case Chemistry:
            return "Chemistry";
        default:
            return "Unknown Specialization";
        }
    }

    void SetSpecialization(Specialization spec) {
        specialization = spec;
    }

    int GetCourseNumber() const {
        return course_number;
    }

    void SetCourseNumber(int course) {
        course_number = course;
    }

    void ShowAllStudents() const {
        cout << "Group: " << group_name << " Specialization: " << GetSpecialization() << " Course: " << course_number << "\n";

        cout << "Students:\n";
        for (int i = 0; i < num_students; ++i) {
            cout << "[" << i + 1 << "] " << students[i]->GetLastName() << " " << students[i]->GetFirstName() << "\n";
        }
    }

    void AddStudent(Student* new_student) {
        students.push_back(new_student);
        num_students++;
    }

    static Group MergeGroups(const Group& group1, const Group& group2) {
        Group merged_group;
        merged_group.SetGroupName(group1.GetGroupName() + "_" + group2.GetGroupName());

        for (int i = 0; i < group1.GetNumStudents(); ++i) {
            Student* student_copy = new Student(*(group1.GetStudent(i)));
            merged_group.AddStudent(student_copy);
        }

        for (int i = 0; i < group2.GetNumStudents(); ++i) {
            Student* student_copy = new Student(*(group2.GetStudent(i)));
            merged_group.AddStudent(student_copy);
        }
        return merged_group;
    }

    void TransferStudent(int student_index, Group& target_group) {
        if (student_index >= 0 && student_index < num_students) {
            Student* student_to_transfer = students[student_index];

            students.erase(students.begin() + student_index);
            num_students--;

            target_group.AddStudent(student_to_transfer);

            cout << "Студент " << student_to_transfer->GetLastName() << " переведен в группу " << target_group.GetGroupName() << endl;
        }
        else {
            cout << "Неправильный индекс студента для перевода." << endl;
        }
    }

    void ExpelStudentsWithFailures() {
        for (int i = 0; i < num_students; ++i) {
            if (HasFailedExams(students[i])) {
                ExpelStudent(i);
                --i;
            }
        }
    }

private:
    bool HasFailedExams(Student* student) const {
        for (int i = 0; i < 100; ++i) {
            if (student->GetMathGrade(i) < 60 || student->GetPhysicalEducationGrade(i) < 60 || student->GetChemistryGrade(i) < 60) {
                return true;
            }
        }
        return false;
    }

    void ExpelStudent(int student_index) {
        if (student_index >= 0 && student_index < num_students) {
            delete students[student_index];
            students.erase(students.begin() + student_index);
            --num_students;
            cout << "Студент отчислен из группы." << endl;
        }
        else {
            cout << "Неправильный индекс студента для отчисления." << endl;
        }
    }

    void ExpelWorstStudent() {
        if (num_students == 0) {
            cout << "Группа пуста. Невозможно отчислить студента." << endl;
            return;
        }

        int worstStudentIndex = 0;
        double worstStudentAverage = CalculateAverageGrade(students[0]);

        for (int i = 1; i < num_students; ++i) {
            double currentAverage = CalculateAverageGrade(students[i]);
            if (currentAverage < worstStudentAverage) {
                worstStudentAverage = currentAverage;
                worstStudentIndex = i;
            }
        }

        ExpelStudent(worstStudentIndex);

        cout << "Студент с наихудшими оценками отчислен." << endl;
    }

};

int main() {
    setlocale(LC_ALL, "");

    Student student("Антон", "Васильев");

    Date birth_date;
    birth_date.SetDay(1);
    birth_date.SetMonth(1);
    birth_date.SetYear(2000);

    student.SetBirthDate(birth_date);
    student.SetHomeAddress("ул. Добровольского, 123");
    student.SetPhoneNumber("+38(097)264-18-54");

    student.AddMathGrade(95);
    student.AddMathGrade(88);

    student.AddPhysicalEducationGrade(85);
    student.AddPhysicalEducationGrade(90);

    student.AddChemistryGrade(75);
    student.AddChemistryGrade(80);

    cout << "Измененная фамилия: " << student.GetLastName() << endl;
    cout << "Измененный телефонный номер: " << student.GetPhoneNumber() << endl;

    return 0;
}
