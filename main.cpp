#include <iostream>
#include <opencv2/opencv.hpp>

#include "operations.h"

using namespace cv;
using namespace std;




int main() {

    cv::Mat frame = cv::Mat(200,500, CV_8UC3);
    frame = cv::Scalar(49, 52, 49);

    std::string src = "/Users/lucasmachado/CIC/FPI/test_images/";
    std::string dst = "/Users/lucasmachado/CIC/FPI/destiny_images/";

    std::string src_gramado = src + "Gramado_72k.jpg";
    string dst_gramado = dst + "Gramado_72k.jpg";

    cv::Mat img = cv::imread(src_gramado);

    if (img.empty()) {
        std::cerr << "Erro ao carregar a imagem." << std::endl;
        return -1;
    }

    // Crie uma matriz 5x5 preenchida com zeros
    cv::Mat m1(5, 5, CV_8UC1, cv::Scalar(0));

    for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            m1.at<uchar>(i, j) = j*(i+1);
        }
    }

    cv::Mat m2(5, 5, CV_8UC1, cv::Scalar(0));

    int columns = m1.cols;

    // Selecione a segunda linha (índice 1) da matriz m1
    cv::Mat linha = m1.row(0);


//    for (int j = 0; j < columns; j++) {
//        cv::Mat column = m1.col(j);
//        memcpy(m2.col(columns - j - 1).data, column.data, m1.rows);
//    }
    cv::Mat column = m1.col(4);

    std::cout << "Column :\n" << column << std::endl;

    memcpy(m2.col(0).data, column.data, m1.rows);

    // Imprima a matriz m2
    std::cout << "Matriz m1:\n" << m1 << std::endl;

    // Imprima a matriz m2
    std::cout << "Matriz m2:\n" << m2 << std::endl;
    // Transponha a matriz
    cv::Mat transposed = m1.t();

    // Exiba a matriz original e a matriz transposta
    std::cout << "Matriz Original:\n" << m1 << std::endl;
    //std::cout << "Matriz Transposta:\n" << transposed << std::endl;

    cv::Mat m3 = vflip(transposed);
    cv::Mat m4 =  m3.t();
    std::cout << "M3 :\n" << m4 << std::endl;



    cv::Mat img_vf = vflip(img);
    cv::Mat img_hf = hflip(img);

    // Exiba a imagem original e a imagem invertida
    cv::imshow("Imagem Original", img);
    cv::imshow("Imagem VF", img_vf);
    cv::imshow("Imagem HF", img_hf);
    cv::waitKey(0);


    return 0;


    cv::waitKey(0);

    return 0;
}