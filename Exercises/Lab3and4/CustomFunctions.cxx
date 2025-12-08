#define _USE_MATH_DEFINES
#include <cmath>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

GaussianDist::GaussianDist(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
  m_mu = 0.0;
  m_sigma = 1.0;
}

GaussianDist::GaussianDist(double range_min, double range_max, std::string outfile, double mu, double sigma){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  m_mu = mu;
  m_sigma = sigma;
  this->checkPath(outfile);
}

void GaussianDist::setMu(double mu) {m_mu = mu;};
void GaussianDist::setSigma(double sigma) {m_sigma = sigma;};

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

