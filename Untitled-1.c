#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

int main(){
    char s = getch();
    bool sair = true;

    while (sair){
        s = getch();
        Sleep(10);
        printf("%c", s);
}
return 0;
}