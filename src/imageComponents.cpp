#include "imageComponents.h"

#define PI 3.14159 // approximation for now

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

    float sigma = rand() % (3 - 1 + 1) + 1;
    psf.resize(pow(size, 2));
    int index = 0;
    float norm = 0.0;

    // Generate Gaussian kernel
    for (int y = -1; y < 2; y++) {
        for (int x = -1; x < 2; x++) {
            psf[index].first = psf[index].second = (1 / (2 * PI * pow(sigma, 2))) * exp(-(pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2)));
            norm += psf[index].first;
            index++;
        }
    }

    // Normalize the kernel with this scuffed ahh method
    for (int i = 0; i < psf.size(); i++) {
        psf[i].first = psf[i].second = psf[i].first / norm;
    }

    cout << "PSF left" << endl;
}

void vectorToPPM(vector<pair<array<int, 3>, float>> &output, const string &outputFilename, int width, int height)
{
    cout << "entered vectortoppm" << endl;
    ofstream outputFile(outputFilename, ios::out | ios::binary);

    if (!outputFile) {
        cerr << "Error: Could not open output file " << outputFilename << endl;
        return;
    }

    // Write PPM header
    outputFile << "P3" << endl;              // ASCII PPM format
    outputFile << width << " " << height << endl; // Width and height
    outputFile << "255" << endl;            // Max color value

    // Write pixel data
    for (const auto &pixel : output) {
        unsigned char r = pixel.first[0];
        unsigned char g = pixel.first[1];
        unsigned char b = pixel.first[2];

        outputFile << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << " ";
    }

    outputFile.close();
    cout << "Saved image as " << outputFilename << endl;
}
