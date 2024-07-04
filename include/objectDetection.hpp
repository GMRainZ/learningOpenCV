#include<opencv2/opencv.hpp>
#include<string>
#include<vector>
#include<fstream>
#include<opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

class ObjectDetection 
{
public:
    ObjectDetection(std::string modelConfiguration="/ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt", 
        std::string modelWeights="/frozen_inference_graph.pb");
    
    ~ObjectDetection()=default;

    // 检测物体
    void detectObject();

private:
    std::vector<cv::String> classNames;
    cv::dnn::DetectionModel mNet;
    void getNames();    
};