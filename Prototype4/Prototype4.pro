TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../Train/Zaher/wavFormat/diviseur.cpp \
    ../Train/Zaher/audioread/wavread.cpp \
    ../Train/Zaher/signal/complex.cpp \
    ../Train/Zaher/signal/melody.cpp \
    ../Train/Zaher/signal/signal.cpp \
    ../Train/Zaher/midi/midicreator.cpp \
    ../Train/Zaher/midi/musicinstrument.cpp \
    ../Train/Zaher/util/util.cpp \
    ../Train/Zaher/midi/note.cpp \
    ../Train/Zaher/libaiff/aifx.c \
    ../Train/Zaher/libaiff/extended.c \
    ../Train/Zaher/libaiff/float32.c \
    ../Train/Zaher/libaiff/g711.c \
    ../Train/Zaher/libaiff/iff.c \
    ../Train/Zaher/libaiff/libaiff.c \
    ../Train/Zaher/libaiff/lpcm.c \
    ../Train/Zaher/libaiff/pascal.c \
    ../Train/Zaher/libaiff/z_util.c \
    ../Train/Zaher/freq/freqtable.cpp \
    ../Train/Zaher/audioread/aiffread.cpp \
    ../Train/Zaher/audioread/audioread.cpp \
    ../Train/Zaher/audiomidiconverter/z_audiomidiconverter.cpp


HEADERS += \
    ../Train/Zaher/wavFormat/diviseur.h \
    ../Train/Zaher/audioread/wavread.h \
    ../Train/Zaher/signal/complex.h \
    ../Train/Zaher/signal/melody.h \
    ../Train/Zaher/signal/signal.h \
    ../Train/Zaher/midi/midicreator.h \
    ../Train/Zaher/midi/musicinstrument.h \
    ../Train/Zaher/util/util.h \
    ../Train/Zaher/midi/note.h \
    ../Train/Zaher/libaiff/private.h \
    ../Train/Zaher/libaiff/z_util.h \
    ../Train/Zaher/libaiff/libaiff/config.h \
    ../Train/Zaher/libaiff/libaiff/endian.h \
    ../Train/Zaher/libaiff/libaiff/libaiff.h \
    ../Train/Zaher/freq/freqtable.h \
    ../Train/Zaher/audioread/aiffread.h \
    ../Train/Zaher/audioread/audioread.h \
    ../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h


