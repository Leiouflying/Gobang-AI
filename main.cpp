#undef UNICODE
#undef _UNICODE	//取消 Unicode 编码的宏定义，让整个项目以 MBCS 编码编译，以解决编码问题
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <easyx_ex.h>
#include <conio.h>
// 引用该库才能使用 TransparentBlt 函数
#pragma comment( lib, "MSIMG32.LIB")

#define VERSION_X 0
#define VERSION_Y 0
#define VERSION_Z 1		//Read more detail: https://www.geekdt.com/335.html

using namespace std;

void version();
void loadimage_transparent(const char *local, int width, int height, COLORREF color, int x, int y);

int main()
{
	version();
	initgraph(800, 600);
	loadimage_transparent("C:\\test.bmp", 800, 800, 0x00ff00, 0, 0);

	system("pause");
	return 0;
}
void loadimage_transparent(const char *local, int width, int height, COLORREF color, int x, int y)//Attention:bmp file only!!!
//目标路径,目标宽度,目标高度,透明色,目标位置x轴偏移量,目标位置y轴偏移量
{
	IMAGE img;
	loadimage(&img, local, width, height);
	// 获取绘图窗口和 IMAGE 对象的句柄，TransparentBlt() 函数需要用
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(&img);
	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, width, height, srcDC, x, y, width, height, color);// 最后一个参数是设置透明色
	FlushBatchDraw(); //使 GDI 操作生效
}
void version()	//More detail https://www.geekdt.com/335.html
{
	printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}