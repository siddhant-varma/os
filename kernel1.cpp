#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int main(void){
	cout<<"\nThe kernel version is:\n";
	system("cat /proc/sys/kernel/osrelease\n");
	cout<<"\nCPU Space:\n";
	system("cat /proc/cpuinfo |awk 'NR==3, NR==4{print}'\n");
	cout<<endl;
	
	return 0;
	
}
	
