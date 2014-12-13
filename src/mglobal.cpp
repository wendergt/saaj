#include "mglobal.h"

mGlobal::mGlobal(QObject *parent) :
    QObject(parent)
{
    //****************************************** PATH *********************************************
    apath = QDir::home().path();
#ifdef Q_OS_LINUX
    apath.append("/.saaj/");
#else
    apath.append("/AppData/Local/Saaj/");
#endif
    qDebug() << "No-Native-GetPath: " + apath;
    apath = QDir::toNativeSeparators(apath);
    qDebug() << "Native-GetPath: " + apath;
    QDir dir;
    dir.setPath(apath);
    if (!dir.exists()){dir.mkdir(apath);}

//************************************************ DATA *******************************************
    adata = QDate::currentDate();
}

mGlobal::~mGlobal()
{

}

QString mGlobal::getPath()
{
    return apath;
}

QString mGlobal::getData()
{
    return adata.toString(Qt::LocalDate);
}
