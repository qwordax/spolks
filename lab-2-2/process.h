#ifndef PROCESS_H
#define PROCESS_H

#include "args.h"
#include "compute.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

int process(int argc, char **argv);

#endif
