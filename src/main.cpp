// include wtv libraries need to be included
#include "convolution.h"
// steps of what needs to be done

// read image + take note of the PSF

// convolute to create blurred image
// go through all pixels

// simulate blur + noise

// restore blur and noisy image 


// begin restoration

int main()
{
    vector<pair<int, float>> output; 
    vector<pair<int, float>> input;
    vector<pair<int,float>> psf; 

    // read image and turn into binary, and then process into bytes
    ifstream image("testImage.jpg", ios::in, ios::binary);
    ofstream binary("binaryTestImage.txt", ios::out | ios::app);

    // process character by character

    char ch;

    while (!image.eof())
    {
        ch = image.get();
        binary.put(ch);
    }

    cout << "Converted image to bitstream" << endl;
    image.close();
    binary.close();

    // Convert Back to Image

    // ifstream binary("binaryTestImage.txt", ios::in | ios::app || ios::binary);
    // ofstream image("testImageOutput.jpg", ios::out | ios::app);

    // char ch2;

    // while (!binary.eof())
    // {
    //     ch2 = binary.get();
    //     image.put(ch2);
    // }

    // cout << "Converted bitstream to image" << endl;
    // image.close();
    // binary.close();

    // Now we need to create our vector pairs array with the intensity and the rgb image data

    // lets first process it in 24 bit chunks


}