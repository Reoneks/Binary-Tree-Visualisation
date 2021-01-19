QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binarytreedata.cpp \
    binarytreefunctions.cpp \
    datainput.cpp \
    endcredits.cpp \
    fileselectionform.cpp \
    helpform.cpp \
    jsoncsvload.cpp \
    jsoncsvsave.cpp \
    main.cpp \
    mainwindow.cpp \
    test.cpp

HEADERS += \
    binarytreedata.h \
    binarytreeelement.h \
    binarytreefunctions.h \
    datainput.h \
    endcredits.h \
    fileselectionform.h \
    helpform.h \
    jsoncsvload.h \
    jsoncsvsave.h \
    mainwindow.h \
    test.h

FORMS += \
    datainput.ui \
    endcredits.ui \
    fileselectionform.ui \
    helpform.ui \
    mainwindow.ui

RC_ICONS += tree8bit.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Media.qrc