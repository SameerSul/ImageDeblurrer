#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <cmath>
#include <array>

using namespace std;

void createPixels(vector<pair<array<int, 3>, float>> &input, int width, int height);
void createPSF(vector<pair<float, float>> &psf, int size);
void vectorToPPM(vector<pair<array<int, 3>, float>> &output, const string& outputFilename, int width, int height);

