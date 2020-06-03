/*
   Copyright 2013 Fabien Pierre-Nicolas.
      - Primarily authored by Fabien Pierre-Nicolas

   This file is part of simple-qt-thread-example, a simple example to demonstrate how to use threads.
   This example is explained on http://fabienpn.wordpress.com/qt-thread-simple-and-stable-with-sources/

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This progra is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*----------------------------------------------------------------------------------------------------->
* How this library works?
* 0 SET UP:
* You should create a thhread
* 1 start:
* use the "check device function" to verify the desired usb device is on
* then start the thread, by doing so it will call the "do work"
*   about dowork:
*       -create variables to ensure data storage and proper operation
*       -will connect to the desired usb device
*       -will send a message to tell them to start sending him data
*       -will then start a reading-loop
*           -will update the counter of the reading
*       -after 100 data reading, will tell the main program the current amount of data
*           -then will reset the counter
*       -will check "abort"variable of the thread to know if it should be in the reading loop
*       -in case of not (in other words, when the main programs changes "abort" value )
*           will get out of the reading loop
*           it will send the device a message to stop sending the host/PC data
*           iw will emit a signal to the main program with the last index
*           -it will disconnect the device
*           -in the Last line it will emit a signal to the main program telling him
* After this the main program should destroy the thread, and create a new one.
*
 */


#ifndef THREAD_WORKER_H
#define THREAD_WORKER_H
//#include "usb_hid_custom.h"
#include <QObject>
#include <QMutex>
#include <QEventLoop>
#include "QVector"
#include <QThread>
#include <QDebug>
#include <hidapi.h>

static QVector<double> time_usb(1000000);
static QVector<double> data_usb_ch1(1000000);
static QVector<double> data_usb_ch2(1000000);

class Worker : public QObject
{
    Q_OBJECT

public:
    //LIBRARY USED VARIABLED DEFINITION
    //we aisgn the variables inside the trigger
    int counter=0;//this is the counter to control when to tell the main program to send the data
    int index=0;//this is the current amount of data recieved
    unsigned int time_rx,data_ch1,data_ch2;//store decimal data
    double data_ch1_double,data_ch2_double,time_rx_double;// rx como double
    int flag_time_minutes=1;//bandera para indicar cambio en el contador de minutos
    double time_resolution;
    unsigned char index_usb;
    unsigned char index_max=64; //= (usb_buffer_recep[0]);
    unsigned char index_zero=4;

    explicit Worker(QObject *parent = 0);

    static QThread *usb_thread2;
    /**

     * @brief Object which contains methods that should be runned in another thread
     */
    static Worker *usb_thread_worker2;
    static QObject *usb_thread_receiver;

     /*
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    //Worker *usb_thread_worker;
    //QThread *usb_thread;
    void requestWork();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abort();
private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;

signals:
    /**
     * @brief This signal is emitted when the Worker request to Work
     * @sa requestWork()
     */
    void workRequested();
    /**
     * @brief This signal is emitted when counted value is changed (every sec)
     */
    void valueChanged(const double* time,const double* data,const double*data_cc,const int &index);
    /**
     * @brief This signal is emitted when process is finished
     */
    void finished();
    void start();

public slots:
    /**
     * @brief Does something
     *
     * Counting is interrupted if #_aborted is set to true.
     */

    void doWork();

    void usb_data_correction();

    //define object and variables
    void usb_recep_setup();
    void usb_simulate_data_rep();
    void data_reception_test();
    void data_reception_1_ch();
    void data_reception_2_ch();
    //void create_thread_usb2(const QObject *receiver);
    static void thread_create_usb2(QThread *thread, Worker *thread_worker,const QObject *receiver);
private slots:
    void thread_delete_usb2(QThread *thread, Worker *thread_worker,const QObject *receiver);
    void thread_communication(const double *pointer_time,const double *pointer_data,const double *pointer_cc_data, int index);
};

#endif // THREAD_WORKER_H
