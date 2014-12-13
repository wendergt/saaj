#include "qparte.h"

void qParte::EditParte()
{
    qFormEdit *myform = new qFormEdit(areg->field("id_pessoa").value().toInt(),QString("pessoas"));
    myform->exec();
}

void qParte::DeleteParteRelation()
{
    QSqlQuery *qry = new QSqlQuery();
    qry->exec(QString("DELETE FROM main.relation WHERE id = %1").arg(areg->field("id_relation").value().toInt()));
    this->hide();
}

void qParte::AddParteRelation()
{
    qFinddlg *dlg1 = new qFinddlg("tipo_parte");
    qFinddlg *dlg2 = new qFinddlg("pessoas");

    if (dlg1->exec() == 1)
        if (dlg2->exec() == 1)
        {
            QSqlQuery *qry = new QSqlQuery;
            qry->exec(QString("INSERT INTO main.relation "
                              "(id_proc,id_pessoa,tipo_parte,status,refere) "
                              "VALUES (%1,%2,%3,%4,%5)").arg(
                          areg->field("id_proc").value().toString(),
                          QString::number(dlg2->GetID()),
                          QString::number(dlg1->GetID()),
                          QString::number(0),
                          areg->field("id_pessoa").value().toString()));

            qDebug() << qry->executedQuery();
        }
}

qParte::qParte(QSqlRecord reg, QWidget *parent) :
    QWidget(parent)
{
    areg = new QSqlRecord(reg);
    texto = new QLabel(areg->field("descricao").value().toString() + ": " + areg->field("nome").value().toString());

    this->setStyleSheet("QFrame{border: none;} "
                        "QLabel{background-color:rgba(10,10,10,0.1); font-family:Monospace; font-style:normal; font-size:12px;}");

  //  texto->setStyleSheet("QLabel{background-color:yellow} "
    //                     "QLabel:pressed {background-color: rgb(224, 0, 0);} "
      //                   "QLabel:hover {background-color: rgb(224, 255, 0);}"
        //                 "QLabel:hover:pressed{border: 1px solid red;}");

    QPushButton *btX = new QPushButton("x");
    QPushButton *btM = new QPushButton("+");
    QPushButton *btE = new QPushButton("...");
    QPushButton *btP = new QPushButton("Imprimir");
    QHBoxLayout *lay = new QHBoxLayout;

    bool tp; int z;
    z = areg->field("tipo_parte").value().toInt();
            tp = !(z >= 50) and !(z <= 55) or !(z >= 150) and !(z <= 155);

    btM->setVisible(tp);
    btP->setFlat(true);
    btP->setFixedSize(45,21);
    lay->setSpacing(1);
    lay->setMargin(1);
    btX->setFixedSize(21,21);
    btM->setFixedSize(21,21);
    btE->setFixedSize(21,21);
    btX->setStyleSheet("color: red");

    connect(btX,SIGNAL(clicked()),this,SLOT(DeleteParteRelation()));
    connect(btM,SIGNAL(clicked()),this,SLOT(AddParteRelation()));
    connect(btE,SIGNAL(clicked()),this,SLOT(EditParte()));

    lay->addSpacing(10);
    lay->addWidget(texto);
    lay->addWidget(btE);
    lay->addWidget(btM);
    lay->addSpacing(5);
    lay->addWidget(btX);
    lay->addWidget(btP);

    lay->addStretch(1);
    this->setLayout(lay);
}
