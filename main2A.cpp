// copyright: yueshi@usc.edu
// Simulation of an M/M/N system with certain dropping rate

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
void print_stats1(ostream &stats_file1, double interarrivals )
{
 
	stats_file1 << interarrivals<<"," << endl;
}
void print_stats2(ostream &stats_file2, double interarrivals )
{
 
	stats_file2 << interarrivals<<"," << endl;
}
void print_stats3(ostream &stats_file3, double interarrivals )
{
 
	stats_file3 << interarrivals<<"," << endl;
}
void print_stats4(ostream &stats_file4, double interarrivals )
{
 
	stats_file4 << interarrivals<<"," << endl;
}
void print_stats5(ostream &stats_file5, double interarrivals )
{
 
	stats_file5 << interarrivals<<"," << endl;
}
void print_stats55(ostream &stats_file5, double avg_inter )
{
 

	stats_file5<<"the average interarrival time is :"<<avg_inter<<"          "<<endl; 
	
}
// The main function of the program that is called at the beginning.
int main(int argc, char *argv[] ) {
	//system variables
	long int tot_arrivals=50000 ,cur_arrivals = 0,customers = 0.0;
	double lambda1=0.2,lambda2=0.8,lambda3=0.5,lambda4=0.5,lambda5=0.5,mu=1;
	double event1=0.0 ,event2=INFIN, event21= INFIN, event22 = INFIN, event23 = INFIN, event24= INFIN, event25 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0;
	double avg_customers = 0.0, avg_service_time = 0.0; //used for calculating statistics
	double utilization;
	double idle_period;
	double avg_delay=0.0;
	double arrival[100000];
	double departure[5000];
	double interarrival[100000];
	double avg_inter;
	int i=0,j=0;
	double packets[21];
	long int s=0;
	for(i=0;i<21;i++)
	{
	 packets[i]=0;
	}
	int serverbusy=0;
	double external=0;
	srand48(unsigned (time(0)));
	ofstream stats_file; //file handler for saving the statistics in a file
	stats_file.open ("stats.txt"); //it creates the file, if it does not exist
	queue<double>myqueue;

	int m=atoi(argv[1]);
  if(m==1)
   {
   ofstream stats_file1; //file handler for saving the statistics in a file
	stats_file1.open ("part2Q2case1.txt"); //it creates the file, if it does not exist
   while (cur_arrivals < tot_arrivals)
	{
	 
		
		if ((event1 < event2))	//arrival
		{
			cur_arrivals++;
			if(serverbusy==1)
			{
			 avg_customers+=myqueue.size()+1;
			 for(i=0;i<21;i++)
			 {
			  if((myqueue.size()+1)==i)
			  packets[i]++;
			 }
            }
			else
			   {
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   }
			cur_time = event1;
			arrival[s]=event1;
			s++;
			myqueue.push(event1);
			event1 = cur_time + expon(lambda1);
			
			if (serverbusy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event2-myqueue.front());
			 myqueue.pop();
			 serverbusy=1;
			}
		}
		else					//departure
		{
			
			cur_time = event2;
			if(drand48()<0)
			{
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   arrival[s]=event2;
			   s++;
			   myqueue.push(event2);
			external++;
			}
			if (myqueue.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
				  myqueue.pop();
				  serverbusy=1;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure schedule
				serverbusy=0;
			}
		}
		
	}
	avg_delay/=(external+cur_arrivals-myqueue.size());	
	avg_customers /=(cur_arrivals+external); 
	
for(i=0;i<external+cur_arrivals-1;i++)
	{
	 interarrival[i]=arrival[i+1]-arrival[i];
	 avg_inter+=interarrival[i];
	}
	
	avg_inter/=(cur_arrivals+external);
	print_stats55(stats_file1,avg_inter );
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 print_stats1(stats_file1, interarrival[i]);
	}
	
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=(cur_arrivals+external);
	 cout << i<<"-" << packets[i] << endl;
	}
	stats_file1.close();
	return 0;
   }
   else if(m==2)
   {
    ofstream stats_file2; //file handler for saving the statistics in a file
	stats_file2.open ("part2Q2case2.txt"); //it creates the file, if it does not exist
   while (cur_arrivals < tot_arrivals)
	{
	 
		
		if ((event1 < event2))	//arrival
		{
			cur_arrivals++;
			if(serverbusy==1)
			{
			 avg_customers+=myqueue.size()+1;
			 for(i=0;i<21;i++)
			 {
			  if((myqueue.size()+1)==i)
			  packets[i]++;
			 }
            }
			else
			   {
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   }
			cur_time = event1;
			arrival[s]=event1;
			   s++;
			myqueue.push(event1);
			event1 = cur_time + expon(lambda2);
			
			if (serverbusy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event2-myqueue.front());
			 myqueue.pop();
			 serverbusy=1;
			}
		}
		else					//departure
		{
			
			cur_time = event2;
			if(drand48()<0)
			{
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   arrival[s]=event2;
			   s++;
			   myqueue.push(event2);
			external++;
			}
			if (myqueue.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
				  myqueue.pop();
				  serverbusy=1;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure schedule
				serverbusy=0;
			}
		}
		
	}
	avg_delay/=(external+cur_arrivals-myqueue.size());
	avg_customers /=(cur_arrivals+external); 
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 interarrival[i]=arrival[i+1]-arrival[i];
	 avg_inter+=interarrival[i];
	}
	
	avg_inter/=(cur_arrivals+external);
	print_stats55(stats_file2,avg_inter );
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 print_stats2(stats_file2, interarrival[i]);
	}
	
	
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=(cur_arrivals+external);
	 cout << i<<"-" << packets[i] << endl;
	}
	stats_file2.close();
	return 0;
   }
   else if(m==3)
   {
   ofstream stats_file3; //file handler for saving the statistics in a file
	stats_file3.open ("part2Q2case3.txt"); //it creates the file, if it does not exist
  while (cur_arrivals < tot_arrivals)
	{
	 
		
		if ((event1 < event2))	//arrival
		{
			cur_arrivals++;
			if(serverbusy==1)
			{
			 avg_customers+=myqueue.size()+1;
			 for(i=0;i<21;i++)
			 {
			  if((myqueue.size()+1)==i)
			  packets[i]++;
			 }
            }
			else
			   {
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   }
			cur_time = event1;
			arrival[s]=event1;
			   s++;
			myqueue.push(event1);
			event1 = cur_time + expon(lambda3);
			
			if (serverbusy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event2-myqueue.front());
			 myqueue.pop();
			 serverbusy=1;
			}
		}
		else					//departure
		{
			
			cur_time = event2;
			if(drand48()<0)
			{
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   arrival[s]=event2;
			   s++;
			   myqueue.push(event2);
			external++;
			}
			if (myqueue.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
				  myqueue.pop();
				  serverbusy=1;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure schedule
				serverbusy=0;
			}
		}
		
	}

	avg_delay/=(external+cur_arrivals-myqueue.size());
	avg_customers /=(cur_arrivals+external); 
for(i=0;i<external+cur_arrivals-1;i++)
	{
	 interarrival[i]=arrival[i+1]-arrival[i];
	 avg_inter+=interarrival[i];
	}
	
	avg_inter/=(cur_arrivals+external);
	print_stats55(stats_file3,avg_inter );
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 print_stats3(stats_file3, interarrival[i]);
	}
	
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=(cur_arrivals+external);
	 cout << i<<"-" << packets[i] << endl;
	}
	stats_file3.close();
	return 0;
   }
   else if(m==4)
   {
    ofstream stats_file4; //file handler for saving the statistics in a file
	stats_file4.open ("part2Q2case4.txt"); //it creates the file, if it does not exist
   while (cur_arrivals < tot_arrivals)
	{
	 
		
		if ((event1 < event2))	//arrival
		{
			cur_arrivals++;
			if(serverbusy==1)
			{
			 avg_customers+=myqueue.size()+1;
			 for(i=0;i<21;i++)
			 {
			  if((myqueue.size()+1)==i)
			  packets[i]++;
			 }
            }
			else
			   {
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   }
			cur_time = event1;
			 arrival[s]=event1;
			   s++;
			myqueue.push(event1);
			event1 = cur_time + expon(lambda4);
			
			if (serverbusy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event2-myqueue.front());
			
			 myqueue.pop();
			 serverbusy=1;
			}
		}
		else					//departure
		{
			
			cur_time = event2;
			if(drand48()<0.08)
			{

			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   arrival[s]=event2;
			   s++;
			   myqueue.push(event2);
			external++;
			}
			if (myqueue.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
				 
				  myqueue.pop();
				  serverbusy=1;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure schedule
				serverbusy=0;
			}
		}
		
	}
	avg_delay/=(external+cur_arrivals-myqueue.size());
	avg_customers /=(cur_arrivals+external); 
	
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 interarrival[i]=arrival[i+1]-arrival[i];
	 avg_inter+=interarrival[i];
	}
	
	avg_inter/=(cur_arrivals+external);
	print_stats55(stats_file4,avg_inter );
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 print_stats4(stats_file4, interarrival[i]);
	}
	
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=(cur_arrivals+external);
	 cout << i<<"-" << packets[i] << endl;
	}
	stats_file4.close();
	return 0;
   }
   else if(m==5)
   {
    ofstream stats_file5; //file handler for saving the statistics in a file
	stats_file5.open ("part2Q2case5.txt"); //it creates the file, if it does not exist
   while (cur_arrivals < tot_arrivals)
	{
	 
		
		if ((event1 < event2))	//arrival
		{
			cur_arrivals++;
			if(serverbusy==1)
			{
			 avg_customers+=myqueue.size()+1;
			 for(i=0;i<21;i++)
			 {
			  if((myqueue.size()+1)==i)
			  packets[i]++;
			 }
            }
			else
			   {
			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   }
			cur_time = event1;
			arrival[s]=event1;
			   s++;
			myqueue.push(event1);
			event1 = cur_time + expon(lambda5);
			
			if (serverbusy==0)	//if there is only 1 customer in the queue, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			 avg_delay+=(event2-myqueue.front());
			 myqueue.pop();
			 serverbusy=1;
			}
		}
		else					//departure
		{
			
			cur_time = event2;
			if(drand48()<0.4)
			{

			   avg_customers+=myqueue.size();
			   for(i=0;i<21;i++)
			 {
			  if((myqueue.size())==i)
			  packets[i]++;
			 }
			   arrival[s]=event2;
			   s++;
			   myqueue.push(event2);
			external++;
			}
			if (myqueue.size()> 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				 avg_delay+=(event2-myqueue.front());
				  myqueue.pop();
				  serverbusy=1;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure schedule
				serverbusy=0;
			}
		}
		
	}
	avg_delay/=(external+cur_arrivals-myqueue.size());
	avg_customers /=(cur_arrivals+external); 
	
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 interarrival[i]=arrival[i+1]-arrival[i];
	 avg_inter+=interarrival[i];
	}
	
	avg_inter/=(cur_arrivals+external);
	print_stats55(stats_file5,avg_inter );
	for(i=0;i<external+cur_arrivals-1;i++)
	{
	 print_stats5(stats_file5, interarrival[i]);
	}
	print_stats(avg_customers, avg_delay);
	cout<<"the distribution of the number of packets present in system: "<<endl;
	for(i=0;i<21;i++)
	{
	 packets[i]/=(cur_arrivals+external);
	 cout << i<<"-" << packets[i] << endl;
	}
	stats_file5.close();
	return 0;
   }
   

	
}

