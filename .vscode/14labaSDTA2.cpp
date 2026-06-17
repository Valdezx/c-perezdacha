#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
};


void printCatalog(const vector<Book>& catalog) {
    if (catalog.empty()) {
        cout << "\nКаталог бібліотеки порожній.\n";
        return;
    }

    cout << left << setw(30) << "Назва книги" 
              << setw(25) << "Автор" 
              << std::setw(10) << "Рік видання" << "\n";
    for (const auto& book : catalog) {
        cout << std::left << std::setw(30) << book.title 
                  << std::setw(25) << book.author 
                  << std::setw(10) << book.year << "\n";
    }
}

void addBook(std::vector<Book>& catalog) {
    Book newBook;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищення буфера

    cout << "Введіть назву книги: ";
    getline(cin, newBook.title);

    cout << "Введіть автора книги: ";
    getline(std::cin, newBook.author);

    cout << "Введіть рік видання: ";
    while (!(cin >> newBook.year) || newBook.year < 0 || newBook.year > 2026) {
        cout << "Некоректний рік. Введіть ще раз: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    catalog.push_back(newBook);
}

void deleteBookByTitle(std::vector<Book>& catalog) {
    if (catalog.empty()) {
        cout << "Каталог порожній. Нічого видаляти.\n";
        return;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string titleToDelete;
    cout << "Введіть точну назву книги для видалення: ";
    getline(cin, titleToDelete);
    auto it = std::remove_if(catalog.begin(), catalog.end(), [&titleToDelete](const Book& book) {
        return book.title == titleToDelete;
    });

    if (it != catalog.end()) {
        catalog.erase(it, catalog.end());
        std::cout << "Книгу(и) з назвою \"" << titleToDelete << "\" видалено.\n";
    } else {
        std::cout << "Книгу з такою назвою не знайдено.\n";
    }
}
void findBooksByAuthor(const vector<Book>& catalog) {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string authorToFind;
    cout << "Введіть ім'я автора для пошуку: ";
    getline(std::cin, authorToFind);
    vector<Book> foundBooks;
    for (const auto& book : catalog) {
        if (book.author == authorToFind) {
            foundBooks.push_back(book);
        }
    }

    cout << "\nРезультати пошуку для автора \"" << authorToFind << "\":";
    printCatalog(foundBooks);
}

void saveToFile(const vector<Book>& catalog, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Помилка відкриття файлу для запису!\n";
        return;
    }

    file << catalog.size() << "\n";
    for (const auto& book : catalog) {
        file << book.title << "\n";
        file << book.author << "\n";
        file << book.year << "\n";
    }

    file.close();
    cout << "Каталог успішно збережено у файл \"" << filename << "\".\n";
}

void loadFromFile(vector<Book>& catalog, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл бази даних не знайдено. Буде створено новий каталог.\n";
        return;
    }

    size_t size = 0;
    if (!(file >> size)) return;
    file.ignore(); 
    catalog.clear(); 
    for (size_t i = 0; i < size; ++i) {
        Book book;
        getline(file, book.title);
        getline(file, book.author);
        file >> book.year;
        file.ignore(); 
        
        catalog.push_back(book);
    }
    file.close();
    cout << "Каталог успішно завантажено з файлу! Знайдено книг: " << size << "\n";
}
int main() {
    setlocale(LC_ALL, "Ukranian");
    vector<Book> library;
    const std::string filename = "library_db.txt";
    loadFromFile(library, filename);
    int choice;
    do {
        cout << "1. Показати всі книги\n";
        cout << "2. Додати книгу\n";
        cout << "3. Видалити книгу за назвою\n";
        cout << "4. Сортувати за автором\n";
        cout << "5. Сортувати за роком видання\n";
        cout << "6. Пошук книг за автором\n";
        cout << "7. Зберегти зміни у файл\n";
        cout << "8. Вийти з програми\n";
        cout << "Оберіть дію (1-8): ";

        while (!(std::cin >> choice) || choice < 1 || choice > 8) {
            std::cout << "Некоректний вибір. Введіть число від 1 до 8: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                printCatalog(library);
                break;
            case 2:
                addBook(library);
                break;
            case 3:
                deleteBookByTitle(library);
                break;
            case 4:
                std::sort(library.begin(), library.end(), [](const Book& a, const Book& b) {
                    return a.author < b.author;
                });
                cout << "Каталог відсортовано за автором.\n";
                printCatalog(library);
                break;
            case 5:
                sort(library.begin(), library.end(), [](const Book& a, const Book& b) {
                    return a.year < b.year;
                });
                cout << "Каталог відсортовано за роком видання.\n";
                printCatalog(library);
                break;
            case 6:
                findBooksByAuthor(library);
                break;
            case 7:
                saveToFile(library, filename);
                break;
        }
    } while (choice != 8);
    saveToFile(library, filename);
    return 0;
}