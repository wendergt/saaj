#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "qproc.h"
#include "databasemanager.h"
#include "qdocumento.h"
#include "qformedit.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    DatabaseManager *banco;
    QDateTimeEdit *data;

    QSqlQueryModel *HoraMdl;
    QTableView *HoraView;

    QWidget *Lab;
    QTreeView *Ocorrencias;
    QSqlQueryModel *Ocorrenciamdl;
    QTextBrowser *Deliberacao;

    QProc *processo;


public slots:
    void UpdateProc(QModelIndex Idx);
    void UpdateAudi(QDate xdata);
    void ExportPauta();

};

#endif // WIDGET_H
