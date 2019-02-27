#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-server-core.h>

//Creates a struct to hold the RGB values
struct RGB {
    int red;
    int green;
    int blue;
};

//Creates a struct for the PPM file
struct PPM {
    char type[2];
    char *comments;
    int width;
    int height;
    int max;
    struct RGB *pixelArray;
};


//Creates an instance of the struct PPM
struct PPM l_ppmfile;

//This method stores the file's information into a struct
struct PPM *getPPM(FILE *im) {
    int count;
    int commentCount = 0;

    //Scans and stores the type
    fscanf(im, "%s", &l_ppmfile.type);

    //Malloc the comments value in the struct for a max of 200 chars
    l_ppmfile.comments = (char *) malloc(sizeof(char) * 200);

    //Getting the the new line char, and then the first char of the next line, checking if it is the start of a comment, if it is, store the the line
    char c;
    c = getc(im);
    c = getc(im);
    while (c == '#') {
        l_ppmfile.comments[commentCount] = c;
        while (c != '\n') {
            c = (char) getc(im);
            commentCount++;
            l_ppmfile.comments[commentCount] = c;
        }
        c = getc(im);
        commentCount++;
    }
    count = 0;
    char *temp = (char *) malloc(sizeof(char) * 6);
    while (c != ' ') {
        temp[count] = c;
        c = getc(im);
        count++;
    }
    sscanf(temp, "%d", &l_ppmfile.width);

    //Scans and stores the width of the picture
//    fscanf(im, "%d", &l_ppmfile.width);

    //Scans and stores the height of the picture
    fscanf(im, "%d", &l_ppmfile.height);

    //Scans and stores the max value of a single rgb value
    fscanf(im, "%d", &l_ppmfile.max);

    //Allocates enough memory in this array of structs to store all the RGB values
    struct RGB *simp = (int *) malloc(l_ppmfile.height * l_ppmfile.width * 3 * sizeof(int));

    for (count = 0; count < l_ppmfile.width * l_ppmfile.height; count++) {
        fscanf(im, "%d", &simp[count].red);
        fscanf(im, "%d", &simp[count].green);
        fscanf(im, "%d", &simp[count].blue);
    }

    //Assigns the array created above's pointer to the pointer in the PPM struct so that both point at the same thing
    l_ppmfile.pixelArray = simp;

    //Returns the address of the PPM struct
    return &l_ppmfile;
}

//This method puts the values
void showPPM(struct PPM *ppm1) {
    int count;

    //Enters the type into the file
    printf("%s\n", ppm1->type);

    //Inserts the comments into the file
    printf("%s", ppm1->comments);
    //Enters the width and height into the file
    printf("%d %d\n", ppm1->width, ppm1->height);

    //Enters the max value into the file
    printf("%d\n", ppm1->max);


    //Enters all the RGB values into the file
    for (count = 0; count < ppm1->width * ppm1->height; count++) {
        printf("%d\n", ppm1->pixelArray[count].red);

        printf("%d\n", ppm1->pixelArray[count].green);

        printf("%d\n", ppm1->pixelArray[count].blue);
    }

}


struct PPM *encode(struct PPM *im, char *message, unsigned int mSize, unsigned int secret) {
    //Uses secret to generate a random value and then gives a random value to rgbCount by modding it by secret
    srand(secret);
    long randoms = rand();
    long rgbCount = (randoms % secret) % (im->width * im->height);
    mSize = mSize + 7;

    //Creates a new char array and adds the message and the ending that needs to be encoded into it
    char *end = "~~~~~~";
    char *newMessage = (char *) malloc((sizeof(char) * mSize) + 6);
    strcat(newMessage, message);
    strcat(newMessage, end);

    //Gets the last bit of the RGB values, and goes through each bit of the message, if the RGB value needs to be
    //changed, then we change it by adding 1 or 0
    int binaryCount = 7;
    int messageCount = 0;
    while (messageCount < mSize) {
        for (rgbCount; rgbCount < im->width * im->height; rgbCount++) {

            if ((im->pixelArray[rgbCount].red & 0x01) == 1 && (newMessage[messageCount] >> binaryCount & 0x01) == 0) {
                im->pixelArray[rgbCount].red--;
            }
            if ((im->pixelArray[rgbCount].red & 0x01) == 0 && (newMessage[messageCount] >> binaryCount & 0x01) == 1) {
                im->pixelArray[rgbCount].red++;
            }
            binaryCount--;
            if (binaryCount < 0) {
                messageCount++;
                binaryCount = 7;
            }
            if (messageCount == mSize) {
                break;
            }

            if ((im->pixelArray[rgbCount].green & 0x01) == 1 && (newMessage[messageCount] >> binaryCount & 0x01) == 0) {
                im->pixelArray[rgbCount].green--;
            }
            if ((im->pixelArray[rgbCount].green & 0x01) == 0 && (newMessage[messageCount] >> binaryCount & 0x01) == 1) {
                im->pixelArray[rgbCount].green++;
            }
            binaryCount--;
            if (binaryCount < 0) {
                messageCount++;
                binaryCount = 7;
            }
            if (messageCount == mSize) {
                break;
            }

            if ((im->pixelArray[rgbCount].blue & 0x01) == 1 && (newMessage[messageCount] >> binaryCount & 0x01) == 0) {
                im->pixelArray[rgbCount].blue--;
            }
            if ((im->pixelArray[rgbCount].blue & 0x01) == 0 && (newMessage[messageCount] >> binaryCount & 0x01) == 1) {
                im->pixelArray[rgbCount].blue++;
            }
            binaryCount--;
            if (binaryCount < 0) {
                messageCount++;
                binaryCount = 7;
            }
            if (messageCount == mSize) {
                break;
            }

        }
        rgbCount++;
        if (rgbCount > im->width * im->height) {
            rgbCount = randoms % secret;
        }
    }
    return im;
}

int binaryDecode(char *binaryMessage) {
    int sum = 0;
    int base = 1;
    int bin2;
    for (bin2 = 7; bin2 > 0; bin2--) {
        int num = binaryMessage[bin2];
        sum = sum + (num * base);
        base = base * 2;
    }
    return sum;
}

//This method takes a ppm file and a secret, and then decodes the bits from the RGB to find a sequence of chars
char *decode(struct PPM *im, unsigned int secret) {
    //Allocates memory for the message when reading as bits
    char *binaryMessage = (char *) malloc(sizeof(200));

    //Generates the pseudo-random value to find where the message is hidden
    srand(secret);
    long randoms = rand();
    long rgb = (randoms % secret) % (im->width * im->height);

    //Allocates memory for the decoded message char array
    int decodeCount = 0;
    char *decodedMessage = (char *) malloc(sizeof(char) * 200);

    int binaryCount = 0;
    int endCounter = 0;
    int sum;


    while (true) {
        //This takes the last bits of RGB and stores them in the binaryMessage array
        binaryMessage[binaryCount] = (char) ((im->pixelArray[rgb].red) & 0x01);
        binaryCount++;

        //This checks if the byte is complete, if it is, then find the decimal value
        if (binaryCount % 8 == 0) {
            sum = binaryDecode(binaryMessage);
            binaryCount = 0;
            if (sum == '~') {
                endCounter++;
                if (endCounter == 6) {
                    break;
                }
            }

            //This stores the decimal value as a char
            decodedMessage[decodeCount] = (char) sum;
            decodeCount++;

        }


        binaryMessage[binaryCount] = (char) ((im->pixelArray[rgb].green) & 0x01);
        binaryCount++;

        if (binaryCount % 8 == 0) {
            sum = binaryDecode(binaryMessage);
            binaryCount = 0;
            if (sum == '~') {
                endCounter++;
                if (endCounter == 6) {
                    break;
                }
            }

            decodedMessage[decodeCount] = (char) sum;
            decodeCount++;
        }

        binaryMessage[binaryCount] = (char) ((im->pixelArray[rgb].blue) & 0x01);
        binaryCount++;

        if (binaryCount % 8 == 0) {
            sum = binaryDecode(binaryMessage);
            binaryCount = 0;
            if (sum == '~') {
                endCounter++;
                if (endCounter == 6) {
                    break;
                }
            }

            decodedMessage[decodeCount] = (char) sum;
            decodeCount++;
        }
        rgb++;
        if (rgb > im->height * im->width) {
            rgb = randoms % secret;
        }
    }

    //This removes the end chars that denote the ending of the message and then prints the message
    decodedMessage[decodeCount - 5] = '\0';
    printf("%s", decodedMessage);


}

int main(int argc, char **argv) {
    FILE *myFile;

//    printf("%c", argv[1][0]);
    myFile = fopen(argv[2], "r");

    struct PPM *ppmFile = getPPM(myFile);
    struct PPM *new;

//    new = encode(ppmFile, "hello", 5, 12345);
    if (argv[1][0] == 'e') {
        char *message[1000];
        fprintf(stderr, "Enter your message up to 1000 characters\n");
        fgets(message, 1000, stdin);
        int length = strlen(message);

        int secret;
        fprintf(stderr, "Enter the secret up to 5 numbers\n");
        scanf("%d", &secret);

        new = encode(ppmFile, message, length, secret);
        showPPM(new);
    }

    if (argv[1][0] == 'd') {
        int secret;
        fprintf(stderr, "Enter the secret \n");
        scanf("%d", &secret);
//        fprintf("%d", secret);
        char finalmessage = decode(ppmFile, secret);
    }
}