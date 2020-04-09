#-------------------------------------------------
#
# Project created by QtCreator 2019-10-10T20:49:16
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xmlpatterns

TARGET = pic_checker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tests_window.cpp \
    test_viewer_window.cpp \
    test_meta_window.cpp \
    object_entry_window.cpp

HEADERS += \
        mainwindow.h \
    prep.h \
    xml_parser_handler.h \
    xml_schema_validator.h \
    test_meta_window.h \
    tests_window.h \
    test_viewer_window.h \
    object_entry_window.h

FORMS += \
        mainwindow.ui \
    test_meta_window.ui \
    tests_window.ui \
    test_viewer_window.ui \
    object_entry_window.ui
