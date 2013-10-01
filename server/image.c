#include "cv.h"
#include "highgui_c.h"
#include "image.h"
#include <string.h>
#include <stdio.h>

void Image_Handler(FCGIContext * context, char * params)
{
	static CvCapture * capture = NULL;
	if (capture == NULL) {
		capture = cvCreateCameraCapture(0);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);
	}
	static int p[] = {CV_IMWRITE_JPEG_QUALITY, 100, 0};

	IplImage * frame = cvQueryFrame(capture);
	assert(frame != NULL);

//        CvMat stub;
 //       CvMat * background = cvGetMat(frame, &stub, 0, 0);

//	CvMat *cv8u = cvCreateMat(frame->width, frame->height, CV_8U);
//	double min, max;
//	CvPoint a,b;	
//	cvMinMaxLoc(background, &min, &max, &a, &b, 0);
	
//	double ccscale = 255.0/(max-min);
//	double ccshift = -min;
	//cvCvtScale(frame, cv8u, ccscale, ccshift);
	CvMat * jpg = cvEncodeImage(".jpg", frame, p);

	// Will this work?
	Log(LOGNOTE, "Sending image!");
	FCGI_PrintRaw("Content-type: image/jpg\r\n");
	FCGI_PrintRaw("Cache-Control: no-cache, no-store, must-revalidate\r\n\r\n");
	//FCGI_PrintRaw("Content-Length: %d", jpg->rows*jpg->cols);
	FCGI_WriteBinary(jpg->data.ptr,1,jpg->rows*jpg->cols);
	
	cvReleaseMat(&jpg);
	cvReleaseImageHeader(&frame);
}
