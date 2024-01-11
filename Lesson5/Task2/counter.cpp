#include "counter.h"

Counter::Counter(): count_(1) {
}

Counter::Counter(const int new_count)
  : count_(new_count){
}

void Counter::Inc() {
  ++count_;
}

void Counter::Dec() {
  --count_;
}

int Counter::GetCount() const {
  return count_;
}



