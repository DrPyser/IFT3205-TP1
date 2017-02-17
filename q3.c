/*------------------------------------------------------*/
/* Prog    : q3.c                                       */
/* Auteur  :                                            */
/* Date    : 17/02/2017                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo1.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_IMG_IN  "Monrstein"
#define NAME_IMG_OUT1 "Monroe"
#define NAME_IMG_OUT2 "Einstein"

void CenterImg(float** spectre, float** out, int length, int width){
    float temp;
    for(int i=0; i < length; i++){
        for(int j=0;j < width/2; j++){
            if (i < length/2){
                temp = spectre[i][j];
                out[i][j] = spectre[i+length/2][j+width/2];
                out[i+length/2][j+width/2] = temp;
            }
            else {
                temp = spectre[i][j];
                out[i][j] = spectre[i-length/2][j+width/2];
                out[i-length/2][j+width/2] = temp;
            }
        }
    }
}

void copy(float** source, float** dest, int length, int width){
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            dest[i][j] = source[i][j];
        }
    }
}

void highFreqAmp(float** spectre, float** out, float coef, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            out[i][j] = log(1 + coef*spectre[i][j]);
        }
    }
}

void lowFreqAmp(float** spectre, float** out, float coef, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            out[i][j] = 255*exp(1/(coef*spectre[i][j] + 1));
        }
    }
}

void setToZero(float** mat, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            mat[i][j] = 0.0;
        }
    }
}


void squarein(float** mat, int radius, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            if(abs(length/2 - i) <= radius && abs(width/2 - j) <= radius){
                mat[i][j] = 1.0;
            } else {
                mat[i][j] = 0.0;
            }
        }
    }
}

void squareout(float** mat, int radius, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            if(abs(length/2 - i) <= radius && abs(width/2 - j) <= radius){
                mat[i][j] = 0.0;
            } else {
                mat[i][j] = 1.0;
            }
        }
    }
}

void circlein(float** mat, int radius, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            if(sqrt((length/2 - i)^2 + (width/2 - j)^2) <= radius){
                mat[i][j] = 1.0;
            } else {
                mat[i][j] = 0.0;
            }
        }
    }
}

void circleout(float** mat, int radius, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            if(sqrt((length/2 - i)^2 + (length/2 - j)^2) <= radius){
                mat[i][j] = 0.0;
            } else {
                mat[i][j] = 1.0;
            }
        }
    }
}


/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
{
    int i,j,k;
    int length,width;
    float** img1;
    float** MatriceImgR;
    float** MatriceImgI;
    float** MatriceImgR2;
    float** MatriceImgI2;
    float** MatriceImgM;
    float** MatriceImgMC;

    /*Allocation memoire pour la matrice image*/
    img1 = LoadImagePgm(NAME_IMG_IN,&length,&width);
    MatriceImgR=fmatrix_allocate_2d(length,width); 
    MatriceImgI=fmatrix_allocate_2d(length,width);
    MatriceImgR2=fmatrix_allocate_2d(length,width); 
    MatriceImgI2=fmatrix_allocate_2d(length,width);
    MatriceImgM=fmatrix_allocate_2d(length,width);
    MatriceImgMC=fmatrix_allocate_2d(length,width);
    /* MatriceImgLF=fmatrix_allocate_2d(length,width); */
    /* MatriceImgHF=fmatrix_allocate_2d(length,width); */
    
    
    /*Initialisation a zero de toutes les matrices */
    for(i=0;i<length;i++) 
        for(j=0;j<width;j++) 
        {
            MatriceImgR[i][j]=0.0;
            MatriceImgI[i][j]=0.0;
            MatriceImgR2[i][j]=0.0;
            MatriceImgI2[i][j]=0.0;
            MatriceImgM[i][j]=0.0;
            MatriceImgMC[i][j]=0.0;            
        }

    //img1 -> MatriceImgR
    copy(img1, MatriceImgR, length, width);

    /*FFT*/
    FFTDD(MatriceImgR,MatriceImgI,length,width);

    copy(MatriceImgR, MatriceImgR2, length, width);
    copy(MatriceImgI, MatriceImgI2, length, width);
    
    /*Module*/
    Mod(MatriceImgM,MatriceImgR,MatriceImgI,length,width);


    //3.2a
    
    //center
    CenterImg(MatriceImgM, MatriceImgMC, length, width);

    Recal(MatriceImgMC, length, width);

    Mult(MatriceImgMC, 100.0, length, width);

    /*Sauvegarde du module centré sous forme d'image pgm*/    
    SaveImagePgm("results/monrstein-spectre",MatriceImgMC,length,width);

    // On centre la partie réelle et imaginaire pour y travailler
    CenterImg(MatriceImgR, MatriceImgR, length, width);
    CenterImg(MatriceImgI, MatriceImgI, length, width);
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++) 
        {
            MatriceImgR[i][j] *= sqrtf((float)(pow(length/2-i,2.0) + pow(j-width/2,2)));
            MatriceImgI[i][j] *= sqrtf((float)(pow(length/2-i,2.0) + pow(j-width/2,2)));
        }
    }

    //On décentre
    CenterImg(MatriceImgR, MatriceImgR, length, width);
    CenterImg(MatriceImgI, MatriceImgI, length, width);
    
    IFFTDD(MatriceImgR, MatriceImgI, length, width);

    Recal(MatriceImgR, length, width);
    /*Sauvegarde de la transformée inverse*/    
    SaveImagePgm("results/monrstein-einstein",MatriceImgR,length,width);


    //3.2b

    // On centre la partie réelle et imaginaire pour y travailler
    CenterImg(MatriceImgR, MatriceImgR, length, width);
    CenterImg(MatriceImgI, MatriceImgI, length, width);
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++) 
        {
            MatriceImgR2[i][j] *= -sqrtf((float)(pow((length/2-i),2) + pow((j-width/2),2)));
            MatriceImgI2[i][j] *= -sqrtf((float)(pow((length/2-i),2) + pow((j-width/2),2)));
        }
    }

    //On décentre
    CenterImg(MatriceImgR2, MatriceImgR2, length, width);
    CenterImg(MatriceImgI2, MatriceImgI2, length, width);
    
    IFFTDD(MatriceImgR2, MatriceImgI2, length, width);
    
    Recal(MatriceImgR2, length, width);

    //Sauvegarde du module centré et log-amplifier sous forme d'image pgm
    SaveImagePgm("results/monrstein-monroe",MatriceImgR2,length,width);


    /*Liberation memoire pour les matrices*/
    free_fmatrix_2d(MatriceImgR);
    free_fmatrix_2d(MatriceImgI); 
    free_fmatrix_2d(MatriceImgR2);
    free_fmatrix_2d(MatriceImgI2); 
    free_fmatrix_2d(MatriceImgM);
    free_fmatrix_2d(MatriceImgMC);

    /*retour sans probleme*/ 
    printf("\n C'est fini ... \n\n");
    return 0;

} 	 



