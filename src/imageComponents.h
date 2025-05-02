#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <cmath>

using namespace std;

void createPixels(vector<pair<int[], float>> &input, int width, int height);
void createPSF(vector<pair<float, float>> &psf, int size);
void vectorToPPM(const vector<pair<int, float>>& output, const string& outputFilename, int width, int height);

