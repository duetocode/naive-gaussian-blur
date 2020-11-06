CC = clang++
CFLAGS = -g -Wall -std=c++14
INCLUDES = -I/usr/local/include/opencv4
LIBS = -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui
PROG = main
SRCS = main.cpp

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(LIBS) $(INCLUDES) $(SRCS)