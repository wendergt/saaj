#include "qformedit.h"

void qFormEdit::PrepareForm()
{
    QSqlQueryModel *DATA = new QSqlQueryModel;
    DATA->setQuery(QString("SELECT * FROM pessoas"));

    QStringList *tables = new QStringList;
    tables->append("pessoas");
    tables->append("tipo_parte");
    tables->append("processos");
    tables->append("relation");
    tables->append("audiencia");

    switch(tables->indexOf(tabela)){
    case 0:{
        fldHeader->append("ID");                     fldName->append("id");
        fldHeader->append("Nome");                   fldName->append("nome");
        fldHeader->append("Nacionalidade");          fldName->append("nacional");
        fldHeader->append("Data de Nascimento");     fldName->append("data_nasc");
        fldHeader->append("Estado Civil");           fldName->append("est_civil");
        fldHeader->append("Ocupação");               fldName->append("ocupacao");
        fldHeader->append("Documento de Identidade");fldName->append("identidade");
        fldHeader->append("CPF nº");                 fldName->append("cpf");
        fldHeader->append("Filiação");               fldName->append("filiacao");
        fldHeader->append("Endereço");               fldName->append("endereco");
        fldHeader->append("Telefone");               fldName->append("telefone");
        fldHeader->append("Possui Antecedestes");    fldName->append("antecedente");
        break;}

    case 1:

        break;

    case 2:

        break;

    case 3:

        break;

    default:

        break;
    }

    for (int i = 0; i < DATA->columnCount(); i++)
    {
        QLabel *lab = new QLabel(fldHeader->at(i)+":");
        lab->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        lab->setFixedHeight(21);

        QLineEdit *edit = new QLineEdit(DATA->index(aid,i).data().toString());
        edit->setFixedHeight(21);
        edit->setProperty("idx",i);
        edit->setProperty("fName",DATA->record(aid).fieldName(i));
        edit->setStyleSheet("QLineEdit { border: 1px solid gray}");

        llay->addWidget(lab);
        elay->addWidget(edit);
        //qDebug() << edit->property("idx").toInt() << " - " << DATA->headerData(i,Qt::Horizontal,0) << " - " << DATA->record(ID).fieldName(i);
    }
}

void qFormEdit::Salvar()
{
    QString campos;
    QString valores;
    QString updt;

    QString virg("");

    QList<QLineEdit*> l_lineEdits = this->findChildren<QLineEdit*>();

    foreach (QLineEdit* l_lineEdit, l_lineEdits)
    {
        campos.append(virg + l_lineEdit->property("fName").toString());
        valores.append(virg + "\"" + l_lineEdit->text() + "\"");
        updt.append(virg + l_lineEdit->property("fName").toString()+"="+"\"" + l_lineEdit->text() + "\"");

        virg = ", ";
    }

    qDebug() << campos; qDebug() << valores; qDebug() << updt;

    QSqlQuery *qry = new QSqlQuery();
    if (aid == -1)
    {
        qry->exec(QString("INSERT INTO "+tabela+" ("+campos+") VALUES ("+valores+")"));
    }else{
        qry->exec(QString("UPDATE "+tabela+" SET "+updt+"WHERE  id = "+QString::number(aid)));
    }

    accept();
}

qFormEdit::qFormEdit(int ID, QString table, QWidget *parent) :
    QDialog(parent)
{
    aid = ID;

    fldHeader = new QStringList;
    fldName = new QStringList;
    fldValue = new QStringList;
    tabela = table;

    QHBoxLayout *mlay = new QHBoxLayout;
    llay = new QVBoxLayout;
    elay = new QVBoxLayout;
    QHBoxLayout *blay = new QHBoxLayout;
    mlay->addLayout(llay);
    mlay->addLayout(elay);


    QPushButton *btSalvar = new QPushButton("Salvar");
    connect(btSalvar, SIGNAL(clicked()),this,SLOT(Salvar()));
    btSalvar->setDefault(true);

    QPushButton *btCancel = new QPushButton("Cancelar");
    connect(btCancel, SIGNAL(clicked()),this,SLOT(close()));

    PrepareForm();

    this->setMinimumWidth(400);

    blay->addWidget(btSalvar);
    blay->addWidget(btCancel);
    elay->addStretch(1);
    llay->addStretch(1);
    elay->addLayout(blay);
    setLayout(mlay);
}
