TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    libaiff/aifx.c \
    libaiff/extended.c \
    libaiff/float32.c \
    libaiff/g711.c \
    libaiff/iff.c \
    libaiff/libaiff.c \
    libaiff/lpcm.c \
    libaiff/pascal.c \
    libaiff/z_util.c \
    AudioRead/aiffread.cpp \
    AudioRead/audioread.cpp



HEADERS += \
    libaiff/private.h \
    libaiff/libaiff/config.h \
    libaiff/libaiff/endian.h \
    libaiff/libaiff/libaiff.h \
    libaiff/z_util.h \
    AudioRead/aiffread.h \
    AudioRead/audioread.h

