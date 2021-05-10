FUNC = func
MAIN = project
EXEC = project

$(EXEC): $(FUNC).o $(MAIN).o
	gcc $(FUNC).o $(MAIN).o gfx3.o -lX11 -lm -o project

$(FUNC).o: $(FUNC).c $(FUNC).h
	gcc -c $(FUNC).c -o $(FUNC).o

$(MAIN).o: $(MAIN).c $(FUNC).h
	gcc -c $(MAIN).c -o $(MAIN).o

clean:
	rm $(MAIN).o
	rm $(FUNC).o
	rm $(EXEC)
