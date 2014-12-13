#include <QtWidgets>
#include "widget.h"
//#include "connection.h"
#include "databasemanager.h"
//#include <QApplication>


QTableView* createView(QSqlQueryModel *model, const QString &title = "")
{
    QTableView *view = new QTableView;
    view->setModel(model);
    static int offset = 0;

    view->setWindowTitle(title);
    view->move(100 + offset, 100 + offset);
    offset += 20;




//    view->setItemDelegateForColumn(0, new MeuPushButton());
//    view->setItemDelegateForColumn(1, new MeuPushButton());


    view->show();

    return view;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    if (!createConnection())
//        return 1;

    Widget w;
    w.show();

//    QSqlQueryModel process;
//    process.setQuery("select * from processos");

//    createView(&process,"Super Pro");

    return a.exec();
}
