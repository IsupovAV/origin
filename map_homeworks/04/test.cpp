#pragma once
#include "./Catch2/src/catch2/catch_session.hpp"
#include "./Catch2/src/catch2/catch_test_macros.hpp"
#include "Catch2/extras/catch_amalgamated.hpp"
#include "shape.h"
#include <cmath>
#include <iostream>

Line line(1, 1, 3, 3);
Sqr sqr(1, 1, 3, 1, 3, 3, 1, 3);
Cube cube(1, 1, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 3, 3, 1, 3, 3,
            3);
Circle circle(0, 0, 1);
Cylinder cylinder(0, 0, 1., 10.);

// test Line
TEST_CASE("class Shape - test Line", "[testLineShape]") {
  SECTION("coordinates Line") {
    CHECK(line.getCoord().x1 == 1);
    CHECK(line.getCoord().y1 == 1);
    CHECK(line.getCoord().x2 == 3);
    CHECK(line.getCoord().y2 == 3);
  }

  SECTION("Square Line") { CHECK(line.getSquare() == 0.0); }

  SECTION("Volume Line") { CHECK(line.getVolume() == 0.0); }
}

// test Sqr
TEST_CASE("class Shape - test Sqr", "[testSqrShape]") {
  SECTION("coordinates Sqr") {
    CHECK(sqr.getCoord().x1 == 1);
    CHECK(sqr.getCoord().y1 == 1);
    CHECK(sqr.getCoord().x2 == 3);
    CHECK(sqr.getCoord().y2 == 1);
    CHECK(sqr.getCoord().x3 == 3);
    CHECK(sqr.getCoord().y3 == 3);
    CHECK(sqr.getCoord().x4 == 1);
    CHECK(sqr.getCoord().y4 == 3);
  }

  SECTION("Square sqr") { CHECK(sqr.getSquare() == 4.0); }

  SECTION("Volume sqr") { CHECK(sqr.getVolume() == 0.0); }
}

// test Cube
TEST_CASE("class Shape - test Cube", "[testCubeShape]") {
  SECTION("coordinates Cube") {
    CHECK(cube.getCoord().x1 == 1);
    CHECK(cube.getCoord().y1 == 1);
    CHECK(cube.getCoord().z1 == 1);
    CHECK(cube.getCoord().x2 == 3);
    CHECK(cube.getCoord().y2 == 1);
    CHECK(cube.getCoord().z2 == 1);
    CHECK(cube.getCoord().x3 == 3);
    CHECK(cube.getCoord().y3 == 1);
    CHECK(cube.getCoord().z3 == 3);
    CHECK(cube.getCoord().x4 == 1);
    CHECK(cube.getCoord().y4 == 1);
    CHECK(cube.getCoord().z4 == 3);
    CHECK(cube.getCoord().x5 == 1);
    CHECK(cube.getCoord().y5 == 3);
    CHECK(cube.getCoord().z5 == 3);
    CHECK(cube.getCoord().x6 == 1);
    CHECK(cube.getCoord().y6 == 3);
    CHECK(cube.getCoord().z6 == 1);
    CHECK(cube.getCoord().x7 == 3);
    CHECK(cube.getCoord().y7 == 3);
    CHECK(cube.getCoord().z7 == 1);
    CHECK(cube.getCoord().x8 == 3);
    CHECK(cube.getCoord().y8 == 3);
    CHECK(cube.getCoord().z8 == 3);
  }

  SECTION("Square Cube") { CHECK(cube.getSquare() == 24.); }

  SECTION("Volume Cube") { CHECK(cube.getVolume() == 8.); }
}

// test Circle
TEST_CASE("class Shape - test Circle", "[testCircleShape]") {
  SECTION("coordinates Circle") {
    CHECK(circle.getCoord().x1 == 0);
    CHECK(circle.getCoord().y1 == 0);
    CHECK(circle.getRadius() == 1.0);
  }

  SECTION("Square Circle") {
    CHECK(circle.getSquare() == 3.14159265358979312);
  }

  SECTION("Volume Circle") { CHECK(circle.getVolume() == 0.); }
}

// test Cylinder
TEST_CASE("class Shape - test Cylinder", "[testCylinderShape]") {
  SECTION("coordinates Cylinder") {
    CHECK(cylinder.getCoord().x1 == 0);
    CHECK(cylinder.getCoord().y1 == 0);
    CHECK(cylinder.getRadius() == 1.);
    CHECK(cylinder.getHeight() == 10.);
  }

  SECTION("Square Cylinder") {
    CHECK(cylinder.getSquare() == 69.11503837897544145);
  }

  SECTION("Volume Cylinder") {
    CHECK(cylinder.getVolume() == 31.41592653589793116);
  }
}

// transform Line
std::once_flag flag1;
void trLineShift(const int m, const int n) { line.shift(m, n); }
std::once_flag flag2;
void trLineScaleX(const int a) { line.scaleX(a); }
std::once_flag flag3;
void trLineScaleY(const int d) { line.scaleY(d); }
std::once_flag flag4;
void trLineScaleZ(const int e) { line.scaleZ(e); }
std::once_flag flag5;
void trLineScale(const int s) { line.scale(s); }

TEST_CASE("class Transform - test Line", "[testLineTransform]") {
  SECTION("class Transform - test Line") {
    const int m = 1;
    const int n = 2;
    std::call_once(flag1, trLineShift, m, n);

    SECTION("coordinates Line after Shift") {

      CHECK(line.getCoord().x1 == 1 + m);
      CHECK(line.getCoord().y1 == 1 + n);
      CHECK(line.getCoord().x2 == 3 + m);
      CHECK(line.getCoord().y2 == 3 + n);
    }

    SECTION("Square Line after Shift") { CHECK(line.getSquare() == 0.0); }

    SECTION("Volume Line after Shift") { CHECK(line.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Line ScaleX") {
    const int a = 3;
    std::call_once(flag2, trLineScaleX, a);

    SECTION("coordinates Line after ScaleX") {
      CHECK(line.getCoord().x1 == 6);
      CHECK(line.getCoord().y1 == 3);
      CHECK(line.getCoord().x2 == 12);
      CHECK(line.getCoord().y2 == 5);
    }

    SECTION("Square Line after ScaleX") { CHECK(line.getSquare() == 0.0); }

    SECTION("Volume Line after ScaleX") { CHECK(line.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Line ScaleY") {
    const int d = 4;
    std::call_once(flag3, trLineScaleY, d);

    SECTION("coordinates Line after ScaleY") {
      CHECK(line.getCoord().x1 == 6);
      CHECK(line.getCoord().y1 == 12);
      CHECK(line.getCoord().x2 == 12);
      CHECK(line.getCoord().y2 == 20);
    }

    SECTION("Square Line after ScaleY") { CHECK(line.getSquare() == 0.0); }

    SECTION("Volume Line after ScaleY") { CHECK(line.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Line ScaleZ") {
    const int e = 5;
    std::call_once(flag4, trLineScaleZ, e);

    SECTION("coordinates Line after ScaleZ") {
      CHECK(line.getCoord().z1 == 0);
      CHECK(line.getCoord().z2 == 0);
    }

    SECTION("Square Line after ScaleZ") { CHECK(line.getSquare() == 0.0); }

    SECTION("Volume Line after ScaleZ") { CHECK(line.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Line Scale") {
    const int s = 2;
    std::call_once(flag5, trLineScale, s);

    SECTION("coordinates Line after Scale") {
      CHECK(line.getCoord().x1 == 3);
      CHECK(line.getCoord().y1 == 6);
      CHECK(line.getCoord().x2 == 6);
      CHECK(line.getCoord().y2 == 10);
    }

    SECTION("Square Line after Scale") { CHECK(line.getSquare() == 0.0); }

    SECTION("Volume Line after Scale") { CHECK(line.getVolume() == 0.0); }
  }
}

//transform Sqt
std::once_flag flag6;
void trSqrShift(const int m, const int n) { sqr.shift(m, n); }
std::once_flag flag7;
void trSqrScaleX(const int a) { sqr.scaleX(a); }
std::once_flag flag8;
void trSqrScaleY(const int d) { sqr.scaleY(d); }
std::once_flag flag9;
void trSqrScaleZ(const int e) { sqr.scaleZ(e); }
std::once_flag flag10;
void trSqrScale(const int s) { sqr.scale(s); }

TEST_CASE("class Transform - test Sqr", "[testSqrTransform]") {
  SECTION("class Transform - test Sqr") {
    const int m = 1;
    const int n = 2;
    std::call_once(flag6, trSqrShift, m, n);

    SECTION("coordinates Sqr after Shift") {
      CHECK(sqr.getCoord().x1 == 2);
      CHECK(sqr.getCoord().y1 == 3);
      CHECK(sqr.getCoord().x2 == 4);
      CHECK(sqr.getCoord().y2 == 3);
      CHECK(sqr.getCoord().x3 == 4);
      CHECK(sqr.getCoord().y3 == 5);
      CHECK(sqr.getCoord().x4 == 2);
      CHECK(sqr.getCoord().y4 == 5);
    }

    SECTION("Square Sqr after Shift") { CHECK(sqr.getSquare() == 4.0); }

    SECTION("Volume Sqr after Shift") { CHECK(sqr.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Sqr ScaleX") {
    const int a = 3;
    std::call_once(flag7, trSqrScaleX, a);

    SECTION("coordinates Sqr after ScaleX") {
      CHECK(sqr.getCoord().x1 == 6);
      CHECK(sqr.getCoord().y1 == 3);
      CHECK(sqr.getCoord().x2 == 12);
      CHECK(sqr.getCoord().y2 == 3);
      CHECK(sqr.getCoord().x3 == 12);
      CHECK(sqr.getCoord().y3 == 5);
      CHECK(sqr.getCoord().x4 == 6);
      CHECK(sqr.getCoord().y4 == 5);
    }

    SECTION("Square Sqr after ScaleX") { CHECK(sqr.getSquare() == 4.0); }

    SECTION("Volume Sqr after ScaleX") { CHECK(sqr.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Sqr ScaleY") {
    const int d = 4;
    std::call_once(flag8, trSqrScaleY, d);

    SECTION("coordinates Sqr after ScaleY") {
      CHECK(sqr.getCoord().x1 == 6);
      CHECK(sqr.getCoord().y1 == 12);
      CHECK(sqr.getCoord().x2 == 12);
      CHECK(sqr.getCoord().y2 == 12);
      CHECK(sqr.getCoord().x3 == 12);
      CHECK(sqr.getCoord().y3 == 20);
      CHECK(sqr.getCoord().x4 == 6);
      CHECK(sqr.getCoord().y4 == 20);
    }

    SECTION("Square Sqr after ScaleY") { CHECK(sqr.getSquare() == 4.0); }

    SECTION("Volume Sqr after ScaleY") { CHECK(sqr.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Sqr ScaleZ") {
    const int e = 5;
    std::call_once(flag9, trSqrScaleZ, e);

    SECTION("coordinates Sqr after ScaleZ") {
      CHECK(sqr.getCoord().z1 == 0);
      CHECK(sqr.getCoord().z2 == 0);
      CHECK(sqr.getCoord().z3 == 0);
      CHECK(sqr.getCoord().z4 == 0);
    }

    SECTION("Square Sqr after ScaleZ") { CHECK(sqr.getSquare() == 4.0); }

    SECTION("Volume Sqr after ScaleZ") { CHECK(sqr.getVolume() == 0.0); }
  }

  SECTION("class Transform - test Sqr Scale") {
    const int s = 2;
    std::call_once(flag10, trSqrScale, s);

    SECTION("coordinates Sqr after Scale") {
      CHECK(sqr.getCoord().x1 == 3);
      CHECK(sqr.getCoord().y1 == 6);
      CHECK(sqr.getCoord().x2 == 6);
      CHECK(sqr.getCoord().y2 == 6);
      CHECK(sqr.getCoord().x3 == 6);
      CHECK(sqr.getCoord().y3 == 10);
      CHECK(sqr.getCoord().x4 == 3);
      CHECK(sqr.getCoord().y4 == 10);
    }

    SECTION("Square Sqr after Scale") { CHECK(sqr.getSquare() == 4.0); }

    SECTION("Volume Sqr after Scale") { CHECK(sqr.getVolume() == 0.0); }
  }
}

// transform Cube
std::once_flag flag11;
void trCubeShift(const int m, const int n, const int k) {
  cube.shift(m, n, k);
}
std::once_flag flag12;
void trCubeScaleX(const int a) { cube.scaleX(a); }
std::once_flag flag13;
void trCubeScaleY(const int d) { cube.scaleY(d); }
std::once_flag flag14;
void trCubeScaleZ(const int e) { cube.scaleZ(e); }
std::once_flag flag15;
void trCubeScale(const int s) { cube.scale(s); }

TEST_CASE("class Transform - test Cube", "[testCubeTransform]") {
  SECTION("class Transform - test Cube") {
    const int m = 1;
    const int n = 2;
    const int k = 3;

    std::call_once(flag11, trCubeShift, m, n, k);

    SECTION("coordinates Cube after Shift") {
      CHECK(cube.getCoord().x1 == 2);
      CHECK(cube.getCoord().y1 == 3);
      CHECK(cube.getCoord().z1 == 4);
      CHECK(cube.getCoord().x2 == 4);
      CHECK(cube.getCoord().y2 == 3);
      CHECK(cube.getCoord().z2 == 4);
      CHECK(cube.getCoord().x3 == 4);
      CHECK(cube.getCoord().y3 == 3);
      CHECK(cube.getCoord().z3 == 6);
      CHECK(cube.getCoord().x4 == 2);
      CHECK(cube.getCoord().y4 == 3);
      CHECK(cube.getCoord().z4 == 6);
      CHECK(cube.getCoord().x5 == 2);
      CHECK(cube.getCoord().y5 == 5);
      CHECK(cube.getCoord().z5 == 6);
      CHECK(cube.getCoord().x6 == 2);
      CHECK(cube.getCoord().y6 == 5);
      CHECK(cube.getCoord().z6 == 4);
      CHECK(cube.getCoord().x7 == 4);
      CHECK(cube.getCoord().y7 == 5);
      CHECK(cube.getCoord().z7 == 4);
      CHECK(cube.getCoord().x8 == 4);
      CHECK(cube.getCoord().y8 == 5);
      CHECK(cube.getCoord().z8 == 6);
    }

    SECTION("Square Cube after Shift") { CHECK(cube.getSquare() == 24.0); }

    SECTION("Volume Cube after Shift") { CHECK(cube.getVolume() == 8.0); }
  }

  SECTION("class Transform - test Cube ScaleX") {
    const int a = 3;
    std::call_once(flag12, trCubeScaleX, a);

    SECTION("coordinates Cube after ScaleX") {
      CHECK(cube.getCoord().x1 == 6);
      CHECK(cube.getCoord().y1 == 3);
      CHECK(cube.getCoord().z1 == 4);
      CHECK(cube.getCoord().x2 == 12);
      CHECK(cube.getCoord().y2 == 3);
      CHECK(cube.getCoord().z2 == 4);
      CHECK(cube.getCoord().x3 == 12);
      CHECK(cube.getCoord().y3 == 3);
      CHECK(cube.getCoord().z3 == 6);
      CHECK(cube.getCoord().x4 == 6);
      CHECK(cube.getCoord().y4 == 3);
      CHECK(cube.getCoord().z4 == 6);
      CHECK(cube.getCoord().x5 == 6);
      CHECK(cube.getCoord().y5 == 5);
      CHECK(cube.getCoord().z5 == 6);
      CHECK(cube.getCoord().x6 == 6);
      CHECK(cube.getCoord().y6 == 5);
      CHECK(cube.getCoord().z6 == 4);
      CHECK(cube.getCoord().x7 == 12);
      CHECK(cube.getCoord().y7 == 5);
      CHECK(cube.getCoord().z7 == 4);
      CHECK(cube.getCoord().x8 == 12);
      CHECK(cube.getCoord().y8 == 5);
      CHECK(cube.getCoord().z8 == 6);
    }

    SECTION("Square Cube after ScaleX") { CHECK(cube.getSquare() == 24.0); }

    SECTION("Volume Cube after ScaleX") { CHECK(cube.getVolume() == 8.0); }
  }

  SECTION("class Transform - test Cube ScaleY") {
    const int d = 4;
    std::call_once(flag13, trCubeScaleY, d);

    SECTION("coordinates Cube after ScaleY") {
      CHECK(cube.getCoord().x1 == 6);
      CHECK(cube.getCoord().y1 == 12);
      CHECK(cube.getCoord().z1 == 4);
      CHECK(cube.getCoord().x2 == 12);
      CHECK(cube.getCoord().y2 == 12);
      CHECK(cube.getCoord().z2 == 4);
      CHECK(cube.getCoord().x3 == 12);
      CHECK(cube.getCoord().y3 == 12);
      CHECK(cube.getCoord().z3 == 6);
      CHECK(cube.getCoord().x4 == 6);
      CHECK(cube.getCoord().y4 == 12);
      CHECK(cube.getCoord().z4 == 6);
      CHECK(cube.getCoord().x5 == 6);
      CHECK(cube.getCoord().y5 == 20);
      CHECK(cube.getCoord().z5 == 6);
      CHECK(cube.getCoord().x6 == 6);
      CHECK(cube.getCoord().y6 == 20);
      CHECK(cube.getCoord().z6 == 4);
      CHECK(cube.getCoord().x7 == 12);
      CHECK(cube.getCoord().y7 == 20);
      CHECK(cube.getCoord().z7 == 4);
      CHECK(cube.getCoord().x8 == 12);
      CHECK(cube.getCoord().y8 == 20);
      CHECK(cube.getCoord().z8 == 6);
    }

    SECTION("Square Cube after ScaleY") { CHECK(cube.getSquare() == 24.0); }

    SECTION("Volume Cube after ScaleY") { CHECK(cube.getVolume() == 8.0); }
  }

  SECTION("class Transform - test Cube ScaleZ") {
    const int e = 5;
    std::call_once(flag14, trCubeScaleZ, e);

    SECTION("coordinates Cube after ScaleZ") {
      CHECK(cube.getCoord().x1 == 6);
      CHECK(cube.getCoord().y1 == 12);
      CHECK(cube.getCoord().z1 == 20);
      CHECK(cube.getCoord().x2 == 12);
      CHECK(cube.getCoord().y2 == 12);
      CHECK(cube.getCoord().z2 == 20);
      CHECK(cube.getCoord().x3 == 12);
      CHECK(cube.getCoord().y3 == 12);
      CHECK(cube.getCoord().z3 == 30);
      CHECK(cube.getCoord().x4 == 6);
      CHECK(cube.getCoord().y4 == 12);
      CHECK(cube.getCoord().z4 == 30);
      CHECK(cube.getCoord().x5 == 6);
      CHECK(cube.getCoord().y5 == 20);
      CHECK(cube.getCoord().z5 == 30);
      CHECK(cube.getCoord().x6 == 6);
      CHECK(cube.getCoord().y6 == 20);
      CHECK(cube.getCoord().z6 == 20);
      CHECK(cube.getCoord().x7 == 12);
      CHECK(cube.getCoord().y7 == 20);
      CHECK(cube.getCoord().z7 == 20);
      CHECK(cube.getCoord().x8 == 12);
      CHECK(cube.getCoord().y8 == 20);
      CHECK(cube.getCoord().z8 == 30);
    }

    SECTION("Square Cube after ScaleZ") { CHECK(cube.getSquare() == 24.0); }

    SECTION("Volume Cube after ScaleZ") { CHECK(cube.getVolume() == 8.0); }
  }

  SECTION("class Transform - test Cube Scale") {
    const int s = 2;
    std::call_once(flag15, trCubeScale, s);

    SECTION("coordinates Cube after Scale") {
      CHECK(cube.getCoord().x1 == 3);
      CHECK(cube.getCoord().y1 == 6);
      CHECK(cube.getCoord().z1 == 10);
      CHECK(cube.getCoord().x2 == 6);
      CHECK(cube.getCoord().y2 == 6);
      CHECK(cube.getCoord().z2 == 10);
      CHECK(cube.getCoord().x3 == 6);
      CHECK(cube.getCoord().y3 == 6);
      CHECK(cube.getCoord().z3 == 15);
      CHECK(cube.getCoord().x4 == 3);
      CHECK(cube.getCoord().y4 == 6);
      CHECK(cube.getCoord().z4 == 15);
      CHECK(cube.getCoord().x5 == 3);
      CHECK(cube.getCoord().y5 == 10);
      CHECK(cube.getCoord().z5 == 15);
      CHECK(cube.getCoord().x6 == 3);
      CHECK(cube.getCoord().y6 == 10);
      CHECK(cube.getCoord().z6 == 10);
      CHECK(cube.getCoord().x7 == 6);
      CHECK(cube.getCoord().y7 == 10);
      CHECK(cube.getCoord().z7 == 10);
      CHECK(cube.getCoord().x8 == 6);
      CHECK(cube.getCoord().y8 == 10);
      CHECK(cube.getCoord().z8 == 15);
    }

    SECTION("Square Cube after Scale") { CHECK(cube.getSquare() == 24.0); }

    SECTION("Volume Cube after Scale") { CHECK(cube.getVolume() == 8.0); }
  }
}

int main(int argc, char *argv[]) { 
  return Catch::Session().run(argc, argv); 
}