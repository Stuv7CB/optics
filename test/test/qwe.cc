#include <stdio.h>
#include <string>
using namespace std;
int main(){
	int k = 10;
	char buf[512];
	sprintf(buf, "%d",k);
	printf("%s\n", buf);
	return 0;
}
