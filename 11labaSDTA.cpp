#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <clocale>


using namespace std;


const int V = 6; 

struct AdjNode {
    int dest;        
    int weight;      
    AdjNode* next;   
};

void addEdgeAdjList(AdjNode* adjList[], int src, int dest, int weight) {
    AdjNode* newNode = new AdjNode{dest, weight, adjList[src]};
    adjList[src] = newNode;

    newNode = new AdjNode{src, weight, adjList[dest]};
    adjList[dest] = newNode;
}

void clearAdjList(AdjNode* adjList[]) {
    for (int i = 0; i < V; ++i) {
        AdjNode* current = adjList[i];
        while (current != nullptr) {
            AdjNode* temp = current;
            current = current->next;
            delete temp;
        }
        adjList[i] = nullptr;
    }
}

int main() {
    setlocale(LC_ALL, "Ukranian");

    int adjMatrix[V][V] = {0};

    adjMatrix[0][2] = 3; adjMatrix[2][0] = 3; 
    adjMatrix[0][3] = 7; adjMatrix[3][0] = 7; 
    adjMatrix[0][5] = 9; adjMatrix[5][0] = 9; 
    adjMatrix[1][2] = 6; adjMatrix[2][1] = 6; 
    adjMatrix[2][3] = 5; adjMatrix[3][2] = 5; 
    adjMatrix[2][4] = 2; adjMatrix[4][2] = 2; 
    adjMatrix[2][5] = 8; adjMatrix[5][2] = 8; 

    cout << "    ";
    for (int i = 1; i <= V; ++i) cout << "M" << i << "  ";
    cout << "\n";
    for (int i = 0; i < V; ++i) {
        cout << "M" << (i + 1) << "   ";
        for (int j = 0; j < V; ++j) {
            cout << adjMatrix[i][j] << "   ";
        }
        cout << "\n";
    }
    AdjNode* adjList[V] = {nullptr};

    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (adjMatrix[i][j] > 0) {
                addEdgeAdjList(adjList, i, j, adjMatrix[i][j]);
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        cout << "Місто " << (i + 1) << ": ";
        AdjNode* current = adjList[i];
        if (current == nullptr) {
            cout << "немає сполучень";
        }
        while (current != nullptr) {
           
            cout << "-> [Місто " << (current->dest + 1) << ", відст: " << current->weight << "] ";
            current = current->next;
        }
        cout << "\n";
    }

    bool isComplete = true;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && adjMatrix[i][j] == 0) {
                isComplete = false;
                break;
            }
        }
        if (!isComplete) break;
    }

    if (isComplete) {
        cout << "Відповідь: Граф Є повним.\n";
    } else {
        cout << "Відповідь: Граф НЕ є повним (оскільки не всі міста з'єднані між собою напряму).\n";
    } 
    double totalDistance = 0;
    int edgesCount = 0;

    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) { 
            if (adjMatrix[i][j] > 0) {
                totalDistance += adjMatrix[i][j];
                edgesCount++;
            }
        }
    }

    double averageDistance = (edgesCount > 0) ? totalDistance / edgesCount : 0;
    cout << "Сумарна відстань усіх доріг: " << totalDistance << "\n";
    cout << "Кількість існуючих доріг: " << edgesCount << "\n";
    cout << "Середня відстань: " << std::fixed << std::setprecision(2) << averageDistance << "\n";

    
    cout << "Результат: ";
    bool foundHighDegree = false;
    for (int i = 0; i < V; ++i) {
        int connections = 0;
        for (int j = 0; j < V; ++j) {
            if (adjMatrix[i][j] > 0) {
                connections++;
            }
        }
        if (connections > 2) {
            cout << "Місто " << (i + 1) << " (" << connections << " зв'язки); ";
            foundHighDegree = true;
        }
    }
    if (!foundHighDegree) cout << "таких міст немає.";
    int routesCount = 0;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            for (int k = 0; k < V; ++k) {

                if (i != k && adjMatrix[i][j] > 0 && adjMatrix[j][k] > 0) {

                    if (i < k) {
                        int totalDist2 = adjMatrix[i][j] + adjMatrix[j][k];
                        cout << "Маршрут: Місто " << (i + 1) << " -> Місто " << (j + 1) << " -> Місто " << (k + 1) 
                                  << " | Відстань: " << totalDist2 << "\n";
                        routesCount++;
                    }
                }
            }
        }
    }
    cout << "Всього унікальних маршрутів довжини 2: " << routesCount << "\n";
    int maxSum = -1;
    int bestA = -1, bestB = -1, bestC = -1;
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            for (int k = j + 1; k < V; ++k) {
                if (adjMatrix[i][j] > 0 && adjMatrix[j][k] > 0 && adjMatrix[i][k] > 0) {
                    int currentSum = adjMatrix[i][j] + adjMatrix[j][k] + adjMatrix[i][k];
                    if (currentSum > maxSum) {
                        maxSum = currentSum;
                        bestA = i; bestB = j; bestC = k;
                    }
                }
            }
        }
    }

    if (maxSum != -1) {
        cout << "Найвіддаленіша трійка міст: Місто " << (bestA + 1) << ", Місто " << (bestB + 1) << " та Місто " << (bestC + 1) << "\n";
        cout << "Дороги між ними: \n"
                  << "  - Місто " << (bestA + 1) << " <-> Місто " << (bestB + 1) << " (" << adjMatrix[bestA][bestB] << ")\n"
                  << "  - Місто " << (bestB + 1) << " <-> Місто " << (bestC + 1) << " (" << adjMatrix[bestB][bestC] << ")\n"
                  << "  - Місто " << (bestA + 1) << " <-> Місто " << (bestC + 1) << " (" << adjMatrix[bestA][bestC] << ")\n";
        cout << "Максимальна сумарна відстань: " << maxSum << "\n";
    } else {
        cout << "У графі немає жодної трійки міст, які б усі три були безпосередньо з'єднані між собою (немає трикутників).\n";
    }
    clearAdjList(adjList);
    return 0;
}