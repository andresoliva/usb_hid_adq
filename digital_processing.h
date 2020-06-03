#ifndef DIGITAL_PROCESSING_H
#define DIGITAL_PROCESSING_H
#include <QVector>

class digital_processing
{
public:
    digital_processing();
};


void convolution(QVector<double> x,QVector<double> h,QVector<double>  &aux_conv,int index,int size_convolution);
double medium(QVector<double> y,int index_init,int index_end,QVector<double> media);
void decimate(QVector<double> x,QVector<double> h,QVector<double>  &aux_conv,int index,int size_decimate);
void interpolate_linear(QVector<double> x,QVector<double>  &result,int index,int size_interpolation);
#endif // DIGITAL_PROCESSING_H
