#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

#define CANTUSER 3 //100
#define CANT_PROD_USUARIOS 5 //1000
#define CANT_VENTAS 5 //1000

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
    int aux;

    do
    {
        menu("\n 1. ALTA DE USUARIO"                        //OK
             "\n 2. MODIFICAR DATOS DEL USUARIO"            //OK
             "\n 3. BAJA DEL USUARIO"                       //OK---ver las otras tablas..
             "\n 4. PUBLICAR PRODUCTO"                      //
             "\n 5. MODIFICAR PUBLICACION"                  //
             "\n 6. CANCELAR PUBLICACION"                   //
             "\n 7. COMPRAR PRODUCTO"                       //
             "\n 8. LISTAR PUBLICACIONES DE USUARIO"        //
             "\n 9. LISTAR PUBLICACIONES"                   //
             "\n10. LISTAR USUARIOS"                        //OK---falta clasificacion
             );
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1: //ALTA DE USUARIO"
                Error = eGen_alta_usuario(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(1,Error);
                }
                break;
            case 2://MODIFICAR DATOS DEL USUARIO"
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(2,Error);
                }

                Error=eGen_modificacion(usuarios ,CANTUSER, get_int("\nIngrese el ID del usuario a modificar: "));
                if(Error!=0)
                {
                    sms_error(3,Error);
                }

                break;
            case 3://BAJA DEL USUARIO"
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(2,Error);
                }
                Error=eGen_baja_Usuario_productos_ventas(usuarios,CANTUSER,get_int("\nIngrese el ID del usuario a Eliminar: "),productosXusuarios,CANT_PROD_USUARIOS,ventas,CANT_VENTAS);

                if(Error!=0)
                {
                    sms_error(5,Error);
                }
                break;
            case 4://PUBLICAR PRODUCTO
                Error=eGen_Publicar_Producto(usuarios,CANTUSER,productosXusuarios,CANT_PROD_USUARIOS);
                break;
            case 8://LISTAR PUBLICACIONES DE USUARIO

                aux=get_int("\nIngrese su ID de usuario: ");
                Error=eGen_Lista_Publicaciones_Usuario(aux,usuarios,CANTUSER,ventas,CANT_VENTAS,productosXusuarios,CANT_PROD_USUARIOS);
                break;
            case 10:
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(2,Error);
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
