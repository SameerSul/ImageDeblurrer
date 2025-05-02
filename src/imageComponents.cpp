#include "imageComponents.h"

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



void createPSF(vector<pair<int, float>> &psf) 
{
    
}
