//5. WRITE A PROGRAM to copy files using system calls.

#include <iostream>	//cout
#include <fcntl.h>	//permissions = 0 & 0744
#include <unistd.h>	//system calls
#include <cstdlib>	//exit()

using namespace std;

int main(int argc, char* argv[]){
	if(argc < 2){
		cout<<"\nFile Not Specified...";
		return 0;
	}
	
	int source = open(argv[1], 0);
	if(source < 0){
		cout<<"\nError opening file...";
		exit(0);
	}
	
	int dest = creat("target.txt", 0744);
	if(dest < 0){
		cout<<"\nError creating file...";
		exit(0);
	}
	int count;
	char buffer[512];
	
	while( count = read(source, buffer, sizeof(buffer)) )
		write(dest, buffer, count);
		
	cout<<"\nFile copied Successfully...";
		
	close(source);
	close(dest);
	
}
