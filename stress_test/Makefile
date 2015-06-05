TARGET = send_post

INSTALL_PATH = ./bin

VPATH = :src

SRC_PATH = $(foreach dir, $(subst :, ,$(VPATH)), $(wildcard $(dir)/*.cpp))

OBJ_DIR = ./obj

OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(subst :, ,$(VPATH)))
	
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .cpp,.o,$(SRC_PATH)))

MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJ_DIR) $(OBJ_PATH))

INCLUDES = -I./include/ \
		   -I./json/include/ \
		   -I./curl/include/

LIBS = -lpthread -ljson -lcurl 

LIBS_DIR = -L./json/lib/ \
		   -L./curl/lib/

CC = gcc

CXX = g++

CXXFLAGES += -Wall -O2 -g

RM = rm -rf

.PHONY : all clean

all:$(INSTALL_PATH)/$(TARGET)

$(INSTALL_PATH)/$(TARGET):$(OBJS)
	$(CXX) -o $(INSTALL_PATH)/$(TARGET) $(OBJS) $(LIBS)

$(OBJ_PATH)/%.o:%.cpp
	$(CXX) $(CXXFLAGES) $(INCLUDES) -c $^ -o $@

clean:
	$(RM) $(INSTALL_PATH)/$(TARGET)
	$(RM) $(wildcard $(OBJ_DIR)/*)
