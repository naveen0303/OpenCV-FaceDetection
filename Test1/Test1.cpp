//Author : Naveen Chalawadi
//Assumption: Assumed that all the input image files are in the same directory

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <imgproc/imgproc_c.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;

CascadeClassifier cascade;
double scale = 1;

//Function to Detect Face and Draw a Rectangle on it
void DetectAndDraw(Mat& img, CascadeClassifier& cascade, double scale,int i)
{
   
    cout << "please wait!!!" << endl;
    vector<Rect> faces;
    Mat grayimg;
    cvtColor(img, grayimg, COLOR_BGR2GRAY);
    cascade.detectMultiScale(grayimg, faces, 1.1, 1, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    int n = faces.size();
    for (size_t i = 0; i < n; i++)
    {
        Rect r = faces[i];
        rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)), cvPoint(cvRound((r.x +r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);
    }

    //For many output images this is the naming seciton
    char name[100] = "tempimg";
    char index[100] = "0";  
        
    _itoa_s(i, index, 100, 10);  //for every new image i increments by 1 and gets appended to the string
    strcat_s(name,50,index);
    strcat_s(name,50,".jpg");   //example: tempimg0.jpg   tempimg1.jpg etc..

    //write the output image
    imwrite(name, img);
    //namedWindow("display_image", WINDOW_AUTOSIZE);
    //imshow("display_image", img);
}

int main(int argc, char** argv)
{
    char *imgName = argv[1];
    
    int i = 0;
    char c = 'p';

    while (c != 'q') //Check for input option (initial input is p) when input is q program exits.
    {
        Mat image;
        //used in-built function to detect faces in image
        cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalcatface.xml");
        //printf("%s", imgName);
        label2:image = imread(imgName, IMREAD_UNCHANGED);
        //image = imread(argv[1], IMREAD_UNCHANGED);
        //image = imread("testimg.jpg", IMREAD_UNCHANGED);
        DetectAndDraw(image, cascade, scale,i);       
        
        //check for option after completion of 1 image
        label1:cout << "Enter option:" << endl;
        cout << "a) q: quit" << endl;
        cout << "b) p: path to file" << endl;
        cin >> c;
        
        //if option doesn't match the requirements go back
        if (c != 'p' && c != 'q') {
            cout << "Error enter correct option!!!" << endl;
            goto label1;
        }
        
        //for next image take the input image filename
        if (c == 'p')
        {
            i++;
            cin >> imgName;
            goto label2;
        }
    }
    return 0;
} 
