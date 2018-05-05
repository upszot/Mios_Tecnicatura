#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

#define CANTUSER 3 //100
#define CANT_PROD_USUARIOS 5 //1000
#define CANT_VENTAS (CANTUSER * CANT_PROD_USUARIOS)

int main()
{
    eUsuario usuarios[CANTUSER];
    inicializa_usuarios( usuarios,CANTUSER);

    eProducto_Usuario productosXusuarios[CANT_PROD_USUARIOS];
    inicializa_user_Prod(productosXusuarios,CANT_PROD_USUARIOS);

    eVentas ventas[CANT_VENTAS];
    inicializa_Ventas(ventas,CANT_VENTAS);

    int Error;
    char seguir='s';
    int opcion;
    int aux; //variables temporales multiproposito
    int aux2;//variables temporales multiproposito

    do
    {
        menu("\n 1. ALTA DE USUARIO"                        //OK
             "\n 2. MODIFICAR DATOS DEL USUARIO"            //OK
             "\n 3. BAJA DEL USUARIO"                       //OK
             "\n 4. PUBLICAR PRODUCTO"                      //OK
             "\n 5. MODIFICAR PUBLICACION"                  //OK
             "\n 6. CANCELAR PUBLICACION"                   //OK
             "\n 7. COMPRAR PRODUCTO"                       //OK
             "\n 8. LISTAR PUBLICACIONES DE USUARIO"        //OK
             "\n 9. LISTAR PUBLICACIONES"                   //OK
             "\n10. LISTAR USUARIOS"                        //OK
             );
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1: //ALTA DE USUARIO"
                Error = eGen_alta_usuario(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 2://MODIFICAR DATOS DEL USUARIO"
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(10,Error);
                }

                Error=eGen_modificacion(usuarios ,CANTUSER, get_int("\nIngrese el ID del usuario a modificar: "));
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 3://BAJA DEL USUARIO"
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(10,Error);
                }
                Error=eGen_baja_Usuario_productos_ventas(usuarios,CANTUSER,get_int("\nIngrese el ID del usuario a Eliminar: "),productosXusuarios,CANT_PROD_USUARIOS,ventas,CANT_VENTAS);

                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 4://PUBLICAR PRODUCTO
                Error=eGen_Publicar_Producto(usuarios,CANTUSER,productosXusuarios,CANT_PROD_USUARIOS);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 5://MODIFICAR PUBLICACION
                aux=get_int("\nIngrese su ID de usuario: ");
                Error=eGen_Lista_Publicaciones_Usuario(aux,usuarios,CANTUSER,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS);
                if(Error!=0)
                {
                    sms_error(8,Error);
                }
                printf("\n");
                system("pause");

                aux2=get_int("\nIngrese su ID Producto a modificar: ");
                Error=eGen_modificar_Publicacion(aux,aux2,productosXusuarios,CANT_PROD_USUARIOS,usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 6://CANCELAR PUBLICACION
                aux=get_int("\nIngrese su ID de usuario: ");
                Error=eGen_Lista_Publicaciones_Usuario(aux,usuarios,CANTUSER,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS);
                if(Error!=0)
                {
                    sms_error(8,Error);
                }
                printf("\n");
                system("pause");

                aux2=get_int("\nIngrese ID Producto a Cancelar Publicacion: ");
                Error=eGen_cancelar_Publicacion(aux,aux2,productosXusuarios,CANT_PROD_USUARIOS,usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 7://COMPRAR PRODUCTO
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(10,Error);
                }
                aux=get_int("\nIngrese ID de usuario a consultar Publicaciones: ");
                Error=eGen_Lista_Publicaciones_Usuario(aux,usuarios,CANTUSER,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                printf("\n");
                system("pause");
                aux2=get_int("\nIngrese ID Producto a Comprar: ");
                //
                Error=Comprar_producto_usuario(aux,aux2,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS );
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
            case 8://LISTAR PUBLICACIONES DE USUARIO
                aux=get_int("\nIngrese ID de usuario a consultar Publicaciones: ");
                Error=eGen_Lista_Publicaciones_Usuario(aux,usuarios,CANTUSER,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                printf("\n");
                system("pause");
                break;
            case 9://LISTAR PUBLICACIONES
                Error=eGen_Lista_Todas_Publicaciones(usuarios,CANTUSER,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                break;
                printf("\n");
                system("pause");
            case 10:
                //Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                Error=eGen_mostrarUsuarios_Clasificacion(usuarios,CANTUSER,productosXusuarios,CANT_PROD_USUARIOS,ventas,CANT_VENTAS);
                if(Error!=0)
                {
                    sms_error(opcion,Error);
                }
                printf("\n");
                system("pause");
                break;
            case 0://salir
                seguir = 'n';
                break;
        }//FIN switch(opcion)


    }while(seguir=='s');
    return 0;

}
