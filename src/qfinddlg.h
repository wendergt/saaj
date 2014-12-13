#ifndef QFINDDLG_H
#define QFINDDLG_H

#include <QtWidgets>
#include "databasemanager.h"

class qFinddlg : public QDialog
{
    Q_OBJECT
public:
    explicit qFinddlg(QString tablename = 0, QWidget *parent = 0);

    int aid;
    QString aquery;
    QStringList *tables;
    QTableView *view;
    QSqlQueryModel *Qry;
    QLineEdit *edit;

signals:

public slots:
    void FindReg(QString busca);
    void DefineReg();
    void DefineReg(QModelIndex reg);
    int GetID();

};

#endif // QFINDDLG_H
