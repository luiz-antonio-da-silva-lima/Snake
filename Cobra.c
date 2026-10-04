#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define altura 30
#define largura 60
#define pixelciano "\033[46m \033[0m"
#define pixelvermelho "\033[41m \033[0m"
#define pixelazul "\033[44m \033[0m"
#define pixelverde "\033[42m \033[0m"
int score, cobratamanho, cobracabecax, cobracabecay, frutaposx, frutaposy, cobraraboy[100], cobrarabox[100];
int mensagemderrota;
bool s;
char direcao, input;
void iniciarFrutaCobra();
void coisas();
void printarTela();

int main()
{
    srand(time(NULL));
    iniciarFrutaCobra();
    while (s)
    {
        coisas();
        printarTela();
        Sleep(100);
    }
    return 0;
}

void iniciarFrutaCobra()
{
    cobratamanho = 0;
    score = 0;
    s = true;
    input = getch();
    cobracabecay = altura / 2;
    cobracabecax = largura / 2;
    frutaposx = rand() % (largura - 2) + 1;
    frutaposy = rand() % (altura - 2) + 1;
}
void coisas() {
     if (kbhit())
        {
            input = getch();
            if (cobratamanho == 0){
                if (input == 'w' || input == 's' || input == 'a' || input == 'd'){
                direcao = input;
                }
            }
            else if ((input == 'w' && (!(cobracabecay == cobraraboy[0]+1))|| input == 's' && (!(cobracabecay == cobraraboy[0]-1))|| input == 'a' && (!(cobracabecax == cobrarabox[0]+1)) || input == 'd' && (!(cobracabecax == cobrarabox[0]-1))))
            {
                direcao = input;
            }
        }
        int cabecaxanterior = cobracabecax;
        int cabecayanterior = cobracabecay;
        for (int i = cobratamanho; i > 0; i--)
        {
            cobrarabox[i] = cobrarabox[i - 1];
            cobraraboy[i] = cobraraboy[i - 1];
        }
        cobrarabox[0] = cobracabecax;
        cobraraboy[0] = cobracabecay;
        switch (direcao)
        {
        case 'w':
            cobracabecay--;
            break;
        case 'a':
            cobracabecax--;
            break;
        case 's':
            cobracabecay++;
            break;
        case 'd':
            cobracabecax++;
            break;
        case 'x':
            s = false;
            break;
        }

        if (cobracabecax == frutaposx && cobracabecay == frutaposy)
        {
            frutaposx = rand() % (largura - 2) + 1;
            frutaposy = rand() % (altura - 2) + 1;
            cobratamanho++;
            score += 10;
        }
        for (int i = 1; i<cobratamanho; i++){
            if (cobracabecax == cobrarabox[i] && cobracabecay == cobraraboy[i]) {
                s = false;
                mensagemderrota = 1;
            }
        }
        if ((cobracabecax == 0 || cobracabecax == largura-1) || (cobracabecay == 0 || cobracabecay == altura-1)){
            cobracabecax = cabecaxanterior;
            cobracabecay = cabecayanterior;
            s = false;
            mensagemderrota = 2;
        }
}
void printarTela()
{
    system("cls");
    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {

            if (y == 0 || y == altura - 1 || x == 0 || x == largura - 1)
            {
                printf(" ");
            }
            else if (y == cobracabecay && x == cobracabecax)
            {
                printf(pixelazul);
            }
            else if (y == frutaposy && x == frutaposx)
            {
                printf(pixelvermelho);
            }
            else {
                bool printouRabo = false;
                for (int i = 0; i < cobratamanho; i++){
                    if (y == cobraraboy[i] && x == cobrarabox[i]){
                        printf(pixelciano);
                        printouRabo = true;
                        break; 
                    }
                }
                if (!printouRabo) {
                    printf(pixelverde);
            }
            }
        }
        printf("\n");
    }
    printf("\nScore : %d\n", (cobratamanho*100));
    if(!s){
        if (mensagemderrota == 1){
            printf("Bateu no propio rabo, morreu");
        } else if (mensagemderrota == 2){
            printf("Bateu na parede, morreu");
        }

    }
}