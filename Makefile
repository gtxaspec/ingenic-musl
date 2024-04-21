CFLAGS += -Wall -O2
LDFLAGS_SHARED = -shared
LDFLAGS_STATIC =
TARGET_LIB_SHARED = libmuslshim.so
TARGET_LIB_STATIC = libmuslshim.a

SRC_FILES = musl_shim.c
OBJ_FILES = $(SRC_FILES:.c=.o)

.PHONY: all clean dynamic static

all: dynamic

ifeq ($(STATIC), 1)
all: static
else
all: dynamic
endif

dynamic: $(TARGET_LIB_SHARED)

static: $(TARGET_LIB_STATIC)

$(TARGET_LIB_SHARED): $(OBJ_FILES)
	$(CC) $(LDFLAGS_SHARED) -o $@ $^

$(TARGET_LIB_STATIC): $(OBJ_FILES)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET_LIB_SHARED) $(TARGET_LIB_STATIC)
