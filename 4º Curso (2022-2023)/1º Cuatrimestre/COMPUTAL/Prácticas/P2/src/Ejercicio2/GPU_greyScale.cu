#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define NCHANNELS 4

__global__ void changeRGB_toGrey(uint8_t *im, int width, int height, int nchannels, uint8_t *grey_image)
{
    unsigned char *offset = im + (threadIdx.x + blockDim.x * blockIdx.x) * nchannels;
    int r = offset[0];
    int g = offset[1];
    int b = offset[2];
    grey_image[threadIdx.x + blockDim.x * blockIdx.x] = (int)(0.2989 * r + 0.5870 * g + 0.1140 * b);
}

int main(int nargs, char **argv)
{
    int width, height, nchannels;
    uint8_t *d_rgb_image, *d_grey_image;
    struct timeval fin,ini;

    if (nargs < 2)
    {
        printf("Usage: %s <image1> [<image2> ...]\n", argv[0]);
    }
    // For each image
    // Bucle 0
    for (int file_i = 1; file_i < nargs; file_i++)
    {
        printf("[info] Processing %s\n", argv[file_i]);
        /****** Reading file ******/
        uint8_t *rgb_image = stbi_load(argv[file_i], &width, &height, &nchannels, NCHANNELS);
        if (!rgb_image)
        {
            perror("Image could not be opened");
        }

        /****** Allocating memory ******/
        // - RGB2Grey
        uint8_t *grey_image = (uint8_t *)malloc(width * height);
        if (!grey_image)
        {
            perror("Could not allocate memory");
        }

        // Alloc space for device copy
        cudaMalloc((uint8_t **)&d_rgb_image, width*height*NCHANNELS);
        cudaMalloc((uint8_t **)&d_grey_image, width*height);

        // Copy to device
        cudaMemcpy(d_rgb_image, rgb_image, width*height*NCHANNELS, cudaMemcpyHostToDevice);

        // - Filenames 
        for (int i = strlen(argv[file_i]) - 1; i >= 0; i--)
        {
            if (argv[file_i][i] == '.')
            {
                argv[file_i][i] = 0;
                break;
            }
        }

        char *grey_image_filename = 0;
        asprintf(&grey_image_filename, "%s_GPUgrey.jpg", argv[file_i]);
        if (!grey_image_filename)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        /****** Computations ******/
        printf("[info] %s: width=%d, height=%d, nchannels=%d\n", argv[file_i], width, height, nchannels);

        if (nchannels != 3 && nchannels != 4)
        {
            printf("[error] Num of channels=%d not supported. Only three (RGB), four (RGBA) are supported.\n", nchannels);
            continue;
        }

        // RGB to grey scale
        gettimeofday(&ini,NULL);
        changeRGB_toGrey<<<width,height>>>(d_rgb_image, width, height, NCHANNELS, d_grey_image);
        gettimeofday(&fin,NULL);

        cudaMemcpy(grey_image, d_grey_image, width*height, cudaMemcpyDeviceToHost);

        stbi_write_jpg(grey_image_filename, width, height, 1, grey_image, 10);
        free(rgb_image);

	      printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
        free(grey_image_filename);
    }
}
