// ObjectTrackingCPP.cpp
#include <cstdio>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>//needed by BackgroungSub
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
//#include <conio.h>           // it may be necessary to change or remove this line if not using Windows
#include <iomanip>
#include "time.h"
#include <fstream>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define SHOW_STEPS            // un-comment or comment this line to show steps or not

// global variables ///////////////////////////////////////////////////////////////////////////////


CvCapture *capture = cvCaptureFromAVI("ship.mp4");

int frame = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

Ptr<BackgroundSubtractorKNN> pBackgroundKnn = createBackgroundSubtractorKNN(300, 300, 1);
bool update_bg_model = true;

int frame_number = 1;

Mat structuringElement3x3 = getStructuringElement(MORPH_RECT, Size(3, 3));
Mat structuringElement5x5 = getStructuringElement(MORPH_RECT, Size(5, 5));
Mat structuringElement7x7 = getStructuringElement(MORPH_RECT, Size(7, 7));
Mat structuringElement9x9 = getStructuringElement(MORPH_RECT, Size(9, 9));
Mat structuringElement11x11 = getStructuringElement(MORPH_RECT, Size(11, 11));
Mat structuringElement15x15 = getStructuringElement(MORPH_RECT, Size(15, 15));
Mat structuringElement21x21 = getStructuringElement(MORPH_RECT, Size(21, 21));
Mat structuringElement25x25 = getStructuringElement(MORPH_RECT, Size(25, 25));

const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_PINK = cv::Scalar(255.0, 192.0, 203.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0);
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	fstream file;
	file.open("frameFPS.txt", ios::app);
	//double start, end;
	VideoCapture capVideo;
	Mat Frame;
	Mat FrameGray;
	
	capVideo.open("ship.mp4");
	//double fps = capVideo.get(CV_CAP_PROP_FPS);
	//¨Ò¥~³B²z/////////////////////////////////////////////////////////////////////////////////////////////////
	if (!capVideo.isOpened()) {                                                 // if unable to open video file
		cout << "error reading video file" << endl;      // show error message
		//_getch();                    // it may be necessary to change or remove this line if not using Windows
		return(0);                                                              // and exit program
	}

	if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
		cout << "error: video file must have at least two frames";
		//_getch();
		return(0);
	}

	capVideo.read(Frame);

	char chCheckForEscKey = 0;	
    
	Size videoSize = Size((int)capVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)capVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

    VideoWriter writer("Final.avi", CV_FOURCC('M', 'J', 'P', 'G'), 15, videoSize);	

		while (capVideo.isOpened() && chCheckForEscKey != 27) {
			frame_number = frame_number+1;
			string str = std::to_string(frame_number);

            Mat src_gray;
            Mat grad;
            Mat edge;
            Mat new_grad;
            Mat grad_rgb;
            int scale = 1;
            int delta = 0;
            int ddepth = CV_16S;

            int c;        
            //GaussianBlur first
            GaussianBlur( Frame, Frame, Size(3,3), 0, 0, BORDER_DEFAULT );

            //Convert to Grayscale
            cvtColor( Frame, src_gray, CV_BGR2GRAY );            

            /// Generate grad_x and grad_y
            Mat grad_x, grad_y;
            Mat abs_grad_x, abs_grad_y;

            /// Gradient X
            //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
            Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
            convertScaleAbs( grad_x, abs_grad_x );

            /// Gradient Y
            //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
            Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
            convertScaleAbs( grad_y, abs_grad_y );
            /// Total Gradient (approximate)
            addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );   
            imshow("After Sobel",grad);
          
            medianBlur(grad, grad,13);
            imshow("1_After medianblur",grad);           

            dilate(grad, grad, structuringElement3x3);
            erode (grad, grad, structuringElement7x7);           
            imshow("After Closing",grad);
       
          
            threshold(grad, grad, 40, 255, THRESH_BINARY);    
            imshow("After threshold",grad);

            //Laplacian(grad, grad, CV_8U, 3, 1, 0, BORDER_DEFAULT );
            // imshow("After Laplacian",grad);
            // dilate(grad, grad, structuringElement3x3);
            // medianBlur(grad, grad,3);
            //imshow("2_After medianblur",grad);

            // GaussianBlur( grad, grad, Size(3,3), 0, 0, BORDER_DEFAULT );
            
            medianBlur(grad, grad,3);
            // erode(grad, grad, structuringElement3x3);
            dilate(grad, grad, structuringElement9x9);
           
            // cv::medianBlur(grad, grad,3);
            // cv::medianBlur(grad, grad,3);
            // imshow("2_After medianblur",grad);

            //erode(grad, grad, structuringElement3x3);
            //dilate(grad, grad, structuringElement9x9);

            // medianBlur(grad, grad, 5);
            // imshow("After medianblur",grad);
            imshow("After Opening",grad);
                        
            std::vector<std::vector<cv::Point> > contours;	    
            std::vector<Vec4i> hierarchy;           

            findContours(grad, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);            

            std::vector<std::vector<cv::Point> > convexHulls(contours.size());

		    for (unsigned int i = 0; i < contours.size(); i++) {			
			    cv::convexHull(contours[i], convexHulls[i]);               
		    }

            for(int i = 0; i<convexHulls.size(); i++){
                if(contourArea(convexHulls[i],0)>20)  
                    
                    drawContours(Frame, convexHulls, i, SCALAR_RED ,1, 8, hierarchy);                              
            }          

            //imshow("二值化＋convexhulls",FrameCopy);
            imshow("原圖+convexhulls",Frame); 
            //imwrite("ori_contours.jpg",src); 
            //imwrite("sobel_contours.jpg",grad);            
            writer  << Frame;        

/////////////////////////laplace////////////////////////////////////////////////////////
/*
            int kernel_size = 3;              
            char* window_name_2= "Laplace";
            Mat dst;           

            /// Create window
            namedWindow( window_name_2, CV_WINDOW_AUTOSIZE );

            /// Apply Laplace function
            Mat abs_dst;

            Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
            convertScaleAbs( dst, abs_dst );
            threshold(abs_dst, abs_dst, 90, 255, THRESH_BINARY);
            /// Show what you got
            // imshow( window_name_2, abs_dst );
*/
///////////////////////////////////////////////////////////////////////////////////////////	
			if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT))             
				capVideo.read(Frame);			
			else             
				break;		

			chCheckForEscKey = cv::waitKey(50);
		}			
	
	    if (chCheckForEscKey != 27)        // if the user did not press esc (i.e. we reached the end of the video)
	        waitKey(0);                        // hold the windows open to allow the "end of video" message to show	    

    system("pause");
	return(0);
}