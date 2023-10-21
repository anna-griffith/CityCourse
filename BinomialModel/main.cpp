//
//  main.cpp
//  BinomialModel
//
//  Created by Anna Griffith on 05/10/2023.
//

#include <iostream>
#include "BinomialModel.h"
using namespace std ;


int main()
{
    double S0, U, D, R;
    
    // User inputs data
    cout << "Enter SO: "; cin >> S0;
    cout << "Enter U: "; cin >> U;
    cout << "Enter D: "; cin >> D;
    cout << "Enter R: "; cin >> R;
    // get input data
    BinomialModel binModel(S0, U, D, R);
    double q = binModel.calculateRiskNeutralProbability();
    cout << "Risk - neutral probability q = " << q << endl ;
    int n = 3;
    int i = 2;
    cout << "S("<< n << " ," << i << ") = " << binModel.calculateStockPrice(n, i) << endl;
    return 0;
}
