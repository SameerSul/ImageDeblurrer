#include "imageComponents.h"

#define PI 3.14159 // approximation for now

// this is to create the vector of pairs
using namespace std;
int counter = 0;
void createPixels(vector<pair<int[], float>> &input, int width, int height) 
{
// Open the text file containing space-separated byte values
    ifstream binary("testingImage.txt");
    if (!binary) {
        cerr << "Error opening text file" << endl;
        return;
    }

    if (input.empty()) {
        input.resize(width * height);  // Resize to the number of pixels
    }

    int byteBuffer[3] = {0, 0, 0}; // Buffer to hold RGB values so we can calculate intensity and put it in our pairs
    int index = 0;

    cout << "Starting to process pixels..." << endl;

    while (binary) {
        int bytesRead = 0;

        // Read 3 values into the buffer
        for (int i = 0; i < 3; i++) {
            if (binary >> byteBuffer[i]) {
                bytesRead++;
            } else {
                byteBuffer[i] = 0; // Fill remaining values with 0 if not enough remaining
            }
        }

        if (bytesRead == 0) {
            break; // Exit if no values were read
        }

        // Store RGB data and intensity
        int r = byteBuffer[0];
        int g = byteBuffer[1];
        int b = byteBuffer[2];


        // need separators to define
        // input[index].first = (r << 17) | (x << 16) | (g << 8) | (x << 7) | b; // Pack RGB into a single int


        input[index].first = byteBuffer; // Pack RGB into array
        input[index].second = (0.299 * r + 0.587 * g + 0.114 * b) / (r+b+g); // Grayscale intensity
        index++;

        if (index >= input.size()) {
            break; // Stop if we've processed all pixels
        }
    }

    binary.close();
    cout << "Finished processing pixels." << endl;
}

// Will use a normal gaussian blur matrix to convolute our values with for now
void createPSF(vector<pair<float, float>> &psf, int size) 
{
    cout << "PSF entered" << endl;

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
    cout << "PSF left" << endl;
        
}

// need to convert from Vector to ppm values -> CHANGE TO ACCOMODATE FOR INT[]

void vectorToPPM(const vector<pair<int, float>>& output, const string& outputFilename, int width, int height) {
    // Open output file
    ofstream outputFile(outputFilename, ios::out | ios::binary);
    
    if (!outputFile) {
        cerr << "Error: Could not open output file " << outputFilename << endl;
        return;
    }
    
    // Write PPM header
    outputFile << "P3" << endl;              // Binary PPM format
    outputFile << width << " " << height << endl;  // Width and height
    outputFile << "255" << endl;             // Maximum color value
    
    // Write pixel data
    for (const auto& pixel : output) {
        // Extract RGB components from packed int
        unsigned char r = (pixel.first >> 16) & 0xFF;
        unsigned char g = (pixel.first >> 8) & 0xFF;
        unsigned char b = pixel.first & 0xFF;
        
        // Write RGB values to file
        outputFile.write(reinterpret_cast<const char*>(&r), 1);
        outputFile.write(reinterpret_cast<const char*>(&g), 1);
        outputFile.write(reinterpret_cast<const char*>(&b), 1);
    }
    
    outputFile.close();
    cout << "Saved image saved as " << outputFilename << endl;
}
