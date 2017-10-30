//3. WRITE A PROGRAM to report behaviour of Linux kernel including information on
// configured memory, amount of free and used memory. (memory information)

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(void){
	cout<<"\nAmount of CPU time since system was last booted is:\n";
	system("sudo cat /proc/uptime\n");
	cout<<"\nConfigured Memory is:\n";
	system("cat /proc/meminfo | awk 'NR==1{print$2}'\n");
	cout<<"\nAmout of Free Memory:\n";
	system("cat /proc/meminfo | awk 'NR==2{print$2}'\n");
	cout<<"\nAmount of Memory used:\n";
	system("cat /proc/meminfo | awk '{if (NR==1) a = $2; if(NR==2) b = $2 }END {print a-b}'\n");

	cout<<endl;
	return 0;	
}
