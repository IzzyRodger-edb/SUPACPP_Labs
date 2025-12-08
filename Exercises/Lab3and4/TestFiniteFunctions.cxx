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

GaussianDist test_func(-10, 10, "Gaussian", -2, 0.02);
test_func.plotFunction();
std::string dataname = "Outputs/data/MysteryData21021.txt";
std::vector<double> randomData = read_data(dataname);
int Nbins;
std::cout << "Number of bins for plotData:" << std::endl;
std::cin >> Nbins;
int Ndiv = 2;
for (int i = 0; i < Ndiv; i++){
    std::cout << i << std::endl;
  }
test_func.plotData(randomData, Nbins);
test_func.printInfo();
return 1;
}