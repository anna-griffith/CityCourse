//
//  OptionPricerBase.hpp
//  BinomialModel
//
//  Created by Anna Griffith on 06/10/2023.
//

#ifndef OptionPricerBase_h
#define OptionPricerBase_h

#include "../BinomialModel/BinomialModel.h"

class OptionPricer{
    protected:
        int m_N;
        BinomialModel m_binModel;
    public:
        OptionPricer(int N, BinomialModel binModel);
        virtual const double payoff(double z) = 0;
    
};

class EurOptionPricer: virtual public OptionPricer {
    public:
        const double calculateNewtonSymbol(int i);
        const double priceByCRR();
        const double priceAnalytic();
};

class AmOptionPricer: virtual public OptionPricer {
    public:
        const double priceBySnell();
};

#endif /* OptionPricerBase_h */
