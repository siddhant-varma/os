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
			bool executed;	
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
				ps[i].executed = false;
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
			ps[0].burstTime = 6;
			ps[0].leftTime = 6;
			ps[0].priority = 7;
			ps[0].executed = false;
			
			ps[1].id = 2;
			ps[1].arrTime = 1;
			ps[1].burstTime = 8;
			ps[1].leftTime = 8;
			ps[1].priority = 4;
			ps[1].executed = false;
			
			ps[2].id = 3;
			ps[2].arrTime = 2;
			ps[2].burstTime = 7;
			ps[2].leftTime = 7;
			ps[2].priority = 5;
			ps[2].executed = false;
			
			ps[3].id = 4;
			ps[3].arrTime = 3;
			ps[3].burstTime = 3;
			ps[3].leftTime = 3;
			ps[3].priority = 2;
			ps[3].executed = false;
			
			timeRequired = 24;
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
		
		void sjrf(void){
			int old, current = 0;	//index for executed & executing processes.
			int time,i ;
			
		    cout<<"\n\tGantt Chart\n ";
		    for(time=0;time < timeRequired ;time++)
		    {
		        old=current;
		        current=getNextProcess(time);
		        if(old != current || time == 0){
		        	cout<<"("<<time<<")[--P"<< current + 1 <<"--]";
				}
				
				ps[current].leftTime = ps[current].leftTime - 1;
		        //rt[next]=rt[next]-1;
		        if(ps[current].leftTime == 0)
		        	ps[current].executed = true;
		  			//finish[next]=1;
		  			
		        for(i = 0 ;i < size; i++)
		            if(i != current && !ps[i].executed && ps[i].arrTime <= time)
		            	ps[i].waitTime ++;
		                //wt[i]++;
		    }
		    cout<<"("<<timeRequired<<")"<<endl;
		    for(i = 0 ;i < size; i++)
		        if(!ps[i].executed){
					cout<<"Scheduling failed, cannot continue\n";
					return ;
				}
		    //dispTime();
		}
		
		int getNextProcess(int time){
			int i,low;
	        for(i = 0; i < size ; i++)
	            if( !ps[i].executed ){
	            	 low=i;
					 break;	
				}
				
	        for(i = 0;i < size; i++)
	            if( !ps[i].executed )
	            	if(ps[i].leftTime < ps[low].leftTime && ps[i].arrTime <= time)
	                //if(rt[i]<rt[low] && at[i]<=time)
	                        low=i;
	                        
	        return low;
		}
		
		void priorityPre(void){
			int old, current = 0;	//index for executed & executing processes.
			int time,i ;
			
		    cout<<"\n\tGantt Chart\n ";
		    for(time=0;time < timeRequired ;time++)
		    {
		        old=current;
		        current=getNext(time);
		        if(old != current || time == 0){
		        	cout<<"("<<time<<")[--P"<< current + 1 <<"--]";
				}
				
				ps[current].leftTime = ps[current].leftTime - 1;
		        //rt[next]=rt[next]-1;
		        if(ps[current].leftTime == 0)
		        	ps[current].executed = true;
		  			//finish[next]=1;
		  			
		        for(i = 0 ;i < size; i++)
		            if(i != current && !ps[i].executed && ps[i].arrTime <= time)
		            	ps[i].waitTime ++;
		                //wt[i]++;
		    }
		    cout<<"("<<timeRequired<<")"<<endl;
		    for(i = 0 ;i < size; i++)
		        if(!ps[i].executed){
					cout<<"Scheduling failed, cannot continue\n";
					return ;
				}
		    //dispTime();
		}
		
		int getNext(int time){
			int i,low;
	        for(i = 0; i < size ; i++)
	            if( !ps[i].executed ){
	            	 low=i;
					 break;	
				}
				
	        for(i = 0;i < size; i++)
	            if( !ps[i].executed )
	            	if(ps[i].priority < ps[low].priority && ps[i].arrTime <= time)
	                //if(rt[i]<rt[low] && at[i]<=time)
	                        low=i;
	                        
	        return low;
		}
};



int main(void){
	int temp;
	
	/*cout<<"Enter Number of processes:\t";
	cin>>temp;
	
	psManagement ps(temp);
	
	cout<<"\nFor entering priority also enter 1 else press 0...\t";
	cin>>temp;
	
	ps.intilizie(temp);*/
	psManagement ps(4);
	ps.autoInitilizie();
	
	cout<<"\nProcess List:";
	ps.show(0);
	
	do{
		cout<<"\n\nEnter:\t1. FCFS\t2.SJF\t3.Priority\t4.Round Robin\t5.SJRF\t6Priority Preemptive\t7.Exit:\t";
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
				ps.sjrf();
				break;
			case 6:
				ps.priorityPre();
				break;
			case 7:
				break;
		}
	}while(temp != 7);
	
		
	return 0;
}
