#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
  char nombre[20];
  char apellido[20];
  char nUsuario[15];
  char pass[15];
  int playlist1[21];//Arreglos q guardan 50 numeros enteros, vendrian a ser los id de las canciones
  int playlist2[21];
  int playlist3[21];
  int playlist4[21];
  int playlist5[21];
  ///Configuracion del menu, colores
}usuario;
typedef struct
{
  int id;
  char titulo[20];
  char artista[30];
  char album[30];
  char genero[20];
  int anio;
  int bpm;
  ///char tonalidad[20];
  ///char letra[1000]; un filtro para buscar re va
}musica;
typedef struct
{
   int id;
   char titulo[20];
   char artista[30];
   char album[20];
}TitIdAlbArt;

typedef struct
{
  TitIdAlbArt dato;
  struct nodo*siguiente;
}nodo;
typedef struct
{
  char genero[20];
  int id;
  nodo*listaMusica;
  struct nodoGen*siguiente;
}nodoGen;
typedef struct
{
  int anio;
  nodo*listaMusica;
  struct nodoAni*siguiente;
}nodoAni;
typedef struct
{
  int bpm;
  nodo*listaMusica;
  struct nodoBpm*siguiente;
}nodoBpm;


void InicializaLaPlayList(int array[],int dim)
{
    int i=0;
    while(i<dim)
    {
      array[i]=0;
      i++;
    }
}
usuario GeneraUnUsuario(char nUsuario[])
{
    usuario u;
    strcpy(u.nUsuario,nUsuario);
    do{
        titulo();
        printf("\n Genere una Contrasenia (Entre 5 y 15 caracteres) : ");
        fflush(stdin);
        gets(u.pass);
        if(strlen(u.pass)<5)
        {
           printf("\n\n La contrasenia es muy corta, intentelo de nuevo \n\n");
           system("pause");
           system("cls");
        }
        else if(strlen(u.pass)>15)
        {
           printf("\n\n La contrasenia es muy larga, intentelo de nuevo \n\n");
           system("pause");
           system("cls");
        }
    }while(strlen(u.pass)<5||strlen(u.pass)>15);
    system("cls");
    titulo();
    printf("\n Introduce tu Nombre : ");
    fflush(stdin);
    gets(u.nombre);
    system("cls");
    titulo();
    printf("\n Introduce tu Apellido : ");
    fflush(stdin);
    gets(u.apellido);

    InicializaLaPlayList(u.playlist1,21);
    InicializaLaPlayList(u.playlist2,21);
    InicializaLaPlayList(u.playlist3,21);
    InicializaLaPlayList(u.playlist4,21);
    InicializaLaPlayList(u.playlist5,21);

    system("cls");
    return u;
}
usuario Registrarse(char nombre_archivo[],usuario u)///Podria retornar el usuario, me ayudaria en el main supongo
{
    FILE*archi;
    archi=fopen(nombre_archivo,"a+b");
    if(archi!=NULL)
    {
      int flag=0;
      char nUsuario[21];
      do
      {
        titulo();
        printf("\n Genere un nombre de usuario (Entre 5 y 15 caracteres): ");
        fflush(stdin);
        gets(nUsuario);
        flag=BuscaEnArchivoSiExisteUnUsuario(archi,nUsuario);
        if(flag==1)
        {
          printf("\n\n El nombre de usuario se encuentra registrado, pruebe con otro \n\n\n");
          system("pause");
        }else if(strlen(nUsuario)<5)
        {
           printf("\n\n El nombre de usuario es muy corto, intentelo de nuevo \n\n\n");
           system("pause");
        }
        else if(strlen(nUsuario)>15)
        {
           printf("\n\n El nombre de usuario es muy largo, intentelo de nuevo \n\n\n");
           system("pause");
        }
        system("cls");
       }while(flag==1||strlen(nUsuario)>15||strlen(nUsuario)<5);

       titulo();
       printf("\n Genial !, tu nombre de usuario sera '%s' \n\n\n",nUsuario);
       system("pause");
       system("cls");

       u=GeneraUnUsuario(nUsuario);

       fwrite(&u,sizeof(usuario),1,archi);
       titulo();
       printf("\n Genial %s ya te registraste correctamente en 'Spotify De La Salada' !! \n\n\n",u.nombre);
       system("pause");
       system("cls");
       fclose(archi);
    }
    return u;
}
usuario IniciarSesion(char nombre_archivo[],usuario u)///Podria retornar el usuario, me ayudaria en el main supongo
{
     FILE*archi;
     archi=fopen(nombre_archivo,"a+b");
     int flag=0;
     if(archi!=NULL)
     {
        char nUsuario[21];
        do
        {
          titulo();
          printf("\n Bienvenido de vuelta, ingrese su nombre de usuario : ");
          fflush(stdin);
          gets(nUsuario);
          flag=BuscaEnArchivoSiExisteUnUsuario(archi,nUsuario);
          if(flag==0)
          {
              printf("\n\n El usuario ingresado no se encuentra, intentelo nuevamente \n\n\n");
              system("pause");
          }
          system("cls");
        }while(flag==0);

        char copiaDePass[14];
        ///Esto es para poner el cursor en su lugar
        flag=0;
        rewind(archi);
        while(fread(&u,sizeof(usuario),1,archi)>0&&flag==0)
        {
           if(strcmpi(nUsuario,u.nUsuario)==0)
           {
               flag=1;
               fseek(archi,sizeof(usuario)*-1,SEEK_CUR);
           }
        }
        //Fijarme si puedo sacar esto, quizá solo con el fseek asi como está funciona, sin rewind

        do
        {
            titulo();
            printf("\n El usuario se ha encontrado, Bienvenido %s ! \n\n",u.nombre);
            printf("\n Ingrese la contrasenia del usuario [%s] : ",u.nUsuario);
            fflush(stdin);
            gets(copiaDePass);
            flag=1;
            if(strcmpi(u.pass,copiaDePass)!=0)
            {
                flag=0;
                printf("\n\n La contrasenia ingresada no es valida, intentelo nuevamente \n\n\n");
                system("pause");
            }
            system("cls");
        }while(flag==0);

        titulo();
        printf("\n Genial %s iniciaste sesion correctamente, Hora de generar una playlist !! \n\n\n",u.nombre);
        system("pause");
        system("cls");
        fclose(archi);
    }
    return u;
}
void salir()
{
    system("cls");
    titulo();
    printf("\n\n Hasta la proxima ....\n\n\n ");
    system("exit");
}
void generaGuion()
{
  int i=0;
    while(i<122)
    {
        printf("-");
        i++;
    }
    printf("\n");
}
char IntroduccionMenu()
{
    printf("\n\t\t\t\t\t   Bienvenido a 'SpotifyDeLaSalada' !!! \n\n");
    generaGuion();
    printf("\t\t\t    En esta App podra crear su playlist con un archivo de Temaikenes ");
    printf("\n\n\t\t\t\tPersonalizar su perfil con los colores que usted quiera ");
    printf("\n\n\t\t\t\t      Ver que generos escuchan los demas usuarios ");
    printf("\n\n\t      Si usted es DJ, podra buscar canciones por los BPM o tonalidades ( Solo musica electronica ) ");
    printf("\n\n\t\t\t Subir musica al archivo de Temaikenes, pasando por el filtro del admin ");
    printf("\n\n\t\t  En un futuro podra descargar estas canciones y descargar los videos si es que existen ");
    printf("\n\n\t   Le podre sugerir algunas canciones depende algunas situaciones ( Estudio, Previa, Manejando, etc )  ");
    printf("\n\n\n\t\t\t  Las canciones fueron muy bien elegidas, INICIA SESION O REGISTRATE ! \n\n\n\n");
    system("pause");
    system("cls");
    char opcion='s';
    titulo();
    printf("\n\n 1 - Registrarse ");
    printf("\n\n\n 2 - Iniciar Sesion");
    printf("\n\n\n 3 - Salir ");
    opcion=getch();
}
void titulo()
{
    printf("\n\t\t\t\t\t\t Spotify de la Salada \n\n");
    generaGuion();
}
int BuscaEnArchivoSiExisteUnUsuario(FILE*archi,char aBuscar[])
{
  int flag=0;
  if(archi!=NULL)
  {
      usuario u;
      rewind(archi);
      while(fread(&u,sizeof(usuario),1,archi)>0&&flag==0)
      {
          if(strcmpi(u.nUsuario,aBuscar)==0)
          {
              flag=1;
          }
      }
  }
  return flag;
}

void Muestra1Usuario(usuario u)
{
    printf("\n\n nUsuario : %s ",u.nUsuario);
    printf("\n pass.....: %s ",u.pass);
    printf("\n nombre...: %s ",u.nombre);
    printf("\n apellido.: %s ",u.apellido);
    int i=0;
    if(u.playlist1[0]!=0)
    {
        printf("\n playList1: ");
        for(i=0;u.playlist1[i]!=0;i++)
        {
           printf(" %i ",u.playlist1[i]);///Ver como le pongo titulo
        }
    }
       if(u.playlist2[0]!=0)
    {
        printf("\n playList2: ");
        for(i=0;u.playlist2[i]!=0;i++)
        {
           printf(" %i ",u.playlist2[i]);///Ver como le pongo titulo
        }
    }
       if(u.playlist3[0]!=0)
    {
        printf("\n playList3: ");
        for(i=0;u.playlist3[i]!=0;i++)
        {
           printf(" %i ",u.playlist3[i]);///Ver como le pongo titulo
        }
    }
       if(u.playlist4[0]!=0)
    {
        printf("\n playList4: ");
        for(i=0;u.playlist4[i]!=0;i++)
        {
           printf(" %i ",u.playlist4[i]);///Ver como le pongo titulo
        }
    }
       if(u.playlist5[0]!=0)
    {
        printf("\n playList5: ");
        for(i=0;u.playlist5[i]!=0;i++)
        {
           printf(" %i ",u.playlist5[i]);///Ver como le pongo titulo
        }
    }
}
void MuestraArchivoDeUsuarios(char nombre_archivo[])
{
    FILE*archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        usuario u;
        printf("\n Archivo de usuarios [%s] : ",nombre_archivo);
        while(fread(&u,sizeof(usuario),1,archi)>0)
        {
            Muestra1Usuario(u);
        }
        fclose(archi);
    }
}
char MenuLuegoDeIniciarSesion(usuario u)
{
    char opcion;
    titulo();
    printf("\n Que tienes ganas de hacer %s ? ",u.nombre);
    printf("\n\n 1 - Crear PlayList ");/// Ponerle nombre y decirle cuantas playlist como maximo podes hacer
    printf("\n\n 2 - Ver las Playlist ");/// Modificarlas Eliminar, Agregar.
    printf("\n\n 3 - Ver que generos andan escuchando los usuarios (Postergado) ");//abrir archivo de usuarios y mostrar 3 temas con diferentes generos en su ultima playlist hecha
    printf("\n\n 4 - Sugerir Musica para ocasiones  ");/// Estudiar, Programar, Previa, Chill, Gimnasio, Manejar -> esas ocasiones las haré yo y solo las mostrare
    printf("\n\n 5 - Personalizar su perfil (Pantalla y texto)(Postergado) ");/// Agregar arreglo para guardar ints
    printf("\n\n 6 - Cerrar Sesion ");/// salir()
    opcion=getch();
}
nodoGen*iniListaGen()
{
    return NULL;
}
nodo*inicListaMusica()
{
   return NULL;
}
nodo*crearNodoMusica(musica m)
{
  nodo*aux=(nodo*)malloc(sizeof(nodo));
  aux->dato.id=m.id;
  strcpy(aux->dato.titulo,m.titulo);
  strcpy(aux->dato.artista,m.artista);
  strcpy(aux->dato.album,m.album);
  aux->siguiente=NULL;
  return aux;
}
nodo*buscarUltimaMusica(nodo*listaMusica)
{
    nodo*aux=listaMusica;
    if(aux!=NULL)
    {
        while(aux->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
    }
    return aux;
}
nodo*AgregarAlFinalMusica(nodo*listaMusica,nodo*nuevaMusica)
{
    if(listaMusica==NULL)
    {
        listaMusica=nuevaMusica;
    }else
    {
        nodo*ultimo=buscarUltimaMusica(listaMusica);
        ultimo->siguiente=nuevaMusica;
    }
    return listaMusica;
}
nodoGen*buscaGenero(nodoGen*listaGenero,char genero[20])
{
    nodoGen*seg=listaGenero;
    nodoGen*generoEncontrado=NULL;
    int flag=0;
       while(seg!=NULL&&flag==0)
       {
          if(strcmp(seg->genero,genero)==0)
          {
             generoEncontrado=seg;
             flag=1;
          }
          seg=seg->siguiente;
       }
    return generoEncontrado;
}
nodoGen*crearNodoGenero(char genero[],int id)
{
    nodoGen*aux=(nodoGen*)malloc(sizeof(nodoGen));
    strcpy(aux->genero,genero);
    aux->id=id;
    aux->listaMusica=inicListaMusica();
    aux->siguiente=NULL;
    return aux;
}
nodoGen*AgregarAlPpioGen(nodoGen*listaGenero,nodoGen*nuevoGenero)
{
    if(listaGenero==NULL)
    {
        listaGenero=nuevoGenero;
    }else
    {
        nuevoGenero->siguiente=listaGenero;
        listaGenero=nuevoGenero;
    }
    return listaGenero;
}
int CuentaNodosListaGenero(nodoGen*listaGenero)
{
    int i=1;
    nodoGen*aux=listaGenero;
    if(aux!=NULL)
    {
       while(aux!=NULL)
       {
           aux=aux->siguiente;
           i++;
       }
    }
    return i;
}
nodoGen*altaGenero(nodoGen*listaGenero,musica m)
{
    nodo*nuevaMusica=crearNodoMusica(m);
    nodoGen*generoEncontrar=buscaGenero(listaGenero,m.genero);
    if(generoEncontrar==NULL)
    {
        int cantNodosGenero=CuentaNodosListaGenero(listaGenero);
        nodoGen*nuevoGenero=crearNodoGenero(m.genero,cantNodosGenero);
        listaGenero=AgregarAlPpioGen(listaGenero,nuevoGenero);
        listaGenero->listaMusica=AgregarAlFinalMusica(listaGenero->listaMusica,nuevaMusica);
    }
    else
    {
        generoEncontrar->listaMusica=AgregarAlFinalMusica(generoEncontrar->listaMusica,nuevaMusica);
    }
    return listaGenero;

}
void ModularizadoTitIdAlbArt(TitIdAlbArt dato)
{
    printf(" %5d \t%-25.20s%-20.20s%-25.20s\n",dato.id,dato.titulo,dato.artista,dato.album);
    /*
    printf("\n\n ID.......: %i ",dato.id);
    printf("\n Titulo...: %s ",dato.titulo);
    printf("\n Artista..: %s ",dato.artista);
    printf("\n Album....: %s ",dato.album);*/
}
void MuestraListaMusica(nodo*listaMusica)
{
    nodo*aux=listaMusica;
    if(aux!=NULL)
    {
        generaTituloSinSalto();
        printf("    ID  TITULO                   ARTISTA             ALBUM");
        generaTituloSinSalto();
        while(aux!=NULL)
        {
           ModularizadoTitIdAlbArt(aux->dato);
           aux=aux->siguiente;
        }
        generaGuion();
    }
}
void MuestraLDLGenero(nodoGen*listaGenero)///Recursiva
{
    nodoGen*aux=listaGenero;
    if(aux!=NULL)
    {
       MuestraLDLGenero(aux->siguiente);
       if(aux->listaMusica!=NULL)
       {
            printf(" %i - %s \n\n",aux->id,aux->genero);
       }
    }
}
nodo*VerificaSiElIDingresadoEsValido(nodo*listaMusica,int idMusica)
{
    nodo*aux=listaMusica;
    nodo*musicaElegida=NULL;
    int flag=0;
    if(aux!=NULL)
    {
       while(aux!=NULL&&flag==0)
       {
           if(aux->dato.id==idMusica)
           {
                musicaElegida=aux;
                flag=1;
           }
           aux=aux->siguiente;
       }
    }
    return musicaElegida;
}
int BuscaSiExisteElgeneroporID(nodoGen*listaGenero,int idGenero)
{
    int flag=0;
    nodoGen*aux=listaGenero;
    nodoGen*generoEncontrar=NULL;
    if(aux!=NULL)
    {
        while(aux!=NULL&&flag==0)
        {
            if(aux->id==idGenero&&aux->listaMusica!=NULL)//Al mostrar los generos apareceran los q contienen musica, si el usuario elige un genero q existe pero esta vacio, no va
            {
                flag=1;
                generoEncontrar=aux;

            }
            aux=aux->siguiente;
        }
    }
    return generoEncontrar;
}
nodo*eliminarNodoMusica(nodo*listaMusica,int idMusica)
{
    if(listaMusica!=NULL&&listaMusica->dato.id==idMusica)
    {
        nodo*aux=listaMusica;
        listaMusica=listaMusica->siguiente;
        free(aux);
    }
    else
    {
        nodo*ante;
        nodo*seg=listaMusica;
        while(seg!=NULL&&seg->dato.id!=idMusica)
        {
            ante=seg;
            seg=seg->siguiente;
        }
        if(seg!=NULL)
        {
            ante->siguiente=seg->siguiente;
            free(seg);
        }
    }
    return listaMusica;
}
int RetornaValidosDePlayList(int playList[])
{
    int i=0;
    while(playList[i]!=0)
    {
        i++;
    }
    return i;
}
void CreaPlaylistPorGenero(FILE*archi,int playlist[])
{
   nodoGen*listaGenero=iniListaGen();
   nodoGen*generoMostrar=iniListaGen();
   nodo*musicaElegida=inicListaMusica();
   musica m;
   int idMusica=0;
   int idGenero=0;
   char opcion='s';
   int v=RetornaValidosDePlayList(playlist);
   while(fread(&m,sizeof(musica),1,archi)>0)
   {
       listaGenero=altaGenero(listaGenero,m);
   }
   do
   {
       system("cls");
       titulo();
       MuestraLDLGenero(listaGenero);
       printf(" Elige el indice del genero a ver la musica, presione 0 para volver : ");
       scanf("%i",&idGenero);
       generoMostrar=BuscaSiExisteElgeneroporID(listaGenero,idGenero);
       if(idGenero==0)
       {
            printf("\n ...Volvamos para atrass ...\n\n");
            system("pause");
            system("cls");
       }
       else if(generoMostrar==NULL)
            {
              printf("\n\n El indice ingresado no es valido, intentelo de nuevo \n\n\n");
              system("pause");
              system("cls");
            }
            else
            {
              do{
                    system("cls");
                    titulo();
                    MuestraListaMusica(generoMostrar->listaMusica);
                    printf("\n\n Tiene %i canciones en su PlayList, le queda %i ",v,20-v);
                    printf("\n\n Introduzca el ID de la cancion para agregarla a su playlist, si quiere volver ingrese '0' : ");
                    scanf("%i",&idMusica);
                    musicaElegida=VerificaSiElIDingresadoEsValido(generoMostrar->listaMusica,idMusica);
                    if(idMusica==0)
                    {
                       system("cls");
                    }
                    else if(musicaElegida==NULL)
                         {
                             printf("\n El ID ingresado no es valido, intentelo nuevamente \n\n\n");
                             system("pause");
                             system("cls");
                         }
                         else
                         {
                             playlist[v]=idMusica;
                             v++;
                             generoMostrar->listaMusica=eliminarNodoMusica(generoMostrar->listaMusica,idMusica);
                             if(v==20)
                             {
                                 system("cls");
                                 titulo();
                                 printf("\n Usted lleno su playlist \n\n\n");
                                 system("pause");
                                 system("cls");
                             }
                         }
                }while( (idMusica!=0)&&(v!=20)&&(generoMostrar->listaMusica!=NULL) );
              }
   }while(idGenero!=0&&v!=20&&generoMostrar!=NULL);

}
usuario CrearPlayList(char archivoMusica [],int playlist[])
{
    usuario u;
    FILE*archi=fopen(archivoMusica,"rb");
    if(archi!=NULL)
    {
      char opcion='s';
      char carga='s';
      int validos=0;//si creo la playlist se supone la q tome, va a estar vacia
      do
      {
        system("cls");
        titulo();
        printf("\n Como desea hacer las busquedas de las canciones ? ");
        printf("\n\n 1 - Por Genero ");
        printf("\n\n 2 - Por Anio (Postergado) ");
        printf("\n\n 3 - Por BPM (Electronica) (Postergado)");
        char opcion=getch();
        system("cls");
        switch(opcion)
        {
         case(49):///Genero
         {
           //Cada vez q entro a estas funciones, debo eliminar las canciones q ya estan previamente en mi playlist
           CreaPlaylistPorGenero(archi,playlist);
           break;
         }
         //case(50):///Anio
         //{
         //  break;
         //}
         //case (51):///BPM
         //{
         //  break;
         //}
        }
        validos=RetornaValidosDePlayList(playlist);
        if(validos!=20)
        {
          system("cls");
          titulo();
          printf("\n Desea seguir cargando musica ? (s/n) ");
          carga=getch();
          system("cls");
        }

      }while(carga=='s'&&validos!=20);

     ///Debo guardar la playlist hecha en usuario o en el archivo de usuarios
     fclose(archi);

    }
    //return u;///no retorna, guarda lo configurado de la playlist
}
int DiceCuantosSlotsDePlaylistTenes(usuario u)
{
    int slots=0;///Ni ==0 ni ==NULL ni invirtiendo lugares

    if(u.playlist1[0]==0&&u.playlist2[0]==0&&u.playlist3[0]==0&&u.playlist4[0]==0&&u.playlist5[0]==0)
    {
        slots=5;/// 1,2,3,4,5 libres -> uso la playlist 1
    }else if(u.playlist2[0]==0&&u.playlist3[0]==0&&u.playlist4[0]==0&&u.playlist5[0]==0)
    {
        slots=4;/// 2,3,4,5 libres -> uso la playlist 2
    }else if(u.playlist3[0]==0&&u.playlist4[0]==0&&u.playlist5[0]==0)
    {
        slots=3;/// 3,4,5 libres -> uso la playlist 3
    }else if(u.playlist4[0]==0&&u.playlist5[0]==0)
    {
        slots=2;/// 4,5 libres -> uso la playlist 4
    }else if (u.playlist5[0]==0)
    {
        slots=1;/// 5 libre -> uso la playlist 5
    }
    return slots;
}
usuario MenuCrearPlaylist(char archivoMusica[],usuario u)
{
    int slots=DiceCuantosSlotsDePlaylistTenes(u);
    titulo();
    printf("\n Tenes 5 playlist como maximo para crear, te quedan %i slots ",slots);
    if(slots==0)
    {
        printf("\n\n Te sugiero eliminar una playlist o eliminar canciones de una playlist en 'Ver las Playlist' \n\n\n");
        system("pause");
        system("cls");
    }
    else
    {
       printf("\n\n Desea crear una nueva playlist ? ");
       printf("\n\n 1 - Si ");
       printf("\n\n 2 - NO ");
       char opcion=getch();
       system("cls");
       switch(opcion)
       {
          case(49):
          {
               if(slots==5)
               {
                 CrearPlayList(archivoMusica,u.playlist1);
               }else if(slots==4)
               {
                 CrearPlayList(archivoMusica,u.playlist2);
               }else if(slots==3)
               {
                 CrearPlayList(archivoMusica,u.playlist3);
               }else if(slots==2)
               {
                 CrearPlayList(archivoMusica,u.playlist4);
               }else if(slots==1)
               {
                 CrearPlayList(archivoMusica,u.playlist5);
               }
               break;
          }
          case(50):
          {
               break;
          }
       }
    }

    return u;
}
int cuentaElementosArchivo(FILE*copia)
{
    int rta=0;

    fseek(copia,0,SEEK_END);

    rta=ftell(copia)/sizeof(musica);

    return rta+1;//ningun id es==0 y esta rta es mi id. le sumo 1
}
void CargaDeArchivoDeMusica(char archivoMusica[])
{
    FILE*archi=fopen(archivoMusica,"ab");
    if(archi!=NULL)
    {
        int validos=0;
        char opcion='s';
        musica m;
        while(opcion=='s')
        {
            m.id=cuentaElementosArchivo(archi);
            printf("\n Tema con id : %i",m.id);
            printf("\n Ingrese el titulo de la cancion : ");
            fflush(stdin);
            gets(m.titulo);
            printf("\n Ingrese el artista de la cancion '%s' : ",m.titulo);
            fflush(stdin);
            gets(m.artista);
            printf("\n Ingrese el album de '%s' : ",m.titulo);
            fflush(stdin);
            gets(m.album);
            printf("\n Ingrese el genero de '%s' : ",m.titulo);
            fflush(stdin);//ser precabido y el genero debe estar bien escrito
            gets(m.genero);
            printf("\n Ingrese el anio de '%s' : ",m.titulo);
            scanf("%i",&m.anio);
            printf("\n Si es electronica, ingrese sus bpm's caso contrario ingrese 0 : ");
            scanf("%i",&m.bpm);
            fwrite(&m,sizeof(musica),1,archi);
            printf("\n Desea seguir agregando musica ? (s/n)");
            opcion=getch();
            system("cls");
        }
        fclose(archi);
    }
}
void ModularizadoMusica(musica m)
{
    printf(" %5d \t%-25.20s%-20.20s%-25.20s%-20.20s%6d%6d\n",m.id,m.titulo,m.artista,m.album,m.genero,m.anio,m.bpm);

    /*printf(" %7d \t  %-20.20s  %15.1f   %15.1f   %8d   \n",m);
    printf("\n ID.......: %i ",m.id);
    printf("\n Titulo...: %s ",m.titulo);
    printf("\n Artista..: %s ",m.artista);
    printf("\n Album....: %s ",m.artista);
    printf("\n Genero...: %s ",m.genero);
    printf("\n Anio.....: %i ",m.anio);
    printf("\n Bpm......: %i ",m.bpm);*/
}
void generaTituloSinSalto()
{
     int i=0;
     printf("\n");
     while(i<122)
     {
       printf("-");
       i++;
     }
}
void InvertirArregloint(int A[],int validos)
{
  int i=0;
  int aux=0;
  int cont=1;

  while(i<(validos-cont)&&(i!=(validos-cont)))
    {
       aux=A[i];
       A[i]=A[validos-cont];
       A[validos-cont]=aux;
       i++;
       cont++;
    }
}
void insertar(int a[],int u,int dato)
{
    int i=0;
    while(i>=0&&dato<a[i])
    {
        a[i+1]=a[i];
        i--;
    }
    a[1+i]=dato;
}

void ordenacion_insercion(int a[])
{
    int u=0;
    while(u<21)
    {
        insertar(a,u,a[u+1]);
        u++;
    }
}

int EliminarIDPlaylist(char playlist [],int idBorrar)
{
    int validos=RetornaValidosDePlayList(playlist);
    int i=0;
    int flag=0;
    //ordenacion_insercion(playlist);
    //InvertirArregloint(playlist,validos);
    while(i<validos&&flag==0)
    {
        if(playlist[i]==idBorrar)
        {
            playlist[i]=0;
            flag=1;
        }
        i++;
    }
    return flag;
}

void EliminaCancionesINTdePlaylist(char playlist [],char archivoMusica[])
{
    char opcion='s';
    int idBorrar=0;
    int flag=0;
    do{
      system("cls");
      titulo();
      MuestraPlaylistCanciones(playlist,archivoMusica);
      printf("\n Ingrese los ids de las canciones a eliminar ingrese 0 para volver:  ");
      scanf("%i",&idBorrar);
      flag=EliminarIDPlaylist(playlist,idBorrar);

      if(idBorrar==0)
      {
        printf("\n Volvamos para atrass...\n\n\n");
      }else if(flag==1)
            {
                printf("\n La cancion se elimino correctamente \n\n\n");
            }else
            {
                printf("\n El id es invalido, intentelo nuevamente n\n\n");
            }
        system("pause");
        system("cls");

    }while(opcion='s'&&idBorrar!=0&&playlist[0]!=0);
}

void MuestraPlaylistCanciones(int playlist[],char archivoMusica[])
{
    FILE*archi=fopen(archivoMusica,"rb");
    if(archi!=NULL)
    {
        musica m;
        int i=0;
        system("cls");
        titulo();
        printf("\n Canciones de la playlist elegida : ");
        generaTituloSinSalto();
        printf("    ID  TITULO                   ARTISTA             ALBUM                    GENERO                ANIO     BPM ");
        generaTituloSinSalto();
        while(fread(&m,sizeof(musica),1,archi)>0)
        {
            if(playlist[i]==m.id)
            {
                ModularizadoMusica(m);
                i++;
            }
        }
        generaGuion();
        fclose(archi);
    }
}
void ModificarPlaylist(int playlist[],char archivoMusica[])
{
    MuestraPlaylistCanciones(playlist,archivoMusica);

    printf("\n\n 1 - Desea eliminar la playlist ? ");///tendria q darle al usuario la opcion obligatoria de eliminar playlist desde la 5 a la 1
    printf("\n\n 2 - Desea eliminar canciones ? ");
    char opcion=getch();

    switch(opcion)
    {
    case(49):
        {
            printf("\n Esta a punto de eliminar la playlist esta seguro ? (s/n) ");
            char borrar=getch();
            system("cls");
            if(borrar=='s')
            {
              InicializaLaPlayList(playlist,21);
              titulo();
              printf("\n Su playlist a sido eliminada \n\n\n");
              system("pause");
              system("cls");
            }
            else
            {
                break;
            }
            break;
        }
    case (50):
        {
            EliminaCancionesINTdePlaylist(playlist,archivoMusica);
            break;
        }
    }
}

usuario MenuVerLasPlaylist(char archivoMusica[],usuario u)
{

     char opcion='s';
     system("cls");
     titulo();
     printf("\n Playlist's : \n");


     if(u.playlist1[0]!=0)
     {
        printf("\n 1 - Playlist 1 ");
     }
     if(u.playlist2[0]!=0)
     {
        printf("\n 2 - Playlist 2 ");
     }
     if(u.playlist3[0]!=0)
     {
        printf("\n 3 - Playlist 3 ");

     }if(u.playlist4[0]!=0)
     {
        printf("\n 4 - Playlist 4 ");

     }if(u.playlist5[0]!=0)
     {
        printf("\n 5 - Playlist 5 ");
     }
     if(u.playlist1[0]==0&&u.playlist2[0]==0&&u.playlist3[0]==0&&u.playlist4[0]==0&&u.playlist5[0]==0)
     {
         printf("\n No hay ninguna playlist :/ \n\n\n");
         system("pause");
         system("cls");
     }else
     {
        printf("\n\n Ingrese el id de la playlist a ver o presione 0 para volver : ");
        opcion=getch();
        system("cls");
     }
     switch(opcion)
     {
      case(49):
        {
          if(u.playlist1[0]!=0)
          {
              ModificarPlaylist(u.playlist1,archivoMusica);
          }
          else
          {
             break;
          }
          break;
        }
      case(50):
        {
          if(u.playlist2[0]!=0)
          {
              ModificarPlaylist(u.playlist2,archivoMusica);

          }
          else
          {
             break;
          }
          break;
        }
      case(51):
        {
           if(u.playlist3[0]!=0)
          {
              ModificarPlaylist(u.playlist3,archivoMusica);
          }
          else
          {
             break;
          }
          break;
        }
      case(52):
        {
           if(u.playlist4[0]!=0)
          {
              ModificarPlaylist(u.playlist4,archivoMusica);
          }
          else
          {
             break;
          }
          break;
        }
      case(53):
        {
            if(u.playlist5[0]!=0)
          {
              ModificarPlaylist(u.playlist5,archivoMusica);
          }
          else
          {
             break;
          }
          break;

        }
      case(48):/// 0
        {
            break;
        }
     }
     return u;

}

void VerArchivoDeMusica(char archivoMusica[])///admin
{
    FILE*archi=fopen(archivoMusica,"rb");
    if(archi!=NULL)
    {
        musica m;
        printf("\n Archivo de Musica : \n");
        generaTituloSinSalto();
        printf("    ID  TITULO                   ARTISTA             ALBUM                    GENERO                ANIO     BPM ");
        generaTituloSinSalto();
        char metal[20]={"Metal"};
        char rock[20]={"Rock Nacional"};
        int i=0;
        while(fread(&m,sizeof(musica),1,archi)>0)
        {
            //if(strcmp(m.genero,metal)==0)
            //{
               ModularizadoMusica(m);
            //}
        }
        fclose(archi);
        generaGuion();
    }
}
void CambiaCosasDeArchivoYGeneraCopia(char archivoMusica[])///admin
{
    FILE*musicaa=fopen(archivoMusica,"r+b");
    if(musicaa!=NULL)
    {
        musica m;
        char album[30]={"Otro Dia"};
       while(fread(&m,sizeof(musica),1,musicaa)>0)
       {
           if(m.id==98)
           {
              strcpy(m.album,album);
              fwrite(&m,sizeof(musica),1,musicaa);
           }

       }
       fclose(musicaa);
    }
}
void GuardaEnArchivoUsuarioLasPlaylist(char archivoUsuario[],usuario u)///admin
{
    FILE*archi=fopen(archivoUsuario,"r+b");
    int flag=0;
    usuario dato;
    usuario u1;
    usuario u2;
    if(archi!=NULL)
    {
        while(fread(&dato,sizeof(usuario),1,archi)>0&&flag==0)
        {
            if(strcmp(dato.nUsuario,u.nUsuario)==0)
            {
                u1=dato;
                dato=u; //lo modificamos
                u2=dato;
                fseek(archi,sizeof(usuario)*-1,SEEK_CUR);
                fwrite(&dato,sizeof(musica),1,archi);
                flag=1;
            }

        }
         fclose(archi);
    }
     /*system("cls");
     printf("\n Dato que encontramos a cambiar (sin cambiar) : ");
     Muestra1Usuario(u1);
     printf("\n registro que era dato ahora es u : ");
     Muestra1Usuario(u2);
     system("pause");*/
}
void VerArchivoDeUsuarios(char archivoUsuario[])///admin
{
    FILE*archi=fopen(archivoUsuario,"rb");
    if(archi!=NULL)
    {
        usuario u;
        while(fread(&u,sizeof(usuario),1,archi)>0)
        {
            Muestra1Usuario(u);
        }
        fclose(archi);
        generaGuion();
    }
}
void ModificaElArchivo(char archivoMusica[],char copiaMusica[])///admin
{
    FILE*archi=fopen(archivoMusica,"rb");
    FILE*copia=fopen(copiaMusica,"wb");
    if(archi!=NULL&&copia!=NULL)
    {
        musica m;
        musica dato;
        char rock[]={"Rock"};
        char metal[]={"Metal"};
        char trap[]={"Trap"};
        char traparge[]={"Trap Argentino"};
        char techno[]={"Techno"};
        char progre[]={"Progressive"};
        char psytrance[]={"Psy Trance"};
        char dubstep[]={"Dubstep"};
        char pop[]={"Pop"};
        char rocknacio[]={"Rock Nacional"};

        int r=0;
        int met=0;
        int t=0;
        int traparg=0;
        int tech=0;
        int pro=0;
        int psy=0;
        int dub=0;
        int popp=0;
        int rnac=0;

        while(fread(&m,sizeof(musica),1,archi)>0)
        {
            musica dato;
            if(strcmp(m.genero,rock)==0&&r<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                r++;
            }else if(strcmp(m.genero,metal)==0&&met<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                met++;
            }else if(strcmp(m.genero,trap)==0&&t<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                t++;
            }else if(strcmp(m.genero,traparge)==0&&traparg<5)
            {
               dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                traparg++;
            }else if(strcmp(m.genero,techno)==0&&tech<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                tech++;
            }else if(strcmp(m.genero,progre)==0&&pro<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                pro++;
            }else if(strcmp(m.genero,psytrance)==0&&psy<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                psy++;
            }else if(strcmp(m.genero,dubstep)==0&&dub<5)
            {
               dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                dub++;
            }else if(strcmp(m.genero,pop)==0&&popp<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                popp++;
            }else if(strcmp(m.genero,rocknacio)==0&&rnac<5)
            {
                dato=m;
                dato.id=cuentaElementosArchivo(copia);
                fwrite(&dato,sizeof(musica),1,copia);
                rnac++;
            }
         }
         fclose(archi);
         fclose(copia);
     }
}
int main()
{
    usuario u;
    char archivoUsuario[]={"usuario.bin"};
    char archivoMusica[]={"canciones.bin"};

     //VerArchivoDeUsuarios(archivoUsuario);

    //char copiaMusica[]={""};
    //CambiaCosasDeArchivoYGeneraCopia(archivoMusica);
    //ModificaElArchivo(archivoMusica,copiaMusica);
    //VerArchivoDeMusica(copiaMusica);


    char opcion=IntroduccionMenu();
    system("cls");
    switch(opcion)
    {
     case(49):
        {
           u=Registrarse(archivoUsuario,u);
           break;
        }
     case(50):
        {
           u=IniciarSesion(archivoUsuario,u);
           break;
        }
     case(51):
        {
            salir();
            return 0;
            break;
        }
    }
    do{
      opcion=MenuLuegoDeIniciarSesion(u);
      system("cls");
      switch(opcion)
      {
        case(49):
           {
             u=MenuCrearPlaylist(archivoMusica,u);
             break;
           }
        case(50):
           {
             u=MenuVerLasPlaylist(archivoMusica,u);
             break;
           }
        //case(51):
          // {
          //    break;
          // }
        //case(52):
          // {
          //
          //    break;
          // }
        //case(53):
          // {
          //
          // break;
          // }
        case(54):
             {
              GuardaEnArchivoUsuarioLasPlaylist(archivoUsuario,u);
              salir();
              break;
           }
       }
    }while(opcion!=54);

}
