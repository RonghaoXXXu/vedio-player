#include <highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/videoio.hpp"
#include <stdlib.h> 
#include <time.h>
#include <opencv.hpp>

using namespace std;
using namespace cv;

Size vsize(1000, 1000);//窗口尺寸。
int key = 1000;//播放停顿时间。

Mat srcImg[6];
Mat dstImg[6];
Mat intImg[6];

void getRandNum(int* a, int n, int min, int max);
void RandNum(int* a,int n);

int main()
{
	int a[6];
	RandNum(a,6);
	//背景颜色。
	intImg[0] = Mat(vsize, CV_8UC3, Scalar(0, 0, 255));//红
	intImg[1] = Mat(vsize, CV_8UC3, Scalar(225, 43, 138));//紫罗兰
	intImg[2] = Mat(vsize, CV_8UC3, Scalar(255, 0, 0));//蓝
	intImg[3] = Mat(vsize, CV_8UC3, Scalar(205, 224,64));//青绿色
	intImg[4] = Mat(vsize, CV_8UC3, Scalar(0,255, 0));//绿
	intImg[5] = Mat(vsize, CV_8UC3, Scalar(65, 254,254));//金黄
	for (int i = 0; i < 6; i++)
	{
		//pnum即为图片编码，name即为图片名称。
		char name[64];
		int pnum=0;
		pnum = a[i];
		sprintf_s(name, "%d.jpg", pnum);
		srcImg[i] = imread(name, 0);
		threshold(srcImg[i],srcImg[i], 100, 255, 1);//二值化
		cv::resize(srcImg[i], srcImg[i], vsize, 0, 0, INTER_CUBIC);
		//彩色图处理。
		Mat bicImg = imread(name);
		cv::resize(bicImg, bicImg, vsize, 0, 0, INTER_CUBIC);
		switch (pnum)
		{
			case 0:
			case 6:
			case 12:
				bitwise_and(bicImg,intImg[0],dstImg[i]);
				break;
			case 1:
			case 7:
			case 13:
				bitwise_and(bicImg, intImg[1], dstImg[i]);
				break;
		    case 2:
			case 8:
			case 14:
				bitwise_and(bicImg, intImg[2], dstImg[i]);
				break;
		    case 3:
			case 9:
			case 15:
				bitwise_and(bicImg, intImg[3], dstImg[i]);
				break;
			case 4:
			case 10:
			case 16:
				bitwise_and(bicImg, intImg[4], dstImg[i]);
				break;
		    case 5:
			case 11:
			case 17:
				bitwise_and(bicImg, intImg[5], dstImg[i]); 
				break;
			default:
				break;
		}
	}
	namedWindow("Movie Player");
	for (int j = 0; j < 6; j++)
	{
		imshow("Movie Player", srcImg[j]);
		waitKey(key);
		imshow("Movie Player", dstImg[j]);
		waitKey(key);
	}
	destroyWindow("Movie Player");
	std::cout << "播放完毕";
	return 0;
}
void getRandNum(int* a, int n, int min, int max)
{
	int i, j, t, m = 0, flag;
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		while (1)
		{
			flag = 0;
			t = rand() % (max - min + 1) + min;
			for (j = 0; j < m; j++)
			{
				if (a[j] == t)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				a[m++] = t;
				break;
			}
		}
	}
}
void RandNum(int *a,int n)
{
	int RandNum[6][3];
	int flag = 0;
	int rows[6] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			RandNum[j][i] = flag;
			flag++;
		}
	}
	getRandNum(rows, 6, 0, 5);
	for(int b=0;b<n;b++)
	{ 
		a[b] = RandNum[rows[b]][rand() % 3];
	}
}



