#undef UNICODE
#undef _UNICODE	//ȡ�� Unicode ����ĺ궨�壬��������Ŀ�� MBCS ������룬�Խ����������
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#pragma comment( lib, "MSIMG32.LIB")// ���øÿ����ʹ�� TransparentBlt ����

#define VERSION_X "0"
#define VERSION_Y "0"
#define VERSION_Z "1"		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

//Gobal variable
int map[15][15];//0:������	1:������	2:������

//function
void version();//More detail https://www.geekdt.com/335.html
void loadimage_transparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);//����͸����ͼ
void create_environment();//������������Ļ���
void draw_piece(char color, int x, int y);//�������� ӳ��ΪGUI
void testtools();//���Թ���
bool whofirst();//�����û�ѡ��AI���ֻ����û�����
void clear_map();//������̵�ͼ
int main()
{
	create_environment();
	clear_map();
	version();
	whofirst();
	system("pause");
	return 0;
}
bool whofirst()//YES: 1	NO: 0
{
	HWND hwnd = GetHWnd();
	if (MessageBox(hwnd, "Let AI first or not ?", "Select Who First", MB_YESNO | MB_ICONQUESTION) == IDYES)//����WinUser API(MFC)�ĺ������ж�˭����
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void clear_map()
{
	for (int m = 0; m <= 14; m++)
	{
		for (int n = 0; n <= 14; n++)
		{
			map[m][n] = 0;
		}
	}
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
	char version[20] = "VERSION: ";
	strcat_s(version, 20, VERSION_X);
	strcat_s(version, 20, ".");
	strcat_s(version, 20, VERSION_Y);
	strcat_s(version, 20, ".");
	strcat_s(version, 20, VERSION_Z);
	outtext(version);
	//printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}
void create_environment()//"m"Ϊ��ֽ����
{
	initgraph(800, 600);//������ͼ����

	//��������
	loadimage(NULL, ("IMAGE"), ("IMAGE_BACKGROUND"), 800, 600);

	//������ֽ
	setlinecolor(0x000000);//
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);

	//��ֽ����Ϊ15.61	�����ز����ƣ�ֻ�ܻ��Ʒ�����ֽ
	for (int i = 1; i <= 13; i++)
	{
		line(27, 27 + 2.5*15.61*i, 2.5*15.61 * 14 + 27, 27 + 2.5*15.61*i);//������
		line(27 + 2.5*15.61*i, 27, 27 + 2.5*15.61*i, 2.5*15.61 * 14 + 27);//������
	}

}
void draw_piece(char color, int x, int y)//color w:white_piece b:black_piece	local 0-14 only
//������ɫ,Ŀ��λ��x��ƫ����,Ŀ��λ��y��ƫ����
{
	x = 27 + 2.5*15.61*x - 15;//Ŀ��λ��x���GUIλ��ƫ�ƻ���
	y = 27 + 2.5*15.61*y - 15;//Ŀ��λ��y���GUIλ��ƫ�ƻ���
	switch (color)
	{
		case 'w':
			{
				loadimage_transparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, x, y);//���ư�ɫ����
				break;
			}
		case 'b':
			{
				loadimage_transparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, x, y);//���ƺ�ɫ����
				break;
			}
		default:
			{
				outtext("ERROR: color error of draw_piece");//��ɫ������������� ֱ�����һ�α����ַ���
			}
	}

}
void testtools()
{
	//���̱߽����
	int x1 = 27, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 574, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
	//������������ߣ��ز������ṩ���ݲ��ظ����Ʒ�ֹ��
	int m = 15.61;//create_environment()�����л��ṩ
	line(27, 27, 2.5 * m * 14 + 27, 27);//�� ��
	line(27, 571, 2.5 * m * 14 + 27, 571);//�� ��
	line(27, 27, 27, 2.5 * m * 14 + 27);//�� ��
	line(574, 27, 574, 2.5 * m * 14 + 27);//�� ��
	//����ӳ����� ����ȫ���̵�����
	for (int i = 0; i <= 15; i++)
	{
		for (int m = 0; m <= 15; m++)
		{
			draw_piece('b', i, m);
		}
	}
}