#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>

#define N 10
#define TAM 10
#define PROF TAM/2
#define PROFX 3*PROF/4

typedef struct{
    int x,y;
    int color;
    int e;
}TCubo;

typedef struct{

 int m,r,c,color;

}TJugador;



void portada();

void crea_contenedor(int x, int y,  TCubo cont[N][N][N]);
void pinta_contenedor(TCubo cont[N][N][N]);
void juego(char nombre[100]);
void pinta_ambiente(char nombre[100]);

void cubo(int x, int y, int color);
int main()
{


    initwindow(640,480,"Proyecto EDA");
    srand(time(NULL));
/*    portada();
    getch();
    cleardevice();
*/

    juego("Silvia");
    getch();
    closegraph();
    return(0);
}

void pinta_contenedor(TCubo cont[N][N][N])
{
  int k,j,i;

  setcolor(15);
  rectangle(cont[0][N-1][0].x+PROFX,cont[0][N-1][0].y-PROF,cont[0][0][N-1].x+TAM+PROFX,cont[0][0][N-1].y+TAM-PROF);
  line(cont[0][N-1][0].x+PROFX,cont[0][N-1][0].y-PROF,cont[N-1][N-1][0].x,cont[N-1][N-1][0].y);
  line(cont[0][0][0].x+PROFX,cont[0][0][0].y+TAM-PROF,cont[N-1][0][0].x,cont[N-1][0][0].y+TAM);
  for(k=0;k<N;k++)
   for(j=0;j<N;j++)
    for(i=0;i<N;i++)
     if(cont[k][j][i].e==1)
       cubo(cont[k][j][i].x,cont[k][j][i].y,cont[k][j][i].color);
  rectangle(cont[N-1][N-1][0].x,cont[N-1][N-1][0].y,cont[N-1][0][N-1].x+TAM,cont[N-1][0][N-1].y+TAM);
  line(cont[0][0][N-1].x+TAM+PROFX,cont[0][0][N-1].y+TAM-PROF,cont[N-1][0][N-1].x+TAM,cont[N-1][0][N-1].y+TAM);
  line(cont[0][N-1][N-1].x+TAM+PROFX,cont[0][N-1][N-1].y-PROF,cont[N-1][N-1][N-1].x+TAM,cont[N-1][N-1][N-1].y);
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

void portada()
{
    srand(time(NULL));
/*     while(kbhit()==0)
        putpixel(rand()%getmaxx(),rand()%getmaxy(),rand()%16);*/
    setcolor(YELLOW);
    line(getmaxx()/2,0,getmaxx()/2,getmaxy());
    setcolor(RED);
    line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
    setcolor(WHITE);
    circle(getmaxx()/2,getmaxy()/2,100);
    rectangle(getmaxx()/2-100,getmaxy()/2-100,getmaxx()/2+100,getmaxy()/2+100);
    settextstyle(3,0,2);
    outtextxy(100,100,"Hola Mundo");

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
  crea_contenedor(getmaxx()/6,getmaxy()/4,contenedor);

  pinta_ambiente(nombre);

  do
  {

    contenedor[jug.m][jug.r][jug.c].e=1;  //Enciende jugador
    contenedor[jug.m][jug.r][jug.c].color=jug.color;

    contenedor[maq.m][maq.r][maq.c].e=1;  //Enciende maquina
    contenedor[maq.m][maq.r][maq.c].color=maq.color;
    setfillstyle(1,0);
    bar(1,1,getmaxx()/2-1,getmaxy()/2-1);
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
 //   setlinestyle(1,0,3);
    rectangle(0,0,getmaxx(),getmaxy());
    line(getmaxx()/2,0,getmaxx()/2,getmaxy()/2);
    line(0,getmaxy()/2,getmaxx()/2,getmaxy()/2);
    outtextxy(getmaxx()/2+10,10,"Nombre: ");
    outtextxy(getmaxx()/2+10+textwidth("Nombre:  "),10,nombre);
    outtextxy(getmaxx()/2+10,60,"Puntos: ");
    outtextxy(getmaxx()/2+10,110,"Tiempo: ");
}











