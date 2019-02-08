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

struct PPM ppmfile;

struct PPM *getPPM(FILE *file){
    int count;
    for(count = 0; count<3; count++){
        ppmfile.type[count]= getc(file);
    }
//    printf(" getPPM Type %s ", ppmfile.type);
    fscanf(file,"%d",&ppmfile.width);
//    printf("%d This is Width", ppmfile.width);
    fscanf(file,"%d",&ppmfile.height);
//    printf("%d This is Width", ppmfile.height);
    fscanf(file,"%d",&ppmfile.max);
    int arr_size;

    arr_size = (ppmfile.height * ppmfile.width);
    printf("Size %d\n", arr_size);
    struct RGB arr_rgb[arr_size];

    for(count=0; count<arr_size;count=count+3){
        fscanf(file,"%d",&arr_rgb[count].red);
        fscanf(file,"%d",&arr_rgb[count+1].green);
        fscanf(file,"%d",&arr_rgb[count+2].blue);
        if (count == 143992) {
            printf("Get red %d\n", arr_rgb[count].red);
            printf("Get green %d\n", arr_rgb[count].green);
            printf("Get Blue %d\n", arr_rgb[count].blue);}
//
//        printf("Size %d\n", arr_size);
    }
//    printf("abcdef %d\n", arr_rgb[143992].blue);

    ppmfile.arr_rgb = arr_rgb;

        printf("xRed %d\n", ppmfile.arr_rgb[143992].red);
        printf("xGreen %d\n", ppmfile.arr_rgb[143992].green);
        printf("xBlue %d\n", ppmfile.arr_rgb[143992].blue);

    return &ppmfile;
}

void showPPM(struct PPM ppm1){
    printf("Show PPM Type %s\n",ppm1.type);
    printf("Show Width %d\nShow Height %d\n",ppm1.width, ppm1.height);
    printf("Show Max %d\n",ppm1.max);
    printf("Show Width x Height %d\n", ppm1.width*ppm1.height);
//    printf("%d", ppm1->arr_rgb[0].blue);
    for (int i = 0; i < ppm1.width*ppm1.height; i++) {
       if (i == 143992) {
            printf("i %d\n", i);
            printf("Show Red %d\n", ppm1.arr_rgb[i].red);
            printf("Show Green %d\n", ppm1.arr_rgb[i].green);
            printf("Show Blue %d\n", ppm1.arr_rgb[i].blue);
        }
    }
}


int main() {
    FILE *myFile;
    myFile = fopen("picture.pnm","r");

    struct PPM *ppmfile = getPPM(myFile);
//    printf(" getPPM Type main %s ", ppmfile->type);

    printf("mShow PPM Type %s\n",ppmfile->type);
    printf("mShow Width %d\nShow Height %d\n",ppmfile->width, ppmfile->height);
    printf("mShow Max %d\n",ppmfile->max);

    printf("mRed %d\n", ppmfile->arr_rgb[143992].red);
    printf("mGreen %d\n", ppmfile->arr_rgb[143992].green);
    printf("mBlue %d\n", ppmfile->arr_rgb[143992].blue);


 showPPM(*ppmfile);
//    printf("%d",ppmfile->width);
//    printf("%d", ppmfile->arr_rgb[143992].blue);

    fclose(myFile);
    return 0;
}