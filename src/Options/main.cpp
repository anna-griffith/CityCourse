//
//  main.cpp
//  Options
//
//  Created by Anna Griffith on 05/10/2023.
//

#include <iostream>
#include "OptionPricer.h"
using namespace std ;


int main()
{
    double S0, U, D, R;
    
    // User inputs data
    cout << "Enter SO: "; cin >> S0;
    cout << "Enter U: "; cin >> U;
    cout << "Enter D: "; cin >> D;
    cout << "Enter R: "; cin >> R;

    BinomialModel binModel(S0, U, D, R);
    
    int N;
    double K;
    cout << "Enter steps to expiry N: "; cin >> N;
    cout << "Enter strike price K: "; cin >> K; cout << endl ;
    
    CallOptionPricer optionsPricer(N, K, binModel);
    
    cout << "European call option price = "
    << optionsPricer.priceByCRR() << endl;
    
    cout << "Analytic European call option price = "
    << optionsPricer.priceAnalytic() << endl;
    
    return 0;
}
