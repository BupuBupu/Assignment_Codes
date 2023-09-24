#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm> // For sorting in getTopK
#include <bits/stdc++.h>
using namespace std;
#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
// Function to generate a unique ID based on an index
string generateUniqueID(int i)
{
    string ifscCode = "ABCD" + to_string(i % 10000);
    string accountNumber = to_string(1000000000 + i);
    return ifscCode + "_" + accountNumber;
}

int main()
{
    Comp bank;

    // Create 100,000 accounts with random initial balances
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distBalance(1, 1000);

    for (int i = 1; i <= 100000; i++)
    {
        string id = generateUniqueID(i);
        int initialBalance = distBalance(gen);
        bank.createAccount(id, initialBalance);
    }

    // Stress test operations
    chrono::high_resolution_clock::time_point start, end;
    chrono::duration<double> duration;

    // Stress test addTransaction by performing 100,000 random transactions
    start = chrono::high_resolution_clock::now();
    uniform_int_distribution<int> distTransaction(-1000, 1000);
    for (int i = 1; i <= 100000; i++)
    {
        string id = generateUniqueID(i);
        int transactionAmount = distTransaction(gen);
        bank.addTransaction(id, transactionAmount);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << "Time for 100,000 addTransaction operations: " << duration.count() << " seconds" << endl;

    // Stress test getBalance by querying balances of all 100,000 accounts
    start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 100000; i++)
    {
        string id = generateUniqueID(i);
        int balance = bank.getBalance(id);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << "Time for querying balances of 100,000 accounts: " << duration.count() << " seconds" << endl;

    // Stress test getTopK by querying top 10,000 balances
    start = chrono::high_resolution_clock::now();
    vector<int> topBalances = bank.getTopK(10000);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << "Time for querying top 10,000 balances: " << duration.count() << " seconds" << endl;

    // Stress test deleteAccount by deleting all 100,000 accounts
    start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 100000; i++)
    {
        string id = generateUniqueID(i);
        bank.deleteAccount(id);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << "Time for deleting 100,000 accounts: " << duration.count() << " seconds" << endl;

    // Stress test doesExist by checking existence for 10,000 random accounts
    start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 10000; i++)
    {
        string id = "IFSC" + to_string(i) + "_" + to_string(i * 10);
        bool exists = bank.doesExist(id);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << "Time for checking existence of 10,000 accounts: " << duration.count() << " seconds" << endl;

    return 0;
}