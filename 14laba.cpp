#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <clocale>

using namespace std;

template <typename T>
int countOccurrences(const T arr[], int size, const T& target) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}


template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void input() {
        cout << "Enter elements of the matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }

    T getSum() const {
        T sum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sum += data[i][j];
            }
        }
        return sum;
    }

    T getMax() const {
        T maxVal = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] > maxVal) {
                    maxVal = data[i][j];
                }
            }
        }
        return maxVal;
    }
};

class Product {
private:
    string name;
    double price;
    int quantity;

public:
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    bool operator<(const Product& other) const {
        return this->price < other.price;
    }

    void display() const {
        cout << "Product: " << name << " | Price: " << price << " | Quantity: " << quantity << "\n";
    }
};

int main() {

    setlocale(LC_ALL, "Ukranian");
    int intSize;
    cout << "Enter array size: ";
    cin >> intSize;
    int* intArr = new int[intSize];
    cout << "Enter " << intSize << " integers: ";
    for (int i = 0; i < intSize; ++i) std::cin >> intArr[i];
    int intTarget;
    cout << "Enter a number to search for: ";
    cin >> intTarget;
    cout << "Result: Found " << countOccurrences(intArr, intSize, intTarget) << " occurrences.";
    delete[] intArr;

    int charSize;
    cout << "Enter array size: ";
    cin >> charSize;
    char* charArr = new char[charSize];
    cout << "Enter " << charSize << " characters : ";
    for (int i = 0; i < charSize; ++i) std::cin >> charArr[i];
    char charTarget;
    cout << "Enter a character to search for: ";
    cin >> charTarget;
    cout << "Result: Found " << countOccurrences(charArr, charSize, charTarget) << " occurrences.\n";
    delete[] charArr;

   
    int doubleSize;
    cout << " Enter array size: ";
    cin >> doubleSize;
    double* doubleArr = new double[doubleSize];
    cout << "Enter " << doubleSize << " real numbers: ";
    for (int i = 0; i < doubleSize; ++i) std::cin >> doubleArr[i];
    double doubleTarget;
    cout << "Enter a number to search for: ";
    cin >> doubleTarget;
    cout << "Result: Found " << countOccurrences(doubleArr, doubleSize, doubleTarget) << " occurrences.\n";
    delete[] doubleArr;

    cout << "\n Matrix 2x3:\n";
    Matrix<int> intMatrix(2, 3);
    intMatrix.input();
    cout << "Your matrix:\n";
    intMatrix.print();
    cout << "Sum of elements: " << intMatrix.getSum() << "\n";
    cout << "Maximum element: " << intMatrix.getMax() << "\n";

    vector<Product> products;
    int prodCount;
    cout << "Enter the number of products to add to the cart: ";
    cin >> prodCount;

    for (int i = 0; i < prodCount; ++i) {
        string name;
        double price;
        int qty;
        cout << "Product " << i + 1 << " (Name Price Quantity): ";
        cin >> name >> price >> qty;
        products.push_back(Product(name, price, qty));
    }

    sort(products.begin(), products.end());

    cout << "\nList of products:\n";
    for (auto it = products.begin(); it != products.end(); ++it) {
        it->display();
    }

    if (!products.empty()) {
        cout << "\nThe most expensive product: \n";
        products.back().display(); 
    }

    for (auto it = products.begin(); it != products.end(); ) {
        if (it->getQuantity() == 0) {
            it = products.erase(it); //
        } else {
            ++it;
        }
    }
    cout << "\nList of remaining products:\n";
    int totalRemainingQty = 0;
    for (auto it = products.begin(); it != products.end(); ++it) {
        it->display();
        totalRemainingQty += it->getQuantity();
    }
    cout << "Remaining quantity: " << totalRemainingQty << " шт.\n";
    return 0;
}