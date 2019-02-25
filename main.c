#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-server-core.h>

int **makeMatrix(int m, int n) {
    int **matrix = (int **) calloc(m, sizeof(int *));
    int i;
    for (i = 0; i < m; i++) {
        matrix[i] = (int *) calloc(n, sizeof(int));
    }
    return matrix;
}

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
    struct RGB *pixelarray;
};

struct PPM l_ppmfile;


struct PPM *getPPM(FILE *file) {
    int count;
    int count2;
    int rows = 0;
    int cols = 0;

    fscanf(file, "%s", &l_ppmfile.type);

    fscanf(file, "%d", &l_ppmfile.width);
    printf("getPPM width %d\n", l_ppmfile.width);

    fscanf(file, "%d", &l_ppmfile.height);
    printf("getPPM height %d\n", l_ppmfile.height);

    fscanf(file, "%d", &l_ppmfile.max);
    printf("getPPM height %d\n", l_ppmfile.max);

//    l_ppmfile.pixelarray = makeMatrix(l_ppmfile.width,l_ppmfile.height);
//
    struct RGB *simp = (int *) malloc(l_ppmfile.height * l_ppmfile.width * 3 * sizeof(int));



//This is for mallocing a 2D array
//    struct RGB **simp = (int**)malloc(l_ppmfile.height*l_ppmfile.width*3* sizeof(int*));
//    int i;
//    for(i = 0; i<l_ppmfile.height*l_ppmfile.width;i++){
//        simp[i] = (int*)malloc(l_ppmfile.height*l_ppmfile.width*3*sizeof(int));
//    }


//Scanning into the matrix
//    for(cols = 0; cols<l_ppmfile.width; cols++){
//        for(rows=0; rows<l_ppmfile.height; rows++){
//            fscanf(file,"%d",&simp[rows][cols].red);
////            printf("%d\n",simp[rows][cols].red);
//            fscanf(file,"%d",&simp[rows][cols].green);
//            fscanf(file,"%d",&simp[rows][cols].blue);
//
//            }
//        }


    for (count = 0; count < l_ppmfile.width * l_ppmfile.height; count++) {
        fscanf(file, "%d", &simp[count].red);
        fscanf(file, "%d", &simp[count].green);
        fscanf(file, "%d", &simp[count].blue);
    }

//    FILE* enterfile1;
//    enterfile1 = fopen("enterfile.ppm","w");
//
//    fprintf(enterfile1,"%s\n",l_ppmfile.type);
//
//    fprintf(enterfile1,"%d %d\n", l_ppmfile.width, l_ppmfile.height);
//
//    fprintf(enterfile1, "%d\n", l_ppmfile.max);
//
//
//    for(count = 0; count<512*349; count++){
//        fprintf(enterfile1, "%d\n", simp[count].red);
//        fprintf(enterfile1, "%d\n", simp[count].green);
//        fprintf(enterfile1, "%d\n", simp[count].blue);
//    }
//    fclose(enterfile1);

    l_ppmfile.pixelarray = simp;


    return &l_ppmfile;
}

void showPPM(struct PPM *ppm1) {
    int rows = 0;
    int cols = 0;
    int count;
    FILE *enterfile;
    enterfile = fopen("enterfile.ppm", "w");

    fprintf(enterfile, "%s\n", ppm1->type);
    printf("%s\n", ppm1->type);

    fprintf(enterfile, "%d %d\n", ppm1->width, ppm1->height);

    fprintf(enterfile, "%d\n", ppm1->max);


    for (count = 0; count < ppm1->width * ppm1->height; count++) {
        fprintf(enterfile, "%d\n", ppm1->pixelarray[count].red);
        fprintf(enterfile, "%d\n", ppm1->pixelarray[count].green);
        fprintf(enterfile, "%d\n", ppm1->pixelarray[count].blue);
    }

//    for(cols = 0; cols<ppm1->height; cols++){
//        for(rows=0; rows<ppm1->width; rows++){
//            fprintf(enterfile,"%d\n",ppm1->pixelarray[cols][rows].red);
//            printf("%d\n",ppm1->pixelarray[rows][cols].red );
//            fprintf(enterfile,"%d\n",ppm1->pixelarray[cols][rows].green);
//            fprintf(enterfile,"%d\n",ppm1->pixelarray[cols][rows].blue);
//
//        }
//    }

    fclose(enterfile);
}

struct PPM *encode(struct PPM *im, char *message, unsigned int mSize, unsigned int secret) {
    srand(5);
    int binaryCount;
    int messageCount = 0;
    int rgbCount = 0;
    int random = rand();
    printf("encode %s\n", im->type);
    printf("%d\n", random);
    for (messageCount = 0; messageCount < mSize; messageCount++) {
        for (binaryCount = 7; binaryCount >= 0; binaryCount--) {
            printf("%d", (message[messageCount] >> binaryCount) & 0x01);
        }
        printf("\n");
    }
    messageCount = 0;
    while (messageCount < mSize) {
        binaryCount = 7;
        for (rgbCount; rgbCount < mSize * 3; rgbCount++) {

            if ((im->pixelarray[rgbCount].red & 0x01) == 1 && (message[messageCount] >> binaryCount & 0x01) == 0) {
                im->pixelarray[rgbCount].red--;
            }
            if ((im->pixelarray[rgbCount].red & 0x01) == 0 && (message[messageCount] >> binaryCount & 0x01) == 1) {
                im->pixelarray[rgbCount].red++;
            }
            binaryCount--;
            if (binaryCount < 0) {
                messageCount++;
                binaryCount = 7;
            }
            if(messageCount == mSize){
                break;
            }

            if ((im->pixelarray[rgbCount].green & 0x01) == 1 && (message[messageCount] >> binaryCount & 0x01) == 0) {
                im->pixelarray[rgbCount].green--;
            }
            if ((im->pixelarray[rgbCount].green & 0x01) == 0 && (message[messageCount] >> binaryCount & 0x01) == 1) {
                im->pixelarray[rgbCount].green++;
            }
            binaryCount--;
            if (binaryCount < 0) {
                messageCount++;
                binaryCount = 7;
            }
            if(messageCount == mSize){
                break;
            }

            if ((im->pixelarray[rgbCount].blue & 0x01) == 1 && (message[messageCount] >> binaryCount & 0x01) == 0) {
                im->pixelarray[rgbCount].blue--;
            }
            if ((im->pixelarray[rgbCount].blue & 0x01) == 0 && (message[messageCount] >> binaryCount & 0x01) == 1) {
                im->pixelarray[rgbCount].blue++;
            }
            binaryCount--;
            if (binaryCount < 0) {
                messageCount++;
                binaryCount = 7;
            }
            if(messageCount == mSize){
                break;
            }

        }
        printf("\n");
        rgbCount++;
    }

    int i;
//    for (i = 0; i < 13; i++) {
//        printf("RED VALUE %d\n", im->pixelarray[i].red);
//        printf("GREEN VALUE %d\n", im->pixelarray[i].green);
//        printf("BLUE VALUE %d\n", im->pixelarray[i].blue);
//    }

    return im;
}

char * decode(struct PPM *im, unsigned int secret){
    char *binary = (char*)malloc(sizeof(200));
    char *itr;
    int bin=0;
    int rgb = 0;

    int endCounter=0;
    int bin2;
    while(true){
        binary[bin] = ((im->pixelarray[rgb].red) & 0x01);
//        printf("%d\n", binary[bin]);
        bin++;
        if(bin%8 == 0){
            int sum = 0;
            int base = 1;
            for(bin2 = 7; bin2>0; bin2--){
                int num = binary[bin2];
                sum = sum+ (num * base);
                base = base *2;
            }
            bin = 0;
            if(sum==36){
                endCounter++;
                if(endCounter == 4){
                    printf("%c",sum);
                    break;
                }
            }

            printf("%c",sum);
        }



        binary[bin] = ((im->pixelarray[rgb].green) & 0x01);
//        printf("%d\n", binary[bin]);
        bin++;
        if(bin%8 == 0){
            int sum = 0;
            int base = 1;
            for(bin2 = 7; bin2>0; bin2--){
                int num = binary[bin2];
                sum = sum+ (num * base);
                base = base *2;
            }
            bin = 0;
            if(sum==36){
                endCounter++;
                if(endCounter == 4){
                    printf("%c",sum);
                    break;
                }
            }

            printf("%c",sum);
        }

        binary[bin] = ((im->pixelarray[rgb].blue) & 0x01);
//        printf("%d\n", binary[bin]);
        bin++;
        if(bin%8 == 0){
            int sum = 0;
            int base = 1;
            for(bin2 = 7; bin2>0; bin2--){
                int num = binary[bin2];
                sum = sum+ (num * base);
                base = base *2;
            }
            bin = 0;
            if(sum==36){
                endCounter++;
                if(endCounter == 4){
                    printf("%c",sum);
                    break;
                }
            }

            printf("%c",sum);
        }
        rgb++;
    }


}

int main() {
    FILE *myFile;
    myFile = fopen("homecat.ppm", "r");
    struct PPM *ppmfile = getPPM(myFile);
//    showPPM(ppmfile);
    struct PPM *new = encode(ppmfile, "Now I'm actually hiding messages$$$$", 36, 12345);
    showPPM(new);
    char *message = decode(new, 12345);
    fclose(myFile);

}