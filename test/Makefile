CMP=g++
MAIN=Rationalmain
FUNCTION=Rational
EXEC=runit
$(EXEC): $(MAIN).o $(FUNCTION).o
	$(CMP) $(MAIN).o $(FUNCTION).o -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(FUNCTION).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o

$(FUNCTION).o: $(FUNCTION).cpp $(FUNCTION).h
	$(CMP) -c $(FUNCTION).cpp -o $(FUNCTION).o

clean:
	rm *.o $(EXEC)

