/*------------------------------------------------------*/
/* Prog    : Tp1_IFT3205-1-1.c                          */
/* Auteur  :                                            */
/* Date    : 18/05/2010                                 */
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
#define NAME_VISUALISER "display "
#define NAME_IMG_IN  "D1r"
#define NAME_IMG_OUT image-Tp1_IFT3205-1-1

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/
void CenterImg(float** spectre, float** out, int length, int width){
//    float temp;
    for(int i=0; i < length; i++){
        for(int j=0;j < width/2; j++){
            if (i < length/2){
                //temp = spectre[i][j];
                out[i][j] = spectre[i+length/2][j+width/2];
                out[i+length/2][j+width/2] = spectre[i][j];
            }
            else {
                //temp = spectre[i][j];
                out[i][j] = spectre[i-length/2][j+width/2];
                out[i-length/2][j+width/2] = spectre[i][j];
            }
        }
    }
}

void copy(float** source, float** copy, int length, int width){
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            copy[i][j] = source[i][j];
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

void setToZero(float** mat, int length, int width){
    for (int i = 0;i < length;i++){
        for (int j = 0;j < width;j++){
            mat[i][j] = 0.0;
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
    char BufSystVisuImg[100];
    float** img1;
    float** img2;
    float** img3;
    float** MatriceImgR;
    float** MatriceImgI;
    float** MatriceImgM;
    float** MatriceImgC;
    float** MatriceImgLog;

    /*Allocation memoire pour la matrice image*/
    img1 = LoadImagePgm("D1r",&length,&width);
    img2 = LoadImagePgm("D11r",&length,&width);
    img3 = LoadImagePgm("D46r",&length,&width);
    MatriceImgR=fmatrix_allocate_2d(length,width); 
    MatriceImgI=fmatrix_allocate_2d(length,width);
    MatriceImgM=fmatrix_allocate_2d(length,width);
    MatriceImgLog=fmatrix_allocate_2d(length,width);
    MatriceImgC=fmatrix_allocate_2d(length,width);
    
    
    /*Initialisation a zero de toutes les matrices */
    for(i=0;i<length;i++) 
        for(j=0;j<width;j++) 
        {
            MatriceImgR[i][j]=0.0;
            MatriceImgI[i][j]=0.0;
            MatriceImgM[i][j]=0.0;
            MatriceImgC[i][j]=0.0;
            MatriceImgLog[i][j]=0.0;
        }

    //première image
    copy(img1, MatriceImgR, length, width);
    
    /*FFT*/
    FFTDD(MatriceImgR,MatriceImgI,length,width);

    /*Module*/
    Mod(MatriceImgM,MatriceImgR,MatriceImgI,length,width);

    //recal vers 0-255(pas de négatif)
    Recal(MatriceImgM,length,width);

    //center
    CenterImg(MatriceImgM, MatriceImgC, length, width);
    
    //log
    highFreqAmp(MatriceImgC, MatriceImgLog, 10, length, width);

    Recal(MatriceImgLog, length, width);

    /*Pour visu*/
    Mult(MatriceImgM,100.0,length,width);

    /*Sauvegarde du module sous forme d'image pgm*/
    SaveImagePgm("results/image-1.1",MatriceImgM,length,width);

    Mult(MatriceImgC, 100.0, length, width);
    /*Sauvegarde du module centré sous forme d'image pgm*/    
    SaveImagePgm("results/image-1.2",MatriceImgC,length,width);

    //Sauvegarde du module centré et log-amplifier sous forme d'image pgm
    SaveImagePgm("results/image-1.3",MatriceImgLog,length,width);

    //img2

    copy(img2, MatriceImgR, length, width);
    setToZero(MatriceImgI, length, width);
    setToZero(MatriceImgM, length, width);
    
    FFTDD(MatriceImgR,MatriceImgI,length,width);
    Mod(MatriceImgM,MatriceImgR,MatriceImgI,length,width);
    Recal(MatriceImgM,length,width);
    CenterImg(MatriceImgM, MatriceImgC, length, width);
    highFreqAmp(MatriceImgC, MatriceImgLog, 10, length, width);
    Recal(MatriceImgLog, length, width);
    SaveImagePgm("results/image-1.4-D11r",MatriceImgLog,length,width);

    //img3

    copy(img3, MatriceImgR, length, width);
    setToZero(MatriceImgI, length, width);
    setToZero(MatriceImgM, length, width);
    
    FFTDD(MatriceImgR,MatriceImgI,length,width);
    Mod(MatriceImgM,MatriceImgR,MatriceImgI,length,width);
    Recal(MatriceImgM,length,width);
    CenterImg(MatriceImgM, MatriceImgC, length, width);
    highFreqAmp(MatriceImgC, MatriceImgLog, 10, length, width);
    Recal(MatriceImgLog, length, width);
    SaveImagePgm("results/image-1.4-D46r",MatriceImgLog,length,width);

    
    /*Liberation memoire pour les matrices*/
    free_fmatrix_2d(MatriceImgR);
    free_fmatrix_2d(MatriceImgI); 
    free_fmatrix_2d(MatriceImgM);    

    /*Commande systeme: visualisation de Ingout.pgm*/
    /* strcpy(BufSystVisuImg,NAME_VISUALISER); */
    /* strcat(BufSystVisuImg,NAME_IMG_OUT); */
    /* strcat(BufSystVisuImg,".pgm&"); */
    /* printf(" %s",BufSystVisuImg); */
    /* system(BufSystVisuImg); */

    /*retour sans probleme*/ 
    printf("\n C'est fini ... \n\n");
    return 0;

} 	 



