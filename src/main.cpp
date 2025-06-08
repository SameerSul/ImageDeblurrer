// include wtv libraries need to be included
#include "convolution.h"
#include "imageComponents.h"
#include "convolution.h"


// steps of what needs to be done

// read image + take note of the PSF -> done

// convolute to create blurred image -> should be done
// go through all pixels

// simulate blur + noise

// restore blur and noisy image 


// begin restoration


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
    vector<pair<array<int, 3>, float>> input;
    vector<pair<array<int, 3>, float>> blurredOutput;
    vector<pair<array<int, 3>, float>> unblurredOutput;

    vector<pair<float, float>> psf;

    int kernel_size = 20;
    pair<int, int> dimensions; 

    // Check what kind of file it is
    string fileType;
    cout << "Sameer's Image Deblurrer" << endl;
    cout << "Please enter the type of file you wish to deblur (i.e .ppm, .jpg, .png ...): ";
    cin >> fileType;

    if (fileType == ".ppm" || fileType == "ppm")
    {
        // Read image and turn into text file
        ifstream image("testImage.ppm", ios::in | ios::binary);
        if (!image.is_open()) {
            cerr << "Error: Could not open the file 'testImage.ppm'. Please check if the file exists and the path is correct." << endl;
            return 1;
        }

        ofstream textOutput("testingImage.txt", ios::out);  // Not appending to avoid duplicate data
        if (!textOutput.is_open()) {
            cerr << "Error: Could not open the output file 'testingImage.txt'." << endl;
            return 1;
        }

        // Skip the first line
        string firstLine;
        getline(image, firstLine);
        cout << "PPM format: " << firstLine << endl;

        // Read dimensions from the second line
        int width, height;
        image >> width >> height;
        dimensions = {width, height};
        cout << "Image dimensions: " << width << "x" << height << endl;

        // Skip the third line (max color value)
        int maxVal;
        image >> maxVal;
        cout << "Maximum color value: " << maxVal << endl;

        // Consume the newline character after maxVal
        image.get();

        // // Process character by character for binary PPM (P6)
        // if (firstLine == "P6") {
        //     unsigned char byte;
        //     while (image.read(reinterpret_cast<char*>(&byte), 1)) {
        //         textOutput << static_cast<int>(byte) << " ";
        //     }
        // }
        // Process ASCII PPM (P3)
        // else if (firstLine == "P3") {
            int value;
            while (image >> value) {
                textOutput << value << " ";
            }
        // }
        // else {
        //     cerr << "Unsupported PPM format: " << firstLine << endl;
        //     return 1;
        // }

        cout << "Converted image to text representation" << endl;

        image.close();
        textOutput.close();

        // Turn image into array and calculate intensity
        createPixels(input, width, height);
        cout << "Created vector pair representation with " << input.size() << " pixels" << endl;
        
        // For Debugging sake
        // cout << "First 5 pixels:" << endl;
        // for (int i = 0; i < min(5, (int)input.size()); i++) {
        //     cout << "Pixel " << i << ": RGB(" 
        //          << input[i].first[0] << ", " 
        //          << input[i].first[1] << ", " 
        //          << input[i].first[2] << "), Intensity: " 
        //          << input[i].second << endl;
        // }
        

        createPSF(psf,kernel_size);
        // printKernel(psf);

        cout << "Convolution started" << endl;
        // Convolve psf with image
        // Convolution(output, input, psf);
        gaussianBlurring(blurredOutput, input, psf, width, height, kernel_size);
        cout << "Blurring Convolution completed" << endl;

        // DEBUGGING - Double checking to ensure gaussian blurring was being done right and not in word boxes
        // checkGaussianBlurSetup(input, output, psf, width, height, kernel_size);
        // cout << "First 5 output pixels:" << endl;
        // for (int i = 0; i < min(5, (int)output.size()); i++) {
        //     cout << "Pixel " << i << ": RGB(" 
        //          << output[i].first[0] << ", " 
        //          << output[i].first[1] << ", " 
        //          << output[i].first[2] << "), Intensity: " 
        //          << output[i].second << endl;
        // }

        // Convert back to PPM
        vectorToPPM(blurredOutput, "blurredOutput.ppm", dimensions.first, dimensions.second);

        cout << "Blurred Image processing completed successfully" << endl;

        lucyRichardsonDeblurring(unblurredOutput, blurredOutput, psf, width, height, kernel_size);
        cout << "Deblurring Convolution completed" << endl;

        vectorToPPM(unblurredOutput, "unblurredOutput.ppm", dimensions.first, dimensions.second);






    }
    else 
    {
        cout << "That file type is invalid or not supported yet" << endl;
    }

    return 0;
}