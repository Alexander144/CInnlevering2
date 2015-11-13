#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define j 10
#define Innlevering2.c

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
