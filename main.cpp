#undef UNICODE
#undef _UNICODE	//取消 Unicode 编码的宏定义，让整个项目以 MBCS 编码编译，以解决编码问题
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
// 引用该库才能使用 TransparentBlt 函数
#pragma comment( lib, "MSIMG32.LIB")

#define VERSION_X 0
#define VERSION_Y 0
#define VERSION_Z 1		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

void version();//More detail https://www.geekdt.com/335.html
void loadimage_transparent(LPCTSTR res_Type, LPCTSTR res_Name, COLORREF color, int width, int height, int x, int y);//绘制透明贴图
void environment(double m);//构建五子棋对弈环境
void testtools();//测试工具

int main()
{
	version();
	environment(14.62);//谱纸倍数为14.62 由于素材限制，只能绘制方形谱纸
	loadimage_transparent("IMAGE", "IMAGE_WHITEPiece", 0xffffff, 30, 30, 30, 50);//绘制白色棋子
	loadimage_transparent("IMAGE", "IMAGE_BLACKPiece", 0xffffff, 30, 30, 210, 50);//绘制黑色棋子
	//loadimage_transparent("white_piece.bmp", 800, 800, 0x00ff00, 0, 0);

	system("pause");
	return 0;
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
	printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}
void environment(double m)//"m"为谱纸倍数
{
	initgraph(800, 600);//构建绘图窗口
	//绘制棋盘
	loadimage(NULL, ("IMAGE"), ("IMAGE_BACKGROUND"), 800, 600);
	//绘制谱纸
	setlinecolor(0x00ff00);//
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	line(27, 27, 2.5 * m * 15 + 27, 27);//谱纸倍数为14.62	由于素材限制，只能绘制方形谱纸
	line(27, 571, 2.5 * m * 15 + 27, 571);
	line(27, 27, 27, 2.5 * m * 15 + 27);
	line(574, 27, 574, 2.5 * m * 15 + 27);

}
void testtools()
{
	//棋盘边界测试
	int x1 = 27, y1 = 27;
	fillrectangle(x1, y1, x1 + 20, y1 + 10);
	int x2 = 574, y2 = 571;
	fillrectangle(x2, y2, x2 - 20, y2 - 10);
}