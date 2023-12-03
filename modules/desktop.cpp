#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#include "operations.h"

#define IMG1 0
#define IMG2 1
#define GRAY_IMG 2

using namespace cv;
using namespace std;


/* =================== *
 *  VARIAVEIS GLOBAIS  *
 * =================== */
/*  BOOLEANOS */
bool gray_option_selected = false;


/* ====================================== *
 *      IF USER == __APPLE__              *
 * =======================================*/
#ifdef __APPLE__
//std::cout << "Este programa está sendo compilado para macOS." << std::endl;
bool is_apple = true;

namespace fs = std::__fs::filesystem;
fs::path get_path() {
    // Carrega o caminho atual
        //anotacao:: Concatenar + "TEST " ::  / "test"  :: fs::current_path().parent_path() / "test"
    fs::path p = fs::current_path().parent_path();
    return p;
}
/* IMPORTANTE!! NECESSARIO DEFINIR PASTAS PARA CARREGAR E SALVAR IMAGENS */
const std::string src_folder = "/Users/lucasmachado/CIC/FPI/test_images/";
const std::string dst_folder = "/Users/lucasmachado/CIC/FPI/destiny_images/";

//test images
const string gramado = "Gramado_72k.jpg";
const string space = "Space_187k.jpg";
const string underwater = "Underwater_53k.jpg";

#else
/* ====================================== *
 *  IMPLEMENTAR LOGICA DE BUSCAR ARQUIVOS *
 * =================== ===================*/
bool is_apple = false;
#endif



bool loadImage(const std::string& img_name, cv::Mat& img){
    string path = src_folder + img_name;
    img = cv::imread(path,IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Erro ao carregar a imagem." << std::endl;
        return false;
    }
    return true;
};

void reset_images(std::vector<cv::Mat>& vec_img){
    vec_img[IMG2] = vec_img[IMG1];
    vec_img[GRAY_IMG] = convert_rgb_to_gray(vec_img[IMG1]);
}

void menu(cv::Mat& frame, string& selected_img, string& selected_op, std::vector<cv::Mat>& vec_img ){
    
    /* ============================================ *
     *   ATRIBUINDO VARIAVEIS PARA AS OPERACOES     *
     * ============================================ */ 
    cv::Mat3b img1 = vec_img[0];
    cv::Mat img2 = vec_img[1];
    cv::Mat1b gray_img = vec_img[2];

    /* MENU */

    frame = cv::Scalar(180, 110, 110); //cor frame :: cor menu
    int x = 55;  int y = 15; int incY; //incremento utilizado para avancar o Y 
   
    /* TEXTOS Variaveis */
    cvui::text(frame, 20 ,15, "Imagem selecionada: " , 0.5 , 0x120a8f);
    cvui::text(frame, 200 ,15,  selected_img , 0.5 , 0x7a1b0c);

    cvui::text(frame, 20 ,30, "Efeito selecionado: " , 0.5 , 0x120a8f);
    cvui::text(frame, 200 ,30, selected_op , 0.5 , 0x7a1b0c);

    /* Botao Atualiza New Image */
    string msg_escolha_imagem = "";
    if (cvui::button(frame, 20, 75, "NewImage <= Original")) {
        !gray_option_selected ? img2 = img1 : gray_img = convert_rgb_to_gray(vec_img[IMG1]);
    }
    /* =================== *
     *   DEMAIS BOTOES     *
     * =================== */ 
    // Escolha a foto a ser carregada
    y = 135; 
    incY = 40;
    cvui::text(frame, x-20,y - incY/2, "Escolha a foto a ser carregada ", 0.5 , 0x7a1b0c);
    if (cvui::button(frame, x, y, "Gramado_72k.jpg")) {
        selected_img = gramado;
    }
    if (cvui::button(frame, x, y + incY, "Space_187k.jpg")) {
        selected_img = space;
    }
    if (cvui::button(frame, x, y + 2*incY, "Underwater_53k.jpg")) {
        selected_img = underwater;
    }
    
    /* ESCOLHA A OPERACAO */
    y = y+ 160;
    cvui::text(frame, x-20,  y - 30, "Escolha a operacao ", 0.5 , 0x7a1b0c);

    if (cvui::button(frame, x, y, "Espelhar Horizontalmente")) {
        selected_op = "hflip";
        !gray_option_selected ? img2 = hflip(img2) : gray_img = hflip(gray_img);
    }
    if (cvui::button(frame, x, y + incY, "Espelhar Verticalmente")) {
         selected_op = "vflip";
        !gray_option_selected ? img2 = vflip(img2) : gray_img = vflip(gray_img);
    }
    /* !!! ATUALIZAR !!! */
    if (cvui::button(frame, x,  y + 2*incY, "Converter para cinza")) {
        gray_option_selected = !gray_option_selected;
    }
    /* BOTAO SALVAR IMAGEM */
    if (cvui::button(frame, x,  y + 3*incY, "Salvar Imagem")) {
        
    }
    /* BOTAO RESET */
    if (cvui::button(frame, 40,  550, "Reset")) {
        selected_op = "reset";
        img2 = img1;
        gray_option_selected = false;
    }

    /* REATRIBUINDO OS VALORES AO VETOR DE MATRIZES :: IMAGENS */
    vec_img[IMG2] = img2;
    vec_img[GRAY_IMG] = gray_img;
}

bool loadImage2(std::string img_name, cv::Mat& img, std::string path){
    path += "/test_images/" + img_name ;
    cout << "PATH __---__ :: " << path << endl; 
    
    img = cv::imread(path,IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Erro ao carregar a imagem." << std::endl;
        return false;
    }
    return true;
    
};


int main(int argc, const char *argv[])
{
    /* DEFINICAO :: MATRIZES :: IMAGENS */
    cv::Mat3b img1;
    cv::Mat img2;
    cv::Mat1b gray_img;
    std::vector<cv::Mat> matriz_vetor = {img1, img2, gray_img};

    string path_string = "";
    if(is_apple){
        std::cout << "Este programa está sendo compilado para macOS." << std::endl;

        /* GET PATH :: MACOS */
        fs::path dir_path = get_path();
        path_string = dir_path.string(); // Converte o caminho para uma representação de string
        cout << "Caminho: " << path_string << endl;
    }
    


    /* =================== *
     *      MENU FRAME     *
     * =================== */ 
    cv::Mat frame = cv::Mat(600, 350, CV_8UC3);
    // Window inicialization
    cvui::init("Menu");

    string selected_img = argc >= 2 ? argv[0] : gramado ;
    string selected_op = "";

    loadImage(selected_img, matriz_vetor[IMG1]);
    imshow("Original", matriz_vetor[IMG1]);

    //img2,gray_img == img1
    matriz_vetor[GRAY_IMG] = convert_rgb_to_gray(matriz_vetor[IMG1]);
    matriz_vetor[IMG2] = matriz_vetor[IMG1];

     /*TESTES */
    string path_gramado_teste = "/Users/lucasmachado/CIC/FPI/test_images/Gramado_72k.jpg";
    cout << "PATH CORRETO :: " << path_gramado_teste << endl;
    cv::Mat img_teste; 
    loadImage2(gramado, img_teste, path_string);
    imshow("TESTE", img_teste);

    while (true) {
 


        /* MENU */
        menu(frame,selected_img,selected_op, matriz_vetor);
        /* CINZA */
        cvui::text(frame, 20 ,50, "CHECKBOX CINZA: " , 0.5 , 0x8B008b);
        cvui::checkbox(frame, 170, 50, "CINZA?", &gray_option_selected, 0x8B008b);

        /* IMAGEM 1 */
        loadImage(selected_img, matriz_vetor[IMG1]); // Recarrega imagem :: util ao selecionar outra opcao
        imshow("Original", matriz_vetor[IMG1]);

         /* IMAGEM 2 */
        imshow("New Image", !gray_option_selected ? matriz_vetor[IMG2] : matriz_vetor[GRAY_IMG]);

        /* REFRESH FRAME MENU */
        cvui::update();
        cv::imshow("Menu", frame);
       

        /* CHECK ESC KEY WAS PRESSED */ 
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}


void path(){

      // Loads an image
    fs::path p = fs::current_path();


    cout << "The current path " << p << " decomposes into:\n"
              << "root-path " << p.root_path() << '\n'
              << "relative path " << p.relative_path() << '\n';

}

void foo(std::vector<cv::Mat>& vec_img)
{
    cv::Mat3b img1 = vec_img[0];
    cv::Mat img2 = vec_img[1];
    cv::Mat1b gray_img = vec_img[2];

    loadImage(underwater,img1);
    

    vec_img = {img1, img2, gray_img};

}
/* TO DOS
    * Configurar selecao de arquivo pra MacOS e fora de MacOS :: Load images 
    * Quantizar imagem em tons de cinza
    * A funcao load_image foi concebida com base nos diretorios locais do MacOS => é preciso alterar isto
    * 
    * Boas Praticas :: 
    *  passar variaveis globais por referencia 
    *  criar um arquivo separado para funcoes auxiliares 
    * Passar variaveis como cor para globais (nao sei se é possivel pq nao sao strings) :: 0x120a8f 
*/