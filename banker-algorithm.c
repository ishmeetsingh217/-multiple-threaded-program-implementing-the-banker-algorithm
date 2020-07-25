#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

void checkRequest(int eachValue[], int availRes[]); //function to Check request
void checkRelease(int eachValue[], int availRes[]); //function to Check release
int safe[10], top;
// Define static array
int maxRes[5][4]; //Max available resources data from file
// int allocateRes[5][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,1}}; //Allocated resources in each Customers
int allocateRes[5][4];
int availRes[5];
int eachValue[5];
void outValuse();									//Output Current state of the arrays
void runSafe(int customer_id);						//Rnu all threads with safe sequence
int nCustomers = 0;

// Define static variables
char type[4] = {0};

int nRes = 0;
int customer_id = 0;

void *threadRun();				//the thread function, the code executed by each thread
int readFile(char *fileName);	//function to read the file content and build array of threads
void printFile(char *filename); //function to print of file content
void allThread();				//Run all thread with safe state

int readFile(char *fileName) //Read data from file...
{
	// Read file content from file
	FILE *in = fopen(fileName, "r");
	if (!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}
	struct stat st;
	fstat(fileno(in), &st);
	// malloc filecontent
	char *fileContent = (char *)malloc(((int)st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';
	// Get file content line by line
	while (!feof(in))
	{
		char line[100];
		if (fgets(line, 100, in) != NULL)
		{
			strncat(fileContent, line, strlen(line));
		}
	}
	fclose(in);
	char *mLine = NULL;
	char *fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
	strcpy(fileCopy, fileContent);
	mLine = strtok(fileCopy, "\r\n");
	while (mLine != NULL)
	{
		nCustomers++;
		mLine = strtok(NULL, "\r\n");
	}
	char *lines[nCustomers];
	mLine = NULL;
	int i = 0;
	// splite the filecontent as line
	mLine = strtok(fileContent, "\r\n");
	while (mLine != NULL)
	{
		lines[i] = malloc(sizeof(mLine) * sizeof(char));
		// copy the line content to lines array
		strcpy(lines[i], mLine);
		i++;
		mLine = strtok(NULL, "\r\n");
	}
	int j = 0;
	// add max resource value from file
	for (int k = 0; k < nCustomers; k++)
	{
		char *token = NULL;
		j = 0;
		token = strtok(lines[k], ",");
		while (token != NULL)
		{
			maxRes[k][j] = atoi(token);
			j++;
			token = strtok(NULL, ",");
		}
	}
	return j;
}

void printFile(char *filename)
{

	FILE *in = fopen(filename, "r");
	if (!in)
	{
		printf("Child A: ErrTFIDF approachor in opening input file...exiting with error code -1\n");
	}
	printf("Maximum resources from file : \n");
	// print content line by line
	while (!feof(in))
	{
		char line[100];
		if (fgets(line, 100, in) != NULL)
		{
			printf("%s", line);
		}
	}
	printf("\n");
	fclose(in);
}




// function that implement request command		
void checkRequest(int eachValue[], int availRes[])
{
	int flag = 1;
	// check possibility RQ command
	for (int i = 1; i < 5; i++)
	{
		if ((maxRes[eachValue[0]][i - 1] < eachValue[i]) && (eachValue[i] * 2 > availRes[i]))
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
	{
		// Reset the available value and allocated values
		for (int i = 1; i < 5; i++)
		{
			availRes[i] = availRes[i] - eachValue[i];
			allocateRes[eachValue[0]][i - 1] = eachValue[i];
		}
		printf("Request is satisfied\n");
	}
	else
	{
		printf("Request is not satisfied\n");
	}
}

//Funtion that implement release command
void checkRelease(int eachValue[], int availRes[])
{
	int flag = 1;
	// Check the possibility of release command
	for (int i = 1; i < 5; i++)
	{
		if (eachValue[i] > allocateRes[eachValue[0]][i - 1])
		{
			flag = 0;
			break;
		}
	}
	// reset allocated values after release command
	if (flag == 1)
	{
		for (int i = 1; i < 5; i++)
		{
			allocateRes[eachValue[0]][i - 1] = allocateRes[eachValue[0]][i - 1] - eachValue[i];
		}
		printf("Release is satisfied\n");
	}
	else
	{
		printf("Release is not satisfied\n");
	}
}
void outValuse()
{
	// out availabele array
	printf("Available resources : ");
	for (int i = 0; i < nRes; i++)
	{
		printf("%d ", availRes[i + 1]);
	}
	printf("\n");
	// Out maximum array
	printf("Maximum resources : \n");
	for (int i = 0; i < nCustomers; i++)
	{
		for (int j = 0; j < nRes; j++)
		{
			printf("%d ", maxRes[i][j]);
		}
		printf("\n");
	}
	// Out allocate array
	printf("Allocate resources arrays: \n");
	for (int i = 0; i < nCustomers; i++)
	{
		for (int j = 0; j < nRes; j++)
		{
			printf("%d ", allocateRes[i][j]);
		}
		printf("\n");
	}
	// Out need array
	printf("Need resources arrays: \n");
	for (int i = 0; i < nCustomers; i++)
	{
		for (int j = 0; j < nRes; j++)
		{
			printf("%d ", maxRes[i][j] - allocateRes[i][j]);
		}
		printf("\n");
	}
}
void runSafe(int customer_id)
{
	int temp[4];
	printf("\n       Thread has started\n");
	// print the new available array
	for (int i = 0; i < 4; i++)
	{
		temp[i] = availRes[i + 1] + allocateRes[customer_id][i];
	}
	printf("       Thread has finished\n");
	printf("       Thread is releasing resources\n");
	printf("       New Available resources: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", temp[i]);
	}
	printf("\n");
}

void allThread(pthread_t tid)
{
	// execute the Run command
	for (int customer_id = 0; customer_id < nCustomers; customer_id++)
	{
		printf("\n-->Customer/Thread %d\n", customer_id);
		printf("       Allocated resources: ");
		for (int i = 0; i < 4; i++)
		{
			printf("%d ", allocateRes[customer_id][i]);
		}
		printf("\n       Needed resources: ");
		for (int i = 0; i < 4; i++)
		{
			printf("%d ", maxRes[customer_id][i] - allocateRes[customer_id][i]);
		}
		printf("\n       Available resources: ");
		for (int i = 0; i < 4; i++)
		{
			printf("%d ", availRes[i + 1]);
		}
		pthread_create(&tid, NULL, threadRun, NULL);
		pthread_join(tid, NULL);
	}
}

void *threadRun() //implement this function in a suitable way
{
	// Run the function for each command keyword
	if (strcmp(type, "RQ") == 0)
	{
		checkRequest(eachValue, availRes);
	}
	else if (strcmp(type, "RL") == 0)
	{
		checkRelease(eachValue, availRes);
	}
	else if (strcmp(type, "*") == 0)
	{
		outValuse();
	}
	else if (strcmp(type, "Run") == 0)
	{
		runSafe(customer_id);
		customer_id++;
	}
	return 0;
}
int is_available(int customer_id, int need[][nRes])
{
	int flag = 1;
	customer_id = 3; 
	// check if all the available resources
	// are less greater than need of process
	for (int i = 0; i < nRes; i++)
	{
		if (need[customer_id][i] > availRes[i + 1] + allocateRes[customer_id][i])
		{
			flag = 0;
		}
	}
	return flag;
}

// Get safe sequences
void safe_sequence(int need[][nRes])
{
	int safe_flag = 0;
	int i = 0,temp=0;
	while (safe_flag < nCustomers)
	{
		int continue_flag = 0;
		// Check continue with existed elements
		for (int k = 0; k < nCustomers; k++)
		{
			if ((safe[k] == i)&&(safe[k] > 0))
			{
				continue_flag = 1;
			}
		}
		// If i is available, push i to safe array
		if (continue_flag != 1)
		{
			if (is_available(i, need) == 1)
			{
				push(i);
				safe_flag = safe_flag + 1;
			}
			else
			{
				temp = i;
			}
			i++;
			if (i == nCustomers)
			{
				i = temp;
			}
		}
		
	}
	// if a safe-sequence is found, display it
	if ((safe[nCustomers] != 1) || (safe[nCustomers] != -1))
	{
		printf("Safe sequence is : <");
		for (int i = 0; i < nCustomers; i++)
		{
			printf(" %d ", safe[i]);
		}
		printf(">");
	}
}

int main(int argc, char *argv[])
{
	char *filename = "sample4_in.txt";
	nRes = readFile(filename);
	printf("Number of Customers : %d\n", nCustomers);
	// Check argc
	if (argc < nRes + 1)
	{
		fprintf(stderr, "usage: ./assignment04.out <# of src 1> <# of src 2> <# of src 3><# of src 4>\n");
		exit(1);
	}
	printf("Currentrly Available resources : ");
	// Print available resources
	for (int i = 0; i < argc; ++i)
	{
		if (i == 0)
		{
			continue;
		}
		availRes[i] = atoi(argv[i]);
		printf("%d ", availRes[i]);
	}
	printf("\n");
	printFile(filename);
	int com_num = 0;
	char command[3] = {0};
	int command_flag = 1;
	pthread_t tid;
	int need[nCustomers][nRes];
	for (int i = 0; i < nCustomers; i++)
	{
		for (int j = 0; j < nRes; j++)
		{
			need[i][j] = maxRes[i][j] - allocateRes[i][j];
		}
	}
}