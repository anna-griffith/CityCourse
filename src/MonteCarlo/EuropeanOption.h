//
//  EuropeanOption.h
//  CityCourse
//
//  Created by Anna Griffith on 29/10/2023.
//

#ifndef EuropeanOption_h
#define EuropeanOption_h

#include "MCBlackScholes.h"

class EuropeanOption{
    protected:
        double m_T;
        EuropeanOption(double T                    // Expiry
                      ): m_T(T){};
    public:
        double priceByMC(MCBlackScholes model,      // Monte Carlo Black Scholes model
                         long N                     // no. of MC simulations
        );
        virtual double payoff(SamplePath& S) =0;
    
};

class EuropeanCall: public EuropeanOption
{
    double m_K;
    public:
        EuropeanCall(double T, double K): EuropeanOption{T}, m_K(K){};
        double payoff(SamplePath& S);
};

class EuropeanPut: public EuropeanOption
{
    double m_K;
    public:
        EuropeanPut(double T, double K): EuropeanOption{T}, m_K(K){};
        double payoff(SamplePath& S);
};

#endif /* EuropeanOption_h */
