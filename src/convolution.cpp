#include "convolution.h"
// this is going to be block convolution now

// NEED TO CHANGE THIS SUCH THAT WE NOW MULTIPLY THE RGB FLOAT FACTOR SCALARLY TO THE INPUT RGB INT[] ARRAY
void Convolution(vector<pair<array<int, 3>, float>> &output, vector<pair<array<int, 3>, float>> &input, vector<pair<float, float>> &psf) 
{
    cout << "entering convolution" << endl;
    output.clear();
    output.resize(input.size(), make_pair(array<int, 3>{0, 0, 0}, 0.0f)); // Initialize output with default values
    cout << "output size: " << output.size() << endl;

    int width = static_cast<int>(sqrt(input.size())); // Assuming input is a square image
    int height = width; // For simplicity, width = height
    int psfSize = static_cast<int>(sqrt(psf.size())); // PSF is a square matrix
    int psfHalf = psfSize / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            array<float, 3> rgbSum = {0.0f, 0.0f, 0.0f};
            float intensitySum = 0.0f;

            // Apply the PSF (Gaussian kernel)
            for (int ky = -psfHalf; ky <= psfHalf; ky++) {
                for (int kx = -psfHalf; kx <= psfHalf; kx++) {
                    int pixelX = x + kx;
                    int pixelY = y + ky;

                    // Check bounds
                    if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height) {
                        int pixelIndex = pixelY * width + pixelX;
                        int psfIndex = (ky + psfHalf) * psfSize + (kx + psfHalf);

                        rgbSum[0] += input[pixelIndex].first[0] * psf[psfIndex].first; // Red
                        rgbSum[1] += input[pixelIndex].first[1] * psf[psfIndex].first; // Green
                        rgbSum[2] += input[pixelIndex].first[2] * psf[psfIndex].first; // Blue
                        intensitySum += input[pixelIndex].second * psf[psfIndex].second; // Grayscale intensity
                    }
                }
            }

            // Store the result in the output
            int outputIndex = y * width + x;
            output[outputIndex].first[0] = static_cast<int>(rgbSum[0]);
            output[outputIndex].first[1] = static_cast<int>(rgbSum[1]);
            output[outputIndex].first[2] = static_cast<int>(rgbSum[2]);
            output[outputIndex].second = intensitySum;
        }
    }

    cout << "finished convolution" << endl;
}

// can use classic randomly determined impulse response for psf later....

