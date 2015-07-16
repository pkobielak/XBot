#include <windows.h>
#include <time.h>
#include <iostream>
#include <string>
#define POZA_ZAKRESEM znak<48 || znak>57 && znak<65 || znak>90 && znak<97 || znak>122

using namespace std;

int main()
{
    string randomname = "";
    srand(time(NULL));
    int strsize = (rand()%5)+7;
    for(int i = 0; i<strsize; i++)
    {
        char znak = 0;
        while(POZA_ZAKRESEM)
            znak = rand()%160;
        randomname+=znak;
    }
    randomname+=".exe";
    CopyFileA("xbot.exe",randomname.c_str(),false);
}
