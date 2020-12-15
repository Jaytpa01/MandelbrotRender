#include <stdio.h>
#include <stdlib.h>

int coulourMap(int iterCount);

int HSLtoRGB(float hue, float sat, float lum);


int R, G, B;
int main()
{
    FILE *mandelbrotRender;
    mandelbrotRender = fopen("C:\\Users\\Jay Parry\\Desktop\\test\\mandelbrotRender.ppm", "w");

    float zx = 0, zy = 0, zxm1, cx, cy;
    int iteration = 0, maxIteration = 4000;
    float xdim = 2056, ydim = 1440, H, S, L;


    fprintf(mandelbrotRender, "P3\n%f %f\n255\n", xdim, ydim);

    for(int y = 0; y < ydim; y++) {
        for(int x = 0; x < xdim; x++) {

            zx = 0;
            zy = 0;
            cy = (2.4 * (y / ydim)) - 1.2 ;
            cx = (3.5 * (x / xdim)) - 2.5;

            while((zx*zx + zy*zy < 4.0) && (iteration < maxIteration)) {
                zxm1 = (zx*zx) - (zy*zy) + cx;
                zy = 2*zx*zy + cy;
                zx = zxm1;
                iteration++;
            }

            if(iteration == maxIteration){
                R = 0;
                G = 0;
                B = 0;
            }else{
                H = 360.0 *( ((float)iteration) ) / maxIteration;
                S = 360.0 *( ((float)iteration) ) / maxIteration;
                L = 360.0 *( ((float)iteration) ) / maxIteration;
            
                HSLtoRGB(H, S, L);
            }




            //iteration = 0;

            //printf("%d %d", iteration, maxIteration);
            fprintf(mandelbrotRender, "%d %d %d\n", R, G, B);
            iteration = 0;
        }
    }
}





int HSLtoRGB(float hue, float sat, float lum) {
    float tempR, tempG, tempB;
    float temp1, temp2;

    if(lum < 0.5)
        temp1 = lum * (1.0 + sat);
    else
        temp1 = lum + sat - (lum*sat);

    temp2 = 2*lum - temp1;

    hue = hue/360;
    tempR = hue + 0.333;
    tempG = hue;
    tempB = hue - 0.333;

    if(6 * tempR < 1)
        tempR = temp2 + (temp1 - temp2) * 6 * tempR;
    else if(2 * tempR < 1)
        tempR = temp1;
    else if(3 * tempR < 2)
        tempR = temp2 + (temp1 - temp2) * (0.666 - tempR) * 6;
    else
        tempR = temp2;


    if(6 * tempG < 1)
        tempG = temp2 + (temp1 - temp2) * 6 * tempG;
    else if(2 * tempG < 1)
        tempG = temp1;
    else if(3 * tempG < 2)
        tempG = temp2 + (temp1 - temp2) * (0.666 - tempG) * 6;
    else
        tempG = temp2;


    if(6 * tempB < 1)
        tempB = temp2 + (temp1 - temp2) * 6 * tempB;
    else if(2 * tempR < 1)
        tempB = temp1;
    else if(3 * tempR < 2)
        tempB = temp2 + (temp1 - temp2) * (0.666 - tempB) * 6;
    else
        tempB = temp2;

    R = tempR * 255;
    G = tempG * 255;
    B = tempB * 255;

    return 0;
}