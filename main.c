#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-server-core.h>

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

    struct RGB *simp = (int *) malloc(l_ppmfile.height * l_ppmfile.width * 3 * sizeof(int));

    for (count = 0; count < l_ppmfile.width * l_ppmfile.height; count++) {
        fscanf(file, "%d", &simp[count].red);
        fscanf(file, "%d", &simp[count].green);
        fscanf(file, "%d", &simp[count].blue);
    }

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

    fprintf(enterfile, "%d %d\n", ppm1->width, ppm1->height);

    fprintf(enterfile, "%d\n", ppm1->max);


    for (count = 0; count < ppm1->width * ppm1->height; count++) {
        fprintf(enterfile, "%d\n", ppm1->pixelarray[count].red);
        fprintf(enterfile, "%d\n", ppm1->pixelarray[count].green);
        fprintf(enterfile, "%d\n", ppm1->pixelarray[count].blue);
    }

    fclose(enterfile);
}

struct PPM *encode(struct PPM *im, char *message, unsigned int mSize, unsigned int secret) {
    srand(secret);
    long randoms = rand();
    printf("%li\n", randoms%secret);
    int binaryCount;
    int messageCount = 0;
    int rgbCount = randoms%secret;
    for (messageCount = 0; messageCount < mSize; messageCount++) {
        for (binaryCount = 7; binaryCount >= 0; binaryCount--) {
            printf("%d", (message[messageCount] >> binaryCount) & 0x01);
        }
        printf("\n");
    }
    messageCount = 0;
    printf("We reach here");
    while (messageCount < mSize) {
        binaryCount = 7;
        for (rgbCount; rgbCount < 100000000000; rgbCount++) {

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
    printf("But do we reach ere");

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
    srand(secret);
    long randoms = rand();
    printf("%li\n", randoms%secret);
    char *itr;
    int bin=0;
    int rgb = randoms%secret;

    int endCounter=0;
    int bin2;
    printf("It's breaking here");
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