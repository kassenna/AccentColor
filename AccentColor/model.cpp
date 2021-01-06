//
// Created by kasia on 28.11.2019.
//

#include "model.h"
#include <thread>
#include "../SO_CPP/libraryCPP.h"
#include <iostream>
#include <cmath>
extern "C" int accentASM(float*, int, int, int);


void threadsCPP(unsigned char * bgr, int h, int range, int *  v, int begin, int end)
{
    for(int i = begin; i<end; i++)
    accentCPP( bgr, h, range, v[i], i);
}
void threadsAsm(unsigned char * bgr, int h, int range, int *  v, int begin, int end, int z)
{
    int j = 4*begin;
    int i =0;
    for(i = begin; i<end; i++){
       float input[4] = {(float)bgr[j], (float)bgr[j+1], (float)bgr[j+2], 0.0f};
        accentASM(input, h, range, v[i]);
        bgr[j]   = (unsigned char)input[0];
        bgr[j+1] = (unsigned char)input[1];
        bgr[j+2] = (unsigned char)input[2];
        j+=4;
  }
}
void Model::RGBtoHSV(float r, float g, float b, int it){

    unsigned char v;
    float x = std::fmin(r, std::fmin(g, b));
    v =  (unsigned int)std::fmax(r, std::fmax(g, b));
    if((float)v == x)
         return;

    float i;
    float f;
    if(r == x) {
        f = (float)(g - b);
        i = 3;
    }
    else if(g == x) {
        f = (float)(b - r);
        i = 5;
    }
    else
    {
        f = (float)(r - g);
        i = 1;
    }
    picture[it]= fmod((i - f / (float)((float)v - x)) * 60, 360);
}
Model::Model() {
}

int Model::byASM(unsigned char* data, int end, int colorUser, int range, int thread) {
    end = (end >>2);

    picture = new int[end];
    int j = 0;
    for (int i = 0; i < end; i++) {
        RGBtoHSV(data[j + 2], data[j + 1], data[j], i);
        j += 4;
    }
    if(thread ==0){
            threadsAsm( data, colorUser, range, picture, 0, end, 0);
    }else {
        int k = end / thread;
        int r = end % thread;
        std::vector<std::thread> threads;
        int i = 0;
       for (i = 0; i < thread; i++) {
            threads.emplace_back(threadsAsm, data, colorUser, range, picture, i * k, (i + 1) * k - 1, i);
        }
           threads.emplace_back(threadsAsm, data, colorUser, range, picture, i * k, i * k + r, i);

        for (auto &it : threads)
            it.join();
    }
}
void Model::byCPP(unsigned char* data, int end, int colorUser, int range, int thread) {
    end = (end >>2);
    picture = new int[end];
    int j = 0;
    for (int i = 0; i < end; i++) {
        RGBtoHSV(data[j + 2], data[j + 1], data[j], i);
        j += 4;
    }
    if(thread ==0){
        for(int i = 0; i<end; i++)
            accentCPP(data, colorUser, range, picture[i], i);
    }else {
        int k = end / thread;
        int r = end % thread;
        std::vector<std::thread> threads;
        int i = 0;
        for (i = 0; i < thread; i++) {
            threads.emplace_back(threadsCPP, data, colorUser, range, picture, i * k, (i + 1) * k - 1);
        }
        i++;
        threads.emplace_back(threadsCPP, data, colorUser, range, picture, i * k, i * k + r);
        for (auto &it : threads)
            it.join();
    }
 }
 unsigned int Model::numberOfThread() {
    return  std::thread::hardware_concurrency();
}




