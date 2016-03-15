#ifndef OCGL_CONTRACT_H
#define OCGL_CONTRACT_H

#include <cassert>

#define PRE_TRUE(expr) assert(expr);
#define PRE_FALSE(expr) assert(!expr);
#define PRE_EQ(a, b) assert(a == b);
#define PRE_NE(a, b) assert(a != b);
#define PRE_LT(a, b) assert(a < b);
#define PRE_GT(a, b) assert(a > b);
#define PRE_LE(a, b) assert(a <= b);
#define PRE_GE(a, b) assert(a >= b);

#define PRE(expr) PRE_TRUE(expr);

#endif // OCGL_CONTRACT_H
