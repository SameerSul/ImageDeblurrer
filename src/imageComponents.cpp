#include "imageComponents.h"

// this is to create the vector of pairs
using namespace std;

void createPixels(vector<pair<int, float>> &input, vector<pair<int,float>> &psf) 
{
    ifstream binary("binaryTestImage.txt", ios::binary);

    int byteBuffer[3];
    int index = 0;
    char byte; 
    while (true)
    {
        binary.read(reinterpret_cast<char*>(byteBuffer), 3);
        
        // exit condition

        if (binary.gcount() == 0 || binary.eof()) {break;}

        // in case we have an incomplete group, fill with 0's, o.w skyp
        if (binary.gcount() < 3)
        {
            for (int i = binary.gcount(); i < 3; i++)
            {
                byteBuffer[i] = 0;
            }
        }

        // Now load up values for pixel classes
        int r = byteBuffer[0];
        int g = byteBuffer[1];
        int b = byteBuffer[2];


        input[index].first = r << 16 | g << 8 | b;
        input[index].second = 0.299*r+0.587*g+0.114*b; // int value of whatever this is 
        index++;
    }

}
