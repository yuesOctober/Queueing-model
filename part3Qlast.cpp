// EE 465, USC
// Simulation of an M/M/1 system

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
void print_stats(ostream &stats_file,int tot_arrivals ,double avg_delay)
{
	stats_file <<tot_arrivals <<" "<<avg_delay<< ",  "<<endl;
}

// The main function of the program that is called at the beginning.
int main() {
	ofstream stats_file; //file handler for saving the statistics in a file
	
    
	stats_file.open ("part3Qlast.txt"); //it creates the file, if it does not exist
	
	for(long int tot_arrivals=1000000;tot_arrivals<=6000000;)
	{
	//long int tot_arrivals1=5000,tot_arrivals2=5000,tot_arrivals3=5000, 
	long int cur_arrivals = 0;
	double lambda=0.1;
	double event1 = 0.0, event2 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0;
	double avg_customers = 0.0, avg_service_time = 0.0; //used for calculating statistics
	double avg_delay=0.0;
	int i=0,j=0;
	queue<double>myqueue;
	srand48(3000);
	while (cur_arrivals < tot_arrivals)
	{
		if (event1 < event2)	//arrival
		{
			cur_arrivals++;
			avg_customers+=myqueue.size();
            myqueue.push(event1);
			cur_time = event1;
			event1 = cur_time + expon(lambda);
			
			if (myqueue.size() == 1)	//if there is only 1 customer, he/she goes directly to service
			{
				service_time = fs();
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
				service_time = fs();
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure scheduled
			}
		}
	}
	avg_service_time /=(cur_arrivals-myqueue.size());
	avg_delay/=(cur_arrivals-myqueue.size());
	print_stats(stats_file, tot_arrivals,avg_delay);
	tot_arrivals+=500000;
	}
	stats_file.close();
	return 0;
	
	
}

