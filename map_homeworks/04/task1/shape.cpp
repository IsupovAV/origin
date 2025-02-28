#define _USE_MATH_DEFINES
#include <iostream>
#include "shape.h"
#include <cmath>

double Shape::getVolume() const { return volume; }
double Shape::getSquare() const { return square; }
double Shape::getHeight() const { return height; }
double Shape::getRadius() const { return radius; }

Shape::Coordinate Shape::getCoord() { return coord; }

// Line
Line::Line(int x1, int y1, int x2, int y2) {
  coord.x1 = x1;
  coord.y1 = y1;
  coord.x2 = x2;
  coord.y2 = y2;
  CalcArea();
  CalcVolume();
}

void Line::shift(int m, int n) {
  coord.x1 += m;
  coord.y1 += n;
  coord.x2 += m;
  coord.y2 += n;
}

void Line::scaleX(int a) {
  coord.x1 *= a;
  coord.x2 *= a;
}

void Line::scaleY(int d) {
  coord.y1 *= d;
  coord.y2 *= d;
}

void Line::scaleZ(int e) {
  coord.z1 *= e;
  coord.z2 *= e;
}

void Line::scale(int s) {
  coord.x1 /= s;
  coord.y1 /= s;
  coord.x2 /= s;
  coord.y2 /= s;
}

void Line::CalcArea() { square = 0.0; }

void Line::CalcVolume() { volume = 0.0; }

// Sqr
Sqr::Sqr(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  coord.x1 = x1;
  coord.y1 = y1;
  coord.x2 = x2;
  coord.y2 = y2;
  coord.x3 = x3;
  coord.y3 = y3;
  coord.x4 = x4;
  coord.y4 = y4;
  CalcArea();
  CalcVolume();
}

void Sqr::shift(int m, int n) {
  coord.x1 += m;
  coord.y1 += n;
  coord.x2 += m;
  coord.y2 += n;
  coord.x3 += m;
  coord.y3 += n;
  coord.x4 += m;
  coord.y4 += n;
}

void Sqr::scaleX(int a) {
  coord.x1 *= a;
  coord.x2 *= a;
  coord.x3 *= a;
  coord.x4 *= a;
}

void Sqr::scaleY(int d) {
  coord.y1 *= d;
  coord.y2 *= d;
  coord.y3 *= d;
  coord.y4 *= d;
}

void Sqr::scaleZ(int e) {
  coord.z1 *= e;
  coord.z2 *= e;
  coord.z3 *= e;
  coord.z4 *= e;
}

void Sqr::scale(int s) {
  coord.x1 /= s;
  coord.y1 /= s;
  coord.x2 /= s;
  coord.y2 /= s;
  coord.x3 /= s;
  coord.y3 /= s;
  coord.x4 /= s;
  coord.y4 /= s;
}

void Sqr::CalcArea() {
  square = pow((coord.x1 - coord.x2), 2) + pow((coord.y1 - coord.y2), 2);
}

void Sqr::CalcVolume() { 
  volume = 0; 
}

// Cube
Cube::Cube(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3,
           int z3, int x4, int y4, int z4, int x5, int y5, int z5, int x6,
           int y6, int z6, int x7, int y7, int z7, int x8, int y8, int z8) {
  coord.x1 = x1;
  coord.y1 = y1;
  coord.z1 = z1;
  coord.x2 = x2;
  coord.y2 = y2;
  coord.z2 = z2;
  coord.x3 = x3;
  coord.y3 = y3;
  coord.z3 = z3;
  coord.x4 = x4;
  coord.y4 = y4;
  coord.z4 = z4;
  coord.x5 = x5;
  coord.y5 = y5;
  coord.z5 = z5;
  coord.x6 = x6;
  coord.y6 = y6;
  coord.z6 = z6;
  coord.x7 = x7;
  coord.y7 = y7;
  coord.z7 = z7;
  coord.x8 = x8;
  coord.y8 = y8;
  coord.z8 = z8;
  CalcArea();
  CalcVolume();
}

void Cube::shift(int m, int n, int k) {
  coord.x1 += m;
  coord.y1 += n;
  coord.z1 += k;
  coord.x2 += m;
  coord.y2 += n;
  coord.z2 += k;
  coord.x3 += m;
  coord.y3 += n;
  coord.z3 += k;
  coord.x4 += m;
  coord.y4 += n;
  coord.z4 += k;
  coord.x5 += m;
  coord.y5 += n;
  coord.z5 += k;
  coord.x6 += m;
  coord.y6 += n;
  coord.z6 += k;
  coord.x7 += m;
  coord.y7 += n;
  coord.z7 += k;
  coord.x8 += m;
  coord.y8 += n;
  coord.z8 += k;
}

void Cube::scaleX(int a) {
  coord.x1 *= a;
  coord.x2 *= a;
  coord.x3 *= a;
  coord.x4 *= a;
  coord.x5 *= a;
  coord.x6 *= a;
  coord.x7 *= a;
  coord.x8 *= a;
}

void Cube::scaleY(int d) {
  coord.y1 *= d;
  coord.y2 *= d;
  coord.y3 *= d;
  coord.y4 *= d;
  coord.y5 *= d;
  coord.y6 *= d;
  coord.y7 *= d;
  coord.y8 *= d;
}

void Cube::scaleZ(int e) {
  coord.z1 *= e;
  coord.z2 *= e;
  coord.z3 *= e;
  coord.z4 *= e;
  coord.z5 *= e;
  coord.z6 *= e;
  coord.z7 *= e;
  coord.z8 *= e;
}

void Cube::scale(int s) {
  coord.x1 /= s;
  coord.y1 /= s;
  coord.z1 /= s;
  coord.x2 /= s;
  coord.y2 /= s;
  coord.z2 /= s;
  coord.x3 /= s;
  coord.y3 /= s;
  coord.z3 /= s;
  coord.x4 /= s;
  coord.y4 /= s;
  coord.z4 /= s;
  coord.x5 /= s;
  coord.y5 /= s;
  coord.z5 /= s;
  coord.x6 /= s;
  coord.y6 /= s;
  coord.z6 /= s;
  coord.x7 /= s;
  coord.y7 /= s;
  coord.z7 /= s;
  coord.x8 /= s;
  coord.y8 /= s;
  coord.z8 /= s;
}

void Cube::CalcArea() {
  square = 6 * (pow((coord.x1 - coord.x2), 2) + pow((coord.y1 - coord.y2), 2));
}

void Cube::CalcVolume() { 
  volume = 2 * (pow((coord.x1 - coord.x2), 2) + pow((coord.y1 - coord.y2), 2));
}

// Circle
Circle::Circle(int x1, int y1, double r) {
  coord.x1 = x1;
  coord.y1 = y1;
  radius = r;
  CalcArea();
  CalcVolume();
}

void Circle::CalcArea() { 
  square = M_PI * radius * radius; 
}

void Circle::CalcVolume() { 
  volume = 0.0;
}

// Cylinder
Cylinder::Cylinder(int x1, int y1, double r, double h) {
  coord.x1 = x1;
  coord.y1 = y1;
  radius = r;
  height = h;
  CalcArea();
  CalcVolume();
}

void Cylinder::CalcArea() { 
  square = 2* M_PI * radius * radius + 2 * M_PI * radius * height;
}

void Cylinder::CalcVolume() { 
  volume = M_PI * radius * radius * height; 
}
