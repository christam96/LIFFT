#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

// lkdemo
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

// Includes for mouse call back function
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using namespace Colors;

// GLOBAL VARIABLES
Point2f point;
bool pointClicked = false;

int main (int argc) {

    // Read video
    string videoPath = "videos/run.mp4";
    VideoCapture video;
    video.open(videoPath);  // Opens video
    TermCriteria criteria(TermCriteria::COUNT|TermCriteria::EPS,10,0.03);
    Size windowSize(50,50);
    namedWindow("Lifting Video", 1) // Flag 1 autosized lifting video window
    setMouseCallBack("Lifing Video", onMouseClick);

    Mat colourScreenshot, currentColourImage, currentGreyImage, previousGreyImage;
    vector<Point2f> pointArray[2];

    while(1) {
      video >> colourScreenshot;
      if (colourScreenshot.empty()) {
        break;
      }
      colourScreenshot.copyTo(currentColourImage);
      cvtColor(currentColourImage, currentGreyImage, COLOR_BGR2GRAY);
      if (pointClicked == true) {
        vector<uchar> status;
        vector<float> error;
        if (previousGreyImage.empty()) {
          currentGreyImage.copyTo(previousGreyImage);
          // circle(colourScreenshot, pointArray[1])
        }
        calcOpticalFlowPyrLK(previousGreyImage, currentGreyImage, pointArray[0], pointArray[1], status, error, windowSize, 0, criteria, 0, 0.001);

        for (size_t i = j = 0; i < points[1].size(); i++) {
          if (pointClicked == true) {
            points[1][j++] = points[1][i];
            circle(currentColourImage, points[1][i], 3, Scalar(255,255,0), -1, 8);
        }

        points[1].resize(j);

      }
      imshow("Lifting Video", currentColourImage);

      swap(pointArray[0],pointArray[1]);
      currentGreyImage.copyTo(previousGreyImage);
    }



/**
    // Exit if video is not opened
    if(!video.isOpened()) {
        cout << "Could not read video file" << endl;
        return -1;
    }
**/
/**
    Color array = new old_gray[]; // Was originally going to be used to hold frames, do not need anymore???

    // Mouse function segment - Retrieved from: https://stackoverflow.com/questions/15570431/opencv-return-value-from-mouse-callback-function
    Point p;
    nameWindow("window");
    setMouseCallBack("window", mouseCallBack, (void*)(&p));
**/


    /**

    DO NOT NEED ANYMORE:

    // Parameters for goodFeaturesToTrack() function, which initializes a point-based tracker of an object
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;

    **/


    // Parameters for calcOpticalFlowPyrLK() function, which uses the Lucas Kanade method to track objects
/**    Size winSize = (15,15),
    int maxLevel = 2,
    TermCriteria criteria = (cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.05)

    // Assign tracking points colour of red
    Color c = Color().Red;

    // Get first frame of video and find corners in it
    bool ret, old_frame = video.read;
    old_gray = cvtColor(frame, edges, COLOR_BGR2GRAY);
}
**/

// Function to retrieve x, y coordinates of left-click
void onMouseClick(int event, int x, int y, int flags, void* userdata)
{
     if ( event == EVENT_LBUTTONDOWN ) {
          point = Point2f((float)x, (float)y);
          pointClicked = true;
     }
}
