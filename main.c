#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <time.h>

#define N 10
#define TAM 10
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
void crea_contenedor(int x, int y,  TCubo cont[N][N][N]);
void cubo(int x, int y, int color);
void juego(String nombre);
void pinta_ambiente(String nombre);
void pinta_contenedor(TCubo cont[N][N][N]);

// Funciones de portada
void portada();

// Variables globales.
int maxx, maxy; // Evita repetir la funcion getmaxN() cada vez que se llama en un ciclo.

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

void crea_contenedor(int x, int y,TCubo cont[N][N][N])
{
  int k,j,i;

  for(k=0;k<N;k++)
   for(j=0;j<N;j++)
    for(i=0;i<N;i++)
    {
        cont[k][j][i].x=x+i*TAM-k*PROFX;
        cont[k][j][i].y=y-j*TAM+k*PROF;
        cont[k][j][i].color=rand()%16;
        cont[k][j][i].e=0;
    }

}

void cubo(int x, int y, int color)
{
    int puntos[8];

    setcolor(15);
    setfillstyle(1,color);
    //Cara frontal
    bar(x,y,x+TAM,y+TAM);
    rectangle(x,y,x+TAM,y+TAM);
    //Cara lateral
    puntos[0]=x+TAM;
    puntos[1]=y;
    puntos[2]= x+TAM;
    puntos[3]= y+TAM;
    puntos[4]= x+TAM+PROFX;
    puntos[5]= y-PROF+TAM;
    puntos[6]= x+TAM+PROFX;
    puntos[7]= y-PROF;
    fillpoly(4,puntos);
    //Cara Superior
    puntos[0]=x;
    puntos[1]=y;
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

    TCubo contenedor[N][N][N];
    TJugador jug={0,0,0,13};
    TJugador maq={N-1,N-1,N-1,1};
    int tecla,dir;

    srand(time(NULL));
    crea_contenedor(maxx/6,maxy/4,contenedor);

    pinta_ambiente(nombre);

    do
    {

    contenedor[jug.m][jug.r][jug.c].e=1;  //Enciende jugador
    contenedor[jug.m][jug.r][jug.c].color=jug.color;

    contenedor[maq.m][maq.r][maq.c].e=1;  //Enciende maquina
    contenedor[maq.m][maq.r][maq.c].color=maq.color;
    setfillstyle(1,0);
    bar(1,1,maxx/2-1,maxy/2-1);
    pinta_contenedor(contenedor);
    delay(100);
    contenedor[jug.m][jug.r][jug.c].e=0;  //Apaga jugador
    contenedor[jug.m][jug.r][jug.c].color=0;
    contenedor[maq.m][maq.r][maq.c].e=0;  //Apaga maq
    contenedor[maq.m][maq.r][maq.c].color=0;

    dir=rand()%6+1;
    switch(dir)
    {
        case 1:
                 if(maq.r<N-1)
                   maq.r++;//Arriba
                 break;

        case 4:
                 if(maq.r>0)
                   maq.r--;//Abajo
                 break;
         case 3:
                 if(maq.c<N-1)
                   maq.c++;//Arriba
                 break;

        case 6:
                 if(maq.c>0)
                   maq.c--;//Abajo
                 break;
        case 5:
                 if(maq.m<N-1)
                   maq.m++;//Arriba
                 break;

        case 2:
                 if(maq.m>0)
                   maq.m--;//Abajo
                 break;
    }


    if(kbhit()!=0)
    {


      tecla=getch();
      if(tecla==0)
       tecla=getch();
      switch(tecla)
      {

        case 72:
                 if(jug.r<N-1)
                   jug.r++;//Arriba
                 break;

        case 80:
                 if(jug.r>0)
                   jug.r--;//Abajo
                 break;
         case 77:
                 if(jug.c<N-1)
                   jug.c++;//Arriba
                 break;

        case 75:
                 if(jug.c>0)
                   jug.c--;//Abajo
                 break;
      }
    }
    }while(tecla!=27);



}

void pinta_ambiente(char nombre[100])
{
    cleardevice();
 // setlinestyle(1,0,3);

    settextstyle(3, HORIZ_DIR, 1);

    setcolor(WHITE);
    rectangle(0,0,maxx,maxy);
    line(maxx/2,0,maxx/2,maxy/2);
    line(0,maxy/2,maxx/2,maxy/2);
    outtextxy(maxx/2+10,10,"Nombre: ");
    outtextxy(maxx/2+10+textwidth("Nombre:  "),10,nombre);
    outtextxy(maxx/2+10,60,"Puntos: ");
    outtextxy(maxx/2+10,110,"Tiempo: ");
}

void pinta_contenedor(TCubo cont[N][N][N])
{
    int i,j,k;

    setcolor(WHITE);
    rectangle(cont[0][N-1][0].x+PROFX,cont[0][N-1][0].y-PROF,cont[0][0][N-1].x+TAM+PROFX,cont[0][0][N-1].y+TAM-PROF);
    line(cont[0][N-1][0].x+PROFX,cont[0][N-1][0].y-PROF,cont[N-1][N-1][0].x,cont[N-1][N-1][0].y);
    line(cont[0][0][0].x+PROFX,cont[0][0][0].y+TAM-PROF,cont[N-1][0][0].x,cont[N-1][0][0].y+TAM);
    for(i=0;i<N;i++)
    for(j=0;j<N;j++)
    for(k=0;k<N;k++)
     if(cont[k][j][i].e==1)
       cubo(cont[k][j][i].x,cont[k][j][i].y,cont[k][j][i].color);
    rectangle(cont[N-1][N-1][0].x,cont[N-1][N-1][0].y,cont[N-1][0][N-1].x+TAM,cont[N-1][0][N-1].y+TAM);
    line(cont[0][0][N-1].x+TAM+PROFX,cont[0][0][N-1].y+TAM-PROF,cont[N-1][0][N-1].x+TAM,cont[N-1][0][N-1].y+TAM);
    line(cont[0][N-1][N-1].x+TAM+PROFX,cont[0][N-1][N-1].y-PROF,cont[N-1][N-1][N-1].x+TAM,cont[N-1][N-1][N-1].y);
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

    // cielo
    setfillstyle(1,0xFF9900);
    bar(0, 0, maxx+1, maxy+1);

    // titulo
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

    // tierra
    setfillstyle(1,0x336699);
    bar(0, maxy-altura+tam, maxx+1, maxy+1);

    // pasto
    setfillstyle(1,0x00CC7A);
    setcolor(0x00CC7A);
    bar(0, maxy-altura+tam, maxx+1, maxy-altura+tam+10);

    // mas tierra
    int i, tmp = maxy-altura+tam+10;
    for(i=0; i<40000; i++)
        putpixel(rand()%maxx, rand()%maxy+tmp, 0x275078);

    // enter
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
