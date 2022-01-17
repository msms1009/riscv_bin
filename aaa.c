
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char a[0x2000] = {1,2,3,4,5,6,7,8};
	printf("addr %p\n", (void*)a);
	void* a_page = (unsigned long)a & 0xfffffffffffff000;
	a_page = (unsigned long)a_page + 0x1000;
	printf("%p\n",(void*)a_page);
	printf("victim's pid : ");
	int pid;
	int my_pid = getpid();
	scanf("%d",&pid);
	
	unsigned long vaddr = 0;
	printf("victim's vaddr : ");
	scanf("%lx",&vaddr);
	printf("vaddr : 0x%lx\n",vaddr);

	unsigned long vpage = (unsigned long)vaddr & 0xfffffffffffff000;
	unsigned long offset = (unsigned long)vaddr & 0xfff;
	printf("vpage : 0x%lx\n",vpage);
	printf("offset : 0x%lx\n",offset);

	register long int a7 asm ("a7") = 257;
	register long int a0 asm ("a0") = pid;
	register long int a1 asm ("a1") = my_pid;
	register long int a2 asm ("a2") = vpage;
	register long int a3 asm ("a3") = a_page;
	asm volatile ("scall\n\t"
		: "+r" (a0)
		: "r" (a7), "r" (a1), "r" (a2), "r" (a3)
		: "memory");

	printf("START[CHANGE/PRINT]\n");
	char *iter = a_page;
	for(int i = 0; i< 0x1000 - 10 ;i++){
		if(!memcmp((iter+i),"Secret",6)){
			memcpy((iter+i),"HACKED",6);
			break;
		}
	}
	printf("END\n");

	return 0;
}