#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#define N 8
#define TAM 15
#define PROF TAM/2
#define PROFX 3*PROF/4

typedef struct{
    int x,y;
    int color;
    int e;
}TCubo;

void cubo3D(int x, int y, int color);
void cubo(int x, int y, int color);
void pintarContenedor(TCubo cont[N][N][N]);
void typeWriter(int w, int h, char str[80]);
void crearContenedor(int x, int y, TCubo cont[N][N][N]);

///VARIABLES GLOBALES
int width = 640,
    height= 480,
    width2 = width/2,
    height2= height/2;

///MAIN
int main()
{
    int i;
    TCubo contenedor[N][N][N];

    initwindow(width, height, "JUEGO");
    crearContenedor(width2, height2, contenedor);
    pintarContenedor(contenedor);

    getch();
    closegraph();
    return 0;
}

///FUNCIONES
void crearContenedor(int x, int y, TCubo cont[N][N][N])
{
    int i,j,k;

    for(k=0; k<N; k++)
        for(j=0;j<N; j++)
            for(i=0;i<N; i++)
            {
                cont[k][j][i].x = x+i*TAM-k*PROFX;
                cont[k][j][i].y = y-j*TAM+k*PROF;
                cont[k][j][i].color = 0x0 + rand()%255;//0x0 +((rand()%75)*1000000)+((rand()%150)*1000)+(rand()%100);
                //if((k>=0 && i<6) || (j>14 && i<=20))
                    cont[k][j][i].e = 0;
            }

    cont[0][0][0].e = 1;
    cont[0][N-1][0].e = 1;
}

void cubo3D(int x, int y, int color)
{
     setcolor(15);
     setfillstyle(1, color);
     bar3d(x, y, x+TAM, y+TAM, PROF, 1);

     setcolor(15);
     setfillstyle(1, color);
     floodfill(x+TAM+2, y+TAM/4, 15);

     setcolor(14);
     setfillstyle(1, color);
     floodfill(x+TAM/2, y-2, 15);
}

void cubo(int x, int y, int color)
{
     int puntos[8];

     setcolor(0x0045ff);
     setfillstyle(1, color);
     //Cara frontal
     bar(x, y, x+TAM, y+TAM);
     rectangle(x, y, x+TAM, y+TAM);

     //Cara lateral
     puntos[0]= x+TAM;
     puntos[1]= y;
     puntos[2]= x+TAM;
     puntos[3]= y+TAM;
     puntos[4]= x+TAM+PROFX;
     puntos[5]= y-PROF+TAM;
     puntos[6]= x+TAM+PROFX;
     puntos[7]= y-PROF;
     fillpoly(4, puntos);

     //Cara superior
     puntos[0]= x;
     puntos[1]= y;
     puntos[2]= x+TAM;
     puntos[3]= y;
     puntos[4]= x+TAM+PROFX;
     puntos[5]= y-PROF;
     puntos[6]= x+PROFX;
     puntos[7]= y-PROF;

     fillpoly(4, puntos);
}

void pintarContenedor(TCubo cont[N][N][N])
{

    int i,j,k;

    setcolor(0xAC5DFC);
    rectangle(cont[0][N-1][0].x+PROFX, cont[0][N-1][0].y-PROF, cont[0][0][N-1].x+TAM+PROFX, cont[0][0][N-1].y+TAM-PROF);
    line(cont[0][N-1][0].x+PROFX, cont[0][N-1][0].y-PROF, cont[N-1][N-1][0].x, cont[N-1][N-1][0].y);

    for(k=0; k<N; k++)
        for(j=0;j<N; j++)
            for(i=0;i<N; i++)
                if(cont[k][j][i].e == 1)
                    cubo(cont[k][j][i].x, cont[k][j][i].y, cont[k][j][i].color);

}
