#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Room{
 public:
 int number;
 int BasePrice;
 double TotalPrice;
 int days;
    virtual void showInfo(){
        cout << "Room number: " << number << "\n";
        cout << "Base price per day: " << BasePrice << "\n";
        cout << "Number of days: " << days << "\n";
    }
    virtual double calculateCost(){
        return TotalPrice= BasePrice * days;
    }
};
class StandardRoom : public Room{
public:
StandardRoom(int num, int base, int d, int count, int price) {
    number = num;
    BasePrice = base;
    days = d;
     CountOfBreakfasts = count;
     PriceOfBreakfast = price;
}
int CountOfBreakfasts;
int PriceOfBreakfast;
    void showInfo() override {
        cout << "Standard Room:\n";
        Room::showInfo();
    }
    double calculateCost() override {
        return TotalPrice = BasePrice * days+ CountOfBreakfasts * PriceOfBreakfast;
    }
};
class LuxuryRoom : public Room{
public:
LuxuryRoom(int num, int base, int d, double comfort, double price) {
    number = num;
    BasePrice = base;
    days = d;
     Comfortlevel = comfort;
     PriceOfService = price;
}
double Comfortlevel;
double PriceOfService;
double calculateCost() override {
    return TotalPrice = BasePrice * days+  Comfortlevel * PriceOfService;
}
    void showInfo() override {
        cout << "Luxury Room:\n";
        Room::showInfo();
    }
};
class SuiteRoom : public Room{
public:
SuiteRoom(int num, int base, int d, double prestige, int transfer, double other) {
    number = num;
    BasePrice = base;
    days = d;
     PrestigeLevel = prestige;
     TransferPrice = transfer;
     OtherServicesPrice = other;
}
double PrestigeLevel;
int TransferPrice;
double OtherServicesPrice;
double calculateCost() override {
    return TotalPrice = BasePrice * days+ PrestigeLevel * TransferPrice+ OtherServicesPrice;
}
    void showInfo() override {
        cout << "Suite Room:\n";
        Room::showInfo();
    }
};
double calculateTotalRevenue(const vector<Room*>& rooms) {
    double totalRevenue = 0.0;
    for (const auto& room : rooms) {
        totalRevenue += room->calculateCost();
    }
    return totalRevenue;
}
double calculateAverageRevenue(const vector<Room*>& rooms) {
    if (rooms.empty()) return 0.0;
    return calculateTotalRevenue(rooms) / rooms.size();
}
double HighestPrice(const vector<Room*>& rooms) {
    double highest = 0.0;
    for (const auto& room : rooms) {
        double cost = room->calculateCost();
        if (cost > highest) {
            highest = cost;
        }
    }
    return highest;
}
double TotalStandardRoomCost(const vector<Room*>& rooms) {
    double total = 0.0;
    for (const auto& room : rooms) {
        if (dynamic_cast<StandardRoom*>(room)) {
            total += room->calculateCost();
        }
    }
    return total;
}
double TotalLuxuryRoomCost(const vector<Room*>& rooms) {
    double total = 0.0;
    for (const auto& room : rooms) {
        if (dynamic_cast<LuxuryRoom*>(room)) {
            total += room->calculateCost();
        }
    }
    return total ;
}
double TotalSuiteRoomCost(const vector<Room*>& rooms) {
    double total = 0.0;
    for (const auto& room : rooms) {
        if (dynamic_cast<SuiteRoom*>(room)) {
            total += room->calculateCost();
        }
    }
    return total;
}

int main()
{
vector<Room*> rooms;
rooms.push_back(new StandardRoom(101, 100, 3, 3, 20));
rooms.push_back(new LuxuryRoom(202, 200, 2, 1.5, 50));
rooms.push_back(new SuiteRoom(303, 300, 4, 2.0, 100, 150));
rooms.push_back(new StandardRoom(102, 120, 5, 5, 25));
rooms.push_back(new LuxuryRoom(203, 250, 1, 2.0, 60));

cout << "Total Revenue: " << calculateTotalRevenue(rooms) << endl;
cout << "Average Revenue: " << calculateAverageRevenue(rooms) << endl;
cout << "Highest Price: " << HighestPrice(rooms) << endl;
cout << "Total Standard Room Cost: " << TotalStandardRoomCost(rooms) << endl;
cout << "Total Luxury Room Cost: " << TotalLuxuryRoomCost(rooms) << endl;
cout << "Total Suite Room Cost: " << TotalSuiteRoomCost(rooms) << endl;
return 0;
}