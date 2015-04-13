#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <time.h>

#define N 25
#define R 2 // Renglones de altura
#define TAM 20
#define PROF TAM/2
#define PROFX 3*PROF/4

typedef char String [100];
typedef struct{
    int x,y;
    int color;
    int e;
}TCubo;

typedef struct{
    int m,r,c,color;
}TJugador;


// Funciones del juego
void crea_contenedor(int x, int y,  TCubo cont[N][R][N]);
void cubo(int x, int y, int color);
void juego(String nombre);
void pinta_ambiente(char nombre[100]);
void pinta_contenedor(TCubo cont[N][R][N]);

// Funciones de portada
void animarPac(int tam, int altura);
void portada();

// Variables globales.
int maxx, maxy, // Evita repetir la funcion getmaxN() cada vez que se llama en un ciclo.
    suelo[8]; // Coordenadas de la plataforma de juego, comenzado en la izquierda-arriba, izquierda-abajo ...

int main()
{

    initwindow(800,600,"Pacmario");
    maxx = getmaxx();
    maxy = getmaxy();

    srand(time(NULL));
    portada();
    cleardevice();

    setbkcolor(BLACK);
    juego("Jesús");
    getch();
    closegraph();
    return(0);
}

void crea_contenedor(int x, int y,TCubo cont[N][R][N])
{
  int i,j,k;

  for(i=0;i<N;i++)
   for(j=0;j<R;j++)
    for(k=0;k<N;k++)
    {
        cont[i][j][k].x = x+k*TAM-i*PROFX;
        cont[i][j][k].y = y-j*TAM+i*PROF;
        cont[i][j][k].color = 0x009966;
        cont[i][j][k].e = 0;
        //cont[i][j][k].e = ( i%6 && k%4 && j == 0)?1:0;
        if(i==5 && j == 0 && k == 3)
            cont[i][j][k].e = 1;
    }

    suelo[0] = cont[0][0][0].x+PROFX;
    suelo[1] = cont[0][0][0].y+TAM-PROF;
    suelo[2] = cont[N-1][0][0].x;
    suelo[3] = cont[N-1][0][0].y+TAM;
    suelo[4] = cont[N-1][0][N-1].x+TAM;
    suelo[5] = cont[N-1][0][N-1].y+TAM;
    suelo[6] = cont[0][0][N-1].x+TAM+PROFX;
    suelo[7] = cont[0][0][N-1].y+TAM-PROF;
}

void cubo(int x, int y, int color)
{
    int puntos[8];

    setcolor(0x2DC501);
    setfillstyle(1,color);

    //Cara frontal
    bar(x,y,x+TAM,y+TAM);
    rectangle(x,y,x+TAM,y+TAM);
    //Cara lateral
    puntos[0]= x+TAM;
    puntos[1]= y;
    puntos[2]= x+TAM;
    puntos[3]= y+TAM;
    puntos[4]= x+TAM+PROFX;
    puntos[5]= y-PROF+TAM;
    puntos[6]= x+TAM+PROFX;
    puntos[7]= y-PROF;
    fillpoly(4,puntos);
    //Cara Superior
    puntos[0]= x;
    puntos[1]= y;
    puntos[2]= x+TAM;
    puntos[3]= y;
    puntos[4]= x+TAM+PROFX;
    puntos[5]= y-PROF;
    puntos[6]= x+PROFX;
    puntos[7]= y-PROF;
    fillpoly(4,puntos);
}

void juego(char nombre[100])
{
    int tecla,dir;
    srand(time(NULL));

    TCubo contenedor[N][R][N];
    TJugador jug = {0,0,0,0x00ffff};
    TJugador maq = {N/2, 0, N/2, 0x532FFF};
    crea_contenedor(maxx/2-maxy/4,maxy/8*3,contenedor);
    pinta_contenedor(contenedor);

    do
    {

        contenedor[jug.m][jug.r][jug.c].e=1;  //Enciende jugador
        contenedor[jug.m][jug.r][jug.c].color=jug.color;
        contenedor[maq.m][maq.r][maq.c].e=1;  //Enciende maquina
        contenedor[maq.m][maq.r][maq.c].color=maq.color;

        pinta_contenedor(contenedor);
        contenedor[jug.m][jug.r][jug.c].e=0;  //Apaga jugador
        contenedor[jug.m][jug.r][jug.c].color=0;
        contenedor[maq.m][maq.r][maq.c].e=0;  //Apaga maq
        contenedor[maq.m][maq.r][maq.c].color=0;

        int dirm=rand()%4+1; // Direccion de la maquina
        switch(dirm)
        {
            case 1:
                     if(maq.m>0)
                       maq.m--; // Abajo
                     break;
            case 2:
                     if(maq.m<N-1)
                       maq.m++; // Arriba
                     break;
            case 3:
                     if(maq.c<N-1)
                       maq.c++; // Derecha
                     break;
            case 4:
                     if(maq.c>0)
                       maq.c--; // Izquierda
                     break;
        }
        if(kbhit()!=0)
        {
            switch(tecla = getch())
            {
                case 72: dir = 0; break; // Arriba
                case 75: dir = 1; break; // Izquierda
                case 77: dir = 2; break; // Derecha
                case 80: dir = 3; break; // Abajo
            }
        }

        switch(dir)
        {
            case 0:
                if(jug.m>0 && (jug.c != 3 || jug.m != 6))
                    jug.m--;
                else if(jug.m == 0 && jug.c == N-1)
                {
                    jug.c = 0;
                    jug.m = N-1;
                }
                break;
            case 1:
                if(jug.c>0 && (jug.c != 4 || jug.m != 5))
                    jug.c--; break;
            case 2:
                if(jug.c<N-1 && (jug.c != 2 || jug.m != 5))
                    jug.c++; break;
            case 3:
                if(jug.m<N-1 && (jug.c != 3 || jug.m != 4))
                    jug.m++;
                else if(jug.m == N-1 && jug.c == 0)
                {
                    jug.c = N-1;
                    jug.m = 0;
                }
                    break;
        }
        delay(120);
    }while(tecla!=27);

}

void pinta_ambiente(char nombre[100])
{

}

void pinta_contenedor(TCubo cont[N][R][N])
{
    int i,j,k;

    // Cielo
    setfillstyle(1, 0xCCCC33);
    bar(0, 0, maxx+1, suelo[1]);

    // Pasto
    setcolor(0x31D301);
    setfillstyle(1, 0x31D301);
    bar(0, suelo[1], maxx+1, maxy+1);

    // Zona de juego
    setcolor(0x31D301);
    setfillstyle(1, 0x2DC501);
    fillpoly(4,suelo);

    for(i=0;i<N;i++)
        for(j=0;j<R;j++)
            for(k=0;k<N;k++)
                if(cont[i][j][k].e==1)
                    cubo(cont[i][j][k].x,cont[i][j][k].y,cont[i][j][k].color);
}

void animarPac(int tam, int altura)
{
    int x, ang, aux = 1;

    for(x=0, ang=0; x<maxx+tam*2; x+=2, ang += aux)
    {
        if(ang==60)
            aux = -aux;
        else if(ang == 0)
            aux = abs(aux);

        setfillstyle(1,0xFF9900);
        setcolor(0xFF9900);
        bar(0, maxy-altura-tam, x, maxy-altura+tam);

        setfillstyle(1,0x00CCFF);
        setcolor(0x00CCFF);
        pieslice(x, maxy-altura, ang, 360-ang, tam);

        delay(3);
    }
}
void portada()
{
    int tam = 20, // Tamaño del Pac
        altura = 140; // Altura del suelo

    // Cielo
    setfillstyle(1,0xFF9900);
    bar(0, 0, maxx+1, maxy+1);

    // Titulo
    int margin = 6;
    String titulo = " PAC-MARIO ";
    settextstyle(10, HORIZ_DIR, 8);
    setfillstyle(9,0x40E8FF);
    setbkcolor(0x00B6EA);
    bar(
        maxx/2-textwidth(titulo)/2-margin,
        maxy/8-margin,
        maxx/2+textwidth(titulo)/2+margin,
        maxy/8+textheight(titulo)+margin);
    setcolor(0x40E8FF);
    outtextxy(maxx/2-textwidth(titulo)/2, maxy/8, titulo);

    // Tierra
    setfillstyle(1,0x336699);
    bar(0, maxy-altura+tam, maxx+1, maxy+1);

    // Pasto
    setfillstyle(1,0x00CC7A);
    setcolor(0x00CC7A);
    bar(0, maxy-altura+tam, maxx+1, maxy-altura+tam+10);

    // Mas tierra
    int i, tmp = maxy-altura+tam+10;
    for(i=0; i<40000; i++)
        putpixel(rand()%maxx, rand()%maxy+tmp, 0x275078);

    // Enter
    setfillstyle(1,0x00CC7A);
    setcolor(BLACK);
    settextstyle(8, HORIZ_DIR, 2);
    setbkcolor(0xFF9900);
    outtextxy(maxx/2-textwidth("Presiona Enter")/2, maxy/2, "Presiona Enter");

    while(kbhit()==0)
    {
        time_t tiempo = time(NULL);
        struct tm *tm;
        tm = localtime (&tiempo);
        if(tm->tm_sec == 15 || tm->tm_sec == 45)
            animarPac(tam, altura);
        delay(500);
    }
}
