#_____________G++ STUFF__________________________________________
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CC = clang++
INCPATH = -I /opt/local/include/ -I /usr/local/include/ -I /usr/local/include/glm
LIBPATH = -L /opt/local/lib/ -L /usr/local/lib/
CCFLAGS = -stdlib=libc++ -framework OpenGL -framework IOKit -framework Cocoa -std=c++11
endif
ifeq ($(UNAME), Linux)
CC = g++
INCPATH = -I. -I/home/farzon/OpenCV-2.4.3/include -I /usr/include/
LIBPATH = -L/home/farzon/OpenCV-2.4.3/release/lib/ -L /usr/lib/
CCFLAGS = -std=c++0x -DGLEW_STATIC -lGL -lGLU
endif
OPTIONS = -lopencv_core -lopencv_imgproc -lopencv_video -lopencv_highgui -lopencv_contrib -lopencv_legacy -lglfw -lGLEW

CFLAGS = $(INCPATH) $(LIBPATH) $(OPTIONS) $(CCFLAGS) -Wall
UNAME := $(shell uname)
EXE     := $(UNAME)_lens_craft
#_____________G++________________________________________________

run : build-release
	./$(EXE) 

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

build-release : CFLAGS += -O3

build-release : Effects.o Shape.o BoothUI.o ShaderCode.o CaptureCam.o
	$(CC) $(CFLAGS) main.cpp *.o -o $(EXE)

build-debug : CFLAGS += -g -DDEBUG
build-debug : Effects.o Shape.o BoothUI.o ShaderCode.o CaptureCam.o
	$(CC) $(CFLAGS) main.cpp *.o  -o $(EXE)

Effects.o : Effects.cpp Effects.hpp
	$(CC) $(CFLAGS) -c Effects.cpp Grayscale.cpp Grayscale.hpp Sepia.cpp Sepia.hpp Contrast.cpp Contrast.hpp Drawing.cpp Drawing.hpp Xray.cpp Xray.cpp cannyTex.hpp SobelTex.hpp mirror.hpp radialBlur.hpp

Shape.o :  Shape.cpp  Shape.hpp
	$(CC) $(CFLAGS) -c  Shape.cpp  Shape.hpp BoundingBox.cpp BoundingBox.hpp Rectangle.hpp Rectangle.cpp

BoothUI.o : BoothUI.cpp BoothUI.hpp
	$(CC) $(CFLAGS) -c BoothUI.cpp BoothUI.hpp

ShaderCode.o : Shader.cpp Shader.hpp
	$(CC) $(CFLAGS) -c Shader.cpp Shader.hpp 

CaptureCam.o : CaptureCam.hpp CaptureCam.cpp
	$(CC) $(CFLAGS) -c CaptureCam.hpp CaptureCam.cpp

clean :
	rm *.o* $(EXE)* || rm -r $(BINDIR)


