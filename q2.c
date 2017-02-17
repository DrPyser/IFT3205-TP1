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
#define NAME_IMG_IN  "photograph"

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

/* void threshold() */

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
    float** MatriceImgRa;
    float** MatriceImgIa;
    float** MatriceImgRb;
    float** MatriceImgIb;
    float** MatriceImgRc;
    float** MatriceImgIc;
    float** MatriceImgRd;
    float** MatriceImgId;
    float** MatriceImgRe;
    float** MatriceImgIe;
    float** MatriceImgM;
    float** MatriceImgMC;//pour affichage du spectre centré

    /*Allocation memoire pour la matrice image*/
    img1 = LoadImagePgm(NAME_IMG_IN,&length,&width);
    MatriceImgR=fmatrix_allocate_2d(length,width); 
    MatriceImgI=fmatrix_allocate_2d(length,width);
    MatriceImgRa=fmatrix_allocate_2d(length,width); 
    MatriceImgIa=fmatrix_allocate_2d(length,width);
    MatriceImgRb=fmatrix_allocate_2d(length,width); 
    MatriceImgIb=fmatrix_allocate_2d(length,width);
    MatriceImgRc=fmatrix_allocate_2d(length,width); 
    MatriceImgIc=fmatrix_allocate_2d(length,width);
    MatriceImgRd=fmatrix_allocate_2d(length,width); 
    MatriceImgId=fmatrix_allocate_2d(length,width);
    MatriceImgRe=fmatrix_allocate_2d(length,width); 
    MatriceImgIe=fmatrix_allocate_2d(length,width);
    MatriceImgM=fmatrix_allocate_2d(length,width);
    MatriceImgMC=fmatrix_allocate_2d(length,width);
    
    
    /*Initialisation a zero de toutes les matrices */
    for(i=0;i<length;i++) 
        for(j=0;j<width;j++) 
        {
            MatriceImgR[i][j]=0.0;
            MatriceImgI[i][j]=0.0;
            MatriceImgM[i][j]=0.0;
            MatriceImgMC[i][j]=0.0;
            MatriceImgRa[i][j]=0.0;
            MatriceImgIa[i][j]=0.0;
            MatriceImgRb[i][j]=0.0;
            MatriceImgIb[i][j]=0.0;
            MatriceImgRc[i][j]=0.0;
            MatriceImgIc[i][j]=0.0;
            MatriceImgRd[i][j]=0.0;
            MatriceImgId[i][j]=0.0;
            MatriceImgRe[i][j]=0.0;
            MatriceImgIe[i][j]=0.0;
        }

    //img1 -> MatriceImgR
    copy(img1, MatriceImgR, length, width);

    /*FFT*/
    FFTDD(MatriceImgR,MatriceImgI,length,width);

    /*Module*/
    Mod(MatriceImgM,MatriceImgR,MatriceImgI,length,width);

    //center
    CenterImg(MatriceImgM, MatriceImgMC, length, width);

    /* //recal vers 0-255(pas de négatif) */
    Recal(MatriceImgMC,length,width);

    Mult(MatriceImgMC, 100.0, length, width);

    /*Sauvegarde du module centré sous forme d'image pgm*/    
    SaveImagePgm("results/photograph-spectre",MatriceImgMC,length,width);

    //on centre le réel et l'imaginaire pour les manips
    CenterImg(MatriceImgR, MatriceImgRa, length, width);
    CenterImg(MatriceImgI, MatriceImgIa, length, width);


    //on copie le réel et img. centré dans les autres matrices
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++) 
        {
            MatriceImgRb[i][j] = MatriceImgRa[i][j];
            MatriceImgIb[i][j] = MatriceImgIa[i][j];
            MatriceImgRc[i][j] = MatriceImgRa[i][j];
            MatriceImgIc[i][j] = MatriceImgIa[i][j];
            MatriceImgRd[i][j] = MatriceImgRa[i][j];
            MatriceImgId[i][j] = MatriceImgIa[i][j];
            MatriceImgRe[i][j] = MatriceImgRa[i][j];
            MatriceImgIe[i][j] = MatriceImgIa[i][j];
        }
    }
    
    // 2.a)
    
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++) 
        {
            if((length/2 - i) == (j - width/2) && abs(length/2 - i) <= 30){
                MatriceImgRa[i][j] = 0.0;
                MatriceImgIa[i][j] = 0.0;
            }
        }
    }
    
    // on décentre les matrices
    CenterImg(MatriceImgRa, MatriceImgRa, length, width);
    CenterImg(MatriceImgIa, MatriceImgIa, length, width);
    
    IFFTDD(MatriceImgRa, MatriceImgIa, length, width);

    Recal(MatriceImgRa, length, width);
    
    /*Sauvegarde de la transformée inverse*/    
    SaveImagePgm("results/photograph-a",MatriceImgRa,length,width);

    // 2.b)
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++) 
        {
            if(sqrtf((float)(pow(length/2-i,2) + pow(j-width/2,2))) > 7){
                MatriceImgRb[i][j] = 0.0;
                MatriceImgIb[i][j] = 0.0;
            }
        }
    }

    // on décentre les matrices
    CenterImg(MatriceImgRb, MatriceImgRb, length, width);
    CenterImg(MatriceImgIb, MatriceImgIb, length, width);
    
    IFFTDD(MatriceImgRb, MatriceImgIb, length, width);

    Recal(MatriceImgRb, length, width);
    
    /*Sauvegarde de la transformée inverse*/    
    SaveImagePgm("results/photograph-b",MatriceImgRb,length,width);

    // 2.c)
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++) 
        {
            MatriceImgRc[i][j] *= sqrtf((float)(pow(length/2-i,2.0) + pow(j-width/2,2)));
            MatriceImgIc[i][j] *= sqrtf((float)(pow(length/2-i,2.0) + pow(j-width/2,2)));
        }
    }

    // on décentre les matrices
    CenterImg(MatriceImgRc, MatriceImgRc, length, width);
    CenterImg(MatriceImgIc, MatriceImgIc, length, width);
    
    IFFTDD(MatriceImgRc, MatriceImgIc, length, width);

    Recal(MatriceImgRc, length, width);
    
    /*Sauvegarde de la transformée inverse*/    
    SaveImagePgm("results/photograph-c",MatriceImgRc,length,width);

    //2.d)
    for(i=0;i<length;i++) {
        for(j=0;j<width;j++)
        {
            if(abs(length/2 - i) >= 10){
                MatriceImgRd[i][j] = 0.0;
                MatriceImgId[i][j] = 0.0;
            }
        }
    }

    // on décentre les matrices
    CenterImg(MatriceImgRd, MatriceImgRd, length, width);
    CenterImg(MatriceImgId, MatriceImgId, length, width);
    
    IFFTDD(MatriceImgRd, MatriceImgId, length, width);

    Recal(MatriceImgRd, length, width);
    
    /*Sauvegarde de la transformée inverse*/
    SaveImagePgm("results/photograph-d",MatriceImgRd,length,width);

    //2.e)

    for(i=0;i<length;i++) {
        for(j=0;j<width;j++)
        {
            if(abs(j-width/2) >= 10){
                MatriceImgRe[i][j] = 0.0;
                MatriceImgIe[i][j] = 0.0;
            }
            
        }
    }

    // on décentre les matrices
    CenterImg(MatriceImgRe, MatriceImgRe, length, width);
    CenterImg(MatriceImgIe, MatriceImgIe, length, width);
    
    IFFTDD(MatriceImgRe, MatriceImgIe, length, width);

    Recal(MatriceImgRd, length, width);
    
    /*Sauvegarde de la transformée inverse*/
    SaveImagePgm("results/photograph-e",MatriceImgRe,length,width);    
    
    /*Liberation memoire pour les matrices*/
    free_fmatrix_2d(MatriceImgR);
    free_fmatrix_2d(MatriceImgI); 
    free_fmatrix_2d(MatriceImgM);    
    free_fmatrix_2d(MatriceImgMC);
    free_fmatrix_2d(MatriceImgRa);
    free_fmatrix_2d(MatriceImgIa);
    free_fmatrix_2d(MatriceImgRb);
    free_fmatrix_2d(MatriceImgIb);
    free_fmatrix_2d(MatriceImgRc);
    free_fmatrix_2d(MatriceImgIc);
    free_fmatrix_2d(MatriceImgRd);
    free_fmatrix_2d(MatriceImgId);
    free_fmatrix_2d(MatriceImgRe);
    free_fmatrix_2d(MatriceImgIe);

    /*retour sans probleme*/ 
    printf("\n C'est fini ... \n\n");
    return 0;

} 	 


