#Anthony Bartman 
#Makefile for Lab 5
CC = g++
CFLAGS = -c -MMD
LDFLAGS = -lX11
SOURCES = main.cpp gcontext.cpp x11context.cpp matrix.cpp image.cpp shape.cpp line.cpp triangle.cpp mydrawing.cpp viewcontext.cpp
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = painting-pixels

all: $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) $(OBJECTS)

-include *.d

%.o:%.cpp
	$(CC) $(CFLAGS) $<

clean: 
	rm -f $(EXECUTABLE) 
	rm -f $(OBJECTS)
	rm -f *.d
