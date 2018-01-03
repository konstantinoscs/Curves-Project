#ifndef ASSIGN_ENTRY_H
#define ASSIGN_ENTRY_H

#include "curve.h"

//hashtable's entries
typedef struct assign_entry{
  real_curve* rcurve;//pointer to the original curve
  int centroid;//centroid in which will belong the rcurve
  double distance;//in case of conflicts check min distance
}assign_entry;

#endif
