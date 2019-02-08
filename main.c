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
    arr_size = ppmfile.height * ppmfile.width;
    struct RGB arr_rgb[arr_size];

    for(count=0; count<arr_size;count++){
        fscanf(file,"%d",&arr_rgb[count].red);
        fscanf(file,"%d",&arr_rgb[count].green);
        fscanf(file,"%d",&arr_rgb[count].blue);
//        printf("Counter %d\n", count);
//        printf("Size %d\n", arr_size);
    }

    ppmfile.arr_rgb = arr_rgb;
    return &ppmfile;
}

void showPPM(struct PPM *ppm1){
    printf("showPPM Type%s\n",&ppm1->type);
    printf("%d %d\n",ppm1->width, ppm1->height);
    printf("%d\n",&ppm1->max);
//    printf("%d Is the product", ppm->width*ppm->height);
//    for (int i = 0; i < ppm->width*ppm->height; i++) {
//        printf("%d\n",ppm->arr_rgb[i].red);
//        printf("%d\n",ppm->arr_rgb[i].green);
//        printf("%d\n",ppm->arr_rgb[i].blue);
//    }

}


int main() {
    FILE *myFile;
    myFile = fopen("picture.pnm","r");

    struct PPM *ppmfile = getPPM(myFile);
//    printf(" getPPM Type main %s ", ppmfile->type);

    showPPM(&ppmfile);
//    printf("%d",ppmfile->width);


//    for(rows = 0; rows<width; rows++){
//        for(cols = 0; cols<height; cols++){
//            fscanf(myFile, "%d", &matrix[rows][cols]);
//            printf("%d\n", matrix[rows][cols]);
//        }
//    }

    fclose(myFile);
    return 0;
}