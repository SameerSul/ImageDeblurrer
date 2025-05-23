#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bitset>
#include <array>
#include <cmath>

using namespace std;

void Convolution(vector<pair<array<int, 3>, float>> &output, vector<pair<array<int, 3>, float>> &input, vector<pair<float,float>> &psf); 

void gaussianBlurring(vector<pair<array<int, 3>, float>> &output, 
    vector<pair<array<int, 3>, float>> &input, 
    vector<pair<float, float>> &psf, int width, int height, int kernel_size);
bool checkGaussianBlurSetup(
        const vector<pair<array<int, 3>, float>> &input,
        const vector<pair<array<int, 3>, float>> &output,
        const vector<pair<float, float>> &psf,
        int width, int height, int kernel_size);