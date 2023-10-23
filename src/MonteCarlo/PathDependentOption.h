//
//  PathDependentOption.h
//  CityCourse
//
//  Created by Anna Griffith on 22/10/2023.
//

#ifndef PathDependentOption_h
#define PathDependentOption_h

#include "MCBlackScholes.h"

class PathDependentOption{
    protected:
        double m_T;
        int m_m;
        PathDependentOption(double T,               // Expiry
                            int m                   // no. of timesteps
                            ): m_T(T), m_m(m){};
    public:
        double priceByMC(MCBlackScholes model,      // Monte Carlo Black Scholes model
                         long N                     // no. of MC simulations
        );
        virtual double payoff(SamplePath& S) =0;
    
};

class ArthmAsianCall: public PathDependentOption
{
    double m_K;
    public:
        ArthmAsianCall(double T, double K, int m): PathDependentOption{T, m}, m_K(K){};
        double payoff(SamplePath& S);
};

#endif /* PathDependentOption_h */
