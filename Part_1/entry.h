#ifndef ENTRY_H
#define ENTRY_H

#include "curve.h"

//hashtable's entries
typedef struct h_entry{
	real_curve* rcurve;//pointer to the original curve
	real_curve* gcurve;//pointer to grid representation of above curve
}entry;

#endif
