#include "mglobal.h"

bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map)
{
    QXmlStreamReader xmlReader(&device);
    QStringList elements;

    // Solange Ende nicht erreicht und kein Fehler aufgetreten ist
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        // Nächsten Token lesen
        xmlReader.readNext();

        // Wenn Token ein Startelement
        if (xmlReader.isStartElement() && xmlReader.name() != "Settings") {
            // Element zur Liste hinzufügen
            elements.append(xmlReader.name().toString());
            // Wenn Token ein Endelement
        } else if (xmlReader.isEndElement()) {
            // Letztes Element löschen
            if(!elements.isEmpty()) elements.removeLast();
            // Wenn Token einen Wert enthält
        } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
            QString key;

            // Elemente zu String hinzufügen
            for(int i = 0; i < elements.size(); i++) {
                if(i != 0) key += "/";
                key += elements.at(i);
            }

            // Wert in Map eintragen
            map[key] = xmlReader.text().toString();
        }
    }

    // Bei Fehler Warnung ausgeben
    if (xmlReader.hasError()) {
        qWarning() << xmlReader.errorString();
        return false;
    }

    return true;
}

bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    QXmlStreamWriter xmlWriter(&device);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Settings");

    QStringList prev_elements;
    QSettings::SettingsMap::ConstIterator map_i;

    // Alle Elemente der Map durchlaufen
    for (map_i = map.begin(); map_i != map.end(); map_i++) {

        QStringList elements = map_i.key().split("/");

        int x = 0;
        // Zu schließende Elemente ermitteln
        while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
            x++;
        }

        // Elemente schließen
        for(int i = prev_elements.size() - 1; i >= x; i--) {
            xmlWriter.writeEndElement();
        }

        // Elemente öffnen
        for (int i = x; i < elements.size(); i++) {
            xmlWriter.writeStartElement(elements.at(i));
        }

        // Wert eintragen
        xmlWriter.writeCharacters(map_i.value().toString());

        prev_elements = elements;
    }

    // Noch offene Elemente schließen
    for(int i = 0; i < prev_elements.size(); i++) {
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    return true;
}



mGlobal::mGlobal(QObject *parent) :
    QObject(parent)
{
    //****************************************** PATH *********************************************
    QString BaseDir = QDir::home().path();
    QString DocDir  = QDir::home().path();

#ifdef Q_OS_LINUX
    BaseDir.append("/.saaj/");
    DocDir. append("/.saaj/Documentos/Audiencias/");
#else
    BaseDir.append("/AppData/Local/Saaj/");
    DocDir. append("/Documents/Audiencias/");
#endif

    BaseDir = QDir::toNativeSeparators(BaseDir);
    DocDir  = QDir::toNativeSeparators(DocDir);

    QDir dir;
    dir.setPath(BaseDir);
    if (!dir.exists()){dir.mkdir(BaseDir);}
    dir.setPath(DocDir);
    if (!dir.exists()){dir.mkdir(DocDir);}

    //************************************************ CONFIG *******************************************

    XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);

    QFile f(BaseDir+"config.xml");

    if ( f.exists() )
    {
        settings = new QSettings(BaseDir+"config.xml", XmlFormat);
    }
    else
    {
        settings = new QSettings(BaseDir+"config.xml", XmlFormat);

        settings->beginGroup("app");
        settings->setValue("application", "SAAJ");
        settings->setValue("organization", "NewRed Software Ltda");
        settings->setValue("suport", "mailto://admin@newred.com");
        settings->setValue("user", "loged.user");
        settings->endGroup();

        settings->beginGroup("config");
        settings->setValue("comarca","Comarca de Cacoal");
        settings->setValue("vara","1ª Vara do Juizado Especial");
        settings->setValue("email","email@tjro.jus.br");
        settings->setValue("endereco","Av. Proto Velho, Cacoal");
        settings->setValue("forum","Fórum Ministra Sandra Nascimento - TJRO (www.tjro.jus.br)");
        settings->setValue("juizo","Juizado Especial Cível, Criminal e da Fazenda Pública");
        settings->setValue("tipojuiz","Juíza de Direito");
        settings->setValue("nomejuiz","Anita Magdelaine Perez Belem");
        settings->setValue("telefone","(69) 3441-0835");
        settings->endGroup();

        settings->beginGroup("path");
        settings->setValue("DATA", BaseDir);
        settings->setValue("DOC", DocDir);
        settings->setValue("DB", BaseDir + "saaj.sqlite");
        settings->setValue("TEMP", BaseDir + "template/");
        settings->endGroup();
    }
}

mGlobal::~mGlobal()
{

}

QString mGlobal::getPath(QString path)
{
    //qDebug() << "getPath: " << settings->value("path/"+path).toString();
    return QDir::toNativeSeparators(settings->value("path/"+path,"").toString());
}

QString mGlobal::getValue(QString key)
{
    qDebug() << "getVallue: " + key + "= " + settings->value(key,"").toString();
    return settings->value(key,"").toString();
}
