#include <iostream>
#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#include "operations.h"

using namespace cv;
using namespace std;

/* IMPORTANTE!! NECESSARIO DEFINIR PASTAS PARA CARREGAR E SALVAR IMAGENS */
const std::string src_folder = "/Users/lucasmachado/CIC/FPI/test_images/";
const std::string dst_folder = "/Users/lucasmachado/CIC/FPI/destiny_images/";

//test images
const string gramado = "Gramado_72k.jpg";
const string space = "Space_187k.jpg";
const string underwater = "Underwater_53k.jpg";




bool loadImage(const std::string& img_name, cv::Mat& img){
    string path = src_folder + img_name;
    img = cv::imread(path,IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Erro ao carregar a imagem." << std::endl;
        return false;
    }
    return true;
};

/* bc == button clicked */
bool bcImg1 = false;
bool bcImg2 = false;
string selected_img = "";
string selected_op = "";



int main(int argc, const char *argv[])
{
    cv::Mat img;
    cv::Mat img2;

    // Menu frame
    cv::Mat frame = cv::Mat(600, 1300, CV_8UC3);
    // Window inicialization
    cvui::init("Menu");

    while (true) {
        frame = cv::Scalar(180, 110, 110); //cor frame
        cvui::text(frame, 300 ,40, "Imagem selecionada: " + selected_img, 0.5 , 0x120a8f);

        if (cvui::button(frame, 40, 40, "Carregar Imagem")) {
            bcImg1 = true;
        }

        // Escolha a foto a ser carregada
        if (bcImg1) {
            cvui::text(frame, 40,90, "Escolha a foto a ser carregada ", 0.5 , 0x7a1b0c);
            if (cvui::button(frame, 40, 120, "Gramado_72k.jpg")) {
                selected_img = gramado;
            }
            if (cvui::button(frame, 40, 160, "Space_187k.jpg")) {
                selected_img = space;
            }
            if (cvui::button(frame, 40, 200, "Underwater_53k.jpg")) {
                selected_img = underwater;
            }
        }

        if (selected_img != "") {
            /* CARREGA IMAGEM NO FRAME */
            loadImage(selected_img, img);
            cvui::image(frame, 300, 200, img);

            /* ESCOLHA A OPERACAO */
            cvui::text(frame, 40,250, "Escolha a operacao ", 0.5 , 0x7a1b0c);
            if (cvui::button(frame, 40, 280, "Espelhar Horizontalmente")) {
                selected_op = "hflip";
            }
            if (cvui::button(frame, 40, 320, "Espelhar Verticalmente")) {
                selected_op = "vflip";
            }
            if (cvui::button(frame, 40, 360, "Converter para cinza")) {
                selected_op = "rgb_to_gray";
            }
        }

        if (selected_op != "") {
            if (selected_op == "hflip") {
                img2 = hflip(img);
            } else if (selected_op == "vflip") {
                img2 = vflip(img);
            } else if (selected_op == "rgb_to_gray") {
                cout<< "lembrar que é uma matriz 1b" << endl;
            }

            /* CARREGA IMG2 */
            cvui::image(frame, 650, 200, img2);
            imshow("nova image", img2);
        }
        cvui::update();
        cv::imshow("Menu", frame);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}