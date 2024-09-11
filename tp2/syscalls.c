#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#undef errno
extern int errno;

register char *stack_ptr asm("sp");

caddr_t _sbrk(int incr) {
    extern char end asm("end"); // Déclaration de la fin de l'espace non initialisé (BSS)
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &end;
    }
    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr) {
        // Dépassement de la pile
        errno = ENOMEM;
        return (caddr_t) -1;
    }
    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _write(int file, char *ptr, int len) {
    return len;
}

void _exit(int status) {
    while (1) {}
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

int _getpid(void) {
    return 1;
}

int _gettimeofday(struct timeval *tv, struct timezone *tz) {
    if (tv) {
        tv->tv_sec = 0;
        tv->tv_usec = 0;
    }
    return 0;
}

