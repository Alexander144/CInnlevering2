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
	if(f != NULL)
	{
		while (!feof(f)) 
		{
			if(i==LocalCount)
			{	
				i=i*2;
				TheSong = (char*) realloc(TheSong,i*sizeof(char));	
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

char *BeReadyForCryp(char *TheSong, char *TheSong2, int *Count, int *CountSongNew)
{
	int i;
	int l = 0;
	for(i = 0; i<=*Count; i++)
	{
		if(l==*Count)
		{
			TheSong2 = (char*) realloc(TheSong2,2*l*sizeof(char));
		}
		if(TheSong[i]>='A' && TheSong[i]<='Z')
		{			
			TheSong2[l]=TheSong[i]+32;			
			l++;
		}
		else if(TheSong[i]>='a' && TheSong[i]<='z')
		{
			TheSong2[l]=TheSong[i];			
			l++;
		}
	}
	*CountSongNew = l;
	return TheSong2;
}

void Cryp(char *TheSong2, int *CountSongNew, char *Text, int *CountText)
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
		for(i = 0; i<=*CountSongNew; i++)
		{
			if(TheSong2[i]==Text[h] && TheSong2[i]>=97 && TheSong2[i]<=122 && Text[h]>=97 && Text[h]<=122)
			{
				fprintf(f,"[%d]",i);
				break;
			}
			else if(TheSong2[i]==Text[h]+32 && TheSong2[i]>=97 && TheSong2[i]<=122 && Text[h]>=65 && Text[h]<=90)
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
void DeCrypt(char *TheSong2, char *CryptText, int *CountSong, int *NewCryptCount)
{
	int i;
	int h;
	int o = 1;
	for(h = 0; h<=*NewCryptCount; h++)
	{
		for(i = 0; i<=*CountSong; i++)
		{
			//printf("%c",TheSong2[i]);
			if(CryptText[h]=='-' && CryptText[h-1] == '[')
			{
				printf("%c",CryptText[h-1]);
				o = o * -1;
			}
			if(i==CryptText[h] && CryptText[h]>=48 && CryptText[h]<=57)
			{
				if(o == -1)
				{
					//printf("Big");
					printf("%c", TheSong2[i]+32);
					o = o * -1;
				}
				else
				{
					//printf("small");
					printf("%c", TheSong2[i]);
				}
				break;
			}
			else if(CryptText[h] == 32 || CryptText[h] >=44 && CryptText[h]<=46)
			{	
				if(CryptText[h] == 45 && !(CryptText[h-1]=='['))
				{
					printf("%c",CryptText[h]);
				}
				else
				{	
					printf("%c",CryptText[h]);	
				}
				break;
			}
			
		}
		//printf("dette er :%d",o);
	}
}

int main(int argc, char *argv[])
{
	char *FileSong = argv[1];
	char *TheSong = (char*)malloc(j*sizeof(char));
	int *CountSong = (int*)malloc(j*sizeof(int));
	TheSong = ReadFile(FileSong, TheSong, CountSong);

	char *TheSong2 = (char*)malloc(*CountSong*sizeof(char));
	int *CountSongNew = (int*)malloc(j*sizeof(int));
	TheSong2 = BeReadyForCryp(TheSong,TheSong2, CountSong, CountSongNew);	
	//PrintFile(TheSong2, CountSong);
	
	char *FileText = argv[2];
	char *Text = (char*)malloc(j*sizeof(char));
	int *CountText = (int*)malloc(j*sizeof(int));	
	int *CryptCount = (int*)malloc(j*sizeof(int));
	Text = ReadFile(FileText, Text, CountText);
	Cryp(TheSong2, CountSongNew, Text, CountText);
	
	char *SecretText = "Secret.txt";
	char *CryptText = (char*)malloc(j*sizeof(char));
	int *NewCryptCount = CryptCount;
	CryptText = ReadFile(SecretText, CryptText, NewCryptCount);
	DeCrypt(TheSong2, CryptText, CountSongNew, NewCryptCount);
	free(TheSong);	
	free(CountSong);
	free(CountText);
	free(Text);
	free(CountSong);
}
