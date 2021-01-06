//
// Created by kasia on 28.11.2019.
//

#ifndef JA_MODEL_H
#define JA_MODEL_H
struct HSV{
    float h;
    unsigned int s;
    unsigned int v;
};


#include <QtGui/QColor>
#include <QtGui/QImage>

class Model {
    int (*funkcja)(float*, int, int, int);
private: void *Biblioteka;
private: HSV colorHSV;
private:
   int* picture;
public: void RGBtoHSV(float b, float g, float r, int i);
public:  Model();
public: int byASM(uchar* data, int end, int colorUser, int range, int thread);
public: void byCPP(uchar*, int size, int colorUser, int range, int);
public: static unsigned int numberOfThread();
};



#endif //JA_MODEL_H
