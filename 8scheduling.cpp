#include <iostream>
#include <cmath>

using namespace std;

class psManagement{
	private:
		int size, timeRequired;
		struct process{
			int arrTime, burstTime, priority, id;	//basic
			int leftTime;							//advanced
			int waitTime, turnTime;					//Performance	
		} *ps;
		
	public:
		psManagement(int s){
			size = s;
			ps = new process[size];
			timeRequired = 0;
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
				timeRequired += ps[i].burstTime;
				if(ch == 1){
					cout<<"\tPriority:\t";
					cin>>ps[i].priority;	
				}
			}
		}
		
		void autoInitilizie(void){
			ps[0].id = 1;
			ps[0].arrTime = 0;
			ps[0].burstTime = 10;
			ps[0].leftTime = 10;
			
			ps[1].id = 2;
			ps[1].arrTime = 5;
			ps[1].burstTime = 6;
			ps[1].leftTime = 6;
			
			ps[2].id = 3;
			ps[2].arrTime = 9;
			ps[2].burstTime = 3;
			ps[2].leftTime = 3;
			
			timeRequired = 19;
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
		
		void rr(int timeQuanta){
			cout<<"Process execution:";
			bool completed = false;
			//for(int i = 0; !completed ; i = (i+1) % size)
			
			for(int timeElapsed = 0, i = 0; timeElapsed < timeRequired; i = (i+1) % size){
				//cout<<"\ti="<<i;
				//cout<<"\tElapsed="<<timeElapsed;
				if(ps[i].arrTime <= timeElapsed && ps[i].leftTime > 0){
					int time = 0;
					ps[i].leftTime = ps[i].leftTime - timeQuanta;	// Process executed
					
					if(ps[i].leftTime >= 0){
						time = timeQuanta;
					}
					else{
						time = abs(timeQuanta + ps[i].leftTime);
					}
					cout<<"\tP"<<ps[i].id<<"("<<time<<")";			// for time.
					timeElapsed += time;
					//i = (i+1) % size;
				}
				
				else{
					completed = true;
				}	
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
	/*psManagement ps(3);
	ps.autoInitilizie();*/
	
	cout<<"\nProcess List:";
	ps.show(0);
	
	do{
		cout<<"\n\nEnter:\t1. FCFS\t2.SJF\t3.Priority\t4.Round Robin\t5.Exit:\t";
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
				int tq;
				cout<<"\nEnter time quanta:\t";
				cin>>tq;
				ps.rr(tq);
				break;
			case 5:
				break;
		}
	}while(temp != 5);
	
		
	return 0;
}
