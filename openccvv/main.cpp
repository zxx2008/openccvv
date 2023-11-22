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

	Mat img;	//�洢��Ƶ��ÿһ֡
	//Mat show;
	//׼���滻���ַ�
	const char* str = "@#$&%=+()1~'^,.   ";
	int length = strlen(str);
	int index = 0;
	string text;
	//�����滻���ֵ���ʽ
	settextstyle(12, 0, "����");	//��������
	setbkmode(TRANSPARENT);			//ȥ�����ֱ���
	settextcolor(WHITE);		//����������ɫ

	BeginBatchDraw();	//��ʼ˫�����ͼ

	while (1) {
		video >> img;
		if (img.empty()) {
			break;
		}
		//����ͼ���һЩ����
		//��ԭͼ���ɻҶ�ͼ
		cvtColor(img, img, COLOR_BGR2GRAY);
		//resize(img, show, Size(300, 150));
		resize(img, img, Size(150, 50));

		cleardevice(); //����

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
		//��ʱ30ms
		int key = waitKey(0);
		if (key == ' ')
			break;
		FlushBatchDraw();	//˫�����ͼ
	}
	EndBatchDraw();		//����˫����
	//while (1);
	//mciSendString("close 1.mp3", 0, 0, 0);
	closegraph();
	return 0;
}