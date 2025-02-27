# Directories
BIN = bin
OBJ = obj
LIB = lib

DIRS=\
     $(BIN)\
     $(OBJ)\
     $(LIB)

$(shell mkdir -p $(DIRS))

# Flags
CFLAGS = -g -Wall -Wpedantic -Wextra -Wsign-compare -Werror 
# Uncomment the following line for optimized builds
# CFLAGS = -O3 -lm -Wall -pthread -Wpedantic -Wextra -Wsign-compare -Werror -Wconversion
SANI_ADDR = -fsanitize=address -fno-omit-frame-pointer -static-libasan
SANI_THREAD = -fsanitize=thread -fno-omit-frame-pointer -static-libtsan
#CC= cc $(CFLAGS) $(SANI_ADDR)
#CC= cc $(CFLAGS) $(SANI_THREAD) 
CC = cc $(CFLAGS)

# Libraries
SQRTFLAGS = -lsqrt 

# Targets
TARGETS = \
    arbsqrt 

LIBS = \
	$(LIB)/libsqrt.a 

MYOBJS = 

all: $(LIBS) $(TARGETS)

libs: $(LIBS)

clean:
	rm -r $(LIB) $(OBJ) $(BIN) $(TARGETS)

$(OBJ)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

lib/libsqrt.a: $(OBJ)/libsqrt.o
	ar -rcs $@ $<

$(LIB)/lib%.a: $(OBJ)/%.o
	ar -rcs $@ $<

%: %.c $(LIBS)
	$(CC) -L$(LIB) -o $@ $< $(SQRTFLAGS) -lm  
