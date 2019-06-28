CC			:= g++
TARGET		:= main
FLAGS		:= -Wall -Wextra -std=c++17 -mavx -mfma -O3 -ffast-math -fomit-frame-pointer
LIBS		:= -lm -lpthread -lX11
SOURCE		:= $(wildcard src/*.cpp)
HEADERS		:= $(wildcard src/*.hpp)
OBJS		:= $(patsubst %.cpp, %.o, $(SOURCE))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ 

%.o: %.cpp $(HEADERS)
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean debug
