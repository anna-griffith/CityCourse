//
//  DoubleBarrierOptionPricer.cpp
//  BinomialModel
//
//  Created by Anna Griffith on 19/10/2023.
//

#include "BarrierOptionPricer.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>

using namespace std;

const double BarrierOptionPricer::priceByCRR()
{
    const double q = m_binModel.calculateRiskNeutralProbability();
    vector<double> Price(m_N + 1);
    
    for (int i = 0; i <= m_N; i++)
    {
        Price[i] = payoff(m_binModel.calculateStockPrice(m_N, i));
    }
    for (int n = m_N - 1; n >= 0; n--)
    {
        for (int i = 0; i <= n; i++)
        {
            double calc_payoff = payoff(m_binModel.calculateStockPrice(n,i));
            if (calc_payoff == m_payoff_barrier_missed)
            {
                Price[i] = (q * Price[i+1] + (1.0 - q) * Price[i]) / (1.0 + m_binModel.getR());
            }
            else
            {
                Price[i] = m_payoff_barrier_hit;
            }
    
        }
    }
    double result = Price[0];
    return result;
    
}

KOBarrierOptionPricer::KOBarrierOptionPricer(int N, double lowerBarrier, double upperBarrier,  BinomialModel binModel)
    :OptionPricer{N, binModel},
    m_LowerBarrier{lowerBarrier},
    m_UpperBarrier{upperBarrier},
    BarrierOptionPricer(0.0, 1.0)
{
    if (binModel.getS0() >= m_UpperBarrier || binModel.getS0() <= m_LowerBarrier)
    {
        throw invalid_argument("Illegal data ranges, require S0 between barriers");
    }
}

KOBarrierOptionPricer::KOBarrierOptionPricer(int N, double barrier,  BinomialModel binModel)
                                            :OptionPricer{N, binModel},
                                             BarrierOptionPricer(0.0, 1.0)
{
    //if one barrier is provided, work out whether it is an upper or lower barrier based on value of S0. Set the other barrier to 0 or dbl_max accordingly
    if (m_binModel.getS0() >= barrier)
    {
        m_LowerBarrier = barrier;
        m_UpperBarrier = numeric_limits<double>::max();
    }
    else
    {
        m_LowerBarrier = 0.0;
        m_UpperBarrier = barrier;
    }
                                            
}

const double KOBarrierOptionPricer::payoff(double z      // stock price
)
{
    if (m_LowerBarrier <= z && z <= m_UpperBarrier) return 1.0;
    return 0.0;
}

KIBarrierOptionPricer::KIBarrierOptionPricer(int N, double lowerBarrier, double upperBarrier,  BinomialModel binModel)
    :OptionPricer{N, binModel},
    m_LowerBarrier{lowerBarrier},
    m_UpperBarrier{upperBarrier},
    BarrierOptionPricer(1.0, 0.0)
{
    if (binModel.getS0() <= m_UpperBarrier && binModel.getS0() >= m_LowerBarrier)
    {
        throw invalid_argument("Illegal data ranges, require S0 outside barriers");
    }
}

KIBarrierOptionPricer::KIBarrierOptionPricer(int N, double barrier,  BinomialModel binModel)
                                            :OptionPricer{N, binModel},
                                             BarrierOptionPricer(1.0, 0.0)
{
    //if one barrier is provided, work out whether it is an upper or lower barrier based on value of S0. Set the other barrier to 0 or dbl_max accordingly
    if (m_binModel.getS0() <= barrier)
    {
        m_LowerBarrier = barrier;
        m_UpperBarrier = numeric_limits<double>::max();
    }
    else
    {
        m_LowerBarrier = 0.0;
        m_UpperBarrier = barrier;
    }
                                            
}

const double KIBarrierOptionPricer::payoff(double z      // stock price
)
{
    if (m_LowerBarrier <= z && z <= m_UpperBarrier) return 1.0;
    return 0.0;
}
