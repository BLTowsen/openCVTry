#ifndef VIDEO_ANALYSIS_H
#define VIDEO_ANALYSIS_H
#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>


class VideoAnalysis {
private:
	cv::CascadeClassifier faceCascade;
	double scale{2};
	std::string haarcascade{ "C:\\Users\\lawra\\Desktop\\Coding Private\\C++\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml" };
	std::string videoLocation;
public:
	VideoAnalysis();
	VideoAnalysis(std::string haarcascade);
	VideoAnalysis(std::string haarcascade, std::string video);
	VideoAnalysis(std::string haarcascade, double scale);
	VideoAnalysis(std::string haarcascade, std::string video, double scale);
	int AnalyzeVideo();
};


#endif /* VIDEO_ANALYSIS_H */ 
