#include "videoAnalysis.h"
using namespace cv;
using namespace std;

/*
Constructor with no inputs
Uses webcam and the frontal_face haarcascade
*/
VideoAnalysis::VideoAnalysis() {} 

/*
Constructor for selecting haarcascade
Will use webcam as video input
*/
VideoAnalysis::VideoAnalysis(std::string haarcascade) {
	this->haarcascade = haarcascade;
};

/*
Constructor for selecting haarcascade and video for analysis
*/
VideoAnalysis::VideoAnalysis(std::string haarcascade, std::string video) {
	this->haarcascade = haarcascade;
	videoLocation = video;
}

/*
Constructor for selecting haarcascade and setting scale
Uses webcam for video
*/
VideoAnalysis::VideoAnalysis(std::string haarcascade, double scale) {
	this->haarcascade = haarcascade;
	this->scale = scale;
}

/*
Constructor for selecting haarcascade, inputing video for analysis and setting scale
*/
VideoAnalysis::VideoAnalysis(std::string haarcascade, std::string video, double scale) {
	this->haarcascade = haarcascade;
	videoLocation = video;
	this->scale = scale;
};

/*
Analysis the video and displays the output
*/
int VideoAnalysis::AnalyzeVideo() {
	faceCascade.load(haarcascade);

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}

	for (;;) {
		Mat frame;
		cap >> frame;
		flip(frame, frame, 1);
		Mat grayscale;
		cvtColor(frame, grayscale, COLOR_BGR2GRAY);
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		vector<Rect> faces;
		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}

		imshow("Webcam Frame", frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}