#include "convolution.h"
// this is going to be block convolution now

// NEED TO CHANGE THIS SUCH THAT WE NOW MULTIPLY THE RGB FLOAT FACTOR SCALARLY TO THE INPUT RGB INT[] ARRAY
// Fixed convolution function
// Fixed convolution function
void Convolution(vector<pair<array<int, 3>, float>> &output, 
    vector<pair<array<int, 3>, float>> &input, 
    vector<pair<float, float>> &psf)
{
cout << "entering convolution" << endl;
output.clear();
output.resize(input.size(), make_pair(array<int, 3>{0, 0, 0}, 0.0f));
cout << "output size: " << output.size() << endl;

int width = static_cast<int>(sqrt(input.size()));
int height = width;
int psfSize = static_cast<int>(sqrt(psf.size())); 
int psfHalf = psfSize / 2;

cout << "Image dimensions: " << width << "x" << height << endl;
cout << "PSF size: " << psfSize << "x" << psfSize << endl;

for (int y = 0; y < height; y++) {
for (int x = 0; x < width; x++) {
array<float, 3> rgbSum = {0.0f, 0.0f, 0.0f};
float intensitySum = 0.0f;

// Apply the kernel
for (int ky = -psfHalf; ky <= psfHalf; ky++) {
   for (int kx = -psfHalf; kx <= psfHalf; kx++) {
       int pixelX = x + kx;
       int pixelY = y + ky;

       // Handle boundaries during calculations instead of afterwards
       pixelX = max(0, min(width - 1, pixelX));
       pixelY = max(0, min(height - 1, pixelY));
       
       int pixelIndex = pixelY * width + pixelX;
       int psfIndex = (ky + psfHalf) * psfSize + (kx + psfHalf);
       
       if (psfIndex >= psf.size()) {
           cout << "PSF index out of bounds: " << psfIndex << endl;
           continue;
       }
       
       float kernelValue = psf[psfIndex].first;
       
       rgbSum[0] += input[pixelIndex].first[0] * kernelValue;
       rgbSum[1] += input[pixelIndex].first[1] * kernelValue;
       rgbSum[2] += input[pixelIndex].first[2] * kernelValue;
       intensitySum += input[pixelIndex].second * kernelValue;
   }
}

// Store result
int outputIndex = y * width + x;
output[outputIndex].first[0] = static_cast<int>(round(rgbSum[0]));
output[outputIndex].first[1] = static_cast<int>(round(rgbSum[1]));
output[outputIndex].first[2] = static_cast<int>(round(rgbSum[2]));
output[outputIndex].second = intensitySum;
}
}

cout << "finished convolution" << endl;
}

// can use classic randomly determined impulse response for psf later....

