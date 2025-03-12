#include <QtCore>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSqlDatabase>

bool testInternextConnection() {
  // Взял отсюда:
  // https://ru.stackoverflow.com/questions/1226273/
  QNetworkAccessManager nam;
  QNetworkRequest req(QUrl("https://google.com"));
  QNetworkReply *reply = nam.get(req);
  QEventLoop loop;
  QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
  QObject::connect(&nam, SIGNAL(finished(QNetworkReply*)), &loop,
                    SLOT(quit()));
  if (!reply->isFinished())
      loop.exec();
  return reply->error() == QNetworkReply::NoError;
}

bool testDBConnection() {
  // Взял отсюда:
  // https://doc.qt.io/qt-6/qsqldatabase.html
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
  db.setDatabaseName("dbName");
  db.setHostName("host");
  db.setUserName("user");
  db.setPassword("password");
  if (!db.open()) {
      return false;
    }
  return true;
}

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  if (testInternextConnection())
    qDebug() << "You are connected to the Google site";
  else
    qDebug() << "No connection to the Google site";

  if (testDBConnection())
    qDebug() << "The database is open";
  else
    qDebug() << "Failed connect to database";

  return 0;
}
