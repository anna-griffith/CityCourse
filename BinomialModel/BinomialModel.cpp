//
//  user_inputs.cpp
//  BinomialTree
//
//  Created by Anna Griffith on 05/10/2023.
//

#include "BinomialModel.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

void BinomialModel::check_inputs()
{
    // 1. make sure S0>0, (1+U)>0, (1+D)>0, (1+R)>0
    if (m_S0 <=0.0 || m_U <= -1.0 || m_D <= -1.0 || m_R <= -1.0 || m_U <= m_D)
    {
        throw invalid_argument("Illegal data ranges");
    }
    //2. Checking for arbitrage D<R<U; q>1, or q<0; q=(R-D)/(U - D)
    if (m_R<=m_D || m_R>=m_U)
    {
        throw invalid_argument("Arbitrage exists");
    }
    cout << "Input data checked \n";
    cout << "No arbitrage exists \n";
    
}

BinomialModel::BinomialModel(double S0, // initial stock price
                             double U,  // up movement, S(up) = (1+U)S
                             double D,  // down movement, S(down) = (1+D)S
                             double R   // risk neutral rate
)
                            : m_S0{S0}, m_U{U}, m_D{D}, m_R{R}
{
    check_inputs();
}

BinomialModel::BinomialModel(double S0,
                             double sigma,
                             double T,
                             int N,
                             double r)
: m_S0{S0}
{
    double h = T/N;
    m_R = exp(r*h) - 1.0;
    m_U = exp((r + sigma * sigma / 2.0) * h + sigma * sqrt(h)) - 1.0;
    m_D = exp((r + sigma * sigma / 2.0) * h - sigma * sqrt(h)) - 1.0;
    cout << "Binomial model constructed with:" << endl;
    cout << "SO: " << m_S0 << endl;
    cout << "U: " << m_U << endl;
    cout << "D: " << m_D << endl;
    cout << "R: " << m_R << endl;
    check_inputs();

}

const double BinomialModel::calculateRiskNeutralProbability()
{
    double q = (m_R - m_D) / (m_U - m_D);
    return q;
}

const double BinomialModel::calculateStockPrice(int n, // horizontal tree node
                                          int i  // vertical tree node
)
{
    return m_S0 * pow(1.0 + m_U, i) * pow(1.0 + m_D, n - i);
}

const double& BinomialModel::getR()
{
    return m_R;
}

const double& BinomialModel::getS0()
{
    return m_S0;
}
