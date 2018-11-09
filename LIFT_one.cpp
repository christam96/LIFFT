#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

using namespace cv;
using namespace std;
using namespace Colors;

// Read video
string videoPath = "videos/run.mp4";
VideoCapture video(videoPath);

// Exit if video is not opened
if(!video.isOpened()) {
    cout << "Could not read video file" << endl;
    return 1;
}

// Parameters for goodFeaturesToTrack() function, which initializes a point-based tracker of an object
vector<Point2f> corners;
double qualityLevel = 0.01;
double minDistance = 10;
int blockSize = 3;
bool useHarrisDetector = false;
double k = 0.04;

// Parameters for calcOpticalFlowPyrLK() function, which uses the Lucas Kanade method to track objects
Size winSize = (15,15),
int maxLevel = 2,
TermCriteria criteria = (cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.05)

// Assign tracking points random colour
Color c = Color().Red;

// Get first frame of video
bool ret, old_frame = video.read;
