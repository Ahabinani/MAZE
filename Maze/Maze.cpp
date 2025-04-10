


#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <math.h>
#include <random>
#include <iostream>
#include <windows.h>
#include <time.h>
#include "Mazetile.h"
#include <winuser.h>
#include "Player.h"
#include "Entity.h"
#include <cstring>
#include <chrono>

//live input
#include <conio.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"
#define PINK    "\x1b[38;2;255;105;180m"
#define LBLUE   "\x1b[38;5;14m"
#define BLACK   "\x1b[38;2;5;5;5m"
#define GRAY    "\x1b[38;2;40;40;40m"
#define WHITE   "\x1b[38;2;250;250;250m"
#define LGREEN  "\x1b[38;2;50;255;0m"

#define LAMP10 "\x1b[38;2;255;200;0m"
#define LAMP9 "\x1b[38;2;255;190;0m"
#define LAMP8 "\x1b[38;2;255;178;0m"
#define LAMP7 "\x1b[38;2;255;143;0m"
#define LAMP6 "\x1b[38;2;255;97;0m"
#define LAMP5 "\x1b[38;2;255;97;0m"
#define LAMP4 "\x1b[38;2;211;70;0m"
#define LAMP3 "\x1b[38;2;153;50;0m"
#define LAMP2 "\x1b[38;2;107;57;36m"
#define LAMP1 "\x1b[38;2;76;55;44m"

#define DASHED "\x1b[9m"
#define BLINKING "\x1b[5m"

#define PLAYER1 "\x1b[38;2;0;255;178m"
#define PLAYER2 "\x1b[38;2;106;0;255m"
#define PLAYER3 "\x1b[38;2;153;255;0m"
#define PLAYER4 "\x1b[38;2;228;255;113m"
#define PLAYER5 "\x1b[48;2;255;255;255;38;2;60;0;50m"
#define PLAYER6 "\x1b[5;38;2;0;60;255m"
#define PLAYER7 "\x1b[38;2;0;0;0;41m"
#define PLAYER8 "\x1b[38;2;255;255;255m"


/*struct sFelder {
    bool bVisited = 0; // vom solver besucht?
    char cType;  // aussehen    ╚ ╔ ╗ ╝ ═ ╬ ║
    bool bConNorth;
    bool bConEast;
    bool bConSouth; //connections definen
    bool bConWest;

};*/



Mazetile aFelder[10000];
Player Players[5];
Entity Bot;
int iMode;  // 1 = steps, 2 = time

char string[500000];

int iPlayerCurrent = 0;
int iInset = 10;
int iSize = 76; //IMMER GERADE default 76
int iOffset = 119 - (iSize + iInset);

int iCollumns = iInset + iOffset + iSize; //Playarea size   DEFAULT KONSOLE 120X30
int iRows = (12 * (2)) + 1;

int iColorOld;
int iSolved = -1;
int iNumberPlayers;

int spacer;

void StartScreen() {

    int caStartScreen[] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,255,204,205,203,205,202,205,206,205,206,205,206,205,202,205,203,205,202,205,206,205,203,205,206,205,202,205,202,205,206,205,205,205,206,205,202,205,202,205,206,205,185,255,204,205,206,205,206,255,204,255,204,205,203,205,206,205,205,255,204,205,202,205,206,255,186,255,185,255,203,205,185,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,204,205,205,255,204,205,202,205,185,255,206,205,205,205,185,255,206,255,186,255,202,255,186,255,206,205,206,205,206,205,185,255,206,205,206,205,206,255,204,205,206,205,206,205,206,205,206,205,206,205,206,205,206,205,185,255,185,255,203,255,186,255,185,255,186,255,185,255,202,205,185,255,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,205,205,206,205,206,205,206,205,206,205,185,255,185,255,185,255,202,255,204,255,204,205,185,255,186,255,206,205,206,205,203,205,185,255,205,205,203,205,185,255,205,205,203,205,202,255,204,205,202,205,202,205,202,255,186,255,206,255,186,255,205,205,205,205,185,255,204,205,206,205,206,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,203,205,206,205,206,205,203,205,202,205,185,255,186,255,206,205,206,205,185,255,206,205,206,205,203,205,206,205,185,255,206,255,204,205,206,205,205,205,206,255,204,205,203,205,206,255,204,205,206,205,206,205,202,205,203,255,204,255,204,255,186,255,202,255,204,205,203,205,202,205,203,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,203,205,185,255,185,255,206,205,206,205,206,205,206,205,205,205,185,255,202,255,186,255,203,205,185,255,185,255,186,255,202,205,206,205,202,205,206,205,206,255,186,255,186,255,202,205,206,205,206,205,205,205,185,255,203,255,186,255,185,255,203,205,203,255,186,255,206,205,206,205,206,205,202,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,205,202,255,204,255,186,255,205,205,205,255,255,255,206,205,185,255,203,205,202,255,204,205,205,205,203,205,206,205,202,205,202,205,206,205,203,205,203,205,206,205,206,205,206,205,206,255,186,255,206,255,186,255,202,255,204,205,185,255,206,255,186,255,206,205,203,205,206,205,205,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,202,205,206,205,203,205,205,205,202,205,203,205,205,205,205,205,202,205,202,205,205,205,205,205,202,205,206,205,206,205,205,205,205,205,202,205,202,205,185,255,204,205,202,205,202,205,205,205,202,205,206,205,203,205,205,205,202,205,202,205,206,205,206,205,206,205,202,205,202,205,205,255,204,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,185,255,204,205,206,205,202,255,204,205,185,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,204,205,185,255,255,255,201,205,187,255,255,255,204,205,185,255,255,255,255,255,255,255,255,255,204,205,185,255,255,255,255,255,255,255,204,205,206,205,203,205,206,205,185,255,186,255,186,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,185,255,186,255,204,205,206,205,205,205,185,255,255,255,201,205,187,255,255,255,201,205,187,255,255,255,204,205,185,255,255,255,186,205,186,255,255,255,204,205,206,205,203,205,203,205,203,205,255,255,204,205,185,255,201,205,205,205,203,205,185,255,204,205,205,205,206,205,206,255,204,205,202,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,204,205,185,255,205,205,206,205,185,255,186,255,255,255,204,205,185,255,255,255,204,205,185,255,255,255,186,255,185,255,255,255,200,205,188,255,255,255,204,205,206,205,206,205,206,205,188,255,255,255,204,205,185,255,200,205,202,205,205,205,206,205,205,205,206,205,205,205,205,205,205,205,205,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,205,206,205,206,205,206,255,186,255,186,255,255,255,186,255,186,255,255,255,186,255,186,255,255,255,204,205,185,255,255,255,201,205,187,255,255,255,204,205,202,205,206,205,188,255,255,255,201,205,206,205,185,255,255,255,255,255,255,255,204,205,185,255,185,255,206,205,203,205,203,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,205,185,255,185,255,204,205,203,205,185,255,255,255,204,205,206,205,205,205,206,205,185,255,255,255,204,205,185,255,255,255,186,255,186,255,255,255,204,205,206,205,188,255,255,255,201,205,185,255,204,205,185,255,201,205,203,205,203,205,206,205,206,205,206,205,185,255,203,205,202,255,204,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,203,255,186,255,206,205,206,255,186,255,186,255,255,255,204,205,202,205,206,205,185,255,186,255,255,255,186,255,185,255,255,255,204,205,185,255,255,255,186,255,185,255,255,255,201,205,202,205,206,255,204,205,185,255,204,205,205,205,185,255,186,255,186,255,204,205,185,255,206,205,203,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,203,255,204,205,202,205,185,255,185,255,185,255,255,255,204,205,202,205,206,205,205,205,185,255,255,255,204,205,185,255,255,255,204,205,185,255,255,255,204,205,185,255,255,205,202,205,205,205,202,205,185,255,186,255,200,205,205,205,205,205,206,205,203,205,202,205,206,205,206,205,203,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,205,206,255,186,255,206,205,206,205,185,255,255,255,204,205,185,255,206,205,206,255,186,255,255,255,186,255,185,255,255,255,204,205,185,255,255,255,204,255,186,255,255,255,255,255,255,255,255,255,204,205,185,255,255,255,255,255,255,255,204,205,206,205,202,205,206,205,202,255,204,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,185,255,186,255,206,205,206,205,203,205,206,205,203,205,185,205,206,205,206,205,206,205,206,205,203,205,206,205,206,205,203,205,206,205,206,205,203,205,206,205,206,205,203,205,203,205,203,205,203,205,185,255,206,205,205,205,205,205,205,205,206,205,202,205,205,205,202,205,206,205,206,205,202,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,205,206,205,206,205,206,205,206,205,203,205,206,255,204,205,185,255,203,205,185,255,206,205,206,255,204,205,185,255,206,205,185,255,206,255,186,255,202,205,203,205,206,255,186,255,185,255,206,205,185,255,206,255,186,255,206,255,186,255,186,255,206,255,186,255,206,205,206,205,206,255,204,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,205,205,206,255,186,255,202,255,204,205,202,255,204,205,203,205,206,255,186,255,185,255,202,205,185,255,185,255,202,205,206,255,204,205,205,205,202,205,206,205,203,205,185,255,202,205,205,205,206,205,206,205,202,205,206,255,186,255,206,205,205,205,205,205,205,205,185,255,202,255,204,255,204,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,202,205,206,205,206,205,202,205,206,255,186,255,202,205,206,205,206,205,206,205,205,255,186,255,204,205,206,205,206,255,204,205,206,205,205,205,205,255,204,205,185,255,202,255,204,255,186,255,203,205,203,255,204,255,186,255,202,205,185,255,203,205,206,255,186,255,206,255,204,205,203,205,205,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,203,205,202,205,185,255,204,205,202,255,204,205,205,205,206,205,202,205,202,205,185,255,202,205,202,205,203,205,206,205,203,205,206,205,206,205,206,205,185,255,186,255,185,255,205,205,185,255,202,255,186,255,203,255,204,205,206,205,185,255,206,205,206,205,202,255,204,205,205,255,186,255,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,255,204,205,206,205,203,205,205,255,186,255,204,205,205,205,185,255,204,205,205,205,206,255,204,205,202,205,203,255,204,205,206,205,202,205,185,255,186,255,205,205,206,205,206,255,204,205,206,205,185,255,206,205,203,205,205,205,206,255,204,205,206,205,185,255,206,205,206,205,206,205,206,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,203,205,206,205,206,255,204,255,186,255,186,255,185,255,203,255,204,205,206,205,206,205,206,255,204,205,206,205,203,205,206,205,206,205,205,205,202,205,206,205,203,205,185,255,206,205,203,255,186,255,186,255,206,205,203,205,205,205,206,205,203,205,206,205,206,205,206,205,206,205,205,205,185,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,206,205,203,205,185,255,205,205,205,255,186,255,202,205,206,255,186,255,206,205,185,255,202,205,206,205,205,255,186,255,185,255,206,205,203,205,206,205,206,205,185,255,202,255,186,255,203,205,206,205,206,205,185,255,205,255,204,205,206,205,206,205,206,255,186,255,205,205,205,205,206,205,205,255,219,600,255,255,255,255,255,255,255,255,255,255,219,255,205,205,205,205,206,255,186,255,205,205,205,205,202,205,206,205,185,255,206,255,204,205,205,205,203,205,202,205,206,205,206,205,185,255,205,205,202,205,185,255,202,205,202,205,206,205,206,205,206,205,206,205,185,255,206,205,203,255,204,205,206,205,206,205,203,255,186,255,204,205,206,205,202,255,219,600,255,255,255,255,255,255,255,255,255,255,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,21,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,600,999 };
    int iStartChar = 0;
    //ich geb hier auf ;-;
    for (int iStartChar = 0; caStartScreen[iStartChar] != 999; iStartChar++) {
        if (caStartScreen[iStartChar] == 600) { printf("\n"); }
        else if (caStartScreen[iStartChar] == 219) { printf(GRAY"%c" RESET, caStartScreen[iStartChar]); }
        else { printf(RED "%c" RESET, caStartScreen[iStartChar]); }
    }


    Sleep(5000);
}

void PlayerSetup() {

    system("cls");
    printf("Number Of Players(1-4): ");

    while (true) {
        if (scanf("%i", &iNumberPlayers) == 1) {
            if (iNumberPlayers >= 1 && iNumberPlayers <= 4) { break; }
            else { printf(RED "Invalid Input. \n" RESET); }
        }
        else {
            while (getchar() != '\n') {}
            printf(RED "Invalid Input. \n" RESET);
        }
    }
    const char* caPCOLORS[8] = { PLAYER1,PLAYER2,PLAYER3,PLAYER4,PLAYER5,PLAYER6,PLAYER7,PLAYER8 };
    for (int i = 0; i < iNumberPlayers; i++) {
        system("cls");
        printf("Player %i insert your name (max 8): ", i + 1);
    GetName:
        scanf("%s", &Players[i].caDisplayName);
        fflush(stdin);
        getchar();
        if (strlen(Players[i].caDisplayName) > 8) { printf(RED "Name too long! \n" RESET); goto GetName; }
        printf("Player %i choose a color: ", i + 1);
        for (int c = 0; c < 8; c++) {
            for (int j = 0; j < i; j++) {
                if (c == Players[j].iDisplayColor) { printf(DASHED ""); break; }
            }

            printf("%s %i " RESET, caPCOLORS[c], c + 1);
        }
    GetColor:
        if (scanf("%i", &Players[i].iDisplayColor) == 1) {
            --Players[i].iDisplayColor;
            getchar();
            if (Players[i].iDisplayColor < 0 || Players[i].iDisplayColor > 7) { printf(RED "Invalid Input. \n" RESET); goto GetColor; }
            for (int k = 0; k < i; k++) { if (Players[i].iDisplayColor == Players[k].iDisplayColor) { printf(RED "Color in use by %s.\n" RESET, Players[k].caDisplayName); goto GetColor; } }
        }
        else {
            while (getchar() != '\n') {}
            printf(RED "Invalid Input.\n" RESET);
            goto GetColor;
        }

    }
    system("cls");
    printf("Move Battle (Bot) (1) / Time Chase (2): ");
    scanf("%i", &iMode);
}

int GetID(int x, int y) {   //ID von tile mit x/y koordinate (beginnend 0,0 top left vom maze)
    int ID = (((y + 1) * iCollumns) + (x + iInset)) /*für eine reihe platz at top + 1 collumns*/;
    return ID;
}
/*Direction 0 U, 1 R, 2 D, 3 L*/
int Check(int iDirection, int iX, int iY) {

    switch (iDirection) {
    case 0:
        switch (aFelder[GetID(iX, iY)].iType) {
        case 185:
        case 186:
        case 188:
        case 200:
        case 202:
        case 204:
        case 206:
            return 1;
        default: return 0;
        }
    case 1:
        switch (aFelder[GetID(iX, iY)].iType) {
        case 200:
        case 201:
        case 202:
        case 203:
        case 204:
        case 205:
        case 206:
        case 175:
            return 1;
        default: return 0;
        }
    case 2:
        switch (aFelder[GetID(iX, iY)].iType) {
        case 185:
        case 186:
        case 187:
        case 201:
        case 203:
        case 204:
        case 206:
            return 1;
        default: return 0;
        }
    case 3:
        switch (aFelder[GetID(iX, iY)].iType) {
        case 185:
        case 187:
        case 188:
        case 202:
        case 203:
        case 205:
        case 206:
        case 175:
            return 1;
        default: return 0;
        }


    }
}

void Connector(int ixCheck, int iyCheck) {
    int ixCheckL = ixCheck - 1;
    int ixCheckR = ixCheck + 1;
    bool bConnR = false;
    bool bConnL = false;

    bConnL = true;

    bConnR = Check(3, ixCheckR, iyCheck);
    bConnL = Check(1, ixCheckL, iyCheck);



    if (((bConnR == true) && (bConnL == true))) { aFelder[GetID(ixCheck, iyCheck)].iType = 205; aFelder[GetID(ixCheck, iyCheck)].iColor = 1; }

    else { aFelder[GetID(ixCheck, iyCheck)].iType = ' '; }
}

void Mazegen() {
    srand(time(NULL));
    int acZeichen[11] = { 175,219, /*200,201,187,188,*/205, 206, 206, 186, 206, 185, 202, 203, 204 }; //'╚', '╔', '╗', '╝', '═', '╬', '║' , ' ' , '╣' , '╠ ', '╦' , '╩'




    for (int x = 0; x <= iSize; x += 2) {
        for (int y = 0; y <= iRows; y++) {
            if (x == 0 || x == iSize || y == 0 || y == iRows) {
                aFelder[GetID(x, y)].iType = acZeichen[1];
                aFelder[GetID(x, y)].iColor = 4;
            }
            else {
                aFelder[GetID(x, y)].iType = acZeichen[(rand() % 9) + 2]; //hinterer value erhöhen für UI zeichen
                aFelder[GetID(x, y)].iColor = 1;
            }
            aFelder[GetID(x, y)].bVisited = false;

        }
    }


    for (int x = 1; x < iSize; x += 2) {
        for (int y = 0; y <= iRows; y++) {
            if (y == 0 || y == iRows) { aFelder[GetID(x, y)].iType = acZeichen[1]; aFelder[GetID(x, y)].iColor = 4; }
            else { Connector(x, y); }
            aFelder[GetID(x, y)].bVisited = false;
        }
    }

    //start / ende
    for (int x = -9; x <= 0; x++) { aFelder[GetID(x, iRows / 2)].iType = 175; aFelder[GetID(x, iRows / 2)].iColor = 30 + x; }
    for (int x = iSize + 9; x >= iSize; x--) { aFelder[GetID(x, iRows / 2)].iType = 175; aFelder[GetID(x, iRows / 2)].iColor = 30 - (x - iSize); }
    Connector(1, iRows / 2);
    Connector(iSize - 1, iRows / 2);
}

void UIPrinter(int iXprint, int iYprint, const char* acWord, int iColor, int iStyle) {
    for (int i = 0; iXprint < iXprint + strlen(acWord) - i; iXprint++, i++) {
        int iCurrentField = GetID(iXprint, iYprint); aFelder[iCurrentField].iType = acWord[i]; aFelder[iCurrentField].iColor = iColor; aFelder[iCurrentField].iStyle = iStyle;
    }
}

void UI(int iMazesUI) {

    //for (int x = iSize + 2, l = 0; x < iSize + 7; x++, l++) { aFelder[GetID(x, 4)].iType = acUITEXT[l]; aFelder[GetID(x, 4)].iColor = 5; }
    UIPrinter(iSize + 3, 4, "MAZES", 5, 0);
    UIPrinter(iSize + 3, 5, "TESTED:", 5, 0);
    //for (int x = iSize + 2, l = 6; x < iSize + 9; x++, l++) { aFelder[GetID(x, 5)].iType = acUITEXT[l]; aFelder[GetID(x, 5)].iColor = 5; }    //Nr Mazes
    for (int x = iSize + 9; x > iSize + 1; x--) { if (iMazesUI >= 1) { aFelder[GetID(x, 6)].iType = '0' + (iMazesUI % 10); iMazesUI = iMazesUI / 10; } aFelder[GetID(x, 6)].iColor = 5; }


    UIPrinter(iSize + 3, iRows / 2 + 3, "CONTROLS:", 5, 0);
    aFelder[GetID(iSize + 14, iRows / 2 + 4)].iType = 'W'; aFelder[GetID(iSize + 14, iRows / 2 + 4)].iColor = 5;
    aFelder[GetID(iSize + 14, iRows / 2 + 5)].iType = 186; aFelder[GetID(iSize + 14, iRows / 2 + 5)].iColor = 5;
    UIPrinter(iSize + 10, iRows / 2 + 6, "A\xCD\xCD\xCD\xCE\xCD\xCD\xCD""D", 5, 0);
    aFelder[GetID(iSize + 14, iRows / 2 + 7)].iType = 186; aFelder[GetID(iSize + 14, iRows / 2 + 7)].iColor = 5;
    aFelder[GetID(iSize + 14, iRows / 2 + 8)].iType = 'S'; aFelder[GetID(iSize + 14, iRows / 2 + 8)].iColor = 5;
    UIPrinter(iSize + 22, iRows / 2 + 8, "SKIP PLAYER", 5, 0);
    UIPrinter(iSize + 25, iRows / 2 + 9, "[Q]", 5, 0);

    UIPrinter(iSize + 15, 4, "PLAYERS:", 5, 0);

    for (int i = 0; i < iNumberPlayers; i++) {
        const char* currentPlayerName = Players[i].caDisplayName;
        int iNameLen = strlen(currentPlayerName);
        for (int j = 0; j < iNameLen; j++) { aFelder[GetID(iSize + 23 - iNameLen + j, 5 + i)].iType = currentPlayerName[j]; aFelder[GetID(iSize + 23 - iNameLen + j, 5 + i)].iColor = Players[i].iDisplayColor + 10; }
    }
}

void PlayerMove() {
    char cInput{};
Input:
    //scanf("%c", &cInput);
    cInput = (char)_getch();

    aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iColor = iColorOld;

    switch (cInput) {
    case 'w':
        if (Check(0, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) {
            --Players[iPlayerCurrent].iCoordY;
            if (Check(2, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) { aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iPlayerVisited = iPlayerCurrent; Players[iPlayerCurrent].iMoveCount++; break; }
            else {
                ++Players[iPlayerCurrent].iCoordY;
                goto Input;
            }
        }
        else { goto Input; }

    case 's':
        if (Check(2, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) {
            ++Players[iPlayerCurrent].iCoordY;
            if (Check(0, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) { aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iPlayerVisited = iPlayerCurrent; Players[iPlayerCurrent].iMoveCount++; break; }
            else {
                --Players[iPlayerCurrent].iCoordY;
                goto Input;
            }
        }
        else { goto Input; }
    case 'a':
        if (Check(3, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) {
            Players[iPlayerCurrent].iCoordX -= 2;
            if (Check(1, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) { aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iPlayerVisited = iPlayerCurrent; aFelder[GetID(Players[iPlayerCurrent].iCoordX - 1, Players[iPlayerCurrent].iCoordY)].iPlayerVisited = iPlayerCurrent; Players[iPlayerCurrent].iMoveCount += 2; break; }
            else {
                Players[iPlayerCurrent].iCoordX += 2;
                goto Input;
            }
        }
        else { goto Input; }
    case 'd':
        if (Check(1, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) {
            Players[iPlayerCurrent].iCoordX += 2;
            if (Check(3, Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY) == 1) { aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iPlayerVisited = iPlayerCurrent; aFelder[GetID(Players[iPlayerCurrent].iCoordX + 1, Players[iPlayerCurrent].iCoordY)].iPlayerVisited = iPlayerCurrent; Players[iPlayerCurrent].iMoveCount += 2; break; }
            else {
                Players[iPlayerCurrent].iCoordX -= 2;
                goto Input;
            }
        }
        else { goto Input; }
    case 'q': Players[iPlayerCurrent].iCoordX = iSize; Players[iPlayerCurrent].iCoordY = iRows / 2; Players[iPlayerCurrent].iMoveCount = 999; break;
    case '\n':  goto Input;
    default: goto Input;
    }

    iColorOld = aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iColor;
    aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iColor = Players[iPlayerCurrent].iDisplayColor + 10;

}

int Solver(int iCurrX, int iCurrY, int iMove) {                                                     //Trackt Movecount garnicht??????
    aFelder[GetID(iCurrX, iCurrY)].bVisited = true;                                                 //Pls Fix
    if (iCurrX == iSize) {                                                         //-07:09 AM 03.01 garkein bock mehr
        return iMove;
    }
    if (iSolved != -1) {
        aFelder[GetID(iCurrX, iCurrY)].bSolution = 1; return iSolved;
    }
    if (Check(1, iCurrX, iCurrY) == 1) {
        if (Check(3, iCurrX + 1, iCurrY)) {
            if (aFelder[GetID(iCurrX + 1, iCurrY)].bVisited == false) {
                iSolved = Solver(iCurrX + 1, iCurrY, iMove + 1);
            }
        }
    }
    if (iSolved != -1) {
        aFelder[GetID(iCurrX, iCurrY)].bSolution = 1; return iSolved;
    }
    if (Check(2, iCurrX, iCurrY) == 1) {
        if (Check(0, iCurrX, iCurrY + 1)) {
            if (aFelder[GetID(iCurrX, iCurrY + 1)].bVisited == false) {
                iSolved = Solver(iCurrX, iCurrY + 1, iMove + 1);
            }
        }
    }
    if (iSolved != -1) {
        aFelder[GetID(iCurrX, iCurrY)].bSolution = 1; return iSolved;
    }
    if (Check(0, iCurrX, iCurrY) == 1) {
        if (Check(2, iCurrX, iCurrY - 1)) {
            if (aFelder[GetID(iCurrX, iCurrY - 1)].bVisited == false) {
                iSolved = Solver(iCurrX, iCurrY - 1, iMove + 1);
            }
        }
    }
    if (iSolved != -1) {
        aFelder[GetID(iCurrX, iCurrY)].bSolution = 1; return iSolved;
    }
    if (Check(3, iCurrX, iCurrY) == 1) {
        if (Check(1, iCurrX - 1, iCurrY)) {
            if (aFelder[GetID(iCurrX - 1, iCurrY)].bVisited == false) {
                iSolved = Solver(iCurrX - 1, iCurrY, iMove + 1);
            }
        }
    }
    if (iSolved != -1) {
        aFelder[GetID(iCurrX, iCurrY)].bSolution = 1; return iSolved;
    }
    return iSolved;
}

void Printscreen(bool bHidden) {
    //system("cls");
    printf("\033[0;0H");
    for (int y = -1; y <= iRows; y++)
    {
        for (int x = -iInset; x <= iSize + iOffset; x++)
        {
            switch (aFelder[GetID(x, y)].iColor) {
            case 0: sprintf(string + strlen(string), BLACK ""); break;
            case 1: sprintf(string + strlen(string), RED ""); break;
            case 2: sprintf(string + strlen(string), LBLUE ""); break;
            case 3: sprintf(string + strlen(string), PINK ""); break;
            case 4: sprintf(string + strlen(string), GRAY ""); break;
            case 5: sprintf(string + strlen(string), WHITE ""); break;
            case 6: sprintf(string + strlen(string), LGREEN ""); break;

                //Players
            case 10: sprintf(string + strlen(string), PLAYER1 ""); break;
            case 11: sprintf(string + strlen(string), PLAYER2 ""); break;
            case 12: sprintf(string + strlen(string), PLAYER3 ""); break;
            case 13: sprintf(string + strlen(string), PLAYER4 ""); break;
            case 14: sprintf(string + strlen(string), PLAYER5 ""); break;
            case 15: sprintf(string + strlen(string), PLAYER6 ""); break;
            case 16: sprintf(string + strlen(string), PLAYER7 ""); break;
            case 17: sprintf(string + strlen(string), PLAYER8 ""); break;

            case 21: sprintf(string + strlen(string), LAMP1 ""); break; //Lamps
            case 22: sprintf(string + strlen(string), LAMP2 ""); break;
            case 23: sprintf(string + strlen(string), LAMP3 ""); break;
            case 24: sprintf(string + strlen(string), LAMP4 ""); break;
            case 25: sprintf(string + strlen(string), LAMP5 ""); break;
            case 26: sprintf(string + strlen(string), LAMP6 ""); break;
            case 27: sprintf(string + strlen(string), LAMP7 ""); break;
            case 28: sprintf(string + strlen(string), LAMP8 ""); break;
            case 29: sprintf(string + strlen(string), LAMP9 ""); break;
            case 30: sprintf(string + strlen(string), LAMP10 ""); break;

            }
            switch (aFelder[GetID(x, y)].iStyle) {
            case 0: break;
            case 1: sprintf(string + strlen(string), BLINKING ""); break;
            case 2: sprintf(string + strlen(string), DASHED ""); break;
            }

            if (bHidden == 0) { sprintf(string + strlen(string), "%c" RESET, aFelder[GetID(x, y)].iType); }
            if (bHidden == 1) {
                if (y == iRows / 2 && x == iSize / 2 - 6) { sprintf(string + strlen(string), RED "PUSH TO START" RESET); x = iSize / 2 + 6; }
                else if (x > 0 && x < iSize && y > 0 && y < iRows) { sprintf(string + strlen(string), GRAY "%c" RESET, 178); }
                else sprintf(string + strlen(string), "%c" RESET, aFelder[GetID(x, y)].iType);
            }
        }
        sprintf(string + strlen(string), "\n");
    }
    printf("%s", string);
    sprintf(string, "");
}

void EndSequence() {
    for (int x = 0; x <= iSize; x++) {
        for (int y = 0; y <= iRows; y++) {
            if (aFelder[GetID(x, y)].bSolution == 1) {
                aFelder[GetID(x, y)].iColor = 6;
            }
            if (aFelder[GetID(x, y)].iPlayerVisited != -1) {
                aFelder[GetID(x, y)].iColor = Players[aFelder[GetID(x, y)].iPlayerVisited].iDisplayColor + 10;

            }
        }
    }


    for (int i = 0; i < iNumberPlayers; i++) {
        for (int j = i + 1; j < iNumberPlayers; j++) {
            if (((Players[i].iMoveCount > Players[j].iMoveCount) && iMode == 1) || ((Players[i].tTime > Players[j].tTime)&&iMode == 2)) {
                Players[4] = Players[i];
                Players[i] = Players[j];
                Players[j] = Players[4];
            }
        }
    }
    for (int i = 0; i < iNumberPlayers; i++) {
        const char* currentPlayerName = Players[i].caDisplayName;
        int iNameLen = strlen(currentPlayerName);
        for (int j = 0; j < iNameLen; j++) {
            aFelder[GetID(iSize + 23 - iNameLen + j, 5 + i)].iType = currentPlayerName[j];
            aFelder[GetID(iSize + 23 - iNameLen + j, 5 + i)].iColor = Players[i].iDisplayColor + 10;
        }
        if (iMode == 1) {
            for (int x = iSize + 27; x > iSize + 24; x--) {
                if (Players[i].iMoveCount >= 1) {
                    aFelder[GetID(x, i + 5)].iType = '0' + (Players[i].iMoveCount % 10);
                    Players[i].iMoveCount /= 10;
                    aFelder[GetID(x, i + 5)].iColor = Players[i].iDisplayColor + 10;
                }
            }
        }
        else if (iMode == 2) {
            for (int x = iSize + 27; x > iSize + 24; x--) {
                aFelder[GetID(x, i + 5)].iType = '0' + (Players[i].tTime).count();
                Players[i].tTime -= (Players[i].tTime);
                aFelder[GetID(x, i + 5)].iColor = Players[i].iDisplayColor + 10;

            }

        }
    }
    UIPrinter(iSize + 21, 6 + iNumberPlayers, "BOT", 6, 0);
    for (int i = iSize + 20; i <= iSize + 30; i++) { aFelder[GetID(i, iNumberPlayers + 4)].iStyle = 0; }
    for (int x = iSize + 27; x > iSize + 24; x--) {
        if (iSolved >= 1) {
            aFelder[GetID(x, 6 + iNumberPlayers)].iType = '0' + (iSolved % 10);
            iSolved /= 10;
            aFelder[GetID(x, 6 + iNumberPlayers)].iColor = 6;
        }
    }
    Printscreen(0);
}


int main()
{
    StartScreen();
    PlayerSetup();


    printf("Starting");
    int iMazesTested = 0;
    while (iSolved == -1) {
        printf("Generating Maze %i\n", iMazesTested + 1);
        Mazegen();
        printf("Generated Maze %i\n", iMazesTested + 1);
        Bot.iCoordX = 0;
        Bot.iCoordY = iRows / 2;
        Bot.iMoveCount = 0;
        iSolved = -1;
        printf("Testing Maze %i\n", iMazesTested + 1);
        Solver(Bot.iCoordX, Bot.iCoordY, Bot.iMoveCount);
        printf("Tested Maze %i\n", iMazesTested + 1);
        iMazesTested++;
    }
    printf("Generating UI");
    UI(iMazesTested);
    printf("Generated UI");

    //Gameloop
    for (iPlayerCurrent = 0; iPlayerCurrent < iNumberPlayers; iPlayerCurrent++) {
        //highlight current player
        for (int i = 0; i < iNumberPlayers; i++) {
            if (i == iPlayerCurrent) {
                for (int x = iSize + 15; x <= iSize + 25; x++) { aFelder[GetID(x, 5 + i)].iStyle = 1; }
                aFelder[GetID(iSize + 25, 5 + i)].iType = 174; aFelder[GetID(iSize + 25, 5 + i)].iColor = Players[iPlayerCurrent].iDisplayColor + 10;
            }
            else if (i < iPlayerCurrent) { for (int x = iSize + 15; x <= iSize + 25; x++) { aFelder[GetID(x, 5 + i)].iStyle = 0; } aFelder[GetID(iSize + 25, 5 + i)].iType = '?'; }
        }

        Players[iPlayerCurrent].iCoordX = 0;
        Players[iPlayerCurrent].iCoordY = iRows / 2;
        aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iColor = Players[iPlayerCurrent].iDisplayColor + 10;
        iColorOld = 30;
        system("cls");
        Printscreen(1);
        _getch();
        //scanf("%[^\n]%*c");
        //start Timer
        auto startTime = std::chrono::system_clock::now();

        while (Players[iPlayerCurrent].iCoordX < iSize) {
            Printscreen(0);

            PlayerMove();

        }
        std::chrono::duration<double> endTime{std::chrono::system_clock::now() - startTime};
        Players[iPlayerCurrent].tTime = endTime;
        printf("%i", endTime);
        _getch();
        aFelder[GetID(Players[iPlayerCurrent].iCoordX, Players[iPlayerCurrent].iCoordY)].iColor = iColorOld;

    }

    EndSequence();
    //reveal Anzahl züge + Zeiten der Spieler
    //(Zeig Wege)
    //Announce Gewinner
//start screen
    getchar();
}
