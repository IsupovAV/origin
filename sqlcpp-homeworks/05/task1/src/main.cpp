#include "db_connector.h"
#include <iostream>
#include <pqxx/pqxx>

void create_database(const std::string &dbname) {
  try {
    const std::string str_query =
        "CREATE DATABASE " + dbname + " ENCODING 'UTF8' TEMPLATE template1;";

    pqxx::connection con("user=postgres password=753111 host=localhost "
                         "port=5432 dbname=postgres");

    pqxx::nontransaction query(con, ""); //<--- ключевой момент

    // операция создания базы должна быть "не транкзационной"
    pqxx::result res = query.exec(str_query);
    std::cout << dbname << " database successfully created" << std::endl;

  } catch (const pqxx::sql_error &e) {
    std::cerr << "problem: " << e.what() << std::endl;
  }
}

void PrintFindResult(const std::vector<Client> &res) { 
  std::cout << "result of FindClient" << '\n';
  for (const auto &c : res) {
    std::cout << c.first_name << ' ' << c.last_name << c.email << ' ' << c.phone
              << '\n';
  }
}


int main() {
  system("chcp 65001");

  // Создать базу данных task1
  const std::string db_name = "task1";
  create_database(db_name);

  // Подключиться к базе db_name
  std::string connection_string = "host=localhost port=5432 dbname=" + db_name +
                                  " user=postgres password=753111";
  DBConnector db_connector(connection_string);

  db_connector.CreateTables(); // создать таблицы
  db_connector.FillBeginData(); // заполнить некоторыми начальными данными

  db_connector.ShowDB(); // Показать как это выглядит 

  // Добавить клиента
  db_connector.AddClient("Ivan", "Ivanov", "IvanIvanov1999@gmail.com",
                         "+7-905-982-5115");
  // Добавить телефон
  db_connector.AddPhoneNumber("Ivan", "Ivanov", "+7-923-586-4514");
  db_connector.AddPhoneNumber("Ivan", "Ivanov", "+7-909-111-1234");

  db_connector.ShowDB();  // Показать что получилось

  db_connector.UpdateClientsData(6, "Иван", "Иванов", "Ivanov@mail.ru");
  db_connector.ShowDB(); // Показать что получилось

  db_connector.DeleteClientsPhone(6, "+7-909-111-1234");
  db_connector.ShowDB(); // Показать что получилось

  db_connector.DeleteClientByID(6);
  db_connector.ShowDB(); // Показать что получилось

  auto res = db_connector.FindClient("Doloritas");
  PrintFindResult(res);
  std::cout << std::endl;

  res = db_connector.FindClient(5);
  PrintFindResult(res);
  std::cout << std::endl;

  res = db_connector.FindClient("+86 (405) 754-4327");
  PrintFindResult(res);
  std::cout << std::endl;

  return 0;
}
