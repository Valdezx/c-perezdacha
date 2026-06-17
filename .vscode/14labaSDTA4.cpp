#include <iostream>
#include <list>
#include <limits>
#include <stdlib.h>

using namespace std;

void printList(const list<int>& myList, const string& listName) {
    cout << listName << ": [ ";
    for (int val : myList) {
        cout << val << " ";
    }
    cout << "]\n";
}

int main() {
    std::setlocale(LC_ALL, "Ukranian");

    list<int> list1;
    list<int> list2;
    list1.push_back(10);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(5);   
    list1.push_back(12);
    list1.push_back(3);
    list1.push_back(8);   
    printList(list1, "Початковий список 1");

    list1.remove_if([](int n) { return n % 2 == 0; });
    printList(list1, "Список 1 після видалення парних");
    list1.sort();
    printList(list1, "Відсортований список 1");
    list1.unique();
    printList(list1, "Список 1 без повторів");
    list2.push_back(15);
    list2.push_back(1);
    list2.push_back(7);
    list2.sort(); 
    printList(list2, "Відсортований список 2");
    list1.merge(list2); 
    printList(list1, "Фінальний об'єднаний список");
    printList(list2, "Стан списку 2 після об'єднання");
    return 0;
}