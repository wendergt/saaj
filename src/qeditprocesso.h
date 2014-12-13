#ifndef QEDITPROCESSO_H
#define QEDITPROCESSO_H

#include <QWidget>
#include <QtWidgets>
#include "databasemanager.h"

class qEditProcesso : public QDialog
{
    Q_OBJECT
public:
    explicit qEditProcesso(int ID = 0, QStringList *DATA = 0, QWidget *parent = 0);

    int aid;
    int vara;
    QComboBox *cbVara;
    QLineEdit *line1;
    QLineEdit *line2;
    QLineEdit *line3;
    QLineEdit *line4;
    QLineEdit *line5;
    QLineEdit *line6;

signals:

public slots:
    void Salvar();

};

#endif // QEDITPROCESSO_H
