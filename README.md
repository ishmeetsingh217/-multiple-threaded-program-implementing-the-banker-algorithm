# PROJECT TITLE

Deadlock Avoidance Using Banker's Algorithm

# MOTIVATION/ Description

> In this project, we have made a multiple threaded program that implements the banker's algorithm. A customer has the ability to request and release resoruces from the bank. The resources will be tracked by the banker and the request will be granted if the safety algorithm is satisfied. The banker has the ability to deny the request if the safe state is not satisfied. 

# INSTALLATION / USAGE

To rename makefile.mk to makefile, run:

### $mv makefile.mk Makefile

Makefile is in the same folder as your .c file to compile run

### $make

This will compile your program with warnings turned into errors. If you instead run

### $make warnings_OK

This will compile your program with warnings enabled but not fatal. If successful (ie gcc didn't complain) you should now have a file name Assignment04.out

Try running
### $./assignment04.out

and see what happens. It should fail with an appropriate error message

To run it properly use
### $./assignment04.out <# of src 1> <# of src 2> <# of src 3><# of src 4>

 For example, if there were four resource types, with ten instances of the first type, five of the second type, seven of the third type, and eight of the fourth type, you would invoke your program as follows: **./assignment04.out 10 5 7 8**
where **<# of src 1> <# of src 2> <# of src 3><# of src 4>** is the resources that customer request 
 For example, if customer/thread0 were to request the resources (3, 1, 2, 1), the following command would be entered:
                                         **RQ 0 3 1 2 1**

# SCREENSHOTS/OUTPUT
<table>
  <tr>
    <td><img src="https://i.imgur.com/ngljUWq.png" height = "430" width="430"></td>
    <td><img src="https://i.imgur.com/NISI2RF.png" height = "430" width="430"></td>
  </tr>
 <tr>
    <td><img src="https://i.imgur.com/NISI2RF.png" height = "430" width="430"></td>
    <td><img src="https://imgur.com/sf5CdUb.png" height = "430" width="430"></td>
  </tr>
 <tr>
    <td><img src="https://imgur.com/mzvi2wP.png" height = "430" width="430"></td>
    <td><img src="https://imgur.com/t03pMPi.png" height = "430" width="430"></td>
  </tr>
 <tr>
    <td><img src="https://imgur.com/gjkQYxj.png" height = "430" width="430"></td>
    <td><img src="https://imgur.com/wBU925P.png" height = "430" width="430"></td>
  </tr>
</table>

# INDIVIDUAL CONTRIBUTION 

Following functions are written and implemented by Ishmeet:
1) int readFile(char *fileName)
2) void checkRequest(int eachValue[], int availRes[])
3) void checkRelease(int eachValue[], int availRes[])
4) void *threadRun()
5) void safe_sequence(int need[][nRes])
6) int main(int argc, char *argv[])

Following functions are written and implemented by Kiishi:
1) void printFile(char *filename)
2) void outValuse()
3) void runSafe(int customer_id)
4) void allThread(pthread_t tid)
5) int is_available(int customer_id, int need[][nRes])
6) void push(int element)

# FEATURES

The features of this project is to implement banker's algorithm. This method is used by banking systems to determine whether a loan can be granted or not. This program implements RQ, RL,Asterisk symbol(*), Run features.
#### RQ is resource request of customer.
#### RL is resource release of customer.
#### Asterisk symbol(*) is command to output status of all arrays value.
#### Run is to get safe sequence and run all threads with same code.

# CODE EXAMPLE 
<table>
  <tr>
    <td><img src="https://imgur.com/N3hEHPD.png" height = "430" width="500"></td>
    <td><img src="https://imgur.com/yGUZZpg.png" height = "430" width="500"></td>
    <td><img src="https://imgur.com/MgovzVD.png" height = "430" width="500"></td>
  </tr>
</table>


# Authors and Acknowledgment
- ISHMEET SINGH 

# Contributors
 - ISHMEET SINGH 
 - KIISHI 


# LICENSE
- MIT License
- GNU GPLv3


