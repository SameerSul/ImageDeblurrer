#include "convolution.h"
// this is going to be block convolution now
void Convolution(vector<pair<int, float>> &output, vector<pair<int[], float>> &input, vector<pair<float,float>> &psf) 
{
    output.clear();
    output.resize(input.size() + psf.size() - 1, {0.0, 0.0}); 
    
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < psf.size(); j++)
        {
                output[i+j].first += input[i].first*psf[j].first;
                output[i+j].second += input[i].second*psf[j].second;
        }
    }

    // remove the first and last element, and resize accordingly
    output.erase(output.begin());
    output.erase(output.end() - 1);
    output.resize(input.size());
    // vector<pair<int, float>> temp;
    // for (int k = 1; k < temp.size() - 1; k++)
    // {
    //     output[k].first = temp[k].first;
    //     output[k].second = temp[k].second;
    // }

}

// can use classic randomly determined impulse response for psf later....

