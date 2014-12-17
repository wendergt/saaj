#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{   

}

DatabaseManager::~DatabaseManager()
{

}

bool DatabaseManager::openDB()
    {
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    mGlobal gb;
    qDebug() << "Banco: " << gb.getPath("DATA") + "saaj.sqlite";
    db.setDatabaseName(gb.getPath("DATA") + "saaj.sqlite");

    // Open databasee
    return db.open();
    }

QSqlError DatabaseManager::lastError()
    {
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
    }

bool DatabaseManager::deleteDB()
    {
    // Close database
    db.close();
    mGlobal gb;
    return QFile::remove(gb.getPath() + "saaj.sqlite");
}

bool DatabaseManager::closeDB()
    {
    // Close database
    db.close();
    return !db.isOpen();
}

bool DatabaseManager::executeSQL(QString sql)
{
    qDebug() << sql.data();
    bool xl = false;
    // Executar uma SQL
    if (db.isOpen())
        {
        QSqlQuery query;
        xl = query.exec(sql);
        }
    return xl;
}
