#ifndef USB_HID_CUSTOM_H
#define USB_HID_CUSTOM_H

#include <QMainWindow>
#include <QElapsedTimer> // ???
#include <QTime>
#include "hidapi.h"
#include <QByteArray> //para ahcer arreglos de bits
#include <QBitArray>
//***********sistema de hilos y graficado
#include <QThread>
#include "thread_worker.h"
#include <QTextStream>
#include <QFile>
//Variables iclyudas para el testeo
#define QDEBUG
#ifdef QDEBUG
    #include <QDebug>
    #define Debug_custom qDebug
    #define QDEBUG_CUSTOM(x)(qDebug(x)
#endif
#ifndef QDEBUG
    #define Debug_custom //
    #define QDEBUG_CUSTOM(x){}
#endif

#define K_KUBICEK 135 // [cm*ohm]Constante de la ecuación de kubicek
#define K_SAMEK 4.25

#define DATA_SAMPLE 1000000 //Cantidad maxima de data_DZ
#define DIEZMADO 1 //valor a diesmar
#define DATA_DIEZMADA (DATA_SAMPLE/DIEZMADO)

#define SAMPLES_DECIMATE  0//Min 30 por razones que desconosco Numero de data_DZ iniciales a eliminar
#define Vref 3300

#define USB_BUFFER 64  //Tamaño de datos transferidos

#define USB_BUFFER_WRITE 65//Debe ser USB_BUFFER+1 //Tamaño de datos transferidos EN ESCRITURA

#define DATA_BUFFER 6 //Tamaño de datos enviados
#define DATA_BUFFER_1_CH 2 //Tamaño de datos enviados
#define DATA_BUFFER_2_CH 4 //Tamaño de datos enviados
#define usb_vendor_id_device 1240//4d8 hex 1240 dec
#define usb_product_id_device 63//3f hex 6 hex

//## HS-ULM HID CTRL  I N S T R U C T I O N    D E F I N I T I O N S ###########
typedef enum {
    CID_INIT              = 0x00,
    CID_DEVICE            = 0x10,    //Envia a la interfaz datos de identificación
    CID_LED_USB_MASTER    = 0x30,    //Manejo de lus led del master
    CID_LED_ERROR_SLAVE   = 0x40,    //Manejo de lus led del esclavo
    CID_TEST              = 0x50,    //Configura el ADC para que solo envie señal de prueba
    CID_ADQ               = 0x60,    //Inicia peticion de datos analogicos
    CID_STOP              = 0x70,    //Inicia petición de stop
    CID_ADQ_TIMER         = 0x80,    //Permite configurar la frecuencia de muestreo
    CID_DDS_SETUP         = 0x90,    //Cambia Configuración del generador  DDS
    ID_MESSAGE            = 0xE0,
    ID_ERROR              = 0xFF
}COMMANDS;

hid_device_info *usb_check_device_aviable(void);
hid_device *usb_device_connect(hid_device_info *hid_dev_info);
void usb_device_disconnect(hid_device *connected_device);
static unsigned char usb_buffer_recep[64];

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static bool BOOL_USB_SIM_TEST;//Simula que hay un dispo usb conectado, usando los datos de prueba
    static bool BOOL_USB_DATA_TEST;//Ignora los datos usb recibidos, aplasandolo con los de prueba
    static bool BOOL_DATA_TEST;
    static bool BOOL_PLOT_SIGNAL_Z;
    static bool BOOL_PLOT_SIGNAL_DZ;
    static bool BOOL_PLOT_SIGNAL_DZ_PB;
    static bool BOOL_PLOT_SIGNAL_DZ_PA;
    static bool BOOL_PLOT_SIGNAL_dZ;
    static bool PLOT_INVERT_SIGNAL_dZ;
    static bool PLOT_SIGNAL_dZ_PEAK;
     static int LENGTH_PLOT; //1000
     static int LENGTH_CONVOLUTION;//200 defecto

    //***********sistema de hilos y graficado

     static int FREQ_SAMPLE;//Frecuencia cada el cual tomo data_DZ
     static int TIME_PLOT;//=(LENGTH_CONVOLUTION/FREQ_SAMPLE); //Tiempo en microsegundos cada el cual grafica y resuelve convolucion
     double GAIN_Z=1; //Ganancia comun a las impedancias
     double GAIN_Z0=1; //Ganancia unica de Z0
     double GAIN_DZ=0; //Ganancia unica de Delta Z
     double GAIN_Z0_TOTAL;//Ganancia total de Z0
     double GAIN_DZ_TOTAL;//Ganancia total de Delta Z
     double GAIN_DERIVADA=-1000;//Es la inversa de la frecuencia
     double Z0_OFFSET=0000;
     double Z0_OFFSET_TOTAl; //Ganancia unica de Z0
     double TRESHOLD=100;
     double TRESHOLD_ESCALA=0.5;
     int VENTANA_PEAK_FIRST=150;
     int VENTANA_PEAK=125;
     double DISTANCIA_ELECTRODOS=0;//Distancia electrodo -electrodo
     double processing_INIT;
     double processing_END;
     double y_axis_DZ_max,y_axis_DZ_min,y_axis_dZ_max,y_axis_dZ_min;
     static QString qts_gasto_cardiaco_buffer;
     static QString qts_freq_cardiaca_buffer;
     static QTextStream qts_gasto_cardiaco;
     static QTextStream qts_freq_cardiaca;
     static QString qts_Z0_buffer;
     static QTextStream qts_Z0;
     static int INDEX_MIN_processing;//200 defecto
    //Variables del sistema de hilos y graficado
     double *time_pointer, *data_pointer, *data_cc_pointer,*pointer_data_max_inicial;
     int     index_pointer,index_pointer_max;
     void processing_setup();//Se declara aca porque comparte variables.
     void read_real_table(const char* filename,QVector<double> &aux, int &length );
     void filtrado(QVector<double> data_DZ,QVector<double> &data_DZ_pasaaltos,QVector<double> filtro,QVector<double> filtro_pasaaltos,int &length);
     int i,j,length_conv,data_index,data_index_diezmado;
     QVector<double> data_time,data_DZ,data_Z,data_time_ejemplo,data_DZ_ejemplo;
     QVector<double> data_DZ_pasabajos,data_DZ_pasabajos_ruido,data_DZ_diezmadas,aux; // initialize with entries 0..100
     QVector<double> data_DZ_diezmado;
     QVector<double> x_diezmado;
     QVector<double> data_DZ_pasaaltos;
     QVector<double> data_dZ,data_dZ_segunda;
     QVector<double> filtro;
     QVector<double> filtro_pasaaltos;
     QVector<double> filtro_pasabajos_ruido;
     QVector<int> dZ_peak_i;//Guarda los indices de los picos
     int dZ_peak_i_anterior=0;
     QVector<double> dZ_peak_t;
     QVector<double> dZ_peak;
     double dz_pico_medio=0;
     QVector<double> Z0,DZ0;
     double DZ_RESET;
     QVector<double> T_EV,T_cardio;//Tiempo e eyección ventricular, y periodo cardiaco, respectivamente
     QVector<double> GC_kubicek,GC_samek;//Guarda los resultados de los calculos.

     static struct hid_device_info *devices;
    // static hid_device *connected_device;
     static int iDevice;
     static int countDevices;
     static bool adquiriendo;
     static bool procesando;
     static bool detectando_picos;
     static bool filtrado_signal;
     static unsigned int transaction;
     static unsigned int intentos;
     int flag_spi;
     int flag_time_plot=0;
     static int time_minutes;
     int time_plot = 0;
     //Valores de datos
     static double peak_min;
     static double peak_max;
     static double peak_peak;
     static double sum;
     static  double mean;
     static double variance;
     //Valores de Reloj
     static double time_value;
     static double time_before;
     static double time_delta_max;
     static double time_delta_min;
     static double time_delta;
     static double time_sum;
     static double time_mean;
     static double time_variance;
     //Empleados en las formulas de kubicek y Samek

     //int counter_recepcion=0;
     QTimer *RXtimer;
     QElapsedTimer USBelapsedtimer;
     QTimer *PLOTtimer;



private slots:
//Correspondiente al sistema de hilos.
    void data_pointer_call(const double *pointer_time,const double *pointer_data,const double *pointer_cc_data, int index);
    void processing_adquisicion();
    void processing(int &data_index_p,int data_index_p_length);
    void plot();
    void leer_botones();
    //void change_X(QCPRange);
    void on_btnConnect();
    void on_rbZoomClicked();
    void on_wheel_axis();
    void on_btnSave();
    void on_btnOpen();
    void on_btnProcesar();
    void on_scrollArea_destroyed();
    void create_thread_usb(const QObject *receiver);
    void delete_thread_usb(const QObject *receiver);


private:
    Ui::MainWindow *ui;
    QTimer *plot_timer;
    QThread *usb_thread;
    /**

     * @brief Object which contains methods that should be runned in another thread
     */
    Worker *usb_thread_worker;
};

#endif // USB_HID_CUSTOM_H
