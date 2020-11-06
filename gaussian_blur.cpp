#include <iostream>

#include "gaussian_blur.hpp"

// Naive gaussion implementation using static kernel
static const float GAUSSIAN_KERNEL[3] = {0.27901f, 0.44198f, 0.27901f};

void GaussianBlur(uint8_t *src, uint8_t *dest, int width, int height)
{
    // compute gaussian blur with sepratable kernel
    // For rows
    for (int i = 0; i < height; i++)
    {
        int head = i * width;
        int pixelIndex  = 0;

        // As the kernel is symetric, we only use the last weight
        // and cache the intermediate value
        float bufferA = 0.0f;
        float bufferB = GAUSSIAN_KERNEL[2] * src[head];
        float bufferC = bufferB;

        for (int j = 0; j < width - 1; j++)
        {
            pixelIndex = head + j;

            // Reuse the value in the queue
            bufferA = bufferB;
            bufferB = bufferC;
            bufferC = GAUSSIAN_KERNEL[2] * src[pixelIndex + 1];

            dest[pixelIndex] = (uint8_t)(
                bufferA +
                GAUSSIAN_KERNEL[1] * src[pixelIndex] + 
                bufferC
            );
        }

        pixelIndex += 1;
        dest[pixelIndex] = (uint8_t)(
            bufferB +
            GAUSSIAN_KERNEL[1] * src[pixelIndex] + 
            bufferC
        );
    }
    // For columns
    for (int i = 0; i < width; i++)
    {
        int head = i;
        int pixelIndex  = 0;

        float bufferA = 0.0f;
        float bufferB = GAUSSIAN_KERNEL[2] * src[head];
        float bufferC = bufferB;

        for (int j = 0; j < height - 1; j++)
        {
            pixelIndex = head + j * width;

            bufferA = bufferB;
            bufferB = bufferC;
            bufferC = GAUSSIAN_KERNEL[2] * src[pixelIndex + width];

            dest[pixelIndex] = (uint8_t)(
                bufferA +
                GAUSSIAN_KERNEL[1] * src[pixelIndex] + 
                bufferC
            );
        }

        pixelIndex += width;
        dest[pixelIndex] = (uint8_t)(
            bufferB +
            GAUSSIAN_KERNEL[1] * src[pixelIndex] + 
            bufferC
        );
    }
}