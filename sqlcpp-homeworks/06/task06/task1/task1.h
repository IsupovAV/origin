#pragma once

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <iostream>
#include <string>

namespace dbo = Wt::Dbo;

class Book;
class Stock;
class Sale;

class Publisher {
public:
  std::string name = "";
  dbo::collection<dbo::ptr<Book>> books;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, books, dbo::ManyToOne, "publisher");
  }
};

class Book {
public:
  std::string title = "";
  dbo::ptr<Publisher> publisher;
  dbo::collection<dbo::ptr<Stock>> stocks;

  template <class Action> void persist(Action &a) {
    dbo::field(a, title, "title");
    dbo::belongsTo(a, publisher, "publisher");
    dbo::hasMany(a, stocks, dbo::ManyToOne, "book");
  }
};

class Shop {
public:
  std::string name = "";
  dbo::collection<dbo::ptr<Stock>> stocks;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, stocks, dbo::ManyToOne, "shop");
  }
};

class Stock {
public:
  dbo::ptr<Book> book;
  dbo::ptr<Shop> shop;
  int count = 0;
  dbo::collection<dbo::ptr<Sale>> sales;

  template <class Action> void persist(Action &a) {
    dbo::field(a, count, "count");
    dbo::belongsTo(a, book, "book");
    dbo::belongsTo(a, shop, "shop");
    dbo::hasMany(a, sales, dbo::ManyToOne, "stock");
  }
};

class Sale {
public:
  double price = 0.0;
  std::string date_sale = "";
  dbo::ptr<Stock> stock;
  int count = 0;

  template <class Action> void persist(Action &a) {
    dbo::field(a, price, "price");
    dbo::field(a, date_sale, "date_sale");
    dbo::field(a, count, "count");
    dbo::belongsTo(a, stock, "stock");
  }
};

// Вспомогательные функции лежат в utility.cpp
bool create_database(const std::string &db_name);
void initial_filling(dbo::Session &s);