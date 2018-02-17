#undef UNICODE
#undef _UNICODE	//取消 Unicode 编码的宏定义，让整个项目以 MBCS 编码编译，以解决编码问题
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#pragma comment( lib, "MSIMG32.LIB")// 引用该库才能使用 TransparentBlt 函数

#define VERSION_X "0"
#define VERSION_Y "0"
#define VERSION_Z "1"		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

//Gobal variable
int map[15][15];//0:空坐标	1:黑棋子	2:白棋子

//function
void version();//More detail https://www.geekdt.com/335.html
void loadimage_transparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);//绘制透明贴图
void create_environment();//构建五子棋对弈环境
void put_piece(char color, int x, int y);//绘制棋子 映射为GUI
void testtools();//测试工具
bool whofirst();//请求用户选择AI先手还是用户先手
void clear_map();//清空棋盘地图
bool judge(int x, int y);//检查该检查点是否构成一方获胜的条件


int main()
{
	srand((int)time(0));//Set a send of rand fuction by time
	create_environment();
	clear_map();	//使用前可能要清理一下map
	version();
	if (whofirst() == 1)//AI first
	{
		put_piece('b', (int)rand() % 14, (int)rand() % 14);
	}
	else if (whofirst == 0)//User first
	{

	}
	else //未知错误 From: whofirst function
	{

	}
	system("pause");
	return 0;
}
bool judge(int x, int y)//检查点x坐标,检查点y坐标 RETURN: win=1 empty=0
{
	int color_source = map[x][y];
	int judge_x = 0, judge_y = 0, slope_left = 0, slope_right = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (map[x - i][y] != color_source && judge_x != -1)
			//横向_逻辑左 判断是否连子
		{
			judge_x++;
		}
		else
		{
			judge_x = -1;
		}

		if (map[x + 1][y] != color_source && judge_x != -1)
			//横向_逻辑右 判断是否连子
		{
			judge_x++;
		}
		else
		{
			judge_x = -1;
		}

		if (map[x][y - 1] != color_source && judge_y != -1)
			//纵向_逻辑上 判断是否连子
		{
			judge_y++;
		}
		else
		{
			judge_y = -1;
		}

		if (map[x][y + 1] != color_source && judge_y != -1)
			//纵向_逻辑下 判断是否连子
		{
			judge_y++;
		}
		else
		{
			judge_y = -1;
		}

		if (map[x - 1][y - 1] != color_source && slope_left != -1)
			//倾斜_逻辑左上 判断是否连子
		{
			slope_left++;
		}
		else
		{
			slope_left = -1;
		}

		if (map[x - 1][y + 1] != color_source && slope_right != -1)
			//倾斜_逻辑左下 判断是否连子
		{
			slope_right++;
		}
		else
		{
			slope_right = -1;
		}

		if (map[x + 1][y - 1] != color_source && slope_right != -1)
			//倾斜_逻辑右上 判断是否连子
		{
			slope_right++;
		}
		else
		{
			slope_right = -1;
		}

		if (map[x + 1][y + 1] != color_source && slope_left != -1)
			//倾斜_逻辑右下 判断是否连子
		{
			slope_left++;
		}
		else
		{
			slope_left = -1;
		}
	}
	if (judge_x == 5 || judge_y == 5 || slope_left == 5 || slope_right == 5)//判断获胜
	{
		return 1;
	}
	else//没人获胜
	{
		return 0;
	}
}
bool whofirst()//RETURN: AI first: 1	User first: 0
{
	HWND hwnd = GetHWnd();
	if (MessageBox(hwnd, "Let AI first or not ?", "Select Who First", MB_YESNO | MB_ICONQUESTION) == IDYES)//来自WinUser API(MFC)的函数，判断谁先手
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
//目标路径,目标宽度,目标高度,透明色,目标位置x轴偏移量,目标位置y轴偏移量
{
	IMAGE img;
	loadimage(&img, (res_Type), (res_Name), width, height);
	// 获取绘图窗口和 IMAGE 对象的句柄，TransparentBlt() 函数需要用
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(&img);
	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, width, height, srcDC, 0, 0, width, height, color);// 最后一个参数是设置透明色
	FlushBatchDraw(); //使 GDI 操作生效
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
	//printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z); //终端界面输出的代码（无需启用）
}
void create_environment()//"m"为谱纸倍数
{
	initgraph(800, 600);//构建绘图窗口

	//绘制棋盘
	loadimage(NULL, ("IMAGE"), ("IMAGE_BACKGROUND"), 800, 600);

	//绘制谱纸
	setlinecolor(0x000000);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);

	//谱纸倍数为15.61	由于素材限制，只能绘制方形谱纸
	for (int i = 1; i <= 13; i++)
	{
		line(27, 27 + 2.5*15.61*i, 2.5*15.61 * 14 + 27, 27 + 2.5*15.61*i);//画横线
		line(27 + 2.5*15.61*i, 27, 27 + 2.5*15.61*i, 2.5*15.61 * 14 + 27);//画竖线
	}

}
void put_piece(char color, int x, int y)//color w:white_piece b:black_piece	local 0-14 only
//棋子颜色,目标位置x轴偏移量,目标位置y轴偏移量
{
	x = 27 + 2.5*15.61*x - 15;//目标位置x轴的GUI位置偏移换算
	y = 27 + 2.5*15.61*y - 15;//目标位置y轴的GUI位置偏移换算
	switch (color)
	{
		case 'w':
			{
				loadimage_transparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, x, y);//绘制白色棋子
				map[x][y] = 2;
				break;
			}
		case 'b':
			{
				loadimage_transparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, x, y);//绘制黑色棋子
				map[x][y] = 1;
				break;
			}
		default:
			{
				outtext("ERROR: color error of draw_piece");//颜色参数输入错误处理 直接输出一段报错字符串
			}
	}

}
void testtools()
{
	//棋盘边界测试
	int x1 = 27, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 574, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
	//绘制棋盘外框线（素材中已提供，暂不重复绘制防止误差）
	int m = 15.61;//create_environment()函数中会提供
	line(27, 27, 2.5 * m * 14 + 27, 27);//上 横
	line(27, 571, 2.5 * m * 14 + 27, 571);//下 横
	line(27, 27, 27, 2.5 * m * 14 + 27);//左 竖
	line(574, 27, 574, 2.5 * m * 14 + 27);//右 竖
	//棋子映射测试 绘制全棋盘的棋子
	for (int i = 0; i <= 15; i++)
	{
		for (int m = 0; m <= 15; m++)
		{
			put_piece('b', i, m);
		}
	}
}