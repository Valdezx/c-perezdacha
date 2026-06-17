#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <stdlib.h>

using namespace std;

void addStudent(multimap<int, string>& students) {
    int course;
    string lastName;

    cout << "Введіть номер курсу (1-6): ";
    while (!(cin >> course) || course < 1 || course > 6) {
        cout << "Некоректний курс. Введіть число від 1 до 6: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    cout << "Введіть прізвище студента: ";
    getline(cin, lastName);

    students.insert({course, lastName});
    cout << "Студента успішно додано!\n";
}

void printStudentsOfCourse(const std::multimap<int, std::string>& students) {
    if (students.empty()) {
        cout << "База даних порожня.\n";
        return;
    }

    int course;
    cout << "Введіть номер курсу для перегляду: ";
    cin >> course;
    auto range = students.equal_range(course);
    if (range.first == range.second) {
        std::cout << "На " << course << "-му курсі немає студентів.\n";
        return;
    }

    cout << "\nСтуденти " << course << "-го курсу:\n";
    for (auto it = range.first; it != range.second; ++it) {
        cout << "- " << it->second << "\n";
    }
}

void printAllStudentsGrouped(const std::multimap<int, std::string>& students) {
    if (students.empty()) {
        cout << "База даних порожня.\n";
        return;
    }

    cout << "\n=== Список студентів за курсами ===\n";
    
    int currentCourse = -1;
    for (const auto& pair : students) {
        if (pair.first != currentCourse) {
            currentCourse = pair.first;
            std::cout << "\nКурс " << currentCourse << ":\n";
        }
        std::cout << "  " << pair.second << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Ukranian");
    multimap<int, string> studentMap;

    int choice;
    do {
        cout << "1. Додати студента\n";
        cout << "2. Вивести список студентів конкретного курсу\n";
        cout << "3. Вивести всіх студентів (згрупованих за курсами)\n";
        cout << "4. Вийти\n";
        cout << "Оберіть дію (1-4): ";

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Некоректний вибір. Введіть число від 1 до 4: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (choice) {
            case 1: addStudent(studentMap); break;
            case 2: printStudentsOfCourse(studentMap); break;
            case 3: printAllStudentsGrouped(studentMap); break;
        }
    } while (choice != 4);
    return 0;
}