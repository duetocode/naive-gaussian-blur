#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdint.h>

#include "gaussian_blur.hpp"

cv::Mat readImage()
{
    // read and decode image file
    cv::Mat image = cv::imread("sample.jpg", cv::IMREAD_GRAYSCALE);
    std::cout << "Dims: " << image.dims << "\tStep: " << image.step << std::endl;
    std::cout << "Rows: " << image.rows << "\tCols: " << image.cols << "\tElements: " << image.elemSize() << std::endl;
    return image;
}

static const std::string WINDOW_NAME = "Preview";

int main()
{
    cv::Mat image = readImage();
    cv::Mat blurred(image.rows, image.cols, image.type());

    GaussianBlur<uint8_t>((uint8_t*)image.data, (uint8_t*)blurred.data, image.cols, image.rows);

    cv::imshow(WINDOW_NAME, image);
    cv::waitKey(0);
    cv::imshow(WINDOW_NAME, blurred);
    cv::waitKey(0);
    cv::destroyAllWindows();
} 