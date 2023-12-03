#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

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


int main() {
    // Carrega a imagem
    cv::Mat imagem = cv::imread("/Users/lucasmachado/CIC/FPI/FPI/test_images/Gramado_72k.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat imagemColor = cv::imread("/Users/lucasmachado/CIC/FPI/FPI/test_images/Gramado_72k.jpg", cv::IMREAD_COLOR);

    if (imagem.empty()) {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    // Calcular o negativo da imagem colorida
    cv::Mat imagemNegativaColorida = calcularNegativoColorido(imagem);

    // Calcula o histograma
    //calcularHistograma(imagem);

      // Exibir as imagens original e negativa
    cv::imshow("Imagem Colorida Original", imagemColor);
    cv::imshow("Imagem Colorida Negativa", imagemNegativaColorida);
    cv::waitKey(0);


    return 0;
}
