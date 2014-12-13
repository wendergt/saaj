#ifndef QFORMEDIT_H
#define QFORMEDIT_H

#include <QtWidgets>
#include "databasemanager.h"

class qFormEdit : public QDialog
{
    Q_OBJECT
public:
    explicit qFormEdit(int ID = -1, QString table = 0, QWidget *parent = 0);

    int aid;
    int vara;
    QString tabela;
    QStringList *fldHeader;
    QStringList *fldName;
    QStringList *fldValue;

    QVBoxLayout *llay;
    QVBoxLayout *elay;

signals:

public slots:
    void PrepareForm();
    void Salvar();

};

#endif // QFORMEDIT_H
