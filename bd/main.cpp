#include <QtSql/QtSql>
#include <iostream>
#define CONNECTION_FAILED -1

using std::cout;
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("SQLITECIPHER");
    db.setUserName("hrono");
    db.setPassword("password");
    db.setDatabaseName("storage.db");

    if (!db.open()) {
        qDebug() << "Can not open connection.";
        exit(CONNECTION_FAILED);
    }

    QSqlQuery query;
    QSqlError errordb,errorqr;
    query.exec("drop table permissions");
    query.exec("drop table users");
    query.exec("drop table sasha");
    query.exec("drop table pasha");
     if ( !query.exec("create table users (client_id integer PRIMARY KEY AUTOINCREMENT, login text not null, pass text not null)")){
       errorqr=query.lastError();
       errordb=db.lastError();
       cout<<"Ни в какие ворота! Я покидаю это бренное ядро  № "<<errordb.number()<<"\n";
       qDebug() << "\n""Can not create table.  "<<
                errordb.text()
                <<errorqr.text();
     query.exec("drop table users");
     exit(CONNECTION_FAILED);
    }
     if (! query.exec("insert into users (login,pass) values ('sasha', '123')")){
        errorqr=query.lastError();
        errordb=db.lastError();
        qDebug() << "\n Can not insert into table.  "
                 <<errordb.text()
                 <<errorqr.text();
      query.exec("drop table users");
      exit(CONNECTION_FAILED);
     }
           query.exec("insert into users (login,pass) values ('pasha', '123')");

    query.exec("select client_id, login, pass from users");
    while (query.next()) {
    qDebug() << query.value(0).toInt() << ": " << query.value(1).toString()<<" "<< query.value(2).toString();
    }

     if ( !query.exec("create table permissions (client_id integer not null,table_id int not null)")){
       errorqr=query.lastError();
       errordb=db.lastError();
       qDebug() << "\n""Can not create table permissions.  "<<
                errordb.text()
                <<errorqr.text();
    query.exec("drop table permissions");
     exit(CONNECTION_FAILED);
     }
     if (! query.exec("insert into permissions (client_id,table_id) values ('1', '1')")){
        errorqr=query.lastError();
        errordb=db.lastError();
        qDebug() << "\n Can not insert into table permissions.  "
                 <<errordb.text()
                 <<errorqr.text();
      query.exec("drop table permissions");
      exit(CONNECTION_FAILED);
     }
           query.exec("insert into permissions (client_id,table_id) values ('1', '2')");
           query.exec("insert into permissions (client_id,table_id) values ('2', '2')");

    query.exec("select client_id, table_id from permissions");
    while (query.next()) {
   qDebug() << query.value(0).toInt() << ": "<< query.value(1).toInt();
   }

    if ( !query.exec("create table sasha (name text not null, data blob not null)")){
      errorqr=query.lastError();
      errordb=db.lastError();
      qDebug() << "\n""Can not create table sasha.  "<<
               errordb.text()
               <<errorqr.text();
    query.exec("drop table sasha");
    }

    if ( !query.exec("create table pasha (name text not null, data blob not null)")){
      errorqr=query.lastError();
      errordb=db.lastError();
      qDebug() << "\n""Can not create table pasha.  "<<
               errordb.text()
               <<errorqr.text();
    query.exec("drop table pasha");
        exit(CONNECTION_FAILED);
    }

    db.close();

    return app.exec();
}
