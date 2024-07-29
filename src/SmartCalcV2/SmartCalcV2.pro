QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    model/equationsolver.cc \
    main.cc \
    model/model.cc \
    model/parser.cc \
    model/polishtranslator.cc \
    model/supportive.cc \
    model/validator.cc \
    view/qcustomplot.cc \
    view/view.cc

HEADERS += \
    controller/controller.h \
    model/equationsolver.h \
    model/model.h \
    model/parser.h \
    model/polishtranslator.h \
    model/supportive.h \
    model/validator.h \
    view/qcustomplot.h \
    view/view.h

FORMS += \
    view/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
