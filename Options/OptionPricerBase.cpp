//
//  OptionPricerBase.cpp
//  BinomialModel
//
//  Created by Anna Griffith on 06/10/2023.
//

#include "OptionPricerBase.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace std;

OptionPricer::OptionPricer(int N,                     // Steps to expiry
                           BinomialModel binModel     // Binomial Model
                           ): m_N{N}, m_binModel{binModel}
{
    // 1. N >=0
    if (N < 0)
    {
        throw invalid_argument("Illegal data ranges, require N >= 0");
    }
}

const double EurOptionPricer::priceByCRR()
{
    const double q = m_binModel.calculateRiskNeutralProbability();
    double* Price = new double[m_N + 1]; // since N is unknown at compile time, need to use 'new' to allocate memory on the heap, which then requires deleting later. OR just use a vector, which wrap new and delete calls for you
    
    for (int i = 0; i <= m_N; i++)
    {
        Price[i] = payoff(m_binModel.calculateStockPrice(m_N, i));
    }
    for (int n = m_N - 1; n >= 0; n--)
    {
        for (int i = 0; i <= n; i++)
        {
            Price[i] = (q * Price[i+1] + (1.0 - q) * Price[i]) / (1.0 + m_binModel.getR());
    
        }
    }
    double result = Price[0];
    delete [] Price;
    return result;
    
}

const double EurOptionPricer::priceAnalytic()
{
    const double q = m_binModel.calculateRiskNeutralProbability();
    vector<double> PDF(m_N + 1);
    double sum_PDF = 0.0;
    vector<double> Price(m_N + 1);
    double sum = 0.0;
    
    for (int i = 0; i <= m_N; i++)
    {
        Price[i] = payoff(m_binModel.calculateStockPrice(m_N, i));
    }
    for (int i = 0; i <= m_N; i++)
    {
        PDF[i] = calculateNewtonSymbol(i) * pow(q, i) * pow (1.0 - q, m_N - i);
        sum_PDF += PDF[i];
        cout << " i = " << i << ", PDF [i] = " << PDF[i] << endl;
        sum += PDF[i] * Price[i];
    }
    cout << "PDFSum = " << sum_PDF << endl;
    
    const double result = sum / pow(1.0 + m_binModel.getR(), m_N);
    return result;
}

const double EurOptionPricer::calculateNewtonSymbol(int i // calculate N choose i
)
{
    if (i < 0 || i > m_N) return 0;
    double result = 1;
    for (int k = 1; k <= i; k++) result = result * (m_N - i + k) / k;
    return result;
}

const double AmOptionPricer::priceBySnell()
{
    const double q = m_binModel.calculateRiskNeutralProbability();
    vector<double> Price(m_N + 1);
    double contVal;
    
    for (int i = 0; i <= m_N; i++)
    {
        Price[i] = payoff(m_binModel.calculateStockPrice(m_N, i));
    }
    for (int n = m_N - 1; n >= 0; n--)
    {
        for (int i = 0; i <= n; i++)
        {
            contVal = (q * Price[i+1] + (1.0 - q) * Price[i]) / (1.0 + m_binModel.getR());
            Price[i] = payoff(m_binModel.calculateStockPrice(n, i));
            if (contVal > Price[i]) Price[i]=contVal;
    
        }
    }
    return Price[0];
}
