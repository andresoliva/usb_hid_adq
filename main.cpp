#include <QtWidgets/QApplication>
#include "usb_hid_custom.h"
struct hid_device_info *MainWindow::devices;
//hid_device *MainWindow::connected_device;
int MainWindow::iDevice=1;
int MainWindow::countDevices=100;
bool MainWindow::BOOL_USB_SIM_TEST=false;//Simula que hay un dispo usb conectado, usando los datos de prueba
bool MainWindow::BOOL_USB_DATA_TEST=false;//Ignora los datos usb recibidos, aplasandolo con los de prueba
bool MainWindow::BOOL_DATA_TEST=false;
bool MainWindow::BOOL_PLOT_SIGNAL_Z=true;
bool MainWindow::BOOL_PLOT_SIGNAL_DZ=false;
bool MainWindow::BOOL_PLOT_SIGNAL_DZ_PB=false;
bool MainWindow::BOOL_PLOT_SIGNAL_DZ_PA=true;
bool MainWindow::BOOL_PLOT_SIGNAL_dZ=true;
bool MainWindow::PLOT_INVERT_SIGNAL_dZ=true;
bool MainWindow::PLOT_SIGNAL_dZ_PEAK=false;

 int MainWindow::LENGTH_PLOT=1000; //1000
 int MainWindow::LENGTH_CONVOLUTION=200;//200 defecto
 //***********sistema de hilos y graficado
 int MainWindow::FREQ_SAMPLE=1000;//Frecuencia cada el cual tomo data_DZ
 int MainWindow::TIME_PLOT=(MainWindow::LENGTH_CONVOLUTION*1000)/MainWindow::FREQ_SAMPLE;//Va en msegundos //Tiempo en microsegundos cada el cual grafica y resuelve convolucion

 int MainWindow::INDEX_MIN_processing=0;
 bool MainWindow::adquiriendo = false;
 bool MainWindow::procesando = false;
 bool MainWindow::detectando_picos = false;
 bool MainWindow::filtrado_signal = true;

 unsigned int MainWindow::transaction = 1;
 unsigned int MainWindow::intentos = 1;

 int MainWindow::time_minutes = 0;
 //Valores de Reloj
 double MainWindow::time_value = 0;
 double MainWindow::time_before = 0;
 double MainWindow::time_delta = 0 ;

 //Gasto Cardiaco
 QString MainWindow::qts_gasto_cardiaco_buffer;
 QTextStream MainWindow::qts_gasto_cardiaco(&MainWindow::qts_gasto_cardiaco_buffer);
 QString MainWindow::qts_freq_cardiaca_buffer;
 QTextStream MainWindow::qts_freq_cardiaca(&MainWindow::qts_freq_cardiaca_buffer);
 QString MainWindow::qts_Z0_buffer;
 QTextStream MainWindow::qts_Z0(&MainWindow::qts_Z0_buffer);
 QThread *Worker::usb_thread2 ;
 Worker *Worker::usb_thread_worker2 ;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        MainWindow w;
    w.show();
    qRegisterMetaType<QVector<double> >("QVector<double>");//Utilisado para pasar argumentos
    qRegisterMetaType<double *>("double *");
    return a.exec();
}
