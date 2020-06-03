#include "peak_detection.h"
#include <stdio.h>
#include <stdlib.h>
#include <QVector>
#include <QtMath>
#include <QDebug>
#include "digital_processing.h"
typedef int boolean;
#define winSize			120//Ventana inicial apra detectar maximo
#define trigtime	    350
void find_peak(QVector<double> x,QVector<double> y,QVector<int> &dZ_peak_i, QVector<double> &dZ_peak_t,QVector<double> &dZ_peak, int index_max,int ventana_max,double treshhold) {
    //Busca los picos locales contenidos entre un intervalo de 1.3 segundos (que alvergara al menos 1 máximo)
    //El punto de inicio para buscar un pico és el último pico encontrado + la ventana mínima
    //El punto de final es el ultimo
    //Funcionamiento:
    //Busca un valor que supere el treshold:
        //lo coloca como maximo
        //Si ese máximo se sostiene como tal por el intervalo de la ventana (200 ms)
        // entonces lo considera como pico
    //Repite este proceso hasta que ya no encuentre máximos
    double max=treshhold;//%inicio en el; treshhold
    int ventana_contador=0;
    int indedZ_peak_t;
    int indedZ_peak_t_index=dZ_peak_i[0];//Valor seteado del indice
    int index=0;
    int peak_limit=2.5*dZ_peak[1];
    bool validar_maximo_on=false;
    for (index=(dZ_peak_i[indedZ_peak_t_index]+ventana_max); index < index_max; index++)
    {
               if ((y[index]>max)&&(y[index]<peak_limit))
                   {
                   max=y[index];
                   indedZ_peak_t=index;
                   ventana_contador=0;
                   validar_maximo_on=true;
                   }
                if(validar_maximo_on==true)
                     {
                       if (y[index]<max)
                       {
                       ventana_contador=ventana_contador+1;
                       if (ventana_contador==ventana_max)
                          {indedZ_peak_t_index=indedZ_peak_t_index+1;//Aumenta para idndicar que encontro un pico
                          dZ_peak_i[0]=indedZ_peak_t_index;
                          dZ_peak_i[indedZ_peak_t_index]= indedZ_peak_t;
                          dZ_peak_t[indedZ_peak_t_index]=x[indedZ_peak_t];
                          dZ_peak[indedZ_peak_t_index]=y[indedZ_peak_t];
                         // Debug_custom()<< " Pico en el indice" << QString::number(indedZ_peak_t)<<",pico de valor:"<<QString::number(dZ_peak[indedZ_peak_t_index])<<",indice:"<<QString::number(dZ_peak_i[0]);
                          max=treshhold;

                          }
                       }
                      }
                    }

    }

void find_peak_first(QVector<double> x,QVector<double> y,QVector<int> &dZ_peak_i, QVector<double> &dZ_peak_t,QVector<double> &dZ_peak,int index_init, int index_max,int ventana_max,double treshhold) {
    //Realiza una busqueda del primer valor pico, tomando como inicio el valor en donde es 0
    //Tomo como pico un valor que supere el treshold
    //Si ese valor se mantiene como pico durante una ventana (en general 0.5 segundos)
    //Sera un valor valido,el programa termina el lazo for y retorna el indicen que lo contiene.
    //Sino, coloca el indice como 0.
    double max=treshhold;//%inicio en el; treshhold
    int indedZ_peak_t;
    int ventana_contador=0;
    bool validar_maximo_on=false;
    int index;
    for (index=index_init; index < index_max; index++)
    {
               if (y[index]>max)
                   {
                   max=y[index];
                   indedZ_peak_t=index;
                   ventana_contador=0;
                   validar_maximo_on=true;
                   }
                if(validar_maximo_on==true)
                     {
                       if (y[index]<max)
                       {
                       ventana_contador=ventana_contador+1;
                       if (ventana_contador==ventana_max)
                          {dZ_peak_i[0]=1;
                          dZ_peak_i[1]= indedZ_peak_t;
                          dZ_peak_t[1]=x[indedZ_peak_t];
                          dZ_peak[1]=y[indedZ_peak_t];
                          //Debug_custom() << QString::number(indedZ_peak_t)<< " Ubicación del primer pico en indice"<<QString::number(dZ_peak_i[0]) ;
                          validar_maximo_on=false;//Para salir del for
                          break;//Para salir del for
                          }
                       }
                      }
                    }

}

void find_peak_min_and_cero(QVector<double> x,QVector<double> y,QVector<double> y_derivada, QVector<int> &dZ_peak_i,QVector<double> &T_EV, int dZ_peak_i_init,int ventana_max) {
    //Realiza una busqueda del primer valor pico, tomando como inicio el valor en donde es 0
    //Tomo como pico un valor que supere el treshold
    //Si ese valor se mantiene como pico durante una ventana (en general 0.5 segundos)
    //Sera un valor valido,el programa termina el lazo for y retorna el indicen que lo contiene.
    //Sino, coloca el indice como 0.
    int index;
    int index_cero_max;
    double x_cero=0;
    double dZ_peak_t_min=0;
    int indedZ_peak_t_max;
    int indedZ_peak_t_limit=dZ_peak_i[0];
    int indedZ_peak_t_start;
    int index_pks=dZ_peak_i_init+1;
           int aux=dZ_peak_i[1];
    int treshold_min=y[aux]/10;
    while (index_pks<=indedZ_peak_t_limit){
        indedZ_peak_t_start=dZ_peak_i[index_pks];
        //indedZ_peak_t_max=dZ_peak_t_start+min_peak_dist_sample;
        //if (indedZ_peak_t_max>indedZ_peak_t_limit)
        //   {indedZ_peak_t_max=indedZ_peak_t_limit;}
        indedZ_peak_t_max=indedZ_peak_t_start+ventana_max;
       for (index =indedZ_peak_t_start; index < indedZ_peak_t_max; index++)
        {
            if ((y_derivada[index] < 0) && (y_derivada[index-1] < 0) && (y_derivada[index +1] > 0)&&(y[index]<treshold_min))
               {dZ_peak_t_min=x[index];
               Debug_custom() <<" Min en indice"<<QString::number(x[index])<<" Max en indice"<<QString::number(x[indedZ_peak_t_start]);
               index=indedZ_peak_t_max;
               break;}
        }
            index_cero_max=indedZ_peak_t_start-ventana_max;
            //ddeteción de cero
        for (index =indedZ_peak_t_start; index > index_cero_max; index=index-1)
            {
            if ((y[index] < 0) && (y[index-1] < 0) && (y[index +1] > 0))
              {x_cero= x[index];
                Debug_custom() <<" Cero en indice"<<QString::number(x[index]) ;
                index=indedZ_peak_t_max;
                break;}
           }
        T_EV[index_pks]=dZ_peak_t_min-x_cero;
        //Debug_custom()<<" T EV="<<QString::number(T_EV[index_pks], 'f', 4)  <<" en indice"<<QString::number(dZ_peak_i[index_pks]);
        index_pks=index_pks+1;
        }


}

void gasto_cardiaco(QVector<double> dZ_peak_t,QVector<double> &dZ_peak, QVector<double> &T_EV,QVector<double> &T_cardio,QVector<double> &GC_kubicek,QVector<double> &GC_samek,int index_init, int index_max,QVector<double> &Z0, double DISTANCIA_ELECTRODOS) {
    //Realiza una busqueda del primer valor pico, tomando como inicio el valor en donde es 0
    //Tomo como pico un valor que supere el treshold
    //Si ese valor se mantiene como pico durante una ventana (en general 0.5 segundos)
    //Sera un valor valido,el programa termina el lazo for y retorna el indicen que lo contiene.
    //Sino, coloca el indice como 0.
    int index=(T_cardio[1]);//Cargo el valor de indice
    int indedZ_peak_t=index_init;//Indice de valor pico
    double aux_T_cardio;
    //IMPORTANTE
    // T_cardio[0]=Valor promedio de T_cardio
    // T_cardio[1]=Indice de T_cardio ()
    // T_cardio[2]=1er valor de T_cardio
    //.......
    //.T_cardio[N]=(N-1)avo valor de T_cardio
    //Por lo tanto, el numero de valores de T_cardio es igual a: indice del vector-1
   //Debug_custom() <<"indice gasto cardiaco:"<<QString::number(index)<<",i de pico : "<<QString::number(indedZ_peak_t)<<"a" <<QString::number(index_max);
    while (indedZ_peak_t<=index_max){
        aux_T_cardio=dZ_peak_t[indedZ_peak_t]-dZ_peak_t[indedZ_peak_t-1];//intervalo latido a latido
        if ((index<3)&(indedZ_peak_t>1))
        {
          index=2;
          T_cardio[index]=aux_T_cardio;
         // Debug_custom() <<" Primer valor de T QRS : "<<QString::number(T_cardio[index]) ;
          dZ_peak[index]=((dZ_peak[indedZ_peak_t]));
          T_cardio[0]=T_cardio[index];
          T_EV[0]=T_EV[index];
          dZ_peak[0]=((dZ_peak[indedZ_peak_t]));
          //Z0[0]=((Z0[indedZ_peak_t]));
          index=index+1;
        }
        else
        {
        if ((1==1)&(T_EV[index]>0)&aux_T_cardio<(2))//Condicion adicional aux_T_cardio<(2*(T_cardio[2]
            {
            T_cardio[index]=aux_T_cardio;
            T_cardio[0]=((T_cardio[0])*(index-2)+T_cardio[index])/(index-1);
                        //Debug_custom() <<" Valor medio de T QRS : "<<QString::number(T_cardio[0]) ;
            T_EV[0]=((T_EV[0])*(index-2)+T_EV[index])/(index-1);//valor promedio
                      // Debug_custom() <<" Valor medio de T_EV : "<<QString::number(T_EV[0]) ;
            dZ_peak[0]=((dZ_peak[0])*(index-2)+dZ_peak[indedZ_peak_t])/(index-1);
            //Z0[0]=((Z0[0])*(index-2)+Z0[indedZ_peak_t])/(index-1);
            //Debug_custom() <<" Valor medio de y0 : "<<QString::number(dZ_peak[0])<<" Valor pico de yo : "<<QString::number(dZ_peak[indedZ_peak_t]) ;
            GC_kubicek[index]=K_KUBICEK*((((qPow(0.17*DISTANCIA_ELECTRODOS/(Z0[0]), 2))*(60*T_EV[0])*(dZ_peak[0])))/(1000*(T_cardio[0])));
            GC_kubicek[0]=index;//Guarda el indice actual.
            GC_samek[index]=(1/K_SAMEK)*((qPow(0.17*DISTANCIA_ELECTRODOS, 3))*((1/(Z0[0]))*(60*T_EV[0])*(dZ_peak[0])))/(1000*(T_cardio[0]));
            GC_samek[0]=index;
            //Debug_custom() <<" GC kubicek : "<<QString::number(GC_kubicek[index])<< "GC indice "<<QString::number(index) ;
            //Debug_custom() <<" GC samek : "<<QString::number(GC_samek[index]) ;
            index=index+1;
            }
        }
        indedZ_peak_t=indedZ_peak_t+1;
       }
        T_cardio[1]=index;
        Debug_custom() <<"Valor de dz/dt medio : "<<QString::number(dZ_peak[index]) ;
}


