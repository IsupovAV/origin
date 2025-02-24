// task2.cpp : Прогресс бар

#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std::chrono_literals;

int random_number(int range) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, range);

  return dist(gen);
}

COORD get_cursor_position() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
  GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);
  return bufferInfo.dwCursorPosition;
}

void set_cursor_position(int x, int y) {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD position;
  position.X = x;
  position.Y = y;
  SetConsoleCursorPosition(consoleHandle, position);
}

std::chrono::steady_clock::time_point process_time() {
  int sleep = random_number(500);
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
  return std::chrono::high_resolution_clock::now();
}
  
std::mutex mtx;
int constexpr begin_progress_line = 5;

void calc_simulator(int duration, int thread_num, int col_time) {
  double elapsed_time = 0;
  int count = 0;
  int line = thread_num + begin_progress_line;
  int col = 0;
  mtx.lock();
  set_cursor_position(col, line);
  std::cout << thread_num << '\t'<< std::this_thread::get_id()
            << "\t";
  col = get_cursor_position().X;
  mtx.unlock();
  for(count = 0; count < duration; ++count) {
    auto start_time = std::chrono::high_resolution_clock::now();
    mtx.lock();
    set_cursor_position(col, line);
    std::cout << "█";
    if (count == duration - 1) {
      set_cursor_position(col_time, line);
      std::cout << elapsed_time / 1000. << 's';
    }
    col = get_cursor_position().X;
    mtx.unlock();
    auto end_time = process_time();
    elapsed_time =
        elapsed_time + std::chrono::duration_cast<std::chrono::milliseconds>(
                           end_time - start_time)
                           .count();
  }
}

int main(int argc, char **argv) {
  system("chcp 65001");

  int treads_quantity{1};
  int calc_duration{1};
  std::cout << "Enter the number of threads: ";
  std::cin >> treads_quantity;
  std::cout << "Enter the number of iterations: ";
  std::cin >> calc_duration;
  std::cout << std::endl;
  std::string number_space = std::string(calc_duration, ' ');
  std::cout << "#\tid\tPrograss Bar" << number_space;
  int time_column = get_cursor_position().X;
  std::cout << "Time\n";

  std::vector<std::thread> threads;

  for (int i = 0; i < treads_quantity; ++i) {

    threads.emplace_back(calc_simulator, calc_duration, i, time_column);
  }

  for (auto &thread : threads) {
    thread.join();
  }
  
  set_cursor_position(0, begin_progress_line + treads_quantity);
  
  return 0;
}