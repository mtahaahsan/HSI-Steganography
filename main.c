#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int ** makeMatrix(int m, int n){
//    int **matrix = (int**)malloc(m*sizeof(int*));
//    int i;
//    for(i = 0; i<m;i++){
//        matrix[i] = (int*)malloc(n*sizeof(int));
//    }
//    return matrix;
//}
struct RGB {
    int red;
    int green;
    int blue;
};

struct PPM {
    char type[2];
    int width;
    int height;
    int max;
    struct RGB *arr_rgb;
};


int main() {
    FILE *myFile;
    myFile = fopen("picture.pnm","r");
    struct PPM ppmfile;
    int count;
    for(count = 0; count<3; count++){
        ppmfile.type[count]= getc(myFile);
    }
    printf("%s", ppmfile.type);
    fscanf(myFile,"%d",&ppmfile.width);
    fscanf(myFile,"%d",&ppmfile.height);
    fscanf(myFile,"%d",&ppmfile.max);
    struct RGB arr_rgb[ppmfile.width*ppmfile.height];

    for(count=0; count<144000;count++){
        struct RGB rgbval;
        fscanf(myFile,"%d",&arr_rgb[count].red);
        fscanf(myFile,"%d",&arr_rgb[count].green);
        fscanf(myFile,"%d",&arr_rgb[count].blue);

    }
    ppmfile.arr_rgb = arr_rgb;
    printf("%d",ppmfile.arr_rgb[0].green);


//    for(rows = 0; rows<width; rows++){
//        for(cols = 0; cols<height; cols++){
//            fscanf(myFile, "%d", &matrix[rows][cols]);
//            printf("%d\n", matrix[rows][cols]);
//        }
//    }

    fclose(myFile);
    return 0;
}