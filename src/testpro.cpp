#include"testpro.hpp"

/*
void cv::circle(

    Mat& img, // 输入的图像，可以在图像上绘制圆圈
    Point center, // 圆心坐标
    int radius, // 圆的半径
    Scalar color, // 圆圈的颜色，可以用Scalar(B, G, R[, A])格式指定
    int thickness = 1, // 线条的粗细，负值表示填充圆圈
    int lineType = LINE_8, // 线型
    int shift = 0 // 圆心和半径中的小数点位数
);
*/
PointList pointList;
void angleFinder()
{
    std::string base=IMAGE_DIR;

    //read image
    cv::Mat img=cv::imread(base+"/angel.png");
    

    cv::imshow("image", img);
    cv::setMouseCallback("image", onMouse, &img);
    while(true)
    {
        if(pointList.size()%3==0 && pointList.size()>0)
        {
            cv::Point p3=pointList[pointList.size()-1],p2=pointList[pointList.size()-2],p1=pointList[pointList.size()-3];
            
            double k1=gradient(p1,p2);
            double k2=gradient(p1,p3);

            double angle=atan((k2-k1)/(1+k1*k2))*180/acos(-1);

            std::cout<<angle<<std::endl;
            pointList.clear();
        }    
        int k=cv::waitKey(10);

        if(k=='q')
        {
            img=cv::imread(base+"/angel.png");
            pointList.clear();
        }
        if(k==27)
            break;
        cv::imshow("image", img);
    }

}
/*
void cv::setMouseCallback(

    const string& windowName, // 需要监听鼠标事件的窗口名称
    MouseCallback onMouse, // 鼠标回调函数，当鼠标事件发生时被调用
    void* userdata = NULL // 传递给回调函数的用户数据指针，可选

);
*/
void onMouse(int event, int x, int y, int flags, void* param)
{
    cv::Mat* img = (cv::Mat*)param;
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        int curSize
            = pointList.size();

        if(curSize!=0 && curSize%3)
            cv::line(*img,pointList[(curSize-1)/3*3],cv::Point(x,y),cv::Scalar(0,255,0),2,8,0);
        pointList.emplace_back(x,y);
        cv::circle(*img, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        cv::imshow("image", *img);
    }

}


double gradient(cv::Point p1,cv::Point p2)
{
    return 1.*(p2.y-p1.y)/(p2.x-p1.x);
}