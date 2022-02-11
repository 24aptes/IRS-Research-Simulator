//
//  IRS.h
//  IRS Project
//
//  Created by Sohil Apte on 1/26/22.
//

#ifndef IRS_h
#define IRS_h


#endif /* IRS_h */

#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <cctype>
#include <set>
#include <iterator>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <limits>
using namespace std;

class Game {
    vector<vector<int>> gameArray;
    vector<int> prunedNumbers;
    vector<int> prunedDivisors;
    vector<int> IRSTotal;
    vector<int> playerTotal;
    vector<int> primeNumberSet;
    int n;
    int playerSum;
    int IRSSum;
public:
     
    void constructGameArray() {
        cout << "How large would you like the game to be?" << endl;
        cin >> n;
        gameArray.push_back({});
        for (int i = 1; i <= n; i++) {
            vector<int> factors = createDivisorVector(i);
            gameArray.push_back(factors);
        }
    }
    
    void constructGameArrayLargeSim(int n) {
        gameArray.push_back({});
        for (int i = 1; i <= n; i++) {
            vector<int> factors = createDivisorVector(i);
            gameArray.push_back(factors);
        }
    }
    
    vector<int> createDivisorVector(int currentVal) {
        vector<int> returnDivisors;
        for (int i = 2; i < currentVal; i++) {
            if (currentVal % i == 0) {
                returnDivisors.push_back(i);
            }
        }
        return returnDivisors;
    }
    
    int largestPrimeNumber() {
        int currentLargestPrime = 0;
        for (int i = 1; i <= n; i++) {
            if (gameArray[i].size() == 0) {
                primeNumberSet.push_back(i);
                currentLargestPrime = i;
            }
        }
        return currentLargestPrime;
    }
    
    int chooseNumber() {
        //Player chooses a number from the array
        //Player chooses number from UPPER HALF (n+1) / 2 of the array with the smallest number of divisors
        int midPoint = ceil((static_cast<double>(n) + 1.0) / 2.0);
        int currentSmallestDivisorSize = 10000000;
        int currentChosenNumber = 0;
        
        int i = midPoint;
        for (; i <= n; i++) {
            if (gameArray[i].size() <= currentSmallestDivisorSize && gameArray[i].size() != 0 && !isPruned(i)) {
                currentSmallestDivisorSize = static_cast<int>(gameArray[i].size());
                currentChosenNumber = i;
            }
        }
        return currentChosenNumber;
    }
    
    bool isPruned(int current) {
        for (int i = 0; i < prunedNumbers.size(); i++) {
            if (current == prunedNumbers[i]) {
                return true;
            }
        }
        return false;
    }
    
    void IRSPushBack(int chosenNumber) {
        for (int i = 0; i < gameArray[chosenNumber].size(); i++) {
            IRSTotal.push_back(gameArray[chosenNumber][i]);
        }
    }
    
    void eraseDivisorFromVector(int divisor) {
        int midPoint = ceil((static_cast<double>(n) + 1.0) / 2.0);
        int i = midPoint;
        for (; i <= n; i++) {
            if (!gameArray[i].empty()) {
                int position = getPositionToDelete(divisor, i);
                if (position != 100000) {
                    gameArray[i].erase(gameArray[i].begin() + position);
                }
            }
        }
    }
    
    int getPositionToDelete(int divisor, int currentIndex) {
        int position = 100000;
        
        for (int j = 0; j < gameArray[currentIndex].size(); j++) {
            if (gameArray[currentIndex][j] == divisor) {
                position = j;
            }
        }
        return position;
    }
    
    //Running the Game:
    //Step 1: Player Chooses the largest prime number (largest prime goes to player, 1 goes to IRS)
    //Step 1.5, all other primes go to IRS
    //Step 2: Choose the number with the smallest number of divisors.
        // -- That number goes to the Player, the divisors go to IRS.
    //Step 3: The chosen number is "pruned" from the list of possible numbers we can choose
    //Step 4: The divisors of that number are pruned from the possible divisors of all the other nummbers.
    
    void stepOne() {
        int largestPrimeVal = largestPrimeNumber();
        playerTotal.push_back(largestPrimeVal);
        //cout << "Player Chose: " << largestPrimeVal << endl;
        IRSTotal.push_back(1);
        prunedNumbers.push_back(largestPrimeVal);
        prunedNumbers.push_back(1);
        
        int midPoint = ceil((static_cast<double>(n) + 1.0) / 2.0);
        
        for (int i = 0; i < primeNumberSet.size(); i++) {
            if (primeNumberSet[i] != largestPrimeVal && primeNumberSet[i] != 1
                && primeNumberSet[i] >= midPoint) {
                IRSTotal.push_back(primeNumberSet[i]);
                prunedNumbers.push_back(primeNumberSet[i]);
            }
        }
    }
    
    void stepTwo() {
        int chosenNumber = chooseNumber();
        if (chosenNumber != 0) {
        //cout << "Player Chose: " << chosenNumber << endl;
        playerTotal.push_back(chosenNumber);
        IRSPushBack(chosenNumber);
            prunedNumbers.push_back(chosenNumber);
            
            int divArraySize = static_cast<int>(gameArray[chosenNumber].size());
            for (int i = 0; i < divArraySize; i++) {
                prunedNumbers.push_back(gameArray[chosenNumber][i]);
            }
            for (int i = 0; i < divArraySize; i++) {
                eraseDivisorFromVector(gameArray[chosenNumber][i]);
            }
        } else {
            int i = 1;
            for (; i <= n; i++) {
                if (!isPruned(i)) {
                    IRSTotal.push_back(i);
                    prunedNumbers.push_back(i);
                }
            }
        }
    }
    
    void printIRS() {
        for (int i = 0; i < IRSTotal.size(); i++) {
            cout << IRSTotal[i] << ", ";
            IRSSum += IRSTotal[i];
        }
    }
    
    void printPlayer() {
        for (int i = 0; i < playerTotal.size(); i++) {
            cout << playerTotal[i] << ", ";
            playerSum += playerTotal[i];
        }
    }
    
    void outputModule() {
        if (playerSum > IRSSum) {
            cout << "Player won by: " << playerSum - IRSSum << " points!" << endl;
        } else if (playerSum == IRSSum) {
            cout << "Player tied IRS with :" << playerSum << " points!" << endl;
        } else {
            cout << "IRS won by: " << IRSSum - playerSum << " points!" << endl;
        }
    }
    
    void netOutput() {
        int totalSum = (n * (n + 1)) / 2;
        int r = ceil((static_cast<double>(n) + 1.0) / 2.0);
        int sumOfLowerSequence = (r * (r - 1)) / 2;
        int sumOfPrimes = 0;
        for (int i = 0; i < primeNumberSet.size() - 1; i++) {
            if (primeNumberSet[i] >= r) {
            sumOfPrimes += primeNumberSet[i];
            }
        }
        int net = totalSum - sumOfLowerSequence - sumOfPrimes;
        cout << "Net: " << net << endl;
        
        cout << "Difference between Net and Algorithm Strategy is: " << net - playerSum << endl;
    }
    
    void runGame() {
        constructGameArray();
        stepOne();
        while (prunedNumbers.size() < n) {
            stepTwo();
        }
        cout << "Player Numbers: ";
        printPlayer();
        cout << endl;
        cout << "IRS Numbers: ";
        printIRS();
        
        cout << endl;
        cout << "Player Sum: " << playerSum << endl;
        cout << "IRS Sum: " << IRSSum << endl;
        
        outputModule();
        
        //netOutput();
    }
    
    void runGameLargeSim(int passedNum) {
        constructGameArrayLargeSim(passedNum);
        stepOne();
        while (prunedNumbers.size() < n) {
            stepTwo();
        }
//        cout << "Player Numbers: ";
//        printPlayer();
//        cout << endl;
//        cout << "IRS Numbers: ";
//        printIRS();
//
//        cout << endl;
        cout << "Player Sum: " << playerSum << endl;
        cout << "IRS Sum: " << IRSSum << endl;
        
        outputModule();
        netOutput();
    }
};
