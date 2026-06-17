#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <clocale>
#include <map>

using namespace std;
void SortByValue(map<string, double>& m) {
    vector<pair<string, double>> vec(m.begin(), m.end());
    sort(vec.begin(), vec.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second; 
    });
    for (const auto& pair : vec) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}
void maxvalue (map<string, double>& m){}
int main()
{
    setlocale(LC_ALL, "Ukranian");
    std::map <string, double> Days;
    Days["Понеділок"] = 12000.1;
    Days["Вівторок"] = 22543.5;
    Days["Середа"] = 15000.0;
    Days["Четвер"] = 7930.75;
    Days["П'ятниця"] = 2100;
    Days["Субота"] = 30000.0;
    Days["Неділя"] = 33215.9;



    cout << "Оберіть дію:\n";
    cout << "1. Показати виторг за день\n";
    cout << "2. Показати загальний та середній виторг\n";
    cout << "3. Змінити виторг за день\n";
    cout << "4. Вивести день з найбільшими продажами"<<endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Введіть день тижня (українською): ";
        string inputDay;
        cin >> inputDay;
        auto it = Days.find(inputDay);
        if (it != Days.end()) {
            cout << "Виторг: " << it->second << "\n";
        } else {
            cout << "Невірний день тижня.\n";
        }
    } else if (choice == 2) {
        double totalRevenue = 0.0;
        for (const auto& pair : Days) {
            totalRevenue += pair.second;
        }
        double averageRevenue = totalRevenue / Days.size();
        cout << "Загальний виторг за тиждень: " << totalRevenue << "\n";
        cout << "Середній виторг за день: " << averageRevenue << "\n";
    } else if (choice == 3) {
        cout << "Виберіть день тижня для зміни виторгу (українською): ";
        string dayToChange;
        cin >> dayToChange;
        auto itChange = Days.find(dayToChange);
        if (itChange != Days.end()) {
            cout << "Введіть новий виторг для " << dayToChange << ": ";
            double newRevenue;
            cin >> newRevenue;
            itChange->second = newRevenue;
            cout << "Виторг для " << dayToChange << " оновлено.\n";
        
        // Show updated total
        double totalRevenue = 0.0;
        for (const auto& pair : Days) totalRevenue += pair.second;
        cout << "Виторг за тиждень після змін: \"" << totalRevenue << "\n";
    }
    return 0;
}