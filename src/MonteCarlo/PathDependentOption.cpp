//
//  PathDependentOption.cpp
//  CityCourse
//
//  Created by Anna Griffith on 22/10/2023.
//

#include "PathDependentOption.h"

double PathDependentOption::priceByMC(MCBlackScholes model, long N)
{
    double h = 0.0;
    SamplePath S(m_m);
    
    for (long i=0; i<N; i++)
    {
        model.generateSamplePath(m_T, m_m, S);
        h += payoff(S);
    }
    return exp(-1.0 * model.get_r() * m_T) * h / N;
}

double ArthmAsianCall::payoff(SamplePath &S)
{
    double average = 0.0;
    for (int k=0; k<m_m; k++)
    {
        average = (k * average + S[k]) / (k + 1);
    }
    if (average < m_K) return 0.0;
    return average - m_K;
}
