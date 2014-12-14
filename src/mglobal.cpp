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
    apath = QDir::home().path();
#ifdef Q_OS_LINUX
    apath.append("/.saaj/");
#else
    apath.append("/AppData/Local/Saaj/");
#endif
    qDebug() << "No-Native-GetPath: " + apath;
    apath = QDir::toNativeSeparators(apath);
    qDebug() << "   Native-GetPath: " + apath;
    QDir dir;
    dir.setPath(apath);
    if (!dir.exists()){dir.mkdir(apath);}

//************************************************ DATA *******************************************
    adata = QDate::currentDate();


    XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    settings = new QSettings(apath+"config.xml", XmlFormat);

    settings->beginGroup("config");
    settings->setValue("application", "SAAJ");
    settings->setValue("organization", "NewRed Software Ltda");
    settings->setValue("suport", "mailto://admin@newred.com");
    settings->setValue("USER", "loged.user");
    settings->endGroup();

    settings->beginGroup("path");
    settings->setValue("DATA", apath);
    settings->setValue("DOC", apath + "Documentos/");
    settings->setValue("DB", apath);
    settings->setValue("TEMP", apath + "template/");
    settings->endGroup();
}

mGlobal::~mGlobal()
{

}

QString mGlobal::getPath()
{
    //qDebug() << "Returned Settings: " << settings->value("path/DATA").toString();
    return settings->value("path/DATA","").toString();
}

QString mGlobal::getData()
{
    return adata.toString(Qt::LocalDate);
}
