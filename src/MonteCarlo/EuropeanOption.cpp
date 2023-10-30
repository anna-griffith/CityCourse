//
//  EuropeanOption.cpp
//  CityCourse
//
//  Created by Anna Griffith on 29/10/2023.
//

#include "EuropeanOption.h"

double EuropeanOption::priceByMC(MCBlackScholes model, long N)
{
    double h = 0.0;
    SamplePath S(1);        //EuropeanOptions are not path dependent, so can use one timestep
    
    for (long i=0; i<N; i++)
    {
        model.generateSamplePath(m_T, 1, S);
        h += payoff(S);
    }
    return exp(-1.0 * model.get_r() * m_T) * h / N;
}

double EuropeanCall::payoff(SamplePath &S)
{
    if (S[0] < m_K) return 0.0;
    return S[0] - m_K;
}

double EuropeanPut::payoff(SamplePath &S)
{
    if (S[0] > m_K) return 0.0;
    return m_K - S[0];
}
