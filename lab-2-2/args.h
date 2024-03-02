#ifndef ARGS_H
#define ARGS_H

#define FOLDER "bin/"

#define FILE_A "a.bin"
#define FILE_B "b.bin"
#define FILE_C "c-%d.bin"

struct args {
    int nsize;
    int ngroup;
};

extern struct args args;

#endif
