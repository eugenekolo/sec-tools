CFLAGS= -Wall -O4 -std=c99
OBJS= aeskeyfind.o aes.o util.o

all: aeskeyfind

aeskeyfind: $(OBJS)
	$(CC) -o aeskeyfind $(OBJS)

clean:
	@rm -f aeskeyfind *~ \#* $(OBJS)

