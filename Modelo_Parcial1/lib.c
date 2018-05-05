#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

#define OCUPADO 1
#define LIBRE 0

#------------- Genericas -------------#
void menu(char *opciones)
{
    system("cls");
    printf("%s \n",opciones);
    printf("\n0.  Salir \n");
    printf("\n\tIngrese Opcion: ");
}

char *get_char(char *sms,int LongitudCadena)
{
    char *PTexto= (char *) malloc (sizeof(char)*LongitudCadena);
    char *TextoLibre=(char *) malloc (sizeof(char)*LongitudCadena+4);
    fflush(stdin);
    int flag=0;
    do
    {
        printf("%s ",sms);
        fgets(TextoLibre,LongitudCadena+3,stdin);
        if(flag==1)
        {
            printf("\n La longitud maxima del campo es: %d \n",LongitudCadena);
            system("pause");
            system("cls");
        }
        flag=1;
    }while(strlen(TextoLibre) >= LongitudCadena);

    strcpy(PTexto,TextoLibre);
    return PTexto;
}

int get_int(char *sms)
{
    int Numero;
    int flag=0;
    do
    {
        printf("%s ",sms);
        scanf("%d",&Numero);
        if(Numero<=0)
        {
            flag=1;
        }
        if(flag==1)
        {
            printf("\n No es un ID valido \n");
            system("pause");
            system("cls");
        }
        flag=0;
    }while(Numero <= 0);
    return Numero;
}

void sms_error(int mensaje,int Error)
{
    switch(mensaje)
    {
        case 1:
            Printf("Se produjo un Error en la alta de Usuarios -- COD: %d",Error);
            break;
        case 2:
            Printf("Se produjo un Error al mostrar Usuarios -- COD: %d",Error);
            break;
        case 3:
            Printf("Se produjo un Error al Modificar datos del Usuario -- COD: %d",Error);
            break;
        case 4:
            Printf("Se produjo un Error No se encontro el ID del Usuario -- COD: %d",Error);
            break;
        case 5:
            Printf("Se produjo un Error al Eliminar un Usuario -- COD: %d",Error);
            break;
        default:
            Printf("Se produjo un Error Inesperado...");
            break;
    }
}

#------------- Con estructuras -------------#
void inicializa_usuarios( eUsuario listado[],int limite)
{
    if(limite > 0 && listado != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            listado[i].estado= LIBRE;
            listado[i].id= 0;
        }
    }
}
void inicializa_user_Prod(eProducto_Usuario listado[],int limite)
{
    if(limite > 0 && listado != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            listado[i].id_producto=0;
            listado[i].id_usuario=0;
            listado[i].stock=0;
        }
    }
}

void inicializa_Ventas(eVentas listado[],int limite)
{
    if(limite > 0 && listado != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            listado[i].id_producto=0;
            listado[i].id_usuario_compra=0;
        }
    }
}

int eGen_buscarLugarLibre(eUsuario listado[],int limite)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(int i=0;i<limite;i++)
        {
            if(listado[i].estado== LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int eGen_siguienteId(eUsuario listado[],int limite)
{
    int retorno = 0;
    if(limite > 0 && listado != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            if(listado[i].estado == OCUPADO)
            {
                    if(listado[i].id>retorno)
                    {
                         retorno=listado[i].id;
                    }
            }
        }//FIN for(int i=0; i<limite; i++)
    }
    return retorno+1;
}

int eGen_alta_usuario(eUsuario  listado[],int limite)
{
    int retorno = -1;
    int indice;

    if(limite > 0 && listado != NULL)
    {//no me exedi de la longitud del vector
        retorno = -2;
        indice = eGen_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            listado[indice].id = eGen_siguienteId(listado,limite);
            listado[indice].estado= OCUPADO;

            strcpy(listado[indice].nombre,get_char("\n Ingrese Nombre: ",50));
            strcpy(listado[i].password,get_char("\n Ingrese Password: ",10));
            retorno = 0;
        }//FIN if(indice >= 0)
    }//FIN if(limite > 0 && listado != NULL)
    return retorno;
}


int eGen_mostrarUno(eUsuario record)
{
     printf("\n ID: %d  -- %s  ", record.id,record.nombre);
}

int eGen_mostrarUsuarios(eUsuario listado[],int limite)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(int i=0; i<limite; i++)
        {
            if(listado[i].estado==OCUPADO)
            {
                eGen_mostrarUno(listado[i]);
            }
        }
    }
    return retorno;
}


int eGen_buscarPorId(eUsuario listado[] ,int limite, int id)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(int i=0;i<limite;i++)
        {
            if(listado[i].estado == OCUPADO && listado[i].idGenerica == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int eGen_modificacion(eUsuario listado[] ,int limite, int id)
{
    int retorno = -1;
    int posmodifica;

    posmodifica=eGen_buscarPorId(listado,limite,id);

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;

        if(posmodifica >= 0)
        {
            retorno = 0;
            strcpy(listado[indice].nombre,get_char("\n Ingrese Nombre: ",50));
            strcpy(listado[i].password,get_char("\n Ingrese Password: ",10));
            listado[posmodifica].estado = OCUPADO;
        }
    }
    return retorno;
}

int eGen_baja_usuario(eUsuario listado[] ,int limite, int id)
{
    int retorno = -1;
    int PosID;
    PosID=eGen_buscarPorId(listado ,limite, id);
    if(PosID>=0)
    {
        retorno = 0;
        listado[PosID].estado==0;
    }
    else
    {
        retorno = -2;
        sms_error(4,Error);
    }
    return retorno;
}


int eGen_baja_ProductosXUsuarios(eUsuario usuarios[] ,int cant_usuario, int id_usuario, eProducto_Usuario prodXuser, int cant_prodXuser )
{
    int retorno = -1;
    if( eGen_baja_usuario(usuarios ,cant_usuario, id_usuario) == 0)
    {
        retorno = 0;
        for(int i =0;i<cant_prodXuser;i++)
        {
            if(prodXuser.id_usuario==id_usuario)
            {
                prodXuser.id_producto=0;
            }
        }
    }
    else
    {
        retorno = -2;
    }
    return retorno;
}

#--------- No vistas ------#

float get_PromedioClasificacion_usuario(int id_usuario)
{//recorrer tabla vendidas para dicho usuario y calcular
    int SumaClasificaciones=0;
    int Cant_Total_Vendido=0;


}

int eGen_mostrarUno_Clasificacion(eUsuario record,float Clasificacion)
{
     printf("\n ID: %d  -- %s  -- Clasificacion: 2%f", record.id,record.nombre,Clasificacion );

}

int eGen_mostrarUsuarios_Clasificacion(eUsuario usuarios[] ,int cant_usuario, eProducto_Usuario prodXuser, int cant_prodXuser,eVentas Ventas_Usuario)
{
    int retorno = -1;
    if(cant_usuarios > 0 && usuarios != NULL)
    {
        retorno = 0;
        for(int i=0; i<cant_usuarios; i++)
        {
            if(usuarios[i].estado==OCUPADO)
            {
                eGen_mostrarUno(usuarios[i]);
            }
        }
    }
    return retorno;
}