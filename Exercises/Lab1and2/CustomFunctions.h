#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <cmath>

std::pair<std::vector<float>, std::vector<float>> read_xy_data(std::string);
void print_xy_data(std::vector<float>, std::vector<float>, int);
float calculate_magnitude(float, float);
float sum_array(std::vector<float>);
std::vector<float> multiply_array(std::vector<float>, std::vector<float>);
std::pair<float, float> least_squares_fit(std::vector<float>, std::vector<float>);
float chi_squared(std::vector<float>, std::vector<float>, std::vector<float>, float, float);
float x_tothe_y(float, float);
