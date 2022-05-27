#include <stdio.h>

//---------------------------------------------------------------------------------------------
//brief Передает пакет карте и возвращает ответ
//
//param[in] pTxBuf - буфер с пакетом для передаче карте
//param[in] txBufLen - размер пакета карте
//param[out] pRxBuf - буфер, куда будет записан ответный пакет карты
//param[out] rxBufLen - максимальный размер pRxBuf, туда же будет записан размер ответного пакета карты
//
//return true - успех
//return false - ошибка

//bool SendAPDU (unsigned char* pTxBuf, unsigned short txBufSize, unsigned char* pRxBuf, unsigned short* rxBufLen) {
        

//    return true;
//}


//RID = A000000658  - MIR
unsigned char temp[100] = {0x6F, 0x10, 0x84, 0x0E, 0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0x90, 0x00};

unsigned char pRxBuf[1000];
unsigned short rxBufLen[2]; 


int main() {
    //printf("answer from card: %f", SendAPDU());
    for (int i = 0; i < 101; i++) {
        printf("%x ", temp[i]);
    }
    

    return 0;
}
