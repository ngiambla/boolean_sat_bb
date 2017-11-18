#Makefile for placer

PLATFORM = X11

EXE = placer
HDR = log.h
FLAGS = -g -Wall -D$(PLATFORM) -std=c++11
CUR_DIR = $(shell pwd)
UMF_LIB = -L$(CUR_DIR)/SuiteSparse/lib -lumfpack -lamd -lsuitesparseconfig -I$(CUR_DIR)/SuiteSparse/include -lm -Wl,-rpath=$(CUR_DIR)/SuiteSparse/lib
UNAME := $(shell uname)

$(System is $(UNAME))

ifeq ($(UNAME), Darwin)
	ifeq ($(PLATFORM),X11)
	#@ld-options
	   #UMF_LIB = -L$(CUR_DIR)/SuiteSparse/lib -lumfpack -lamd -lsuitesparseconfig -I$(CUR_DIR)/SuiteSparse/include -lm -Wl,RPATH=$(CUR_DIR)/SuiteSparse/lib
	   GRAPHICS_LIBS = -lX11 -L/usr/X11/lib -I/usr/X11/include
	endif
else
	ifeq ($(PLATFORM),X11)
	   GRAPHICS_LIBS = -lX11
	endif
endif


$(EXE): graphics.o csynth.o configholder.o placer.o blck.o ic.o
	g++ $(FLAGS) graphics.o csynth.o configholder.o placer.o blck.o ic.o $(GRAPHICS_LIBS) -o $(EXE) $(UMF_LIB)

graphics.o: graphics.cpp $(HDR)
	g++ -c $(FLAGS) graphics.cpp

csynth.o: csynth.cpp $(HDR)
	g++ -c $(FLAGS) csynth.cpp

configholder.o: configholder.cpp $(HDR)
	g++ -c $(FLAGS) configholder.cpp

placer.o: placer.cpp $(HDR)
	g++ -c $(FLAGS) placer.cpp $(UMF_LIB) -fPIC

blck.o: blck.cpp $(HDR)
	g++ -c $(FLAGS) blck.cpp

ic.o: ic.cpp $(HDR)
	g++ -c $(FLAGS) ic.cpp

clean:
	rm $(EXE) *.o