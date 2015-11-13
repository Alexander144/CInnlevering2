
char *ReadFile(char *FileName, char *TheSong, int *Count);
void PrintFile(char *TheSong, int *Count);
char *BeReadyForCryp(char *TheSong, char *TheSong2, int *Count, int *CountSongNew);
void Cryp(char *TheSong2, int *CountSongNew, char *Text, int *CountText);
void DeCrypt(char *TheSong2, char *CryptText, int *CountSong, int *NewCryptCount);
