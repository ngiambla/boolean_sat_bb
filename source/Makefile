#Makefile for placer

PLATFORM = X11

EXE = ms_util
HDR = log.h
FLAGS = -g -Wall -D$(PLATFORM) -std=c++11
CUR_DIR = $(shell pwd)
UNAME := $(shell uname)

$(System is $(UNAME))

ifeq ($(UNAME), Darwin)
	ifeq ($(PLATFORM),X11)
	   GRAPHICS_LIBS = -lX11 -L/usr/X11/lib -I/usr/X11/include
	endif
else
	ifeq ($(PLATFORM),X11)
	   GRAPHICS_LIBS = -lX11
	endif
endif


$(EXE): expression.o ms_util.o
	g++ $(FLAGS) expression.o ms_util.o $(GRAPHICS_LIBS) -o $(EXE)

expression.o: expression.cpp $(HDR)
	g++ -c $(FLAGS) expression.cpp

ms_util.o: ms_util.cpp $(HDR)
	g++ -c $(FLAGS) ms_util.cpp

clean:
	rm $(EXE) *.o