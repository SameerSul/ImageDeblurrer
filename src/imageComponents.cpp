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
    
    // Adjust sigma based on kernel size
    float sigma = (size - 1) / 6.0f;
    if (sigma < 1.0f) sigma = 1.0f;
    
    psf.resize(size * size);
    int halfSize = size / 2;
    
    float sum = 0.0f;
    int index = 0;

    cout << "Starting kernel generation, size: " << size << endl;

    // Generate Gaussian kernel
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            
            // Convert to centered coordinates because some even numbers were causing problems
            int centered_x = x - halfSize;
            int centered_y = y - halfSize;
            
            float value = (1.0f / (2.0f * M_PI * sigma * sigma)) * 
                          exp(-(centered_x*centered_x + centered_y*centered_y) / (2.0f * sigma * sigma));
            
            if (index < 5) cout << "Index " << index << ": value = " << value << endl;
            
            psf[index].first = value;
            psf[index].second = value;
            
            sum += value;
            index++;
        }
    }

    cout << "Sum before normalization: " << sum << endl;
    
    // DEBUGGING - Check first few values before normalization
    // for (int i = 0; i < min(5, (int)psf.size()); i++) {
    //     cout << "Before norm - psf[" << i << "].first = " << psf[i].first << endl;
    // }

    // Normalize the kernel
    for (int i = 0; i < psf.size(); i++) {
        psf[i].first = psf[i].first / sum;
        psf[i].second = psf[i].second / sum;
    }
    
    // DEBUGGING - Check first few values after normalization  
    // for (int i = 0; i < min(5, (int)psf.size()); i++) {
    //     cout << "After norm - psf[" << i << "].first = " << psf[i].first << endl;
    // }

    cout << "PSF left" << endl;
}

void vectorToPPM(vector<pair<array<int, 3>, float>>& data, const string& filename, int width, int height) {
    ofstream file(filename);
    file << "P3\n" << width << " " << height << "\n255\n";
    
    for (const auto& pixel : data) {
        file << pixel.first[0] << " " 
             << pixel.first[1] << " " 
             << pixel.first[2] << " ";
    }
    file.close();
}

// DEBUGGING - Making sure that PSF has center pixel as highest value
// void printKernel(const vector<pair<float, float>> &kernel) {
//     cout << "printKernel entered" << endl;
    
//     cout << "Kernel vector size: " << kernel.size() << endl;
    
//     if (kernel.empty()) {
//         cout << "Error: Kernel is empty!" << endl;
//         return;
//     }
    
//     int size = static_cast<int>(sqrt(kernel.size()));
//     cout << "Calculated kernel size: " << size << "x" << size << endl;
    
//     // Check if it's a perfect square
//     if (size * size != kernel.size()) {
//         cout << "Warning: Kernel size is not a perfect square! Expected " << size*size << ", got " << kernel.size() << endl;
//     }
    
//     cout << "About to print kernel values..." << endl;
    
//     // Print kernel values
//     cout << "Kernel values:" << endl;
//     for (int y = 0; y < size; y++) {
//         cout << "Row " << y << ": ";
//         for (int x = 0; x < size; x++) {
//             int index = y * size + x;
//             if (index >= kernel.size()) {
//                 cout << "INDEX_ERROR ";
//                 break;
//             }
//             cout << kernel[index].first << "\t";
//         }
//         cout << endl;
//     }
    
//     cout << "Calculating sum..." << endl;
    
//     // Verify kernel sum
//     float sum = 0.0f;
//     for (int i = 0; i < kernel.size(); i++) {
//         sum += kernel[i].first;
//         if (i < 5) { // Debug first few values
//             cout << "kernel[" << i << "].first = " << kernel[i].first << endl;
//         }
//     }
//     cout << "Kernel sum: " << sum << " (should be close to 1.0)" << endl;
    
//     cout << "printKernel finished" << endl;
// }
