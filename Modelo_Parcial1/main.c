#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

#define CANTUSER 3 //100
#define CANT_PROD_USUARIOS 5 //1000

int main()
{
    eUsuario usuarios[CANTUSER];
    inicializa_usuarios( usuarios,CANTUSER);

    eProducto_Usuario productosXusuarios[CANT_PROD_USUARIOS];
    inicializa_user_Prod(productosXusuarios,CANT_PROD_USUARIOS);

    int Error;
    char seguir='s';
    int opcion;

    do
    {
        menu("\n1. ALTA DE USUARIO"
             "\n2. MODIFICAR DATOS DEL USUARIO"
             "\n3. BAJA DEL USUARIO"
             "\n4. PUBLICAR PRODUCTO"
             "\n5. MODIFICAR PUBLICACION"
             "\n6. CANCELAR PUBLICACION"
             "\n7. COMPRAR PRODUCTO"
             "\n8. LISTAR PUBLICACIONES DE USUARIO"
             "\n9. LISTAR PUBLICACIONES"
             "\n10. LISTAR USUARIOS"
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

                Error=eGen_modificacion(usuarios ,CANTUSER, get_int("Ingrese el ID del usuario a modificar"));
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

    Error= eGen_baja_ProductosXUsuarios(usuarios,CANTUSER,get_int("Ingrese el ID del usuario a Eliminar"),productosXusuarios,CANT_PROD_USUARIOS);
                //Error= eGen_baja_ProductosXUsuarios(usuarios ,CANTUSER, get_int("Ingrese el ID del usuario a Eliminar"), productosXusuarios, PROD_USUARIOS );

                if(Error!=0)
                {
                    sms_error(5,Error);
                }

                break;
            case 10:
                Error= eGen_mostrarUsuarios(usuarios,CANTUSER);
                if(Error!=0)
                {
                    sms_error(2,Error);
                }
                break;
            case 0://salir
                seguir = 'n';
                break;
        }//FIN switch(opcion)


    }while(seguir=='s');
    return 0;

}
