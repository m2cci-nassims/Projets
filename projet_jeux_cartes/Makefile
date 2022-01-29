CC = gcc

LIB_DIR = lib
SRC_DIR = src
INC_DIR = include

CFLAGS = -Wall -g -ansi -I./$(INC_DIR) -std=c89
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm -I./$(INC_DIR)

LIB_FILES = $(LIB_DIR)/Alea.c $(LIB_DIR)/Tas.c $(LIB_DIR)/AfficherTas.c
LIB_HEADERS = $(INC_DIR)/Alea.h $(INC_DIR)/Tas.h $(INC_DIR)/AfficherTas.h $(INC_DIR)/TypesConst.h
LIB_OBJS = $(LIB_FILES:.c=.o)

EXECUTABLES = ReussiteR7 ReussiteQLL ReussiteC4 ReussiteMD Reussites

all: $(EXECUTABLES)

%.o: %.c $(LIB_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

ReussiteR7: $(SRC_DIR)/R7.o $(SRC_DIR)/InteractionR7.o $(SRC_DIR)/ReussiteR7.o
ReussiteC4: $(SRC_DIR)/C4.o $(SRC_DIR)/InteractionC4.o $(SRC_DIR)/ReussiteC4.o
ReussiteQLL: $(SRC_DIR)/QLL.o $(SRC_DIR)/InteractionQLL.o $(SRC_DIR)/ReussiteQLL.o
ReussiteMD: $(SRC_DIR)/MD.o $(SRC_DIR)/InteractionMD.o $(SRC_DIR)/ReussiteMD.o
Reussites: $(SRC_DIR)/R7.o $(SRC_DIR)/C4.o $(SRC_DIR)/QLL.o $(SRC_DIR)/MD.o $(SRC_DIR)/InteractionToutes.o $(SRC_DIR)/Reussites.o

$(EXECUTABLES): $(LIB_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -f */*.o
	rm -f $(EXECUTABLES)
