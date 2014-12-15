#include "qdocumento.h"

void qDocumento::doPrint()
{
    qDebug() << "TestWindow::doPrint()";
    mGlobal gb;

    QFile f(QDir::toNativeSeparators(gb.getPath() + "template/content.xml"));
    if (f.open(QFile::WriteOnly | QFile::Text));
    qDebug() << f.size();
    QTextStream out(&f);
    out.setCodec("UTF-8");
    out << html;
    f.close();
    QZipWriter zip(QDir::toNativeSeparators(QDir::home().path() + "/Documentos/AtaPronta.odt"));
    zip.setCompressionPolicy(QZipWriter::AutoCompress);

    QDirIterator it(QDir::toNativeSeparators(gb.getPath() + "template"), QDir::Files|QDir::Dirs, QDirIterator::Subdirectories);

    qDebug() << "ZipFile: " + QDir::toNativeSeparators(QDir::home().path() + "/Documentos/AtaPronta.odt");
    while(it.hasNext())
    {
        qDebug() << QString("Size:%1 Tipo:%2%3 FilePath:%4").arg
                    (QString::number(it.fileInfo().size()), QString::number(it.fileInfo().isDir()),
                     QString::number(it.fileInfo().isFile()), it.filePath());

        QString file_path = QDir::toNativeSeparators(it.next());
        //QString tmp = file_path.at(file_path.count()-1);

        if (it.fileInfo().isDir() && it.fileName() != "." && it.fileName() != "..")
                                  //QString::compare(tmp, ".", Qt::CaseInsensitive))
        {
            /*    qDebug() << "Folder";
        qDebug() << "File_Path: " << file_path;
        qDebug() << "SplitLast: " << file_path.split(QDir::toNativeSeparators("/")).last();
        qDebug() << "GetPath  : " << QDir::toNativeSeparators(gb.getPath() + "template/");
        qDebug() << "Remove   : " << file_path.remove(QDir::toNativeSeparators(gb.getPath() + "template/"));
        qDebug() << " ";
        enum Permission {
            ReadOwner = 0x4000, WriteOwner = 0x2000, ExeOwner = 0x1000,
            ReadUser  = 0x0400, WriteUser  = 0x0200, ExeUser  = 0x0100,
            ReadGroup = 0x0040, WriteGroup = 0x0020, ExeGroup = 0x0010,
            ReadOther = 0x0004, WriteOther = 0x0002, ExeOther = 0x0001*/

            zip.setCreationPermissions(QFile::permissions(file_path));
            zip.addDirectory(file_path.remove(QDir::toNativeSeparators(gb.getPath() + "template/")));
        }

        if(it.fileInfo().isFile())
        {
            QFile file(file_path);

            if (!file.open(QIODevice::ReadOnly))
                continue;
            /*    qDebug() << "File";
    qDebug() << "File_Path: " << file_path;
    qDebug() << "SplitLast: " << file_path.split(QDir::toNativeSeparators("/")).last();
    qDebug() << "GetPath  : " << QDir::toNativeSeparators(gb.getPath() + "template/");
    qDebug() << "Remove   : " << file_path.remove(QDir::toNativeSeparators(gb.getPath() + "template/"));
    qDebug() << " ";
*/
            zip.setCreationPermissions(QFile::permissions(file_path));
            QByteArray ba = file.readAll();
            zip.addFile(file_path.remove(QDir::toNativeSeparators(gb.getPath() + "template/")), ba);

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
     //baseDir.mkpath(QDir::toNativeSeparators(QFileInfo(absPath).absolutePath()));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/progressbar"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/popupmenu"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/images/Bitmaps"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/toolbar"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/floater"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/menubar"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/toolpanel"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/accelerator"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Configurations2/statusbar"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/META-INF"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Pictures"));
     baseDir.mkpath(QDir::toNativeSeparators(baseDir.absolutePath()+"/Thumbnails"));

     QZipReader unzip ( gb.getPath() + FileName , QIODevice :: ReadOnly ) ;
     QList < QZipReader :: FileInfo > allFiles = unzip.fileInfoList() ;
     //QZipReader :: FileInfo fi;

     qDebug() << "UnzipFile: " + gb.getPath() + FileName;

     foreach (QZipReader :: FileInfo var, allFiles) {
         qDebug() << QString("Size:%1 Tipo:%2%3 FilePath:%4").arg
                     (QString::number(var.size),
                      QString::number(var.isDir),
                      QString::number(var.isFile),
                      var.filePath);
     }



     foreach ( QZipReader :: FileInfo fi , allFiles )
     {
     QString absPath = QDir::toNativeSeparators(baseDir.absolutePath() + "/" + fi.filePath) ;

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

    QFile f(QDir::toNativeSeparators(gb.getPath() + "template/content.xml"));

    //if (
    f.open(QFile::ReadOnly | QFile::Text);
    //{
    QTextStream in(&f);
    in.setCodec("UTF-8");
    //qDebug() << f.size();
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
