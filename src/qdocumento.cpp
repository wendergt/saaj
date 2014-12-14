#include "qdocumento.h"

void qDocumento::doPrint()
{
    qDebug() << "TestWindow::doPrint()";
    mGlobal gb;
    QFile f(QDir::toNativeSeparators(gb.getPath() + "template/content.xml"));
    //if (f.open(QFile::WriteOnly | QFile::Text);
    qDebug() << f.size();
    QTextStream out(&f);
    out.setCodec("UTF-8");
//    out << html;
    //in.setString(&html,QIODevice::WriteOnly);
    f.close();
    QZipWriter zip(QDir::toNativeSeparators(QDir::home().path() + "/Documentos/DocumentoZIP.odt"));
//    zip.addDirectory(QDir::toNativeSeparators(gb.getPath() + "template"));
//    qDebug() << QString("%1").arg(JlCompress::compressDir("C:/Users/GinaMarise/Documents/Saaj/Documento.odt",
//                                                          gb.getPath() + "template"));



    //QZipWriter zip(path + "/dir.zip");

    //if (zip.status() != QZipWriter::NoError)

    zip.setCompressionPolicy(QZipWriter::AutoCompress);

    QDirIterator it(QDir::toNativeSeparators(gb.getPath() + "template"), QDir::Files|QDir::Dirs, QDirIterator::Subdirectories);



    while(it.hasNext())
    {
    QString file_path = it.next();
   // qDebug() << "isdir: " << it.fileInfo().isDir() << " isfile: " << it.fileInfo().isFile() <<
   //             " - filapath do zip: " + file_path.remove(gb.getPath() + "template/");

    QString tmp = file_path.at(file_path.count()-1);
    bool aux = QString::compare(tmp, ".", Qt::CaseInsensitive) && QString::compare(tmp, "..", Qt::CaseInsensitive);
    qDebug() << "*********   tmp: " << tmp << " aux: " << aux;


    if (it.fileInfo().isDir() && aux)
    {
    zip.setCreationPermissions(QFile::permissions(file_path));
    //int x = QString::compare(tmp, ".", Qt::CaseInsensitive);
    zip.addDirectory(file_path.remove(gb.getPath() + "template"));
    }
    //else
    if(it.fileInfo().isFile())
    {
    QFile file(file_path);

    if (!file.open(QIODevice::ReadOnly))
    continue;

    zip.setCreationPermissions(QFile::permissions(file_path));
    QByteArray ba = file.readAll();
    zip.addFile(file_path.remove(gb.getPath() + "template/"), ba);

    file.close();
    }
    }

    zip.close();





}

void qDocumento::doPrintVis()
{
/*    qDebug() << "TestWindow::doPrintVis()";

    QPrinter printer;
    QPrintDialog printDlg(&printer);
    if (printDlg.exec() == QDialog::Rejected)
        return;

    QPainter painter(&printer);
    labb->render(&painter, labb->pos(), labb->visibleRegion());
*/
}

void qDocumento::PutData(QString ident, QString dados)
{
    html.replace(ident,dados);
    labb->setHtml(html);
}

qDocumento::qDocumento(QString FileName, QWidget *parent) :
    QDialog(parent)
{
    mGlobal gb;

    QDir baseDir (QDir::toNativeSeparators(gb.getPath() + "template/"));

    qDebug() << "UnzipFile: " + gb.getPath() + FileName;

     QZipReader unzip ( gb.getPath() + FileName , QIODevice :: ReadOnly ) ;
     QList < QZipReader :: FileInfo > allFiles = unzip.fileInfoList ( ) ;
     QZipReader :: FileInfo fi;

     foreach ( QZipReader :: FileInfo fi , allFiles )
     {
     QString absPath = QDir::toNativeSeparators(baseDir.absolutePath() + "/" + fi.filePath) ;

     qDebug() << fi.isDir << fi.isFile << QDir::toNativeSeparators(QFileInfo(absPath).absolutePath());

     baseDir.mkpath(QDir::toNativeSeparators(QFileInfo(absPath).absolutePath()));
     if ( fi.isDir )
     {
     if ( ! baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath() + "/" + fi.filePath) ) )
     return ;
     if ( ! QFile :: setPermissions ( absPath , fi.permissions ) )
     return ;
     }
     }

     foreach ( QZipReader :: FileInfo fi , allFiles )
     {
     QString absPath = QDir::toNativeSeparators(baseDir.absolutePath() + "/" + fi. filePath );
     //absPath = QDir::toNativeSeparators(absPath);
     if ( fi. isFile )
     {
     QFile file ( absPath ) ;
     if ( file . open ( QFile :: WriteOnly ) )
     {
     QApplication :: setOverrideCursor ( Qt :: WaitCursor ) ;
     file . write ( unzip. fileData ( fi. filePath ) , unzip. fileData ( fi. filePath ) . size ( ) ) ;
     file . setPermissions ( fi. permissions ) ;
     QApplication :: restoreOverrideCursor ( ) ;
     file . close ( ) ;
     }
     }
     }
     unzip. close ( ) ;
//    JlCompress::extractDir(gb.getPath() + FileName, gb.getPath() + "template");
//    QZipReader zip(gb.getPath() + FileName);
//    qDebug() << zip.exists();
//    qDebug() << zip.status();
//    qDebug() << gb.getPath() + FileName;
//    zip.extractAll(gb.getPath() + "template");

    QFile f(QDir::toNativeSeparators(gb.getPath() + "template/content.xml"));

    //if (
    f.open(QFile::ReadOnly | QFile::Text);
    //{
    QTextStream in(&f);
    in.setCodec("UTF-8");
    qDebug() << f.size();
    html.append(in.readAll());
    //}

    mainLay = new QVBoxLayout;
    labb = new QTextBrowser;
    QPushButton *btPrint= new QPushButton;

    btPrint->setStyleSheet("QPushButton{background-color:yellow;border: 1px solid gray;} "
                           "QPushButton:pressed {background-color: rgb(224, 0, 0);} "
                           "QPushButton:hover {background-color: rgb(224, 255, 0);}"
                           "QPushButton:hover:pressed{border: 1px solid red;}");

    btPrint->setMaximumWidth(150);

    //connect(printAction, SIGNAL(triggered(bool)), this, SLOT(doPrint()));
    connect(btPrint, SIGNAL(clicked()), this, SLOT(doPrint()));

    mainLay->addWidget(btPrint);
    mainLay->addWidget(labb);



    this->setLayout(mainLay);
    //qDebug() << html;
}
