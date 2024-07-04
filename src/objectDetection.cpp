#include "objectDetection.hpp"

ObjectDetection::ObjectDetection(std::string modelConfiguration, std::string modelWeights)
:mNet(CONFIG_PATH + modelConfiguration,CONFIG_PATH + modelWeights)
{
    std::cout<<modelConfiguration<<std::endl;
    std::cout<<modelWeights<<std::endl;
    //加载模型
    mNet.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    mNet.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    //设置输入尺寸
    mNet.setInputSize(320,320);
    //设置输入比例
    mNet.setInputScale(1.0/127.5);
    //设置输入平均值
    mNet.setInputMean((127.5,127.5,127.5));
    //设置输入通道顺序
    mNet.setInputSwapRB(true);

    getNames();
}

void ObjectDetection::detectObject()
{

    cv::VideoCapture cap(std::string(IMAGE_DIR)+"/Road_traffic_video2.mp4");
    if (!cap.isOpened())
    {
        fprintf(stderr,"cap fail to open\n");
        return;
    }

    cv::Mat frame,blob;
    std::vector<std::vector<cv::Mat>> outputs;
    // 解析输出
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    while (cap.read(frame))
    {

    }
    cap.release();
    cv::destroyAllWindows();
}

void ObjectDetection::getNames()
{
    std::string filename=CONFIG_PATH;
    filename+="/coco.names";
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            classNames.emplace_back(line);
        }
    }
    file.close();
}
