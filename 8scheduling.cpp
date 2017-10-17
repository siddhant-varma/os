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
					if(ps[i].burstTime > ps[j].burstTime && finished.burstTime >= ps[j].arrTime){
						hold = ps[j];
						ps[j] = ps[i];
						ps[i] = hold;
					}
				}				
			}
			show(1);
		}
		
		void priority(void){
			process hold, finished;
			cout<<"\t\t\t(1 is Highest Priority.)\n";
			for(int i = 1; i < size; i++){
				finished = ps[i - 1];
				for(int j = i+1; j < size; j++){
					if(ps[i].priority > ps[j].priority && finished.burstTime >= ps[j].arrTime){
						hold = ps[j];
						ps[j] = ps[i];
						ps[i] = hold;
					}
				}			
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
	
	cout<<"\nFor entering priority also enter 1 else press 0...\t";
	cin>>temp;
	
	ps.intilizie(temp);
	cout<<"\nProcess List:";
	ps.show(0);
	
	do{
		cout<<"\n\nEnter:\t1. FCFS\t2.SJF\t3.Priority4.Exit:\t";
		cin>>temp;
		switch(temp){
			case 1:
				ps.fcfs();
				break;
			case 2:
				ps.sjf();
				break;
			case 3:
				ps.priority();
				break;
			case 4:
				break;
		}
	}while(temp != 4);
	
		
	return 0;
}
