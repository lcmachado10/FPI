#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void calcularHistograma(const cv::Mat& imagem) {
    // Configuração dos parâmetros para o cálculo do histograma
    int canais[] = {0}; // Calcula o histograma apenas no canal 0 (escala de cinza)
    int nbins = 256; // Número de bins (intensidades) no histograma
    float intervalo[] = {0, 256}; // Intervalo dos valores de intensidade
    const float* faixas[] = {intervalo};

    // Calcula o histograma
    cv::Mat histograma;
    cv::calcHist(&imagem, 1, canais, cv::Mat(), histograma, 1, &nbins, faixas);

    // Exibe o histograma (opcional)
    int largura = 512;
    int altura = 400;
    cv::Mat histImage(altura, largura, CV_8UC3, cv::Scalar(255, 255, 255));

    // Normaliza o histograma para que ele caiba na imagem
    cv::normalize(histograma, histograma, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // Desenha o histograma
    for (int i = 1; i < nbins; i++) {
        line(histImage, cv::Point(i - 1, altura - cvRound(histograma.at<float>(i - 1))),
             cv::Point(i, altura - cvRound(histograma.at<float>(i))),
             cv::Scalar(0, 0, 0), 2, 8, 0);
    }

    // Exibe o histograma (opcional)
    imshow("Histograma", histImage);
    cv::waitKey(0);
}

cv::Mat calcularNegativo(const cv::Mat& imagem) {
    // Criar uma imagem de saída com as mesmas dimensões e tipo que a imagem original
    cv::Mat resultado = imagem.clone();

    // Inverter as intensidades dos pixels usando a fórmula: novo_valor = 255 - valor_antigo
    resultado = 255 - resultado;

    return resultado;
}



cv::Mat calcularNegativoColorido(const cv::Mat& imagem) {
    // Criar uma imagem de saída com as mesmas dimensões e tipo que a imagem original
    cv::Mat resultado = imagem.clone();

    // Inverter as intensidades dos canais de cor (RGB)
    cv::bitwise_not(resultado, resultado);

    return resultado;
}

cv::Mat quantizarTonsDeCinza(const cv::Mat& imagem, int niveis) {
    cv::Mat imagemQuantizada;
    
    // Quantizar os tons de cinza
    cv::Mat imagemConvertida;
    cv::cvtColor(imagem, imagemConvertida, cv::COLOR_BGR2GRAY);

    // Normalizar os valores antes da quantização
    cv::normalize(imagemConvertida, imagemConvertida, 0, 255, cv::NORM_MINMAX);

    // Quantizar usando a função cv::divide
    cv::divide(imagemConvertida, cv::Scalar::all(256.0 / niveis), imagemQuantizada);
    cv::convertScaleAbs(imagemQuantizada, imagemQuantizada);

    return imagemQuantizada;
}

//     int q: how many colors will be used
void quantization(cv::Mat1b& src, int q) {
    int divisor = 256 / q;
    int max_quantized_value = 255 / divisor;

    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            src.at<uchar>(r, c) = ((src.at<uchar>(r, c) / divisor) * 255) / max_quantized_value;
        }

    }
}

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
int main() {
    // Carrega a imagem
    cv::Mat imagem = cv::imread("/Users/lucasmachado/CIC/FPI/FPI/test_images/Space_187k.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat imagemColor = cv::imread("/Users/lucasmachado/CIC/FPI/FPI/test_images/Space_187k.jpg", cv::IMREAD_COLOR);

    if (imagem.empty()) {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    // Definir o número desejado de níveis (por exemplo, 4 para uma quantização de 4 tons)
    int niveis = 110;

    // Aplicar a quantização em tons de cinza
    //cv::Mat imagemQuantizada = quantizarTonsDeCinza(imagemColor, niveis);
    cv::Mat1b imagemQuantizada = convert_rgb_to_gray(imagemColor);
    quantization(imagemQuantizada,8);

    // Calcular o negativo da imagem colorida
    cv::Mat imagemNegativaColorida = calcularNegativoColorido(imagem);


    // Calcula o histograma
    //calcularHistograma(imagem);

    // Exibir as imagens original e negativa
    cv::imshow("Imagem Colorida Original", imagemColor);
    cv::imshow("Imagem original cinza", imagem);
    cv::imshow("Imagem Colorida Negativa", imagemNegativaColorida);
    cv::imshow("Imagem Quantizada", imagemQuantizada);
    cv::waitKey(0);

    return 0;
}
