#ifndef VIDEO_ANALYSIS_H
#define VIDEO_ANALYSIS_H
#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
#include<mutex>

class VideoAnalysis {
private:
	cv::CascadeClassifier faceCascade;
	double scale{3};
	std::string haarcascade{ "C:\\Users\\lawra\\Desktop\\Coding Private\\C++\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml" };
	std::string videoLocation{""} ;
	std::deque<cv::Mat> frames; 
	//std::mutex mtx;
	void Analyze(cv::Mat frame);
	void Buffer(cv::VideoCapture cap);
	void Display();

public:
	VideoAnalysis();
	VideoAnalysis(std::string haarcascade);
	VideoAnalysis(std::string haarcascade, std::string video);
	VideoAnalysis(std::string haarcascade, double scale);
	VideoAnalysis(std::string haarcascade, std::string video, double scale);
	int Webcam();
	int Video();
};


#endif /* VIDEO_ANALYSIS_H */ 
