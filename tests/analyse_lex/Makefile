FONCTION = ../../flex/analyseur # à modifier si besoin
PRINCIPAL = main

$(PRINCIPAL): obj
	gcc -o $(PRINCIPAL) $(FONCTION).o $(PRINCIPAL).o

obj: $(FONCTION).c $(PRINCIPAL).c
	gcc -c $(FONCTION).c -o $(FONCTION).o
	gcc -c $(PRINCIPAL).c -o $(PRINCIPAL).o

$(FONCTION).c: $(FONCTION).l
	flex -o $(FONCTION).c $(FONCTION).l

clean:
	rm -f $(PRINCIPAL) $(FONCTION).c $(FONCTION).o $(PRINCIPAL).o
