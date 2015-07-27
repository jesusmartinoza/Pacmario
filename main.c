#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <time.h>

#define TOP 10 // Numero maximo del top.
#define N 25
#define R 5 // Renglones de altura
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

typedef struct {
    String nombre;
    int puntos;
} Registro;

// Funciones del jue
void guardarRegistro(String nombre, Registro registro);
void ayuda(String nombre, int x1, int y1, int x2, int y2);
void crea_contenedor(int x, int y,  TCubo cont[N][R][N]);
void cubo(int x, int y, int color);
void girar(TCubo cubo[N][R][N], int derecha);
void guardarRegistro(Registro registro);
void imprimeTiempo(int x1, int y1, int x2, int y2, clock_t inicio);
void juego(String nombre);
void pinta_ambiente(String nombre, int puntos);
void pinta_contenedor(TCubo cont[N][R][N]);
void popup(int puntos);

// Funciones de portada.
void animarPac(int tam, int altura);
void portada();

// Variables globales.
int maxx, maxy, // Evita repetir la funcion getmaxN() cada vez que se llama en un ciclo.
    suelo[8]; // Coordenadas de la plataforma de juego, comenzado en la izquierda-arriba, izquierda-abajo ...
    clock_t ini = clock();
int main()
{

    initwindow(1024,800,"Pacmario");
    maxx = getmaxx();
    maxy = getmaxy();

    srand(time(NULL));
    portada();

    // ayuda("ayuda.txt", 0, 0, maxx, maxy);
    setbkcolor(BLACK);
    juego("Jesús");
    getch();
    closegraph();
    return(0);
}

void ayuda(String nombre, int x1, int y1, int x2, int y2)
{
    FILE *f;
    String texto;
    int x, y;

    cleardevice();
    setcolor(0x0011AA);
    settextstyle(0, HORIZ_DIR, 2);
    rectangle(x1, y1, x2, y2);

    f = fopen(nombre, "r");

    if(f == NULL)
    {
        outtextxy(x1+((x2-x1)-textwidth("No se encuentra el archivo")/2), (y1-y2)/2, "No se encontró archivo.");
        getch();getch();
    } else {
        y = y1;
        while(!feof(f))
        {
            fgets(texto, 100, f);
            y += textheight(texto);
            x = x1 + (((x2-1)-textwidth(texto))/2);
            outtextxy(x, y, texto);
            if( y > (y2 - 30))
            {
                outtextxy((x2-x1)/2, y2-10, "Presiona una tecla para continuar");
                getch();getch();
                cleardevice();
                rectangle(x1, y1, x2, y2);
                y = y1;
            }
        }
        getch();getch();
        fclose(f);
    }
}
void crea_contenedor(int x, int y, TCubo cont[N][R][N])
{
    int i,j,k, existes[N*N];
    FILE *campo;
    campo = fopen("escenario.txt", "r");
    int c;
    for(i=0;i<N;i++)
        for(j=0;j<R;j++)
            for(k=0;k<N;k++)
            {
                c = fgetc(campo);
                cont[i][j][k].x = x+k*TAM-i*PROFX;
                cont[i][j][k].y = y-j*TAM+i*PROF;
                cont[i][j][k].e = c-48;
                cont[i][j][k].color = 0x0052BF;
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

void girar(TCubo cubo[N][R][N], int derecha)
{
    int aux[N][R][N],
        auxC[N][R][N],
        m, r, c;

    if(derecha)
        for(m=0;m<N;m++)
            for(r=0;r<R;r++)
                for(c=0;c<N;c++)
                {
                    aux[m][0][c] = cubo[c][0][N-1-m].e;
                    auxC[m][0][c] = cubo[c][0][N-1-m].color;
                }
    else
        for(m=0;m<N;m++)
            for(r=0;r<R;r++)
                for(c=0;c<N;c++)
                {
                    aux[m][0][c] = cubo[N-1-c][0][m].e;
                    auxC[m][0][c] = cubo[N-1-c][0][m].color;
                }

    for(m=0;m<N;m++)
        for(r=0;r<R;r++)
            for(c=0;c<N;c++)
            {
                cubo[m][0][c].e = aux[m][0][c];
                cubo[m][0][c].color = auxC[m][0][c];
            }
}

void guardarRegistro(Registro registro)
{
    FILE *f;
    Registro jugadores[TOP], j = {"", 0};
    int i;
    String nombre = "records.dat";
    f = fopen(nombre, "rb+");
    if(f== NULL)
    {
        f = fopen(nombre, "wb");
        jugadores[0] = registro;
        for(i=0; i<TOP; i++)
            jugadores[i] = j;
        fwrite(jugadores, sizeof(Registro), TOP, f);
    } else {
        fread(jugadores, sizeof(Registro),TOP, f);
        for(i=TOP-1; i>0; i--)
            if(registro.puntos >= jugadores[i].puntos)
            {
                jugadores[i+1] = jugadores[i];
                jugadores[i] = registro;
            }
        fseek(f, 0, SEEK_SET);
        fwrite(jugadores, sizeof(Registro), TOP, f);
    }
    fclose(f);
}

void intextxy(int x, int y, int bkcolor, String texto)
{
    int xi = x;
    int i = 0, tecla;
    char letra[2];
    settextstyle(8, HORIZ_DIR, 4);
    do
    {
        do
        {
            setbkcolor(bkcolor);
            setcolor(BLACK);
            outtextxy(xi, y, "_");
            delay(100);
            setcolor(bkcolor);
            outtextxy(xi, y, "_");
            delay(100);
        }while(!kbhit());
        tecla = getch();
        if(tecla!=13 && tecla!='\b')
        {
            letra[0] = tecla;
            letra[1] = '\0';
            setcolor(BLACK);
            outtextxy(xi, y, letra);
            xi+=textwidth(letra);
            texto[i++] = letra[0];

        } else {
            if(tecla=='\b' && i>0)
            {
                letra[0] = texto[--i];
                letra[1] = '\0';
                xi-=textwidth(letra);
                setcolor(bkcolor);
                outtextxy(xi, y, letra);
            }
        }
    }while(tecla!=13 && i<15);
    texto[i] = '\0';
}
void imprimeTiempo(int x1, int y1, int x2, int y2, clock_t inicio)
{
    clock_t actual;
    int seg;
    char texto[10];

    actual = clock();
    seg = (actual-inicio)/CLK_TCK;
    sprintf(texto, "%d:%d", seg/60, seg%60);
    bar(x1, y1, x2,y2);
    outtextxy(x1+5, y1+5, texto);
}
void juego(String nombre)
{
    int aux,
        derecha = 1, // 1 gira derecha, 0 izquierda
        np = 0, //Paginacion
        i = 0,
        puntos = 0,
        salir = 0, // Bandera para salir del juego.
        tecla;
    srand(time(NULL));

    TCubo contenedor[N][R][N];
    TJugador jug = {N/2+2,0,N/2,0x00ffff};
    TJugador bots[2];

    bots[0] = {2, 0, 2, 0x532FFF};
    bots[1] = {N-3, 0, N-3, 0xA9C903};

    crea_contenedor(maxx/2-maxy/4,maxy/8*3,contenedor);

    setactivepage(0);
    pinta_contenedor(contenedor);
    pinta_ambiente(nombre, puntos);
    setactivepage(1);
    pinta_contenedor(contenedor);

    setvisualpage(np);

    do
    {
        // Salir cuando toque a los bots
        for(;i<2; i++)
            salir = (bots[i].m == jug.m && bots[i].c == jug.c ) ? 1: 0;

        //Enciende jugador
        contenedor[jug.m][jug.r][jug.c].e=1;
        contenedor[jug.m][jug.r][jug.c].color=jug.color;

        //Enciende maquinas
        for(i=0;i<2;i++)
        {
            contenedor[bots[i].m][bots[i].r][bots[i].c].e=1;
            contenedor[bots[i].m][bots[i].r][bots[i].c].color=bots[i].color;
        }

        np=!np;
        setactivepage(np);


        pinta_contenedor(contenedor);
        pinta_ambiente(nombre, puntos);


        setvisualpage(np);
        contenedor[jug.m][jug.r][jug.c].e=0;  //Apaga jugador
        contenedor[bots[1].m][bots[1].r][bots[1].c].e=0;  //Apaga maq

        int dirm=rand()%4+1; // Direccion de la maquina
        switch(dirm)
        {
            case 1:
                     if(bots[1].m>0 && (contenedor[bots[1].m-1][bots[1].r][bots[1].c].e == 0))
                       bots[1].m--; // Abajo
                     break;
            case 2:
                     if(bots[1].m<N-1 && (contenedor[bots[1].m+1][bots[1].r][bots[1].c].e == 0))
                       bots[1].m++; // Arriba
                     break;
            case 3:
                     if(bots[1].c<N-1 && (contenedor[bots[1].m][bots[1].r][bots[1].c+1].e == 0))
                       bots[1].c++; // Derecha
                     break;
            case 4:
                     if(bots[1].c>0 && (contenedor[bots[1].m][bots[1].r][bots[1].c-1].e == 0))
                       bots[1].c--; // Izquierda
                     break;
        }
        if(kbhit()!=0)
        {
            /*switch(tecla = getch())
            {
                case 72: dir = 0; break; // Arriba
                case 75: dir = 1; break; // Izquierda
                case 77: dir = 2; break; // Derecha
                case 80: dir = 3; break; // Abajo
            }*/



            switch(tecla = getch())
            {
                case 71: // G
                case 103: // g
                    aux = jug.m;
                    jug.m = jug.c;
                    jug.c = aux;
                    girar(contenedor, derecha = !derecha);
                    puntos++;
                    break;
                case 72:
                    if(jug.m>0 && (contenedor[jug.m-1][jug.r][jug.c].e == 0))
                        jug.m--;
                    else if(jug.m == 0 && jug.c == N-1)
                    {
                        jug.c = 0;
                        jug.m = N-1;
                    }
                    puntos++;
                    break;
                case 75:
                    if(jug.c>0 && (contenedor[jug.m][jug.r][jug.c-1].e == 0))
                        jug.c--;
                    puntos++;
                    break;
                case 77:
                    if(jug.c<N-1 && (contenedor[jug.m][jug.r][jug.c+1].e == 0))
                        jug.c++;
                    puntos++;
                    break;
                case 80:
                    if(jug.m<N-1 && (contenedor[jug.m+1][jug.r][jug.c].e == 0))
                        jug.m++;
                    else if(jug.m == N-1 && jug.c == 0)
                    {
                        jug.c = N-1;
                        jug.m = 0;
                    }
                    puntos++;
                    break;
            }
        }
    }while(tecla!=27 && !salir);

    popup(puntos);
}
void menu()
{
    int op, xm, ym;
    do
    {
        rectangle(100, 100, 300, 200);
        outtextxy(120, 110, "Juego");
        rectangle(100, 200, 300, 250);
        outtextxy(120, 210, "Record");
        rectangle(100, 300, 300, 300);
        outtextxy(120, 310, "Ayuda");
        while(!ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, xm, ym);
            if(xm>100 && xm<300 && ym>100 && ym<150)
                op =1;
        }
    }while(op!=4);
}
void pinta_ambiente(String nombre, int puntos)
{
    setbkcolor(0xFF9900);
    setfillstyle(1, 0xFF9900);
    settextstyle(1,HORIZ_DIR, 2);

    setcolor(WHITE);
    outtextxy(textwidth(nombre), 10, nombre);

    String sPuntos;
    sprintf(sPuntos, "%d", puntos*10);
    outtextxy(maxx-textwidth("1000")*2, 10, sPuntos);

    imprimeTiempo(maxx/2, 10, maxx/2+100, 100, ini);
}

void pinta_contenedor(TCubo cont[N][R][N])
{
    int i,j,k;
    // Cielo
    setfillstyle(1, 0xFF9900);
    bar(0, 0, maxx+1, suelo[1]);

    /*for(i=0, j=0; i<suelo[1]; i++)
    {
        setcolor(COLOR(0, 0, i%255));
        line(0, i, maxx, i);
    }*/

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
void popup(int puntos)
{
    int x1,x2,y1,y2, i,
        nRec = 13; // Numero de rectangulos
    x1 = x2 = (maxx/2);
    y1 = y2 = (maxy/2);
    String pts;
    sprintf(pts, "%d", puntos*10);

    setfillstyle(1,0x00CCFF);
    for(i=0; i<nRec; x1-=15, y1-=10, x2+=15, y2+=10, i++)
    {
        bar(x1, y1, x2, y2);
        delay(2);
    }

    // ¡PERDISTE!
    setbkcolor(0x00CCFF);
    setcolor(0x0054D3);
    settextstyle(3, HORIZ_DIR, 6);
    outtextxy(maxx/2-textwidth("¡PERDISTE!")/2, y1+textheight("P")/2, "¡PERDISTE!");

    // Puntuacion
    setcolor(0x4b78F2);
    settextstyle(3, HORIZ_DIR, 3);
    outtextxy(maxx/2-textwidth("Puntuación:")/2, y1+textheight("P")*4, "Puntuación:");

    // Puntos
    settextstyle(3, HORIZ_DIR, 6);
    outtextxy(maxx/2-textwidth(pts)/2, maxy/2, pts);

    // Nombre
    String nombre;
    setfillstyle(1, 0x5ADEFF);
    bar(maxx/2-textwidth("Puntuación:")/3+15, maxy/2+65, maxx/2+textwidth("Puntuacion:")/3-15, maxy/2+100);
    intextxy(maxx/2-60, maxy/2+65, 0x5ADEFF, nombre);
    fflush(stdin);
    getch();
    Registro r = {"nombre", puntos};
    guardarRegistro(r);
}

// Funciones de la portada
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

        delay(1);
    }
}
void dibujo()
{
    int tam = 20, // Tamaño del Pac
        altura = 140; // Altura del suelo

    // Cielo
    setfillstyle(1,0xFF9900);
    bar(0, 0, maxx+1, maxy+1);
    setbkcolor(0xFF9900);
    // Enter
    setcolor(BLACK);
    settextstyle(0, HORIZ_DIR, 2);
    outtextxy(maxx/2-textwidth("Presiona Enter")/2, maxy/2, "Presiona Enter");

    // Titulo
    int margin = 6;
    String titulo = " PAC-MARIO ";
    settextstyle(10, HORIZ_DIR, 8);
    setfillstyle(4,0x40E8FF);
    setbkcolor(0x00B6EA);
    bar(
        maxx/2-textwidth(titulo)/2-margin,
        maxy/8-margin,
        maxx/2+textwidth(titulo)/2+margin,
        maxy/8+textheight(titulo)+margin);
    setcolor(0x40E8FF);
    outtextxy(maxx/2-textwidth(titulo)/2, maxy/8, titulo);

    // TierraF5D76E
    setfillstyle(1,0x336699);
    bar(0, maxy-altura+tam, maxx+1, maxy+1);

    // Pasto
    setfillstyle(1,0x00CC7A);
    setcolor(0x00CC7A);
    bar(0, maxy-altura+tam, maxx+1, maxy-altura+tam+10);
}
void portada()
{
    int tam = 20, // Tamaño del Pac
        altura = 140, // Altura del suelo
        np = 0;

    dibujo();
    while(kbhit()==0)
    {
        time_t tiempo = time(NULL);
        struct tm *tm;
        tm = localtime (&tiempo);
        int seg = tm->tm_sec;
        if(seg == 15 || seg == 45 || seg == 30 || seg == 0)
            animarPac(tam, altura);
        printf("%d ", seg);
        delay(200);
    }
}
