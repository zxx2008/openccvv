#include <iostream>
#include <opencv2/opencv.hpp>
#include <easyx.h>
#include <mmsystem.h>
#include <graphics.h>

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace cv;

#define WIDTH 960
#define HEIGHT 640

int main() {
	initgraph(WIDTH, HEIGHT);

	VideoCapture video("C:\\Users\\26659\\Downloads\\Bad Apple but it's in 4k 60fps.mp4");

	mciSendString("open 1.mp3", 0, 0, 0);

	Mat img;	//�洢��Ƶ��ÿһ֡

	while (1) {
		video >> img;
		if (img.empty()) {
			break;
		}
		//����ͼ���һЩ����
		//��ԭͼ���ɻҶ�ͼ
		cvtColor(img, img, COLOR_BGR2GRAY);
		imshow("BadApple", img);
		mciSendString("play 1.mp3", 0, 0, 0);
		//��ʱ30ms
		int key = waitKey(23);
		if (key == ' ')
			break;
	}

	//while (1);

	closegraph();
	return 0;
}