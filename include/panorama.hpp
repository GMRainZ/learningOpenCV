#include<opencv2/opencv.hpp>
#include<io.h>

#include<opencv2/stitching.hpp>

void panorama(const std::vector<cv::Mat>& images, cv::Mat& pano);

void getAllFiles(const std::string& path, std::vector<std::string>& files);

void testPanorama();
