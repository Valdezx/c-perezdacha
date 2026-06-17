#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <clocale>
#include <queue>

using namespace std;

struct PrintJob {
    std::string documentName;
    int pagesCount;
    PrintJob* next;
};


void pushQueue(PrintJob*& front, PrintJob*& rear, std::string name, int pages) {
    PrintJob* newJob = new PrintJob;
    newJob->documentName = name;
    newJob->pagesCount = pages;
    newJob->next = nullptr;

    if (front == nullptr) { 
        front = rear = newJob;
    } else {
        rear->next = newJob;
        rear = newJob;
    }
    std::cout << "Додано до черги: " << name << " (" << pages << " стор.)\n";
}

void popQueue(PrintJob*& front, PrintJob*& rear) {
    if (front == nullptr) {
        std::cout << "Черга порожня, немає чого видаляти.\n";
        return;
    }
    PrintJob* temp = front;
    front = front->next;

    if (front == nullptr) { 
        rear = nullptr;
    }

    std::cout << "Видалено з черги (пущено на друк): " << temp->documentName << "\n";
    delete temp; 
}

// Виведення поточного порядку черги
void printQueue(PrintJob* front) {
    if (front == nullptr) {
        std::cout << "Черга друку порожня.\n";
        return;
    }
    std::cout << "\nПоточний порядок друку:\n";
    PrintJob* current = front;
    int index = 1;
    while (current != nullptr) {
        std::cout << index << ". " << current->documentName << " — " << current->pagesCount << " стор.\n";
        current = current->next;
        index++;
    }
    std::cout << "\n";
}

// Повне вивільнення пам'яті черги
void clearQueue(PrintJob*& front, PrintJob*& rear) {
    while (front != nullptr) {
        popQueue(front, rear);
    }
}




// Елемент стеку
struct StackNode {
    char data;
    StackNode* next;
};

// Додавання символу на вершину стеку
void pushStack(StackNode*& top, char character) {
    StackNode* newNode = new StackNode;
    newNode->data = character;
    newNode->next = top;
    top = newNode;
}

// Видалення символу з вершини стеку
void popStack(StackNode*& top) {
    if (top == nullptr) return;
    StackNode* temp = top;
    top = top->next;
    delete temp; // Вивільнення пам'яті
}

// Отримання символу з вершини без його видалення
char getTopStack(StackNode* top) {
    if (top == nullptr) return '\0';
    return top->data;
}

// Повне очищення стеку
void clearStack(StackNode*& top) {
    while (top != nullptr) {
        popStack(top);
    }
}



int main() {
    std::setlocale(LC_ALL, "Ukranian");



    PrintJob* queueFront = nullptr;
    PrintJob* queueRear = nullptr;
    int n;

    std::cout << "Введіть кількість документів (n): ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string docName;
        int pages;
        std::cout << "Документ " << i + 1 << " (Назва Кількість_сторінок): ";
        std::cin >> docName >> pages;
        pushQueue(queueFront, queueRear, docName, pages);
    }

    printQueue(queueFront);

    popQueue(queueFront, queueRear);

    printQueue(queueFront);

    clearQueue(queueFront, queueRear);


    StackNode* stackTop = nullptr;
    std::string userString;

    std::cin.ignore(256, '\n'); 

    std::cout << "Введіть текстовий рядок: ";
    std::getline(std::cin, userString);

    std::string cleanStr = "";
    for (char ch : userString) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            cleanStr += std::tolower(static_cast<unsigned char>(ch));
        }
    }

    for (char ch : cleanStr) {
        pushStack(stackTop, ch);
    }

    bool isPalin = true;
    for (char ch : cleanStr) {
        if (ch != getTopStack(stackTop)) {
            isPalin = false;
            break; 
        }
        popStack(stackTop); 
    }


    std::cout << "Порядок друку/перевірки символів завершено.\n";
    if (isPalin) {
        std::cout << "Результат: Рядок є паліндромом!\n";
    } else {
        std::cout << "Результат: Рядок НЕ є паліндромом.\n";
    }

    clearStack(stackTop);
  
    return 0;
}