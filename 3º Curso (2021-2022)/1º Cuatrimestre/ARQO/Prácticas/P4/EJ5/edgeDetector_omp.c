#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#define MEDIAN 0
#define GAUSSIAN 1
#define GAUSSIAN_K 1.0

#define TYPE_FILTER GAUSSIAN

float* gaussian_kernel(int ksize, double sigma) {
    float* gauss = malloc(ksize*ksize*sizeof(float));
    double sum = 0;
    int i, j;
    
    for (j = 0; j < ksize; j++) {
        for (i = 0; i < ksize; i++) {
            double x = i - (ksize - 1) / 2.0;
            double y = j - (ksize - 1) / 2.0;
            gauss[i + ksize*j] = (GAUSSIAN_K * exp(((pow(x, 2) + pow(y, 2)) / ((2 * pow(sigma, 2)))) * (-1)));
            sum += gauss[i + ksize*j];
        }
    }

    for (i = 0; i < ksize; i++) {
        for (j = 0; j < ksize; j++) {
            gauss[i + ksize*j] /= sum;
        }
    }

    return gauss;
}

static inline void getRGB(uint8_t *im, int width, int height, int nchannels, int x, int y, int *r, int *g, int *b)
{

    unsigned char *offset = im + (x + width * y) * nchannels;
    *r = offset[0];
    *g = offset[1];
    *b = offset[2];
}

int comparate(const void *a, const void *b)
{
    return (*((uint8_t *)a)) - (*((uint8_t *)b));
}

int main(int nargs, char **argv)
{
    int width, height, nchannels;
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
        uint8_t *rgb_image = stbi_load(argv[file_i], &width, &height, &nchannels, 4);
        if (!rgb_image)
        {
            perror("Image could not be opened");
        }

        /****** Allocating memory ******/
        // - RGB2Grey
        uint8_t *grey_image = malloc(width * height);
        if (!grey_image)
        {
            perror("Could not allocate memory");
        }

        // - Sobel
        int width_edges = width - 2;
        int height_edges = height - 2;
        uint8_t *edges = malloc(width_edges * height_edges);
        if (!edges)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        // - Denoising
        int radius = 2;
        int width_denoised = width_edges - radius;
        int height_denoised = height_edges - radius;
        uint8_t *edges_denoised = malloc(width_denoised * height_denoised);
        if (!edges_denoised)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        uint8_t *array = malloc((2 * radius + 1) * (2 * radius + 1));
        if (!array)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

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
        asprintf(&grey_image_filename, "%s_grey.jpg", argv[file_i]);
        if (!grey_image_filename)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        char *grad_image_filename = 0;
        asprintf(&grad_image_filename, "%s_grad.jpg", argv[file_i]);
        if (!grad_image_filename)
        {
            perror("Could not allocate memory");
            exit(-1);
        }
    

        char *denoised_image_filename = 0;
        asprintf(&denoised_image_filename, "%s_grad_denoised.jpg", argv[file_i]);
        if (!denoised_image_filename)
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

        gettimeofday(&ini,NULL);
        // RGB to grey scale
        int r, g, b;
        //cambiamos el orden de height widht
        for (int j = 0; j < height; j++) 
        {
            #pragma omp parallel for firstprivate(width, r, g, b) shared(grey_image) 
            for (int i = 0; i < width; i++)
            {
                getRGB(rgb_image, width, height, 4, i, j, &r, &g, &b);
                grey_image[j * width + i] = (int)(0.2989 * r + 0.5870 * g + 0.1140 * b);
            }
        }
        #ifdef WRITEONTHEGO
        stbi_write_jpg(grey_image_filename, width, height, 1, grey_image, 10);
        free(rgb_image);
        #endif

        // Sobel edge detection
#define PIXEL_GREY(x, y) (grey_image[(x) + (y)*width])
        for (int j = 1; j < height - 1; j++)    
        {
            #pragma omp parallel for firstprivate(width, width_edges) shared(edges) 
            for (int i = 1; i < width - 1; i++)
            {
                int x = i - 1;
                int y = j - 1;
                float a = (PIXEL_GREY(i - 1, j - 1) + PIXEL_GREY(i - 1, j) * 2 + PIXEL_GREY(i - 1, j + 1) -
                           (PIXEL_GREY(i + 1, j - 1) + PIXEL_GREY(i + 1, j) * 2 + PIXEL_GREY(i + 1, j + 1)));
                float b = (PIXEL_GREY(i - 1, j - 1) + PIXEL_GREY(i, j - 1) * 2 + PIXEL_GREY(i + 1, j - 1) -
                           (PIXEL_GREY(i - 1, j + 1) + PIXEL_GREY(i - 1, j + 1) * 2 + PIXEL_GREY(i - 1, j + 1)));

                edges[x + y * width_edges] = sqrt(a * a + b * b);
            }
        }
        
        #ifdef WRITEONTHEGO
        stbi_write_jpg(grad_image_filename, width - 2, height - 2, 1, edges, 10);
        free(grey_image);
        #endif

        // Denoising
#define PIXEL_EDGES(x, y) (edges[(x) + (y)*width_edges]);

        int x = 0, y = 0, k = 0;
        // Use salt&pepper filter
        if (TYPE_FILTER == MEDIAN)
        {
            printf("[info] Using median denoising...\n");
            for (int j = radius; j < height_edges - radius; j++)
            {
                #pragma omp parallel for firstprivate(width_edges, array) shared(edges_denoised) 
                for (int i = radius; i < width_edges - radius; i++)
                {
                    y = j - radius;
                    x = i - radius;
                    k = 0;

                    for (int p1 = i - radius; p1 <= i + radius; p1++)
                    {
                        for (int p2 = j - radius; p2 <= j + radius; p2++)
                        {
                            array[k++] = PIXEL_EDGES(p1, p2);
                        }
                    }
                    qsort(array, (2 * radius + 1) * (2 * radius + 1), 1, comparate);
                    edges_denoised[x + y * width_denoised] = array[(2 * radius + 1) * (2 * radius + 1) / 2]>50?255:0;
                }
            }
        // More classic gaussian filter
        } else {
            printf("[info] Using gaussian denoising...\n");
            float* kernel = gaussian_kernel(2*radius+1, 1.0);
            double sum = 0;
            for (int j = radius; j < height_edges - radius; j++)
            {
                #pragma omp parallel for firstprivate(width_edges, sum, kernel) shared(edges_denoised)
                for (int i = radius; i < width_edges - radius; i++)
                {
                    x = i - radius;
                    y = j - radius;
                    sum = 0;
                    for (int p1 = 0; p1 <= 2 * radius; p1++)
                    {
                        for (int p2 = 0; p2 <= 2 * radius; p2++)
                        {
                            if (kernel[p1+p2*(2*radius+1)]>1) 
                                printf("%f, %d, %d\n", kernel[p1+p2*(2*radius+1)], p1, p2);
                            sum += kernel[p1+p2*(2*radius+1)] * PIXEL_EDGES(i-radius+p1, j-radius+p2);
                        }
                    }
                    edges_denoised[x + y * width_denoised] = sum>50?255:0;
                }
            }
        }

        #ifdef WRITEONTHEGO
        printf("[info] Writing final result.\n");
        stbi_write_jpg(denoised_image_filename, width_denoised, height_denoised, 1, edges_denoised, 10);
        free(edges_denoised);
        free(edges);
        #endif
        gettimeofday(&fin,NULL);

	    printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
        #ifndef WRITEONTHEGO
        stbi_write_jpg(grey_image_filename, width, height, 1, grey_image, 10);
        stbi_write_jpg(grad_image_filename, width_edges, height_edges, 1, edges, 10);
        stbi_write_jpg(denoised_image_filename, width_denoised, height_denoised, 1, edges_denoised, 10);
        free(rgb_image);
        free(grey_image);
        free(edges);
        free(edges_denoised);
        #endif
        free(grey_image_filename);
        free(grad_image_filename);
        free(denoised_image_filename);
    }
}
