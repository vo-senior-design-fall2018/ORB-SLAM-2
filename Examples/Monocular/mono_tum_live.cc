#include <iostream>
#include <algorithm> 
#include <fstream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <System.h>

using namespace std;
int main(int argc, char **argv) 
{
   if(argc != 3) 
   {
     cerr << endl << "Usage: ./path_to_PF_ORB path_to_vocabulary path_to_settings path_to_dev_video" << endl;
     return 1;
   }
const std::string url = "http://172.29.242.106:80/live";
   cv::VideoCapture cap(url);
   if (!cap.isOpened())
   {
     cerr << endl  <<"Could not open camera feed."  << endl;
	perror("This is the error");
     return -1;
   }
   // Create SLAM system. It initializes all system threads and gets ready to process frames.
   ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

   cout << endl << "-------" << endl;
   cout << "Start processing sequence ..." << endl;

   // Main loop
   int timeStamps=0;
   for(;;timeStamps++)
   {
     //Create a new Mat
     cv::Mat frame;

     //Send the captured frame to the new Mat
     cap>>frame;

     // Pass the image to the SLAM system
     SLAM.TrackMonocular(frame, timeStamps);
    }

   // Stop all threads
   SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");
    return 0;
}
