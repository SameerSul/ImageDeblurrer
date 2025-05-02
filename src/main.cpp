// include wtv libraries need to be included
#include "convolution.h"
// steps of what needs to be done

// read image + take note of the PSF

// convolute to create blurred image
// go through all pixels

// simulate blur + noise

// restore blur and noisy image 


// begin restoration

#include "convolution.h"

using namespace std;

int main()
{
    vector<pair<int, float>> output; 
    vector<pair<int, float>> input;
    vector<pair<int, float>> psf; 

    // check what kind of file it is
    string fileType;
    cout << "Sameer's Image Deblurrer" << endl;
    cout << "Please enter the type of file you wish to deblur (i.e .ppm, .jpg, .png ...): ";
    cin >> fileType;

    if (fileType == ".ppm" || fileType == "ppm")
    {
        // read image and turn into text file
        ifstream image("testImage.ppm", ios::in | ios::binary);
        ofstream textOutput("testImage.txt", ios::out | ios::app);

        // Skip the first three lines (header of the .ppm file)
        string headerLine;
        for (int i = 0; i < 3; ++i) {
            getline(image, headerLine);
        }

        // Process character by character
        unsigned char byte;
        while (image.read(reinterpret_cast<char*>(&byte), 1)) {
            textOutput << dec << static_cast<int>(byte) << " "; // Ensure decimal output
        }

        cout << "Converted image to text representation" << endl;

        image.close();
        textOutput.close();
    }

    else 
    {
        cout << "That file type is invalid or not supported yet" << endl;
    }

    return 0;
}