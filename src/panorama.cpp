#include "panorama.hpp"

void panorama(const std::vector<cv::Mat>&images, cv::Mat &pano)
{
    cv::Ptr<cv::Stitcher>stitcher = cv::Stitcher::create(cv::Stitcher::PANORAMA);
    auto status=stitcher->stitch(images, pano);

    if(status!=cv::Stitcher::OK)
    {
        std::cout<<"stitching failed"<<std::endl;
        exit(1);
    }
}

void getAllFiles(const std::string &path, std::vector<std::string> &files)
{
	//文件句柄
	long long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;  
	std::string p;  
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					//递归搜索
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else {
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}

void testPanorama()
{
    std::string path=IMAGE_DIR;
    std::vector<std::string> files;
    getAllFiles(path+"/panorama", files);

    std::vector<cv::Mat> images;
    for(const auto &file:files)
    {
        printf("%s\n", file.c_str());
        cv::Mat img=cv::imread(file);
        if(img.empty())continue;

        cv::resize(img, img, cv::Size(img.cols*0.2, img.rows*0.2));


        //cv::imshow("img", img);
        images.emplace_back(img);
    }

    cv::Mat pano;
    panorama(images, pano);

    printf("pano.cols=%d, pano.rows=%d\n", pano.cols, pano.rows);


    cv::imshow("pano", pano);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return ;
}


