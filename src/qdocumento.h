#ifndef QDOCUMENTO_H
#define QDOCUMENTO_H

#include <QWidget>
#include <QtWidgets>
//#include <QWebView>
//#include <QPrinter>
//#include <QPrintDialog>
//#include <JlCompress.h>
#include "mglobal.h"
#include "qzipreader_p.h"
#include "qzipwriter_p.h"

class qDocumento : public QDialog
{
    Q_OBJECT
public:
    explicit qDocumento(QString FileName, QWidget *parent = 0);

    QString texto;
    QString stilo;
    QTextBrowser *labb;
    QVBoxLayout *mainLay;

signals:

public slots:
    void SaveODT();
    void LoadODT(QString FileName);
    void PutData(QString key, QString dados);

};

#endif // QDOCUMENTO_H
