#include <stdio.h>

int main()
{
	FILE *fp;
	fp = fopen("a.text","r");
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fseek(fp,-2,SEEK_END);
	printf("입력받은 문자 : %c",fgetc(fp));
	fclose(fp);
	
	
	return 0;
}
//https://modoocode.com/117 부터 보기.