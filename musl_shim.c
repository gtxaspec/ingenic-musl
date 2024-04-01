#include <fcntl.h>       // For file control options, off_t
#include <stdarg.h>      // For variable arguments handling
#include <stdio.h>       // For standard input/output functions, file handling
#include <stdlib.h>      // For standard library functions, abort
#include <sys/stat.h>    // For file status/statistics
#include <errno.h>       // For error number definitions
#include <string.h>      // For string handling functions
#include <unistd.h>      // For POSIX operating system API, syscall interface
#include <sys/syscall.h> // For syscall numbers and syscall interface
#include <stdint.h>      // For standard integer types

/*
 * Shim to create missing function calls in the ingenic libimp library.
 */

#define DEBUG 0  // Set this to 1 to enable debug output or 0 to disable

#if DEBUG
#define DEBUG_PRINT(...) fprintf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...) (void)0
#endif

void __pthread_register_cancel(void *buf) {
	DEBUG_PRINT(stderr, "[WARNING] Called __pthread_register_cancel. This is a shim and does nothing.\n");
}

void __pthread_unregister_cancel(void *buf) {
	DEBUG_PRINT(stderr, "[WARNING] Called __pthread_unregister_cancel. This is a shim and does nothing.\n");
}

void __assert(const char *msg, const char *file, int line) {
	DEBUG_PRINT(stderr, "Assertion failed: %s (%s: %d)\n", msg, file, line);
	abort();
}

int __fgetc_unlocked(FILE *stream) {
	DEBUG_PRINT(stderr, "[WARNING] Called __fgetc_unlocked. This is a shim and does nothing.\n");
	return fgetc(stream);
}

void __ctype_b(void) {
	DEBUG_PRINT(stderr, "[WARNING] Called __ctype_b. This is a shim and does nothing.\n");
}
void __ctype_tolower(void) {
	DEBUG_PRINT(stderr, "[WARNING] Called __ctype_tolower. This is a shim and does nothing.\n");
}

// Custom mmap implementations address an Ingenic library bug affecting memory mapping offsets.
// Using musl, the library requires specific handling of offsets, necessitating these workarounds.
// The first variant uses an `off_t` type for static memory mappings, aligning with systems where
// larger offset sizes may be needed. The second uses `uint32_t` for shared memory mappings,
// suitable for scenarios requiring defined, 32-bit wide offsets. Both adjust the offset by
// shifting it 12 bits right (off >> 12) before calling syscall with SYS_mmap2, ensuring proper
// offset handling despite the library's limitations.
#ifdef INGENIC_MMAP_STATIC
void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off) {
	DEBUG_PRINT(stderr, "[WARNING] Called INGENIC_MMAP_STATIC\n");
	return (void *)syscall(SYS_mmap2, start, len, prot, flags, fd, off >> 12);
}
#else // This else branch makes INGENIC_MMAP_SHARED the default if INGENIC_MMAP_STATIC is not defined
void *mmap(void *start, size_t len, int prot, int flags, int fd, uint32_t off) {
	DEBUG_PRINT(stderr, "[WARNING] Called INGENIC_MMAP_STATIC\n");
	return (void *)syscall(SYS_mmap2, start, len, prot, flags, fd, off >> 12);
}
#endif

/* Required for Xburst2 libraries */

int __fputc_unlocked(int c, FILE *stream) {
	DEBUG_PRINT(stderr, "[WARNING] Called __fputc_unlocked. This is a shim and does nothing.\n");
	return fputc(c, stream);
}

FILE* fopen64(const char *path, const char *mode) {
	DEBUG_PRINT(stderr, "[WARNING] Called fopen64. This is a shim and does nothing.\n");
	return fopen(path, mode);
}

int open64(const char *path, int flags, ...) {
	mode_t mode = 0;

	// Mode is only provided if O_CREAT is passed in flags
	if (flags & O_CREAT) {
		va_list args;
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
	}

	DEBUG_PRINT(stderr, "[WARNING] Called open64. This is a shim and does nothing.\n");
	if (flags & O_CREAT) {
		return open(path, flags, mode);
	} else {
		return open(path, flags);
	}
}

int fseeko64(FILE *stream, off_t offset, int whence) {
	DEBUG_PRINT(stderr, "[WARNING] Called fseeko64. This is a shim and does nothing.\n");
	return fseeko(stream, offset, whence);
}

void* mmap64(void *start, size_t len, int prot, int flags, int fd, uint32_t off) {
return (void *)syscall(SYS_mmap2, start, len, prot, flags, fd, off >> 12);
}

/* End Required for Xburst2 libraries */
