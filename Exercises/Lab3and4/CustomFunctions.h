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

class CauchyLorentzDist : public FiniteFunction {
    public:
        CauchyLorentzDist();
        CauchyLorentzDist(double range_min, double range_max, std::string outfile, double x0, double gamma);

        void setx0(double x0);
        void setGamma(double gamma);

        double x0();
        double gamma();
        virtual double callFunction(double x);
        void printInfo();
        

    private:
        double m_x0;
        double m_gamma;
        double cauchy_lorentz(double x);
};

class CrystalBallDist : public FiniteFunction {
    public:
        CrystalBallDist();
        CrystalBallDist(double range_min, double range_max, std::string outfile, double n, double alpha, double sigma, double xbar);

        void setn(double n);
        void setAlpha(double alpha);
        void setSigma(double sigma);
        void setXbar(double xbar);

        double n();
        double alpha();
        double sigma();
        double xbar();
        virtual double callFunction(double x);
        void printInfo();
        

    private:
        double m_n;
        double m_alpha;
        double m_sigma;
        double m_xbar;
        double crystal_ball(double x);
};