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
void print_stats(double avg_customers, double avg_delay , double idle_period,double avg_service_time,double waiting_time,double blocking_ratio)
{
    cout << "The mean number of packets in system: " << avg_customers << endl;
	cout << "Average delay per customer: " << avg_delay << endl;
	cout << "Average Service Time: " << avg_service_time << endl;
	cout << "Average Waiting Time: " << waiting_time << endl;
	cout << "Idle period of server: " << idle_period << endl;
	cout << "Blocking ratio : " <<blocking_ratio << endl;

}

// The main function of the program that is called at the beginning.
int main(int argc, char *argv[] ) {
	//system variables
	long int cur_arrivals = 0;
	double lambda=0.1;
	double event1 = 0.0, event2 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0;
	double avg_customers = 0.0, avg_service_time = 0.0; //used for calculating statistics
	double utilization;
	double idle_period;
	double avg_delay=0.0;
	double arrival[5000];
	double departure[5000];
	int i=0,j=0;
	double blocking_ratio=0.0;
	double waiting_time;
	long int tot_arrivals=atol(argv[1]);
    srand48(atoi(argv[2]));
	queue<double>myqueue;
	
	// discrete event simulator 
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
    waiting_time=(avg_delay-avg_service_time)/(cur_arrivals-myqueue.size());
	avg_delay/=(cur_arrivals-myqueue.size());
    idle_period=(cur_time-avg_service_time)/cur_time;
	utilization	=1-idle_period;
	avg_customers /=cur_arrivals; 
	avg_service_time /=(cur_arrivals-myqueue.size());
	print_stats(avg_customers, avg_delay,idle_period,avg_service_time,waiting_time,blocking_ratio);
	return 0;
	
	
}

