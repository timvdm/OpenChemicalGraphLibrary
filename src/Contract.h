#ifndef OCGL_CONTRACT_H
#define OCGL_CONTRACT_H

#ifdef NDEBUG

#define PRE_TRUE(expr)
#define PRE_FALSE(expr)
#define PRE_EQ(a, b)
#define PRE_NE(a, b)
#define PRE_LT(a, b)
#define PRE_GT(a, b)
#define PRE_LE(a, b)
#define PRE_GE(a, b)

#define PRE(expr) PRE_TRUE(expr)

#else // NDEBUG

#include <cassert>
#include <iostream>

#define STRINGIFY(x) #x

#define PRE_BINARY(name, cmp, a, b) \
  if (!(a cmp b)) { \
    std::cerr << name << "(" << STRINGIFY(a) << ", " << STRINGIFY(b) <<") FAILED:" << std::endl; \
    std::cerr << "    " << STRINGIFY(a) << " = " << a << std::endl; \
    std::cerr << "    " << STRINGIFY(b) << " = " << b << std::endl; \
  } \
  assert(a cmp b);

#define PRE_TRUE(expr) assert(expr);
#define PRE_FALSE(expr) assert(!expr);
#define PRE_EQ(a, b) PRE_BINARY("PRE_EQ", ==, a, b);
#define PRE_NE(a, b) PRE_BINARY("PRE_NE", !=, a, b);
#define PRE_LT(a, b) PRE_BINARY("PRE_LT", <, a, b);
#define PRE_GT(a, b) PRE_BINARY("PRE_GT", >, a, b);
#define PRE_LE(a, b) PRE_BINARY("PRE_LE", <=, a, b);
#define PRE_GE(a, b) PRE_BINARY("PRE_GE", >=, a, b);
#define PRE(expr) PRE_TRUE(expr);

#endif // NDEBUG

#endif // OCGL_CONTRACT_H
