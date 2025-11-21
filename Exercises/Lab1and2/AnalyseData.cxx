#include "CustomFunctions.h"

void print_to_file(std::string inputfile, std::string errorfile, float p, float q, float chi_squared_metric)
{
    std::string output_name = "least_squares_model.txt";
    std::ofstream outStream;
    outStream.open(output_name);
    outStream << "Fitting to (x,y) data in " << inputfile << ":" << std::endl;
    outStream << "y = " << p << "x + " << q <<std::endl;
    outStream << "Using y errors from " << errorfile << ":" << std::endl;
    outStream << "Reduced chi-squared metric: " << chi_squared_metric << std::endl;
    outStream.close();
    std::cout << "Output written to 'least_squares_model.txt'" << std::endl;
}

void print_to_file(std::vector<float> x_data, std::vector<float> y_data, std::vector<float> func_output, std::string preamble, std::string filename)
{
    // This print script can be reused for print magnitudes and x^y output files.
    //
    std::string output_name = filename;
    std::ofstream outStream;
    outStream.open(output_name);
    outStream << preamble << std::endl;
    for (int i = 0; i < std::size(x_data); i++)
        {
        outStream << x_data[i] << ", " << y_data[i] <<", " << func_output[i] << std::endl;
        } 
    outStream.close();
    std::cout << "Output written to '" << filename << "'" << std::endl;

}



int main(){
    int option;
    do {
        std::cout << "Please select a function:" << std::endl;
        std::cout << "1) Print N lines of data" << std::endl;
        std::cout << "2) Calculate the magnitude of all datapoints" << std::endl;
        std::cout << "3) Least-squares fitting to a data file" << std::endl;
        std::cout << "4) Calculate x^y for all datapoints" << std::endl;
        std::cout << "5) Exit the program" << std::endl;
        std::cin >> option;
        std::cout << "" << std::endl;
        switch (option)
        {
            case 1: { // Print N lines of data from a given file to the terminal
                std::string inputfile; 
                std::cout << "Name of file to print from:" << std::endl;
                std::cin >> inputfile;
                auto [x_data, y_data] = read_xy_data(inputfile) ;
                if (x_data[0] == -1){
                // End the main() cluster if the file wasn't read in successfully.
                break;
                }   

                int Ndata;
                std::cout << "Number of datapoints to be sampled: " << std::endl;
                std::cin >> Ndata;

                print_xy_data(x_data, y_data, Ndata) ;
                break;
                    }
            case 2: { // Calculate the magnitude of the each datapoint, printing to an output file
                std::string inputfile; 
                std::cout << "Name of file to calculate magnitudes of" << std::endl;
                std::cin >> inputfile;
                auto [x_data, y_data] = read_xy_data(inputfile) ;
		
                if (x_data[0] == -1){
                    // End the main() cluster if the file wasn't read in successfully.
                    break;
                }
        	std::vector<float> magnitudes;
                for (int i = 0; i < std::size(x_data); i++)
                    {
                    float magnitude = calculate_magnitude(x_data[i], y_data[i]);
		    magnitudes.push_back(magnitude);
                    }
		std::string preamble = "x, y, |(x,y)|";
		std::string filename = "magnitudes.txt";
		print_to_file(x_data, y_data, magnitudes, preamble, filename);
                break;
            
                    }
            case 3: { // Perform a least-squares fit to a data file and an error file, printing to an output file
                std::string inputfile;
                std::cout << "Name of data file to fit least-squares to:" << std::endl;
                std::cin >> inputfile;
                auto [x_data, y_data] = read_xy_data(inputfile);
                if (x_data[0] == -1){
                    // End the main() cluster if the file wasn't read in successfully.
                    break;
                }
                auto [p, q] = least_squares_fit(x_data, y_data);
                
                std::string errorfile;
                std::cout << "Name of corresponding error file for chi-squared metric:" << std::endl;
                std::cin >> errorfile;
                auto [x_error, y_error] = read_xy_data(errorfile);
                if (y_error[0] == -1){
                    // End the main() cluster if the file wasn't read in successfully.
                    break;
                }
                float chi_squared_metric = chi_squared(x_data, y_data, y_error, p, q);
                print_to_file(inputfile, errorfile, p, q, chi_squared_metric);
                break;
                    }

            case 4: {
                std::string inputfile;
                std::cout << "Name of file to calculate x^y of:" << std::endl;
                std::cin >> inputfile;
                auto [x_data, y_data] = read_xy_data(inputfile) ;

                if (x_data[0] == -1){
                    // End the main() cluster if the file wasn't read in successfully.
                    break;
                }
                std::vector<float> xy_array;
                for (int i = 0; i < std::size(x_data); i++)
                    {
                    float xy = x_tothe_y(x_data[i], y_data[i]);
		    xy_array.push_back(xy);
                    }
		std::string preamble = "x, y, x^y";
                std::string filename = "x_tothey_y.txt";

                print_to_file(x_data, y_data, xy_array, preamble, filename);
                break;
                    }
            case 5: {
                std::cout << "Thank you for using this program! :)" << std::endl;
                break;
                    }
            
        }
    std::cout << "\n" << std::endl;
    } while (option != 5);
            
    return 0;
}
 
