TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        application.cpp \
        bmp.cpp \
        dir.cpp \
        foodwidget.cpp \
        lcd.cpp \
        loginwidget.cpp \
        main.cpp \
        mainwidget.cpp \
        mfont.cpp \
        shopcarwidget.cpp \
        singledish.cpp \
        touch.cpp \
        widget.cpp

DISTFILES +=

HEADERS += \
    application.h \
    bmp.h \
    dir.h \
    font.h \
    foodwidget.h \
    lcd.h \
    loginwidget.h \
    mainwidget.h \
    mfont.h \
    shopcarwidget.h \
    singledish.h \
    touch.h \
    widget.h
