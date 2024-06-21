#include <chrono>
#include <iostream>
#include <thread>

constexpr int MAX_NUMBER_CLIENTS = 7;
constexpr int QUEUING_TIME = 1; // время постановки в очередь
constexpr int SEVICE_TIME = 2; // время обслуживания

int client_сounter = 0;

void clients_thread() {
  while (client_сounter < MAX_NUMBER_CLIENTS) {
    std::this_thread::sleep_for(std::chrono::seconds(QUEUING_TIME));
    std::cout << "клиент поставлен в очередь, текущее число клиентов: "
              << ++client_сounter << std::endl;
  }
}

void teller_thread() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(SEVICE_TIME));
    if (client_сounter > 0) {
      std::cout << "клиент обслужен, текущее число клиентов: "
                << --client_сounter << std::endl;
    } else {
      std::cout << "все клиенты обслужены, текущее число клиентов: "
                << client_сounter << std::endl;
      break;
    }
  }
}

int main(int argc, char **argv) {

  system("chcp 65001");

  std::thread client(clients_thread); // поток клиентов
  std::thread teller(teller_thread);  // поток оператора

  client.join();
  teller.join();

  return 0;
}