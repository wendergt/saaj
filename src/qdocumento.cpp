#include "qdocumento.h"

void qDocumento::SaveODT()
{
    qDebug() << "Salvar documento: ";
    mGlobal gb;
    //*********************************************************************************************************
    QFile fi(gb.getPath("TEMP") + "content.xml");
    QFile fo(gb.getPath("TEMP") + "styles.xml");
    fi.open(QFile::WriteOnly | QFile::Text);
    fo.open(QFile::WriteOnly | QFile::Text);
    QTextStream outi(&fi);
    QTextStream outo(&fo);
    outi.setCodec("UTF-8");
    outo.setCodec("UTF-8");
    outi << texto;
    outo << stilo;
    fi.close();
    fo.close();
    //*********************************************************************************************************
    QZipWriter zip ( gb.getPath("DOC") + "AtaPronta.odt");
    zip.setCompressionPolicy(QZipWriter::AutoCompress);

    QDirIterator it(QDir::toNativeSeparators(gb.getPath("TEMP")),
                    QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    qDebug() << "ZipFile: " + gb.getPath("DOC") + "AtaPronta.odt";

    while(it.hasNext())
    {
        QString file_path = QDir::toNativeSeparators(it.next());

        qDebug() << QString("Size:%1 Tipo:%2%3 FilePath:%4").arg
                    (QString::number(it.fileInfo().size()), QString::number(it.fileInfo().isDir()),
                     QString::number(it.fileInfo().isFile()), it.filePath());
        //qDebug() << "Path com Remove >>>>> " << file_path.remove(gb.getPath("TEMP"));


        if (it.fileInfo().isDir())
        {
            zip.setCreationPermissions(QFile::permissions(file_path));
            zip.addDirectory(file_path.remove(gb.getPath("TEMP")));
        }

        if(it.fileInfo().isFile())
        {
            QFile file(file_path);

            if (!file.open(QIODevice::ReadOnly))
                continue;
            zip.setCreationPermissions(QFile::permissions(file_path));
            QByteArray ba = file.readAll();
            zip.addFile(file_path.remove(gb.getPath("TEMP")), ba);
            file.close();
        }
    }
    zip.close();
}

void qDocumento::LoadODT(QString FileName)
{
    mGlobal gb;
    QDir baseDir(gb.getPath("TEMP"));

    if ( baseDir.exists() )
    {
        baseDir.removeRecursively();
        baseDir.mkpath(gb.getPath("TEMP"));
    }
    else
    {
        baseDir.mkpath(gb.getPath("TEMP"));
    }

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

        if ( fi.isFile )
        {
            QFile file ( absPath ) ;
            if ( file.open ( QFile :: WriteOnly ) )
            {
                QApplication :: setOverrideCursor ( Qt :: WaitCursor ) ;
                file . write ( unzip. fileData ( fi.filePath ) , unzip. fileData ( fi.filePath ) . size ( ) ) ;
                file . setPermissions ( fi.permissions ) ;
                QApplication :: restoreOverrideCursor ( ) ;
                file . close ( ) ;
            }
        }
    }
    unzip. close ( ) ;

    qDebug() << "arquivo desempacotado com sucesso";
    //**********************************************************************************************************************

    QFile fi(gb.getPath("TEMP") + "content.xml");
    QFile fo(gb.getPath("TEMP") + "styles.xml");
    fi.open(QFile::ReadOnly | QFile::Text);
    fo.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&fi);
    QTextStream on(&fo);
    in.setCodec("UTF-8");
    on.setCodec("UTF-8");
    texto.append(in.readAll());
    stilo.append(on.readAll());

    qDebug() << "xml carregado com sucesso";
}

void qDocumento::PutData(QString key, QString dados)
{
    texto . replace ( key , dados ) ;
    stilo . replace ( key , dados ) ;
}

qDocumento::qDocumento(QString FileName, QWidget *parent) :
    QDialog(parent)
{
    mGlobal gb;

    LoadODT( FileName );

  //*************************** REPLACE DEFAULTS ************************************
    PutData("$_HORA.AGORA_$" , QTime::currentTime().toString());
    PutData("$_DATA_$" , QDate::currentDate().toString(Qt::SystemLocaleShortDate) );
    PutData("$_HORA_$" , QTime::currentTime().toString());

    PutData("$_NUMERO.PROCESSO_$","num.proc");
    PutData("$_COMARCA_$" , gb.getValue("config/comarca") );
    PutData("$_JUIZO_$" , gb.getValue("config/juizo") );
    PutData("$_VARA_$" , gb.getValue("config/vara") );
    PutData("$_NOME.PASSIVA_$" , gb.getValue("config/vara") );
    PutData("$_NOME.ATIVA_$" , "nomepassiva" );
    PutData("$_TIPO.DEPOENTE_$", gb.getValue("config/email"));
/*
    PutData("$_HORA_$" ,  );
    PutData("$_NUMERO.PROCESSO_$" ,  );
    PutData("$_INFRACAO_$" ,  );

    PutData("$_TIPO.PASSIVA_$" ,  );
    PutData("$_NOME.PASSIVA_$" ,  );
    PutData("$_QUALIFICACAO.PASSIVA_$" ,  );

    PutData("$_TIPO.ATIVA_$" ,  );
    PutData("$_NOME.ATIVA_$" ,  );
    PutData("$_QUALIFICACAO.ATIVA_$" ,  );

    PutData("$_TIPO.DEPOENTE_$" ,  );
    PutData("$_NOME.DEPOENTE_$" ,  );
    PutData("$_QUALIFICACAO.DEPOENTE_$" ,  );
    PutData("$_COMPROMISSADO_$" ,  );

    PutData("$_TIPO.PROMOTOR_$" ,  );
    PutData("$_NOME.PROMOTOR_$" ,  );

    PutData("$_TIPO.DEFENSOR_$" ,  );
    PutData("$_NOME.DEFENSOR_$" ,  );
*/
    PutData("$_TIPO.JUIZ_$" , gb.getValue("config/tipojuiz") );
    PutData("$_NOME.JUIZ_$" , gb.getValue("config/nomejuiz") );
    PutData("$_FORUM.NOME_$" , gb.getValue("config/forum") );
    PutData("$_FORUM.ENDERECO_$" , gb.getValue("config/endereco") );
    PutData("$_FORUM.TELEFONE_$" , gb.getValue("config/telefone") );
    PutData("$_FORUM.EMAIL_$" , gb.getValue("config/email") );

/*  <app>
        <user>loged.user</user>
        <application>SAAJ</application>
        <organization>NewRed Software Ltda</organization>
        <suport>mailto://admin@newred.com</suport>
    </app>
    <config>
        <tipo.juiz>Juíza de Direito</tipo.juiz>
        <nome.juiz>Anita Magdelaine Perez Belem</nome.juiz>
        <comarca>Comarca de Cacoal</comarca>
        <juizo>Juizado Especial Cível, Criminal e da Fazenda Pública</juizo>
        <vara>1ª Vara do Juizado Especial</vara>
        <forum>Fórum Ministra Sandra Nascimento - TJRO (www.tjro.jus.br)</forum>
        <endereco>1ª Vara do Juizado Especial</endereco>
        <telefone>1ª Vara do Juizado Especial</telefone>
        <email>1ª Vara do Juizado Especial</email>
    </config>
    <path>
        <DATA>/home/wender/.saaj/</DATA>
        <DB>/home/wender/.saaj/saaj.sqlite</DB>
        <DOC>/home/wender/.saaj/Documentos/</DOC>
        <TEMP>/home/wender/.saaj/template/</TEMP>
    </path>
    */

//***********************************************************************************************************************
    mainLay = new QVBoxLayout;
    labb = new QTextBrowser;
    QPushButton *btPrint= new QPushButton;
qDebug() << "put 8";
    btPrint->setStyleSheet("QPushButton{background-color:yellow;border: 1px solid gray;} "
                           "QPushButton:pressed {background-color: rgb(224, 0, 0);} "
                           "QPushButton:hover {background-color: rgb(224, 255, 0);}"
                           "QPushButton:hover:pressed{border: 1px solid red;}");

    btPrint->setMaximumWidth(150);

    //connect(printAction, SIGNAL(triggered(bool)), this, SLOT(doPrint()));
    connect(btPrint, SIGNAL(clicked()), this, SLOT(SaveODT()));

    mainLay->addWidget(btPrint);
    mainLay->addWidget(labb);

    this->setLayout(mainLay);
    //qDebug() << html;
}
