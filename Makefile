NAME1 = NearestNeighbour
NAME2 = NearestNeighbour_BruteForce
NAME3 = Generator

EXEC1 = $(NAME1).exe
EXEC2 = $(NAME2).exe
EXEC3 = $(NAME3).exe

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

DIMENSIONS = 5
NUMBEROFPOINTS = 10

CFLAGS = -Wall -std=c++11 -pedantic -O2 -DDIMENSIONS=$(DIMENSIONS) -DNUMBEROFPOINTS=$(NUMBEROFPOINTS)
LFLAGS = -Wall -std=c++11 -pedantic -O2

CO = g++
LD = $(CO)

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

.PHONY: all clean run
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(OBJS1): $(NAME1).cpp
	$(CO) $(CFLAGS) -c -o $@ $<

$(OBJS2): $(NAME2).cpp
	$(CO) $(CFLAGS) -c -o $@ $<

$(OBJS3): $(NAME3).cpp
	$(CO) $(CFLAGS) -c -o $@ $<

run: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC3)
	./$(EXEC1) points.txt addedPoints.txt
	./$(EXEC2) points.txt addedPoints.txt

clean:
	rm -f *.o *.exe
