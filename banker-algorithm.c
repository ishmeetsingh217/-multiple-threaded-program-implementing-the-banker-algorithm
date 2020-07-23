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
int nCustomers = 0;


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