QT       += core gui
QT+=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contact.cpp \
    interaction.cpp \
    main.cpp \
    crmga.cpp \
    sqldatatodo.cpp \
    todo.cpp \
    sqldataConatact.cpp \
    sqldatainteraction.cpp

HEADERS += \
    chrono_io.h \
    contact.h \
    crmga.h \
    date.h \
    interaction.h \
    sqldatatodo.h \
    todo.h \
    sqldataContact.h \
    sqldatainteraction.h

FORMS += \
    crmga.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
