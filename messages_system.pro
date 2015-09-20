TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    messages/message.cpp \
    strucutures/queue.cpp \
    subjects/sender.cpp

HEADERS += \
    message.h \
    messages/message.h \
    strucutures/queue.h \
    subjects/sender.h
