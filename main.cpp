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

void version();//More detail https://www.geekdt.com/335.html
void loadimage_transparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);//����͸����ͼ
void environment(double m);//������������Ļ���
void testtools();//���Թ���

int main()
{
	version();
	environment(14.62);//��ֽ����Ϊ14.62 �����ز����ƣ�ֻ�ܻ��Ʒ�����ֽ
	loadimage_transparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, 30, 50);//���ư�ɫ����
	loadimage_transparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, 210, 50);//���ƺ�ɫ����
	//loadimage_transparent("white_piece.bmp", 800, 800, 0x00ff00, 0, 0);

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
void version()
{
	printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}
void environment(double m)//"m"Ϊ��ֽ����
{
	initgraph(800, 600);//������ͼ����
	//��������
	loadimage(NULL, ("IMAGE"), ("IMAGE_BACKGROUND"), 800, 600);
	//������ֽ
	setlinecolor(0x00ff00);//
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	line(27, 27, 2.5 * m * 15 + 27, 27);//��ֽ����Ϊ14.62	�����ز����ƣ�ֻ�ܻ��Ʒ�����ֽ
	line(27, 571, 2.5 * m * 15 + 27, 571);
	line(27, 27, 27, 2.5 * m * 15 + 27);
	line(574, 27, 574, 2.5 * m * 15 + 27);

}
void testtools()
{
	//���̱߽����
	int x1 = 27, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 574, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
}