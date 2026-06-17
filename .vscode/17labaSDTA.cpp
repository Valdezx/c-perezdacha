#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct Book {
    string title;
    int year;
    double ratings[5];
    double averageRating; 
};

void calculateAverageRating(Book& book) {
    double sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += book.ratings[i];
    }
    book.averageRating = sum / 5.0;
}
void printBooks(const std::vector<Book>& books, const std::string& message) {
    std::cout << "\n--- " << message << " ---\n";
    std::cout << std::left << std::setw(25) << "Назва книги" 
              << std::setw(15) << "Рік видання" 
              << std::setw(20) << "Оцінки читачів" 
              << std::setw(15) << "Сер. рейтинг" << "\n";
    
    for (const auto& book : books) {
        std::cout << std::left << std::setw(25) << book.title 
                  << std::setw(15) << book.year;

        std::string ratingsStr = "";
        for (int i = 0; i < 5; ++i) {
            ratingsStr += std::to_string(book.ratings[i]) + (i < 4 ? "," : "");
        }
        std::cout << std::setw(20) << ratingsStr;
        
        std::cout << std::fixed << std::setprecision(2) << book.averageRating << "\n";
    }
}
void insertionSortByRatingAsc(std::vector<Book>& books) {
    int n = books.size();
    for (int i = 1; i < n; ++i) {
        Book key = books[i];
        int j = i - 1;

        while (j >= 0 && books[j].averageRating > key.averageRating) {
            books[j + 1] = books[j];
            j = j - 1;
        }
        books[j + 1] = key;
    }
}
void gnomeSortByYearDesc(std::vector<Book>& books) {
    int n = books.size();
    int index = 0;
    
    while (index < n) {
        if (index == 0) {
            index++;
        }

        if (books[index].year <= books[index - 1].year) {
            index++;
        } else {
            std::swap(books[index], books[index - 1]);
            index--;
        }
    }
}

void linearSearchByYear(const std::vector<Book>& books, int searchYear) {
    std::vector<Book> results;
    for (const auto& book : books) {
        if (book.year == searchYear) {
            results.push_back(book);
        }
    }
    if (results.empty()) {
        std::cout << "\n[Пошук] Книг " << searchYear << " року видання не знайдено.\n";
    } else {
        printBooks(results, "Результати пошуку для року " + std::to_string(searchYear));
    }
}
int main() {
    std::setlocale(LC_ALL, "Ukranian");

    std::vector<Book> library = {
        {"Кобзар", 2015, {5, 4, 5, 5, 4}, 0.0},
        {"Тіні забутих предків", 2008, {4, 3, 4, 5, 4}, 0.0},
        {"Захар Беркут", 2020, {5, 5, 5, 4, 5}, 0.0},
        {"Місто", 2012, {3, 4, 3, 4, 3}, 0.0},
        {"Кайдашева сім'я", 2015, {5, 4, 4, 5, 4}, 0.0}
    };
    for (auto& book : library) {
        calculateAverageRating(book);
    }
    printBooks(library, "Початковий каталог (Розраховано середній рейтинг)");
    insertionSortByRatingAsc(library);
    printBooks(library, "Масив, відсортований ВСТАВКАМИ (за зростанням рейтингу)");
    std::vector<Book> libraryCopy = library;
    gnomeSortByYearDesc(libraryCopy);
    int searchYear;
    std::cout << "\nВведіть рік видання для пошуку книг: ";
    while (!(std::cin >> searchYear) || searchYear < 0) {
        std::cout << "Некоректне введення року. Спробуйте ще раз: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    linearSearchByYear(library, searchYear);
    return 0;
}