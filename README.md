PROJECT TITLE

Deadlock Avoidance Using Banker's Algorithm

MOTIVATION

In this project, we have made a multiple threaded program that implements the banker's algorithm. A customer has the ability to request and release resoruces from the bank. The resources will be tracked by the banker and the request will be granted if the safety algorithm is satisfied. The banker has the ability to deny the request if the safe state is not satisfied. 

INSTALLATION

To rename makefile.mk to makefile, run:

$mv makefile.mk Makefile

Makefile is in the same folder as your .c file to compile run

$make

This will compile your program with warnings turned into errors. If you instead run

$make warnings_OK

This will compile your program with warnings enabled but not fatal. If successful (ie gcc didn't complain) you should now have a file name Assignment04.out

Try running
$./assignment04.out

and see what happens. It should fail with an appropriate error message

To run it properly use
$./assignment04.out <# of src 1> <# of src 2> <# of src 3><# of src 4>

# For example, if there were four resource types, with ten instances of the first type, five of the second type, seven of the third type, and eight of the fourth type, you would invoke your program as follows: ./assignment04.out 10 5 7 8

# where <# of src 1> <# of src 2> <# of src 3><# of src 4> is the resources that customer request 
# For example, if customer/thread0 were to request the resources (3, 1, 2, 1), the following command would be entered:
#                                          RQ 0 3 1 2 1

SCREENSHOTS

INDIVIDUAL CONTRIBUTION 

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

FEATURES

TESTS

CODE EXAMPLE 

AUTHORS

CREDITS 

LICENSE