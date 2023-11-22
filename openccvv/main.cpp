#include <iostream>
#include <opencv2/opencv.hpp>
#include <easyx.h>
#include <mmsystem.h>
#include <graphics.h>
#include <conio.h>


#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace cv;

#define WIDTH 900
#define HEIGHT 506

int main() {
	initgraph(WIDTH, HEIGHT);
	//Bad Apple but it's in 4k 60fps
	VideoCapture video("D:\\BaiduNetdiskDownload\\Bad Apple but it's in 4k 60fps.mp4");

	mciSendString("open 1.mp3", 0, 0, 0);

	Mat img;	//存储视频的每一帧
	//Mat show;
	//准备替换的字符
	const char* str = "@#$&%=+()1~'^,.   ";
	int length = strlen(str);
	int index = 0;
	string text;
	//设置替换文字的样式
	settextstyle(12, 0, "楷体");	//设置字体
	setbkmode(TRANSPARENT);			//去掉文字背景
	settextcolor(WHITE);		//设置文字颜色

	BeginBatchDraw();	//开始双缓冲绘图

	while (1) {
		video >> img;
		if (img.empty()) {
			break;
		}
		//调整图像的一些属性
		//把原图像变成灰度图
		cvtColor(img, img, COLOR_BGR2GRAY);
		//resize(img, show, Size(300, 150));
		resize(img, img, Size(150, 50));

		cleardevice(); //清屏

		for (int x = 0; x < img.rows; ++x) {
			for (int y = 0; y < img.cols; ++y) {
				int color = img.at<uchar>(x, y);
				index = color / 256.0 * length;
				text += str[index];
			}
			outtextxy(0, x * textheight(str[index]), text.data());
			text.clear();
		}

		//imshow("BadApple", img);
		mciSendString("play 1.mp3", 0, 0, 0);
		//延时30ms
		int key = waitKey(0);
		if (key == ' ')
			break;
		FlushBatchDraw();	//双缓冲绘图
	}
	EndBatchDraw();		//结束双缓冲
	//while (1);
	//mciSendString("close 1.mp3", 0, 0, 0);
	closegraph();
	return 0;
}