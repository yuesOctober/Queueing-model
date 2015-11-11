In the project I have the following source files
(1)For part1:
main1.cpp
(2)For part2:
main2A.cpp
main2B.cpp
(3)For part3
main3.cpp
part3avg.cpp
part3Qlast.cpp

How to run
first run the command :make 
 
(1)For part 1:
case1: M/M/1/inifinite, with arrival rate = 0.3; departure rate = 1, FIFO, 5000 arrivals. command:./part1 1
case2: M/M/1/inifinite, with arrival rate = 0.97; departure rate = 1, FIFO, 5000 arrivals. command:./part1 2
case3: M/M/2/5, with arrival rate = 0.7; departure rate = 1, FIFO, 10000 arrivals. command:./part1 3
(2)For part2:
main2A: (five servers, one queue)
case1: arrival rate = 0.2; departure rate = 1,dropping probability= 0. command:./part2A 1
case2: arrival rate = 0.8; departure rate = 1,dropping probability= 0. command:./part2A 2
case3: arrival rate = 0.5; departure rate = 1,dropping probability= 0. command:./part2A 3
case4: arrival rate = 0.5; departure rate = 1,dropping probability= 0.08 .command:./part2A 4
case5: arrival rate = 0.5; departure rate = 1,dropping probability= 0.4 . command:./part2A 5
main2B.cpp: (five servers, five queues, 1/5 probability go to each queue)
case1: arrival rate = 0.2; departure rate = 1,dropping probability= 0. command:./part2B 1
case2: arrival rate = 0.8; departure rate = 1,dropping probability= 0. command:./part2B 2
case3: arrival rate = 0.5; departure rate = 1,dropping probability= 0. command:./part2B 3
(3)For part3, M/G/1 queue, service time S:
f(S)=a*m^a/(1-(m/M)^a) * S^(-a-1), m<=S<=M, m=1, M=10^4, a=1.3
   a)command eg:./part3 1000000 123
   b)in order to get the relation of average service time and the number of samples ,command:./part3avg
   c)in order to get the relation of average delay in system and the number of samples , command:./part3Qlast


The output and output files in each part:
(1)For part1:
After run 
case1 command:./part1 1
we can see the output of the simulator in the window , and it also create a txt file named part1Q4.txt which is used
to verify the PK formula
case2 command:./part1 2
we can see the output of the simulator in the window 
case3 command:./part1 3
we can see the output of the simulator in the window 
(2)For part2:
part2A:
After run
case1 command:./part2A 1
we can see the output of the simulator in the window , and it also create a txt file named part2Q2case1.txt 
which is used to plot the distribution of interarrival time for case1
case2 command:./part2A 2
we can see the output of the simulator in the window , and it also create a txt file named part2Q2case2.txt 
which is used to plot the distribution of interarrival time for case2
case3 command:./part2A 3
we can see the output of the simulator in the window , and it also create a txt file named part2Q2case3.txt 
which is used to plot the distribution of interarrival time for case3
case4 command:./part2A 4
we can see the output of the simulator in the window , and it also create a txt file named part2Q2case4.txt 
which is used to plot the distribution of interarrival time for case4
case5 command:./part2A 5
we can see the output of the simulator in the window , and it also create a txt file named part2Q2case5.txt 
which is used to plot the distribution of interarrival time for case5

part2B:
After run
case1 command:./part2B 1
we can see the output of the simulator in the window
case2 command:./part2B 2
we can see the output of the simulator in the window
case3 command:./part2B 3
we can see the output of the simulator in the window
(3)For part3
After run
a)./part3 1000000 123
we can see the output of the simulator in the window
b)./part3avg

We get the relation of average service time and the number of samples (from 10^4 to 10^5 ,increment by 10),
the result is saved in a txt file named part3Q3.txt used for plotting.
(this may take long time to run ,you can direcly see one of the result in txt file)
c)./part3Qlast
We get the relation of average delay in system and the number of samples (from 10^6 to 6*10^6,increment by 500000),
the result is saved in a txt file named part3Qlast.txt used for plotting.
(this may take long time to run ,you can direcly see one of the result in txt file)


