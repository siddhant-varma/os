#include <iostream>

using namespace std;

class psManagement{
	private:
		int size;
		
		struct process{
			int arrTime, burstTime, priority, id;
			
		} *ps;
		
	public:
		psManagement(int s){
			size = s;
			ps = new process[size];
		}
		
		void intilizie(int ch){
			for(int i = 0; i < size; i++){
				cout<<"\nFor Process "<<i+1<<" enter:\n\tId:\t";
				cin>>ps[i].id;
				cout<<"\tArrival Time:\t";
				cin>>ps[i].arrTime;
				cout<<"\tBurst Time:\t";
				cin>>ps[i].burstTime;
				/*cout<<"\tPriority:\t";
				cin>>ps[i].priority;*/
			}
		}
};

int main(void){
	int temp;
	
	cout<<"Enter Number of processes:\t";
	cin>>temp;
	
	psManagement ps(temp);
	ps.intilizie(temp);
	
	return 0;
}
