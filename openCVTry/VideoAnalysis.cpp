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
	this->videoLocation = video;
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
	this->videoLocation = video;
	this->scale = scale;
};

/*
Analyze the webcam video and displays the output
*/
int VideoAnalysis::Webcam() {
	faceCascade.load(haarcascade);
	VideoCapture cap;
	
	cap = VideoCapture(0);
	if (!cap.isOpened()) {
		return -1;
	}

	while(true) {
		Mat frame;
		cap >> frame;
		flip(frame, frame, 1);
		this->Analyze(frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}

/*
Analyzes a video input and uses a buffer to try get rid of lag.
*/
int VideoAnalysis::Video() {
	faceCascade.load(haarcascade);
	VideoCapture cap;

	if (videoLocation == "") {
		return -1;
	}
	cap = VideoCapture(videoLocation);
	if (!cap.isOpened()) {
		return -1;
	}
	//buffer to grab all frames out of memory before working with them
	//Problem will arise if video is very long
	/*while (true) {
		Mat frame;
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		flip(frame, frame, 1);
		//imshow("Frame", frame);
		
		frames.push_back(frame);//std::move(std::make_unique<Mat>(frame))
		std::cout << "Frame added \n";
		
	}*/
	this->Buffer(cap);


	for (int i = 0; i < frames.size(); ++i) {
		this->Analyze(frames[i]);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}

/*
Analyzes a frame to find if a face is present and then displays the frame with rectangles around 
all the faces that are present in the frame.
*/
void VideoAnalysis::Analyze(Mat frame) {
	Mat grayscale;
	cvtColor(frame, grayscale, COLOR_BGR2GRAY);
	resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

	vector<Rect> faces;
	faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

	for (Rect area : faces)
	{
		Scalar drawColor = Scalar(255, 0, 0);
		rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
			      Point(cvRound(((int)area.x + (int)area.width - 1) * scale), cvRound(((int)area.y + (int)area.height - 1) * scale)), drawColor);
	}
	imshow("Webcam Frame", frame);//add print out for face shown at what time and location, and frame 
}

/*
Adds frames to a vector called buffer
*/
void VideoAnalysis::Buffer(VideoCapture cap) {
	while (true) {
		Mat frame;
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		flip(frame, frame, 1);
		//imshow("Frame", frame);
		//mtx.lock();
		frames.push_back(frame);//std::move(std::make_unique<Mat>(frame))
		std::cout << "Frame added \n";
		//mtx.unlock();
	}
}
/*
Display the output of buffer
*/
void VideoAnalysis::Display() {

}