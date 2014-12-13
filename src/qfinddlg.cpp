#include "qfinddlg.h"

void qFinddlg::FindReg(QString busca)
{
    Qry->setQuery(aquery + busca + "%'");
    view->setModel(Qry);

    if (Qry->rowCount() == 1)
        {aid = Qry->record(0).value(0).toInt();}
        else
        {aid = -1;}

    //qDebug() << Qry->query().executedQuery();
}

void qFinddlg::DefineReg()
{
    //view->selectRow(1);
    if (aid > -1)
    {this->DefineReg(view->indexAt(QPoint(10,10)));}
}

void qFinddlg::DefineReg(QModelIndex reg)
{
    aid = Qry->record(reg.row()).value(0).toInt();
    qDebug() << "Define: " << QString::number(aid);
    if (aid > -1){this->accept();}
}

int qFinddlg::GetID()
{
    return aid;
}

qFinddlg::qFinddlg(QString tablename, QWidget *parent) :
    QDialog(parent)
{
    aid = -1;
    QVBoxLayout *mlay = new QVBoxLayout;
    QHBoxLayout *alay = new QHBoxLayout;

    QLabel *lab = new QLabel("Pesquisar:");
    edit = new QLineEdit;
    QPushButton *bt = new QPushButton("...");
    QPushButton *btX= new QPushButton("X");

    connect(edit,SIGNAL(textChanged(QString)),this,SLOT(FindReg(QString)));
    connect(bt,SIGNAL(clicked()),this,SLOT(DefineReg()));
    connect(btX,SIGNAL(clicked()),this,SLOT(close()));

    bt->setDefault(true);
    bt->setFixedWidth(24);
    btX->setFixedWidth(24);
    edit->setMinimumWidth(200);

    alay->addWidget(lab);
    alay->addWidget(edit);
    alay->addWidget(bt);
    alay->addWidget(btX);

    Qry = new QSqlQueryModel;
    Qry->setQuery(aquery);

    view = new QTableView;
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(DefineReg(QModelIndex)));
    connect(view,SIGNAL(activated(QModelIndex)),this, SLOT(DefineReg(QModelIndex)));
    view->setModel(Qry);
    view->setColumnWidth(1,150);

    mlay->addLayout(alay);
    mlay->addWidget(view);
    this->setLayout(mlay);




    tables = new QStringList;
    tables->append("pessoas");
    tables->append("tipo_parte");
    tables->append("processos");
    tables->append("relation");
    tables->append("audiencia");

    switch(tables->indexOf(tablename)){
    case 0:{
        //qFinddlg *dlg1 = new qFinddlg("tipo_parte");
        //if (dlg1->exec() == 1)
        //    {atp = dlg1->GetID();}
        //else
        //    {this->close();}
        aquery.append("SELECT id, "
                      "nome as Nome, "
                      "data_nasc as 'Data de Nascimento', "
                      "filiacao as Filiação, "
                      "printf('%s - %s',coalesce(identidade,''), coalesce(cpf,''))as Documentos "
                      "FROM pessoas WHERE nome like '%");
    break;}

    case 1:
        aquery.append("SELECT id, "
                      "descricao as Descrição "
                      "FROM tipo_parte WHERE descricao like '%");
    break;

    case 2:
        aquery.append("");
    break;

    case 3:
        aquery.append("");
    break;

    default:
        aquery.append("");
    break;
    }

    this->FindReg("");
}
