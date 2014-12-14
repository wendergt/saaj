#-------------------------------------------------
#
# Project created by QtCreator 2014-09-09T15:33:57
#
#-------------------------------------------------

QT       += core gui sql
#INCLUDEPATH += C:/Qt/quazip-0.7/quazip
#LIBS += -LC:/Qt/quazip-0.7/quazip/release -lquazip
#INCLUDEPATH += $$[QT_INSTALL_PREFIX])/Src/qtbase/src/3rdparty/zlib
#LIBS += -L$$[QT_INSTALL_PREFIX])/Src/qtbase/src/3rdparty/zlib -lz

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#contains( QT_CONFIG, system-zlib ) {
#  if( unix|win32-g++* ): LIBS += -lz
#  else: LIBS += zdll.lib
#} else {
#  INCLUDEPATH += $$PWD
#}

TARGET = saaj
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    databasemanager.cpp \
    qproc.cpp \
    qeditprocesso.cpp \
    qparte.cpp \
    qfinddlg.cpp \
    qformedit.cpp \
    qdocumento.cpp \
    mglobal.cpp

HEADERS  += widget.h \
    databasemanager.h \
    qproc.h \
    qeditprocesso.h \
    qparte.h \
    qfinddlg.h \
    qformedit.h \
    qdocumento.h \
    mglobal.h \
    connection.h \
    qzipreader_p.h \
    qzipwriter_p.h

RESOURCES += \
    recurso.qrc
