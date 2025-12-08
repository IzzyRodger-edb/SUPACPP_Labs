#include "FiniteFunctions.h"
#pragma once

class GaussianDist : public FiniteFunction {
    public:
        GaussianDist();
        GaussianDist(double range_min, double range_max, std::string outfile, double mu, double sigma);

        void setMu(double mu);
        void setSigma(double sigma);

        double mu();
        double sigma();
        virtual double callFunction(double x);
        void printInfo();
        

    private:
        double m_mu;
        double m_sigma;
        double gaussian(double x);
};