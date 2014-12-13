#include "qeditprocesso.h"

void qEditProcesso::Salvar()
{
    QSqlQuery *qry = new QSqlQuery();
    if (aid == -1)
    {
    qry->exec(QString("INSERT INTO main.processos "
              "(num_proc, classe, assunto, vara, num_tco, data_tco, infracao) "
              "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7')").arg(
              line1->text(),line2->text(),line3->text(),QString::number(cbVara->currentIndex()),line4->text(),line5->text(),line6->text()));
    }else{
    qry->exec(QString("UPDATE main.processos SET "
              "num_proc = '%1', "
              "classe = '%2', "
              "assunto = '%3', "
              "vara = '%4', "
              "num_tco = '%5', "
              "data_tco = '%6', "
              "infracao = '%7' "
              "WHERE  id = '%8'").arg(
              line1->text(),line2->text(),line3->text(),QString::number(vara),line4->text(),line5->text(),line6->text(),QString::number(aid)));
    }
    accept();
}

qEditProcesso::qEditProcesso(int ID, QStringList *DATA, QWidget *parent) :
    QDialog(parent)
{
    aid = ID;
    vara = DATA->at(3).toInt();
    cbVara = new QComboBox;
    QGridLayout *lay = new QGridLayout;

    cbVara->addItem("Juizado Especial Cível");
    cbVara->addItem("Juizado Especial Criminal");
    cbVara->addItem("Juizado Especial da Fazenda Pública");

    //NUM-PROC, CLASSE, ASSUNTO, VARA, TCO, DT-TCO, INFRACAO
    QLabel *lab0 = new QLabel("Vara: ");
    QLabel *lab1 = new QLabel("Processo: ");
    QLabel *lab2 = new QLabel("Classe: ");
    QLabel *lab3 = new QLabel("Assunto: ");
    QLabel *lab4 = new QLabel("TCO nº: ");
    QLabel *lab5 = new QLabel("Data TCO: ");
    QLabel *lab6 = new QLabel("Infração: ");
    line1 = new QLineEdit;
    line2 = new QLineEdit;
    line3 = new QLineEdit;
    line4 = new QLineEdit;
    line5 = new QLineEdit;
    line6 = new QLineEdit;
    line1->setMinimumWidth(300);

    lab4->setVisible(vara == 1); line4->setVisible(vara == 1);
    lab5->setVisible(vara == 1); line5->setVisible(vara == 1);
    lab6->setVisible(vara == 1); line6->setVisible(vara == 1);

//*************************** NOVO ***********************************
    if (aid == -1) {
        cbVara->setEnabled(true);
        line1->setText("");
        line2->setText("");
        line3->setText("");
        line4->setText("");
        line5->setText("");
        line6->setText("");
    }else{      //********************* EDITAR **********************
        cbVara->setEnabled(false);
        cbVara->setCurrentIndex(vara);
        line1->setText(DATA->at(0));
        line2->setText(DATA->at(1));
        line3->setText(DATA->at(2));
        line4->setText(DATA->at(4));
        line5->setText(DATA->at(5));
        line6->setText(DATA->at(6));
    }

    QPushButton *btSalvar = new QPushButton("Salvar");
    QPushButton *btCancel = new QPushButton("Cancelar");
    btSalvar->setDefault(true);
    btSalvar->setFixedWidth(90);
    btCancel->setFixedWidth(90);

    connect(btSalvar,SIGNAL(clicked()),this,SLOT(Salvar()));
    connect(btCancel,SIGNAL(clicked()),this,SLOT(close()));

    lay->addWidget(lab0,0,0,1,1);   lay->addWidget(cbVara,0,1,1,3);
    lay->addWidget(lab1,1,0,1,1);   lay->addWidget(line1, 1,1,1,3);
    lay->addWidget(lab2,2,0,1,1);   lay->addWidget(line2, 2,1,1,3);
    lay->addWidget(lab3,3,0,1,1);   lay->addWidget(line3, 3,1,1,3);
    lay->addWidget(lab4,4,0,1,1);   lay->addWidget(line4, 4,1,1,3);
    lay->addWidget(lab5,5,0,1,1);   lay->addWidget(line5, 5,1,1,3);
    lay->addWidget(lab6,6,0,1,1);   lay->addWidget(line6, 6,1,1,3);

    lay->addWidget(btSalvar,7,2,1,1);
    lay->addWidget(btCancel,7,3,1,1);

    setLayout(lay);
}
