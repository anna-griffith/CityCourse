//
//  main.cpp
//  MonteCarlo
//
//  Created by Anna Griffith on 22/10/2023.
//

#include <iostream>
#include "MCBlackScholes.h"

using namespace std;

int main(int argc, const char * argv[]) {
    double S0, sigma, r;
    
    // User inputs data
    cout << "Enter SO: "; cin >> S0;
    cout << "Enter sigma: "; cin >> sigma;
    cout << "Enter r: "; cin >> r;
    // get input data
    
    MCBlackScholes mcBlackScholes(S0, sigma, r);
    return 0;
}
