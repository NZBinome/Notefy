TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../App_prot_1/wavFormat/diviseur.cpp \
    ../App_prot_1/wavFormat/wavread.cpp \
    ../App_prot_1/signal/complex.cpp \
    ../App_prot_1/signal/melody.cpp \
    ../App_prot_1/signal/signal.cpp \
    ../App_prot_1/midi/midicreator.cpp \
    ../App_prot_1/midi/musicinstrument.cpp \
    ../App_prot_1/midi/note.cpp \
    ../App_prot_1/libaiff/aifx.c \
    ../App_prot_1/libaiff/extended.c \
    ../App_prot_1/libaiff/float32.c \
    ../App_prot_1/libaiff/g711.c \
    ../App_prot_1/libaiff/iff.c \
    ../App_prot_1/libaiff/libaiff.c \
    ../App_prot_1/libaiff/lpcm.c \
    ../App_prot_1/libaiff/pascal.c \
    ../App_prot_1/libaiff/z_util.c \
    ../App_prot_1/freq/freqtable.cpp \
    ../App_prot_1/audioread/aiffread.cpp \
    ../App_prot_1/audioread/audioread.cpp \
    ../App_prot_1/audiomidiconverter/z_audiomidiconverter.cpp


HEADERS += \
    ../App_prot_1/wavFormat/diviseur.h \
    ../App_prot_1/wavFormat/wavread.h \
    ../App_prot_1/signal/complex.h \
    ../App_prot_1/signal/melody.h \
    ../App_prot_1/signal/signal.h \
    ../App_prot_1/midi/midicreator.h \
    ../App_prot_1/midi/musicinstrument.h \
    ../App_prot_1/midi/note.h \
    ../App_prot_1/libaiff/private.h \
    ../App_prot_1/libaiff/z_util.h \
    ../App_prot_1/libaiff/libaiff/config.h \
    ../App_prot_1/libaiff/libaiff/endian.h \
    ../App_prot_1/libaiff/libaiff/libaiff.h \
    ../App_prot_1/freq/freqtable.h \
    ../App_prot_1/audioread/aiffread.h \
    ../App_prot_1/audioread/audioread.h \
    ../App_prot_1/audiomidiconverter/z_audiomidiconverter.h


