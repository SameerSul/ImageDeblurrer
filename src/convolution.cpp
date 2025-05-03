#include "convolution.h"
// this is going to be block convolution now

// NEED TO CHANGE THIS SUCH THAT WE NOW MULTIPLY THE RGB FLOAT FACTOR SCALARLY TO THE INPUT RGB INT[] ARRAY
void Convolution(vector<pair<array<int, 3>, float>> &output, vector<pair<array<int, 3>, float>> &input, vector<pair<float, float>> &psf) 
{
    cout << "entering convolution" << endl;
    output.clear();
    output.resize(input.size() + psf.size() - 1, make_pair(array<int, 3>{0, 0, 0}, 0.0f)); // Explicitly construct the pair to avoid dumb error
    cout << "output size: " << output.size() << endl;
    int counter = 0;
    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = 0; j < psf.size(); j++) {
            if (i + j < output.size()) { // Ensure index is within bounds
                output[i + j].first[0] += input[i].first[0] * psf[j].first; // Red
                output[i + j].first[1] += input[i].first[1] * psf[j].first; // Green
                output[i + j].first[2] += input[i].first[2] * psf[j].first; // Blue

                output[i + j].second += input[i].second * psf[j].second; // Grayscale intensity
                counter++;
            }
        }
    }

    // Resize to match the input size after convolution
    if (output.size() > input.size()) {
        output.resize(input.size());
    }

    cout << "resized to " << input.size() << " pixels and finished convolution" << endl;
}

// can use classic randomly determined impulse response for psf later....

