#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T10:51:00
#
#-------------------------------------------------

QT += core gui\
    multimedia\
    network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draw_snake.cpp \
    snake_algorithm.cpp \
    theme_window.cpp \
    options.cpp \
    snake_coord.cpp

HEADERS  += mainwindow.h \
    draw_snake.h \
    snake_algorithm.h \
    theme_window.h \
    options.h \
    snake_coord.h \
    content.h \
    array.h

FORMS    += \
    mainwindow.ui \
    theme_window.ui \
    options.ui

RESOURCES += \
    themes.qrc \
    sound.qrc \
    buttons.qrc
