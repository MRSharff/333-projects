/* Mat Sharff
 * HW2
 * 1/23/2015
 * TCSS333
 */

#include <stdio.h>
#define OFFSET 23


int main(int argc, char *argv[]) {

    if (argc != 2) {
      return 1;
    }

    FILE *infile = fopen(argv[1],"rb");

    if (infile == NULL) {
      printf("File does not exist.\n");
      return 1;
    }
    FILE *outfile = fopen("doubleSize.bmp","wb");
    FILE *outfile2 = fopen("halfSize.bmp", "wb");

    int r, c, i, j, rCounter, cCounter;
    int bpp, bppMult;
    int fileSize, pixelWidth, pixelHeight, cStay, rStay, newCIndex;
    int doublePixelHeight, doublePixelWidth, halfPixelHeight, halfPixelWidth;
    int doubleFileSize, halfFileSize;
    char bmField[2];
    char restOfHdr[48];
    char firstHalfHdr[12];
    char colorPanes[2];
    char secondHalfHdr[OFFSET];


    fread(bmField, sizeof(char), 2, infile);
    fread(&fileSize, sizeof(int), 1, infile);
    printf("file size = %d\n", fileSize);
    fread(firstHalfHdr, sizeof(char), 12, infile);
    fread(&pixelWidth, sizeof(int), 1, infile);
    fread(&pixelHeight, sizeof(int), 1, infile);
    fread(&colorPanes, sizeof(char), 2, infile);

    //handle different bits per pixel bitmaps (needs more work for full integration)
    fread(&bpp, sizeof(int), 1, infile);
    bppMult = bpp / 8;

    fread(secondHalfHdr, sizeof(char), OFFSET, infile);
    doublePixelHeight = pixelHeight * 2;
    doublePixelWidth = pixelWidth * 2;
    halfPixelHeight = pixelHeight / 2;
    halfPixelWidth = pixelWidth / 2;
    char pixels[pixelHeight][pixelWidth * bppMult];
    char doubleSize[doublePixelHeight][doublePixelWidth * bppMult];
    char halfSize[halfPixelHeight][halfPixelWidth * bppMult];

    fread(pixels, sizeof(char), pixelHeight * pixelWidth * bppMult, infile);

    fclose(infile);

    printf("Original Pixel width: %d\n", pixelWidth);
    printf("Original Pixel height: %d\n", pixelHeight);

    //fill double size array
    for (r = 0; r < pixelHeight; r++) {

        rStay = r;

        for (c = 0; c < pixelWidth * bppMult; c++) {

            cStay = c;
            for (i = 0; i < bppMult; i++) {
                newCIndex = (2 * cStay) + i;
                doubleSize[2 * rStay][newCIndex] = pixels[rStay][c];
                doubleSize[2 * rStay][newCIndex + bppMult] = pixels[rStay][c];
                doubleSize[2 * rStay + 1][newCIndex] = pixels[rStay][c];
                doubleSize[2 * rStay + 1][newCIndex + bppMult] = pixels[rStay][c];
                c++;
            }
            c--;
        }
    }

        //set variable for double size
    doubleFileSize = doublePixelWidth * doublePixelHeight * bppMult + 54;

    //debug
    printf("Doubled file size = %d\n", doubleFileSize);
    printf("Doubled Pixel width: %d\n", doublePixelWidth);
    printf("Doubled Pixel height: %d\n", doublePixelHeight);
    printf("bpp = %d\n", bpp);
    printf("colorPanes = %s\n", colorPanes);


    //write double size
    fwrite(bmField, sizeof(char), 2, outfile);
    fwrite(&doubleFileSize, sizeof(int), 1, outfile);
    fwrite(firstHalfHdr, sizeof(char), 12, outfile);
    fwrite(&doublePixelWidth, sizeof(int), 1, outfile);
    fwrite(&doublePixelHeight, sizeof(int), 1, outfile);
    fwrite(&colorPanes, sizeof(char), 2, outfile);
    fwrite(&bpp, sizeof(int), 1, outfile);
    fwrite(secondHalfHdr, sizeof(char), OFFSET, outfile);
    fwrite(doubleSize, sizeof(char), doublePixelHeight * doublePixelWidth * bppMult, outfile);

    //close double size file reader
    fclose(outfile);


    //fill half size array
    rCounter = 0;
    for (r = 0; r < pixelHeight; r+= 2) {

        cCounter = 0;

        for (c = 0; c < pixelWidth * bppMult; c+= 6) {
            halfSize[rCounter][cCounter] = pixels[r][c];
            cCounter++;
            halfSize[rCounter][cCounter] = pixels[r][c + 1];
            cCounter++;
            halfSize[rCounter][cCounter] = pixels[r][c + 2];
            cCounter++;
        }
        rCounter++;
    }

    //compute half size file size
    halfFileSize = halfPixelWidth * halfPixelHeight * bppMult + 54;

    //half size debug
    printf("Halved file size = %d\n", halfFileSize);
    printf("Halved Pixel width: %d\n", halfPixelWidth);
    printf("Halved Pixel height: %d\n", halfPixelHeight);
    printf("bpp = %d\n", bpp);
    printf("colorPanes = %s\n", colorPanes);


    //write half size
    fwrite(bmField, sizeof(char), 2, outfile2);
    fwrite(&halfFileSize, sizeof(int), 1, outfile2);
    fwrite(firstHalfHdr, sizeof(char), 12, outfile2);
    fwrite(&halfPixelWidth, sizeof(int), 1, outfile2);
    fwrite(&halfPixelHeight, sizeof(int), 1, outfile2);
    fwrite(&colorPanes, sizeof(char), 2, outfile2);
    fwrite(&bpp, sizeof(int), 1, outfile2);
    fwrite(secondHalfHdr, sizeof(char), OFFSET, outfile2);
    fwrite(halfSize, sizeof(char), halfPixelHeight * halfPixelWidth * bppMult, outfile2);

    //close half size file writer
    fclose(outfile2);

    return 0;

}
