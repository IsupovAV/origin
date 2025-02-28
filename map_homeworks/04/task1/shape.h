#pragma once
enum class figures { line, sqr, cube, cylynder };

class Shape {
protected:
  struct Coordinate {
    int x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0, x3 = 0, y3 = 0, z3 = 0,
        x4 = 0, y4 = 0, z4 = 0, x5 = 0, y5 = 0, z5 = 0, x6 = 0, y6 = 0, z6 = 0,
        x7 = 0, y7 = 0, z7 = 0, x8 = 0, y8 = 0, z8 = 0;
  };
  double volume = 0.0;
  double square = 0.0;
  double height = 0.0;
  double radius = 0.0;

  Coordinate coord;

public:

  Shape() = default;

  double getVolume() const;
  double getSquare() const;
  double getHeight() const;
  double getRadius() const;

  virtual void shift(int m, int n) {};
  virtual void shift(int m, int n, int k) {};
  virtual void scaleX(int a) {};
  virtual void scaleY(int d) {};
  virtual void scaleZ(int e) {};
  virtual void scale(int s) {};

  Coordinate getCoord();
};

class Line : public Shape {
public:
  Line(int x1, int y1, int x2, int y2);

  void shift(int m, int n) override;
  virtual void scaleX(int a);
  virtual void scaleY(int d);
  virtual void scaleZ(int e);
  virtual void scale(int s);

private:
  void CalcArea();
  void CalcVolume();
};

class Sqr : public Shape {
public:
  Sqr(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

  void shift(int m, int n) override;
  void scaleX(int a) override;
  void scaleY(int d) override;
  void scaleZ(int e) override;
  void scale(int s) override;

private:
  void CalcArea();
  void CalcVolume();
};

class Cube : public Shape {
public:
  Cube(int x1, int y1, int z1, 
    int x2, int y2, int z2, 
    int x3, int y3, int z3, 
    int x4, int y4, int z4, 
    int x5, int y5, int z5, 
    int x6, int y6, int z6, 
    int x7, int y7, int z7, 
    int x8, int y8, int z8);

  void shift(int m, int n, int k) override;
  void scaleX(int a) override;
  void scaleY(int d) override;
  void scaleZ(int e) override;
  void scale(int s) override;

private:
  void CalcArea();
  void CalcVolume();
};

class Circle : public Shape {
public:
  Circle(int x1, int y1, double r);

private:
  void CalcArea();
  void CalcVolume();
};

class Cylinder : public Shape {
public:
  Cylinder(int x1, int y1, double r, double h);

private:
  void CalcArea();
  void CalcVolume();
};


