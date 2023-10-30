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
        double m_price = 0.0;
        double m_pricing_error = 0.0;
        double m_delta = 0.0;
    
        PathDependentOption(double T,               // Expiry
                            int m                   // no. of timesteps
                            ): m_T(T), m_m(m){};
        void rescale(SamplePath& S, double x);
    public:
        double priceByMC(MCBlackScholes model,      // Monte Carlo Black Scholes model
                         long N,                    // no. of MC simulations
                         double epsilon = 0.01      // bump size
        );
        virtual double payoff(SamplePath& S) =0;
        const double calculateStockPrice(int n, int i);
        const double& getPrice(){return m_price;};
        const double& getPricingError(){return m_pricing_error;};
        const double& getDelta(){return m_delta;};
    
};

class ArthmAsianCall: public PathDependentOption
{
    double m_K;
    public:
        ArthmAsianCall(double T, double K, int m): PathDependentOption{T, m}, m_K(K){};
        double payoff(SamplePath& S);
};

#endif /* PathDependentOption_h */
