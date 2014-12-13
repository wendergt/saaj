#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQueryModel>
#include <QFile>
#include <QDateTime>
#include "mglobal.h"


class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

public:
    bool openDB();
    bool deleteDB();
    bool closeDB();
    bool executeSQL(QString sql);
    QSqlError lastError();
    QDir dir;

private:
    QSqlDatabase db;
    
signals:
    
public slots:
    
};

#endif // DATABASEMANAGER_H
