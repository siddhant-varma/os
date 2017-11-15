#include <iostream>
#include <cmath>

using namespace std;

class psManagement{
	private:
		int size, timeRequired;
		struct process{
			int arrTime, burstTime, priority, id;	//basic
			int leftTime;							
			int waitTime, turnTime;					//Performance
			bool executed;
		} *ps;
		
	public:
		int choice;	//	For choosing which scheduling algo will be executed
		
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
		
		//	Non Preemptive Schedule Algo	
		void nonPreSchedule(void){
			int time = 0;
			process hold, finished;
			for(int i = 1; i < size; i++){
				cout<<"("<<time<<")[--P"<< ps[i - 1].id <<"--]";
				finished = ps[i - 1];
				ps[i - 1].waitTime = time - ps[i - 1].arrTime;
				time += finished.burstTime;
				for(int j = i+1; j < size; j++){
					if( finished.burstTime >= ps[j].arrTime )
						if(ps[i].burstTime > ps[j].burstTime && choice == 2 || ps[i].priority > ps[j].priority && choice == 3){
							hold = ps[j];
							ps[j] = ps[i];
							ps[i] = hold;
						}
				}		
			}
			
			ps[size - 1].waitTime = time - ps[size - 1].arrTime;
			cout<<"("<<time<<")[--P"<< ps[size - 1].id <<"--]"<<"("<<timeRequired<<")";
		}
		
		//	Round Robin Scheduling
		void rr(int timeQuanta){
			cout<<"Process execution:";
			bool completed = false;
			
			for(int timeElapsed = 0, i = 0; timeElapsed < timeRequired; i = (i+1) % size){
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

					for(int j = 0; j < size; j++){
						if(!ps[j].executed && j != i && ps[j].arrTime <= timeElapsed)
							ps[j].waitTime = ps[j].waitTime + time ;
					}

				}
				
				else{
					completed = true;
				}	
			}
		}
		
		//Preemptive Schedule
		void preSchedule(void){
			int old, current = 0;	//index for executed & executing processes.
			int time,i ;
			
		    cout<<"\n\tGantt Chart\n ";
		    for(time=0;time < timeRequired ;time++)
		    {
		        old=current;
		        if(ps[current].executed)
		        current=getNextProcess(time);
		        //	conext switching
		        if(old != current || time == 0){	//	if current process is not old then execute and Initial process execution
		        	cout<<"("<<time<<")[--P"<< ps[current].id <<"--]";	//	time outputs leaving time of last executing process
				}
				
				ps[current].leftTime = ps[current].leftTime - 1;	// decrementing remaining execution time for executing process
		        
				if(ps[current].leftTime == 0)
		        	ps[current].executed = true;	//	Successful complition of process
		  			
		        for(i = 0 ;i < size; i++)
		            if(i != current && !ps[i].executed && ps[i].arrTime <= time)
		            	ps[i].waitTime ++;	//	incrementing waiiting time of all arrived process except executed and executing one
		    }
		    
		    cout<<"("<<timeRequired<<")"<<endl;	//	displaying total execution time or time when last process completes
		    
		    //Checks for any leftover process that has not completed execution.
		    for(i = 0 ;i < size; i++)
		        if(!ps[i].executed){
					cout<<"Scheduling failed, cannot continue\n";
					return ;
				}
		}
		
		//	Determing next process to be executed for Preemptive Scheduling
		int getNextProcess(int time){
			int i,low;
			
			//	Initially choosing the first uncomplete process irrespective of time and assigning its value to low
	        for(i = 0; i < size ; i++)
	            if( !ps[i].executed ){
	            	 low=i;
					 break;	
				}
			
			//	Determining eligble process
	        for(i = 0;i < size; i++)
	            if( !ps[i].executed ) 	//	checking if the process has completed execution or not
	            	if(ps[i].arrTime <= time)	//	Checking the process has arrived or not at the given time
	            		switch(choice){
	            			case 1:
	            				if(ps[i].arrTime < ps[low].arrTime)	//	choosing process with least remaining execution time
		                        	low=i;	//	fcfs
	            				break;
	            			case 5:
	            				if(ps[i].leftTime < ps[low].leftTime)	//	choosing process with least remaining execution time
		                        	low=i;	//	sjrf
		                        break;
		                    case 6:
		                    	if(ps[i].priority < ps[low].priority)
		                    		low = i;	//	preemptive priority
		                    	break;
						}
						    
	        return low;
		}
	
		//	Calculating Average Waiting and Turnaround time
		void performance(void){
			float totalWait = 0, totalTurnAround = 0;
			for(int i = 0; i < size; i++){
				//cout<<"\t"<<ps[i].waitTime;
				totalWait += ps[i].waitTime;
				
				ps[i].turnTime = ps[i].waitTime + ps[i].arrTime;
				totalTurnAround += ps[i].turnTime;
			}
			cout<<"\nAverage Waiting Time:\t"<<(totalWait / size);
			cout<<"\nAverage Turn Around Time:\t"<<(totalTurnAround / size);
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

	cout<<"\n\nEnter:\t1. FCFS\t2.SJF\t3.Priority\t4.Round Robin\t5.SJRF\t6.Priority Preemptive\t7.Exit:\t";
	cin>>temp;
	cout<<"\nProcess Execution:\t";
	
	ps.choice = temp;
	switch(temp){
		case 1:
			ps.preSchedule();
			break;
		case 2:
			ps.nonPreSchedule();
			break;
		case 3:
			ps.nonPreSchedule();
			break;
		case 4:
			int tq;
			cout<<"\nEnter time quanta:\t";
			cin>>tq;
			ps.rr(tq);
			break;
		case 5:
			ps.preSchedule();
			break;
		case 6:
			ps.preSchedule();
			break;
		case 7:
			break;
	}
	
	ps.performance();
	
	return 0;
}
