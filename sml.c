//
// Created by akihide.sato on 2019/07/12.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define INPUT 64
#define MIDDLE 50
#define OUTPUT 20
#define MESH_SIZE 8
#define FILE_SIZE 100

//シグモイド関数のプロトタイプ宣言
double sigmoid(double x);
void generateInputLayerFromData(double mesh[OUTPUT][FILE_SIZE][MESH_SIZE*MESH_SIZE], int who);
void initializeWeight(double Wim[MIDDLE][MESH_SIZE*MESH_SIZE], double Wmo[OUTPUT][MIDDLE]);
void initializeTeacher(int teacher[OUTPUT][OUTPUT]);
void printLayer(double mesh[MESH_SIZE*MESH_SIZE]);

int main(void){
    //重み関数
    double Wim[MIDDLE][MESH_SIZE*MESH_SIZE];
    double Wmo[OUTPUT][MIDDLE];
    //教師
    int teacher[OUTPUT][OUTPUT];
    //重み関数をランダムな値で初期化
    initializeWeight(Wim, Wmo);
    initializeTeacher(teacher);


    //パラメータ
    float a = 0.1;
    float b = 0.1;
    float c = 1.0;

    //層
    double input[OUTPUT][FILE_SIZE][MESH_SIZE*MESH_SIZE] = {0};
    double mid[MIDDLE] = {0};
    double output[OUTPUT] = {0};

    generateInputLayerFromData(input, 0);
    do {
        for (int w = 0; w < OUTPUT; ++w) {
            for (int f = 0; f < FILE_SIZE; ++f) {
                // 入力層 to 中間層
                for (int j = 0; j < MIDDLE; ++j) {
                    for (int i = 0; i < INPUT; ++i) {
                       mid[j] += Wim[j][i] * input[w][f][i];
                    }
                    mid[j] = sigmoid(mid[j]);
                }
                // 中間層 to 出力層
                for (int k = 0; k < OUTPUT; ++k) {
                    for (int j = 0; j < MIDDLE; ++j) {
                      output[k] += mid[j] * Wmo[k][j];
                    }
                    output[k] = sigmoid(output[k]);
                }
            }
        }
    } while (0);


    return 0;
}


double sigmoid(double x){
    double c = exp(-1 * x);
    return 1.0 / (1.0 + c);
}

void generateInputLayerFromData(double mesh[OUTPUT][FILE_SIZE][MESH_SIZE*MESH_SIZE], int who) {
    char f_name[MESH_SIZE*MESH_SIZE], str[MESH_SIZE*MESH_SIZE+1];
    FILE *fp;
    double add = 1.0/64;

    for(int i = 0; i<OUTPUT; i++) {
        switch (who) {
            case 0:
                sprintf(f_name, "./Data/hira0_%02dL.dat", i);
                break;
            case 1:
                sprintf(f_name, "./Data/hira0_%02dT.dat", i);
                break;
            case 2:
                sprintf(f_name, "./Data/hira1_%02dL.dat", i);
                break;
            default:
                sprintf(f_name, "./Data/hira1_%02dT.dat", i);
        }
        if(fp == NULL) {
            printf("%s file not open!\n", f_name);
        } else {
            printf("%s file opened!\n", f_name);
        }

        fp = fopen(f_name, "r");

        for(int mesh_itr = 0, word_itr = 0; fgets(str,66,fp) != NULL; mesh_itr++){
            for (int j = 0; j<64; j++) {
                if (str[j] == '1') {
                    mesh[i][word_itr][(mesh_itr%64/8)*8+j/8] += add;
                }
            }
            if (mesh_itr%INPUT == INPUT-1) {
                word_itr++;
            }
        }
        fclose(fp);
        printLayer(mesh[i][0]);
    }
}

void initializeWeight(double Wim[MIDDLE][MESH_SIZE*MESH_SIZE], double Wmo[OUTPUT][MIDDLE]) {
    for(int j=0; j<MIDDLE;j++) {
        for (int i = 0; i < MESH_SIZE*MESH_SIZE; ++i) {
            srand(rand());
            Wim[j][i] = (double)rand()/RAND_MAX;
        }
    }
    for(int k=0; k<OUTPUT;k++) {
        for (int j = 0; j < MIDDLE; ++j) {
            srand(rand());
            Wmo[k][j] = (double)rand()/RAND_MAX;
        }
    }
}

void initializeTeacher(int teacher[OUTPUT][OUTPUT]) {
    for (int i = 0; i < OUTPUT; ++i) {
        for (int j = 0; j < OUTPUT; ++j) {
            teacher[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void printLayer(double mesh[MESH_SIZE*MESH_SIZE]) {
    for(int j=0; j<MESH_SIZE;j++){
        for(int k=0; k<MESH_SIZE; k++){
            printf("%2.3f", mesh[j*8+k]);
        }
        puts("");
    }
    puts("");
}