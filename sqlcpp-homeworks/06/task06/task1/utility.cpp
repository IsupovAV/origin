#include "task1.h"

using namespace std;

bool create_database(const string &db_name) {
  string connection_string = "host=localhost "
                             "port=5432 "
                             "dbname= " + db_name +
                             " user=postgres "
                             "password=753111";
  bool base_exist = true;
  try {
    unique_ptr<dbo::backend::Postgres> postgres =
        make_unique<dbo::backend::Postgres>(connection_string);
    cout << "database: " << db_name << " already exists." << endl;
  } catch (const exception &ex) {
    auto start = connection_string.find(db_name);
    connection_string.replace(start, db_name.length(), "postgres"); 
    unique_ptr<dbo::backend::Postgres> postgres =
        make_unique<dbo::backend::Postgres>(connection_string);
    postgres->executeSql("create database " + db_name + ";");
    cout << "database: " << db_name << " created." << endl;
    base_exist = false;
  }

  return base_exist;
}

// При генерации данных таблиц использовал сервис https://www.mockaroo.com/
// очень интересная отдельная задача, особо впечатлил AI сервиса.
void initial_filling(dbo::Session &s) {
  try {
    dbo::Transaction t{s};
    // заполняем таблицу publisher
    auto p1 = unique_ptr<Publisher>(new Publisher{"Penguin Random House"});
    auto p2 = unique_ptr<Publisher>(new Publisher{"HarperCollins"});
    auto p3 = unique_ptr<Publisher>(new Publisher{"Simon & Schuster"});
    auto p4 = unique_ptr<Publisher>(new Publisher{"Macmillan Publishers"});

    auto pp1 = s.add<Publisher>(move(p1));
    auto pp2 = s.add<Publisher>(move(p2));
    auto pp3 = s.add<Publisher>(move(p3));
    auto pp4 = s.add<Publisher>(move(p4));

    // заполняем таблицу book
    auto b1 = unique_ptr<Book>(new Book{"The Midnight Garden", pp1});
    auto b2 = unique_ptr<Book>(new Book{"Whispers in the Dark", pp1});
    auto b3 = unique_ptr<Book>(new Book{"Echoes of the Past", pp2});
    auto b4 = unique_ptr<Book>(new Book{"The Enchanted Forest", pp4});
    auto b5 = unique_ptr<Book>(new Book{"Lost in Time", pp3});
    auto b6 = unique_ptr<Book>(new Book{"The Secret Keepers", pp1});
    auto b7 = unique_ptr<Book>(new Book{"Shadows of the Night", pp1});
    auto b8 = unique_ptr<Book>(new Book{"The Forgotten City", pp2});
    auto b9 = unique_ptr<Book>(new Book{"Mysteries of the Moon", pp1});

    auto pb1 = s.add<Book>(move(b1));
    auto pb2 = s.add<Book>(move(b2));
    auto pb3 = s.add<Book>(move(b3));
    auto pb4 = s.add<Book>(move(b4));
    auto pb5 = s.add<Book>(move(b5));
    auto pb6 = s.add<Book>(move(b6));
    auto pb7 = s.add<Book>(move(b7));
    auto pb8 = s.add<Book>(move(b8));
    auto pb9 = s.add<Book>(move(b9));

    // заполняем таблицу shop
    auto sh1 = unique_ptr<Shop>(new Shop{"Book Haven"});
    auto sh2 = unique_ptr<Shop>(new Shop{"Novel Nook"});
    auto sh3 = unique_ptr<Shop>(new Shop{"Literary Lounge"});

    auto psh1 = s.add<Shop>(move(sh1));
    auto psh2 = s.add<Shop>(move(sh2));
    auto psh3 = s.add<Shop>(move(sh3));

    // заполняем таблицу stock
    auto st1 = unique_ptr<Stock>(new Stock{pb7, psh3, 1});
    auto st2 = unique_ptr<Stock>(new Stock{pb6, psh2, 2});
    auto st3 = unique_ptr<Stock>(new Stock{pb3, psh2, 2});
    auto st4 = unique_ptr<Stock>(new Stock{pb5, psh3, 3});
    auto st5 = unique_ptr<Stock>(new Stock{pb9, psh1, 5});
    auto st6 = unique_ptr<Stock>(new Stock{pb1, psh3, 4});
    auto st7 = unique_ptr<Stock>(new Stock{pb2, psh1, 2});
    auto st8 = unique_ptr<Stock>(new Stock{pb1, psh2, 3});
    auto st9 = unique_ptr<Stock>(new Stock{pb4, psh1, 5});
    auto st10 = unique_ptr<Stock>(new Stock{pb6, psh1, 7});
    auto st11 = unique_ptr<Stock>(new Stock{pb8, psh1, 1});
    auto st12 = unique_ptr<Stock>(new Stock{pb5, psh1, 2});

    auto pst1 = s.add<Stock>(move(st1));
    auto pst2 = s.add<Stock>(move(st2));
    auto pst3 = s.add<Stock>(move(st3));
    auto pst4 = s.add<Stock>(move(st4));
    auto pst5 = s.add<Stock>(move(st5));
    auto pst6 = s.add<Stock>(move(st6));
    auto pst7 = s.add<Stock>(move(st7));
    auto pst8 = s.add<Stock>(move(st8));
    auto pst9 = s.add<Stock>(move(st9));
    auto pst10 = s.add<Stock>(move(st10));
    auto pst11 = s.add<Stock>(move(st11));
    auto pst12 = s.add<Stock>(move(st12));

    // заполняем таблицу sale
    auto sl1 = unique_ptr<Sale>(new Sale{121.25, "2024-01-30", pst8, 1});
    auto sl2 = unique_ptr<Sale>(new Sale{70.35, "2023-02-14", pst7, 2});
    auto sl3 = unique_ptr<Sale>(new Sale{111.80, "2022-11-22", pst3, 1});
    auto sl4 = unique_ptr<Sale>(new Sale{122.57, "2024-05-12", pst6, 1});
    auto sl5 = unique_ptr<Sale>(new Sale{121.93, "2024-05-12", pst12, 1});
    auto sl6 = unique_ptr<Sale>(new Sale{97.64, "2022-03-15", pst11, 1});
    auto sl7 = unique_ptr<Sale>(new Sale{110.00, "2022-11-22", pst6, 2});
    auto sl8 = unique_ptr<Sale>(new Sale{146.52, "2022-03-15", pst5, 2});
    auto sl9 = unique_ptr<Sale>(new Sale{36.39, "2023-04-30", pst4, 2});
    auto sl10 = unique_ptr<Sale>(new Sale{74.67, "2022-01-05", pst12, 1});
    auto sl11 = unique_ptr<Sale>(new Sale{72.27, "2023-12-25", pst10, 6});
    auto sl12 = unique_ptr<Sale>(new Sale{100.92, "2022-11-22", pst5, 2});

    auto psl1 = s.add<Sale>(move(sl1));
    auto psl2 = s.add<Sale>(move(sl2));
    auto psl3 = s.add<Sale>(move(sl3));
    auto psl4 = s.add<Sale>(move(sl4));
    auto psl5 = s.add<Sale>(move(sl5));
    auto psl6 = s.add<Sale>(move(sl6));
    auto psl7 = s.add<Sale>(move(sl7));
    auto psl8 = s.add<Sale>(move(sl8));
    auto psl9 = s.add<Sale>(move(sl9));
    auto psl10 = s.add<Sale>(move(sl10));
    auto psl11 = s.add<Sale>(move(sl11));
    auto psl12 = s.add<Sale>(move(sl12));

    t.commit();

    cout << "the initial filling of the tables is complete." << endl;

  } catch (const exception &ex) {
    cout << "exception happened: " << ex.what() << endl;
  }
}
