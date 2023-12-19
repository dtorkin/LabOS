CC = gcc
CFLAGS = -Wall
SENDER = sender
RECEIVER = receiver

all: $(SENDER) $(RECEIVER)

$(SENDER): $(SENDER).c
	$(CC) $(CFLAGS) -o $(SENDER) $(SENDER).c -lrt -lpthread

$(RECEIVER): $(RECEIVER).c
	$(CC) $(CFLAGS) -o $(RECEIVER) $(RECEIVER).c -lrt -lpthread

clean:
	rm -f $(SENDER) $(RECEIVER)
