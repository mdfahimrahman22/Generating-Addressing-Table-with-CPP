# Generating Addressing Table with CPP
#### Software Tools -
-  [MinGW C++](https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html "Link")
- [Codeblocks](https://www.codeblocks.org/downloads/binaries/ "Codeblocks")

#### Compiler used -
- C++14 ISO C++ language standard

### How to run?
- There is a file called input.txt, update it with your corresponding LAN topology connection.
- Execute the exe file or run the cpp file using Codeblocks IDE. 
- The output will be saved in the output.txt file. 
- The tutorial[[Link](https://youtu.be/e63vZB7RHGE "Link")] is availabe for better understanding. 

#### Input -
The first input line contains a single integer n  — the number of connections in the network. Then n lines contain 2 string or 2 string & 1 integer each, each integer denotes number of host. The last line indicates starting address. PC connection name must have 'PC' substring. Router - PC connection input can be in any order, like R0 PC1 or PC1 R0.
See this tutorial - [Generating Addressing Table and Router Configuration Commands](https://youtu.be/e63vZB7RHGE "Generating Addressing Table and Router Configuration Commands") for better understanding.
#### Output -
Pring the addressing table and router configuration commands.

#### Example:
Test case 1:
```bash
5
R0 PC1 40
R0 R1
R0 R2
R1 PC0 80
R2 PC2 20
192.168.1.0/24

```
Note: 
Here 5 is the number of connections. There following 5 lines contains connections. For example, router R0 is connected with PC1 and the network will have 40 hosts. 

#### Considerations -
- Switch is not considered. If there is a switch between router and PC just ignore it.



