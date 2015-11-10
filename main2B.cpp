// EE 465, USC
// Simulation of an M/G/1 system

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include<queue>
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
double fs()
{
	double u; // used to store a random number. 
	
	do
	{
		u = drand48(); //uniform number in the interval [0.0, 1.0]
	}
	while ((u == 0) || (u == 1) || ((pow((1/(1-u*(1-pow(0.0001,1.3)))),(1/1.3)))<1)  || ((pow((1/(1-u*(1-pow(0.0001,1.3)))),(1/1.3)))>10000) ); //special cases that we want to avoid
	
	return pow((1/(1-u*(1-pow(0.0001,1.3)))),(1/1.3));
	
}
// Function Name:	print_stats
// Description: 	Saves and prints system statistics 
// Input:           stats_file (ostream object): ostream object for the stats file
//					avg_customers (double): average customers in the system
//					avg_service_time (double): average service time 
// Output: 			void (output stored to file and printed in the screen)
//
void print_stats( double avg_customers, double avg_delay )
{
	cout << "Average number of packets in system: " << avg_customers << endl;
	cout << "Average delay in system: " << avg_delay << endl;
}
double minimum(double event21,double event22, double event23,double event24 ,double event25)
{
 double event[5];
 double events;
 event[0]=event21;
 event[1]=event22;
 event[2]=event23;
 event[3]=event24;
 event[4]=event25;
 events=event[0];
 int i1;
 for(i1=0;i1<5;i1++)
 {
  
   if(events>=event[i1])
   {
    events=event[i1];
   }
 } 
  return events;
}


// The main function of the program that is called at the beginning.
int main(int argc, char *argv[] ) {
	//system variables
	long int tot_arrivals=50000;
	double lambda1=1,lambda2=4,lambda3=2.5,mu=1;
	double event1 = 0.0, event2=INFIN,event21= INFIN, event22 = INFIN, event23 = INFIN, event24= INFIN, event25 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0;
	double avg_customers = 0.0,avg_service_time = 0.0; //used for calculating statistics
	double utilization;
	double idle_period;
	double avg_delay=0.0;
	double r=0;
	long int cur_arrivals = 0,customers = 0.0;
	int i=0,j=0,s=0;
	int select=atoi(argv[1]);
	srand48(unsigned(time(0)));
	ofstream stats_file; //file handler for saving the statistics in a file
    int server1busy=0;
     int server2busy=0;
	 int server3busy=0;
     int server4busy=0;
	 int server5busy=0;
double packets[21];
double m0,m1,m2,m3,m4,m5;
	for(i=0;i<21;i++)
	{
	 packets[i]=0;
	}
	int serverbusy=0;
	stats_file.open ("stats.txt"); //it creates the file, if it does not exist
	queue<double>myqueue1;
	queue<double>myqueue2;
	queue<double>myqueue3;
	queue<double>myqueue4;
	queue<double>myqueue5;
	// discrete event simulator 
	if(select==1)
	{
	while (cur_arrivals < tot_arrivals)
	{
	 
		event2=minimum(event21,event22,event23,event24,event25);
		if (event1<event2)	//arrival
		{
			 r=drand48();
			cur_arrivals++;
       
			  if(server1busy==1)
		  {
		  avg_customers+=myqueue1.size()+1;
		  m1=myqueue1.size()+1;
          }
	       else
	       {
		   avg_customers+=myqueue1.size();
		    m1=myqueue1.size();
	       }
		 if(server2busy==1)
		  {
		  avg_customers+=myqueue2.size()+1;
		  m2=myqueue2.size()+1;
          }
	       else
	       {
		   avg_customers+=myqueue2.size();
		    m2=myqueue2.size();
	       }
		if(server3busy==1)
		  {
		   avg_customers+=myqueue3.size()+1;
		   m3=myqueue3.size()+1;
		   
           }
		  else
		  {
			avg_customers+=myqueue3.size();
			 m3=myqueue3.size();
		  }   
		if(server4busy==1)
		  {
		   avg_customers+=myqueue4.size()+1;
		   m4=myqueue4.size()+1;
           }
		  else
		  {
			avg_customers+=myqueue4.size();
			 m4=myqueue4.size();
		  }  
		if(server5busy==1)
		  {
		   avg_customers+=myqueue5.size()+1;
		   m5=myqueue5.size()+1;
           }
		  else
		  {
			avg_customers+=myqueue5.size();
			 m5=myqueue5.size();
		  } 
		  m0=m1+m2+m3+m4+m5;
		    for(i=0;i<21;i++)
		  {
		  if((m1+m2+m3+m4+m5)==i)
		  {
		   packets[i]++;
		  }
		  }
		 cur_time = event1; 
		 event1 = cur_time + expon(lambda1);
		  if((r>=0)&&(r<0.2))
		   {
            
		
			myqueue1.push(cur_time);
			
			
			if (server1busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
			 service_time = expon(mu);
			 event21 = cur_time + service_time;
			 avg_service_time += service_time;
			 avg_delay+=(event21-myqueue1.front());
			 myqueue1.pop();
			 server1busy=1;
			}
		  }
          else if(r<0.4)
          {
			myqueue2.push(cur_time);
			if (server2busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event22 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event22-myqueue2.front());
			 myqueue2.pop();
			 server2busy=1;
			}
		  }
          else if(r<0.6)	
          {
			myqueue3.push(cur_time);
			if (server3busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event23 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event23-myqueue3.front());
			 myqueue3.pop();
			 server3busy=1;
			}
		  }
          else if(r<0.8)	
          {
			myqueue4.push(cur_time);
			if (server4busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event24 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event24-myqueue4.front());
			 myqueue4.pop();
			 server4busy=1;
			}
		  }
		   else 	
          {
			myqueue5.push(cur_time);
			if (server5busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event25 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event25-myqueue5.front());
			 myqueue5.pop();
			 server5busy=1;
			}
		  }
		  
		}
		 else					//departure
		 {
			if(event2==event21)
			{
			cur_time = event21;
			if (myqueue1.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event21 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event21-myqueue1.front());
				  myqueue1.pop();
				  server1busy=1;
			}
			else 				//the departure left the queue empty
			{
				event21 = INFIN; //no departure schedule
				server1busy=0;
			}
		   }
          else if(event2==event22)
			{
			cur_time = event22;
			if (myqueue2.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event22 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event22-myqueue2.front());
				  myqueue2.pop();
				  server2busy=1;
			}
			else 				//the departure left the queue empty
			{
				event22 = INFIN; //no departure schedule
				server2busy=0;
			}
		   }
		   else if(event2==event23)
			{
			cur_time = event23;
			if (myqueue3.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event23 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event23-myqueue3.front());
				  myqueue3.pop();
				  server3busy=1;
			}
			else 				//the departure left the queue empty
			{
				event23= INFIN; //no departure schedule
				server3busy=0;
			}
			}
		   else if(event2==event24)
			{
			cur_time = event24;
			if (myqueue4.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event24 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event24-myqueue4.front());
				  myqueue4.pop();
				  server4busy=1;
			}
			else 				//the departure left the queue empty
			{
				event24 = INFIN; //no departure schedule
				server4busy=0;
			}
		   }
		   else if(event2==event25)
			{
			cur_time = event25;
			if (myqueue5.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event25 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event25-myqueue5.front());
				  myqueue5.pop();
				  server5busy=1;
			}
			else 				//the departure left the queue empty
			{
				event25 = INFIN; //no departure schedule
				server5busy=0;
			}
		   }
		   
		 }
	}
	avg_delay/=(cur_arrivals-myqueue1.size()-myqueue2.size()-myqueue3.size()-myqueue4.size()-myqueue5.size());
	avg_customers/=cur_arrivals; 
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=cur_arrivals;
	 cout<<i<<"-"<<packets[i]<<endl;
	}
	return 0;
	}
	else if(select==2)
	{
	while (cur_arrivals < tot_arrivals)
	{
	 
		event2=minimum(event21,event22,event23,event24,event25);
		if (event1<event2)	//arrival
		{
			 r=drand48();
			cur_arrivals++;
       
			  if(server1busy==1)
		  {
		  avg_customers+=myqueue1.size()+1;
		  m1=myqueue1.size()+1;
          }
	       else
	       {
		   avg_customers+=myqueue1.size();
		    m1=myqueue1.size();
	       }
		 if(server2busy==1)
		  {
		  avg_customers+=myqueue2.size()+1;
		  m2=myqueue2.size()+1;
          }
	       else
	       {
		   avg_customers+=myqueue2.size();
		    m2=myqueue2.size();
	       }
		if(server3busy==1)
		  {
		   avg_customers+=myqueue3.size()+1;
		   m3=myqueue3.size()+1;
		   
           }
		  else
		  {
			avg_customers+=myqueue3.size();
			 m3=myqueue3.size();
		  }   
		if(server4busy==1)
		  {
		   avg_customers+=myqueue4.size()+1;
		   m4=myqueue4.size()+1;
           }
		  else
		  {
			avg_customers+=myqueue4.size();
			 m4=myqueue4.size();
		  }  
		if(server5busy==1)
		  {
		   avg_customers+=myqueue5.size()+1;
		   m5=myqueue5.size()+1;
           }
		  else
		  {
			avg_customers+=myqueue5.size();
			 m5=myqueue5.size();
		  } 
		  m0=m1+m2+m3+m4+m5;
		    for(i=0;i<21;i++)
		  {
		  if((m1+m2+m3+m4+m5)==i)
		  {
		   packets[i]++;
		  }
		  }
		 cur_time = event1; 
		 event1 = cur_time + expon(lambda2);
		  if((r>=0)&&(r<0.2))
		   {
            
		
			myqueue1.push(cur_time);
			
			
			if (server1busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
			 service_time = expon(mu);
			 event21 = cur_time + service_time;
			 avg_service_time += service_time;
			 avg_delay+=(event21-myqueue1.front());
			 myqueue1.pop();
			 server1busy=1;
			}
		  }
          else if(r<0.4)
          {
			myqueue2.push(cur_time);
			if (server2busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event22 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event22-myqueue2.front());
			 myqueue2.pop();
			 server2busy=1;
			}
		  }
          else if(r<0.6)	
          {
			myqueue3.push(cur_time);
			if (server3busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event23 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event23-myqueue3.front());
			 myqueue3.pop();
			 server3busy=1;
			}
		  }
          else if(r<0.8)	
          {
			myqueue4.push(cur_time);
			if (server4busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event24 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event24-myqueue4.front());
			 myqueue4.pop();
			 server4busy=1;
			}
		  }
		   else 	
          {
			myqueue5.push(cur_time);
			if (server5busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event25 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event25-myqueue5.front());
			 myqueue5.pop();
			 server5busy=1;
			}
		  }
		  
		}
		 else					//departure
		 {
			if(event2==event21)
			{
			cur_time = event21;
			if (myqueue1.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event21 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event21-myqueue1.front());
				  myqueue1.pop();
				  server1busy=1;
			}
			else 				//the departure left the queue empty
			{
				event21 = INFIN; //no departure schedule
				server1busy=0;
			}
		   }
          else if(event2==event22)
			{
			cur_time = event22;
			if (myqueue2.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event22 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event22-myqueue2.front());
				  myqueue2.pop();
				  server2busy=1;
			}
			else 				//the departure left the queue empty
			{
				event22 = INFIN; //no departure schedule
				server2busy=0;
			}
		   }
		   else if(event2==event23)
			{
			cur_time = event23;
			if (myqueue3.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event23 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event23-myqueue3.front());
				  myqueue3.pop();
				  server3busy=1;
			}
			else 				//the departure left the queue empty
			{
				event23= INFIN; //no departure schedule
				server3busy=0;
			}
			}
		   else if(event2==event24)
			{
			cur_time = event24;
			if (myqueue4.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event24 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event24-myqueue4.front());
				  myqueue4.pop();
				  server4busy=1;
			}
			else 				//the departure left the queue empty
			{
				event24 = INFIN; //no departure schedule
				server4busy=0;
			}
		   }
		   else if(event2==event25)
			{
			cur_time = event25;
			if (myqueue5.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event25 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event25-myqueue5.front());
				  myqueue5.pop();
				  server5busy=1;
			}
			else 				//the departure left the queue empty
			{
				event25 = INFIN; //no departure schedule
				server5busy=0;
			}
		   }
		   
		 }
	}
	avg_delay/=(cur_arrivals-myqueue1.size()-myqueue2.size()-myqueue3.size()-myqueue4.size()-myqueue5.size());
	avg_customers/=cur_arrivals; 
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=cur_arrivals;
	 cout<<i<<"-"<<packets[i]<<endl;
	}
	return 0;
	}
	else if(select==3)
	{
	while (cur_arrivals < tot_arrivals)
	{
	 
		event2=minimum(event21,event22,event23,event24,event25);
		if (event1<event2)	//arrival
		{
			 r=drand48();
			cur_arrivals++;
       
			  if(server1busy==1)
		  {
		  avg_customers+=myqueue1.size()+1;
		  m1=myqueue1.size()+1;
          }
	       else
	       {
		   avg_customers+=myqueue1.size();
		    m1=myqueue1.size();
	       }
		 if(server2busy==1)
		  {
		  avg_customers+=myqueue2.size()+1;
		  m2=myqueue2.size()+1;
          }
	       else
	       {
		   avg_customers+=myqueue2.size();
		    m2=myqueue2.size();
	       }
		if(server3busy==1)
		  {
		   avg_customers+=myqueue3.size()+1;
		   m3=myqueue3.size()+1;
		   
           }
		  else
		  {
			avg_customers+=myqueue3.size();
			 m3=myqueue3.size();
		  }   
		if(server4busy==1)
		  {
		   avg_customers+=myqueue4.size()+1;
		   m4=myqueue4.size()+1;
           }
		  else
		  {
			avg_customers+=myqueue4.size();
			 m4=myqueue4.size();
		  }  
		if(server5busy==1)
		  {
		   avg_customers+=myqueue5.size()+1;
		   m5=myqueue5.size()+1;
           }
		  else
		  {
			avg_customers+=myqueue5.size();
			 m5=myqueue5.size();
		  } 
		  m0=m1+m2+m3+m4+m5;
		    for(i=0;i<21;i++)
		  {
		  if((m1+m2+m3+m4+m5)==i)
		  {
		   packets[i]++;
		  }
		  }
		 cur_time = event1; 
		 event1 = cur_time + expon(lambda3);
		  if((r>=0)&&(r<0.2))
		   {
            
		
			myqueue1.push(cur_time);
			
			
			if (server1busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
			 service_time = expon(mu);
			 event21 = cur_time + service_time;
			 avg_service_time += service_time;
			 avg_delay+=(event21-myqueue1.front());
			 myqueue1.pop();
			 server1busy=1;
			}
		  }
          else if(r<0.4)
          {
			myqueue2.push(cur_time);
			if (server2busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event22 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event22-myqueue2.front());
			 myqueue2.pop();
			 server2busy=1;
			}
		  }
          else if(r<0.6)	
          {
			myqueue3.push(cur_time);		
			if (server3busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event23 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event23-myqueue3.front());
			 myqueue3.pop();
			 server3busy=1;
			}
		  }
          else if(r<0.8)	
          {
			myqueue4.push(cur_time);		
			if (server4busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event24 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event24-myqueue4.front());
			 myqueue4.pop();
			 server4busy=1;
			}
		  }
		   else 	
          {
			myqueue5.push(cur_time);
			if (server5busy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event25 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event25-myqueue5.front());
			 myqueue5.pop();
			 server5busy=1;
			}
		  }
		  
		}
		 else					//departure
		 {
			if(event2==event21)
			{
			cur_time = event21;
			if (myqueue1.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event21 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event21-myqueue1.front());
				  myqueue1.pop();
				  server1busy=1;
			}
			else 				//the departure left the queue empty
			{
				event21 = INFIN; //no departure schedule
				server1busy=0;
			}
		   }
          else if(event2==event22)
			{
			cur_time = event22;
			if (myqueue2.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event22 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event22-myqueue2.front());
				  myqueue2.pop();
				  server2busy=1;
			}
			else 				//the departure left the queue empty
			{
				event22 = INFIN; //no departure schedule
				server2busy=0;
			}
		   }
		   else if(event2==event23)
			{
			cur_time = event23;
			if (myqueue3.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event23 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event23-myqueue3.front());
				  myqueue3.pop();
				  server3busy=1;
			}
			else 				//the departure left the queue empty
			{
				event23= INFIN; //no departure schedule
				server3busy=0;
			}
			}
		   else if(event2==event24)
			{
			cur_time = event24;
			if (myqueue4.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event24 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event24-myqueue4.front());
				  myqueue4.pop();
				  server4busy=1;
			}
			else 				//the departure left the queue empty
			{
				event24 = INFIN; //no departure schedule
				server4busy=0;
			}
		   }
		   else if(event2==event25)
			{
			cur_time = event25;
			if (myqueue5.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event25 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event25-myqueue5.front());
				  myqueue5.pop();
				  server5busy=1;
			}
			else 				//the departure left the queue empty
			{
				event25 = INFIN; //no departure schedule
				server5busy=0;
			}
		   }
		   
		 }
	}
	avg_delay/=(cur_arrivals-myqueue1.size()-myqueue2.size()-myqueue3.size()-myqueue4.size()-myqueue5.size());
	avg_customers/=cur_arrivals; 
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=cur_arrivals;
	 cout<<i<<"-"<<packets[i]<<endl;
	}
	return 0;
	}
	
}

