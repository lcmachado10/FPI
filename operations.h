//
// Created by Lucas Machado on 06/11/23.
//

#ifndef OPEN_CV_PROJECT_OPERATIONS_H
#define OPEN_CV_PROJECT_OPERATIONS_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


/*  converte imagem colorida para imagem em tons de cinza */
cv::Mat1b convert_rgb_to_gray(const Mat3b& src) ;


/* vertical_flip: espelhamento vertical de imagens coloridas, trocando pixel a pixel atraves de dois lacos for */
cv::Mat3b vertical_flip(cv::Mat3b src) ;

/* horizontal_flip: espelhamento vertical de imagens coloridas, trocando pixel a pixel atraves de dois lacos for */
cv::Mat3b horizontal_flip(cv::Mat3b src);

/* vflip: Espelhamento vertical da imagem, utilizando memcpy para inverter linha a linha em vez de ponto a ponto */
cv::Mat vflip(const cv::Mat& src);


/* hflip: Espelhamento horizontal da imagem,  transpoe a matriz, e utiliza a funcao vflip, em seguida transpoe de volta */
cv::Mat hflip(const cv::Mat& src);
#endif //OPEN_CV_PROJECT_OPERATIONS_H
