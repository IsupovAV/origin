#pragma once

#include <pqxx/pqxx>
#include <exception>
#include <iostream>
#include <iomanip>
#include <set>
#include <string>
#include <variant>

struct Client {
  std::string first_name;
  std::string last_name;
  std::string email;
  std::string phone;
};

using field_type = std::variant<std::string, int>;

class DBConnector {
public:
  DBConnector(const std::string &string_connection);
  void CreateTables();
  void FillBeginData();

  void AddClient(const std::string &fname, const std::string &lname,
                 const std::string &em, const std::string phone);
  void AddPhoneNumber(const std::string &fname, const std::string &lname,
                      const std::string phone);
  void UpdateClientsData(const int client_id, const std::string &new_fname,
                         const std::string &new_lname,
                         const std::string &new_email);
  void DeleteClientsPhone(int client_id, const std::string& phone_number);
  void DeleteClientByID(int client_id);
  std::vector<Client> FindClient(const  field_type &field);
  void ShowDB();

private:
  pqxx::connection con_;
};

