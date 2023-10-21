//
//  OptionPricer.cpp
//  BinomialModel
//
//  Created by Anna Griffith on 12/10/2023.
//

#include "OptionPricer.h"
#include <stdexcept>

using namespace std;

const double CallOptionPricer::payoff(double z             // stock price
)
{
    if (z > m_K) return z - m_K;
    return 0.0;
}

const double PutOptionPricer::payoff(double z              // stock price
)
{
    if (z < m_K) return m_K - z;
    return 0.0;
}

const double DigitalCallOptionPricer::payoff(double z      // stock price
)
{
    if (z > m_K) return 1.0;
    return 0.0;
}

DoubleDigitalOptionPricer::DoubleDigitalOptionPricer(int N,
                                   double lowerBarrier,
                                   double upperBarrier,
                                   BinomialModel binModel
                                   ): OptionPricer{N, binModel}, m_LowerBarrier{lowerBarrier}, m_UpperBarrier{upperBarrier}
{
    if (m_UpperBarrier <= m_LowerBarrier)
    {
        throw invalid_argument("Illegal data ranges, require upperBarrier > lowerBarrier");
    }
    
}

const double DoubleDigitalOptionPricer::payoff(double z      // stock price
)
{
    if (m_LowerBarrier <= z && z <= m_UpperBarrier) return 1.0;
    return 0.0;
}
