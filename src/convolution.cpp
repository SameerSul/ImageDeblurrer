#include "convolution.h"
void Convolution(vector<pair<int, float>> &output, const vector<pair<int, float>> &input, vector<pair<int,float>> &psf) 
{
    output.clear();
    output.resize(input.size() + psf.size() - 1, {0.0, 0.0}); 
    
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < psf.size(); j++)
        {
                output[i].first += input[i].first*psf[j].first;
                output[i].second += input[i].second*psf[j].second;
        }
    }

}

// can use classic randomly determined impulse response for psf later....

