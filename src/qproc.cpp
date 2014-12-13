#include "qproc.h"
#include "databasemanager.h"
#include "qdocumento.h"

void QProc::PrepareAta()
{
    //NUM-PROC, CLASSE, ASSUNTO, VARA, TCO, DT-TCO, INFRACAO
    qDocumento *doc = new qDocumento("ata.odt");

    doc->PutData("$_VARA_$",        property("VARA").toString());
    doc->PutData("$_TIPO.AUDI_$",   property("TIPO.AUDI").toString());
    doc->PutData("$_DATA.AUDI_$",   property("DATA.AUDI").toString());
    doc->PutData("$_HORA.AUDI_$",   property("HORA.AUDI").toString());
    doc->PutData("$_HORA.INICIO_$", property("HORA.INICIO").toString());
    doc->PutData("$_NUM.PROCESSO_$",property("NUM.PROCESSO").toString());
    doc->PutData("$_INFRACAO_$",    property("INFRACAO").toString());
    doc->PutData("$_NUM.TCO_$",     property("NUM.TCO").toString());
    doc->PutData("$_DATA.TCO_$",    property("DATA.TCO").toString());

    doc->PutData("$_DATA_$",parentWidget()->property("teste").toString());
    doc->PutData("$_HORA_$", this->property("hora_audi").toString());
    doc->PutData("$_NUM.PROCESSO_$", aprocesso->at(0));
    doc->PutData("$_NUM.TCO_$", aprocesso->at(4)+"-"+aprocesso->at(5));
    doc->PutData("$_INFRACAO_$", aprocesso->at(6));
    doc->PutData("$_NUMPROCESSO_$", aprocesso->at(0));
    doc->PutData("$_NUMPROCESSO_$", aprocesso->at(0));

    //doc->PutData("$_PRESENTES_$", ParMdl->record(1).field("tipo_parte").value().toInt());


/*    QString lista;
    QString auxiliar;
    for (int i = 0; i < HoraMdl->rowCount(); i++)
    {
        auxiliar.clear();
        auxiliar.append("<tr>"
            "<td style='border-top: 1px solid #000000; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000' height='20' align='center' valign=middle sdnum='1046;0;@'><font face='Calibri' size=4>$_HORA_$</font></td>"
            "<td style='border-top: 1px solid #000000; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000' align='left'   valign=middle sdnum='1046;0;@'><font face='Calibri' size=3>$_PROCESSO_$</font></td>"
            "<td style='border-top: 1px solid #000000; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000' align='left'   valign=middle sdnum='1046;0;@'><font face='Calibri' size=4>(___) Iniciada<br>(___) Encerrada</font></td>"
        "</tr>");
        auxiliar.replace("$_HORA_$",HoraMdl->index(i,2).data().toString());
        processo->SetProcesso(HoraMdl->index(i, 0).data().toInt());
        auxiliar.replace("$_PROCESSO_$",processo->GetProcesso());
        lista.append(auxiliar);
    }
    pauta->PutData("$_LISTA_$",lista);*/
    doc->exec();
}

void QProc::ShowProcesso()
{
    if (aprocesso->count() == 7) //NUM-PROC, CLASSE, ASSUNTO, VARA, TCO, DT-TCO, INFRACAO
    {
     lab1->setText(QString("»Processo: <b>%1<b>").arg(aprocesso->at(0)));

     if (aprocesso->at(3).toInt() == 1)//**** SE FOR CRIMINAL
       {
        QString tmp;
        tmp = aprocesso->at(5);
        tmp.remove(0,6);
        lab2->setVisible(true);
        lab2->setText(QString("Autos de TCO nº <b>%1/%2</b> (%3)").arg(
                          aprocesso->at(4), tmp, aprocesso->at(6)));
       }
     else
       {
        lab2->setText("");
        lab2->setVisible(false);
       }
     lab3->setText(QString("Classe: %1").arg(aprocesso->at(1)));
     lab4->setText(QString("Assunto: %1").arg(aprocesso->at(2)));
    }

        delete ParteAtiva;
        delete PartePassiva;

        ParteAtiva = new QFrame();
        PartePassiva = new QFrame();

        QHBoxLayout *palay = new QHBoxLayout;
        QHBoxLayout *pplay = new QHBoxLayout;
        QLabel *patit = new QLabel("»Parte Ativa");
        QLabel *pptit = new QLabel("»Parte Passiva");
        QPushButton *btpa = new QPushButton("▼");
        QPushButton *btpp = new QPushButton("▼");
        connect(btpa, SIGNAL(clicked()),this,SLOT(AddParteRelation()));
        connect(btpp, SIGNAL(clicked()),this,SLOT(AddParteRelation()));
        btpa->setFixedWidth(24);
        btpp->setFixedWidth(24);

        palay->setMargin(0);
        patit->setStyleSheet("QFrame{border: 0px; border-bottom: 1px solid gray;}");
        palay->addWidget(patit,1);
        palay->addWidget(btpa);

        pplay->setMargin(0);
        pptit->setStyleSheet("QFrame{border: 0px; border-bottom: 1px solid gray;}");
        pplay->addWidget(pptit,1);
        pplay->addWidget(btpp);

        PAlay = new QVBoxLayout;
        PPlay = new QVBoxLayout;
        PAlay->setSpacing(0);
        PPlay->setSpacing(0);
        PAlay->setMargin(0);
        PPlay->setMargin(0);
        PAlay->addLayout(palay);
        PPlay->addLayout(pplay);

        ParteAtiva->setLayout(PAlay);
        PartePassiva->setLayout(PPlay);
    if (ParMdl->rowCount() > 0)
    {
    for (int i=0; i < ParMdl->rowCount(); i++)
        {
/*        bool tp; int z;
        z = ParMdl->record(i).value(2).toInt();
        tp = !(z >= 50 and z <= 55 or z >= 150 and z <= 155);

        qParte *pt = new qParte(aid,                                //processo id
                                ParMdl->record(i).value(1).toInt(), //relation id
                                ParMdl->record(i).value(0).toInt(), //pessoa id
                                QString("%1: %2").arg(
                                ParMdl->record(i).value(3).toString(),
                                ParMdl->record(i).value(4).toString()),
                                tp);
*/
        qParte *pt = new qParte(ParMdl->record(i));

        if(ParMdl->record(i).field("tipo_parte").value().toInt() < 100)
            {PAlay->addWidget(pt);}
            else
            {PPlay->addWidget(pt);}
        }

    }else{
        QLabel *lab5 = new QLabel("Não há partes associadas a este processo!");
        QLabel *lab6 = new QLabel("Não há partes associadas a este processo!");
        PAlay->addWidget(lab5);
        PPlay->addWidget(lab6);
    }
    PAlay->addStretch(1);
    PPlay->addStretch(1);
    lay->addWidget(ParteAtiva);
    lay->addWidget(PartePassiva);
}

void QProc::SetProcesso(int ID)
{
    ProMdl->setQuery(QString("SELECT "
                             "p.num_proc, "
                             "p.classe, "
                             "p.assunto, "
                             "p.vara, "
                             "p.num_tco, "
                             "p.data_tco, "
                             "p.infracao "
                             "FROM "
                             "processos as p "
                             "WHERE "
                             "p.id=%1").arg(ID));



    ParMdl->setQuery(QString("SELECT "
                             "r.id_pessoa as id_pessoa, "
                             "r.id as id_relation, "
                             "r.id_proc as id_processo, "
                             "r.tipo_parte, "
                             "tp.descricao, "
                             "pe.nome, "
                             "pe.nacional, "
                             "pe.est_civil, "
                             "pe.ocupacao, "
                             "pe.data_nasc, "
                             "pe.filiacao, "
                             "pe.cpf, "
                             "pe.identidade, "
                             "pe.endereco, "
                             "pe.telefone, "
                             "pe.antecedente, "
                             "r.refere, "
                             "r.status "
                             "FROM "
                             "pessoas as pe, "
                             "processos as p, "
                             "relation as r, "
                             "tipo_parte as tp "
                             "WHERE "
                             "p.id=%1 "
                             "and r.id_proc=p.id "
                             "and r.id_pessoa=pe.id "
                             "and tp.id=r.tipo_parte "
                             "ORDER BY r.tipo_parte").arg(ID));

    aid = ID;
    aprocesso->clear();//NUM-PROC, CLASSE, ASSUNTO, VARA, TCO, DT-TCO, INFRACAO
    aprocesso->append(ProMdl->record(0).value(0).toString());
    aprocesso->append(ProMdl->record(0).value(1).toString());
    aprocesso->append(ProMdl->record(0).value(2).toString());
    aprocesso->append(ProMdl->record(0).value(3).toString());
    aprocesso->append(ProMdl->record(0).value(4).toString());
    aprocesso->append(ProMdl->record(0).value(5).toString());
    aprocesso->append(ProMdl->record(0).value(6).toString());

    setProperty("ID",ID);
    setProperty("VARA","DeifniçãodaVara");
    setProperty("TIPO.AUDI","");
    setProperty("DATA.AUDI","");
    setProperty("HORA.AUDI","");
    setProperty("HORA.INICIO","");
    setProperty("NUM.PROCESSO","");
    setProperty("INFRACAO","");
    setProperty("NUM.TCO","");
    setProperty("DATA.TCO","");

    qDebug() << ProMdl->record(0).field("num_proc").value().toString();



    ShowProcesso();
}

void QProc::EditProcesso()
{
    qEditProcesso *EPro = new qEditProcesso(aid,aprocesso);
    if(EPro->exec()){SetProcesso(aid);}
}

void QProc::AddProcesso()
{
    int tmp = aid;
    aid = -1;
    qEditProcesso *EPro = new qEditProcesso(aid,aprocesso);
    if(EPro->exec()){SetProcesso(tmp);}
    aid = tmp;
}

void QProc::AddParteRelation()
{
qFinddlg *dlg1 = new qFinddlg("pessoas");
qFinddlg *dlg2 = new qFinddlg("tipo_parte");

if (dlg2->exec() == 1)
if (dlg1->exec() == 1)
{
    QSqlQuery *qry = new QSqlQuery;
    qry->exec(QString("INSERT INTO main.relation "
                      "(id_proc,id_pessoa,tipo_parte,status,refere) "
                      "VALUES (%1,%2,%3,%4,%5)").arg(
              QString::number(aid),
              QString::number(dlg1->GetID()),
              QString::number(dlg2->GetID()),
              QString::number(0),
              QString::number(0)));

    SetProcesso(aid);
}
}

QString QProc::GetProcesso()
{                         //NUM-PROC, CLASSE, ASSUNTO, VARA, TCO, DT-TCO, INFRACAO
    QString temp;
    if (aprocesso->count() == 7)
    {
        QString tmp;
        tmp = aprocesso->at(5);
        tmp.remove(0,6);

    temp.append(QString("Processo: <b>%1 (%2)</b><BR>").arg(aprocesso->at(0),aprocesso->at(6)));
    if(aprocesso->at(3)=="1"){
    temp.append(QString("Autos de TCO nº <b>%1/%2</b> (%3)<BR>").arg(aprocesso->at(4),tmp,aprocesso->at(2)));
    }else{
    temp.append(QString("Assunto: %1<BR>").arg(aprocesso->at(2)));
    }
    }
    if (ParMdl->rowCount() > 0)
    {
    for (int i=0; i < ParMdl->rowCount(); i++)
        {
        temp.append(QString("%1: %2").arg(ParMdl->record(i).value(3).toString(),
                                          ParMdl->record(i).value(4).toString()));
        if(i < ParMdl->rowCount()){temp.append(QString("<BR>"));}
        }
    }else{temp.append("Não há partes associadas a este processo!");}

    return temp;
}

QProc::QProc(QWidget *parent) :
    QWidget(parent)
{
    lay = new QVBoxLayout;
    QHBoxLayout *sublay = new QHBoxLayout;
    QVBoxLayout *sublay2 = new QVBoxLayout;
    QHBoxLayout *llay2 = new QHBoxLayout;
    QHBoxLayout *llay3 = new QHBoxLayout;
    QHBoxLayout *llay4 = new QHBoxLayout;

    this->setMinimumWidth(400);
    this->setStyleSheet("QFrame{background-color:rgba(255,255,255,0.5); border: 2px solid white;"
                        "font-family:Monospace; font-style:normal; font-size:12px;}");
    lab1 = new QLabel;
    lab2 = new QLabel;
    lab3 = new QLabel;
    lab4 = new QLabel;
    ProMdl = new QSqlQueryModel;
    ParMdl = new QSqlQueryModel;
    aprocesso = new QStringList;
    QFrame *FProcesso = new QFrame;
    ParteAtiva = new QFrame;
    PartePassiva = new QFrame;

//*********************************************************************************************************
    QPushButton *btEdit = new QPushButton("...");
    QPushButton *btAdd = new QPushButton("+");
    QPushButton *btDel = new QPushButton("x");

    btEdit->setFixedWidth(24);
    btAdd->setFixedWidth(24);
    btDel->setFixedWidth(24);

    connect(btEdit,SIGNAL(clicked()),this,SLOT(EditProcesso()));
    connect(btAdd, SIGNAL(clicked()),this,SLOT(AddProcesso()));
    connect(btDel,SIGNAL(clicked()),this,SLOT(PrepareAta()));
//*********************************************************************************************************

    /*QString style = "QLabel{border:0px; color:#000000; background-color:rgba(100,100,100,0.1); "
    "selection-color:#FFFFFF; selection-background-color:#000000; font-family:Monospace;"
    "font-style:normal; font-size:12px; }";*/

    lab1->setStyleSheet("QFrame{border: 0px; border-bottom: 1px solid gray;}");
    lab2->setStyleSheet("QFrame{border: 0px;}");
    lab3->setStyleSheet("QFrame{border: 0px;}");
    lab4->setStyleSheet("QFrame{border: 0px;}");

    lab2->setFixedHeight(21);
    lab3->setFixedHeight(21);
    lab4->setFixedHeight(21);


    sublay->setSpacing(1);
    sublay->setMargin(0);
    sublay->addWidget(lab1);
    sublay->addWidget(btEdit);
    sublay->addWidget(btAdd );
    sublay->addWidget(btDel );

    sublay2->setSpacing(1);
    sublay2->setMargin(0);
    sublay2->addLayout(sublay);

    llay2->setSpacing(1); llay2->setMargin(0); llay2->addSpacing(10); llay2->addWidget(lab2);llay2->addStretch();sublay2->addLayout(llay2);
    llay3->setSpacing(1); llay3->setMargin(0); llay3->addSpacing(10); llay3->addWidget(lab3);llay3->addStretch();sublay2->addLayout(llay3);
    llay4->setSpacing(1); llay4->setMargin(0); llay4->addSpacing(10); llay4->addWidget(lab4);llay4->addStretch();sublay2->addLayout(llay4);
    sublay2->addSpacing(3);
    FProcesso->setLayout(sublay2);

    lay->setSpacing(2);
    lay->setMargin(0);
    lay->addWidget(FProcesso);
    lay->addWidget(ParteAtiva);
    lay->addWidget(PartePassiva);

    setLayout(lay);
}
