#pragma once

#include "quadrangle.h"

#ifdef PARALLELOGRAM_EXPORTS
#define PARALLELOGRAM_API __declspec(dllexport)
#else
#define PARALLELOGRAM_API __declspec(dllimport)
#endif

// Параллелограмм
class PARALLELOGRAM_API Parallelogram : public Quadrangle {
public:
  Parallelogram(int a, int b, int A, int B);
  std::string get_name() override;
};
