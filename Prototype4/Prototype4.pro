TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

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
    ../Train/Zaher/audiomidiconverter/z_audiomidiconverter.cpp \
    ../Train/Zaher/libmel/melfile.cpp \
    ../Train/Zaher/signal/mixer.cpp \
    ../Train/Zaher/audiowrite/audiowrite.cpp \
    ../Train/Zaher/audiowrite/aiffwrite.cpp \
    ../Train/Zaher/midi/midieotevent.cpp \
    ../Train/Zaher/midi/midievent.cpp \
    ../Train/Zaher/midi/midimanipulator.cpp \
    ../Train/Zaher/midi/midinoteevent.cpp \
    ../Train/Zaher/midi/midiprogramchangeevent.cpp \
    ../Train/Zaher/midi/miditempoevent.cpp \
    ../Train/Zaher/midi/miditextevent.cpp


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
    ../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h \
    ../Train/Zaher/libmel/melfile.h \
    ../Train/Zaher/signal/mixer.h \
    ../Train/Zaher/audiowrite/audiowrite.h \
    ../Train/Zaher/audiowrite/aiffwrite.h \
    ../Train/Zaher/midi/midieotevent.h \
    ../Train/Zaher/midi/midievent.h \
    ../Train/Zaher/midi/midimanipulator.h \
    ../Train/Zaher/midi/midinoteevent.h \
    ../Train/Zaher/midi/midiprogramchangeevent.h \
    ../Train/Zaher/midi/miditempoevent.h \
    ../Train/Zaher/midi/miditextevent.h


