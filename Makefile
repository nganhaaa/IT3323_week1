TEXTFILE ?= alice30.txt
OUTPUT ?= index.txt

all: run

run:
	gcc index.c -o index
	./index $(TEXTFILE) $(OUTPUT)

clean:
	rm -f index
	rm -f $(OUTPUT)
