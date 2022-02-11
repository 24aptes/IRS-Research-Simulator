//
//  Grid.h
//  IRS Project
//
//  Created by Sohil Apte on 1/26/22.
//

#ifndef Grid_h
#define Grid_h


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

class Grid {
    int n;
    vector<vector<string>> divisorVector;
    vector<vector<string>> multipleVector;
    
public:
    void inputModule() {
        cout << "How large would you like your grid?" << endl;
        cin >> n;
        divisorVector.resize(n+1);
        multipleVector.resize(n+1);
    }
    
    void createDivisorsVector() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i % j == 0) {
                    divisorVector[i].push_back("*");
                } else {
                    divisorVector[i].push_back(" ");
                }
            }
        }
    }
    
    void createMultipleVector() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (j % i == 0) {
                    multipleVector[i].push_back("*");
                } else {
                    multipleVector[i].push_back(" ");
                }
            }
        }
    }
    
    void createGridDivisor() {
        for (int i = n; i > 0; i--) {
            cout << setw(2) << i;
            for (int j = 0; j < divisorVector[i].size(); j++) {
                cout << " " << setw(2) << divisorVector[i][j];
            }
            cout << endl;
        }
        
        for (int i = 0; i <= n; i++) {
            cout << setw(2) << i;
            if (i < n) {
                cout << " ";
            }
        }
        
        cout << endl;
    }
    
    void createGridMultiple() {
        for (int i = n; i > 0; i--) {
            cout << setw(2) << i;
            for (int j = 0; j < multipleVector[i].size(); j++) {
                cout << " " << setw(2) << multipleVector[i][j];
            }
            cout << endl;
        }
        
        for (int i = 0; i <= n; i++) {
            cout << setw(2) << i;
            if (i < n) {
                cout << " ";
            }
        }
        
        cout << endl;
    }
    
    void runGridFactor() {
        inputModule();
        createDivisorsVector();
        createGridDivisor();
    }
    
    void runGridMultiple() {
        inputModule();
        createMultipleVector();
        createGridMultiple();
    }
};
