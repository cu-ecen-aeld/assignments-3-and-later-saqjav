CC = gcc
CFLAGS = -Wall

SRC = writer.c
ELF = writer


ifeq ($(CROSS_COMPILE),aarch64-none-linux-gnu-gcc)
	CC = aarch64-none-linux-gnu-gcc
endif

default: $(ELF)

$(ELF): $(SRC) 
	$(CC) $(CFLAGS) $(SRC) -o $(ELF)

clean:
	rm -f *.out $(ELF)