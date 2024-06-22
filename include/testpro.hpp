#include<opencv2/opencv.hpp>
#include<string>
#include<cmath>


typedef std::vector<cv::Point> PointList;
typedef void (*MouseCallback)(int event, int x, int y, int flags, void* param);


void angleFinder();

void onMouse(int event, int x, int y, int flags, void* param);

double gradient(cv::Point p1,cv::Point p2);


