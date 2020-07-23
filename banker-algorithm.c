#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

// Define static array
int maxRes[5][4]; //Max available resources data from file
// int allocateRes[5][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,1}}; //Allocated resources in each Customers
int allocateRes[5][4];


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