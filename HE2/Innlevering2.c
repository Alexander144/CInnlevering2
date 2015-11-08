#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define j 10000
int ReadFile(char *FileName, char *TheSong)
{
	FILE *f = fopen(FileName, "r");
	char Sentence;
	int Count = 0;
	int i = j;
	if(f != NULL)
	{
		while (!feof(f)) 
		{
			if(i==Count)
			{	
				i=i*2;
				TheSong = (char*) realloc(TheSong,i*sizeof(char));	
			}
				fscanf(f,"%c",&Sentence);
				TheSong[Count] = Sentence;							
				Count++;
				
		}
	}
	else{printf("File error");}
	fclose(f);
	return Count;
}

void PrintFile(char *TheSong, int Count)
{
	int i;
	for(i = 0; i<Count; i++)
	{
		printf("%c",TheSong[i]);
	}
}

int main(int argc, char *argv[])
{
	char *FileName = argv[1];
	char *TheSong = (char*)malloc(j*sizeof(char));
	printf("Dette er: %s",FileName);
	
	int Count = ReadFile(FileName, TheSong);
	//printf("%d",Count);
	PrintFile(TheSong, Count);
}
