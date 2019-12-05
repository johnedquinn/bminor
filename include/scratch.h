

#ifndef SCRATCH_H
#define SCRATCH_H

#include <stdlib.h>
#include <stdio.h>
#include "library.h"

extern unsigned int COUNTER;

int scratch_alloc (int scratch_table []);
void scratch_free (int scratch_table [], int r);
const char * scratch_name (int r);
int label_create ();
const char * label_name (int label);

#endif
