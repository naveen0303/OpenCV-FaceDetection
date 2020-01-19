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

//Function to Detect Face and Draw a Rectangle on it
void DetectAndDraw(Mat& img, CascadeClassifier& cascade, double scale,int i)
{
   
    cout << "please wait!!!" << endl;
    vector<Rect> faces;
    Mat grayimg;
    cvtColor(img, grayimg, COLOR_BGR2GRAY);
    cascade.detectMultiScale(grayimg, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    size_t n = faces.size();
    for (size_t j = 0; j < n; j++)
    {
        Rect r = faces[j];
        rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)), cvPoint(cvRound((r.x +r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);
    }

    //For many output images this is the naming seciton
    char name[100] = "tempimg";
    char index[100] = "0";  
    char name2[5] = ".jpg";
    _itoa_s(i, index, 100, 10);  //for every new image i increments by 1 and gets appended to the string
    strcat_s(name,100,index);
    strcat_s(name,100,name2);   //example: tempimg0.jpg   tempimg1.jpg etc..
    //puts(name);
    //write the output image
    imwrite(name, img);
    //namedWindow("display_image", WINDOW_AUTOSIZE);
    //imshow("display_image", img);
}

int main(int argc, char** argv)
{
    if(argc !=2)
     {
        cout << "Error!!! This program needs only 1 argument i.e, ImageName" << endl;
        exit(1);
     } 
    char *imgName = argv[1];
   
   CascadeClassifier cascade;
   double scale = 1;
   
    int i = 0;
    char c = 'p';

    while (c != 'q') //Check for input option (initial input is p) when input is q program exits.
    {
        Mat image;
        //used in-built function to detect faces in image
        cascade.load("haarcascade_frontalface_alt.xml");
        //printf("%s", imgName);
        label2:image = imread(imgName, IMREAD_UNCHANGED);
        //image = imread(argv[1], IMREAD_UNCHANGED);
        //image = imread("testimg.jpg", IMREAD_UNCHANGED);
        DetectAndDraw(image, cascade, scale,i);       
        
        //check for option after completion of 1 image
        label1:
        cout << "Enter option:" << endl;
        cout << "a) q: quit" << endl;
        cout << "b) p: path to file" << endl;
        cin >> c;
        
        //if option doesn't match the requirements go back
        switch (c) {
        case 'q': break;
        case 'p': i++; cin >> imgName; break;
        default: cout << "Error!!! enter correct option" << endl; goto label1;
        }
    }
    return 0;
} 
