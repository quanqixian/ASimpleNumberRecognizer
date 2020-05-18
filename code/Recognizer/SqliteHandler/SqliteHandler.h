﻿#ifndef SQLITEHANDLER_H
#define SQLITEHANDLER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

struct Characteristic
{
    int array[9];
};

class SqliteHandler : public QObject
{
    Q_OBJECT
public:
    static SqliteHandler* getInstance(void);
    bool additem(int tableIndex, int (&array)[9]);
    bool getitems(int tableIndex, int startIndex, int number, QList<Characteristic > &retList);
    bool clearTable(int tableIndex);
    ~SqliteHandler();
private:
    static QSqlDatabase m_db;
    static SqliteHandler* m_instance;
    bool init(void);
private:
    SqliteHandler();
    SqliteHandler(SqliteHandler&);
    SqliteHandler& operator = (const SqliteHandler&);
};
#endif