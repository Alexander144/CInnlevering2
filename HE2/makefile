CC = gcc
File = Innlevering2.c
Flags = -std=c11 -o
Val = --leak-check=full --show-leak-kinds=all 
Vg = valgrind
Prog = Program
TARGET = songLibrary/timber.txt
Compile: $(File)
		$(CC) $(Flags) $(Prog) $(File)
Valgrind: $(File)
		$(Vg) $(Val) ./$(Prog) $(TARGET)


