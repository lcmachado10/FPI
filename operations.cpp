//
// Created by Lucas Machado on 06/11/23.
//

#include "operations.h"


/*
 *  convert_rgb_to_gray: Mat3b -> Mat1b
 *      Converte imagem colorida[Mat3b] para imagem em tom de cinza [Mat1b] (luminancia)
 *          Formula utilizada para o calculo:
 *          L = 0.299 * Red + 0.587 * Green + 0.114 * Blue
 */
cv::Mat1b convert_rgb_to_gray(const Mat3b& src) {
    cv::Mat1b dst;
    dst = Mat1b(src.rows, src.cols);

    for (int j = 0; j < src.rows; j++) {
        for (int i = 0; i < src.cols; i++) {
            Vec3b color = src.at<Vec3b>(j, i);
            uchar gray_value = static_cast<uchar>(0.114 * color[0] + 0.587 * color[1] + 0.299 * color[2]);
            dst.at<uchar>(j, i) = gray_value;
        }
    }
    return dst;
}

/* vertical_flip: espelhamento vertical de imagens coloridas,
 *                  trocando pixel a pixel atraves de dois lacos for
 */
cv::Mat3b vertical_flip(cv::Mat3b src) {
    cv::Mat3b dst(src.rows, src.cols);
    int columns = src.cols;
    int rows = src.rows;

    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < rows; i++) {
            cv::Vec3b color = src.at<cv::Vec3b>(i, j);
            int mirrored_row = rows - i - 1; // Calcula posição espelhada na matriz de destino
            memcpy(&dst.at<cv::Vec3b>(mirrored_row, j), &color, sizeof(cv::Vec3b));
        }
    }
    return dst;
}

/* horizontal_flip: espelhamento vertical de imagens coloridas,
 *                  trocando pixel a pixel atraves de dois lacos for
 */
cv::Mat3b horizontal_flip(cv::Mat3b src) {
    int rows = src.rows;
    int cols = src.cols;
    cv::Mat3b dst(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Vec3b color = src.at<cv::Vec3b>(i, j);
            int mirrored_col = cols - j - 1;
            memcpy(&dst.at<cv::Vec3b>(i, mirrored_col), &color, sizeof(cv::Vec3b));
        }
    }
    return dst;
}
/*
 * vflip: Espelhamento vertical da imagem,
 *        utilizando memcpy para inverter linha a linha em vez de ponto a ponto
 */
cv::Mat vflip(const cv::Mat& src) {
    int columns = src.cols;
    int rows = src.rows;
    cv::Mat dst(rows, columns, src.type());

    for (int i = 0; i < rows; i++) {
        cv::Mat row = src.row(i);
        std::memcpy(dst.row(rows - i - 1).data, row.data, src.cols * src.elemSize());
    }

    return dst;
}
//hflip: Espelhamento horizontal da imagem,
//                transpoe a matriz, e utiliza a funcao vflip, em seguida transpoe de volta
cv::Mat hflip(const cv::Mat& src) {
    cv::Mat img_aux = src.t();
    cv::Mat dst = vflip(img_aux).t();
    return dst;
}