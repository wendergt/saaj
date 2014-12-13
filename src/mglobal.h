#ifndef MGLOBAL_H
#define MGLOBAL_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QDebug>

class mGlobal : public QObject
{
    Q_OBJECT
public:
    explicit mGlobal(QObject *parent = 0);
    ~mGlobal();
    QString getPath();
    QString getData();

private:
    QString apath;
    QString atapath;
    QDate adata;
    QTime ahora;

signals:

public slots:

};

#endif // MGLOBAL_H
