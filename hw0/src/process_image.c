#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

int clip_image(int v, int min, int max){
    assert(min <= max);
    if (v < min){
        v = min;
    }
    if (v >= max){
        v = max - 1;
    }
    return v;
}

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    c = clip_image(c, 0, im.c);
    y = clip_image(y, 0, im.h);
    x = clip_image(x, 0, im.w);
    int pixel_idx = (c*im.h*im.w) + (y*im.w) + x;
    float pixel_val = im.data[pixel_idx];
    return pixel_val;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    int pixel_idx = (c*im.h*im.w) + (y*im.w) + x;
    im.data[pixel_idx] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
//     int i, j, k;

//     for (i = 0; i <= im.c; ++i)
//     {
//         for (j = 0; j <= im.w; ++j)
//         {
//             for (k = 0; k <= im.h; ++k)
//             {
//                 // Method 1
//                 // set_pixel(copy, j, k, i, get_pixel(im, j, k, i));
//                 // Method 2
//                 int pixel_idx = (i*im.h*im.c) + (k*im.w) + j;
//                 copy.data[pixel_idx] = im.data[pixel_idx];

//             }
//         }
//     }
    // Method 3
    memcpy(copy.data, im.data, (im.c*im.h*im.w*4));
    // memcpy(copy.data, im.data, sizeof(im.data));
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    int i, j;
    float red, green, blue;
    for (i = 0; i < im.w; ++i)
    {
        for (j = 0; j < im.h; ++j)
        {
            red = get_pixel(im, i, j, 0);
            green = get_pixel(im, i, j, 1);
            blue = get_pixel(im, i, j, 2);
            float gray_val = 0.299*red + 0.587*green + 0.114*blue;
            set_pixel(gray, i, j, 0, gray_val);
        }
    }   
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    int i, j;
    for (i = 0; i < im.w; ++i)
    {
        for (j = 0; j < im.h; ++j)
        {
            float new_val = get_pixel(im, i, j, c) + v;
            set_pixel(im, i, j, c, new_val);
        }
    }
}

void clamp_image(image im)
{
    // TODO Fill this in
    int i, j, k;
    for (i = 0; i < im.c; ++i){
        for (j = 0; j < im.w; ++j){
            for (k = 0; k < im.h; ++k){
                if (get_pixel(im, j, k, i) < 0){
                    set_pixel(im, j, k, i, 0);
                } else if (get_pixel(im, j, k, i) > 1){
                    set_pixel(im, j, k, i, 1);
                }
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    int i, j;
    float C=0, S, H_dash=0, H;
    for (i = 0; i < im.w; ++i){
        for (j = 0; j < im.h; ++j){
            float r = get_pixel(im, i, j, 0);
            float g = get_pixel(im, i, j, 1);
            float b = get_pixel(im, i, j, 2);
            // Compute Value
            float V = three_way_max(r, g, b); // Value
            // Compute saturation
            if (V == 0){
                S = 0; // Saturation
            } else{
            float m = three_way_min(r, g, b);
            C = V - m;
            S = C/V; // Saturation
            }
            // Compute Hue
            H_dash = 0; 
            if (C == 0){
                H = 0; //Hue
            } else if (V == r){
                H_dash = (g - b)/C;
            }else if (V == g){
                H_dash = ((b - r)/C) + 2;
            } else if (V == b){
                H_dash = ((r - g)/C) + 4;
            }
            if(H_dash < 0){
                H = (H_dash/6) + 1; // Hue
            } else{
                H = (H_dash/6); // Hue
            }
            set_pixel(im, i, j, 0, H);
            set_pixel(im, i, j, 1, S);
            set_pixel(im, i, j, 2, V);
        }
    }   
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
