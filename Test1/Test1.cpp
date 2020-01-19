//Author : Naveen Chalawadi
//Assumption: Assumed that all the input image files are in the same directory

/* Question 1 - Serial Implementation of Face Detection Algorithm using OpenCV
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
    for (size_t i = 0; i < n; i++)
    {
        Rect r = faces[i];
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

    //used in-built function to detect faces in image
    cascade.load("haarcascade_frontalface_alt.xml");
    
    Mat image;

    while (c != 'q') //Check for input option (initial input is p) when input is q program exits.
    {
        //printf("%s", imgName);
        image = imread(imgName, IMREAD_UNCHANGED);
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
*/

/* Question 2 - Parallel Implementation of Face Detection Algorithm
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <imgproc/imgproc_c.h>
#include <iostream>
#include <cstring>
#include <omp.h>
#include <time.h>

using namespace std;
using namespace cv;

//Function to Detect Face and Draw a Rectangle on it
void DetectAndDraw(Mat& img, CascadeClassifier& cascade, double scale, int i)
{

    cout << "please wait!!!" << endl;
    vector<Rect> faces;
    Mat grayimg;
    cvtColor(img, grayimg, COLOR_BGR2GRAY);
    cascade.detectMultiScale(grayimg, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    //size_t n = faces.size();
    int n = faces.size();

#pragma omp parallel for
    //for (size_t j = 0; j < n; j++)
    for (int j = 0; j < n; j++)
    {
        Rect r = faces[j];
        rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)), cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);
    }

    //For many output images this is the naming seciton
    char name[100] = "tempimg";
    char index[100] = "0";
    char name2[5] = ".jpg";
    _itoa_s(i, index, 100, 10);  //for every new image i increments by 1 and gets appended to the string
    strcat_s(name, 100, index);
    strcat_s(name, 100, name2);   //example: tempimg0.jpg   tempimg1.jpg etc..
    //puts(name);
    //write the output image
    imwrite(name, img);
    //namedWindow("display_image", WINDOW_AUTOSIZE);
    //imshow("display_image", img);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Error!!! This program needs only 1 argument i.e, ImageName" << endl;
        exit(1);
    }

    char* imgName = argv[1];

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
        image = imread(imgName, IMREAD_UNCHANGED);
        //image = imread(argv[1], IMREAD_UNCHANGED);
        //image = imread("testimg.jpg", IMREAD_UNCHANGED);
        DetectAndDraw(image, cascade, scale, i);

        //check for option after completion of 1 image
    label1:cout << "Enter option:" << endl;
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
*/

/* Question 3 - Parallel Processing using t threads
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <imgproc/imgproc_c.h>
#include <iostream>
#include <cstring>
#include <omp.h>

using namespace std;
using namespace cv;

//Function to Detect Face and Draw a Rectangle on it
void DetectAndDraw(Mat& img, CascadeClassifier& cascade, double scale,int i,int t)
{

    cout << "please wait!!!" << endl;
    vector<Rect> faces;
    Mat grayimg;
    cvtColor(img, grayimg, COLOR_BGR2GRAY);
    cascade.detectMultiScale(grayimg, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    //size_t n = faces.size();
    int n = faces.size();

    #pragma omp parallel for num_threads(t)
    //for (size_t j = 0; j < n; j++)
    for(int j = 0; j < n; j++)
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

    int n=omp_get_max_threads();
    
    int i = 0,t=1;
    char c = 'p';

    while (c != 'q') //Check for input option (initial input is p) when input is q program exits.
    {
        Mat image;
        //Displaying Max number of threads avaialble
        cout << "Maximum number of threads available is " << n << endl;
                
        //Selecting how many threads you want use
        label3:
        cout << "Enter number of threads to use (min=1 max=" << n << "):" << endl;
        cin >> t;
        if (t < 1 || t > n) {
            cout << "Error!!! thread value is out of bounds" << endl;
            goto label3;
        }
        omp_set_num_threads(t);
        
        //used in-built function to detect faces in image
        cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml");
        //printf("%s", imgName);
        image = imread(imgName, IMREAD_UNCHANGED);
        //image = imread(argv[1], IMREAD_UNCHANGED);
        //image = imread("testimg.jpg", IMREAD_UNCHANGED);
        DetectAndDraw(image, cascade, scale,i,t);

        //check for option after completion of 1 image
        label1:
        cout << "Enter option:" << endl;
        cout << "a) q: quit" << endl;
        cout << "b) p: path to file" << endl;
        cin >> c;

        switch (c) {
        case 'q': break;
        case 'p': i++; cin >> imgName; break;
        default: cout << "Error!!! enter correct option" << endl; goto label1;
        }        
    }
    return 0;
}
*/
