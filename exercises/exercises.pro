TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp

HEADERS +=

INCLUDEPATH += C:\Armadillo\include


LIBS += -LC:\Armadillo\lib_win64
    -llapack_win64_MT
    -lblas_win64_MT
