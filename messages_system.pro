TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    messages/message.cpp \
    strucutures/queue.cpp \
    subjects/sender.cpp \
    subjects/receiver.cpp \
    dispatcher.cpp \
    templatedispatcher.cpp

HEADERS += \
    message.h \
    messages/message.h \
    strucutures/queue.h \
    subjects/sender.h \
    subjects/receiver.h \
    dispatcher.h \
    templatedispatcher.h
