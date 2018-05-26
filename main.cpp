#undef UNICODE
#undef _UNICODE	//取消 Unicode 编码的宏定义，让整个项目以 MBCS 编码编译，以解决编码问题
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#pragma comment( lib, "MSIMG32.LIB")// 引用该库才能使用 TransparentBlt 函数

#define VERSION_X "0"
#define VERSION_Y "0"
#define VERSION_Z "1"		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

//Gobal variable
int map[15][15];//0:空坐标	1:黑棋子	2:白棋子
MOUSEMSG m;//定义鼠标消息
char ai_color;
char user_color;
int now_x, now_y;//最后一次操作的xy坐标 棋盘逻辑型
int score_ai[15][15], score_user[15][15];//节点评分数据库，被占用则为-1，参数分别为x轴坐标，y轴坐标，横竖左斜右斜的判断
												//0：横	1：竖向	2：左斜	3：右斜		注:最后一个参数暂时废弃


//function
void version();//More detail https://www.geekdt.com/335.html
void LoadimageTransparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);//绘制透明贴图
void CreateEnvironment();//构建五子棋对弈环境
void PutPiece(char color, int x, int y);//绘制棋子 映射为GUI
void TestTools();//测试工具
bool WhoFirst();//请求用户选择AI先手还是用户先手
void ClearMap();//清空棋盘地图
bool judge(int x, int y);//检查该检查点是否构成一方获胜的条件
void UserPut(char color);
void AIPut(char color);
int score(int x, int y, char color);

int score_copy(int m, int n, int k);//mn为坐标,k为判断是谁下的
int main()
{
	srand((int)time(0));//Set a send of rand fuction by time
	CreateEnvironment();
	ClearMap();	//使用前可能要清理一下map
	version();
	if (WhoFirst() == 1)//AI first
	{
		//设定AI先手下的位置 使用随机数
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

	FILE *stream;
	freopen_s(&stream, "E:\\test.txt", "w", stdout);
	while (true)
	{
		AIPut(ai_color);
		if (judge(now_x, now_y) == 1)
		{
			outtext("AI获胜");//临时代码!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break;
		}

		UserPut(user_color);
		if (judge(now_x, now_y) == 1)
		{
			outtext("您获胜了");//临时代码!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break;
		}
		for (int m = 0; m <= 14; m++)
		{
			for (int n = 0; n <= 14; n++)
			{
				cout << map[m][n] << "\t";
			}
			cout << endl;
		}
		cout << "========================================" << endl;
	}
	outtext("结束了");//临时代码！！！！！！！！！！！！！！！！！！！！！！！！
	system("pause");
	return 0;
}
void AIPut(char color)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			score_user[i][j] = 0;
			score_ai[i][j] = 0;
		}
	}
	int user_mapcolor, ai_mapcolor;
	if (color == 'b')
	{
		ai_mapcolor = 1;
		user_mapcolor = 2;
	}
	else
	{
		ai_mapcolor = 2;
		user_mapcolor = 1;
	}
	//执行估值 遍历全地图
	for (int m = 10; m <= 14; m++)
	{
		for (int n = 0; n <= 14; n++)
		{
			if (map[m][n] == 0)
			{
				map[m][n] = user_mapcolor;
				score_user[m][n] += score_copy(m, n, 1);
				map[m][n] = ai_mapcolor;
				score_ai[m][n] += score_copy(m, n, 2);
				map[m][n] = 0;
				outtext("");
			}
		}
	}
	int max_x=0, max_y=0, max = 0;//最高分的坐标以及最高分的分数
	for (int m = 0; m < 15; m++)
	{
		for (int n = 0; n < 15; n++)
		{
			if (score_user[m][n] > max)
			{
				max = score_user[m][n];
				max_x = m;
				max_y = n;
			}
			if (score_ai[m][n] > max)
			{
				max = score_ai[m][n];
				max_x = m;
				max_y = n;
			}
		}
	}
	PutPiece(ai_color, max_x, max_y);
	now_x = max_x;
	now_y = max_y;
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
			now_x = user_x;
			now_y = user_y;
			return;
		}
	}
}
int score_copy(int m, int n, int k)//mn为坐标,k为判断是谁下的
{
	int i, j, p = 0, q = 0, b[4] = { 0 }, x = 0, shu, heng, zuoxie, youxie;
	char s;
	if (k == 1)
		s = 1;
	else
		s = 2;
	for (i = m; i < m + 5, i < 15; i++)
	{
		if (map[i][n] != s)
		{
			if (map[i][n] == 0)
			{
				b[0]++;
			}
			break;
		}
		else
			p++;
	}
	for (i = m - 1; i > m - 5, i > 0; i--)
	{
		if (map[i][n] != s)
		{
			if (map[i][n] == 0)
			{
				b[0]++;
			}
			break;
		}
		else
			q++;
	}
	heng = p + q;
	for (j = n, p = 0; j < n + 5, j < 15; j++)
	{
		if (map[m][j] != s)
		{
			if (map[m][j] == 0)
			{
				b[1]++;
			}
			break;
		}
		else
			p++;
	}
	for (j = n - 1, q = 0; j > n - 5, j > 0; j--)
	{
		if (map[m][j] != s)
		{
			if (map[i][n] == 0)
			{
				b[1]++;
			}
			break;
		}
		else
			q++;
	}
	shu = p + q;
	for (i = m, j = n, p = 0; i < 15, i < m + 5, j < 15; i++, j++)
	{
		if (map[i][j] != s)
		{
			if (map[i][j] == 0)
			{
				b[2]++;
			}
			break;
		}
		else
			p++;
	}
	for (i = m - 1, j = n - 1, q = 0; i >= 0, i > m - 5, j > 0; i--, j--)
	{
		if (map[i][j] != s)
		{
			if (map[i][j] == 0)
			{
				b[2]++;
			}
			break;
		}
		else
			q++;
	}
	zuoxie = p + q;
	for (i = m, j = n, p = 0; i >= 0, i > m - 5, j < 16; i--, j++)
	{
		if (map[i][j] != s)
		{
			if (map[i][j] == 0)
			{
				b[3]++;
			}
			break;
		}
		else
			p++;
	}
	for (i = m + 1, j = n - 1, q = 0; i < 15, i < m + 5, j>0; i++, j--)
	{
		if (map[i][j] != s)
		{
			if (map[i][j] == 0)
			{
				b[3]++;
			}
			break;
		}
		else
			q++;
	}
	youxie = p + q;
	if (heng > 4 || shu > 4 || zuoxie > 4 || youxie > 4)
	{
		x = 100;
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			if (b[i] == 0)
			{
				b[i] = -20;
			}
		}
		//heng...求人落子有多少 b[]求空的有多少
		x = heng + b[0];
		if (shu + b[1] > x)
			x = shu + b[1];
		if (zuoxie + b[2] > x)
			x = zuoxie + b[2];
		if (youxie + b[3] > x)
			x = youxie + b[3];
		//如果这附近空位为0 代表没地方下棋权重直接减20，然后求横竖左斜右斜哪个人方+空多，就哪权重高
	}
	return x;
}
int score(int x, int y, char color)
{
	//int score(int m, int n, int k)//mn为坐标,k为判断是谁下的
	//int i, j, p = 0, q = 0, b[4] = { 0 }, x = 0, shu, heng, zuoxie, youxie;
	int color_of_map, map_blank[4], map_friend[4];//0：横		1：竖向		2：左斜		3：右斜
	for (int i = 0; i <= 3; i++)
	{
		map_blank[i] = 0;
		map_friend[i] = 0;
	}

	if (color == 'b')
	{
		color_of_map = 1;
	}
	else
		//即颜色为白色'w'
	{
		color_of_map = 2;
	}
	//横向_右侧
	for (int i = x; i <= x + 5, i < 15; i++)
	{
		if (map[i][y] != color_of_map)
		{
			if (map[i][y] == 0)
			{
				map_blank[0]++;
			}
			break;
		}
		else
		{
			map_friend[0]++;
		}
	}
	//横向_左侧
	for (int i = x - 1; i >= x - 5, i >= 0; i--)
	{
		if (map[i][y] != color_of_map)
		{
			if (map[i][y] == 0)
			{
				map_blank[0]++;
			}
			break;
		}
		else
		{
			map_friend[0]++;
		}
	}
	//纵向_右侧
	for (int i = y; i <= y + 5, i < 15; i++)
	{
		if (map[x][i] != color_of_map)
		{
			if (map[x][i] == 0)
			{
				map_blank[1]++;
			}
			break;
		}
		else
		{
			map_friend[1]++;
		}
	}
	//纵向_左侧
	for (int i = y - 1; i >= y - 5, i >= 0; i++)
	{
		if (map[x][i] != color_of_map)
		{
			if (map[x][i] == 0)
			{
				map_blank[1]++;
			}
			break;
		}
		else
		{
			map_friend[1]++;
		}
	}
	//右斜_右	右上侧
	for (int i = x, u = y; i < 15, u < 15, i <= x + 5, u <= y + 5; i++, u++)
	{
		if (map[i][u] != color_of_map)
		{
			if (map[i][u] == 0)
			{
				map_blank[3]++;
			}
			break;
		}
		else
		{
			map_friend[3]++;
		}
	}
	//右斜_左	左下侧
	for (int i = x - 1, u = y - 1; i >= 0, u >= 0, i >= x - 5, u >= y - 5; i--, u--)
	{
		if (map[i][u] != color_of_map)
		{
			if (map[i][u] == 0)
			{
				map_blank[3]++;
			}
			break;
		}
		else
		{
			map_friend[3]++;
		}
	}
	//左斜_左	左上侧
	for (int i = x, u = y; i >= 0, u < 15, i >= x - 5, u <= y + 5; i--, u++)
	{
		if (map[i][u] != color_of_map)
		{
			if (map[i][u] == 0)
			{
				map_blank[2]++;
			}
			break;
		}
		else
		{
			map_friend[2]++;
		}
	}
	//左斜_右	右下侧
	for (int i = x + 1, u = y - 1; i < 15, u >= 0, i <= x + 5, u >= y - 5; i++, u--)
	{
		if (map[i][u] != color_of_map)
		{
			if (map[i][u] == 0)
			{
				map_blank[2]++;
			}
			break;
		}
		else
		{
			map_friend[2]++;
		}
	}
	if (map_friend[0] > 4 || map_friend[1] > 4 || map_friend[2] > 4 || map_friend[3] > 4)
	{
		return 100;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (map_blank[i] == 0)
			{
				map_blank[i] = -20;
			}
		}
		int max = map_friend[0] + map_blank[0];
		if ((map_friend[1] + map_blank[1]) > max)
		{
			max = (map_friend[1] + map_blank[1]);
		}
		if ((map_friend[2] + map_blank[2]) > max)
		{
			max = (map_friend[2] + map_blank[2]);
		}
		if ((map_friend[3] + map_blank[3]) > max)
		{
			max = (map_friend[3] + map_blank[3]);
		}
		return max;
	}
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
bool WhoFirst()//RETURN: AI first: 1	User first: 0
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
void ClearMap()
{
	for (int m = 0; m <= 14; m++)
	{
		for (int n = 0; n <= 14; n++)
		{
			map[m][n] = 0;
			score_ai[m][n] = 0;
			score_user[m][n] = 0;
		}
	}
}
void LoadimageTransparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y)//*.bmp file only
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
void CreateEnvironment()//"m"为谱纸倍数
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
void PutPiece(char color, int x, int y)//color w:white_piece b:black_piece	local 0-14 only
//棋子颜色,目标位置x轴偏移量,目标位置y轴偏移量
{
	int gui_x = 27 + 2.5*15.61*x - 15;//目标位置x轴的GUI位置偏移换算
	int gui_y = 27 + 2.5*15.61*y - 15;//目标位置y轴的GUI位置偏移换算
	switch (color)
	{
	case 'w':
	{
		LoadimageTransparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, gui_x, gui_y);//绘制白色棋子
		map[x][y] = 2;
		break;
	}
	case 'b':
	{
		LoadimageTransparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, gui_x, gui_y);//绘制黑色棋子
		map[x][y] = 1;
		break;
	}
	default:
	{
		outtext("ERROR: color error of draw_piece");//颜色参数输入错误处理 直接输出一段报错字符串
	}
	}

}
void TestTools()
{
	//棋盘边界测试
	int x1 = 27, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 574, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
	//绘制棋盘外框线（素材中已提供，暂不重复绘制防止误差）
	int m = 15.61;//CreateEnvironment()函数中会提供
	line(27, 27, 2.5 * m * 14 + 27, 27);//上 横
	line(27, 571, 2.5 * m * 14 + 27, 571);//下 横
	line(27, 27, 27, 2.5 * m * 14 + 27);//左 竖
	line(574, 27, 574, 2.5 * m * 14 + 27);//右 竖
	//棋子映射测试 绘制全棋盘的棋子
	for (int i = 0; i <= 15; i++)
	{
		for (int m = 0; m <= 15; m++)
		{
			PutPiece('b', i, m);
		}
	}
}