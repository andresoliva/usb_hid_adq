
#include "thread_worker.h"
//included libraries to handle USB
#include "usb_hid_custom.h"
#include "hidapi.h"
//
Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}
//for thread request work(*DO NOT CHANGE*)
void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    #ifdef Debug_custom
           Debug_custom()<<"Request worker start in Thread "<<thread()->currentThreadId();
    #endif
    mutex.unlock();

    emit workRequested();
}
//for thread abort (*DO NOT CHANGE*)
void Worker::abort()
{
    int i;
    mutex.lock();
        #ifdef Debug_custom
    Debug_custom()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    #endif
    for ( i=0; i<100; i++ ){//to ensure the thread stops
        QThread::usleep(10);
       if (_working) {
        _abort = true;
        if (_abort == true)
        {i=100;}//to go out of function call
                    }
    }
    mutex.unlock();
}
//This is the the function that set up
void Worker::usb_recep_setup(){

}

void Worker::usb_simulate_data_rep(){
                   time_usb[index]=((double)index)/1000;
                   data_usb_ch1[index]=(double)(index);
                   data_usb_ch2[index]=(double)(index);
                   index=index+4;//Incremento el indice
                   counter =counter+4;//Incremento el contador
}
void Worker::data_reception_test(){
    //---------------------------->DATA RECEPTION LOOP--------------------------
                          for( index_usb = index_zero; index_usb <(index_max); index_usb = index_usb + DATA_BUFFER )
                             {//Get the data to from the usb_buffer_recep and asign them
                                time_rx   = (usb_buffer_recep[index_usb]     + 256*usb_buffer_recep[index_usb + 1]) ;
                                data_ch1   = (usb_buffer_recep[index_usb + 2] + 256*usb_buffer_recep[index_usb + 3]) ;
                                data_ch2   = (usb_buffer_recep[index_usb + 4] + 256*usb_buffer_recep[index_usb + 5]) ;
                              //convert to double format
                                time_rx_double = (double) time_rx;
                                data_ch1_double = (double) data_ch1;
                                data_ch2_double = (double) data_ch2;
                              //convert bits to Volts
                                data_usb_ch1[index]=((Vref*data_ch1_double)/(4095));//1023 for 10 bits
                                data_usb_ch2[index]=((Vref*data_ch2_double)/(4095));//1023 for 10 bits
                              //QDEBUG_CUSTOM()<<"index:"<<index<<"tiempo:"<<QString::number(time_rx)<<"data"<<QString::number(data_ch1);
                              //check time close to overflow value
                                  if ((flag_time_minutes==1)and(time_rx>55000)){flag_time_minutes=0;}
                              //check if an overflow happened and increase time
                                  if ((flag_time_minutes==0)and(time_rx<5000)){flag_time_minutes=1;
                                       MainWindow::time_minutes = MainWindow::time_minutes+1;}//increase the time counter
                              //save the current time taking it into account
                                time_usb[index] = ((time_rx_double)/1000) + (double)(60*(MainWindow::time_minutes));
                                MainWindow::time_value= time_usb[index];//último valor medido.
   //-------------------->HERE STARTS DATA INTEGRITY CHECK AND INTERPOLATION of DATA--------------------------
                                if ((index)>2){
                                    usb_data_correction();
                                 }
            //-------------------->Update times and counters
                                MainWindow::time_before=MainWindow::time_value;
                                index=index+1;//Aumento el contador de data_DZ en 1
                                counter=counter+1;
                                }
            //-------------------->end of loop
}
void Worker::data_reception_1_ch(){
   time_usb[index]=((double)index)/1000;
                   data_usb_ch1[index]=(double)(index);
                   data_usb_ch2[index]=(double)(index);
                   index=index+4;//Incremento el indice
                   counter =counter+4;//Incremento el contador
}
void Worker::data_reception_2_ch(){
    //---------------------------->DATA RECEPTION LOOP--------------------------
                            int index_time_begin,index_time_interp;
                            time_rx =(usb_buffer_recep[1]+256*usb_buffer_recep[2]+65536*usb_buffer_recep[3]) ;
qDebug()<<"8bit"<<usb_buffer_recep[1]<<"16bit"<<usb_buffer_recep[2]<<"data"<<usb_buffer_recep[3];
                            time_rx_double = (double) time_rx;
                            time_usb[index] = ((time_rx_double)/1000) + (double)(60*(MainWindow::time_minutes));
                            index_max=64;
                            time_resolution=0.001;//resolution in miliseconds
                            MainWindow::time_value= time_usb[index];//último valor medido.
                            //check time close to overflow value
                                if ((flag_time_minutes==1)and(time_rx>14000000)){flag_time_minutes=0;}
                            //check if an overflow happened and increase time
                                if ((flag_time_minutes==0)and(time_rx<400000)){flag_time_minutes=1;
                                     MainWindow::time_minutes = MainWindow::time_minutes+2400;}//increase the minute counter
                            index_time_begin=index;
                            index_time_interp=0;
                          for( index_usb = index_zero; index_usb <index_max; index_usb = index_usb + DATA_BUFFER_2_CH )
                             {//Get the data to from the usb_buffer_recep and asign them
                                data_ch1   = (usb_buffer_recep[index_usb ] + 256*usb_buffer_recep[index_usb + 1]) ;
                                data_ch2   = (usb_buffer_recep[index_usb + 2] + 256*usb_buffer_recep[index_usb + 3]) ;
                              //convert to double format
                                data_ch1_double = (double) data_ch1;
                                data_ch2_double = (double) data_ch2;
                              //convert bits to Volts
                                data_usb_ch1[index]=((Vref*data_ch1_double)/(4095));//1023 for 10 bits
                                data_usb_ch2[index]=((Vref*data_ch2_double)/(4095));//1023 for 10 bits
                                //set up time:
                                time_usb[index]=time_usb[index_time_begin]+ index_time_interp*time_resolution;
                                //qDebug()<<"index:"<<index<<"tiempo:"<<QString::number(time_usb[index])<<"data"<<QString::number(data_ch1);
                              //save the current time taking it into account
   //-------------------->HERE STARTS DATA INTEGRITY CHECK AND INTERPOLATION of DATA--------------------------
            //-------------------->Update times and counters
                                MainWindow::time_before=MainWindow::time_value;
                                ++index;//Aumento el contador de data_DZ en 1
                                ++counter;
                                ++index_time_interp;
                                }
            //-------------------->end of loop
}
void Worker::usb_data_correction(){
    if(time_usb[index]>MainWindow::time_before)//Verifica que el timer es nuevo
      {
       MainWindow::time_delta=(time_usb[index]-MainWindow::time_before);
       if (MainWindow::time_delta>0.0018)//0.0018 para que no afecte el redondeo
           {
            // QDEBUG_CUSTOM()<<"indicee:"<<index<<"tiempo Actual::"<<QString::number(MainWindow::time_value)<<"tiempo anterior"<<QString::number(MainWindow::time_before));
             if (MainWindow::time_delta>100.000)//original <0.009
                 {//MainWindow::time_value=(MainWindow::time_before)+0.001;
                   //time_usb[index]= MainWindow::time_value;
                   Debug_custom()<< "--->valor interpolado"<<QString::number(MainWindow::time_value) ;
                   counter=counter+10;//Porque interpolo 10 valores
                 }if (MainWindow::time_value-MainWindow::time_before>0.0018)
                 {// QDEBUG_CUSTOM()<< "de valor de tiempo"<<QString::number(MainWindow::time_value));
                 }
             }
        }
    else  //El timer no es nuevo
        {
           index=index-1;//Decrementa el contador para aplastarlo cuando aparesca el nuevo dato
           counter=counter-1;
           MainWindow::time_value=(MainWindow::time_before)+0.001;
           time_usb[index]= MainWindow::time_value;
          // QDEBUG_CUSTOM()<<"Tiempo recibido" <<QString::number(MainWindow::time_value)<<"Anterior tiempo:" <<QString::number(MainWindow::time_before));
        }
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------------------------------
void Worker::doWork()
{
    //initializae variables
    int usb_write_read_result;
    struct hid_device_info *usb_devices;
    hid_device *usb_connected_device;
    double *pointer_time=&time_usb[0];
    double *pointer_data=&data_usb_ch1[0];
    double *pointer_cc_data=&data_usb_ch2[0];
    bool abort = _abort;//Bandera para indicar si el hilo debe trabajar o no.
    mutex.lock();
    mutex.unlock();
    MainWindow::time_before=0;//Indico que comienza en 0.
    emit valueChanged(pointer_time,pointer_data,pointer_cc_data,index);//Paso los datos al programa principal para aplastar los anteriores
    //WHILE LOOP//
    qDebug()<< "--->start recep";
    unsigned char outBuffer[65];//outBuffer[0] is for endpoint number and must always be zero to ensure proper writing
    outBuffer[0] = 0;//MUST ALWAYS BE ZERO
    outBuffer[1] = CID_ADQ;
    MainWindow::time_value=0;
    usb_devices=usb_check_device_aviable();
    usb_connected_device=usb_device_connect(usb_devices);
    usb_write_read_result=hid_set_nonblocking(usb_connected_device,1);
    usb_write_read_result=hid_write(usb_connected_device, outBuffer, USB_BUFFER_WRITE);
    qDebug()<< "--->start recep";
    while(abort==false){//Abort==false-->then means thread is doing work
            QThread::usleep(700);//timer wait to read data
            //to simulate data recepcion
            if ((MainWindow::BOOL_USB_DATA_TEST or MainWindow::BOOL_USB_SIM_TEST )==true){
                usb_simulate_data_rep();
           }else//else proceed to recieve
               {//DO USB READ
                 usb_write_read_result = hid_read(usb_connected_device, usb_buffer_recep ,64);//read THE USB BUFFER
                  if (usb_write_read_result == USB_BUFFER){//to check if a USB packet has arrived
                        //QDEBUG_CUSTOM()<< "--->usb_buffer_recep[0]: "<<QString::number(usb_buffer_recep[0]));//for debug purpose
                        if(usb_buffer_recep[0]==CID_ADQ)	//--------Check if I recieved ADQ data
                            {
//---------------------------->HERE STARTS DATA RECEPTION--------------------------
                                usb_buffer_recep[0]=0;//Cleans the reception bit
                                Debug_custom()<< "--->recieving "<<QString::number(index_max);
                                data_reception_2_ch();
                                }
//---------------------------->END OF DATA RECEPTION LOOP--------------------------
                }
                else{//Debug_custom()<< "USB: there is no read";
                    }
            }
//------------------------------->END OF USB READ LOOP
//------------>CHECK TO SEND THE DATA POINTERS TO MAIN PROGRAM
        if (counter>100){//SEND DATA POINTERS TO MAIN PROGRAM
            emit valueChanged(pointer_time,pointer_data,pointer_cc_data,index);
            counter=0;}//RESET THE DATA SEND POINTER'S COUNTER
        mutex.lock();//allow the variable to be read
        abort = _abort;//read the variable share with the main program
                       //---->if _abort=true--->then the
        mutex.unlock();
    }
//END OF WHILE LOOOP
//Disconnect the device
outBuffer[0] = 0; // 1 ELEMENT OF ARRAY MUST ALWAYS BE ZERO
outBuffer[1] = CID_STOP; // Recieved as usb_buffer_recep[0] to the microcontroller perspective
usb_write_read_result = hid_write(usb_connected_device, outBuffer, USB_BUFFER_WRITE);//DO NOT CHANGE
QThread::msleep(10);//Espero que termine.
hid_close(usb_connected_device);
//
//------------------------------>_abort=true--->we need to stop the trigger
   QThread::msleep(1);//Espero para evitar crash al emitir valores consecutivamente
   index=0;//clear the index with the amount of data collected
   Debug_custom()<< "THREAD FINISHED";
   emit finished();//indicates to the main program that the thread has finished
                   //---->then main program will delete the thread
}



hid_device *usb_device_connect(hid_device_info *hid_dev_info)
{
hid_device *connected_device;
connected_device = hid_open_path(hid_dev_info->path);
hid_set_nonblocking(connected_device,1);
return(connected_device);
}
hid_device_info *usb_check_device_aviable(void)
{
    struct hid_device_info *devices;
    int iDevice;
    int countDevices=100;
    struct hid_device_info *cur_dev,*cur_dev_return;
    hid_free_enumeration(devices);
    cur_dev=devices;
    cur_dev = hid_enumerate(0x0, 0x0);
    if (cur_dev)
    {
        #ifdef Debug_custom
        Debug_custom() <<  "Dispositivos Detectados";
        #endif
        for (iDevice = 1 ; iDevice <=(countDevices); iDevice++)
        { Debug_custom() <<  "Dispositivo: "<<"vendor id: "<<(cur_dev->vendor_id)<<"product id:"<<(cur_dev->product_id);
            if(
               ((cur_dev->vendor_id)== 1240)
                       &
               ((cur_dev->product_id)== 63)
                )
                {//device can connect
                cur_dev_return=cur_dev;
                iDevice=1+countDevices;
                }
                else
                {
                cur_dev = cur_dev->next;//No quitar, sino no funciona
                if (cur_dev == NULL)iDevice=1+countDevices;
                }
        }
    }
if(cur_dev == NULL){return (NULL);}
 else{return(cur_dev_return);}
}
void Worker::thread_create_usb2(QThread *thread, Worker *thread_worker,const QObject *receiver)
{
    thread = new QThread();//create a thread
    thread_worker = new Worker();//create a worker: action we want the thread to do
    thread_worker->moveToThread(thread);//assign this acction/(worker) to the thread
    //after this, we need to asgin the events to the
    //this events will allow us to comunicate the thread created
    connect(thread_worker, SIGNAL(valueChanged(const double*,const double*,const double*,int)),receiver, SLOT(Mainwindow::data_pointer_call(const double*,const double*,const double*,int)));
    connect(thread_worker, SIGNAL(workRequested()), thread, SLOT(start()));//allo use workRequested in the objet
    connect(thread, SIGNAL(started()), thread_worker, SLOT(doWork()));
    connect(thread_worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);//to fihish the thread
    thread_worker->requestWork();
}
void Worker::thread_delete_usb2(QThread *thread, Worker *thread_worker,const QObject *receiver)
{
    thread_worker->abort();//order thread worker to abort
    thread->wait();//order thread to wait
    disconnect(thread_worker, SIGNAL(valueChanged(const double*,const double*,const double*,int)),receiver, SLOT(Mainwindow::data_pointer_call(const double*,const double*,const double*,int)));
    disconnect(thread_worker, SIGNAL(workRequested()), thread, SLOT(start()));//Permite usar workRequested en el objeto
    disconnect(thread, SIGNAL(started()), thread_worker, SLOT(doWork()));//Al usar workRequested, realioza trabajo
    #ifdef Debug_custom
         Debug_custom()<<"Deleting thread and thread worker assined in Thread "<<this->QObject::thread()->currentThreadId();
    #endif
    delete thread_worker; //deletes worker
    delete thread;//deletes trigger
}
void Worker::thread_communication(const double *pointer_time,const double *pointer_data,const double *pointer_cc_data, int index){
        //double data_pointer=   const_cast< double * >(pointer_data);//Convierte la constante en variable
        //double data_cc_pointer=const_cast< double * >(pointer_cc_data);
        //double time_pointer=   const_cast< double * >(pointer_time);//Convierte la constante en variable
       // double index_pointer_max=(index);//Convierte la constante en variable
      //Debug_custom() << QString::number(const double *pointer_data)<< "corresponde al valor" << QString::number(*time_pointer)<< "corresponde al tiempo"<< QString::number(index)<< "indice";
}
