//
//  MCBlackScholes.cpp
//  CityCourse
//
//  Created by Anna Griffith on 22/10/2023.
//

#include "MCBlackScholes.h"
#include <stdexcept>


const double PI = 4.0*atan(1.0);

MCBlackScholes::MCBlackScholes(double S0,
                               double sigma,
                               double r)
  : m_S0{S0}, m_sigma(sigma), m_r(r)
{
      // 1. make sure S0>0, sigma > 0
      if (m_S0 <=0.0 || m_sigma <= 0.0)
      {
          throw invalid_argument("Illegal data ranges");
      }
}

// Generate standard gaussian random numbers
double MCBlackScholes::generateGauss()
{
    double u1 = (rand() + 1.0) / (RAND_MAX + 1.0);
    double u2 = (rand() + 1.0) / (RAND_MAX + 1.0);
    
    return sqrt( -2.0 * log(u1)) * cos(2.0 * PI * u2);
}

void MCBlackScholes::generateSamplePath(double T, int m, SamplePath &S)
{
    double St = m_S0;
    double mul_factor = exp((m_r - m_sigma * m_sigma * 0.5) * T / m);
    double sigma_sqrt_t = m_sigma * sqrt(T/m);
    for (int k=0; k<m; k++)
    {
        S[k] = St * mul_factor * exp(sigma_sqrt_t * generateGauss());
        St = S[k];
    }
}
