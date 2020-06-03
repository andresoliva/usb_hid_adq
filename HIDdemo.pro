#-------------------------------------------------

#Comentarios:
#La linea reduntante (libsetupapi.a) agregada al final (para que se incluya correctamente la libreria mencionada)
#Parece haber solucionado el problema.
##------------------------------------------------------------------
#####Resumen 2:
#### Tras cambiar la interfaz, no hubo mejoras respecto de la cantidad de data_DZ.
##----------Es decir, hay q modificar el protocolo desde el pic, el, grafico solo hace una especie de diesmado
##Y encima interpola linealmente la porqueria esta.
###Nota 2: Los DLL que se debén meter en la carpeta, dependen DEL COMPILADOR
#----------------Si se cambia de compilador, se deben cambiar los dll que acompañan al ejecutable.
##-------------------------------------------------

QT       += core gui
QT       += testlib     #Ussar bandera qt
#DEFINES += QT_NO_DEBUG_OUTPUT #anula la salid de Debug_custom
QT += gui # desaparece la consola de salida

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = HIDdemo
TEMPLATE = app


SOURCES += main.cpp \
    ../QTLibs/QCustomPlot_5/qcustomplot.cpp \
    thread_worker.cpp \
    peak_detection.cpp \
    digital_processing.cpp \
    usb_hid_custom.cpp \
    ui_interface_display.cpp \
    ui_interface_functions.cpp
win32:      SOURCES += ../QTLibs/hidapi-0.7.0/windows/hid.c
#unix:!macx: SOURCES += ../QTLibs/hidapi-0.7.0/linux/hid.c

HEADERS  += \
    ../QTLibs/QCustomPlot_5/qcustomplot.h \
    ../QTLibs/hidapi-0.7.0/hidapi/hidapi.h \
    setupapi.h \
    thread_worker.h \
    filtros.h \
    peak_detection.h \
    ui_PC-HID.h \
    digital_processing.h \
    usb_hid_custom.h \
    ui_interface_display.h \
    ui_interface_functions.h

FORMS    += \
    ui_usb_hid_adq.ui

INCLUDEPATH += ../QTLibs/hidapi-0.7.0/hidapi
win32: LIBS += ../QTLibs/MinGW/libsetupapi.a
#win32: LIBS += -L$$PWD/../QTLibs/MinGW/libsetupapi.a

INCLUDEPATH += $$PWD/../QTLibs/MinGW
DEPENDPATH += $$PWD/../QTLibs/MinGW-


#unix:!macx: LIBS += -ludev

OTHER_FILES += \
Win32:RC_FILE += App.rc
#win64:RC_FILE += App.rc
DISTFILES += \
    filtro_pasaaltos_example.dat \
    filtro_pasabajos_example.dat \
    libwinpthread-1.dll \
    filtro_pasaaltos.dat \
    filtro_pasabajos.dat \
    andres martes_30sec.cvs \
    andres martes_30sec.cvs
#Siempre al final
CONFIG+= -static-libgcc -static-libstdc++ -l:libwinpthread.a -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
#QMAKE_LFLAGS =-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
#QMAKE_LFLAGS+=-static -static-libgcc -static-libstdc++ -lstdc++
QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -l:libwinpthread.a#NO COMENTAR


#DEFINES+=STATIC
#http://www.qtcentre.org/threads/29489-Removing-dependencies-for-mingwm10-dll-and-libgcc_s_dw2-1-dll-static-linking
#CONFIG += c++11
#LIBS += "./libwinpthread-1.dll"
