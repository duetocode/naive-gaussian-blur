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


static const float GAUSSIAN_KERNEL[3] = {0.27901f, 0.44198f, 0.27901f};
cv::Mat gaussianBlur(cv::Mat image)
{
    cv::Mat result(image.rows, image.cols, image.type());
    uchar *data = image.data;
    //cv::GaussianBlur(image, result, cv::Size(KERNEL_SIZE, KERNEL_SIZE), 0);
    const int width = image.cols, height = image.rows;
    
    // compute gaussian blur with sepratable kernel
    // For rows
    for (int i = 0; i < height; i++)
    {
        int head = i * width;
        int pixelIndex  = 0;

        // As the kernel is symetric, we only use the last weight
        // and cache the intermediate value
        float bufferA = 0.0f;
        float bufferB = GAUSSIAN_KERNEL[2] * data[head];
        float bufferC = GAUSSIAN_KERNEL[2] * data[head];

        for (int j = 0; j < width - 1; j++)
        {
            pixelIndex = head + j;

            // Reuse the value in the queue
            bufferA = bufferB;
            bufferB = bufferC;
            bufferC = GAUSSIAN_KERNEL[2] * data[pixelIndex + 1];

            result.data[pixelIndex] = (uchar)(
                bufferA +
                GAUSSIAN_KERNEL[1] * data[pixelIndex] + 
                bufferC
            );
        }

        result.data[head + width - 1] = (uchar)(
            bufferB +
            GAUSSIAN_KERNEL[1] * data[pixelIndex] + 
            bufferC
        );
    }
    // For columns
    for (int i = 0; i < width; i++)
    {
        int head = i;
        int pixelIndex  = 0;

        float bufferA = 0.0f;
        float bufferB = GAUSSIAN_KERNEL[2] * data[head];
        float bufferC = GAUSSIAN_KERNEL[2] * data[head];

        for (int j = 0; j < height - 1; j++)
        {
            pixelIndex = head + j * width;

            bufferA = bufferB;
            bufferB = bufferC;
            bufferC = GAUSSIAN_KERNEL[2] * data[pixelIndex + width];

            result.data[pixelIndex] = (uchar)(
                bufferA +
                GAUSSIAN_KERNEL[1] * data[pixelIndex] + 
                bufferC
            );
        }

        pixelIndex += width;
        result.data[head + width - 1] = (uchar)(
            bufferB +
            GAUSSIAN_KERNEL[1] * data[pixelIndex] + 
            bufferC
        );
    }
    return result;
}

static const std::string WINDOW_NAME = "Preview";

int main()
{
    cv::Mat image = readImage();
    //cv::Mat blurred = gaussianBlur(image);
    cv::Mat blurred(image.rows, image.cols, image.type());
    GaussianBlur((uint8_t*)image.data, (uint8_t*)blurred.data, image.cols, image.rows);

    cv::imshow(WINDOW_NAME, image);
    cv::waitKey(0);
    cv::imshow(WINDOW_NAME, blurred);
    cv::waitKey(0);
    cv::destroyAllWindows();
} 