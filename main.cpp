#undef UNICODE
#undef _UNICODE	//ȡ�� Unicode ����ĺ궨�壬��������Ŀ�� MBCS ������룬�Խ����������
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#pragma comment( lib, "MSIMG32.LIB")// ���øÿ����ʹ�� TransparentBlt ����

#define VERSION_X "0"
#define VERSION_Y "0"
#define VERSION_Z "1"		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

//Gobal variable
int map[15][15];//0:������	1:������	2:������
MOUSEMSG m;//���������Ϣ
int now_x, now_y;//���һ�β�����xy���� �����߼���
int ai_score[15][15][4],user_score[15][15][4];//�ڵ��������ݿ⣬��ռ����Ϊ-1�������ֱ�Ϊx�����꣬y�����꣬������б��б���ж�
												//0����	1������	2����б	3����б

//function
void version();//More detail https://www.geekdt.com/335.html
void LoadimageTransparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);//����͸����ͼ
void CreateEnvironment();//������������Ļ���
void PutPiece(char color, int x, int y);//�������� ӳ��ΪGUI
void TestTools();//���Թ���
bool WhoFirst();//�����û�ѡ��AI���ֻ����û�����
void ClearMap();//������̵�ͼ
bool judge(int x, int y);//���ü����Ƿ񹹳�һ����ʤ������
void UserPut(char color);
void AIPut(char color);

int main()
{
	srand((int)time(0));//Set a send of rand fuction by time
	CreateEnvironment();
	ClearMap();	//ʹ��ǰ����Ҫ����һ��map
	version();
	char ai_color;
	char user_color;
	if (WhoFirst() == 1)//AI first
	{
		now_x = rand() % 14;
		now_y = rand() % 14;
		PutPiece('b', now_x, now_y);
		UserPut('w');
		ai_color = 'b';
		user_color = 'w';
	}
	else//User first -> WhoFirst()==0
	{
		UserPut('b');
		ai_color = 'w';
		user_color = 'b';
	}

	while(true)
	{
		AIPut(ai_color);
		if (judge(now_x, now_y) == 1)
		{
			outtext("AI��ʤ");//��ʱ����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break;
		}
		UserPut(user_color);
		if (judge(now_x, now_y) == 1)
		{
			outtext("����ʤ��");//��ʱ����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break;
		}
	}
	outtext("������");//��ʱ���룡����������������������������������������������
	system("pause");
	return 0;
}
void AIPut(char color)
{

}
void UserPut(char color)
{
	int user_x, user_y;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			user_x = (m.x - 27 + 15) / (2.5*15.61);
			user_y = (m.y - 27 + 15) / (2.5*15.61);
			PutPiece(color, user_x, user_y);
			if (color == 'b')
			{
				map[user_x][user_y] = 1;
			}
			else
			{
				map[user_x][user_y] = 2;
			}
			now_x = user_x;
			now_y = user_y;
			return;
		}
	}
}
bool judge(int x, int y)//����x����,����y���� RETURN: win=1 empty=0
{
	int color_source = map[x][y];
	int judge_x = 0, judge_y = 0, slope_left = 0, slope_right = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (map[x - i][y] != color_source && judge_x != -1)
			//����_�߼��� �ж��Ƿ�����
		{
			judge_x++;
		}
		else
		{
			judge_x = -1;
		}

		if (map[x + 1][y] != color_source && judge_x != -1)
			//����_�߼��� �ж��Ƿ�����
		{
			judge_x++;
		}
		else
		{
			judge_x = -1;
		}

		if (map[x][y - 1] != color_source && judge_y != -1)
			//����_�߼��� �ж��Ƿ�����
		{
			judge_y++;
		}
		else
		{
			judge_y = -1;
		}

		if (map[x][y + 1] != color_source && judge_y != -1)
			//����_�߼��� �ж��Ƿ�����
		{
			judge_y++;
		}
		else
		{
			judge_y = -1;
		}

		if (map[x - 1][y - 1] != color_source && slope_left != -1)
			//��б_�߼����� �ж��Ƿ�����
		{
			slope_left++;
		}
		else
		{
			slope_left = -1;
		}

		if (map[x - 1][y + 1] != color_source && slope_right != -1)
			//��б_�߼����� �ж��Ƿ�����
		{
			slope_right++;
		}
		else
		{
			slope_right = -1;
		}

		if (map[x + 1][y - 1] != color_source && slope_right != -1)
			//��б_�߼����� �ж��Ƿ�����
		{
			slope_right++;
		}
		else
		{
			slope_right = -1;
		}

		if (map[x + 1][y + 1] != color_source && slope_left != -1)
			//��б_�߼����� �ж��Ƿ�����
		{
			slope_left++;
		}
		else
		{
			slope_left = -1;
		}
	}
	if (judge_x == 5 || judge_y == 5 || slope_left == 5 || slope_right == 5)//�жϻ�ʤ
	{
		return 1;
	}
	else//û�˻�ʤ
	{
		return 0;
	}
}
bool WhoFirst()//RETURN: AI first: 1	User first: 0
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
void ClearMap()
{
	for (int m = 0; m <= 14; m++)
	{
		for (int n = 0; n <= 14; n++)
		{
			map[m][n] = 0;
		}
	}
}
void LoadimageTransparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y)//*.bmp file only
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
	//printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z); //�ն˽�������Ĵ��루�������ã�
}
void CreateEnvironment()//"m"Ϊ��ֽ����
{
	initgraph(800, 600);//������ͼ����

	//��������
	loadimage(NULL, ("IMAGE"), ("IMAGE_BACKGROUND"), 800, 600);

	//������ֽ
	setlinecolor(0x000000);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);

	//��ֽ����Ϊ15.61	�����ز����ƣ�ֻ�ܻ��Ʒ�����ֽ
	for (int i = 1; i <= 13; i++)
	{
		line(27, 27 + 2.5*15.61*i, 2.5*15.61 * 14 + 27, 27 + 2.5*15.61*i);//������
		line(27 + 2.5*15.61*i, 27, 27 + 2.5*15.61*i, 2.5*15.61 * 14 + 27);//������
	}

}
void PutPiece(char color, int x, int y)//color w:white_piece b:black_piece	local 0-14 only
//������ɫ,Ŀ��λ��x��ƫ����,Ŀ��λ��y��ƫ����
{
	int gui_x = 27 + 2.5*15.61*x - 15;//Ŀ��λ��x���GUIλ��ƫ�ƻ���
	int gui_y = 27 + 2.5*15.61*y - 15;//Ŀ��λ��y���GUIλ��ƫ�ƻ���
	switch (color)
	{
	case 'w':
	{
		LoadimageTransparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, gui_x, gui_y);//���ư�ɫ����
		map[x][y] = 2;
		break;
	}
	case 'b':
	{
		LoadimageTransparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, gui_x, gui_y);//���ƺ�ɫ����
		map[x][y] = 1;
		break;
	}
	default:
	{
		outtext("ERROR: color error of draw_piece");//��ɫ������������� ֱ�����һ�α����ַ���
	}
	}

}
void TestTools()
{
	//���̱߽����
	int x1 = 27, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 574, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
	//������������ߣ��ز������ṩ���ݲ��ظ����Ʒ�ֹ��
	int m = 15.61;//CreateEnvironment()�����л��ṩ
	line(27, 27, 2.5 * m * 14 + 27, 27);//�� ��
	line(27, 571, 2.5 * m * 14 + 27, 571);//�� ��
	line(27, 27, 27, 2.5 * m * 14 + 27);//�� ��
	line(574, 27, 574, 2.5 * m * 14 + 27);//�� ��
	//����ӳ����� ����ȫ���̵�����
	for (int i = 0; i <= 15; i++)
	{
		for (int m = 0; m <= 15; m++)
		{
			PutPiece('b', i, m);
		}
	}
}