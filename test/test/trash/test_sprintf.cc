#include <stdio.h>

int main(){
	char b[64];
	float f1, f2, f3, f4;
	f1 = 10; f2 = 20; f3 = 30; f4 = 40;
	sprintf(b, "%f %f %c", f1, f2, '\0' );
	printf("%s\n", b);
	sprintf(b, "%f %f", f3, f4);
	printf("%s\n", b);
	return 0;
}
