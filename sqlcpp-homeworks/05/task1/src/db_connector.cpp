#include "db_connector.h"

DBConnector::DBConnector(const std::string &connection_string)
    : con_(connection_string) {
  std::cout << "database connection successful" << std::endl;
}

void DBConnector::CreateTables() {
  try {
    pqxx::work w(con_);
    w.exec(
        R"(CREATE TABLE IF NOT EXISTS clients
          (
            client_id SERIAL PRIMARY KEY,
	          first_name VARCHAR(100) NOT NULL,
            last_name VARCHAR(100) NOT NULL,
	          email VARCHAR(150) NOT NULL UNIQUE
          );
          CREATE TABLE IF NOT EXISTS phones
          (
            phone_id SERIAL PRIMARY KEY,
	          phone_number VARCHAR(50) NOT NULL UNIQUE,
	          client_id INT REFERENCES clients(client_id) NOT NULL
          );
      )");
    w.commit();
    std::cout << "tables are successfully created" << std::endl;
  } catch (const std::exception &ex) {
    std::cerr << "error happened: " << ex.what() << std::endl;
  }
}

void DBConnector::FillBeginData() {
  try {
    pqxx::work w(con_);
    w.exec("insert into clients (first_name, last_name, email) "
           "values ('Doloritas', 'Wheelton', 'dwheelton0@ovh.net');");
    w.exec("insert into clients (first_name, last_name, email) "
           "values ('Wilmette', 'Gauden', 'wgauden1@usnews.com');");
    w.exec("insert into clients (first_name, last_name, email) "
           "values ('Roderigo', 'McMichell', 'rmcmichell2@cbc.ca');");
    w.exec("insert into clients (first_name, last_name, email) "
           "values ('Beverlie', 'Privost', 'bprivost3@hibu.com');");
    w.exec("insert into clients (first_name, last_name, email) "
           "values ('Maje', 'Gallaher', 'mgallaher4@skype.com');");

    w.exec("insert into phones (phone_number, client_id) values ("
           "'+7 (571) 735-8435', 1);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+62 (588) 709-6363', 4);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+375 (849) 383-2621', 5);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+55 (910) 878-6719', 1);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+86 (405) 754-4327', 3);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+86 (823) 356-8024', 4);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+62 (377) 116-6713', 1);");
    w.exec("insert into phones (phone_number, client_id) values ("
           "'+62 (581) 284-1623', 5);");
    w.commit();
  } catch (const std::exception &ex) {
    std::cerr << "error happened: " << ex.what() << std::endl;
  }
}

void DBConnector::AddClient(const std::string &fname, const std::string &lname,
                            const std::string &em, const std::string phone) {
  try {
    pqxx::work trn(con_);
    pqxx::result insres =
        trn.exec_params("INSERT INTO clients(first_name, last_name, email) "
                        "VALUES ($1, $2, $3) RETURNING client_id;",
                        fname, lname, em);
    if (!insres.empty()) {
      int client_id = insres[0][0].as<int>();
      trn.exec_params(
          "INSERT INTO phones(phone_number, client_id) VALUES ($1, $2);", phone,
          client_id);
      trn.commit();
      std::cout << "client added with client_id: " << client_id << std::endl;
    } else {
      trn.abort();
      std::cerr << "failed to add client" << std::endl;
    }
  } catch (const std::exception &ex) {
    std::cerr << "error happened: " << ex.what() << std::endl;
  }
}

void DBConnector::AddPhoneNumber(const std::string &fname,
                                 const std::string &lname,
                                 const std::string phone) {
  try {
    pqxx::work trn(con_);
    pqxx::result insres = trn.exec_params("SELECT client_id FROM clients WHERE "
                                          "first_name = $1 AND last_name = $2;",
                                          fname, lname);
    if (!insres.empty()) {
      int client_id = insres[0][0].as<int>();
      trn.exec_params(
          "INSERT INTO phones(phone_number, client_id) VALUES ($1, $2);", phone,
          client_id);
      trn.commit();
      std::cout << "phone number added for customer with client_id: "
                << client_id << std::endl;
    } else {
      trn.abort();
      std::cerr << "client " << fname << " " << lname << " not found"
                << std::endl;
    }
  } catch (const std::exception &ex) {
    std::cerr << "error happened: " << ex.what() << std::endl;
  }
}

void DBConnector::UpdateClientsData(const int client_id,
                                    const std::string &new_fname,
                                    const std::string &new_lname,
                                    const std::string &new_email) {

  try {
    pqxx::work trn(con_);
    pqxx::result updres = trn.exec_params(
        "SELECT client_id FROM clients WHERE client_id = $1;", client_id);
    if (!updres.empty()) {
      trn.exec_params("UPDATE clients SET first_name = $1, last_name = $2, "
                      "email = $3 WHERE client_id = $4;",
                      new_fname, new_lname, new_email, client_id);
      trn.commit();
      std::cout << "client updated" << std::endl;
    } else {
      trn.abort();
      std::cerr << "client with id: " << client_id << " not found" << std::endl;
    }
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void DBConnector::DeleteClientsPhone(int client_id,
                                     const std::string &phone_number) {
  try {
    pqxx::work trn(con_);
    pqxx::result delres = trn.exec_params(
        "SELECT client_id FROM clients WHERE client_id = $1;", client_id);
    if (!delres.empty()) {
      trn.exec_params(
          "DELETE FROM phones WHERE client_id = $1 AND phone_number = $2;",
          client_id, phone_number);
      trn.commit();
      std::cout << "phone " << phone_number << " deleted "
                << "for client_id: " << client_id << std::endl;
    } else {
      trn.abort();
      std::cerr << "client not found: " << client_id << std::endl;
    }
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void DBConnector::DeleteClientByID(int client_id) {
  try {
    pqxx::work trn(con_);
    pqxx::result res =
        trn.exec_params("SELECT client_id, first_name, last_name "
                        "FROM clients WHERE client_id = $1;",
                        client_id);
    if (!res.empty()) {
      std::string fname = res[0][1].as<std::string>();
      std::string lname = res[0][2].as<std::string>();
      trn.exec_params("DELETE FROM phones WHERE client_id = $1;", client_id);
      trn.exec_params("DELETE FROM clients WHERE client_id = $1;", client_id);
      trn.commit();
      std::cout << "client deleted: " << client_id << " " << fname << " "
                << lname << std::endl;
    } else {
      trn.abort();
      std::cerr << "client not found: " << client_id << std::endl;
    }
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}

std::vector<Client> DBConnector::FindClient(const field_type &field) {
  std::vector<Client> result;
  try {
    pqxx::work trn(con_);
    pqxx::result res;
    if (holds_alternative<std::string>(field)) {
      std::string fi = get<std::string>(field);
      res = trn.exec_params(
          "SELECT  clients.client_id, first_name, last_name, email, phone_number "
          "FROM clients "
          "LEFT JOIN public.phones on public.clients.client_id = "
          "public.phones.client_id "
          "WHERE clients.first_name = $1 OR clients.last_name = $1 "
          "OR clients.email = $1 "
          "OR phones.phone_number = $1;",
          fi);
    } else {
      int fi = get<int>(field);
      res = trn.exec_params(
          "SELECT  clients.client_id, first_name, last_name, email, phone_number "
          "FROM clients "
          "LEFT JOIN public.phones on public.clients.client_id = "
          "public.phones.client_id "
          "WHERE clients.client_id = $1;",
          fi);
    }
    trn.commit();
    for (const auto &row : res) {
      Client client;
      client.first_name = row["first_name"].as<std::string>();
      client.last_name = row["last_name"].as<std::string>();
      client.email = row["email"].as<std::string>();
      client.phone = row["phone_number"].as<std::string>();
      result.push_back(client);
    }

  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }

  return result;
}

void DBConnector::ShowDB() {
  pqxx::transaction trn(con_);

  std::cout << "\nTables database " << con_.dbname() << std::endl;

  pqxx::result tables =
      trn.exec("SELECT table_name FROM information_schema.tables WHERE "
               "table_schema='public';");

  for (const auto &row : tables) {
    std::string table_name = row[0].as<std::string>();

    std::string query = "SELECT * FROM " + table_name;
    pqxx::result data = trn.exec(query);

    std::cout << "table: " << table_name << std::endl;
    for (const auto &row : data) {
      for (const auto &field : row) {
        std::cout << field.c_str() << "  ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
