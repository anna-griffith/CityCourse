//
//  OptionPricer.h
//  BinomialModel
//
//  Created by Anna Griffith on 12/10/2023.
//

#ifndef OptionPricer_h
#define OptionPricer_h

#include "OptionPricerBase.h"

class CallOptionPricer : public EurOptionPricer, public AmOptionPricer{
    private:
        double m_K;
    public:
        CallOptionPricer(int N, double K, BinomialModel binModel):
                         OptionPricer{N, binModel}, m_K(K){};
        const double payoff(double z);
    
};

class PutOptionPricer : public EurOptionPricer, public AmOptionPricer{
    private:
        double m_K;
    public:
        PutOptionPricer(int N, double K, BinomialModel binModel):
                        OptionPricer{N, binModel}, m_K(K){};
        const double payoff(double z);
    
};

class DigitalCallOptionPricer : public EurOptionPricer, public AmOptionPricer{
    private:
        double m_K;
    public:
        DigitalCallOptionPricer(int N, double K, BinomialModel binModel):
                                OptionPricer{N, binModel}, m_K(K){};
        const double payoff(double z);
    
};

class DoubleDigitalOptionPricer : public EurOptionPricer, public AmOptionPricer{
    protected:
        double m_LowerBarrier;
        double m_UpperBarrier;
    public:
        DoubleDigitalOptionPricer(int N, double lowerBarrier, double upperBarrier, BinomialModel binModel);
        const double payoff(double z);
    
};

#endif /* OptionPricer_h */
