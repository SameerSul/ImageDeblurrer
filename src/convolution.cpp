#include "convolution.h"
// this is going to be block convolution now

// NEED TO CHANGE THIS SUCH THAT WE NOW MULTIPLY THE RGB FLOAT FACTOR SCALARLY TO THE INPUT RGB INT[] ARRAY

// need to change this algorithm such that it better adheres to the math behind gaussian blurring


// DONT NEED THIS ANYMORE, INCORRECT IMPLEMENTATION
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

    // Validate inputs
    if (input.empty() || psf.empty() || width <= 0 || height <= 0 || kernel_size <= 0) {
        cout << "Invalid input parameters" << endl;
        return;
    }

    // Check sizing
    if (output.size() != input.size()) {
        output.resize(input.size());
    }

    int kernel_radius = kernel_size / 2; 
    
    cout << "Processing " << input.size() << " pixels" << endl;
    cout << "Image dimensions: " << width << "x" << height << endl;
    cout << "Kernel size: " << kernel_size << ", radius: " << kernel_radius << endl;
    
    // Iterate through all pixels
    for (int i = 0; i < input.size(); i++) 
    {
        // Calculate x and y positions for the current pixel
        int y_pos = i / width;
        int x_pos = i % width;

        // Check boundaries of pixels
        if (y_pos >= height || x_pos >= width) {
            cout << "Warning: Pixel index " << i << " out of bounds (x=" << x_pos << ", y=" << y_pos << ")" << endl;
            continue;
        }

        float new_r = 0.0f;
        float new_g = 0.0f;
        float new_b = 0.0f;
        
        // // DEBUGGING (but also because it looks cool on terminal) - Print at every 1000 pixels
        if (i % 1000 == 0) {
            cout << "Processing pixel " << i << " at (" << x_pos << ", " << y_pos << ")" << endl;
        }

        // Apply Gaussian kernel
        for (int kernel_ypos = 0; kernel_ypos < kernel_size; kernel_ypos++) {
            for (int kernel_xpos = 0; kernel_xpos < kernel_size; kernel_xpos++) {
                // Calculate neighbor positions based on kernel size (centered around current pixel)
                int neighbour_xpos = x_pos + (kernel_xpos - kernel_radius);
                int neighbour_ypos = y_pos + (kernel_ypos - kernel_radius);

                neighbour_xpos = max(0, min(neighbour_xpos, width - 1));
                neighbour_ypos = max(0, min(neighbour_ypos, height - 1));

                // Convert 2D coordinates back to 1D indexing since we have 1D indexing for pixels
                int pixel_pos = neighbour_ypos * width + neighbour_xpos;

                // Bounds check for pixel_pos
                if (pixel_pos < 0 || pixel_pos >= input.size()) {
                    cout << "Warning: Computed pixel position " << pixel_pos << " out of bounds" << endl;
                    continue;
                }

                // Get PSF weight - direct indexing since we iterate 0 to kernel_size
                int psf_index = kernel_ypos * kernel_size + kernel_xpos;
                if (psf_index < 0 || psf_index >= psf.size()) {
                    cout << "Warning: PSF index " << psf_index << " out of bounds" << endl;
                    continue;
                }
                
                float weight = psf[psf_index].first;

                // Check for invalid weight values
                if (isnan(weight) || isinf(weight)) {
                    cout << "Warning: Invalid weight at PSF index " << psf_index << endl;
                    continue;
                }

                // Perform weighted sum for ourRGB values
                new_r += weight * input[pixel_pos].first[0];
                new_g += weight * input[pixel_pos].first[1];
                new_b += weight * input[pixel_pos].first[2];
            }
        }

        // Check for invalid accumulated values
        if (isnan(new_r) || isinf(new_r) || isnan(new_g) || isinf(new_g) || isnan(new_b) || isinf(new_b)) {
            cout << "Warning: Invalid color values at pixel " << i << endl;
            // Copy original values instead
            output[i].first[0] = input[i].first[0];
            output[i].first[1] = input[i].first[1];
            output[i].first[2] = input[i].first[2];
        } else {
            // Cast and assign to output accordingly
            output[i].first[0] = static_cast<int>(new_r);
            output[i].first[1] = static_cast<int>(new_g);
            output[i].first[2] = static_cast<int>(new_b);
        }

        output[i].second = input[i].second;
    }

    cout << "Output Assigned - Processed " << input.size() << " pixels" << endl;
}


void lucyRichardsonDeblurring(vector<pair<array<int, 3>, float>> &output, 
    vector<pair<array<int, 3>, float>> &input, 
    vector<pair<float, float>> &psf, int width, int height, int kernel_size) {
    
    cout << "Starting Lucy-Richardson deblurring..." << endl;
    cout << "Image dimensions: " << width << "x" << height << endl;
    cout << "Kernel size: " << kernel_size << "x" << kernel_size << endl;
    cout << "Input pixels: " << input.size() << endl;
    
    const int iterations = 40; // Number of Lucy-Richardson iterations
    const float epsilon = 1e-8f; // Small value to prevent division by zero
    
    // Ensure output has correct size
    output.resize(input.size());
    
    // Work with intensity values for deblurring, then scale RGB accordingly
    vector<vector<float>> image_intensity(height, vector<float>(width, 0.0f));
    vector<vector<float>> estimate_intensity(height, vector<float>(width, 0.0f));
    vector<vector<float>> blurred(height, vector<float>(width, 0.0f));
    vector<vector<float>> ratio(height, vector<float>(width, 0.0f));
    vector<vector<float>> correction(height, vector<float>(width, 0.0f));
    
    // Store original RGB values for final reconstruction
    vector<vector<array<int, 3>>> original_rgb(height, vector<array<int, 3>>(width, {0, 0, 0}));
    
    // Convert input to dense format using proper indexing
    cout << "Converting input to dense format..." << endl;
    for (int i = 0; i < input.size(); i++) {
        int y = i / width;
        int x = i % width;
        
        if (y < height && x < width) {
            // Store intensity for deblurring
            image_intensity[y][x] = input[i].second;
            estimate_intensity[y][x] = input[i].second; // Initial estimate
            
            // Store original RGB values
            original_rgb[y][x] = input[i].first;
        }
    }
    
    // Convert PSF to 2D kernel
    cout << "Building PSF kernel..." << endl;
    vector<vector<float>> kernel(kernel_size, vector<float>(kernel_size, 0.0f));
    int center = kernel_size / 2;
    
    // Convert linear PSF array to 2D kernel
    for (int y = 0; y < kernel_size; y++) {
        for (int x = 0; x < kernel_size; x++) {
            int psf_index = y * kernel_size + x;
            if (psf_index < psf.size()) {
                kernel[y][x] = psf[psf_index].first;
            }
        }
    }
    
    // Verify kernel normalization
    float kernel_sum = 0.0f;
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            kernel_sum += kernel[i][j];
        }
    }
    cout << "Kernel sum: " << kernel_sum << endl;
    
    // Create flipped kernel for correlation
    vector<vector<float>> flipped_kernel(kernel_size, vector<float>(kernel_size));
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            flipped_kernel[i][j] = kernel[kernel_size - 1 - i][kernel_size - 1 - j];
        }
    }
    
    // Lucy-Richardson iterations
    cout << "Starting " << iterations << " iterations..." << endl;
    for (int iter = 0; iter < iterations; iter++) {
        if (iter % 3 == 0) {
            cout << "  Iteration " << (iter + 1) << "/" << iterations << endl;
        }
        
        // Step 1: Convolve current estimate with PSF
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float sum = 0.0f;
                for (int ky = 0; ky < kernel_size; ky++) {
                    for (int kx = 0; kx < kernel_size; kx++) {
                        int py = y + ky - center;
                        int px = x + kx - center;
                        
                        // Handle boundaries with mirroring
                        if (py < 0) py = -py;
                        if (py >= height) py = 2 * height - py - 2;
                        if (px < 0) px = -px;
                        if (px >= width) px = 2 * width - px - 2;
                        
                        // Clamp to valid range (fallback)
                        py = max(0, min(height - 1, py));
                        px = max(0, min(width - 1, px));
                        
                        sum += estimate_intensity[py][px] * kernel[ky][kx];
                    }
                }
                blurred[y][x] = sum;
            }
        }
        
        // Step 2: Calculate ratio of observed to blurred
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (blurred[y][x] > epsilon) {
                    ratio[y][x] = image_intensity[y][x] / blurred[y][x];
                } else {
                    ratio[y][x] = 1.0f;
                }
            }
        }
        
        // Step 3: Correlate ratio with flipped PSF
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float sum = 0.0f;
                for (int ky = 0; ky < kernel_size; ky++) {
                    for (int kx = 0; kx < kernel_size; kx++) {
                        int py = y + ky - center;
                        int px = x + kx - center;
                        
                        // Handle boundaries with mirroring
                        if (py < 0) py = -py;
                        if (py >= height) py = 2 * height - py - 2;
                        if (px < 0) px = -px;
                        if (px >= width) px = 2 * width - px - 2;
                        
                        // Clamp to valid range (fallback)
                        py = max(0, min(height - 1, py));
                        px = max(0, min(width - 1, px));
                        
                        sum += ratio[py][px] * flipped_kernel[ky][kx];
                    }
                }
                correction[y][x] = sum;
            }
        }
        
        // Step 4: Update estimate
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                estimate_intensity[y][x] *= correction[y][x];
                // Prevent negative values
                if (estimate_intensity[y][x] < 0) {
                    estimate_intensity[y][x] = 0.0f;
                }
                // Prevent excessive brightness
                if (estimate_intensity[y][x] > 255.0f) {
                    estimate_intensity[y][x] = 255.0f;
                }
            }
        }
    }
    
    // Convert result back to your format
    cout << "Converting result back to output format..." << endl;
    for (int i = 0; i < input.size(); i++) {
        int y = i / width;
        int x = i % width;
        
        if (y < height && x < width) {
            float intensity_ratio = 1.0f;
            
            // Calculate intensity scaling ratio (avoid division by zero)
            if (input[i].second > epsilon) {
                intensity_ratio = estimate_intensity[y][x] / input[i].second;
                // Clamp the ratio to reasonable bounds
                intensity_ratio = max(0.1f, min(4.0f, intensity_ratio));
            }
            
            // Scale RGB values proportionally to intensity change
            output[i].first[0] = static_cast<int>(min(255.0f, max(0.0f, original_rgb[y][x][0] * intensity_ratio)));
            output[i].first[1] = static_cast<int>(min(255.0f, max(0.0f, original_rgb[y][x][1] * intensity_ratio)));
            output[i].first[2] = static_cast<int>(min(255.0f, max(0.0f, original_rgb[y][x][2] * intensity_ratio)));
            
            // Update intensity
            output[i].second = estimate_intensity[y][x];
        } else {
            // Fallback: copy original values
            output[i] = input[i];
        }
    }
    
    cout << "Lucy-Richardson deblurring completed!" << endl;
}
// DEBUGGING
// bool checkGaussianBlurSetup(
//     const vector<pair<array<int, 3>, float>> &input,
//     const vector<pair<array<int, 3>, float>> &output,
//     const vector<pair<float, float>> &psf,
//     int width, int height, int kernel_size)
// {
//     cout << "Checking gaussian blur setup:" << endl;
//     cout << "Input size: " << input.size() << ", Expected: " << width * height << endl;
//     cout << "Output size: " << output.size() << ", Expected: " << width * height << endl;
//     cout << "PSF size: " << psf.size() << ", Expected: " << kernel_size * kernel_size << endl;
    
//     bool valid = true;
    
//     if (input.size() != width * height) {
//         cout << "Error: Input buffer size doesn't match dimensions" << endl;
//         valid = false;
//     }
    
//     if (output.size() != width * height) {
//         cout << "Error: Output buffer size doesn't match dimensions" << endl;
//         valid = false;
//     }
    
//     if (psf.size() != kernel_size * kernel_size) {
//         cout << "Error: PSF size doesn't match kernel dimensions" << endl;
//         valid = false;
//     }
    
//     // Check if PSF weights sum approximately to 1.0 (for normalized Gaussian)
//     float sum = 0.0f;
//     for (const auto &p : psf) {
//         sum += p.first;
//     }
//     cout << "PSF weight sum: " << sum << " (should be close to 1.0)" << endl;
    
//     if (abs(sum - 1.0f) > 0.01f) {
//         cout << "Warning: PSF weights don't sum to 1.0, blur may be too dark/bright" << endl;
//     }
    
//     return valid;
// }


