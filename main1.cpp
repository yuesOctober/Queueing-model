// EE 465, USC
// Simulation of an M/M/1 system

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include<queue>
#include<time.h>

using namespace std;

#define INFIN  			999999999

// Function Name:	expon
// Description: 	Generates an exponentially distributed random number 
//					with parameter \lambda. 
// Input: 			lambda (double)
// Output: 			An exponentially distributed random number (double)
//
double expon(double lambda)
{
	double u; // used to store a random number. 
	
	do
	{
		u = drand48(); //uniform number in the interval [0.0, 1.0]
	}
	while ((u == 0) || (u == 1)); //special cases that we want to avoid
	
	return -log(1-u)/lambda;
	
}

// Function Name:	print_stats
// Description: 	Saves and prints system statistics 
// Input:           stats_file (ostream object): ostream object for the stats file
//					avg_customers (double): average customers in the system
//					avg_service_time (double): average service time 
// Output: 			void (output stored to file and printed in the screen)
//
void print_stats(double utilization , double avg_customers, double avg_delay , double idle_period,double blocked_ratio)
{
    cout << "Utilization: " << utilization << endl;
	cout << "Average number of packets in the system: " << avg_customers << endl;
	cout << "Average delay in system: " << avg_delay << endl;
	cout << "Blocked ratio is: " << blocked_ratio << endl;
	cout << "Idle period of server: " << idle_period << endl;
	
}
void print_stats1(ostream &stats_file,double avg_service_time,double second_avg_time ,double waiting_theoretical,double waiting_simulated )
{
    stats_file<< "Average Service Time: " << avg_service_time << endl;
	stats_file << "Second moment average service time is: " <<second_avg_time << endl;
	stats_file  << "Theoretical waiting time using PK with simulated average service time and average second moment service time: " << waiting_theoretical << endl;
	stats_file << "Somulated waiting time: " << waiting_simulated << endl;
	
	
}

// The main function of the program that is called at the beginning.
int main(int argc, char *argv[]) {
	//system variables
	long int tot_arrivals1=5000,tot_arrivals2=5000,tot_arrivals3=10000;
    double	cur_arrivals=0,cur_arrivals1 = 0,cur_arrivals2 = 0,customers = 0.0;
	double lambda1=0.3,lambda2=0.97,lambda3=0.7, mu=1;
	double event=0.0,event1 = 0.0, event2 = INFIN,event3=INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time1,service_time2 ,service_time,cur_time=0.0;
	double avg_customers = 0.0, avg_service_time=0.0,second_avg_time=0.0; //used for calculating statistics
	double utilization;
	double idle_period;
	double avg_delay=0.0;
	double arrival[10000];
	double departure[10000];
	double idle_time[10000];
	double tot_idle=0;
	int server1busy=0;
	int server2busy=0;
	int serverbusy=0;
	double blocked_packets=0;
	double simulated_packets=0;
	int i=0,j=0,s=0,n=0;
	double blocked_ratio;
	double packet0=0;
	double waiting_simulated;
	double waiting_theoretical;
	int avg_customers1;
	ofstream stats_file; //file handler for saving the statistics in a file
   queue<double>myqueue;
srand48(unsigned (time(0)));
	int m=atoi(argv[1]);

    if (m==1)
	{		
	stats_file.open ("part1Q4.txt"); //it creates the file, if it does not exist
	blocked_ratio=0;
	
	// discrete event simulator 
	while (cur_arrivals < tot_arrivals1)
	{
		if (event1 < event2)	//arrival
		{
			cur_arrivals++;
			avg_customers+=myqueue.size();
            myqueue.push(event1);
			cur_time = event1;
			event1 = cur_time + expon(lambda1);
			
			if (myqueue.size()== 1)	//if there is only 1 customer, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			    second_avg_time+=(service_time*service_time);
			}
		}
		else					//departure
		{
			cur_time = event2;
			avg_delay=avg_delay+event2-myqueue.front();
			myqueue.pop();
			if (myqueue.size() > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				second_avg_time+=(service_time*service_time);
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure scheduled
			}
		}
	}
	waiting_simulated=(avg_delay-avg_service_time)/(cur_arrivals-myqueue.size());
	avg_delay/=(cur_arrivals-myqueue.size());	
    idle_period=(cur_time-avg_service_time)/cur_time;
	utilization	=1-idle_period;
	avg_customers /=cur_arrivals; 
	avg_service_time /=(cur_arrivals-customers);
	second_avg_time /=(cur_arrivals-customers);
	waiting_theoretical=lambda1*(second_avg_time)/2/(1-lambda1*avg_service_time);
	print_stats( utilization,avg_customers, avg_delay,idle_period,blocked_ratio);
	print_stats1(stats_file,avg_service_time,second_avg_time ,waiting_theoretical,waiting_simulated);
	stats_file.close();
	return 0;
	}
	 if (m==2)
	{		
	
	blocked_ratio=0;
	
	// discrete event simulator 
	while (cur_arrivals < tot_arrivals2)
	{
		if (event1 < event2)	//arrival
		{
			cur_arrivals++;
			avg_customers+=myqueue.size();
            myqueue.push(event1);
			cur_time = event1;
			event1 = cur_time + expon(lambda2);
			
			if (myqueue.size()== 1)	//if there is only 1 customer, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			
			}
		}
		else					//departure
		{
			cur_time = event2;
			avg_delay=avg_delay+event2-myqueue.front();
			myqueue.pop();
			if (myqueue.size() > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure scheduled
			}
		}
	}
	avg_delay/=(cur_arrivals-myqueue.size());
    idle_period=(cur_time-avg_service_time)/cur_time;
	utilization	=1-idle_period;
	avg_customers /=cur_arrivals; 
	avg_service_time /=(cur_arrivals-myqueue.size());
	print_stats( utilization,avg_customers, avg_delay,idle_period,blocked_ratio);
	return 0;
	}
	if(m==3)
	{
	while (cur_arrivals < tot_arrivals3)
	{
		if(event2<=event3)
		{
		event=event2;
		}
		else
		{
		 event=event3;
		}
		if ((event1 < event))	//arrival
		{
			cur_arrivals++;
			
			if(server1busy==1&&server2busy==1)
			 {
			avg_customers1=myqueue.size()+2;
			
             }
			else if(server1busy==0&&server2busy==0)
			  {
			   avg_customers1=myqueue.size();
			  }
			 else
			  {
			   avg_customers1=myqueue.size()+1;
			  }
			  if(avg_customers1==0)
			  {
			  packet0++;
			  }
			if(avg_customers1<5)
			{
			   simulated_packets++;
			if(server1busy==1&&server2busy==1)
			{
			avg_customers+=myqueue.size()+2;
               }
			   else if(server1busy==0&&server2busy==0)
			   {
			   avg_customers+=myqueue.size();
			   }
			   else
			    {
			   avg_customers+=myqueue.size()+1;
			   }		  
			cur_time = event1;
			 myqueue.push(event1);
			 event1 = cur_time + expon(lambda3);
				 if (server1busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			 {
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
			 myqueue.pop();
			 server1busy=1;
			
			 }
			 else if(server2busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			 {
				service_time = expon(mu);
				event3 = cur_time + service_time;
				avg_service_time += service_time;
				server2busy=1;
				 avg_delay+=(event3-myqueue.front());
			 myqueue.pop();
		
				//customer2++;
			
			 }
			}
             else
             {
			  blocked_packets++;
			  cur_time = event1;
			 event1 = cur_time + expon(lambda1);
			  
			 }			 
		}		
		else					//departure
		{
		 if(event2<event3)
		 {
		   
			cur_time=event2;
			if (myqueue.size()>= 1) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
				 departure[i]=event2;
				i++;
			   myqueue.pop();
			   server1busy=1;
				
			}
			else 				//the departure left the queue empty
			{
				server1busy=0;
				event2 = INFIN; //no departure scheduled
			}
		  }
		  else
		  {
		   
			cur_time = event3;
		    
		
			if (myqueue.size()>= 1) 
			{
			   
				service_time = expon(mu);
				event3 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event3-myqueue.front());
				 departure[i]=event3;
				i++;
			 myqueue.pop();
			 server2busy=1;
			}
			else 				//the departure left the queue empty
			{
	             server2busy=0;
				event3 = INFIN; //no departure scheduled
			}
		  }
		}  
		
	}

	
	blocked_ratio=blocked_packets/cur_arrivals;
	avg_delay/=(simulated_packets);
    idle_period=(packet0)/(cur_arrivals-blocked_packets);
	utilization	=1-idle_period;
	avg_customers /=(cur_arrivals-blocked_packets); 
	avg_service_time /=(simulated_packets);
	print_stats(utilization,avg_customers, avg_delay,idle_period,blocked_ratio);
	stats_file.close();
	return 0;
	}
}

