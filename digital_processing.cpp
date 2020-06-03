
#include "digital_processing.h"
//gets the medium value of a sample
double medium(QVector<double> y,int index_init,int index_end,QVector<double> media)
{
   int index;
   int index_samples=0;
   double media_aux=0;
           for (index =index_init; index < index_end; ++index)
            {
            media_aux=media_aux+y[index];
            index_samples=index_samples+1;
            }
   return(media_aux/index_samples);
}
//Does a convolution operation (ex: to apply a filter) to the vectors

void decimate(QVector<double> x,QVector<double> h,QVector<double>  &aux_conv,int index,int size_convolution){

//La respuesta es guardada el vector de entrada 'aux_conv' gracias a '&'
//Demodo que esta función no necesita crear nuevos espacios de memoria
    int i,j,j_i,size_h,long_conv,index_conv;
    size_h=h.size();
    long_conv=index+size_convolution+2;
    if (index>(size_h+size_convolution))
        index_conv=index-size_h;//Considero los datos anteriores
        else
        index_conv=0;

    for (i=index; i<long_conv; i++)
    {
        aux_conv[i]=0;
        for (j=index_conv; j<(long_conv); j++)
        {
            j_i=i-j+1;
            if((j_i>=0)&(j_i<(size_h)))
                aux_conv[i] = aux_conv[i] + (x[j]*h[j_i]);
        }

    }
}
//Derivates
void derivate(QVector<double> x,QVector<double> h,QVector<double>  &aux_conv,int index,int size_convolution){

//La respuesta es guardada el vector de entrada 'aux_conv' gracias a '&'
//Demodo que esta función no necesita crear nuevos espacios de memoria
    int i,j,j_i,size_h,long_conv,index_conv;
    size_h=h.size();
    long_conv=index+size_convolution+2;
    if (index>(size_h+size_convolution))
        index_conv=index-size_h;//Considero los datos anteriores
        else
        index_conv=0;

    for (i=index; i<long_conv; i++)
    {
        aux_conv[i]=0;
        for (j=index_conv; j<(long_conv); j++)
        {
            j_i=i-j+1;
            if((j_i>=0)&(j_i<(size_h)))
                aux_conv[i] = aux_conv[i] + (x[j]*h[j_i]);
        }

    }
}
//Does a convolution operation (ex: to apply a filter) to the vectors
void convolution(QVector<double> x,QVector<double> h,QVector<double>  &aux_conv,int index,int size_convolution){

//La respuesta es guardada el vector de entrada 'aux_conv' gracias a '&'
//Demodo que esta función no necesita crear nuevos espacios de memoria
    int i,j,j_i,size_h,long_conv,index_conv;
    size_h=h.size();
    long_conv=index+size_convolution+2;
    if (index>(size_h+size_convolution))
        index_conv=index-size_h;//Considero los datos anteriores
        else
        index_conv=0;

    for (i=index; i<long_conv; i++)
    {
        aux_conv[i]=0;
        for (j=index_conv; j<(long_conv); j++)
        {
            j_i=i-j+1;
            if((j_i>=0)&(j_i<(size_h)))
                aux_conv[i] = aux_conv[i] + (x[j]*h[j_i]);
        }

    }
}

void interpolate_linear(QVector<double> &time,QVector<double> &data1,QVector<double> &data2,int &index,int size_interpolation){
    double pendiente_cc,ordenada_cc,pendiente,ordenada,pendiente_t,ordenada_t;
    int index_interpolate;
    int size=size_interpolation+1;
    data2[index+size_interpolation]=data2[index];
    data1[index+size_interpolation]=data1[index];
    time[index+size_interpolation]=time[index];
    //Disminuyo el indice:
    index=index-1;
    ordenada=data1[index];//Tomo el valor anterior, que es el correcto
    pendiente=(data1[index+size]-ordenada)/(size);
    ordenada_cc=data2[index];//Tomo el valor anterior, que es el correcto
    pendiente_cc=(data2[index+size]-ordenada_cc)/size;
    ordenada_t=time[index];//Tomo el valor anterior, que es el correcto
    pendiente_t=(time[index+size]-ordenada_t)/size;
    for(index_interpolate=1; index_interpolate <size; ++index_interpolate)
        //recorre indice de 1 a 10
       {
        data1[index+index_interpolate]=index_interpolate*pendiente_cc + ordenada_cc;
        data2[index+index_interpolate]=index_interpolate*pendiente + ordenada;
        time[index+index_interpolate]=index_interpolate*pendiente_t + ordenada_t;
        }
    //Añadao los valores para indicar que recibi
    index=index+size;//Aumento el contador de data_DZ en 1

}
