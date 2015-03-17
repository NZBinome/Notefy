TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    myvst/myvst.cpp

HEADERS += \
    vst/aeffect.h \
    vst/aeffectx.h \
    vst/vstfxstore.h \
    myvst/myvst.h

