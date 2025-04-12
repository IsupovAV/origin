#ifndef UTILITY_H
#define UTILITY_H

#define POSTGRE_DRIVER "QPSQL"

#define HOSTNAME "981757-ca08998.tmweb.ru"
#define DBNAME "demo"
#define PORT "5432"
#define LOGIN "netology_usr_cpp"
#define PASS "CppNeto3"
#define AUTOCONNECT "true"
#define NUM_OF_CONN_ATTEMPTS "0"
#define TIMEOUT "5"
#define SIZE_LIST_FOR_CONNECT 8

enum ConnectFields {
    host_name = 0,
    db_name,
    port,
    login,
    pass,
    auto_connect,
    num_attempts,
    timeout
};

enum TypeDirection { arrival = 0, departure = 1 };

#endif // UTILITY_H
