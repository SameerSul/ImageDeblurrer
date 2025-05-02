// include wtv libraries need to be included
#include "convolution.h"
#include "imageComponents.h"

// steps of what needs to be done

// read image + take note of the PSF -> done

// convolute to create blurred image -> should be done
// go through all pixels

// simulate blur + noise

// restore blur and noisy image 


// begin restoration

#include "convolution.h"

using namespace std;

int main()
{
    vector<pair<int, float>> output; 
    vector<pair<int[], float>> input;
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
        for (const auto& pair : input) {
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        std::cout << std::endl;
        // cout << input.size() << endl;
        // // create psf
        cout << "entering PSF" << endl;
        createPSF(psf, 3); 

        // // convolve psf with image
        // Convolution(output, input, psf);

        // // return output
        // vectorToPPM(output, "testImage.txt", dimensions.first, dimensions.second);


    }

    else 
    {
        cout << "That file type is invalid or not supported yet" << endl;
    }


    return 0;
}