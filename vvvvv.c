#include <stdio.h>
#include <unistd.h>
int main(){
	char *c = malloc(sizeof(char)*20);
	char *a = "Secret Message";
	memcpy(c,a,16);
	printf("string addr : %lx\n",c);
	while(1){
		printf("%s\n",c);
		for(int i = 0;i<20000000;i++);
	}

	return 0;
}