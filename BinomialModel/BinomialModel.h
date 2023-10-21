//
//  binomial_model.h
//  BinomialTree
//
//  Created by Anna Griffith on 05/10/2023.
//

#ifndef BinomialModel_h
#define BinomialModel_h

class BinomialModel{
    private:
        double m_S0;
        double m_U;
        double m_D;
        double m_R;
    
        void check_inputs();
    
    public:
        BinomialModel(double S0,
                      double U,
                      double D,
                      double R);
        BinomialModel(double S0,
                      double sigma,
                      double T,
                      int N,
                      double r);
        const double calculateRiskNeutralProbability();
        const double calculateStockPrice(int n, int i);
        const double& getR();
        const double& getS0();
};
#endif /* BinomialModel_h */
