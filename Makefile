CFLAGS+=-fPIC -Wall -O2
LDFLAGS+=-shared
TARGET_LIB=libmuslshim.so

SRC_FILES=musl_shim.c
OBJ_FILES=$(SRC_FILES:.c=.o)

.PHONY: all clean

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET_LIB)
