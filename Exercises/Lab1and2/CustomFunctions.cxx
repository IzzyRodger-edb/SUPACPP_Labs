#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <cmath>

std::pair<std::vector<float>, std::vector<float>> read_xy_data(std::string file_name)
{
    std::ifstream data_file;
    data_file.open(file_name);

    // Verifying whether the file was successfully opened
    if (!data_file.is_open()) {
        std::cout << "Error opening file: " << file_name << std::endl;
        std::cout << "Please verify if it is in the current directory." << std::endl;
        std::vector<float> failure = {-1};

        return {failure, failure};
    }
    else{
        std::cout << "File: " << file_name << " opened successfully!" << std::endl;
    }

    std::vector<float> x_data;
    std::vector<float> y_data;

    std::string line;
    float x, y;
    // Skipping the first line, which is assumed to be a header as in the example provided.
    std::getline(data_file, line);

    while (std::getline(data_file, line))
    {
        std::stringstream ss(line);
        std::string value;
        // Read in the x value as before the comma
        if (std::getline(ss, value, ',')){
            x = std::stof(value);
            // Store the x value in the x_data array
            x_data.push_back(x);}
        // Read in the y value as after the comma
        if (std::getline(ss, value)){
            y = std::stof(value);
            // Store the y_value in the y_data array
            y_data.push_back(y);}
    }
    return {x_data, y_data};
}

void print_xy_data(std::vector<float> x_array, std::vector<float> y_array, int Nprint)
{
    if (std::size(x_array) != std::size(y_array))
    {
    std::cout << "X array and Y array are not of equal length, please verify gaps in your data and try again" << std::endl ;
    }

    int len_data = std::size(x_array);
    if (Nprint > len_data){
        std::cout << "Chosen number of data points (" << Nprint << ") is greater than the number of available data points (" << len_data << ")." << std::endl;
        std::cout << "Therefore, 5  data points will be used" << std::endl;
        Nprint = 5;} 
        std::cout << "x, y" << std::endl;
        for (int i = 0; i < Nprint; i++){
            std::cout << x_array[i] << ", " << y_array[i] << std::endl;
    }
    //return 0
}

float calculate_magnitude(float x, float y)
{
    return std::sqrt(x*x + y*y);
}

float sum_array(std::vector<float> array)
{   // Perform a summation over the elements of an array
    int len_array = std::size(array);
    float array_sum = 0;
    for (int i=0; i < len_array; i++){
        array_sum += array[i];
        }
    return array_sum;
}

std::vector<float> multiply_array(std::vector<float> array1, std::vector<float> array2)
{  // Calculate the dot product of two arrays
    int len_array = std::size(array1);
    std::vector<float> array_product;
    for (int i=0; i < len_array; i++){
        array_product.push_back(array1[i] * array2[i]);
        }
    return array_product;
}

std::pair<float, float> least_squares_fit(std::vector<float> x_data, std::vector<float> y_data)
{
    int N = std::size(x_data);
    // Using the provided formulae: y = px + q
    // Calculating p, 
    float numerator = N*sum_array(multiply_array(x_data, y_data)) - sum_array(x_data)*sum_array(y_data);
    float denominator = N*sum_array(multiply_array(x_data, x_data)) - sum_array(x_data)*sum_array(x_data);

    float p = numerator/denominator;

    //Calculating q, which only requires changing the numerator,
    numerator = sum_array(multiply_array(x_data, x_data))*sum_array(y_data) - sum_array(multiply_array(x_data, y_data))*sum_array(x_data);

    float q = numerator/denominator;

    return {p, q};
}

float chi_squared(std::vector<float> x_data, std::vector<float> y_data, std::vector<float> y_error, float p, float q)
{  // Using additional data for the error on the y-values, calculate the chi-squared metric for the least-squares fit.
   int N = std::size(x_data);
   float chi_squared = 0;
   for (int i = 0; i < N; i++){
       chi_squared += ((y_data[i] - (p*x_data[i] + q))/y_error[i]) * ((y_data[i] - (p*x_data[i] + q))/y_error[i]) ;
   }   
   // Model has 2 parameters (p,q), therefore NDOF = N - 2
   chi_squared = chi_squared/(N-2);
   return chi_squared;
}

float x_tothe_y(float x, float y)
{   // Use the built-in pow command to raise x to the power of y, which has been rounded to the nearest integer.
    x = std::pow(x, std::round(y));
    return x;
}

