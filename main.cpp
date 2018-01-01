#include <iostream>
#include <stdio.h>

#define VERSION_X 0
#define VERSION_Y 0
#define VERSION_Z 2		//More detail https://www.geekdt.com/335.html

using namespace std;

void version();

int main()
{
	version();
	cout << "Hello World. This Project is developing...\n";
	system("pause");
	return 0;
}
void version()	//More detail https://www.geekdt.com/335.html
{
	printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}