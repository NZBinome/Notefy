TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wavFormat/diviseur.cpp \
    wavFormat/wavread.cpp \
    signal/complex.cpp \
    signal/signal.cpp \
    midi/midicreator.cpp \
    midi/note.cpp \
    freq/freqtable.cpp \
    signal/melody.cpp

HEADERS += \
    wavFormat/diviseur.h \
    wavFormat/wavread.h \
    signal/complex.h \
    signal/signal.h \
    midi/midicreator.h \
    midi/note.h \
    freq/freqtable.h \
    signal/melody.h

