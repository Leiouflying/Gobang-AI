#include <iostream>
#include <stdio.h>

#define VERSION_X 0
#define VERSION_Y 0
#define VERSION_Z 2
using namespace std;

void version();

int main()
{
	version();
	cout << "Hello World. This Project is developing...\n";
	system("pause");
	return 0;
}
void version()
{
	printf("VERSION: %d.%d.%d\n", VERSION_X, VERSION_Y, VERSION_Z);
}