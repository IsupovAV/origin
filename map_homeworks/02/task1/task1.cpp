// task1.cpp: Атомарная очередь клиентов
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

constexpr int MAX_NUMBER_CLIENTS = 7;
constexpr int QUEUING_TIME = 1; // время постановки в очередь (в сек)
constexpr int SEVICE_TIME = 2;  // время обслуживания (в сек)

std::atomic<bool> clients_is_work{
    true}; // признак, что clients_thread не закончил работу

void print_counter(const std::atomic<int> &counter) {
  std::cout << "текущее число клиентов : "
            << counter.load(std::memory_order_relaxed) << '\n';
}

void clients_thread(std::atomic<int> &counter) {
  while (counter.load(std::memory_order_relaxed) < MAX_NUMBER_CLIENTS) {
    std::this_thread::sleep_for(std::chrono::seconds(QUEUING_TIME));
    counter.fetch_add(1, std::memory_order_relaxed);
    std::cout << "клиент поставлен в очередь, ";
    print_counter(counter);
  }
  clients_is_work.store(!clients_is_work.load());
}

void teller_thread(std::atomic<int> &counter) {
  while (counter.load(std::memory_order_relaxed) > 0 || clients_is_work) {
    std::this_thread::sleep_for(std::chrono::seconds(SEVICE_TIME));
    counter.fetch_sub(1, std::memory_order_relaxed);
    std::cout << "клиент обслужен, ";

    print_counter(counter);
  }
}

int main(int argc, char **argv) {

  system("chcp 65001");

  std::atomic<int> client_сounter{0};

  std::thread client(clients_thread,
                     std::ref(client_сounter)); // поток клиентов

  std::thread teller(teller_thread,
                     std::ref(client_сounter)); // поток операциониста
  client.join();
  teller.join();

  std::cout << "Все клиенты обслужены" << std::endl;

  return 0;
}