#_____________STATIC STUFF________________________________________________
FILES := $(shell echo *.cpp  | sed -e 's/cpp/o/g')
UNAME := $(shell uname)
EXE     := $(UNAME)_lens_craft
#_____________STATIC STUFF________________________________________________

ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++
INCPATH = -I /opt/local/include/ -I /usr/local/include/
LIBPATH = -L /usr/local/lib/
CXXFLAGS = -framework OpenGL -framework IOKit -framework Cocoa -std=c++11
endif
ifeq ($(UNAME), Linux)
CXX = g++
INCPATH = -I. -I /usr/local/include/ -I /usr/include/
LIBPATH = -L /usr/local/lib -L /usr/lib/
CXXFLAGS = -std=c++0x -DGLEW_STATIC -lGL -lGLU
endif
OPTIONS = -lopencv_core -lopencv_imgproc -lopencv_video -lopencv_highgui -lopencv_contrib -lopencv_legacy -lglfw -lGLEW -lpthread

CFLAGS = $(INCPATH) $(LIBPATH) $(OPTIONS) $(CXXFLAGS) -Wall
UNAME := $(shell uname)

build : build-release

run : build-release
	./$(EXE) 

initDep :
	bash uzDep.sh

run-debug : build-debug
	./$(EXE) 

run-gdb : build-debug
	gdb --args ./$(EXE)

edit0 :
	nano -c main.cpp

edit1 :
ifeq ($(UNAME), Linux)
	kate *.cpp *.hpp &
endif
ifeq ($(UNAME), Darwin)
	@echo 'N/A'
endif

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./EXE

build-release : initDep
build-release : CFLAGS += -O3
build-release : $(EXE)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE) : $(FILES)
	$(CXX) $^ -o $(EXE) $(CFLAGS)

clean :
	rm -rf *.o* *.gch $(EXE)*


