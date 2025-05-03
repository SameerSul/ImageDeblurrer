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
    vector<pair<array<int, 3>, float>> input; // Use std::array<int, 3> instead of int[] because c++ loves to complain
    vector<pair<array<int, 3>, float>> output; // Use std::array<int, 3> instead of int[]
    vector<pair<float, float>> psf;
    pair<int, int> dimensions; 

    // check what kind of file it is
    string fileType;
    cout << "Sameer's Image Deblurrer" << endl;
    cout << "Please enter the type of file you wish to deblur (i.e .ppm, .jpg, .png ...): ";
    cin >> fileType;

    if (fileType == ".ppm" || fileType == "ppm")
    {
        // read image and turn into text file
        ifstream image("testImage.ppm", ios::in | ios::binary);
        if (!image.is_open()) {
            cerr << "Error: Could not open the file 'testImage.ppm'. Please check if the file exists and the path is correct." << endl;
            return 1;
        }

        ofstream textOutput("testingImage.txt", ios::out | ios::app);
        if (!textOutput.is_open()) {
            cerr << "Error: Could not open the output file 'testingImage.txt'." << endl;
            return 1;
        }

        // Skip the first line
        string firstLine;
        getline(image, firstLine);
        // if (firstLine != "P6" && firstLine != "P3") {
        //     cerr << "Error: Unsupported ppm file format. Expected P6 or P3 format for .ppm files." << endl;
        //     return 1;
        // }

        // Read dimensions from the second line
        int width, height;
        image >> width >> height;
        dimensions = {width, height};
        cout << "Image dimensions: " << width << "x" << height << endl;

        // Skip the third line (max color value)
        string maxColorValue;
        getline(image, maxColorValue); // Consume the remaining newline
        getline(image, maxColorValue);

        // Process character by character
        unsigned char byte;
        while (image.read(reinterpret_cast<char*>(&byte), 1)) {
            textOutput << dec << static_cast<int>(byte) << " "; // Ensure decimal output
        }

        cout << "Converted image to text representation" << endl;

        image.close();
        textOutput.close();

        // turn image into array and calculate intensity
        createPixels(input, width, height);
        // for (const auto& pair : input) {
        //     std::cout << "(" << pair.first[0] << ", " << pair.first[1] << ", " << pair.first[2] << ", " << pair.second << ") ";
        // }
        cout << "created vector pair representation" << endl;
        // std::cout << std::endl;
        // // cout << input.size() << endl;
        // // // create psf
        // cout << "entering PSF" << endl;
        createPSF(psf, 3);
        cout << "created psf" << endl;
        for (const auto& pair : psf) {
            std::cout << "(" << pair.first << ") ";
        }

        // convolve psf with image
        Convolution(output, input, psf);
        cout << "left convolution" << endl;
        // // return output
        vectorToPPM(output, "finalImage.txt", dimensions.first, dimensions.second);

        cout << "left vectortoppm, we done" << endl;


    }

    else 
    {
        cout << "That file type is invalid or not supported yet" << endl;
    }


    return 0;
}