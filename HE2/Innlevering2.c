#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define j 10
char *ReadFile(char *FileName, char *TheSong, int *Count)
{
	FILE *f = fopen(FileName, "r");
	char Sentence;
	int LocalCount = 0;
	int i = j;
	char *TheSongBuffer;
	if(f != NULL)
	{
		while (!feof(f)) 
		{
			if(i==LocalCount)
			{	
				i=i*2;
				TheSongBuffer = (char*) realloc(TheSong,i*sizeof(char));
				if(TheSongBuffer != NULL)
				{
					TheSong = TheSongBuffer;
				}	
			}
				fscanf(f,"%c",&Sentence);				
				TheSong[LocalCount] = Sentence;							
				LocalCount++;
				
		}
	}
	else{printf("File error");}	
	fclose(f);
	//free(TheSongBuffer);
	*Count = LocalCount;
	return TheSong;
}

void PrintFile(char *TheSong, int *Count)
{
	int i;
	for(i = 0; i<=*Count; i++)
	{
		printf("%c",TheSong[i]);
	}
}

char *BeReadyForCryp(char *TheSong, int *Count)
{
	int i;
	for(i = 0; i<=*Count; i++)
	{
		if(TheSong[i]>=65 && TheSong[i]<=90)
		{
			TheSong[i]=32+TheSong[i];
		}
	}
	return TheSong;
}

void Cryp(char *TheSong, int *CountSong, char *Text, int *CountText)
{
	FILE *f = fopen("Secret.txt", "w");
	if (f == NULL)
	{
   	 	printf("Error opening file!\n");
  	 	exit(1);
	}	
	int i;
	int h;
	for(h = 0; h<=*CountText; h++)
	{
		for(i = 0; i<=*CountSong; i++)
		{
			if(TheSong[i]==Text[h] && TheSong[i]>=97 && TheSong[i]<=122 && Text[h]>=97 && Text[h]<=122)
			{
				fprintf(f,"[%d]",i);
				break;
			}
			else if(TheSong[i]==Text[h]+32 && TheSong[i]>=97 && TheSong[i]<=122 && Text[h]>=65 && Text[h]<=90)
			{
				fprintf(f,"[%d]",-i);
				break;
			}
			else if(Text[h] == 32 || Text[h] >=44 && Text[h]<=46)
			{	
				fprintf(f,"%c",Text[h]);
				break;
			}
		}
	}
	fclose(f);
}
void DeCrypt(char *TheSong, char *CryptText, int *CountSong, int *NewCryptCount)
{
	int i;
	int h;
	for(h = 0; h<=*NewCryptCount; h++)
	{
		for(i = 0; i<=*CountSong; i++)
		{
			if(i==CryptText[h] && CryptText[h]<0 && TheSong[i]>=65 && TheSong[i]<=90 && CryptText[h]>=48 && CryptText[h]<=57)
			{
				int buffer = i-32;
				printf("%c", TheSong[i]);
				break;
			}
			else if(i==CryptText[h] && CryptText[h]>0 && TheSong[i]>=97 && TheSong[i]<=122 && CryptText[h]>=48 && CryptText[h]<=57)
			{
				printf("%c",TheSong[i]);
				break;
			}
			else if(CryptText[h] == 32 || CryptText[h] >=44 && CryptText[h]<=46)
			{	
				printf("%c",CryptText[h]);
				break;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	char *FileSong = argv[1];
	char *TheSong = (char*)malloc(j*sizeof(char));
	int *CountSong = (int*)malloc(j*sizeof(int));
	
	TheSong = ReadFile(FileSong, TheSong, CountSong);
	
	TheSong = BeReadyForCryp(TheSong,CountSong);	

	char *FileText = argv[2];
	char *Text = (char*)malloc(j*sizeof(char));
	int *CountText = (int*)malloc(j*sizeof(int));	
	int *CryptCount = (int*)malloc(j*sizeof(int));
	Text = ReadFile(FileText, Text, CountText);
	Cryp(TheSong, CountSong, Text, CountText);
	
	char *SecretText = "Secret.txt";
	char *CryptText = (char*)malloc(j*sizeof(char));
	int *NewCryptCount = CryptCount;
	CryptText = ReadFile(SecretText, CryptText, NewCryptCount);
	DeCrypt(TheSong, CryptText, CountSong, NewCryptCount);
	free(CountSong);
	free(CountText);
	free(TheSong);
	free(Text);
	free(CountSong);
}
