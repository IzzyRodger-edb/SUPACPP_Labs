#include "FiniteFunctions.h"
#include "CustomFunctions.h"
std::vector<double> read_data(std::string file_name)
{
    std::ifstream data_file;
    data_file.open(file_name);

    // Verifying whether the file was successfully opened
    if (!data_file.is_open()) {
        std::cout << "Error opening file: " << file_name << std::endl;
        std::cout << "Please verify if it is in the current directory." << std::endl;
        std::vector<double> failure = {-1};

        return failure;
    }
    else{
        std::cout << "File: " << file_name << " opened successfully!" << std::endl;
    }

    std::vector<double> x_data;
    std::string line;
    double x;
    while (data_file >> x) {
        x_data.push_back(x);  
    }

    return x_data;
}


int main(){
std::string chosen_code;
std::cout << "Please input the code of mystery data to be used" << std::endl;
std::cin >> chosen_code;
std::string dataname = "Outputs/data/MysteryData" + chosen_code + ".txt";
std::string metro_label = "Metropolis Algorithm";
std::string random_label = "Random Sample " + chosen_code;
std::vector<double> randomData = read_data(dataname);
int Nbins = 800;
int N_metropolis_samples = 100000;
// One may enable the option of having Nbins as a user input by uncommenting the next 2 lines
//std::cout << "Number of bins for plotData:" << std::endl;
//std::cin >> Nbins;

std::cout << "Please select an option from the following distributions:" << std::endl;
std::cout << "1) Gaussian" << std::endl;
std::cout << "2) Cauchy-Lorentz" << std::endl;
std::cout << "3) Crystal Ball" << std::endl;
int choice;
std::cin >> choice;
if (choice == 1){
    std::cout << "Please input the mu and sigma you wish to use" << std::endl;
    double mu;
    double sigma;
    std::cin >> mu;
    std::cin >> sigma;
    std::string outname = "Gaussian";
    GaussianDist distribution(-10.0, 10.0, outname, mu, sigma);
    distribution.setDataName(random_label);
    distribution.setSampleName(metro_label);
    distribution.plotFunction();
    std::vector<double> metropolisData = distribution.generate_Metropolis_sample(N_metropolis_samples);
    distribution.plotData(metropolisData, Nbins, false);
    distribution.plotData(randomData, Nbins, true);
    distribution.printInfo();
    return 1;
};
if (choice == 2){
    std::cout << "Please input the x0 and gamma you wish to use" << std::endl;
    std::cout << "Note gamma must be greater than 0" << std::endl;
    double x0;
    double gamma;
    std::cin >> x0;
    std::cin >> gamma;
    std::string outname = "Cauchy-Lorentz";

    CauchyLorentzDist distribution(-10.0, 10.0, outname, x0, gamma);
    distribution.setDataName(random_label);
    distribution.setSampleName(metro_label);
    distribution.plotFunction();
    std::vector<double> metropolisData = distribution.generate_Metropolis_sample(N_metropolis_samples);
    distribution.plotData(metropolisData, Nbins, false);
    distribution.plotData(randomData, Nbins, true);
    distribution.printInfo();
    return 1;
};

if (choice == 3){
    std::cout << "Please input the n, alpha, sigma, and xbar you wish to use" << std::endl;
    std::cout << "Note that n must be greater than 1, and alpha must be greater than  0" << std::endl;
    double n;
    double alpha;
    double sigma;
    double xbar;
    std::cin >> n;
    std::cin >> alpha;
    std::cin >> sigma;
    std::cin >> xbar;
    std::string outname = "Crystal-Ball";

    CrystalBallDist distribution(-10.0, 10.0, outname, n, alpha, sigma, xbar);
    distribution.setDataName(random_label);
    distribution.setSampleName(metro_label);
    distribution.plotFunction();
    std::vector<double> metropolisData = distribution.generate_Metropolis_sample(N_metropolis_samples);
    distribution.plotData(metropolisData, Nbins, false);
    distribution.plotData(randomData, Nbins, true);
    distribution.printInfo();
    return 1;
};
std::cout << "Please select an option from 1 to 3" << std::endl;
return 1;

};
