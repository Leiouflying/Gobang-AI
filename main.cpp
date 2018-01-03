#undef UNICODE
#undef _UNICODE	//ȡ�� Unicode ����ĺ궨�壬��������Ŀ�� MBCS ������룬�Խ����������
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
// ���øÿ����ʹ�� TransparentBlt ����
#pragma comment( lib, "MSIMG32.LIB")

#define VERSION_X 0
#define VERSION_Y 0
#define VERSION_Z 1		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

void version();
void loadimage_transparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);
void testtools();

int main()
{
	version();
	initgraph(800, 600);
	loadimage(NULL, ("IMAGE"), ("IMAGE_BACKGROUND"), 800, 600);
	loadimage_transparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, 30, 50);
	loadimage_transparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, 210, 50);
	//loadimage_transparent("white_piece.bmp", 800, 800, 0x00ff00, 0, 0);
	testtools();
	system("pause");
	return 0;
}
void loadimage_transparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y)//*.bmp file only
//Ŀ��·��,Ŀ����,Ŀ��߶�,͸��ɫ,Ŀ��λ��x��ƫ����,Ŀ��λ��y��ƫ����
{
	IMAGE img;
	loadimage(&img, (res_Type), (res_Name), width, height);
	// ��ȡ��ͼ���ں� IMAGE ����ľ����TransparentBlt() ������Ҫ��
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(&img);
	// ʹ�� Windows GDI ����ʵ��͸��λͼ
	TransparentBlt(dstDC, x, y, width, height, srcDC, 0, 0, width, height, color);// ���һ������������͸��ɫ
	FlushBatchDraw(); //ʹ GDI ������Ч
}
void version()	//More detail https://www.geekdt.com/335.html
{
	printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}
void testtools()
{
	//���̱߽����
	int x1 = 28, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 573, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
}