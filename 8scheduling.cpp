#include <iostream>

using namespace std;

class psManagement{
	private:
		int size, timeElapsed;
		struct process{
			int arrTime, burstTime, priority, id;	//basic
			int leftTime;							//advanced
			int waitTime, turnTime;					//Performance	
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
				ps[i].leftTime = ps[i].burstTime;
				if(ch == 1){
					cout<<"\tPriority:\t";
					cin>>ps[i].priority;	
				}
			}
		}
		
		void fcfs(void){
			bool switched = true;
			process hold;
			for(int i = 0; i < size - 1 && switched; i++){
				switched = false;
				for(int j = 0; j < size - i - 1; j++){
					if(ps[j].arrTime > ps[j+1].arrTime){
						switched = true;
						hold = ps[j+1];
						ps[j+1] = ps[j];
						ps[j] = hold;
					}
				}
			}
			show(1);
		}
		
		void sjf(void){
			process hold, finished;
			for(int i = 1; i < size; i++){
				finished = ps[i - 1];
				for(int j = i+1; j < size; j++){
					//cout<<"\n\t\t\ti="<<i<<"\tj="<<j;
					if(ps[i].burstTime > ps[j].burstTime && finished.burstTime >= ps[j].arrTime){
						//cout<<"\tP"<<i+1<<"\tP"<<j+1;
						hold = ps[j];
						ps[j] = ps[i];
						ps[i] = hold;
					}
				}
				//show(1);				
			}
			show(1);
		}
		
		void show(int a){
			if(a > 0)
				cout<<"Processes execution sequence:";
			for(int i = 0; i < size; i++){
				cout<<"\tP"<<ps[i].id;
			}
		}
};

int main(void){
	int temp;
	
	cout<<"Enter Number of processes:\t";
	cin>>temp;
	
	psManagement ps(temp);
	ps.intilizie(0);
	cout<<"\nProcess List:";
	ps.show(0);
	
	do{
		cout<<"\n\nEnter:\t1. FCFS\t2.SJF\t3.Exit:\t";
		cin>>temp;
		switch(temp){
			case 1:
				ps.fcfs();
				break;
			case 2:
				ps.sjf();
				break;
			case 3:
				break;
		}
	}while(temp != 3);
	
		
	return 0;
}
