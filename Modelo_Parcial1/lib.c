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

        if(strlen(PTexto) >= LongitudCadena) //el strlen funciona para atras... en estos casos asique no sirve..
        //if(strcmp(PTexto,TextoLibre)<0)
        {//overflow
            flag=1;
            //flag=0;// si lleno mucho el buffer se boludea igual....
            fflush(stdin);
            *PTexto=' ';
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
    do
    {
        fflush(stdin);
        printf("%s ",sms);
        scanf("%d",&Numero);
    }while(Numero <= 0);
    return Numero;
}

int get_int_entre(char *sms,int minimo,int maximo)
{
    int Numero;
    int flag;
    do
    {
        flag=0;
        fflush(stdin);
        printf("%s : ",sms,minimo,maximo);
        scanf("%d",&Numero);
        if((Numero<minimo) || (Numero>maximo))
        {
            printf("\nEl Nro a ingresar debe ser  %d < X < %d ",minimo,maximo);
            flag=1;
        }
    }while(flag==1);
    return Numero;
}

int get_int_con_exit(char *sms)
{
    int Numero;
    int flag=0;

    char buffer[11];
    char aux[10];

    fflush(stdin);
    fgets(buffer,11,stdin);
    strcpy(aux,buffer);
    Numero=atoi(aux);
    if(isalnum(Numero)==0)
    {
        if(isalpha(Numero)!=0)
        {//es numero
            flag=1;
        }
    }
    printf("\nFlag=1 es numero... Valor flag: %d\n",flag);


    system("pause");


    do
    {
        printf("%s (Cualquier caracter no Numerico Para Cancelar)",sms);
        scanf("%d",&Numero);

    }while(Numero <= 0);
    return Numero;
}

float get_float(char *sms)
{
    float Numero;
    do
    {
        printf("%s ",sms);
        scanf("%f",&Numero);
        if(Numero<=0)
        {
            printf("\nValor invalido, debe ser mayor que 0.. ");
            system("pause");
            system("cls");
        }
    }while(Numero <= 0);
    return Numero;
}


void sms_error(int mensaje,int Error)
{
    printf("\n\n");
    switch(mensaje)
    {
        case 1:
            printf("ERROR-COD: %d -- ALTA DE USUARIO",Error);
            break;
        case 2:
            printf("ERROR-COD: %d -- MODIFICAR DATOS DEL USUARIO",Error);
            break;
        case 3:
            printf("ERROR-COD: %d -- BAJA DEL USUARIO ",Error);
            break;
        case 4:
            printf("ERROR-COD: %d -- PUBLICAR PRODUCTO",Error);
            break;
        case 5:
            printf("ERROR-COD: %d -- MODIFICAR PUBLICACION",Error);
            break;
        case 6:
            printf("ERROR-COD: %d -- CANCELAR PUBLICACION",Error);
            break;
        case 7:
            printf("ERROR-COD: %d -- COMPRAR PRODUCTO",Error);
            break;
        case 8:
            printf("ERROR-COD: %d -- LISTAR PUBLICACIONES DE USUARIO",Error);
            break;
        case 9:
            printf("ERROR-COD: %d -- LISTAR PUBLICACIONES",Error);
            break;
        case 10:
            printf("ERROR-COD: %d -- LISTAR USUARIOS",Error);
            break;
        case 99:
            printf("ERROR-COD: %d -- No Encontro ID del Usuario ",Error);
            break;
        default:
            printf("Se produjo un Error Inesperado...");
            break;
    }
    printf("\n\n");
    system("pause");
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
            sms_error(99,PosID);
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
        sms_error(99,PosID);
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


int eGen_buscarLugarLibre_productos(eProducto_Usuario listado[],int limite)
{
    int retorno = -1;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(int i=0;i<limite;i++)
        {
            if((listado[i].id_producto == 0) && (listado[i].id_usuario == 0))
            {
                retorno = i;
                break;
            }
        }
    }//FIN if(limite > 0 && listado != NULL)
    return retorno;
}

int eGen_siguienteId_Producto(eProducto_Usuario listado[],int limite,int ID_User)
{
    int retorno = 0;
    if(limite > 0 && listado != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            if(listado[i].id_usuario == ID_User)
            {
                if(listado[i].id_producto > retorno)
                {
                    retorno=listado[i].id_producto;
                }
            }
        }//FIN for(int i=0; i<limite; i++)
    }
    return retorno+1;
}
int valida_password(char *validar,char *password)
{
    int retorno=-10;
    int aux;
    if(validar!=NULL && password!=NULL)
    {
        retorno=-100;
        aux=strcmp(validar,password);
        if(aux == 0)
        {
            retorno=aux;
        }
        else
        {
            retorno=retorno+aux;
        }//FIN if(aux == 0)
    }//FIN if(validar!=NULL && password!=NULL)
    return retorno;
}

int eGen_Publicar_Producto(eUsuario usuarios[],int cant_usuarios,eProducto_Usuario prodXuser[],int Cant_ProdXuser)
{
    int retorno=-1;
    int ID_User;
    int PosID;
    char clave[10];
    int PosID_Prod;
    if(cant_usuarios > 0 && usuarios != NULL && Cant_ProdXuser >0 && prodXuser !=NULL)
    {
        retorno = -2;

        ID_User=get_int("\nIngrese su ID de usuario: ");
        PosID=eGen_buscarPorId(usuarios,cant_usuarios,ID_User);
        if(PosID>=0)
        {//usuario existe
            retorno=-3;
            strcpy(clave,get_char("\n Ingrese Password: ",10));
            if(valida_password(clave,usuarios[PosID].password) == 0)
            {//Clave correcta
                retorno=-4;
                PosID_Prod=eGen_buscarLugarLibre_productos(prodXuser,Cant_ProdXuser);
                if(PosID_Prod>=0)
                {
                    retorno=0;
                    prodXuser[PosID_Prod].id_usuario=ID_User;
                    prodXuser[PosID_Prod].id_producto=eGen_siguienteId_Producto(prodXuser,Cant_ProdXuser,ID_User);
                    strcpy(prodXuser[PosID_Prod].nombre,get_char("\n Ingrese Nombre del Producto: ",50));
                    prodXuser[PosID_Prod].precio=get_float("\n Ingrese Precio del producto: ");
                    prodXuser[PosID_Prod].stock=get_int("\n Ingrese stock: ");
                    //prodXuser[PosID_Prod]
                }
                else
                {
                    retorno = -5;
                }//FIN if(PosID_Prod)>0)
            }
            else
            {//Error de password
                retorno=-6;
            }//FIN if(strcmp(clave,usuarios[PosID].password) == 0)
        }//FIN if(PosID>0)
    }//if(cant_usuarios > 0 && usuarios != NULL && Cant_ProdXuser >0 && prodXuser !=NULL)
    return retorno;
}

int get_cantVendidos_Producto(int ID_User, int ID_Prod,eVentas listado[],int limite)
{
    int retorno = -1;
    int contador=0;
    if(limite > 0 && listado != NULL)
    {
        retorno =-2;
        for(int i=0;i<limite;i++)
        {
            if( (listado[i].id_usuario_vende==ID_User) && ( listado[i].id_producto==ID_Prod)  )
            {
                contador++;
            }
        }//for(int i=0;i<limite;i++)
    }
    if(retorno==-2)
    {
        retorno=contador;
    }
    return retorno;
}

int eGen_Lista_Publicaciones_Usuario(int ID_User,eUsuario usuarios[],int cant_user,eVentas ventas[],int cant_ventas,eProducto_Usuario prodXuser[],int cant_prod)
{
    int retorno =-1;
    int aux;
    int PosID;
    PosID=eGen_buscarPorId(usuarios,cant_user,ID_User);
    if(PosID>=0)
    {//usuario existe
        retorno =0;
        system("cls");
        printf("\n ID: %d - Nombre: %s",usuarios[PosID].id,usuarios[PosID].nombre);
        printf("\n---------- Productos en Venta -----------------------\n");
        for(int i=0;i<cant_prod;i++)
        {//recorro los productos
            if(prodXuser[i].id_usuario==usuarios[PosID].id)
            {//propuctos de este usuario
                //id, nombre, precio, cantidad vendida y stock.
                printf("\nID Producto: %d ",prodXuser[i].id_producto);
                printf("\nNombre: %s ",prodXuser[i].nombre);
                printf("\nPrecio: %.2f ",prodXuser[i].precio);
                printf("\nStok: %d ",prodXuser[i].stock);

                aux=get_cantVendidos_Producto(ID_User,prodXuser[i].id_producto,ventas,cant_ventas);
                if(aux>=0)
                {
                    printf("\nCantidad Vendida: %d ",aux);
                }
                else
                {
                    retorno =-3;
                }
                printf("\n");
            }//if(prodXuser[i].id_usuario==usuarios[PosID].id)
        }//for(int i=0;i<cant_prod;i++)
        printf("\n");
    }
    return retorno;
}

int eGen_modificar_Publicacion(int ID_Usuario,int ID_Producto,eProducto_Usuario prodXuser[],int cant_prod ,eUsuario usuarios[],int cant_usuarios)
{
    int retorno=-1;
    char clave[10]={""};
    int PosID;
    PosID=eGen_buscarPorId(usuarios,cant_usuarios,ID_Usuario);
    if(PosID>=0)
    {
        retorno=-2;
        strcpy(clave,get_char("\n Ingrese Password: ",10));
        if(valida_password(clave,usuarios[PosID].password) == 0)
        {
            retorno=-3;
            for(int i=0;i<cant_prod;i++)
            {
                if( (prodXuser[i].id_usuario==ID_Usuario) && (prodXuser[i].id_producto==ID_Producto))
                {
                    retorno=0;
                    prodXuser[i].precio=get_float("\n Ingrese Precio del producto: ");
                    prodXuser[i].stock=get_int("\n Ingrese stock: ");
                }
            }//FIN for(int i=0;i<cant_prod;i++)
        }//FIN if(valida_password(clave,usuarios[PosID].password) == 0)
    }//FIN if(PosID>=0)
    return retorno;
}

int eGen_cancelar_Publicacion(int ID_Usuario,int ID_Producto,eProducto_Usuario prodXuser[],int cant_prod ,eUsuario usuarios[],int cant_usuarios)
{
    int retorno=-1;
    char clave[10]={""};
    int PosID;
    PosID=eGen_buscarPorId(usuarios,cant_usuarios,ID_Usuario);
    if(PosID>=0)
    {
        retorno=-2;
        strcpy(clave,get_char("\n Ingrese Password: ",10));
        if(valida_password(clave,usuarios[PosID].password) == 0)
        {
            retorno=-3;
            for(int i=0;i<cant_prod;i++)
            {
                if( (prodXuser[i].id_usuario==ID_Usuario) && (prodXuser[i].id_producto==ID_Producto))
                {
                    retorno=0;
                    prodXuser[i].id_producto=0;
                    prodXuser[i].id_usuario=0;
                }
            }//FIN for(int i=0;i<cant_prod;i++)
        }//FIN if(valida_password(clave,usuarios[PosID].password) == 0)
    }//FIN if(PosID>=0)
    return retorno;
}

int eGen_Lista_Todas_Publicaciones(eUsuario usuarios[],int cant_usuarios,eVentas ventas[],int cant_ventas,eProducto_Usuario prodXuser[],int cant_prod)
{
    int retorno=-1;
    for(int i=0;i<cant_usuarios;i++)
    {
        if(usuarios[i].estado==OCUPADO)
        {
                retorno=-2;
                if(eGen_Lista_Publicaciones_Usuario(usuarios[i].id,usuarios,cant_usuarios,ventas,cant_ventas,prodXuser,cant_prod)==0 )
                {
                    retorno=0;
                }
                else
                {
                    retorno=-3;
                }//FIN if(eGen_Lista_Publicaciones_Usuario(usuarios[i].id,usuarios,cant_usuarios,ventas,cant_ventas,prodXuser,cant_prod)==0 )
        system("pause");
        }//FIN if(usuarios[i].estado==OCUPADO)
    }//FIN for(int i=0;i<cant_usuarios;i++)
    return retorno;
}

int eGen_siguienteId_Venta(eVentas listado[],int limite)
{
    int retorno = 0;
    if(limite > 0 && listado != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            if(listado[i].id_venta==OCUPADO)
            {
                    if(listado[i].id_venta > retorno)
                    {
                         retorno=listado[i].id_venta;
                    }
            }
        }//FIN for(int i=0; i<limite; i++)
    }
    return retorno+1;
}

int AltaVenta(eVentas ventas[],int cant_ventas,int ID_Usuario,int ID_Producto,int Cant_Items )
{
    int retorno=-1;
    for(int i=0;i<cant_ventas;i++)
    {
        if(ventas[i].id_venta==0)
        {
            retorno =0;
            ventas[i].id_venta=eGen_siguienteId_Venta(ventas,cant_ventas);
            ventas[i].id_usuario_vende=ID_Usuario;
            ventas[i].id_producto=ID_Producto;
            ventas[i].cantVendidos=Cant_Items;
            ventas[i].clasificacion=get_int_entre("\nPor favor califique al vendedor (1<-X->10):",0,11);
        }
    }
    return retorno;
}

int Comprar_producto_usuario(int ID_Usuario,int ID_Producto,eVentas ventas[],int cant_ventas,eProducto_Usuario prodXuser[],int cant_prod)
{
    int retorno=-1;
    int Cant_Comprar;
    float costo;
    for(int i=0;i<cant_prod;i++)
    {
        if( (prodXuser[i].id_usuario==ID_Usuario) && (prodXuser[i].id_producto==ID_Producto))
        {
            retorno=-2;
            if(prodXuser[i].stock>0)
            {
                retorno=0;
                Cant_Comprar=get_int_entre("\nIngrese cantidad a comprar ",0,prodXuser[i].stock + 1);
                prodXuser[i].stock=prodXuser[i].stock - Cant_Comprar;
                costo=prodXuser[i].precio*Cant_Comprar;
                printf("\n\n El costo Total de la compra es: %.2f ",costo);
                if(AltaVenta(ventas,cant_ventas,ID_Usuario,ID_Producto,Cant_Comprar) != 0 )
                {//quedo la base inconsistente
                    retorno=-4;
                }
            }
            else
            {
                printf("\n No puede comprar este producto se acabo el stock.");
                retorno=-3;
            }//FIN if(prodXuser[i].stock>0)
        }
    }//FIN for(int i=0;i<cant_prod;i++)



    return retorno;
}

//#--------- No vistas ------#

float get_PromedioClasificacion_usuario(int ID_Usuario,eVentas ventas[],int cant_ventas)
{//recorrer tabla vendidas para dicho usuario y calcular
    int SumaClasificaciones=0;
    int Cant_Total_Vendido=0;
    float promedio;
    for(int i=0;i<cant_ventas;i++)
    {
        if(ventas[i].id_usuario_vende == ID_Usuario)
        {
            SumaClasificaciones=SumaClasificaciones+ventas[i].clasificacion;
            Cant_Total_Vendido++;
        }
    }
    if(Cant_Total_Vendido==0)
    {
        promedio=0;
    }
    else
    {
        promedio=SumaClasificaciones/Cant_Total_Vendido;
    }
    return promedio;
}

void eGen_mostrarUno_Clasificacion(eUsuario record,float Clasificacion)
{
     printf("\n ID: %d  -- %s  -- Clasificacion: %.2f", record.id,record.nombre,Clasificacion );

}

int eGen_mostrarUsuarios_Clasificacion(eUsuario usuarios[] ,int cant_usuarios, eProducto_Usuario prodXuser[], int cant_prodXuser,eVentas Ventas_Usuario[],int cant_ventas)
{
    int retorno = -1;
    float promedio;
    if(cant_usuarios > 0 && usuarios != NULL)
    {
        retorno = 0;
        for(int i=0; i<cant_usuarios; i++)
        {
            if(usuarios[i].estado == OCUPADO)
            {
                promedio=get_PromedioClasificacion_usuario(usuarios[i].id,Ventas_Usuario,cant_ventas);
                eGen_mostrarUno_Clasificacion(usuarios[i],promedio);
            }//if(usuarios[i].estado == OCUPADO)
        }//for(int i=0; i<cant_usuarios; i++)
    }
    return retorno;
}

