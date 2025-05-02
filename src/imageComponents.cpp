#include "imageComponents.h"

#define PI 3.14159 // approximation for now

// this is to create the vector of pairs
using namespace std;

void createPixels(vector<pair<int, float>> &input) 
{
    // Open the text file containing space-separated byte values
    ifstream binary("testImage.txt");
    if (!binary) {
        cerr << "Error opening text file" << endl;
        return;
    }

    int byteBuffer[3];
    int index = 0;
    
    // store 3 ints at a time in buffer, each packet of 3 is 1 rgb val
    while (true) {
        for (int i = 0; i < 3; i++) {
            if (!(binary >> byteBuffer[i])) {
                // If we dont have enough values, fill the rest w/ zeroes
                if (i > 0) {
                    for (int j = i; j < 3; j++) {
                        byteBuffer[j] = 0;
                    }
                    break;
                } else {
                    // No values read at all, exit the function
                    binary.close();
                    return;
                }
            }
        }
        
        // Check if we need to resize the input vector
        if (index >= input.size()) {
            input.resize(input.size() * 2);
        }
        
        // RGB values
        int r = byteBuffer[0];
        int g = byteBuffer[1];
        int b = byteBuffer[2];

        // Store RGB data and intensity
        input[index].first = r << 16 | g << 8 | b;
        input[index].second = 0.299*r + 0.587*g + 0.114*b; // Grayscale conversion formula
        index++;
    }
    
    // Resize vector to actual used size
    if (index < input.size()) {
        input.resize(index);
    }
    
    binary.close();
}


// Will use a normal gaussian blur matrix to convolute our values with for now
void createPSF(vector<pair<float, float>> &psf, int size) 
{
    float sigma = rand() % (3 - 1 + 1) + 1;
    psf.resize(pow(size, 2));
    // lets stick with a 3x3 matrix for now
    int index = 0;
    float norm = 0.0;
    // coordinates of matrix, so we'll have to run this in a for loop, in a really weird order since 00 is center of matrix
    for (int y = -1; y < 2; y++)
        for (int x = -1; x < 2; x++)
            {
                psf[index].first = psf[index].second = (1/(2*PI*pow(sigma, 2))) * exp(-(pow(x, 2) + pow(y, 2))/(2*pow(sigma, 2)));
                norm += psf[index].first;
                index++;
            }
    // really scuffed scalar division normalization

    for (int i = 0; i < psf.size(); i++) {psf[i].first = psf[i].second = psf[i].first/norm;}
            

}
