#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Debian 5.10.13 x64
//gcc 10.2.1 20210110 (Debian 10.2.1-6)
//bool SendAPDU (unsigned char* pTxBuf, unsigned short txBufSize, unsigned char* pRxBuf, unsigned short* rxBufLen)

typedef unsigned char byte;
typedef unsigned short twobyte;

//byte pRxBuf[61] = {0x6F, 0x39, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x27, 0xBF, 0x0C, 0x24, 0x61, 0x12, 0x9F, 0x2A, 0x03, 0x81, 0x06, 0x43, 0x87, 0x01, 0x03, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x04, 0x32, 0x00, 0x01, 0x61, 0x0E, 0x87, 0x01, 0x02, 0x4F, 0x09, 0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10, 0x33, 0x33, 0x90, 0x00};
//byte pRxBuf[45] = {0x6F, 0x29, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x17, 0xBF, 0x0C, 0x14, 0x61, 0x12, 0x9F, 0x2A, 0x03, 0x81, 0x06, 0x43, 0x87, 0x01, 0x81, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10, 0x90, 0x00};
//byte pRxBuf[20] = {0x6F, 0x10, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0x90, 0x00};
//byte pRxBuf[36] = {0x6F, 0x20, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x0E, 0xBF, 0x0C, 0x0B, 0x61, 0x09, 0x9F, 0x2A, 0x03, 0x81, 0x06, 0x43, 0x87, 0x01, 0x01, 0x90, 0x00};
//byte pRxBuf[59] = {0x6F, 0x37, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x25, 0xBF, 0x0C, 0x22, 0x61, 0x12, 0x9F, 0x2A, 0x03, 0x81, 0x06, 0x43, 0x87, 0x01, 0x03, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x04, 0x32, 0x00, 0x01, 0x61, 0x0C, 0x87, 0x01, 0x02, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10, 0x90, 0x00};
byte pRxBuf[74] = {0x6F, 0x61, 0x12, 0x9F, 0x2A, 0x03, 0x81, 0x06, 0x43, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x04, 0x32, 0x00, 0x01, 0x87, 0x01, 0x03, 0x61, 0x0C, 0x87, 0x01, 0x02, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10, 0x61, 0x0E, 0x87, 0x01, 0x00, 0x4F, 0x09, 0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10, 0x33, 0x33, 0x61, 0x12, 0x9F, 0x2A, 0x03, 0x81, 0x06, 0x43, 0x87, 0x01, 0x03, 0x4F, 0x07, 0xA0, 0x00, 0x00, 0x04, 0x32, 0x00, 0x01, 0x90, 0x00};
//byte pRxBuf[20] = {0x6f, 0x10, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0x90, 0x00};
twobyte rxBufLen[2] = {0x0400, 0x4A}; 

typedef struct AID {
    byte *aid;
    byte prio;
    twobyte lenaid;
} AID;

AID *listAID;
byte appCount = 0;

int cmp (const void *a, const void *b);
twobyte lenSeq (byte *lenByte);
int parsing();
void sorting();
void testing();
void result();

int main() {

    parsing();

    testing();

    sorting();

    testing();

    result();

    free(listAID);
    return 0;
}


twobyte lenSeq (byte *lenByte) {
        if ( *lenByte == 0x81 )
            return (twobyte) *(lenByte + 1);
        else if ( *lenByte == 0x82 )
            return ((twobyte) *(lenByte + 1) << 8) | (twobyte) *(lenByte + 2);
        else
            return (twobyte) *lenByte;
    }


int parsing() {
    printf("---------------парсинг----------------------");
    
    for ( twobyte i = 0; i < rxBufLen[1]; i++ )
        
        if ( pRxBuf[i] == 0x61 ) {
            printf("\n%.2x ", pRxBuf[i]);
            appCount++;
            twobyte len61 = lenSeq (pRxBuf + i + 1);
            twobyte d61 = ( len61 > 255 ? 3 : len61 > 128 ? 2 : 1 );
            listAID = (AID *) realloc (listAID, appCount * sizeof(AID));
            if (listAID == NULL) 
                return 1;
            i += d61;

            for ( twobyte j = 1; j <= len61; j++ ) {

                if ( pRxBuf[i + j] == 0x87) {
                    printf("\n %.2x ", pRxBuf[i + j]);
                    twobyte len87 = lenSeq(pRxBuf + i + j + 1);
                    twobyte d87 = len87 > 255 ? 3 : len87 > 128 ? 2 : 1;
                    (listAID + appCount - 1) -> prio = pRxBuf[i + j + d87 + len87];
                    j += len87 + d87;
                }

                if ( pRxBuf[i + j] == 0x4F ) {
                    printf("\n %.2x ", pRxBuf[i + j]);
                    twobyte len4F = lenSeq(pRxBuf + i + j + 1);
                    twobyte d4F = len4F > 255 ? 3 : len4F > 128 ? 2 : 1;
                    (listAID + appCount - 1) -> lenaid = len4F;
                    (listAID + appCount - 1) -> aid = malloc (len4F * sizeof(byte));
                    if ( (listAID + appCount - 1) -> aid == NULL )
                        return 1;
                    i += d4F;

                    for ( byte k = 1; k <= len4F; k++ ) 
                        (listAID + appCount - 1) -> aid[k - 1] = pRxBuf[i + j + k];

                    j += len4F;
                }
            }     
        }

    return 0;
}


void sorting() {
    printf("\n---------------сортировка-------------------");
    byte supApp[]= {0xA0, 0x00, 0x00, 0x06, 0x58};

    for ( byte i = 1, count = 1; i <= appCount; i++, count++ ) {
        if ( listAID[i - 1].aid != NULL )
            if ( memcmp( supApp, listAID[i - 1].aid, 5 ) != 0 ) {
                printf("\nудалено app № %x", count);
                memmove ( &listAID[i - 1], &listAID[i], ( appCount - i ) * sizeof (AID) );
                appCount--;
                i--;
            }
    }

    qsort (listAID, appCount, sizeof (AID), cmp);
}


void testing () {
    printf("\n---------------тестирование-----------------");
    printf("\nappCount = %.2x\n", appCount);

    for ( byte i = 0; i < appCount; i++ ) {
        printf("\nprio     = %.2x", (listAID + i) -> prio);
        printf("\nlenaid   = %.2x", (listAID + i) -> lenaid);
        printf("\naid      = ");
        for ( byte j = 0; j < (listAID + i) -> lenaid; j++ )
            printf("%.2x ", (listAID + i) -> aid[j]);
    }
}

int cmp (const void *a, const void *b) {
    if ( ( (AID *) b ) -> prio == 0x00 || ( (AID *) b) -> prio > 0x0F )
        return -1;
    else
        return ( (AID *) a ) -> prio  - ( (AID *) b ) -> prio;
}

void result () {
    printf("\n------------------результат-----------------\n");

    for ( byte i = 0; i < appCount; i++ ) {
        if ( listAID[i].lenaid > 0 ) {
            for ( byte j = 0; j < 5; j++ ) 
                printf("%.2x", listAID[i].aid[j]);

            printf(" + ");

            for ( byte j = 5; j < listAID[i].lenaid; j++ )
                printf("%.2x", listAID[i].aid[j]);
            printf("\n");
        }
    }

}
