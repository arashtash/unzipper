/*
 * @author Arash Tashakori
 */
#include <stdio.h>

typedef struct {
    unsigned char character;
    unsigned char length;
    unsigned short encoding;
} Encoding;

/*This method receives the number of characters in the Encoding table, the encoding table
 * as well as the number of characters to be decoded, decodes them according to the table
 * and prints them to stdout*/
void decodeChars(char T, const Encoding *table, unsigned int N) {
    int numOfEncodedCharsSoFar = 0;
    int currentlyEncoding = 0;
    int currentLength = 0;

    while (numOfEncodedCharsSoFar < N) {
        //Get an inputed byte
        unsigned char nextByte = 0;
        scanf("%hhx", &nextByte);

        //Going through the inputed new byte bit by bit adding it one by one from the left
        for (int i = 7; i >= 0; i--){
            unsigned char nextBit = nextByte >> i & 0x01;
            currentlyEncoding = (currentlyEncoding << 1) | nextBit;
            currentLength++;

            //Compare what we have so far with the encodings in the table
            if (T == 0){    //If T is 0, then we have 256 elements in the table
                //Compare what we have taken in so far with every encoding in the table
                for (int j = 0; j < 256; j++){
                    if (currentLength == table[j].length){
                        if (currentlyEncoding == table[j].encoding){
                            printf("%c", table[j].character);

                            //Reset currently Encoding to check the next Bytes
                            currentlyEncoding = 0;
                            currentLength = 0;
                            numOfEncodedCharsSoFar++;

                            if (numOfEncodedCharsSoFar >= N) {
                                return;
                            }
                        }
                    }
                }
            } else { //If T is 0-255
                for (int j = 0; j < T; j++){
                    //Compare what we have taken in so far with every encoding in the table
                    if (currentLength == table[j].length){
                        if (currentlyEncoding == table[j].encoding){
                            printf("%c", table[j].character);

                            //Reset currently Encoding to check the next Bytes
                            currentlyEncoding = 0;
                            currentLength = 0;
                            numOfEncodedCharsSoFar++;

                            if (numOfEncodedCharsSoFar >= N) {
                                return;
                            }

                        }
                    }
                }
            }
        }
    }
}

/* This table receives an Encoding table and prints the Encoding in the format C : L E
 * where C is the hex representation of a character, L is the length of encryption of that letter
 * and E is the bit encoded value for that letter.*/
void printTable(char T, const Encoding *table) {
    if (T == 0){ //If T = 0, it means there are 256 entries
        for (int i = 0; i < 256; i++){
            printf("0x%2.2x : %d ", table[i].character, table[i].length);

            //Printing the encoding bitstream bit by bit
            for (int j = table[i].length; j > 0; j--){
                int bitToPrint = (table[i].encoding >> (j - 1)) & 1;
                printf("%d", bitToPrint);
            }

            printf("\n");
        }
    } else {
        for (int i = 0; i < T; i++){
            printf("0x%2.2x : %d ", table[i].character, table[i].length);

            //Printing the encoding bitstream bit by bit
            for (int j = table[i].length; j > 0; j--){
                int bitToPrint = (table[i].encoding >> (j - 1)) & 1;
                printf("%d", bitToPrint);
            }

            printf("\n");
        }
    }
}


int main() {
    char T = 0;
    char bitstreamLengthByte1 = 0;
    char bitstreamLengthByte2 = 0;
    char bitstreamLengthByte3 = 0;
    char bitstreamLengthByte4 = 0;
    Encoding table [256];

    scanf("%hhx", &T);


    //If the entered T is 0, we consider it as 256
    if (T == 0){
        for (int i = 0; i < 256; i++){
            unsigned char entry1;
            unsigned char entry2;
            unsigned char entry3;

            scanf("%hhx %hhx %hhx", &entry1, &entry2, &entry3);

            table[i].character = entry1;
            table[i].length = (entry2 >> 4) & 0x0F;

            //Merging the encoding and cutting them according to their length
            int lengthRightShift = 12 - table[i].length;
            table[i].encoding = (((entry2 & 0x0F) << 8) | entry3) >> lengthRightShift;
        }
    } else {
        for (int i = 0; i < T; i++){
            unsigned char entry1;
            unsigned char entry2;
            unsigned char entry3;

            scanf("%hhx %hhx %hhx", &entry1, &entry2, &entry3);

            table[i].character = entry1;
            table[i].length = (entry2 >> 4) & 0x0F;

            //Merging the encoding and cutting them according to their length
            int lengthRightShift = 12 - table[i].length;
            table[i].encoding = (((entry2 & 0x0F) << 8) | entry3) >> lengthRightShift;
        }
    }


    // Reading 4 Bytes encoding the length of the compressed bitstream to be decoded.
    scanf("%hhx %hhx %hhx %hhx", &bitstreamLengthByte1, &bitstreamLengthByte2,
          &bitstreamLengthByte3,&bitstreamLengthByte4);
    //Combining the bitstream length bytes into a 32-bit bit stream
    unsigned int N = ((bitstreamLengthByte1 << 24) & 0xFF000000) |
            ((bitstreamLengthByte2 << 16) & 0xFF0000) | ((bitstreamLengthByte3 << 8) & 0xFF00) |
            (bitstreamLengthByte4 & 0xFF);


    if (N == 0){ //If no encoded text is given
        //Printing the table
        printTable(T, table);
    } else {
        //Decoding and Printing the decoded text
        decodeChars(T, table, N);
    }

    return 0;
}


