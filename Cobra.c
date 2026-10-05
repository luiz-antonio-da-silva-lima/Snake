#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define altura 30
#define largura 60
#define VerdeEscuro "\x1b[48;2;9;175;30m  "
#define VerdeClaro "\x1b[48;2;59;247;73m  "
#define Vermelho "\x1b[48;2;255;0;0m  "
#define AzulEscuro "\x1b[48;2;0;0;200m  "
#define AzulmenosEscuro "\x1b[48;2;0;120;255m  "
#define linhaNova "\x1b[0m\n"
#define setCursorIncio "\033[H"
#define esconderCursor "\033[?25l"
#define mostrarCursor "\033[?25h"
int score, cobratamanho, cobracabecax, cobracabecay, frutaposx, frutaposy, cobraraboy[100], cobrarabox[100];
int mensagemderrota;

bool s, reiniciar;

char direcao, input;

void IniciarValores();

void coisas();
    
void printarTela();

void DesejaReiniciar();

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    GetConsoleMode(handle, &modo);
    SetConsoleMode(handle, modo | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    srand(time(NULL));
    do
    {
        reiniciar = false;
        IniciarValores();
        while (s)
        {
            coisas();
            printarTela();
            Sleep(100);
        }
        Sleep(1000);
        DesejaReiniciar();
    } while (reiniciar);
     return 0;
}

void IniciarValores()
{
    cobratamanho = 0;
    score = 0;
    s = true;
    cobracabecay = altura / 2;
    cobracabecax = largura / 2;
    frutaposx = rand() % (largura - 2) + 1;
    frutaposy = rand() % (altura - 2) + 1;
    printf(esconderCursor);
    printarTela();
}

void coisas()
{
    if (kbhit())
    {
        input = getch();
        if (cobratamanho == 0)
        {
            if (input == 'w' || input == 's' || input == 'a' || input == 'd')
            {
                direcao = input;
            }
        }
        else if (((input == 'w') && (!(cobracabecay == cobraraboy[0] + 1))) ||
                 ((input == 's') && (!(cobracabecay == cobraraboy[0] - 1))) ||
                 ((input == 'a') && (!(cobracabecax == cobrarabox[0] + 1))) ||
                 ((input == 'd') && (!(cobracabecax == cobrarabox[0] - 1))))
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
    for (int i = 1; i < cobratamanho; i++)
    {
        if (cobracabecax == cobrarabox[i] && cobracabecay == cobraraboy[i])
        {
            s = false;
            mensagemderrota = 1;
        }
    }
    if ((cobracabecax == 0 || cobracabecax == largura - 1) || (cobracabecay == 0 || cobracabecay == altura - 1))
    {
        cobracabecax = cabecaxanterior;
        cobracabecay = cabecayanterior;
        s = false;
        mensagemderrota = 2;
    }
}

void printarTela()
{
    printf(setCursorIncio);
    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {

            if (y == 0 || y == altura - 1 || x == 0 || x == largura - 1)
            {
                printf(VerdeEscuro);
            }
            else if (y == cobracabecay && x == cobracabecax)
            {
                printf(AzulEscuro);
            }
            else if (y == frutaposy && x == frutaposx)
            {
                printf(Vermelho);
            }
            else
            {
                bool printouRabo = false;
                for (int i = 0; i < cobratamanho; i++)
                {
                    if (y == cobraraboy[i] && x == cobrarabox[i])
                    {
                        printf(AzulmenosEscuro);
                        printouRabo = true;
                        break;
                    }
                }
                if (!printouRabo)
                {
                    printf(VerdeClaro);
                }
            }
        }
        printf(linhaNova);
    }
    printf("\nScore : %d\n", (cobratamanho * 100));
    if (!s)
    {
        if (mensagemderrota == 1)
        {
            printf("Bateu no propio rabo, morreu");
        }
        else if (mensagemderrota == 2)
        {
            printf("Bateu na parede, morreu");
        }
        printf(mostrarCursor);
    }
}

void DesejaReiniciar()
{
        while (kbhit())
        {
            getch();
        }
        printf("\nAperte R para reiniciar, ou aperte ou tecla para sair");
        char resposta = getch();
        if (resposta == 'R' || resposta == 'r')
        {
            reiniciar = true;
            printf("\033[2J\033[H");
        }
        else 
        {
            reiniciar = false;
        }
}
