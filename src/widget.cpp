#include "widget.h"
#include "databasemanager.h"

void Widget::UpdateAudi(QDate xdata)
{
    HoraMdl->setQuery(QString("select a.id_proc, a.tipo_audi, a.hora_audi as Horário, a.data_audi "
                              "from audiencia as a "
                              "where a.data_audi='%1' "
                              "order by a.hora_audi").arg(
                              xdata.toString(Qt::LocalDate)));

    HoraView->setColumnHidden(0,true);
    HoraView->setColumnHidden(1,true);
    HoraView->selectRow(0);

    processo->SetProcesso(HoraMdl->index(0, 0).data().toInt());
    processo->setProperty("data_audi",HoraMdl->index(0, 3).data().toDate());
    processo->setProperty("hora_audi",HoraMdl->index(0, 2).data().toTime());
    processo->setProperty("tipo_audi",HoraMdl->index(0, 1).data().toInt());
    setProperty("teste",data->dateTime().toString((Qt::LocalDate)));

    qDebug() <<xdata.toString(Qt::LocalDate);
}

void Widget::UpdateProc(QModelIndex Idx)
{
    processo->SetProcesso(HoraMdl->index(Idx.row(), 0).data().toInt());
    processo->setProperty("data_audi",HoraMdl->index(Idx.row(), 3).data().toDate());
    processo->setProperty("hora_audi",HoraMdl->index(Idx.row(), 2).data().toTime());
    processo->setProperty("tipo_audi",HoraMdl->index(Idx.row(), 1).data().toString());
    setProperty("teste",data->dateTime());
}

void Widget::ExportPauta()
{
    qDocumento *pauta = new qDocumento("pauta.html");
    pauta->PutData("$_DATA_$",data->date().toString(Qt::LocalDate));

    QString lista;
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
    pauta->PutData("$_LISTA_$",lista);
    pauta->exec();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    banco = new DatabaseManager;
    banco->openDB();

    processo = new QProc;//(this, Qt::Popup | Qt:: Dialog);

    data = new QDateTimeEdit(this);
    QPushButton *btDesignar = new QPushButton("Designar Audiência");
    HoraMdl = new QSqlQueryModel(this);
    HoraView = new QTableView(this);
    QPushButton *btPauta = new QPushButton("Exportar Pauta");

    QTabWidget *table = new QTabWidget;


    Lab = new QWidget;
    Ocorrencias = new QTreeView;//=======================
    Ocorrenciamdl = new QSqlQueryModel;
    Ocorrenciamdl->setQuery("select * from ocorrencia");
    Ocorrencias->setModel(Ocorrenciamdl);
    Ocorrencias->setColumnHidden(0,true);
    Ocorrencias->setColumnHidden(1,true);
    Ocorrencias->setColumnHidden(2,true);
    Ocorrencias->setUniformRowHeights(false);
    Ocorrencias->setWordWrap(true);
    Ocorrencias->setExpandsOnDoubleClick(true);

    Deliberacao = new QTextBrowser;
    QTextBrowser *AtaView = new QTextBrowser;
    AtaView->setFixedSize(500,300);
//    AtaView->setUrl(QString("http://192.168.2.1"));

    QHBoxLayout *mLayout = new QHBoxLayout;
    QVBoxLayout *Lay1 = new QVBoxLayout;
    QVBoxLayout *Lay2 = new QVBoxLayout;
    //QVBoxLayout *labLay = new QVBoxLayout;

//    Ocorrencias->setReadOnly(false);
    table->addTab(Ocorrencias,"Ocorrências");
    table->addTab(Deliberacao,"Deliberações");
    table->addTab(Lab,"Encerramento");


/*** LAYOUTS *************************************************************************/

    //labLay->addWidget(Juiz);
    //labLay->addWidget(processo);

    //Lab->setLayout(labLay);

    Lay1->addWidget(data);
    Lay1->addWidget(btDesignar);
    Lay1->addWidget(HoraView);
    Lay1->addWidget(btPauta);

    Lay2->addWidget(processo);
    //processo->setWindowModality(Qt::WindowModal);     <<<<<<<<<<
    //processo->showFullScreen();
    Lay2->addWidget(AtaView);
    //Lay2->addStretch();

    mLayout->addLayout(Lay1);
    mLayout->addLayout(Lay2);
    mLayout->addWidget(table);
    //mLayout->addStretch(1);
    setLayout(mLayout);
/*************************************************************************************/

/*** HORÁRIO *************************************************************************/
    data->setCalendarPopup(true);
    data->setDate(QDate::currentDate());

    HoraView->setSelectionMode(QAbstractItemView::SingleSelection);
    HoraView->setSelectionBehavior(QAbstractItemView::SelectRows);
    HoraView->setFixedWidth(120);
    HoraView->setModel(HoraMdl);
/*************************************************************************************/

/*** CONEXÕES ************************************************************************/
    QObject::connect(HoraView,SIGNAL(clicked(QModelIndex)),this,SLOT(UpdateProc(QModelIndex)));
    QObject::connect(HoraView,SIGNAL(activated(QModelIndex)),this,SLOT(UpdateProc(QModelIndex)));
    QObject::connect(data,SIGNAL(dateChanged(QDate)),this, SLOT(UpdateAudi(QDate)));
    QObject::connect(btPauta,SIGNAL(clicked()), this, SLOT(ExportPauta()));
/*************************************************************************************/

}

Widget::~Widget()
{
    banco->closeDB();
}
