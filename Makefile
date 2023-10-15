CC = gcc
CFLAGS = -std=c99 -Wall 
SOURCES = main.c 
OBJECTS = $(SOURCES:.c=.o)
LIB_NAME =  mymalloc.a
LIB_OBJ = $(LIB_NAME:.a=.o)
LDFLAGS = -L./ -lmymalloc
TARGET  = main

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS) lib$(LIB_NAME)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

lib$(LIB_NAME) : $(LIB_OBJ)
	ar rcs  $@ $^


.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJECTS) lib$(LIB_NAME) $(LIB_OBJ)
