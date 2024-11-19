QT       += core gui widgets

TARGET = EVA
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/ColorBox.cpp \


HEADERS += \
    src/MainWindow.h \
    src/ColorBox.h \

INCLUDEPATH += \
    src \


# 默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target