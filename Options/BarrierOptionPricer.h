//
//  DoubleBarrierOptionPricer.hpp
//  BinomialModel
//
//  Created by Anna Griffith on 19/10/2023.
//

#ifndef BarrierOptionPricer_h
#define BarrierOptionPricer_h

#include "OptionPricerBase.h"


class BarrierOptionPricer: public EurOptionPricer, public AmOptionPricer {
    protected:
        double m_payoff_barrier_hit;        // payoff recieved if we hit barrier(s)
        double m_payoff_barrier_missed;     // payoff recieved if we don't hit barrier(s)
        BarrierOptionPricer(double payoff_barrier_hit, double payoff_barrier_missed)
                            : m_payoff_barrier_hit{payoff_barrier_hit},
                              m_payoff_barrier_missed{payoff_barrier_missed}{};
    public:
        const double priceByCRR();
};

class KOBarrierOptionPricer: public BarrierOptionPricer {
    private:
        double m_LowerBarrier;
        double m_UpperBarrier;
    public:
        KOBarrierOptionPricer(int N, double lowerBarrier, double upperBarrier,  BinomialModel binModel);
        KOBarrierOptionPricer(int N, double barrier,  BinomialModel binModel);
        const double payoff(double z);
};

class KIBarrierOptionPricer: public BarrierOptionPricer {
    private:
        double m_LowerBarrier;
        double m_UpperBarrier;
    public:
        KIBarrierOptionPricer(int N, double lowerBarrier, double upperBarrier,  BinomialModel binModel);
        KIBarrierOptionPricer(int N, double barrier,  BinomialModel binModel);
        const double payoff(double z);
};

#endif /* DoubleBarrierOptionPricer_h */
