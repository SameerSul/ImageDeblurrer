#include "imageComponents.h"

#define M_PI 3.14159 // approximation for now

using namespace std;

void createPixels(vector<pair<array<int, 3>, float>> &input, int width, int height)
{
    ifstream binary("testingImage.txt");
    if (!binary) {
        cerr << "Error opening text file" << endl;
        return;
    }

    if (input.empty()) {
        input.resize(width * height); // Resize to the number of pixels
    }

    int index = 0;
    cout << "Starting to process pixels..." << endl;

    while (binary) {
        int bytesRead = 0;

        // Read RGB values directly into std::array
        for (int i = 0; i < 3; i++) {
            if (binary >> input[index].first[i]) {
                bytesRead++;
            } else {
                input[index].first[i] = 0; // Fill remaining values with 0 if not enough data
            }
        }

        if (bytesRead == 0) {
            break; // Exit if no values were read
        }

        // Calculate grayscale intensity
        int r = input[index].first[0];
        int g = input[index].first[1];
        int b = input[index].first[2];
        input[index].second = 0.299 * r + 0.587 * g + 0.114 * b;

        index++;

        if (index >= input.size()) {
            break; // Stop if we've processed all pixels
        }
    }

    binary.close();
    cout << "Finished processing pixels." << endl;
}

void createPSF(vector<pair<float, float>> &psf, int size)
{
    cout << "PSF entered" << endl;

    float sigma = 10.0f; // removed random bc i want fixed results for debugging and it doesn't really matter too much
    psf.resize(size * size);
    int halfSize = size / 2;
    
    float sum = 0.0f;
    int index = 0;

    // Generate Gaussian kernel
    for (int y = -halfSize; y <= halfSize; y++) {
        for (int x = -halfSize; x <= halfSize; x++) {
            float value = (1.0f / (2.0f * M_PI * sigma * sigma)) * 
                          exp(-(x*x + y*y) / (2.0f * sigma * sigma));
            
            psf[index].first = psf[index].second = value;
            sum += value;
            index++;
        }
    }

    // Normalize the kernel
    for (int i = 0; i < psf.size(); i++) {
        psf[i].first = psf[i].second = psf[i].first / sum;
    }

    cout << "PSF left" << endl;
}

void vectorToPPM(vector<pair<array<int, 3>, float>> &output, const string &outputFilename, int width, int height)
{
    cout << "entered vectortoppm" << endl;
    ofstream outputFile(outputFilename); // Text mode for P3 format

    if (!outputFile) {
        cerr << "Error: Could not open output file " << outputFilename << endl;
        return;
    }

    // Write PPM header
    outputFile << "P3" << endl;
    outputFile << width << " " << height << endl;
    outputFile << "255" << endl;

    // Write pixel data
    for (const auto &pixel : output) {
        // Clamp values to 0-255 range
        int r = max(0, min(255, pixel.first[0]));
        int g = max(0, min(255, pixel.first[1]));
        int b = max(0, min(255, pixel.first[2]));

        outputFile << r << " " << g << " " << b << " ";
    }

    outputFile.close();
    cout << "Saved image as " << outputFilename << endl;
}
// Add this function to help debug your kernel
void printKernel(const vector<pair<float, float>> &kernel) {
    int size = static_cast<int>(sqrt(kernel.size()));
    cout << "Kernel size: " << size << "x" << size << endl;
    
    // Print kernel values
    cout << "Kernel values:" << endl;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int index = y * size + x;
            cout << kernel[index].first << "\t";
        }
        cout << endl;
    }
    
    // Verify kernel sum (should be very close to 1.0 for a normalized kernel)
    float sum = 0.0f;
    for (const auto &k : kernel) {
        sum += k.first;
    }
    cout << "Kernel sum: " << sum << " (should be close to 1.0)" << endl;
}