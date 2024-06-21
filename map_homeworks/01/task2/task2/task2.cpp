#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

static void sum_two_vectors(std::vector<int> &result,
                            const std::vector<int> &v1,
                            const std::vector<int> &v2, int lhs, int rhs) {
  for (int i = lhs; i < rhs; ++i) {
    result[i] = v1[i] + v2[i];
  }
}

int main(int argc, char **argv) {
  system("chcp 65001");
  std::cout << "Количество аппаратных ядер: "
            << std::thread::hardware_concurrency() << "\n\n";
  std::cout << std::setw(19) << "1000" << std::setw(16) << "10000"
            << std::setw(16) << "100000" << std::setw(16) << "1000000"
            << "\n";

  std::vector<int> num_of_threads{1, 2, 4, 8, 16};
  std::vector<int> size_of_vectors{1'000, 10'000, 100'000, 1'000'000};

  std::vector<int> v1;
  std::vector<int> v2;

  for (auto &cnt_thr : num_of_threads) {
    std::cout << cnt_thr << (cnt_thr < 10 ? "  потоков" : " потоков");

    for (auto sz : size_of_vectors) {
      std::vector<int> v1(sz, 1), v2(sz, 2), result(sz);
      std::vector<std::thread> threads(cnt_thr);

      int size_portion = sz / cnt_thr;

      auto start = std::chrono::steady_clock::now();

      for (int j = 0; j < cnt_thr - 1; j++) {
        threads.emplace_back(sum_two_vectors, std::ref(result), std::ref(v1),
                             std::ref(v2), j * size_portion,
                             (j + 1) * size_portion);
      }
      // 1000 не делиться нацело на 16
      threads.emplace_back(sum_two_vectors, std::ref(result), std::ref(v1),
                           std::ref(v2), (cnt_thr - 1) * size_portion,
                           cnt_thr * size_portion + sz % cnt_thr);

      for (auto &t : threads) {
        if (t.joinable())
          t.join();
      }

      auto end = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsed_time = end - start;
      std::cout << std::right << std::setw(14) << std::setprecision(7)
                << elapsed_time.count() << "s";
    }
    std::cout << std::endl;
  }

  return 0;
}
