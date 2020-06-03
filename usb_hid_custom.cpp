#include <usb_hid_custom.h>
#include <QTimer>
#include <QtMath> //uso de qpow: elevar potencias
#include <QElapsedTimer> //permite contar intervalos menores a 1 milisegundo
#include <QString>
#include <QByteArray> //Byte Array
#include <QBitArray>
//#include <QTest> //Usar delay y que aparesca en pantalla
#include <QVector>
#include <iostream>
//#include <iomanip> //añadir espacios al exportar datos
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
//#include <QFileDialog>
#include <QMessageBox>//Pop Up al apretar un boton
#include "PC-HID.h"
#include "ui_ui_usb_hid_adq.h"
#include "digital_processing.h"
#include "peak_detection.h"
#include "thread_worker.h"
#include <filtros.h>
#include <unistd.h> //Para función sleep
//#include "QLibrary"//Para incluir version
#include <QDialog>

#define VERSION "Medidor de Gasto Cardiaco AOT™"

    //inicializa la variable staticas.

      //del Sistema de Hilos
//##############################################################################
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(VERSION);


//lectura de datos
MainWindow::processing_setup(); //
//----Armado de las variables para Poder procesar.
    flag_spi=0;
    plot_timer = NULL;
    //connect(RXtimer, SIGNAL(timeout()), this, SLOT(rxHandler()));
    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(on_btnConnect()));
    connect(ui->rbZoomH,SIGNAL(clicked()), SLOT(on_rbZoomClicked()));
    connect(ui->rbZoomV,SIGNAL(clicked()), SLOT(on_rbZoomClicked()));
    connect(ui->rbZoomVH,SIGNAL(clicked()), SLOT(on_rbZoomClicked()));
    connect(ui->btnSave, SIGNAL(clicked()), SLOT(on_btnSave()));
    connect(ui->btnOpen, SIGNAL(clicked()), SLOT(on_btnOpen()));
    connect(ui->btnProcesar, SIGNAL(clicked()), SLOT(on_btnProcesar()));
    //connect(ui->plot, SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(on_wheel_axis()));//Si el objeto emite señal de finish, lo termina
    //qts_gasto_cardiaco<<c;
   // ui->result_GC->setText(ts.readAll());
    ui->tabDemo->setEnabled(true);

    //create_thread_usb(this);
    plot_timer = new QTimer(this);
    connect(plot_timer, SIGNAL(timeout()), this, SLOT(processing_adquisicion()));//Grafica mientras haya datos para plot
}

//##############################################################################
MainWindow::~MainWindow()
{
    delete_thread_usb(this);
    delete ui;
}

//##############################################################################


//##############################################################################
void MainWindow::on_btnConnect()
{
    struct hid_device_info *cur_dev;
    //ui->tabDemo->setDisabled(true);
    adquiriendo=false;
    if(ui->btnConnect->text() == "Iniciar Adquisición"){
        //Seteo el sistema según las opciones seleccionadas:
        #ifdef Debug_custom
        Debug_custom() <<  "Dispositivos Detectados";
        #endif
        leer_botones();
        cur_dev=usb_check_device_aviable();
        if(cur_dev==NULL){Debug_custom() <<  "interface number "<<"NULL";}
            else{
            Debug_custom() <<  "interface number "<<(cur_dev->interface_number);
                    ui->btnConnect->setText("conectando....");
                        #ifdef Debug_custom
                        Debug_custom() <<  "conectando";
                        #endif
                    time_minutes = 0;
                    index_pointer=0;
                    index_pointer_max=0;
                    data_index=0;
                    dZ_peak_i[0]=0;
                    adquiriendo=true;
                    ui->lcdcounter->display(4400);
                    ui->tabDemo->setEnabled(true);
                    ui->rbZoomH->setDisabled(true);
                    ui->rbZoomV->setDisabled(true);
                    ui->rbZoomVH->setDisabled(true);
                   // Worker::usb_thread_receiver=this;
                    //usb_thread_receiver
                    //Worker::thread_create_usb2(Worker::usb_thread2,Worker::usb_thread_worker2,this);
                    create_thread_usb(this);
                    //usb_thread_worker->requestWork();
                    plot_timer->start(TIME_PLOT);
                    ui->btnConnect->setText("Detener Adquisición");
                }
     if (adquiriendo==false){
     if (BOOL_USB_SIM_TEST==false){
        QMessageBox::critical(this,tr("ERROR"),tr("No se encuentra el dispositivo: Revise la conexión"),tr("Aceptar"));
        }
        else//Simula que adquiere valores
         {   ui->btnConnect->setText("conectando....");
            ui->tabDemo->setEnabled(true);
            ui->rbZoomH->setDisabled(true);
            ui->rbZoomV->setDisabled(true);
            ui->rbZoomVH->setDisabled(true);
            ui->lcdcounter->display(57002);
            time_minutes = 0;
            data_index=0;
            index_pointer=0;
            index_pointer_max=0;
            dZ_peak_i[0]=0;
            adquiriendo=true;
            plot_timer->start(TIME_PLOT);
            ui->btnConnect->setText("Detener Adquisición");
          }
        }
    }
 else{
  if(ui->btnConnect->text() == "Detener Adquisición"){
        ui->btnConnect->setText("...............");
        ui->lcdcounter->display(000);
        adquiriendo=false;
        usb_thread_worker->abort();//Ordena al usb que deje de operar
        plot_timer->stop();
        QThread::msleep(100);//allow 100 mseconds to finalize thread
        while (procesando==true)
        {QThread::msleep(1);};
        plot();
        delete_thread_usb(this);
        ui->lcdcounter->display(int(data_time[data_index]/1000));
        ui->btnConnect->setText("Iniciar Adquisición");
        }
      }
}
//##############################################################################
void MainWindow::leer_botones(){
        //Para simular USB
    if(ui->checkBox_usb_data_test->isChecked()){
        BOOL_USB_DATA_TEST=true;}else{BOOL_USB_DATA_TEST=false;}
    if(ui->checkBox_data_test->isChecked()){
        BOOL_DATA_TEST=true;}else{BOOL_DATA_TEST=false;}
    if(ui->checkBox_usb_test->isChecked()){
        BOOL_USB_SIM_TEST=true;}else{BOOL_USB_SIM_TEST=false;}
    //Para plot
    if(ui->checkBox_PLOT_SIGNAL_DZ->isChecked()){
        BOOL_PLOT_SIGNAL_DZ=true;}else{BOOL_PLOT_SIGNAL_DZ=false;}
    if(ui->checkBox_PLOT_SIGNAL_dZ->isChecked()){
        BOOL_PLOT_SIGNAL_dZ=true;}else{BOOL_PLOT_SIGNAL_dZ=false;}
    if (ui->checkBox_INVERT_SIGNAL_dZ->isChecked()){
            PLOT_INVERT_SIGNAL_dZ=true;}else{PLOT_INVERT_SIGNAL_dZ=false;}
    if(ui->checkBox_PLOT_SIGNAL_DZ_PA->isChecked()){
        BOOL_PLOT_SIGNAL_DZ_PA=true;}else{BOOL_PLOT_SIGNAL_DZ_PA=false;}
    if(ui->checkBox_PLOT_SIGNAL_DZ_PB->isChecked()){
        BOOL_PLOT_SIGNAL_DZ_PB=true;}else{BOOL_PLOT_SIGNAL_DZ_PB=false;}
    if(ui->checkBox_PLOT_SIGNAL_dZ_PEAK->isChecked()){
        PLOT_SIGNAL_dZ_PEAK=true;}else{PLOT_SIGNAL_dZ_PEAK=false;}
    if(ui->checkBox_PLOT_SIGNAL_Z->isChecked()){
        BOOL_PLOT_SIGNAL_Z=true;}else{BOOL_PLOT_SIGNAL_Z=false;}
        //LENGTH_PLOT=ui->ventanagraficado->value(); //1000
        //LENGTH_CONVOLUTION=ui->ventanaconvolucion->value();//200 defecto
        //FREQ_SAMPLE=1000;//Frecuencia cada el cual tomo data_DZ
        //TIME_PLOT=(LENGTH_CONVOLUTION*1000)/FREQ_SAMPLE; //Tiempo en milisegundos cada el cual grafica y resuelve convolucion
         DISTANCIA_ELECTRODOS=ui->distancia->value();
         GAIN_Z=ui->GZ->value(); //Ganancia comun a las impedancias
         GAIN_Z0=ui->GZ0->value(); //Ganancia unica de Z0
         GAIN_DZ=ui->GDZ->value();//Ganancia unica de Delta Z
         GAIN_Z0_TOTAL=1000;//(GAIN_Z*GAIN_Z0);
         #ifdef Debug_custom
         Debug_custom() << "ganancia de Z"<<QString::number(GAIN_Z0_TOTAL);
         #endif
         Z0_OFFSET=ui->Z0_offset->value();
         Z0_OFFSET_TOTAl=Z0_OFFSET*GAIN_Z0_TOTAL;
         GAIN_DERIVADA=ui->Gderivada->value();
         GAIN_DZ_TOTAL=1000;//(GAIN_Z*GAIN_DZ);//La idea es compensar el valor de ganancia de la derivadda
         //GAIN_DZ_TOTAL=1;
         TRESHOLD=ui->treshold->value();
         TRESHOLD_ESCALA=ui->treshold_escala->value();
         VENTANA_PEAK_FIRST=ui->ventana_peak_first->value();
         VENTANA_PEAK=ui->ventana_peak->value();

         processing_INIT=ui->procesamiento_inicial->value();
         processing_END=ui->procesamiento_inicial->value();

         //Valor de reset de barra:
         DZ_RESET=0.8*Vref/GAIN_DZ_TOTAL;
         //Ranmgo de Graficado
         y_axis_DZ_max=1.03*Vref/GAIN_DZ_TOTAL;
         y_axis_DZ_min=-0.23;
         y_axis_dZ_max=3;
         y_axis_dZ_min=-1;
}
//##############################################################################

//##############################################################################
void MainWindow::on_rbZoomClicked()
{
    if(ui->rbZoomH->isChecked()){
        ui->plot->axisRect()->setRangeZoom(Qt::Horizontal);
        ui->plot_dZ->axisRect()->setRangeZoom(Qt::Horizontal);
    }
    else if(ui->rbZoomV->isChecked()){
        ui->plot->axisRect()->setRangeZoom(Qt::Vertical);
        ui->plot_dZ->axisRect()->setRangeZoom(Qt::Vertical);
    }
    else{
        ui->plot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
        ui->plot_dZ->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    }
}
void MainWindow::on_wheel_axis()
{
//La idea de esta función es hacer que el escalado del eje x sea simetrico para ambos ejes
//Debug_custom() <<  "rueada";
//ui->plot_dZ->xAxis->setRange(ui->plot->wheelEvent(this););
//ui->plot_dZ->wheelEvent(*QWheelEvent);
  // ui->plot->yAxis->setRange(y_axis_DZ_min, y_axis_DZ_max);
}
//------------------------------------------------------------------------------
void MainWindow::on_btnSave()
{
   if (index_pointer>0){
       //Hay datos para guardar
         QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",
                                                     tr("Files (*.cvs)"));
         QFile file(fileName);
         if(file.open(QFile::WriteOnly | QFile::Truncate))
            {
               QApplication::setOverrideCursor(Qt::WaitCursor);
               QTextStream out(&file);
               out <<"Tiempo[ms]" <<" "<<"ΔZ[Ω]" <<" "<<"Z0[Ω]"<< " "<< endl ;

              for ( int i = 0; i < index_pointer; i++)
            {
              out << QString::number((data_time[i]))<<" "<<QString::number(data_DZ[i])<<" "<< QString::number(data_Z[i])<<" "<< endl ;//Guarda tiempo datos alterna datos cc
            }
              file.close();
              QApplication::restoreOverrideCursor();
      }
      }
   else
       //No hay suficientes datos para guardar datos para guardar
     {
     QMessageBox::critical(this,tr("ERROR"),tr("No hay datos suficientes para guardar"),tr("Aceptar"));
     }
}
void MainWindow::on_btnOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",
                                                    tr("Files (*.cvs)"));
    QFile file(fileName);
    data_time.fill(0);
    data_DZ.fill(0);
    //Leo los datos
    //void MainWindow::read_real_table(const char* filename,QVector<double> &aux, int &length ){
    //Lee una tabla con valores reales, almacenandolos en un vector double en el mismo formato
    //std::ifstream
    if(file.open(QFile::ReadOnly))
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        QTextStream in(&file);

                double buffer;
                int i=0;
                in.readLine();
                //Debug_custom()<< QString::number(buffer);//QString::number
                in >> buffer;
                //Debug_custom()<< QString::number(buffer);
                in >> buffer;
                //Debug_custom()<< QString::number(buffer);
                while(!file.atEnd()){
                    in.readLine();
                        in >> buffer;
                        data_time[i]=buffer;
                        in >> buffer;
                        data_DZ[i]=buffer;
                        in >> buffer;
                        data_Z[i]=buffer;
                    i=i+1;
                    }
                    i=i-1;
         file.close();
         QApplication::restoreOverrideCursor();
         leer_botones();
       //Realizo processing y graficado
         data_DZ_pasaaltos.fill(0);
         data_dZ.fill(0);
         data_dZ_segunda.fill(0);
         dZ_peak_i.fill(0);
         dZ_peak_t.fill(0);
         dZ_peak.fill(0);
         T_cardio.fill(0);
        if (i>INDEX_MIN_processing){
        int index_init=0;

        QDialog *findDialog = new QDialog(this);//Permite abrir un dialogo q no se cierra mientras corre el programa
        findDialog->setFixedSize(ui->plot->width(),ui->plot->height());
        findDialog->setWindowFlags(Qt::Dialog | Qt::Desktop);//Evita que pueda ser cerrado
        //Añadir texto
        QLabel *label = new QLabel;
        label->setText ("Test");
        label->show ();
        QHBoxLayout *HLayout = new QHBoxLayout(findDialog);
        HLayout->addWidget (label);
        findDialog->setLayout (HLayout);

        findDialog->show ();
        processing(index_init,i);

        findDialog->setAttribute(Qt::WA_DeleteOnClose);//no quitar
        findDialog->close();//Cierra la ventana

        index_pointer=i;
          //  processing(index_init,index_end);
        }
      plot();
    }
    }

void MainWindow::on_btnProcesar()
{
int i=0;
bool i_flag;
int index_init=0;
int index_end=0;
leer_botones();
//Busco inicio
    i=0;
    while ((i<index_pointer_max))
    {
            i=i+1;
            if (i_flag==false)
             {if(data_time[i]<processing_INIT)
                {i_flag=true;}
             }
            else
            {
             if(data_time[i]>=processing_INIT)
              {
              index_init=i;
              i=index_pointer_max;//Para salir del loop
              #ifdef Debug_custom
              Debug_custom() <<  "i min encontrado"<<"";
              #endif
              }
            }
      }

//Busco ddindice de
    i=0;
    while (i<index_pointer_max)
    {
            i=i+1;
            if(data_time[i]>=processing_END)
            {
             index_end=i;
             i=index_pointer_max;//Para salir del loop
             #ifdef Debug_custom
              Debug_custom() <<  "i max encontrado";
              #endif
            }
      }

//Verifico que los indices encontrados tengan sentido
if (((index_init>0)&(index_end>0))&(index_end>index_init))
{

    data_dZ.fill(0);
    data_dZ_segunda.fill(0);
    dZ_peak_i.fill(0);
    dZ_peak_t.fill(0);
    dZ_peak.fill(0);
    T_cardio.fill(0);
    int index_min_processing_anterior=INDEX_MIN_processing;
    INDEX_MIN_processing=index_init+index_min_processing_anterior;
    filtrado_signal=false;
    detectando_picos=true;
    //QMessageBox::information(this,tr("Espere"),tr("Los datos estan siendo procesados"),tr("Aceptar"));
    processing(index_init,index_end-index_init);
    filtrado_signal=true;
    detectando_picos=false;
    INDEX_MIN_processing=index_min_processing_anterior;//Vuelvo al valor original, que corresponde a la suma de las respuestas al impulso de los filtros.
    data_index=index_end;
    plot();
}
else//Los indices no tienen sentido:
{   //Pido al usuario que ingrese valores reales
     #ifdef Debug_custom
Debug_custom() <<  "indices fuera de rango al intentar procesar: ingrese una ventana correcta";
      #endif
    QMessageBox::critical(this,tr("ERROR"),tr("The processing window is not valid"),tr("Aceptar"));
}
}
//##############################################################################

//##############################################################################

//##############################################################################

void MainWindow::on_scrollArea_destroyed()
{

}
//##############################################################################
//##############################################################################
//##############################################################################
                                //Sistema de hilos
//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################
void MainWindow::data_pointer_call(const double *pointer_time,const double *pointer_data,const double *pointer_cc_data, int index){
        data_pointer=   const_cast< double * >(pointer_data);//Convierte la constante en variable
        data_cc_pointer=const_cast< double * >(pointer_cc_data);
        time_pointer=   const_cast< double * >(pointer_time);//Convierte la constante en variable
        index_pointer_max=(index);//Convierte la constante en variable
      //Debug_custom() << QString::number(const double *pointer_data)<< "corresponde al valor" << QString::number(*time_pointer)<< "corresponde al tiempo"<< QString::number(index)<< "indice";
}

void MainWindow::processing_adquisicion(){
if (adquiriendo==true){
   // Debug_custom()<<  QString::number(index_pointer)<<"<--indice min;indice max-->"<<QString::number(index_pointer_max)<<QString::number(data_index);
if (index_pointer<index_pointer_max){
            procesando=true;
    //Añade datos a los vectores
    for (i = index_pointer ;i<index_pointer_max;i++){
        data_DZ[i]=(*(data_pointer+i))/GAIN_DZ_TOTAL;
        data_Z[i]=(*(data_cc_pointer+i))/GAIN_Z0_TOTAL;//Divido por GDZ total para que quede a igual escala
        data_time[i]=*(time_pointer+i);
        if ((BOOL_DATA_TEST or BOOL_USB_SIM_TEST)==true){
            if(i<data_DZ_ejemplo.size()){
            data_DZ[i]=(data_DZ_ejemplo[i]);
            data_Z[i]=1;
            data_time[i]=data_time_ejemplo[i]/250;
            }
            else
            {   data_DZ[i]=data_DZ[data_DZ_ejemplo.size()-1];
                data_Z[i]=data_time[data_DZ_ejemplo.size()-1];
                data_time[i]=data_time[data_DZ_ejemplo.size()-1];}
            }

        }
 index_pointer=index_pointer_max;//Cantidad dedatos muestra disponible
    }

    if((data_index+LENGTH_CONVOLUTION)<=(index_pointer)){
         // Debug_custom()<< "Graficando:";
        processing(data_index,LENGTH_CONVOLUTION);
        if ((data_index>LENGTH_PLOT)&(adquiriendo==true)){//Solo grafico cuando estoy adquiriendo
        if (BOOL_PLOT_SIGNAL_DZ==true){
        ui->plot->graph(0)->setData(data_time.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT),data_DZ.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT));
        ui->plot->graph(0)->addToLegend();}
        if (BOOL_PLOT_SIGNAL_DZ_PB==true){
        ui->plot->graph(1)->setData(data_time.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT),data_DZ_pasabajos.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT));
        ui->plot->graph(1)->addToLegend();}
        if (BOOL_PLOT_SIGNAL_Z==true){
        ui->plot->graph(3)->setData(data_time.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT),data_Z.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT));
        ui->plot->graph(3)->addToLegend();}
        if (BOOL_PLOT_SIGNAL_DZ_PA==true){
        ui->plot->graph(2)->setData(data_time.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT),data_DZ_pasaaltos.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT));}
        if (BOOL_PLOT_SIGNAL_dZ==true){
        ui->plot_dZ->graph(0)->setData(data_time.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT),data_dZ.mid(data_index-LENGTH_PLOT-1,LENGTH_PLOT));}
        // set axes ranges, so we see all data:
        //ui->plot->yAxis->setRange(-0.25, y_graph);
        ui->plot->xAxis->setRange(data_time[data_index-LENGTH_PLOT], data_time[data_index-1]);
        ui->plot_dZ->xAxis->setRange(data_time[data_index-LENGTH_PLOT], data_time[data_index-1]);
        ui->plot->replot();
        ui->plot_dZ->replot();
        ui->lcdcounter->display(int(data_time[data_index] /1000));
        }
  //Pocrsamiento
  //Debug_custom()<< QString::number(index_pointer)<< "Graficado:";
}
}
procesando=false;//Indico que termine de procesar los datos
}

void MainWindow::processing(int &data_index_p,int data_index_p_length){
    int data_index_p_max=data_index_p+data_index_p_length;
    convolution(data_DZ,filtro,data_DZ_pasabajos_ruido,data_index_p,data_index_p_length);
    //Convolucion:Aplico filtro pasabajos_antiruido
    convolution(data_DZ_pasabajos_ruido,filtro_pasabajos_ruido,data_DZ_pasabajos,data_index_p,data_index_p_length);
    //convolution(data_DZ,filtro_pasabajos_ruido,data_DZ_pasabajos,data_index_p,data_index_p_length);
    //Convolucion:Aplico el filtro pasa altos
    convolution(data_DZ_pasabajos,filtro_pasaaltos,data_DZ_pasaaltos,data_index_p,data_index_p_length);

    //Derivación
    for (j = data_index_p; j<(data_index_p_max); j=j+1) {
        if (j>0){
        data_dZ[j] = (GAIN_DERIVADA)*(data_DZ_pasaaltos[j]- data_DZ_pasaaltos[j-1]);
        }
        else
         data_dZ[j]=0;
    }
    for (j = data_index_p; j<(data_index_p_max); j=j+1) {
         if (j>1){//Porque el indice 0 vale 0
          data_dZ_segunda[j] =(data_dZ[j]- data_dZ[j-1]);
             }
                else
            data_dZ_segunda[j]=0;
            }
   // find_peak(data_dZ,dZ_peak_t,dZ_peak,data_index,800,data_index+LENGTH_CONVOLUTION);
             // Debug_custom()<<  QString::number(dZ_peak_t[0]);
    //Actualizo los indices
    //Valor de Z0
    Z0[0]=medium(data_Z,data_index_p,data_index_p_max,Z0);
    Z0[0]=Z0[0]-Z0_OFFSET;
    qts_Z0<<(QString::number(Z0[0],'f',2));//Como escribir el numero
    ui->result_Z0->setText(qts_Z0.readAll());

    DZ0[0]=medium(data_DZ_pasabajos,data_index_p,data_index_p_max,DZ0);
    //qts_Z0>>qts_Z0_buffer;//limpio
    //Debug_custom() <<" Media : "<<QString::number((Z0[0]));
    data_index_p=data_index_p_max;
    if (detectando_picos==true)
   {
    dZ_peak_i_anterior=dZ_peak_i[0];
    if (data_index_p>INDEX_MIN_processing)
    //Significa que el indice de processing está por encima del valor transitorio de ventana
   {Debug_custom() <<" buscando picos";
        if ((dZ_peak_i[0])==0){find_peak_first(data_time,data_dZ,dZ_peak_i,dZ_peak_t,dZ_peak,INDEX_MIN_processing,data_index_p,VENTANA_PEAK_FIRST,TRESHOLD);}
    if ((dZ_peak_i[0])>0){find_peak(data_time,data_dZ,dZ_peak_i,dZ_peak_t,dZ_peak,data_index_p,VENTANA_PEAK,TRESHOLD_ESCALA*dZ_peak[1]);}
    //Si se enconto un pico, procedo a calcular un cero y gasto cardiaco
    if ((dZ_peak_i[0])>dZ_peak_i_anterior)
        {    find_peak_min_and_cero(data_time,data_dZ,data_dZ_segunda,dZ_peak_i,T_EV,dZ_peak_i_anterior,VENTANA_PEAK);
    //Gasto Cardiaco
            if (dZ_peak_i[0]>1)
            {
              gasto_cardiaco(dZ_peak_t,dZ_peak,T_EV,T_cardio,GC_kubicek,GC_samek,dZ_peak_i_anterior,dZ_peak_i[0],Z0,DISTANCIA_ELECTRODOS);
              //Mostrar GC en el display:
                //qts_gasto_cardiaco>>qts_gasto_cardiaco_buffer;//NO ES NECESARIO LIMPIAR EL BUFFER ASÍ
                qts_gasto_cardiaco<<(QString::number(GC_samek[GC_samek[0]],'f',2));//Como escribir el numero
                ui->result_GC->setText(qts_gasto_cardiaco.readAll());
                qts_freq_cardiaca<<(QString::number(60/(T_cardio[0]),'f',2));
                ui->result_FreqCardio->setText(qts_freq_cardiaca.readAll());
            }

       }

      }
   }
}
//--------Diezmado
    //NO USADO
/* data_index_diezmado=data_index/DIEZMADO;//Antes de aumentarlo
length_conv=data_index+LENGTH_CONVOLUTION;
j=data_index_diezmado;
//Diezmo los nuevos datos
for (i = data_index; i<(length_conv); i=i+DIEZMADO) {
    x_diezmado[j]=data_time[i];
    data_DZ_diezmado[j] = data_DZ_pasabajos[i];
    j=j+1;
//Aumento el indice al haber terminado la operacion
*/

void MainWindow::plot()

{   ui->rbZoomH->setEnabled(true);
    ui->rbZoomV->setEnabled(true);
    ui->rbZoomVH->setEnabled(true);
    //Grafico Todo:
    ui->plot->clearItems();
    if (BOOL_PLOT_SIGNAL_DZ==true){
        ui->plot->graph(0)->setData(data_time,data_DZ);
        ui->plot->graph(0)->addToLegend();}else{ui->plot->graph(0)->removeFromLegend();}
    if (BOOL_PLOT_SIGNAL_DZ_PB==true){
    ui->plot->graph(1)->setData(data_time,data_DZ_pasabajos);
        ui->plot->graph(1)->addToLegend();}else{ui->plot->graph(1)->removeFromLegend();}
    if (BOOL_PLOT_SIGNAL_Z==true){
      ui->plot->graph(3)->setData(data_time,data_Z);
      ui->plot->graph(3)->addToLegend();}else{ ui->plot->graph(3)->removeFromLegend();}
    if (BOOL_PLOT_SIGNAL_DZ_PA==true){
     ui->plot->graph(2)->setData(data_time,data_DZ_pasaaltos);}else{ui->plot->graph(2)->removeFromLegend();}
    if (BOOL_PLOT_SIGNAL_dZ==true){
      ui->plot_dZ->graph(0)->setData(data_time,data_dZ);}else{ui->plot_dZ->graph(0)->removeFromLegend();}
    if (PLOT_INVERT_SIGNAL_dZ==true)
    {ui->plot_dZ->yAxis->QCPAxis::setRangeReversed(true);}else{ui->plot_dZ->yAxis->QCPAxis::setRangeReversed(false);}
    if (PLOT_SIGNAL_dZ_PEAK==true){
      ui->plot_dZ->graph(1)->setData(dZ_peak_t,dZ_peak);
      ui->plot_dZ->graph(1)->addToLegend();}else{ui->plot_dZ->graph(1)->removeFromLegend();}
    processing(data_index,LENGTH_CONVOLUTION);
    if ((data_index>LENGTH_PLOT)&(adquiriendo==true)){//Solo grafico cuando estoy adquiriendo
    if (data_index>LENGTH_CONVOLUTION){
        ui->plot->xAxis->setRange(data_time[data_index-LENGTH_CONVOLUTION],data_time[data_index]);
        ui->plot_dZ->xAxis->setRange(data_time[data_index-LENGTH_CONVOLUTION],data_dZ[data_index]);
            }
        ui->plot->yAxis->setRange(y_axis_DZ_min, y_axis_DZ_max);
        ui->plot_dZ->yAxis->setRange(y_axis_dZ_min, y_axis_dZ_max);
    ui->plot->replot();
    ui->plot_dZ->replot();
}
}

void MainWindow::processing_setup(){
    //inicialiso las variables
    data_index=0;

    data_time.resize(DATA_SAMPLE);
    x_diezmado.resize(DATA_DIEZMADA);
    data_time_ejemplo.resize(DATA_SAMPLE);
    aux.resize(DATA_SAMPLE);

    data_DZ.resize(DATA_SAMPLE);
    data_Z.resize(DATA_SAMPLE);
    data_DZ_ejemplo.resize(DATA_SAMPLE);
    data_DZ_pasabajos.resize(DATA_SAMPLE);
    data_DZ_pasabajos_ruido.resize(DATA_SAMPLE);
    data_DZ_diezmado.resize(DATA_DIEZMADA);
    data_DZ_pasaaltos.resize(DATA_DIEZMADA);
    data_dZ.resize(DATA_DIEZMADA);
    data_dZ_segunda.resize(DATA_DIEZMADA);

    dZ_peak_i.resize(DATA_SAMPLE/500);
    dZ_peak_t.resize(DATA_SAMPLE/500);
    dZ_peak.resize(DATA_SAMPLE/500);
    Z0.resize(DATA_SAMPLE/500);
    DZ0.resize(1);
    T_EV.resize(DATA_SAMPLE/500);
    T_cardio.resize(DATA_SAMPLE/500);
    GC_kubicek.resize(DATA_SAMPLE/500);
    GC_samek.resize(DATA_SAMPLE/500);
    dZ_peak_i[0]=0; //Inicialisa el primer valor del valor pico
    dZ_peak_t[0]=0;
    dZ_peak[0]=0;
    T_cardio[0]=0;//Valor Medio
    T_cardio[1]=0;//Valor inicial

    index_pointer=0;
    INDEX_MIN_processing=0;
    //Cargo el vector de data_DZ de prueba
    // double tones_freq[] = {CONST_ARRAY};
    for (i=0; i<(DATA_SAMPLE); i++)
    {
       data_time_ejemplo[i]=i;
    }
   //Cargo las data_DZ y filtro de pruebas desde el archivo.
   //Lectura de .txt exterior:
  // MainWindow::read_real_table("puntos.txt",aux,length);
    //     data_DZ_ejemplo.resize(length);
    //     aux.resize(length);
    //     data_DZ_ejemplo=aux;
  //Filtro Pasabajos:

    filtro={FILTRO_PASABAJOS_ruido};//CARGA FILTRO PASABAJOS
    filtro_pasabajos_ruido={0.5,0.5};
    filtro_pasaaltos={0.5,0.5};//{FILTRO_PASAALTOS};  //CARGA FILTRO PASAALTOS
    INDEX_MIN_processing=filtro.size()+filtro_pasaaltos.size()+filtro_pasabajos_ruido.size();
    Debug_custom()<< QString::number(INDEX_MIN_processing)<< "transitorios filtros";
 // MainWindow::read_real_table("filtro.txt",aux,length);
   //   filtro.resize(length);
     //  aux.resize(length);
      //  filtro=aux;
    //   Debug_custom()<< QString::number(filtro_pasaaltos.size())<< "tamaño filtro";
  //MainWindow::read_real_table("filtro_pasaaltos.txt",aux,length);
    //    filtro_pasaaltos.resize(length);
      //  aux.resize(length);
     //filtro_pasaaltos=aux;

   leer_botones();
   //Carácteristica de la barra

   //QString qprogressbar_color = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1,stop: 0 #FFFF00,stop: 0.4 #ffdf00,stop: 0.6 #FFFF00,stop: 1 #ffdf00);border-top-right-radius: 10px;border-top-left-radius: 10px;border-bottom-right-radius: 10px;border-bottom-left-radius: 10px;border: 1px solid grey;}";
   //QString qprogressbar_color_2="QProgressBar::chunk { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 0,  stop: 0 yellow,  stop: 1 yellow);}";
   //ui->progressBar_reset->setStyleSheet(qprogressbar_color);

   // Caracteristicas de los Graficos
   QPen pen;
   //Grafico de Delta Z sin filtrar
   ui->plot->addGraph();//Señal Sin filtrar
   //ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,8));//Añade circulos alrededor de cada punto
   pen.setWidth(1);
   pen.setColor(QColor(100,200, 100, 100));//Hace a la linea verde suave
   ui->plot->graph(0)->setPen(pen);//Hace a la linea verde suave
   ui->plot->graph(0)->setName("ΔZ sin filtrado");
   ui->plot->graph(0)->removeFromLegend();
   //Grafico de Delta Z
   ui->plot->addGraph();//Señal filtrada pasabajos
   //ui->plot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 10)));//Azul con sombreado suave
   pen.setWidth(2);
   pen.setColor(QColor(0, 0, 255, 255));//Hace a la linea azul
   ui->plot->graph(1)->setPen(pen);//Hace a la linea azul
   ui->plot->graph(1)->setLineStyle(QCPGraph::lsStepRight);//Linea diferente
   ui->plot->graph(1)->setName("ΔZ");
   ui->plot->graph(1)->removeFromLegend();
   //Grafico de Delta Z cardiaca
   ui->plot->addGraph();//Señal filtrada pasaaltos
   pen.setWidth(2);
   pen.setColor(QColor(255,0,0,255));//Hace a la linea roja
   ui->plot->graph(2)->setPen(pen);//Hace a la linea roja
   ui->plot->graph(2)->setName("ΔZ cardíaca");
   //ui->plot->graph(2)->setBrush(QBrush(QColor(0, 255, 0, 30)));//Ver con sombreado fuerte
   //Grafico de Z
   ui->plot->addGraph();//Señal de Continua
   ui->plot->graph(3)->setPen(QPen(QColor(0,0,0,100)));//Hace a la linea negro suave
   ui->plot->graph(3)->setName("Z");
   ui->plot->graph(3)->removeFromLegend();
   //Grafico de dZ
   ui->plot_dZ->addGraph();//Señal Derivada
   pen.setWidth(2);
   pen.setColor(QColor(148,0,211,255));//Hace a la linea violeta intenso
   ui->plot_dZ->graph(0)->setPen(pen);//Hace a la linea violeta intenso
   ui->plot_dZ->graph(0)->setName("dZ/dt");
   ui->plot_dZ->addGraph();//Picos de Señal Derivada
   //Grafico de valores pico
   ui->plot_dZ->graph(1)->setPen(QPen(QColor(0, 0, 255, 255)));//Atenuo la linea del trasado
   //ui->plot_dZ->graph(1)->setLineStyle(QCPGraph::lsStepRight);//Linea diferente
   ui->plot_dZ->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
   ui->plot_dZ->graph(1)->setName("Máximos dZ/dt");
   ui->plot_dZ->graph(1)->removeFromLegend();
   //addToLegend()
      // Nombre de Ejes
   ui->plot->xAxis->setLabel("Tiempo [s]");
   ui->plot->yAxis->setLabel("Variación de Impedancia (ΔZ)[Ω]");
   ui->plot->yAxis->setRange(y_axis_DZ_min, y_axis_DZ_max);
   ui->plot->legend->setVisible(true);
   ui->plot->legend->setFont(QFont("Helvetica", 12));

   ui->plot_dZ->xAxis->setLabel("Tiempo [s]");
   ui->plot_dZ->yAxis->setLabel("Derivación de Variación de Impedancia (dZ) [Ω]/S");
   ui->plot_dZ->yAxis->setRange(y_axis_dZ_min, y_axis_dZ_max);
   //inversion del eje
   if (PLOT_INVERT_SIGNAL_dZ==true)
   {ui->plot_dZ->yAxis->QCPAxis::setRangeReversed(true);}else{ui->plot_dZ->yAxis->QCPAxis::setRangeReversed(false);}

   ui->plot_dZ->legend->setVisible(true);
   ui->plot_dZ->legend->setFont(QFont("Helvetica", 12));

   ui->plot->setInteraction(QCP::iRangeDrag, true);//Permite mover con el mouse en cualquier eje
   //ui->plot->setInteraction(QCPAxisRect::setRangeDrag(Qt::Horizontal));//Permite mover con el mouse solo en el eje horizontal/vertical
   ui->plot->axisRect()->setRangeDrag(Qt::Horizontal);//Permite mover con el mouse solo en el eje horizontal/vertical
   ui->plot->setInteraction(QCP::iRangeZoom, true);
   ui->plot->axisRect()->setRangeZoom(Qt::Vertical);
   ui->plot->setEnabled(true);

   ui->plot_dZ->setInteraction(QCP::iRangeDrag, true);
   ui->plot_dZ->axisRect()->setRangeDrag(Qt::Horizontal);
   ui->plot_dZ->setInteraction(QCP::iRangeZoom, true);
   ui->plot_dZ->axisRect()->setRangeZoom(Qt::Vertical);
   ui->plot_dZ->setEnabled(true);
}



//-------------------------------------------------------
//Funciones Agregadas


void MainWindow::read_real_table(const char* filename,QVector<double> &aux, int &length ){
//Lee una tabla con valores reales, almacenandolos en un vector double en el mismo formato
    aux.resize(10000);//Para no sobrepasar el indice
    std::ifstream file(filename);
     //Convierto a String
    std::stringstream ss;
    ss << file.rdbuf();//Convierto a double[]
    length=0;
    while(ss>>aux[length])
        {length=length+1;}
}
void MainWindow::create_thread_usb(const QObject *receiver)
{
    usb_thread = new QThread();//create a thread
    usb_thread_worker = new Worker();//create a worker: action we want the thread to do
    usb_thread_worker->moveToThread(usb_thread);//assign this acction/(worker) to the thread
    //after this, we need to asgin the events to the
    //this events will allow us to comunicate the thread created
    connect(usb_thread_worker, SIGNAL(valueChanged(const double*,const double*,const double*,int)),receiver, SLOT(data_pointer_call(const double*,const double*,const double*,int)));
    connect(usb_thread_worker, SIGNAL(workRequested()), usb_thread, SLOT(start()));//allo use workRequested in the objet
    connect(usb_thread, SIGNAL(started()), usb_thread_worker, SLOT(doWork()));
    connect(usb_thread_worker, SIGNAL(finished()), usb_thread, SLOT(quit()), Qt::DirectConnection);//to fihish the thread
    usb_thread_worker->requestWork();
}
void MainWindow::delete_thread_usb(const QObject *receiver)
{
    usb_thread_worker->abort();
    usb_thread->wait();
    disconnect(usb_thread_worker, SIGNAL(valueChanged(const double*,const double*,const double*,int)),receiver, SLOT(data_pointer_call(const double*,const double*,const double*,int)));
    disconnect(usb_thread_worker, SIGNAL(workRequested()), usb_thread, SLOT(start()));//Permite usar workRequested en el objeto
    disconnect(usb_thread, SIGNAL(started()), usb_thread_worker, SLOT(doWork()));//Al usar workRequested, realioza trabajo
    #ifdef Debug_custom
         Debug_custom()<<"Deleting thread and thread worker assined in Thread "<<this->QObject::thread()->currentThreadId();
    #endif
    delete usb_thread_worker;
    delete usb_thread;

}


