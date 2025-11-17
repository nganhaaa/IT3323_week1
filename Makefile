TEXTFILE ?= alice30.txt
all: run

run:
	gcc index.c -o index
	./index $(TEXTFILE)

clean:
	rm -f index
	rm -f index.txt
