#include <stdio.h>
#include <stdlib.h>
#include "test_data.c"

#define byte    unsigned char
#define twobyte unsigned short

//Debian 5.10.13 x64
//gcc 10.2.1 20210110 (Debian 10.2.1-6)
//bool SendAPDU (unsigned char* pTxBuf, unsigned short txBufSize, unsigned char* pRxBuf, unsigned short* rxBufLen)

int main() {
    
    struct appList {
        byte **AppIDs;                          //списко AID
        byte *AppPrio;                          //массив приоритетов
        byte AppCount;                          //количество приложений
        byte  *lenApp;                          //длинна отдельного AID
    } appsList = {.AppCount = 0, .lenApp = 0};

    twobyte lenSeq (byte *lenByte) {
        if ( *lenByte == 0x81)
            return (twobyte) *(lenByte + 1);
        else if ( *lenByte == 0x82 )
            return ((twobyte) *(lenByte + 1) << 8) | (twobyte) *(lenByte + 2);
        else
            return (twobyte) *lenByte;
    }

    twobyte _87 (byte *Buf, twobyte index, struct appList *Apps) {printf("\n _87 ");
        twobyte len = lenSeq(Buf + index + 1);
        twobyte d = len > 255 ? 3 : len > 128 ? 2 : 1;
        printf("%.2x ", Buf[index + d + len]);
        *(Apps -> AppPrio + Apps -> AppCount - 1) = Buf[index + d + len];
        
        return d + len;
    }

    twobyte _4F (byte *Buf, twobyte index, struct appList *Apps) {printf("\n _4F ");
        twobyte len = lenSeq(Buf + index + 1);
        twobyte d = len > 255 ? 3 : len > 128 ? 2 : 1;
        *(Apps -> lenApp + Apps -> AppCount - 1) = len;

        for ( twobyte i = 1; i <= len; i++ ) {
            printf("%.2x ", Buf[index + d + i]);
            *(Apps -> AppIDs + Apps -> AppCount - 1) = (byte *) realloc (*(Apps -> AppIDs + Apps -> AppCount - 1), i * sizeof (byte) );
            *(*(Apps -> AppIDs + Apps -> AppCount - 1) + i - 1) = Buf[index + d + i];
        }
        
        return d + len;
    }

    twobyte _61 (byte *Buf, twobyte index, struct appList *Apps) {printf("\n_61 ");
        twobyte len = lenSeq(Buf + index + 1);
        twobyte d = len > 255 ? 3 : len > 128 ? 2 : 1;
        Apps -> AppPrio = (byte *) realloc (Apps -> AppPrio, (Apps -> AppCount + 1) * sizeof (byte) );
        Apps -> lenApp = (byte *) realloc (Apps -> lenApp, (Apps -> AppCount + 1) * sizeof (byte) );
        Apps -> AppIDs = (byte **) realloc (Apps -> AppIDs, (Apps -> AppCount + 1) * sizeof (byte *) );
        Apps -> AppCount++;

        for (twobyte i = 1; i < len; i++) {
            if ( Buf[index + d + i] == 0x87 )
                i += _87 (Buf, index + d + i, Apps);

            if ( Buf[index + d + i] == 0x4F )
                i += _4F (Buf, index + d + i, Apps);
        }

        return d + len;
    }

    void printAppList (byte *Buf, twobyte lenRxBuf, struct appList *Apps) {
        
        for ( twobyte i = 0; i < lenRxBuf; i++ )
            if ( Buf[i] == 0x61 )
                i += _61 (Buf, i, Apps);
    }
   
    printAppList (temp1, rxBufLen[1], &appsList);

    printf("\n---тестирование---\n");
    printf("appsList.AppCount = %.2x\n", appsList.AppCount);
    

    printf("appsList.AppPrio = ");
    for ( twobyte i = 0; i < appsList.AppCount; i++ )
        printf("%.2x ", *(appsList.AppPrio + i));

    printf("\nappsList.lenApp = ");
    for ( twobyte i = 0; i < appsList.AppCount; i++)
        printf("%.2x ", appsList.lenApp[i]);
    
    for ( twobyte i = 0; i < appsList.AppCount; i++ ) {
        printf("\nappsList.AppIDs = ");
        for ( twobyte j = 0; j < appsList.lenApp[i]; j++ ) 
            printf("%.2x ", appsList.AppIDs[i][j]);
    }



    return 0;
}
