#ifndef PEAK_DETECTION_H
#define PEAK_DETECTION_H


#define Debug_custom qDebug



#define K_KUBICEK 135 // [cm*ohm]Constante de la ecuación de kubicek
#define K_SAMEK 4.25
#include <QVector>
void find_peak(QVector<double> x,QVector<double> y,QVector<int> &dZ_peak_i, QVector<double> &dZ_peak_t,QVector<double> &dZ_peak, int index_max,int ventana_max,double treshhold);
void find_peak_first(QVector<double> x,QVector<double> y, QVector<int> &dZ_peak_i, QVector<double> &dZ_peak_t,QVector<double> &dZ_peak,int index_init, int index_max,int ventana_max,double treshhold) ;
void find_peak_min_and_cero(QVector<double> x,QVector<double> y,QVector<double> y_derivada, QVector<int> &dZ_peak_i,QVector<double> &T_EV, int dZ_peak_i_init,int ventana_max);
void gasto_cardiaco(QVector<double> dZ_peak_t,QVector<double> &dZ_peak, QVector<double> &T_EV,QVector<double> &T_cardio,QVector<double> &GC_kubicek,QVector<double> &GC_samek,int index_init, int index_max,QVector<double> &Z0, double DISTANCIA_ELECTRODOS) ;
#endif // PEAK_DETECTION_H
