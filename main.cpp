#include <iostream>
#include <opencv2/opencv.hpp>

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

    int height = img.rows;
    int width = img.cols;

    cv::Mat mirrored_img = img.clone();  // Criar uma cópia da imagem

    for (int row = 0; row < height / 2; row++) {
        int opposite_row = height - 1 - row;
        uchar* row_ptr = img.ptr<uchar>(row);
        uchar* opposite_row_ptr = img.ptr<uchar>(opposite_row);

        // Inverta as linhas usando memcpy
        std::memcpy(mirrored_img.data + row * mirrored_img.step, opposite_row_ptr, width * mirrored_img.elemSize());
        std::memcpy(mirrored_img.data + opposite_row * mirrored_img.step, row_ptr, width * mirrored_img.elemSize());
    }

    cv::imshow("Imagem Original", img);
    cv::imshow("Imagem Espelhada Verticalmente", mirrored_img);

    cout << "lucas " << endl;

    bool isSuccess = imwrite(dst_gramado, img); //write the image to a file as JPEG
    //bool isSuccess = imwrite("D:/MyImage.png", image); //write the image to a file as PNG
    if (isSuccess == false)
    {
        cout << "Failed to save the image" << endl;
        cin.get(); //wait for a key press
        return -1;
    }

    String windowName = "The Saved Image"; //Name of the window
    namedWindow(windowName); // Create a window
    imshow(windowName, img); // Show our image inside the created window.

    waitKey(0); // Wait for any keystroke in the window

    destroyWindow(windowName); //destroy the created window

    cv::waitKey(0);

    return 0;
}
