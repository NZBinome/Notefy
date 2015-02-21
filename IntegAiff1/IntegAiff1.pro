TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wavFormat/diviseur.cpp \
    wavFormat/wavread.cpp \
    signal/complex.cpp \
    signal/melody.cpp \
    signal/signal.cpp \
    midi/midicreator.cpp \
    midi/note.cpp \
    libaiff/aifx.c \
    libaiff/extended.c \
    libaiff/float32.c \
    libaiff/g711.c \
    libaiff/iff.c \
    libaiff/libaiff.c \
    libaiff/lpcm.c \
    libaiff/pascal.c \
    libaiff/z_util.c \
    freq/freqtable.cpp \
    AudioRead/aiffread.cpp \
    AudioRead/audioread.cpp \
    audiomidiconverter/z_audiomidiconverter.cpp

HEADERS += \
    wavFormat/diviseur.h \
    wavFormat/wavread.h \
    signal/complex.h \
    signal/melody.h \
    signal/signal.h \
    midi/midicreator.h \
    midi/note.h \
    libaiff/private.h \
    libaiff/z_util.h \
    libaiff/libaiff/config.h \
    libaiff/libaiff/endian.h \
    libaiff/libaiff/libaiff.h \
    freq/freqtable.h \
    AudioRead/aiffread.h \
    AudioRead/audioread.h \
    audiomidiconverter/z_audiomidiconverter.h

