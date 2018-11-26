/*
 * File: videotracker.cpp
 * Project: LIFFT - CS3307 Assignment Stage #3
 * Date: November 9th 2018
 * Group Members: Taebum Kim, Marisa Mathura, Christopher Tam, Justin Wang, Samuel Wong *
 *
*/

#include "videotracker.h"
using namespace cv;
using namespace std;


/// LINE TO EDIT TO ABSOLUTE PATH OF THE VIDEO FILE BEING TRACKED
string video_file = "/media/sf_VMShare/deadlift/badform.MOV";

Point2f point;                                                          /**< point2f structure variable for storing a point */
bool point_clicked = false;                                             /**< a boolean to deal with whether a new point has been clicked by user */
TermCriteria criteria(TermCriteria::COUNT|TermCriteria::EPS,20,0.03);   /**< termination criteria information for iterative functions used in main() */
Size window_size(30,30);                                                /**< size of window */
const int MAX_COUNT = 500;                                              /**< maximum number of array items (frame images) allowed in vector */


/*! \brief mouse_click() is a function used by main() to determine where the user has clicked
 *
 *
 *  mouse_click() modifies a point with the new coordinates of x,y, that a user has clicked on with the left button click
 *  It also sets point_clicked as true to signal that a new point has been clicked by the user
 *
 */

static void mouse_click( int event, int x, int y, int , void* )
{
    if( event == EVENT_LBUTTONDOWN )                                    /**< if left button click */
    {
        point = Point2f((float)x, (float)y);                            /**< then update point coordinates */
        point_clicked = true;                                           /**< and set clicked status as true */
    }
}


/*! \brief main() function plays the video file in a new window and allows the user to click on the video and track the object clicked on for the remainder of the video
 *
 *
 * main() opens a window and takes each frame of the input video (given by an absolute path). It shows each of the frames in order and allows the user to click on the video to place a green sticker.
 * The green sticker will follow the object the user has clicked on.
 * main() tracks objects by taking each individual frame image, turning it into greyscale, accepting a point (determining the coordinates on the frame) from mouse_click() and using lucas-kanade optical flow algorithms to determine the next position/point of the object in subsequent frames.
 * The user can place multiple stickers.
 */

int main()
{
    VideoCapture video(video_file);                                             /**< open the video file */
    
    namedWindow( "LIFFT", 1 );                                                  /**< make a window called LIFFT with autosize */
    setMouseCallback( "LIFFT", mouse_click, 0 );                                /**< mouse_click handler */
    Mat current_grey_image, previous_grey_image, current_colour_image, current_colour_screenshot;       /**< create Mat objects to hold the frames/images */
    vector<Point2f> point_array[2];                                             /**< create an array of two vectors to hold the points */

    while(1){                                                                   /**< loop until broken */

        if (!video.read(current_colour_screenshot))                             /**< if no frames, then break loop */
            break;

        current_colour_screenshot.copyTo(current_colour_image);                 /**< make the current frame an image */
        cvtColor(current_colour_image, current_grey_image, COLOR_BGR2GRAY);     /**< convert the image to greyscale */

        if( !point_array[0].empty() ){                                          /**< as long as there are images in the first vector */
            vector<uchar> status;
            vector<float> error;
            if(previous_grey_image.empty())                                     /**< if there is not previous grey image then make the previous one the same as the current grey image */
                current_grey_image.copyTo(previous_grey_image);
            calcOpticalFlowPyrLK(previous_grey_image, current_grey_image, point_array[0], point_array[1], status, error, window_size, 3, criteria, 0, 0.001);           /**< lucas-kanade algorithm for determining the current and next positions and place them into the vector arrays */
            
            size_t i, j;

            for( i = j = 0; i < point_array[1].size(); i++ ){                   /**< for loop to iterate through all of the input vector of next points */
                if( !status[i] )
                    continue;
                point_array[1][j++] = point_array[1][i];                        /**< update the points */
                circle( current_colour_image, point_array[1][i], 3, Scalar(0,255,0), -1, 8);    /**< draw a circle on the current image */
            }
            point_array[1].resize(j);                                           /**< resize vector */
        }

        if( point_clicked && point_array[1].size() < (size_t)MAX_COUNT )        /**< if left button clicked and not too many next points */
        {
            vector<Point2f> holder;
            holder.push_back(point);
            cornerSubPix( current_grey_image, holder, window_size, Size(-1,-1), criteria);
            point_array[1].push_back(holder[0]);
            point_clicked = false;                                              /**< reset click to false */
        }

        imshow("LIFFT", current_colour_image);                                      /**< show the current colour frame image (not grayscale) - the while loop will be fast enough to blend the individual frames into a video */
        char c = (char)waitKey(10);                                                 /**< gives highgui time to process draw requests from imshow */
        swap(point_array[1], point_array[0]);                                       /**< swaps the arrays */
        current_grey_image.copyTo(previous_grey_image);                             /**< move current image to be the previous image */
    }
    return 0;
}