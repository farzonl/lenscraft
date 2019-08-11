#_____________STATIC STUFF________________________________________________
FILES := $(shell echo *.cpp  | sed -e 's/cpp/o/g')
UNAME := $(shell uname)
EXE     := $(UNAME)_lens_craft
#_____________STATIC STUFF________________________________________________
OCV_FLGS := `pkg-config opencv --libs --cflags`
GLFW_FLGS:= `pkg-config libglfw --libs --cflags`
GLEW_FLGS:= `pkg-config glew --libs --cflags`
OGL_FLGS := $(GLFW_FLGS) $(GLEW_FLGS)
ifeq ($(UNAME), Darwin)
CXX = clang++
endif
ifeq ($(UNAME), Linux)
CXX = g++
#OGL_FLGS += -DGLEW_STATIC 
OGL_FLGS += -lXxf86vm -lXext -lX11 -lz
endif

CXXFLAGS = $(OCV_FLGS) $(OGL_FLGS) -Wall -std=c++11

build : initDep
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

build-release : CXXFLAGS += -O3
build-release : $(EXE)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXE) : $(FILES)
	$(CXX) $^ -o $(EXE) $(CXXFLAGS)

clean :
	rm -rf *.o* *.gch $(EXE)*


