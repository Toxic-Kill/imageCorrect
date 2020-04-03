#include <iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat binMat;
	cv::Mat srcMat = cv::imread("D:\\Files\\lena_rot.jpg");//读取图像
	//检测图像是否读取成功
	if (srcMat.empty())
	{
		return -1;
	}
	int width = srcMat.cols;
	int height = srcMat.rows;
	cv::threshold(srcMat, binMat, 250, 255, THRESH_BINARY);//进行二值化
	int x1,y1;
	//第一次遍历寻找顶点
	for (int j = 0; j < width; j++)
	{
		if (binMat.at<Vec3b>(0, j)[0] = 0)
		{
			x1 = j;
			break;
		}
	}
	//第二次遍历寻找顶点
	for (int i = -height + 1; i <= 0; i++)
	{
		if (binMat.at<Vec3b>(i, 0)[0] = 0)
		{
			y1 = -i;
			break;
		}
	}
	//计算出缩放尺寸
	double length = sqrt((width*0.5 - x1)*(width*0.5 - x1) + (height*0.5)*(height*0.5));
	double scale = ((sqrt(width*width + height * height))*0.5) / length;
	//计算出旋转角度
	double angle = atan(x1/y1);
	//旋转中心为图像中心
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	//获得变换矩阵
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
	//进行矫正
	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());
	cv::imshow("src", srcMat);//显示原图像
	cv::imshow("dst", dstMat);//显示矫正后图像
	waitKey(0);
}