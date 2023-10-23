//
//  MCBlackScholes.h
//  CityCourse
//
//  Created by Anna Griffith on 22/10/2023.
//

#ifndef MCBlackScholes_h
#define MCBlackScholes_h

#include <vector>
#include <cmath>
using namespace std;
typedef vector<double> SamplePath ;

class MCBlackScholes
{
    protected:
        double m_S0;
        double m_sigma;
        double m_r;
    private:
        double generateGauss();
    public:
        MCBlackScholes(double S0,
                       double sigma,
                       double r);
        void generateSamplePath(double T, int m, SamplePath& S);
        double get_r(){return m_r;};
};

#endif /* MCBlackScholes_h */
