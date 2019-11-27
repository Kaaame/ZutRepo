//fprintf(fp,"P6\n # \n %d\n %d\n %d\n", X_MAX, Y_MAX, MAX_COLOR_VAL);

#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

// int kernel[] = 
// {
//     -1, -1, -1,
//     -1,  9, -1,
//     -1, -1, -1    
// };

unsigned int **read_int_file(char *fn, int *y_max, int *x_max, unsigned char *max_color_val)
{
    FILE *fp = fopen(fn, "rb");
    char file_extension[2];
    //unsigned char max_color_val;

    fscanf(fp,"%2s %d %d %hhd",
            (char *)(file_extension), y_max, x_max, max_color_val);

    printf("Read header!\n");
    printf("%s %d %d %d\n", file_extension, *y_max, *x_max, *max_color_val);

    unsigned int **input_arr = calloc(sizeof(unsigned int *), (*x_max));
    for (int i = 0; i < *x_max; i++)
    {
        input_arr[i] = calloc(sizeof(unsigned int), (*y_max));
    }

    for (int i = 0; i < *x_max; i++)
    {
        for (int j = 0; j < *y_max; j++)
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            //printf("r = %d\tg = %d\tb = %d\n", r, g, b);
            //seems like gbr is correct way to write it lul
            //endianess actually screwing it up?
            //presume 0x00ff eedd
            //            rr ggbb ----- reading from left to right

            //rr bbgg -- endianness obv, and save from right to left?
            //int val =  (((b << 16) | g << 8) | r);
            fread(&r, sizeof(unsigned char), 1, fp);
            fread(&g, sizeof(unsigned char), 1, fp);
            fread(&b, sizeof(unsigned char), 1, fp);

            input_arr[i][j] |= b & 0xff;
            input_arr[i][j] <<= 8;

            input_arr[i][j] |= g & 0xff;
            input_arr[i][j] <<= 8;

            input_arr[i][j] |= r & 0xff;
        }

    }

    return input_arr;
}

void i_convolution(unsigned int **in, unsigned int ***out,
                int y_max, int x_max, int *kernel, int kernel_size)
{
    //shared
    int kernel_sum = 0;

    //private
    int r, g, b, i, j, y_conv, x_conv, x_index, y_index, val;
    unsigned char rval, gval, bval;
    
    for(int i = 0; i < kernel_size; i++)
    {
        for(int j = 0; j < kernel_size; j++)
        {
            kernel_sum += kernel[i * kernel_size + j];
        }
    }

    printf("kernel sum = %d\n", kernel_sum);
    if (kernel_sum == 0)
    {
        kernel_sum = 1;
    }

    for (int i = 1; i < x_max - 1; i++)
    {
        for (int j = 1; j < y_max - 1; j++)
        {
            int r = 0;
            int g = 0;
            int b = 0;

            for (int y_conv = -1; y_conv <= 1; y_conv++)
            {
                for (int x_conv = -1; x_conv <= 1; x_conv++)
                {
                    y_index = i + y_conv;
                    x_index = j + x_conv;

                    rval = (unsigned char)(in[y_index][x_index] & 0xff);
                    gval = (unsigned char)((in[y_index][x_index] & 0xff00) >> 8);
                    bval = (unsigned char)((in[y_index][x_index] & 0xff0000) >> 16);

                    kernel_val = kernel[(x_conv + 1)*kernel_size + (y_conv + 1)];

                    r += (int)(rval * kernel_val);
                    g += (int)(gval * kernel_val);
                    b += (int)(bval * kernel_val);
                }
            }

            r /= kernel_sum;//median filtration
            g /= kernel_sum;//median filtration
            b /= kernel_sum;//median filtration
            // b = abs(b);

            if (r > 255) r = 255;
            else if(r < 0) r = 0;
            if (g > 255) g = 255;
            else if(g < 0) g = 0;
            if (b > 255) b = 255;
            else if(b < 0) b = 0;

            unsigned int val;
            val = 0;

            val |= b & 0xff;
            val <<= 8;

            val |= g & 0xff;
            val <<= 8;

            val |= r & 0xff;
            (*out)[i][j] = val;
            (*out)[i][j] = 0;

            (*out)[i][j] = val;
        }
    }
}

void save_int_file(char *fn, unsigned int **out, int y_max, int x_max, unsigned char max_color_val)
{
    FILE *fout = fopen (fn, "wb");
    fprintf(fout, "P6\n%d %d\n%d", y_max, x_max, max_color_val);
    //unsigned char nl = '\';
        // fwrite(&nl, 1, 1, fout);
        // fwrite(&nl, 1, 1, fout);
    //fwrite(&nl, 1, 1, fout);
    for (int i = 0; i < x_max; i++)
    {
        for (int j = 0; j < y_max; j++)
        {
            unsigned char r = out[i][j] & 0xff;
            unsigned char g = (out[i][j] & 0xff00) >> 8;
            unsigned char b = (out[i][j] & 0xff0000) >> 16;
            //printf("r = %d\tg = %d\tb = %d\n", r, g, b);
            //seems like gbr is correct way to write it lul
            //endianess actually screwing it up?
            //presume 0x00ff eedd
            //            rr ggbb ----- reading from left to right

            //rr bbgg -- endianness obv, and save from right to left?
            //int val = 0x0a414243;//rgb, howeever written it was 43 42
            //lendian_fwrite(&out[i][j], sizeof(unsigned int), 1, fout);
            //fwrite(&val, sizeof(unsigned int), 1, fout);

            if(i == 500 && j == 997)
            {
                
                printf("i = %d, j = %d\n", i, j);
                //printf("y_index = %d, x_index = %d\n", y_index, x_index);
                printf("r = %d\tg = %d\tb = %d\n", r, g, b);
                //printf("kernel val = %d\n", kernel[(y_conv + 1) * kernel_size + (x_conv + 1)]);
                printf("out[i][j] = %d\n", out[i][j]);
                printf("\n");
            }

            fwrite(&r, 1, 1, fout);
            fwrite(&g, 1, 1, fout);
            fwrite(&b, 1, 1, fout);
            // fwrite(&nl, 1, 1, fout);
        }
        
        // unsigned char nl = '\n';
        // fwrite(&nl, 1, 1, fout);
    }
    fprintf(fout, "\20");

}

void filter_img(char *fn_in, char *fn_out, int *kernel, int kernel_size)
{
    int y_max;
    int x_max;
    unsigned char max_color_val;

    unsigned int **in_arr = NULL;// = malloc(sizeof(rgb *) * y_max);

    in_arr = read_int_file(fn_in, &y_max, &x_max, &max_color_val);
    unsigned int **out_arr = calloc(sizeof(unsigned int *), x_max);
    
    for (int i = 0; i < x_max; i++)
    {
        out_arr[i] = calloc(sizeof(unsigned int), y_max);
    }
    
    for (int i = 0; i < x_max; i++)
    {
        for (int j = 0; j < y_max; j++)
        {
            out_arr[i][j] = in_arr[i][j];
        }
    }

    i_convolution(in_arr, &out_arr, y_max, x_max, kernel, 3);

    save_int_file(fn_out, out_arr, y_max, x_max, max_color_val);
    
    for (int i = 0; i < x_max; i++)
    {
        free(in_arr[i]);
        free(out_arr[i]);
    }
    free(in_arr);
    free(out_arr);
}

int main()
{
    int sharpen_kernel[] = 
    {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1    
    };
    
    int edge_kernel[] = 
    {
        0, 1, 0,
        1, -4, 1,
        0, 1, 0    
    };

    #pragma omp parallel num_threads(2)
    {
        filter_img("flowers.ppm", "flowers_out.ppm", sharpen_kernel, 3);
        filter_img("hongkong.ppm", "hongkong_out.ppm", edge_kernel, 3);
    }
}