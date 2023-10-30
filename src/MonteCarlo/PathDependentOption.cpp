//
//  PathDependentOption.cpp
//  CityCourse
//
//  Created by Anna Griffith on 22/10/2023.
//

#include "PathDependentOption.h"

void PathDependentOption::rescale(SamplePath& S, double x)
{
    for (int j = 0; j<m_m; j++)
    {
        S[j] = x * S[j];
    }
}

double PathDependentOption::priceByMC(MCBlackScholes model, long N, double epsilon)
{
    double h = 0.0;
    double h_sq = 0.0;
    double h_eps = 0.0;
    SamplePath S(m_m);
    
    for (long i=0; i<N; i++)
    {
        model.generateSamplePath(m_T, m_m, S);
        double payoff_loop = payoff(S);
        double div = 1.0 / (i + 1);
        h = (i*h + payoff_loop) * div;
        h_sq = (i*h_sq + payoff_loop * payoff_loop) * div;
        rescale(S, 1.0 + epsilon);
        h_eps = (i*h_eps + payoff(S)) * div;
        
    }
    double exp_factor = exp(-1.0 * model.get_r() * m_T);
    m_price =  exp_factor * h;
    m_pricing_error = exp_factor * sqrt( h_sq - h * h) / sqrt(N - 1);
    m_delta = exp_factor * (h_eps - h)/(model.get_S0() * epsilon);
    return m_price;
}

double ArthmAsianCall::payoff(SamplePath &S)
{
    double average = 0.0;
    // more stable way of computing average
    for (int k=0; k<m_m; k++)
    {
        average = (k * average + S[k]) / (k + 1);
    }
    if (average < m_K) return 0.0;
    return average - m_K;
}
