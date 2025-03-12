#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QMessageBox msg;
  msg.setText("Hello Graphic World!");
  msg.setWindowTitle("Main Window");
  msg.setIcon(QMessageBox::Critical);
  msg.setStyleSheet("color: red;background-color: black");
  msg.show();

  return a.exec();
}


