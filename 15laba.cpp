#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>
#include <clocale>

using namespace std; 

class MultiValidationException : public std::exception {
private:
    std::vector<std::string> errors;
public:
    MultiValidationException(const std::vector<std::string>& errList) : errors(errList) {}
    const std::vector<std::string>& getErrors() const {
        return errors;
    }

    const char* what() const noexcept override {
        return "Error!";
    }
};


class Transport {
protected:
    std::string brand;
    int year;

public:
    Transport(std::string b, int y) : brand(b), year(y) {

    }

    virtual void display() const {
        std::cout << "Mark: " << brand << " | Year: " << year;
    }
};

class Car : public Transport {
private:
    double price;
    double engineVolume;

public:
    Car(std::string b, int y, double p, double ev) : Transport(b, y), price(p), engineVolume(ev) {
        std::vector<std::string> validationErrors;
        if (brand.empty()) {
            validationErrors.push_back("Error: Transport brand cannot be empty!");
        }
        if (year < 1886 || year > 2026) {
            validationErrors.push_back("Error: Release year must be between 1886 and 2026!");
        }
        if (price <= 0) {
            validationErrors.push_back("Error: Price must be a positive number!");
        }
        if (engineVolume <= 0) {
            validationErrors.push_back("Error: Engine volume must be a positive number!");
        }

        if (!validationErrors.empty()) {
            throw MultiValidationException(validationErrors);
        }
    }

    void display() const override {
        Transport::display();
        std::cout << " | Price: $" << price << " | Engine Volume: " << engineVolume << " l\n";
    }

    friend void comparePrice(const Car& car1, const Car& car2);
};


void comparePrice(const Car& car1, const Car& car2) {
    if (car1.price > car2.price) {
        std::cout << car1.brand << " (" << car1.year << ") More expensive than " << car2.brand << ".\n";
    } else if (car1.price < car2.price) {
        std::cout << car2.brand << " (" << car2.year << ") More expensive than " << car1.brand << ".\n";
    } else {
        std::cout << "Both cars have the same price: $" << car1.price << ".\n";
    }
}

int main() {
    std::setlocale(LC_ALL, "Ukranian");
    
    double x;
    std::cout << "Enter x: ";
    std::cin >> x;

    try {
        if (x < 0) {
            throw std::domain_error("Mathematical domain error: The expression under the square root is negative (x < 0)!");
        }
        if (x == 0) {
            throw std::runtime_error("Division by zero error: The denominator becomes 0 (x = 0)!");
        }

        double y = 1.0 / std::sqrt(x);
        std::cout << "Success! The value of the expression y = " << y << "\n";
    }
    catch (const std::domain_error& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    try {
        Car car1("BMW M5", 2021, 75000, 4.4);
        Car car2("Lexus RX", 2023, 62000, 2.4);

        car1.display();
        car2.display();

        comparePrice(car1, car2);
    }
    catch (const MultiValidationException& e) {
        std::cerr << e.what() << "\n";
    }

    try {
        Car brokenCar("", 1700, -500, 0);
        brokenCar.display(); 
    }
    catch (const MultiValidationException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << "Full list of detected violations:\n";

        const auto& errors = e.getErrors();
        for (const auto& errMsg : errors) {
            cerr << " -> " << errMsg << "\n";
        }
    }

    return 0;
}