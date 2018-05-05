#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib.h"

#define OCUPADO 1
#define LIBRE 0

//#------------- Genericas -------------#
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

    int flag;
    do
    {
        flag=0;
        printf("%s ",sms);
        fflush(stdin);
        fgets(TextoLibre,LongitudCadena+3,stdin); //Trunco la lectura del buffer en 3 mas de mi longitud
        strncpy(PTexto, TextoLibre, LongitudCadena); // Copio la cantidad de caracteres hasta 1 menos de la longitud
        PTexto[sizeof(PTexto) -1] = '\n';        //agrego retorno de carro

        //printf("\nL:%s T:%s Dif:%d TAM:%d ultimo:[%c] Overflow:[%c] \n",TextoLibre,PTexto,strcmp(PTexto,TextoLibre),sizeof(PTexto),PTexto[LongitudCadena-1],PTexto[sizeof(PTexto)]);
        //system("pause");

        //if(strlen(PTexto) >= LongitudCadena) //el strlen funciona para atras... en estos casos asique no sirve..
        if(strcmp(PTexto,TextoLibre)<0)
        {//overflow
            flag=1;
        }
        if(flag==1)
        {
            printf("\n Error Overflow: La longitud maxima del campo es: %d \n",LongitudCadena);
            system("pause");
            system("cls");
        }
    }while(flag!=0);

    strcpy(PTexto,strtok(TextoLibre, "\n"));
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
        if(isdigit(Numero))
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

int get_int_con_exit(char *sms)
{
    int Numero;
    int flag=0;

    int buffer[11];
    int aux[10];

    fflush(stdin);
    fgets(buffer,11,stdin);
    strcpy(aux,buffer);
    if(isalnum(aux)==0)
    {
        if(isalpha(aux)!=0)
        {//es numero
            Numero=atoi(aux);
        }
    }



    system("pause");


    do
    {
        printf("%s (Cualquier caracter no Numerico Para Cancelar)",sms);
        scanf("%d",&Numero);

    }while(Numero <= 0);
    return Numero;
}

void sms_error(int mensaje,int Error)
{
    switch(mensaje)
    {
        case 1:
            printf("Se produjo un Error en la alta de Usuarios -- COD: %d",Error);
            break;
        case 2:
            printf("Se produjo un Error al mostrar Usuarios -- COD: %d",Error);
            break;
        case 3:
            printf("Se produjo un Error al Modificar datos del Usuario -- COD: %d",Error);
            break;
        case 4:
            printf("Se produjo un Error No se encontro el ID del Usuario -- COD: %d",Error);
            break;
        case 5:
            printf("Se produjo un Error al Eliminar un Usuario -- COD: %d",Error);
            break;
        default:
            printf("Se produjo un Error Inesperado...");
            break;
    }
}

//#------------- Con estructuras -------------#
int inicializa_usuarios( eUsuario listado[],int limite)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(int i=0; i<limite; i++)
        {
            listado[i].estado= LIBRE;
            listado[i].id= 0;
        }
    }
    return retorno;
}
int inicializa_user_Prod(eProducto_Usuario listado[],int limite)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(int i=0; i<limite; i++)
        {
            listado[i].id_producto=0;
            listado[i].id_usuario=0;
            listado[i].stock=0;
        }
    }
    return retorno;
}

int inicializa_Ventas(eVentas listado[],int limite)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(int i=0; i<limite; i++)
        {
            listado[i].id_venta=0;
            listado[i].id_producto=0;
            listado[i].id_usuario_vende=0;
        }
    }
    return retorno;
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
            strcpy(listado[indice].password,get_char("\n Ingrese Password: ",10));
            retorno = 0;
        }//FIN if(indice >= 0)
    }//FIN if(limite > 0 && listado != NULL)
    return retorno;
}


void eGen_mostrarUno(eUsuario record)
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
            if(listado[i].estado == OCUPADO && listado[i].id == id)
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
    int PosID;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        PosID=eGen_buscarPorId(listado,limite,id);
        if(PosID >= 0)
        {
            retorno = 0;
            strcpy(listado[PosID].nombre,get_char("\n Ingrese Nombre: ",50));
            strcpy(listado[PosID].password,get_char("\n Ingrese Password: ",10));
            listado[PosID].estado = OCUPADO;
        }
        else
        {//en este caso PosID va a tener el codigo de error...
            retorno = -3;
            sms_error(4,PosID);
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
        listado[PosID].estado=0;
    }
    else
    {//en este caso PosID va a tener el codigo de error...
        retorno = -2;
        sms_error(4,PosID);
    }
    return retorno;
}

int eGen_baja_Productos_de_Usuario(int id_usuario,eProducto_Usuario prodXuser[], int cant_prodXuser)
{
    int retorno = -1;
    if(cant_prodXuser > 0 && prodXuser != NULL)
    {
        retorno = 0;
        for(int i=0;i<cant_prodXuser;i++)
        {
            if(prodXuser[i].id_usuario==id_usuario)
            {
                prodXuser[i].id_producto=0;
                prodXuser[i].id_usuario=0;
                prodXuser[i].stock=0;
            }
        }//fin for(int i =0;i<cant_prodXuser;i++)
    }
    return retorno;
}

int eGen_baja_Ventas_de_Usuario(int id_usuario,eVentas ventas_user[],int cant_ventas_user)
{
    int retorno = -1;
    if(cant_ventas_user > 0 && ventas_user != NULL)
    {
        retorno = 0;
        for(int i=0;i<cant_ventas_user;i++)
        {
            if(ventas_user[i].id_usuario_vende==id_usuario)
            {
                ventas_user[i].id_venta=0;
                ventas_user[i].id_usuario_vende=0;
                ventas_user[i].id_producto=0;
            }
        }//fin for(int i =0;i<cant_prodXuser;i++)
    }
    return retorno;
}

int eGen_baja_Usuario_productos_ventas(eUsuario usuarios[] ,int cant_usuario, int id_user_borrar, eProducto_Usuario prodXuser[], int cant_prodXuser,eVentas Ventas_User[],int cant_ventas_user)
{
    int retorno = -1;
    if( eGen_baja_usuario(usuarios ,cant_usuario, id_user_borrar) == 0)
    {//Borro un usuario de la tabla usuarios
        retorno = 0;
        if(eGen_baja_Productos_de_Usuario(id_user_borrar,prodXuser,cant_prodXuser)!=0)
        {
            retorno =-3;
        }
        if(eGen_baja_Ventas_de_Usuario(id_user_borrar,Ventas_User,cant_ventas_user)!=0)
        {
            retorno = -4;
        }
    }
    else
    {
        retorno = -2;
    }//FIN     if( eGen_baja_usuario(usuarios ,cant_usuario, id_user_borrar) == 0)
    return retorno;
}

//#--------- No vistas ------#
/*
float get_PromedioClasificacion_usuario(int id_usuario)
{//recorrer tabla vendidas para dicho usuario y calcular
    int SumaClasificaciones=0;
    int Cant_Total_Vendido=0;


}

int eGen_mostrarUno_Clasificacion(eUsuario record,float Clasificacion)
{
     printf("\n ID: %d  -- %s  -- Clasificacion: 2%f", record.id,record.nombre,Clasificacion );

}

int eGen_mostrarUsuarios_Clasificacion(eUsuario usuarios[] ,int cant_usuarios, eProducto_Usuario prodXuser, int cant_prodXuser,eVentas Ventas_Usuario)
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
*/
