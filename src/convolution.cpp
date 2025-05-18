#include "convolution.h"
// this is going to be block convolution now

// NEED TO CHANGE THIS SUCH THAT WE NOW MULTIPLY THE RGB FLOAT FACTOR SCALARLY TO THE INPUT RGB INT[] ARRAY

// need to change this algorithm such that it better adheres to the math behind gaussian blurring



// void Convolution(vector<pair<array<int, 3>, float>> &output, 
//     vector<pair<array<int, 3>, float>> &input, 
//     vector<pair<float, float>> &psf)
// {
// cout << "entering convolution" << endl;
// output.clear();
// output.resize(input.size(), make_pair(array<int, 3>{0, 0, 0}, 0.0f));
// cout << "output size: " << output.size() << endl;

// int width = static_cast<int>(sqrt(input.size()));
// int height = width;
// int psfSize = static_cast<int>(sqrt(psf.size())); 
// int psfHalf = psfSize / 2;

// cout << "Image dimensions: " << width << "x" << height << endl;
// cout << "PSF size: " << psfSize << "x" << psfSize << endl;

// for (int y = 0; y < height; y++) {
// for (int x = 0; x < width; x++) {
// array<float, 3> rgbSum = {0.0f, 0.0f, 0.0f};
// float intensitySum = 0.0f;

// // Apply the kernel
// for (int ky = -psfHalf; ky <= psfHalf; ky++) {
//    for (int kx = -psfHalf; kx <= psfHalf; kx++) {
//        int pixelX = x + kx;
//        int pixelY = y + ky;

//        // Handle boundaries during calculations instead of afterwards
//        pixelX = max(0, min(width - 1, pixelX));
//        pixelY = max(0, min(height - 1, pixelY));
       
//        int pixelIndex = pixelY * width + pixelX;
//        int psfIndex = (ky + psfHalf) * psfSize + (kx + psfHalf);
       
//        if (psfIndex >= psf.size()) {
//            cout << "PSF index out of bounds: " << psfIndex << endl;
//            continue;
//        }
       
//        float kernelValue = psf[psfIndex].first;
       
//        rgbSum[0] += input[pixelIndex].first[0] * kernelValue;
//        rgbSum[1] += input[pixelIndex].first[1] * kernelValue;
//        rgbSum[2] += input[pixelIndex].first[2] * kernelValue;
//        intensitySum += input[pixelIndex].second * kernelValue;
//    }
// }

// // Store result
// int outputIndex = y * width + x;
// output[outputIndex].first[0] = static_cast<int>(round(rgbSum[0]));
// output[outputIndex].first[1] = static_cast<int>(round(rgbSum[1]));
// output[outputIndex].first[2] = static_cast<int>(round(rgbSum[2]));
// output[outputIndex].second = intensitySum;
// }
// }

// cout << "finished convolution" << endl;
// }


void gaussianBlurring(vector<pair<array<int, 3>, float>> &output, 
    vector<pair<array<int, 3>, float>> &input, 
    vector<pair<float, float>> &psf, int width, int height, int kernel_size)
{
    cout << "Gaussian Started" << endl;

    // Create kernel radius
    int kernel_radius = kernel_size / 2; 

    // Iterate through all pixels
    for (int i = 0; i < input.size(); i++) {
        // Calculate x and y positions for the current pixel
        int y_pos = i / width;
        int x_pos = i % width;

        float new_r = 0.0f;
        float new_g = 0.0f;
        float new_b = 0.0f;

        // Apply Gaussian kernel
        for (int kernel_ypos = -kernel_radius; kernel_ypos <= kernel_radius; kernel_ypos++) {
            for (int kernel_xpos = -kernel_radius; kernel_xpos <= kernel_radius; kernel_xpos++) {
                int neighbour_xpos = x_pos + kernel_xpos;
                int neighbour_ypos = y_pos + kernel_ypos;

                // Handle edge cases
                if (neighbour_ypos < 0) neighbour_ypos = 0;
                if (neighbour_ypos >= height) neighbour_ypos = height - 1;
                if (neighbour_xpos < 0) neighbour_xpos = 0;
                if (neighbour_xpos >= width) neighbour_xpos = width - 1;

                // Convert 2D coordinates back to 1D index
                int pixel_pos = neighbour_ypos * width + neighbour_xpos;

                // Get PSF weight
                int psf_index = (kernel_ypos + kernel_radius) * kernel_size + (kernel_xpos + kernel_radius);
                float weight = psf[psf_index].first;

                // Perform weighted sum for RGB values
                new_r += weight * input[pixel_pos].first[0];
                new_g += weight * input[pixel_pos].first[1];
                new_b += weight * input[pixel_pos].first[2];
            }
        }

        // Cast and assign to output accordingly
        output[i].first[0] = static_cast<int>(new_r);
        output[i].first[1] = static_cast<int>(new_g);
        output[i].first[2] = static_cast<int>(new_b);

        // Preserve the grayscale intensity
        output[i].second = input[i].second;
    }

    cout << "Output Assigned" << endl;

        }
// can use classic randomly determined impulse response for psf later....

