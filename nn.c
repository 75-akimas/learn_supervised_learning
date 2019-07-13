//
// Created by akihide.sato on 2019/07/12.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define INPUT 64
#define CENTER 50
#define OUTPUT 20

//シグモイド関数のプロトタイプ宣言
double sigmoid(double x);

int main(void){

    //ファイル読み込み

    char fname[64];
    char fnamet[64];
    char data_num[64];

    char str[INPUT];
    char strt[INPUT];
    FILE *fp, *fpt;
    int mesh[20][8][8] = {0};
    int mesht[20][8][8] = {0};

    for(int i = 0; i<1; i++){
        sprintf(data_num,"%02d",i);
        sprintf(fname,"./Data/hira0_%sL.dat",data_num);
        sprintf(fnamet,"./Data/hira0_%sT.dat",data_num);

        fp = fopen(fname, "r");
        fpt = fopen(fnamet, "r");

        if(fp == NULL) {
            printf("%s file not open!\n", fname);
            return -1;
        } else {
            printf("%s file opened!\n", fname);
        }

        for(int mesh_itr = 0; fgets(str,66,fp) != NULL && fgets(strt,66,fpt) != NULL; mesh_itr++){
            //printf("%s",str);
            for(int j = 0; j<64; j++){
//                printf("%d %d \n", mesh_itr%64/8, j/8);
                if(str[j] == '1'){
                    mesh[i][mesh_itr%64/8][j/8]++;
                }
                if(strt[j] == '1'){
                    mesht[i][mesh_itr%64/8][j/8]++;
                }
            }
            //いちもじおわり
            if(mesh_itr == 64){
                for(int j=0; j<8;j++){
                    for(int k=0; k<8; k++){
                        printf("%02d ", mesh[i][j][k]);
                    }
                    printf(" ||| ");
                    for(int k=0; k<8; k++){
                        printf("%02d ", mesht[i][j][k]);
                        mesh[i][j][k] = 0, mesht[i][j][k] = 0;
                    }
                    puts("");
                }
                puts("");
            }
        }
        return 0;
    }



    fclose(fp);


    //層
    double Input[INPUT];
    double center[CENTER];
    double Output[OUTPUT];
    //重み関数
    double In_Ce[INPUT][CENTER];
    double Ce_Ou[CENTER][OUTPUT];
    //重み関数をランダムな値で初期化
    for(int i=0; i<INPUT;i++){
        for(int j=0; j<CENTER;j++){
            srand(rand());
            In_Ce[i][j] = (double)rand()/RAND_MAX;
            for(int k=0; k<CENTER;k++){
                srand(rand());
                Ce_Ou[j][k] = (double)rand()/RAND_MAX;
            }
        }
    }

    //パラメータ
    float a = 0.1;
    float b = 0.1;
    float c = 1.0;

    //教師データ
    int teach[20][20];
    for(int i = 0; i<20;i++){
        teach[i][i] = 1;
    }



    for(int i = 0; i<64; i++){
        srand(rand());
        Input[i] = (double)rand()/RAND_MAX;
    }

    return(0);
}


double sigmoid(double x){
    double c = exp(x);
    return 1.0 / (1.0 + c);
}