#ifndef __TYPES_H__
#define __TYPES_H__

/* Color struct */
typedef struct color_struct {
   double r;
   double g;
   double b;
   double f; // "filter" or "alpha"
} color_t;

typedef struct vertex{
  int x;
  int y;
  int z;
} vertex;

typedef struct triangle {
  vertex a;
  vertex b;
  vertex c;
} triangle;

typedef struct rect {
  int minx;
  int maxx;
  int miny;
  int maxy;
  int minz;
  int maxz;
} rect;

#endif
