#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

// Includes for mouse function
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using namespace Colors;

// Read video
string videoPath = "videos/run.mp4";
VideoCapture video(videoPath);

// Exit if video is not opened
if(!video.isOpened()) {
    cout << "Could not read video file" << endl;
    return -1;
}

Color array = new old_gray[];

// Mouse function segment
Point p;
nameWindow("window");
setMouseCallBack("window", mouseCallBack, (void*)(&p));

// Retrieve x, y coordinates of left-click
void mouseCallBack(int event, int x, int y, int flags, void* userdata)
{
     if ( event == EVENT_LBUTTONDOWN ) {
          Point *p = (Point*) ptr;
          p->x = x;
          p->y = y;
     }
}

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
Size winSize = (15,15),
int maxLevel = 2,
TermCriteria criteria = (cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.05)

// Assign tracking points colour of red
Color c = Color().Red;

// Get first frame of video and find corners in it
bool ret, old_frame = video.read;
old_gray = cvtColor(frame, edges, COLOR_BGR2GRAY);
