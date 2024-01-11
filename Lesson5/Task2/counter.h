#pragma once

class Counter {
public:
  Counter(int new_count);
  Counter();
  void Inc();
  void Dec();
  int GetCount() const;

private:
  int count_;
};




