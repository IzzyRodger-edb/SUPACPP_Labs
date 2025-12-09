#define _USE_MATH_DEFINES
#include <cmath>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

// Custom functions for the gaussian distribution
GaussianDist::GaussianDist(){
  m_RMin = -5.0;
  m_DataName = 'data';
  m_RMax = 5.0;
  this->checkPath("Gaussian");
  m_Integral = NULL;
  m_mu = 0.0;
  m_sigma = 1.0;
}

GaussianDist::GaussianDist(double range_min, double range_max, std::string outfile, double mu, double sigma){
  m_RMin = range_min;
  m_DataName = 'data';
  m_RMax = range_max;
  m_Integral = NULL;
  m_mu = mu;
  m_sigma = sigma;
  this->checkPath(outfile);
}

void GaussianDist::setMu(double mu) {m_mu = mu;};
void GaussianDist::setSigma(double sigma) {m_sigma = sigma;};
double GaussianDist::mu() {return m_mu;};
double GaussianDist::sigma() {return m_sigma;};

double GaussianDist::gaussian(double x){
return 1/(m_sigma * std::pow((2* 3.14159265), 0.5)) * std::pow(2.71828, -0.5*std::pow(((x-m_mu)/m_sigma), 2));
};
double GaussianDist::callFunction(double x) {return this->gaussian(x);}; //(overridden from base class)

void GaussianDist::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "mu: " << m_mu << std::endl;
  std::cout << "sigma: " << m_sigma << std::endl; 
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

// Custom functions for the Cauchy-Lorentz Distribution
CauchyLorentzDist::CauchyLorentzDist(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  m_DataName = 'data';
  this->checkPath("Cauchy-Lorentz");
  m_Integral = NULL;
  m_x0 = 0.0;
  m_gamma = 1.0;
}

CauchyLorentzDist::CauchyLorentzDist(double range_min, double range_max, std::string outfile, double x0, double gamma){
  m_RMin = range_min;
  m_RMax = range_max;
  m_DataName = 'data';
  m_Integral = NULL;
  m_x0 = x0;
  if (0 >= gamma){
    std::cout << "Your choice of gamma violates the condition that gamma be greater than 0" << std::endl;
    std::cout << "Defaulting to gamma = 1.0" << std::endl;
    m_gamma = 1.0;
  }
  else{
    m_gamma = gamma;
  }
  this->checkPath(outfile);
}

void CauchyLorentzDist::setx0(double x0) {m_x0 = x0;};
void CauchyLorentzDist::setGamma(double gamma) {m_gamma = gamma;};
double CauchyLorentzDist::x0() {return m_x0;};
double CauchyLorentzDist::gamma() {return m_gamma;};

double CauchyLorentzDist::cauchy_lorentz(double x){
return 1/(3.14159265*m_gamma*(1+ std::pow(((x-m_x0)/m_gamma), 2)));
};

double CauchyLorentzDist::callFunction(double x) {return this->cauchy_lorentz(x);}; //(overridden from base class)

void CauchyLorentzDist::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "x0: " << m_x0 << std::endl;
  std::cout << "gamma: " << m_gamma << std::endl; 
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

// Crystal Ball Distribution
CrystalBallDist::CrystalBallDist(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  m_DataName = 'data';
  this->checkPath("Crystal Ball");
  m_Integral = NULL;
  m_n = 3.0;
  m_alpha = 1.0;
  m_sigma = 1.0;
  m_xbar = 0.0;
}

CrystalBallDist::CrystalBallDist(double range_min, double range_max, std::string outfile, double n, double alpha, double sigma, double xbar){
  m_RMin = range_min;
  m_RMax = range_max;
  m_DataName = 'data';
  m_Integral = NULL;
  m_sigma = sigma;
  m_xbar = xbar;
  if (0 >= alpha){
    std::cout << "Your choice of alpha violates the condition that alpha be greater than 0" << std::endl;
    std::cout << "Defaulting to alpha = 1.0" << std::endl;
    m_alpha = 1.0;
  }
  else{
    m_alpha = alpha;
  }
  if (1 >= n){
    std::cout << "Your choice of n violates the condition that n be greater than 1" << std::endl;
    std::cout << "Defaulting to n = 2.0" << std::endl;
    m_n = 1.0;
  }
  else{
    m_n = n;
  }
  this->checkPath(outfile);
}

void CrystalBallDist::setn(double n) {m_n = n;};
void CrystalBallDist::setAlpha(double alpha) {m_alpha = alpha;};
void CrystalBallDist::setSigma(double sigma) {m_sigma = sigma;};
void CrystalBallDist::setXbar(double xbar) {m_xbar = xbar;};
double CrystalBallDist::n() {return m_n;};
double CrystalBallDist::alpha() {return m_alpha;};
double CrystalBallDist::sigma() {return m_sigma;};
double CrystalBallDist::xbar() {return m_xbar;};

double CrystalBallDist::crystal_ball(double x){
  double C = (m_n/std::abs(m_alpha)) * (1/(m_n - 1)) * std::pow(2.71828, -(std::pow(std::abs(m_alpha), 2))/2);
  double D = std::sqrt(3.14159265/2) * (1 + std::erf(std::abs(m_alpha)/std::sqrt(2)));
  double N = 1/(m_sigma * (C + D));

  if((x-m_xbar)/m_sigma > -m_alpha){
    return N * std::pow(2.71828, -(0.5 * std::pow((x-m_xbar)/m_sigma, 2)));
  }
  else{
    double A = std::pow((m_n/std::abs(m_alpha)), m_n) * std::pow(2.71828, -0.5*std::pow(std::abs(m_alpha),2));
    double B = (m_n/std::abs(m_alpha)) - std::abs(m_alpha);

    return N * A * std::pow((B - ((x-m_xbar)/m_sigma)), -m_n);
  }
};

double CrystalBallDist::callFunction(double x) {return this->crystal_ball(x);}; //(overridden from base class)

void CrystalBallDist::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "n: " << m_n << std::endl;
  std::cout << "alpha: " << m_alpha << std::endl; 
  std::cout << "sigma: " << m_sigma << std::endl; 
  std::cout << "x-bar: " << m_xbar << std::endl; 
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}