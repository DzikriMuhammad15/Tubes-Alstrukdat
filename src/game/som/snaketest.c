#include <stdio.h>
#include "listdp.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "wordmachine.h"

boolean SearchPoint(List L, int X, int Y)
{
    address S = First(L);
    boolean found = true;
    while (S != Nil && found)
    {
        if (Absis(S) == X && Ordinat(S) == Y)
        {
            found = false;
        }
        S = Next(S);
    }
    return found;
}

boolean SearchAbsis(List L, int X)
{
    address S = First(L);
    boolean found = true;
    while (S != Nil && found)
    {
        if (Absis(S) == X)
        {
            found = false;
        }
        S = Next(S);
    }
    return found;
}

address PointAddress(List L, int i, int j)
{
    address P = First(L);
    boolean found = false;
    while (P != Nil && !found)
    {
        if (Absis(P) == i && Ordinat(P) == j)
        {
            found = true;
        }
        else
        {
            P = Next(P);
        }
    }
    if (found)
    {
        return P;
    }
    else
    {
        return Nil;
    }
}

void CreateSnake(List *L)
{
    CreateEmptyLDP(L);
    // srand(time(NULL));
    address P1 = AlokasiLDP(72); // 72 ASCII "H
    address P2 = AlokasiLDP(1);
    address P3 = AlokasiLDP(2);

    Absis(P1) = rand() % 5;
    Ordinat(P1) = rand() % 5;

    if (Absis(P1) == 0)
    {
        if (Ordinat(P1) == 0)
        {
            Absis(P2) = Absis(P1);
            Absis(P3) = Absis(P1);
            Ordinat(P2) = Ordinat(P1) + 1;
            Ordinat(P3) = Ordinat(P1) + 2;
        }
        else
        {
            Absis(P2) = Absis(P1);
            Absis(P3) = Absis(P1);
            if (Ordinat(P1) == 1)
            {
                Ordinat(P2) = Ordinat(P1) + 1;
                Ordinat(P3) = Ordinat(P1) + 2;
            }
            else
            {
                Ordinat(P2) = Ordinat(P1) - 1;
                Ordinat(P3) = Ordinat(P1) - 2;
            }
        }
    }
    else
    {
        if (Ordinat(P1) == 0)
        {
            if (Absis(P1) == 1)
            {
                Absis(P2) = Absis(P1) - 1;
                Absis(P3) = Absis(P1) - 1;
                Ordinat(P2) = Ordinat(P1);
                Ordinat(P3) = Ordinat(P1) + 1;
            }
            else
            {
                Absis(P2) = Absis(P1) - 1;
                Absis(P3) = Absis(P1) - 2;
                Ordinat(P2) = Ordinat(P1);
                Ordinat(P3) = Ordinat(P1);
            }
        }
        else
        {
            Absis(P2) = Absis(P1) - 1;
            Ordinat(P2) = Ordinat(P1);
            if (Absis(P2) == 0)
            {
                Absis(P3) = Absis(P2);
                Ordinat(P3) = Ordinat(P2) - 1;
            }
            else
            {
                Absis(P3) = Absis(P2) - 1;
                Ordinat(P3) = Ordinat(P2);
            }
        }
    }
    InsertLastLDP(L, P1);
    InsertLastLDP(L, P2);
    InsertLastLDP(L, P3);
}

void move(List *L, char *input)
{
    char *atas = "w";
    char *kiri = "a";
    char *bawah = "s";
    char *kanan = "d";
    address P = Last(*L);
    POINT temp;
    if (IsStrEq(input, atas))
    {
        temp = (*Prev(P)).coor;
        while (Prev(P) != Nil)
        {
            (*P).coor = temp;
            P = (P)->prev;
            if (Prev(P) != Nil)
            {
                temp = (*Prev(P)).coor;
            }
        }
    }
    else if (IsStrEq(input, bawah))
    {
        temp = (*Prev(P)).coor;
        while (Prev(P) != Nil)
        {
            (*P).coor = temp;
            P = (P)->prev;
            if (Prev(P) != Nil)
            {
                temp = (*Prev(P)).coor;
            }
        }
    }
    else if (IsStrEq(input, kanan))
    {
        temp = (*Prev(P)).coor;
        while (Prev(P) != Nil)
        {
            (*P).coor = temp;
            P = (P)->prev;
            if (Prev(P) != Nil)
            {
                temp = (*Prev(P)).coor;
            }
        }
    }
    else if (IsStrEq(input, kiri))
    {
        temp = (*Prev(P)).coor;
        while (Prev(P) != Nil)
        {
            (*P).coor = temp;
            P = (P)->prev;
            if (Prev(P) != Nil)
            {
                temp = (*Prev(P)).coor;
            }
        }
    }
    address a = First(*L);
    if (IsStrEq(input, kiri))
    {
        if (Absis(a) == 0)
        {
            Absis(a) = 4;
        }
        else
        {
            Absis(a) -= 1;
        }
    }
    else if (IsStrEq(input, kanan))
    {
        if (Absis(a) == 4)
        {
            Absis(a) = 0;
        }
        else
        {
            Absis(a) += 1;
        }
    }
    else if (IsStrEq(input, atas))
    {
        if (Ordinat(a) == 0)
        {
            Ordinat(a) = 4;
        }
        else
        {
            Ordinat(a) -= 1;
        }
    }
    else if (IsStrEq(input, bawah))
    {
        if (Ordinat(a) == 4)
        {
            Ordinat(a) = 0;
        }
        else
        {
            Ordinat(a) += 1;
        }
    }
}

void makeMeteor(POINT *meteor, POINT food)
{
    // srand(time(NULL));

    int a = rand() % 5;
    int b = rand() % 5;
    boolean found;
    found = false;
    int idx = 0;
    while (!found)
    {
        if (a == food.x && b == food.y)
        {
            if (idx % 3 == 1)
            {
                a = (a - 1) % 5;
                b = (b + 1) % 5;
            }
            else if (idx % 3 == 0)
            {
                a = (a + 1) % 5;
                b = (b - 1) % 5;
            }
            else
            {
                a = (a + 1) % 5;
                b = (b + 1) % 5;
            }
        }
        else
        {
            found = true;
            meteor->x = a;
            meteor->y = b;
        }

        if (a < 0 || b < 0)
        {
            a = rand() % 5;
            b = rand() % 5;
        }
        idx++;
    }
}

void makeObstacle(List L, POINT *obstacle)
{
    // srand(time(NULL));

    int a = rand() % 5;
    int b = rand() % 5;

    boolean found;
    found = false;

    int i = 0;

    while (!found)
    {
        if (SearchPoint(L, a, b))
        {
            found = true;
            obstacle->x = a;
            obstacle->y = b;
        }
        else
        {
            if (i % 3 == 1)
            {
                a = (a - 1) % 4;
                b = (b + 1) % 4;
            }
            else if (i % 3 == 0)
            {
                a = (a + 1) % 4;
                b = (b - 1) % 4;
            }
            else
            {
                a = (a + 1) % 4;
                b = (b + 1) % 4;
            }
            if (a < 0 || b < 0)
            {
                a = rand() % 4;
                b = rand() % 4;
            }
            i++;
        }
    }
}

void makeFood(POINT *food, List L, POINT obstacle)
{
    // srand(time(NULL));

    int a = rand() % 5;
    int b = rand() % 5;

    boolean found;
    found = false;

    int i = 0;

    while (!found)
    {
        if (SearchPoint(L, a, b) && a != obstacle.x && b != obstacle.y)
        {
            found = true;
            (*food).x = a;
            (*food).y = b;
        }
        else
        {
            if (i % 3 == 1)
            {
                a = (a - 1) % 5;
                b = (b + 1) % 5;
            }
            else if (i % 3 == 0)
            {
                a = (a + 1) % 5;
                b = (b - 1) % 5;
            }
            else
            {
                a = (a + 1) % 5;
                b = (b + 1) % 5;
            }
        }
        if (a < 0 || b < 0)
        {
            a = rand() % 5;
            b = rand() % 5;
        }
        i++;
    }
}

boolean foodEaten(List *L, POINT food)
{
    return ((*First(*L))).coor.x == food.x && ((*First(*L)).coor.y == food.y);
}

void kenaMeteor(List *L, POINT food, POINT meteor)
{
    address a;
    a = First(*L);
    address b;
    b = Last(*L);
    boolean found;
    found = false;

    while (a != Nil && !found)
    {
        if (Absis(a) == meteor.x && Ordinat(b) == meteor.y)
        {
            found = true;
        }
        a = Next(a);
    }

    if (found)
    {
        if (a == Nil)
        {
            DelLastLDP(L, &b);
        }
        else if (a == Next(First(*L)))
        {
            DelLastLDP(L, &b);
            DelFirstLDP(L, &b);
            printf("Meteor mengenai bagian Head snake. Permainan berakhir\n");
        }
        else
        {
            while (b != Prev(a))
            {
                Info(b) = Prev(b)->info;
                b = Prev(b);
            }
            DelBeforeLDP(L, &b, a);
        }
    }
}

boolean endGame(List L, POINT meteor, POINT obstacle)
{
    address a;
    a = First(L);
    boolean found = false;
    a = Next(a);

    while (!found && a != Nil)
    {
        if (Absis(a) == Absis(First(L)) && Ordinat(a) == Ordinat(First(L)))
        {
            found = true;
        }
        a = Next(a);
    }
    if (!found)
    {
        address check = First(L);
        if ((Info(check) != 'H'))
        {
            printf("DUAARRRRRR Kepala snake terkena meteor\n");
            return true;
        }
        else if (Absis(First(L)) == obstacle.x && Ordinat(First(L)) == obstacle.y)
        {
            printf("HAHAHA Kepala snake menabrak obstacle\n");
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        printf("YOU LOSE....Kepala snake menabrak badannya sendiri\n");
        return found;
    }
}

void printMap(List L, POINT food, POINT meteor, POINT obstacle)
{

    int i, j;
    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 11; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                printf("%c", 254);
            }
            else if (i % 2 == 0)
            {
                printf("%c%c%c", 205, 205, 205);
            }
            else if (j % 2 == 0)
            {
                printf("%c", 186);
            }
            else if (food.x == ((j + 1) / 2) - 1 && food.y == ((i + 1) / 2) - 1)
            {
                printf(" o ");
            }
            else if (meteor.x == ((j + 1) / 2) - 1 && meteor.y == ((i + 1) / 2) - 1)
            {
                printf(" M ");
            }
            else if (obstacle.x == ((j + 1) / 2) - 1 && obstacle.y == ((i + 1) / 2) - 1)
            {
                printf(" ! ");
            }
            else if (PointAddress(L, ((j + 1) / 2) - 1, ((i + 1) / 2) - 1))
            {
                if (Info(PointAddress(L, ((j + 1) / 2) - 1, ((i + 1) / 2) - 1)) == 72)
                {
                    printf(" %c ", Info(PointAddress(L, ((j + 1) / 2) - 1, ((i + 1) / 2) - 1)));
                }
                else
                {
                    if (Info(PointAddress(L, ((j + 1) / 2) - 1, ((i + 1) / 2) - 1)) < 9)
                    {
                        printf(" %d ", Info(PointAddress(L, ((j + 1) / 2) - 1, ((i + 1) / 2) - 1)));
                    }
                    else
                    {
                        printf("%d ", Info(PointAddress(L, ((j + 1) / 2) - 1, ((i + 1) / 2) - 1)));
                    }
                }
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
}



boolean thereisBody(List L, char* input){
    address p;
    p = First(L);

    char* ei ="a";
    char* di ="d";
    char* wry = "w";
    char* ice = "s";

    if(IsStrEq(input,ei)){
        if(Info(PointAddress((L),Absis(p)-1,Ordinat(p))) < 25){
            return true;
        }
        else{
            return false;
        }
    }
    else if(IsStrEq(input,di)){
        if(Info(PointAddress((L),Absis(p)+1,Ordinat(p))) < 25){
            return true;
        }
        else{
            return false;
        }        
    }
    else if(IsStrEq(input,wry)){
        if(Info(PointAddress((L),Absis(p),Ordinat(p)+1)) < 25){
            return true;
        }
        else{
            return false;
        }        
    }
    else if(IsStrEq(input,ice)){
        if(Info(PointAddress((L),Absis(p),Ordinat(p)-1)) < 25){
            return true;
        }
        else{
            return false;
        }        
    }
}

int main()
{
    List L;
    ElmtList ekorbaru;
    char *input;
    POINT obstacle, food, meteor;
    boolean kena = false;
    int turn = 1;
    int score;

    food.x = Undefined;
    food.y = Undefined;
    meteor.x = Undefined;
    meteor.y = Undefined;

    char *we = "w";
    char *ah = "a";
    char *es = "s";
    char *de = "d";
    // srand(time(NULL));

    printf("Selamat datang di snake on meteor!\n");
    printf("\n");
    printf("Mengenerate peta,snake dan makanan...\n");
    printf("\n");
    printf("Berhasil digenerate!\n");
    printf("\n");
    printf("__________________________________________\n");
    printf("\n");
    printf("Berikut merupakan peta permainan!\n");

    CreateSnake(&L);
    makeObstacle(L, &obstacle);
    makeFood(&food, L, obstacle);
    printMap(L, food, meteor, obstacle);

    while (!kena)
    {
        printf("Turn %d:\n", turn);
        printf("Silahkan masukkan command anda: ");
        input = scaninput();
        if (IsStrEq(input, we) || IsStrEq(input, ah) || IsStrEq(input, es) || IsStrEq(input, de))
        {
            if(!thereisBody(L,input)){
                move(&L, input);
                if (foodEaten(&L, food))
                {
                    ekorbaru = *(Last(L));
                    address alamatekor = AlokasiLDP(((int)Info(Last(L))) + 1);
                    Absis(alamatekor) = ekorbaru.coor.x;
                    Ordinat(alamatekor) = ekorbaru.coor.y;
                    InsertLastLDP(&L, alamatekor);
                    makeFood(&food, L, obstacle);
                }

                makeMeteor(&meteor, food);
                printMap(L, food, meteor, obstacle);
                kenaMeteor(&L, food, meteor);

                if (!endGame(L, meteor, obstacle))
                {
                    turn++;
                }
                else
                {
                    score = Info(Last(L)) * 2;
                    printf("Score : %d\n", score);
                    kena = true;
                }
                
            }
            else{
                printf("Ada badan snake! Silahkan input ulang\n");
            }
        }
        else
        {
            printf("Silahkan memasukkan command yang valid!\n");
        }
    }
    return 0;
}