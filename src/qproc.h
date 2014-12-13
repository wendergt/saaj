#ifndef QPROC_H
#define QPROC_H

#include <QWidget>
#include <QtWidgets>
#include "mglobal.h"
#include "databasemanager.h"
#include "qeditprocesso.h"
#include "qparte.h"
#include "qfinddlg.h"

class QProc : public QWidget
{
    Q_OBJECT
public:
    explicit QProc(QWidget *parent = 0);

    QSqlQueryModel *ProMdl;
    QSqlQueryModel *ParMdl;
    QTableView *partView;
    //QGroupBox
    QWidget *ParteAtiva;
    QVBoxLayout *PAlay;
    //QGroupBox
    QWidget *PartePassiva;
    QVBoxLayout *PPlay;
    QVBoxLayout *lay;
    QLabel *lab1;
    QLabel *lab2;
    QLabel *lab3;
    QLabel *lab4;    

    int aid;
    QStringList *aprocesso; // PROCESSO, INFRAÇÃO, TCO, CLASSE, ASSUNTO, VARA
    QSqlRecord *regpro;
    QSqlRecord *regpar;
    //QStringList *apid, *aptipo, *apnome, *apendereco, *apqualificacao, *apadvogado, *apadvoab;
    //QStringList *apartes[7];

signals:

public slots:
    void PrepareAta();
    void ShowProcesso();
    void SetProcesso(int ID = 0);
    void EditProcesso();
    void AddProcesso();
    void AddParteRelation();
    QString GetProcesso();

};

#endif // QPROC_H
