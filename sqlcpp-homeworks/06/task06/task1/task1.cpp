#include "task1.h"
#include <cstdlib>
#include <set>

using namespace std;

void create_and_fill(const string &db_name) {
  if (!create_database(db_name)) { // создали базу данных задания

    try {
      string connection_string = "host=localhost "
                                 "port=5432 "
                                 "dbname=" +
                                 db_name +
                                 " user=postgres "
                                 "password=753111";

      unique_ptr<dbo::backend::Postgres> postgres =
          make_unique<dbo::backend::Postgres>(connection_string);

      dbo::Session ses;
      ses.setConnection(std::move(postgres));
      ses.mapClass<Publisher>("publisher");
      ses.mapClass<Book>("book");
      ses.mapClass<Shop>("shop");
      ses.mapClass<Stock>("stock");
      ses.mapClass<Sale>("sale");
      ses.createTables();   // создал таблицы
      initial_filling(ses); // заполнил
    } catch (const exception &ex) {
      cout << "exception happened: " << ex.what() << endl;
    }
  }
}

// Для первоначального показа, имеющихся в базе издателей
void show_publishers(const string& db_name) {
  try {
    string connection_string = "host=localhost "
                               "port=5432 "
                               "dbname=" +
                               db_name +
                               " user=postgres "
                               "password=753111";

    unique_ptr<Wt::Dbo::backend::Postgres> postgres =
        make_unique<Wt::Dbo::backend::Postgres>(connection_string);
    dbo::Session ses;

    ses.setConnection(std::move(postgres));
    ses.mapClass<Publisher>("publisher");
    ses.mapClass<Book>("book");
    ses.mapClass<Shop>("shop");
    ses.mapClass<Stock>("stock");
    ses.mapClass<Sale>("sale");
    dbo::Transaction t{ses};


    dbo::collection<dbo::ptr<Publisher>> pubs = ses.find<Publisher>();
    cout << "\npublishers in database:" << endl;
    for (const auto &pub : pubs) {
      cout << pub->name << " has id = " << pub.id() << endl;
    }
    t.commit();
  } catch (const exception &ex) {
    cout << "exception happened: " << ex.what() << endl;
  }  
}

void show_result(const string &db_name, const string &field) {
  try {
    string connection_string = "host=localhost "
                               "port=5432 "
                               "dbname=" +
                               db_name +
                               " user=postgres "
                               "password=753111";

    unique_ptr<Wt::Dbo::backend::Postgres> postgres =
        make_unique<Wt::Dbo::backend::Postgres>(connection_string);
    dbo::Session ses;

    ses.setConnection(std::move(postgres));
    ses.mapClass<Publisher>("publisher");
    ses.mapClass<Book>("book");
    ses.mapClass<Shop>("shop");
    ses.mapClass<Stock>("stock");
    ses.mapClass<Sale>("sale");
    dbo::Transaction t{ses};

    dbo::ptr<Publisher> pub;
    if (field.find_first_not_of("0123456789") == field.npos) {
      int id = atoi(field.c_str());
      pub = ses.find<Publisher>().where("id = ?").bind(id); // ищем по id
    } else {
      pub = ses.find<Publisher>().where("name = ?").bind(field); // ищем по наименованию
    }

    if (pub) {
      set<string> result;
      dbo::collection<dbo::ptr<Shop>> shops = ses.find<Shop>();
      cout << "found a publisher: " << pub->name << " with id: " << pub.id()
           << endl;
      for (const auto &book : pub->books) {
        for (const auto &stock : book->stocks) {
          result.emplace(ses.query<string>("SELECT name FROM shop")
                            .where("id = ?")
                            .bind(stock->shop.id()));
        }
      }
      
      cout << "the publisher: " << pub->name << " books are sold in shops: " << endl;
      for (const auto &e : result) {
        cout << e << endl;
      }
      cout << endl;
    } else {
      cout << "publisher: " << field << " not found." << endl;
    }

    t.commit();
  } catch (const exception &ex) {
    cout << "exception happened: " << ex.what() << endl;
  }
}

int main() {
  system("chcp 65001");

  const string db_name = "task6";
  create_and_fill(db_name);


  string field = "";
  show_publishers(db_name);
  cout << endl;
  std::cout << "Input id or name publisher (q for exit)" << endl;
  // наименование издателя может состоять из нескольких слов
  getline(cin, field);    
  while (field != "q") {
    show_result(db_name, field);
    getline(cin, field);
  }

  return 0;
}
