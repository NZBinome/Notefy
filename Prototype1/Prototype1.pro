#-------------------------------------------------
#
# Project created by QtCreator 2014-09-30T16:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Prototype1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../ZayZaPhone/zayzaphone/midiwrite.cpp \
    ../../ZayZaPhone/zayzaphone/mynote.cpp \
    ../../ZayZaPhone/zayzaphone/wavtable.cpp \
    ../../ZayZaPhone/zayzaphone/wizjet.cpp \
    ../../ZayZaPhone/zayzaphone/wnkn.cpp \
    signal/signal.cpp \
    wavFormat/wavread.cpp \
    ../../ZayZaPhone/zayzaphone/wavread2.cpp \
    rasmeh.cpp \
    signal/complex.cpp \
    midi/note.cpp \
    wavFormat/diviseur.cpp \
    midi/midicreator.cpp

HEADERS  += mainwindow.h \
    signal.h \
    ../../ZayZaPhone/zayzaphone/midiwrite.h \
    ../../ZayZaPhone/zayzaphone/mynote.h \
    ../../ZayZaPhone/zayzaphone/wavtable.h \
    ../../ZayZaPhone/zayzaphone/wizjet.h \
    ../../ZayZaPhone/zayzaphone/wnkn.h \
    signal/signal.h \
    wavFormat/wavread.h \
    ../../ZayZaPhone/zayzaphone/wavread2.h \
    rasmeh.h \
    signal/complex.h \
    midi/note.h \
    wavFormat/diviseur.h \
    midi/midicreator.h \
    freq/freqtable.h

FORMS    += mainwindow.ui
