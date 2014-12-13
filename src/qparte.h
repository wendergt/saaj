#ifndef QPARTE_H
#define QPARTE_H

#include <QWidget>
#include <QtWidgets>
#include "databasemanager.h"
#include "qfinddlg.h"
#include "qformedit.h"

class qParte : public QWidget
{
    Q_OBJECT
public:
    /*explicit qParte(int ProcessID = 0, int RelationID = 0, int PessoaID = 0,
                    QString nome = 0, int tipo = 0, QWidget *parent = 0);*/

    explicit qParte(QSqlRecord reg, QWidget *parent = 0);

    //int arid;
    //int apid;
    //int aprid;
    QSqlRecord *areg;
    QLabel *texto;
    QList <qParte*> aparte;

signals:

public slots:
    void EditParte();
    void DeleteParteRelation();
    void AddParteRelation();
};

#endif // QPARTE_H
