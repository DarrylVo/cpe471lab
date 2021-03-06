/*
  CPE 471 Lab 1 
  Base code for Rasterizer
  Example code using B. Somers' image code - writes out a sample tga
*/

#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "types.h"
#include <iostream>
using namespace std;


rect getBB(triangle t);

double areatri(vertex a, vertex b, vertex c);

int main(int argc, char *argv[]) {
  // make a color
  color_t clr;
  color_t clra;
  color_t clrb;
  color_t clrc;
  color_t clrt;

  cout << "Input 3 vertices: \n";

  int vertices[9], i;
  
  vertex a, b, c;

  cin >> a.x;
  cin >> a.y;
  cin >> a.z;

  cin >> b.x;
  cin >> b.y;
  cin >> b.z;

  cin >> c.x;
  cin >> c.y;
  cin >> c.z;
    

  triangle tri;
  rect bb;

  tri.a = a;
  tri.b = b;
  tri.c = c;



  bb = getBB(tri);

  clr.r = 0.1;
  clr.g = 0.5;
  clr.b = 0.9;

  clra.r = 1;
  clra.g = 0;
  clra.b = 0;

  clrb.r = 0;
  clrb.g = 1;
  clrb.b = 0;

  clrc.r = 0;
  clrc.g = 0;
  clrc.b = 1;




  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);
  double totalarea = areatri(tri.a, tri.b, tri.c);
  cout << totalarea;
  // set a square to be the color above
  for (int i=bb.minx; i < bb.maxx; i++) {
    for (int j=bb.miny; j < bb.maxy; j++) {
    	vertex test;
    	test.x = i;
    	test.y = j;
    	test.z = 0;
    	double alpha = areatri(tri.a, tri.b, test)/totalarea;
    	double beta = areatri(tri.c, tri.a, test)/totalarea;
    	double gamma = 1 - alpha - beta;



    	if (alpha >= 0 && alpha <=1 && beta >= 0 && beta <=1 && gamma >= 0 && gamma <=1) {
    		clrt.r = ((alpha * clrc.r) + (beta * clrb.r) + (gamma * clra.r))/3 ;
    		clrt.g = ((alpha * clrc.g) + (beta * clrb.g) + (gamma * clra.g))/3 ;
    		clrt.b = ((alpha * clrc.b) + (beta * clrb.b) + (gamma * clra.b))/3 ;

    		img.pixel(i,j,clrt);

    	}

    	else
    		img.pixel(i, j, clr);
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

}

double areatri(vertex a, vertex b, vertex c) {
	return ((b.x-a.x)*(c.y - a.y) - (c.x-a.x) * (b.y-a.y))/2;

}

rect getBB(triangle t) {
  rect res;

  // Max X
  if (t.a.x > t.b.x) {
    if (t.a.x > t.c.x) 
      res.maxx = t.a.x;
    else
      res.maxx = t.c.x;
  } else {
    if (t.b.x > t.c.x)
      res.maxx = t.b.x;
    else
      res.maxx = t.c.x;
  }

  //Min X
  if (t.a.x < t.b.x) {
    if (t.a.x < t.c.x) 
      res.minx = t.a.x;
    else
      res.minx = t.c.x;
  } else {
    if (t.b.x < t.c.x)
      res.minx = t.b.x;
    else
      res.minx = t.c.x;
  }

  //Max Y
  if (t.a.y > t.b.y) {
    if (t.a.y > t.c.y) 
      res.maxy = t.a.y;
    else
      res.maxy = t.c.y;
  } else {
    if (t.b.y > t.c.y)
      res.maxy = t.b.y;
    else
      res.maxy = t.c.y;
  }

  //Min Y
  if (t.a.y < t.b.y) {
    if (t.a.y < t.c.y) 
      res.miny = t.a.y;
    else
      res.miny = t.c.y;
  } else {
    if (t.b.y < t.c.y)
      res.miny = t.b.y;
    else
      res.miny = t.c.y;
  }
  
  //Max Z
  if (t.a.z > t.b.z) {
    if (t.a.z > t.c.z) 
      res.maxz = t.a.z;
    else
      res.maxz = t.c.z;
  } else {
    if (t.b.z > t.c.z)
      res.maxz = t.b.z;
    else
      res.maxz = t.c.z;
  }
  
  //Min Z
  if (t.a.z < t.b.z) {
    if (t.a.z < t.c.z) 
      res.minz = t.a.z;
    else
      res.minz = t.c.z;
  } else {
    if (t.b.z < t.c.z)
      res.minz = t.b.z;
    else
      res.minz = t.c.z;
  }
  
  return res;
}
