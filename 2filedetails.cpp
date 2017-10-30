//4. WRITE A PROGRAM to print file details including owner access permissions, file access
// time, where file name is given as argument.

#include <iostream>	//cout
#include <cstdlib>	//exit()
#include <sys/stat.h> 	//stat s

using namespace std;

int main(int argc, char* argv[]){
	if(argc < 2){
		cout<<"\nFile name not specified.\n";
		exit(0);
	}
	
	struct stat s;
	if(stat(argv[1], &s) < 0){
		cout<<"\nError obtaining file stats...\n";
		exit(0);
	}
	else{
		cout<<"\nFile\t\t\t:\t"<<argv[1];
		cout<<"\nOwner ID {UID}\t\t:\t"<<s.st_uid;
		cout<<"\nGroup ID {GID}\t\t:\t"<<s.st_gid;
		cout<<"\nAccess Permissions\t:\t"<<s.st_mode;
		cout<<"\nAccess Time\t\t:\t"<<s.st_atime;
		cout<<"\nFile Size\t\t:\t"<<s.st_size;
		cout<<"\nFile Size {In blocks}\t:\t"<<s.st_blksize;
		cout<<endl;
	}
	
	
	return 0;
}
