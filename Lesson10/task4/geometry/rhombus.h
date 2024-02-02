#pragma once

#include "parallelogram.h"

#ifdef RHOMBUS_EXPORTS
#define RHOMBUS_API __declspec(dllexport)
#else
#define RHOMBUS_API __declspec(dllimport)
#endif

// Ромб
class RHOMBUS_API Rhombus : public Parallelogram {
public:
  Rhombus(int a, int A, int B);
  std::string get_name() override;
};
