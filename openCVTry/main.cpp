#include "videoAnalysis.h"

/*
Main function to run the code
*/
//"C:\\Users\\lawra\\Desktop\\Stuff\\test.mp4" test video
int main() {
	std::string videoName = "";
	std::cout << "Enter the video file name that you want to analyze(if webcam then enter \"w\"): ";
	std::cin >> videoName;
	if (videoName == "w") {
		VideoAnalysis webcam = VideoAnalysis("haarcascade_frontalface_alt.xml");
		return webcam.Webcam();
	}
	else {
		VideoAnalysis video = VideoAnalysis("haarcascade_frontalface_alt.xml", videoName);
		return video.Video();
	}
	return 0;
}