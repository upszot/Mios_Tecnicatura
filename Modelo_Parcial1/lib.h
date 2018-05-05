#ifndef ESTRUCTURAGENERICA_H_INCLUDED
#define ESTRUCTURAGENERICA_H_INCLUDED
typedef struct
{
    int id;             //PK
    char nombre[50];
    char password[10];
    int estado;
}eUsuario;

typedef struct
{
    int id_producto;    //PK
    int id_usuario;     //PK
    char nombre[50];
    float precio;
    int stock;
}eProducto_Usuario;

typedef struct
{
    int id_venta;           //PK
    int id_producto;        //PK
    int id_usuario_vende;  //PK
    int cantVendidos;
    float clasificacion;
}eVentas;

#endif // ESTRUCTURAGENERICA_H_INCLUDED

//#----- GENERICAS ----#
void menu(char *opciones);
char *get_char(char *sms,int LongitudCadena);
int get_int(char *sms);
int get_int_con_exit(char *sms);
float get_float(char *sms);
void sms_error(int mensaje,int Error);

//#----- ESTRUCTURAS ---#
int inicializa_usuarios( eUsuario listado[],int limite);
int inicializa_user_Prod(eProducto_Usuario listado[],int limite);
int inicializa_Ventas(eVentas listado[],int limite);

int eGen_buscarLugarLibre(eUsuario listado[],int limite);
int eGen_siguienteId(eUsuario listado[],int limite);
int eGen_alta_usuario(eUsuario  listado[],int limite);

float get_PromedioClasificacion_usuario(int id_usuario);
void eGen_mostrarUno(eUsuario record);
int eGen_mostrarUsuarios(eUsuario listado[],int limite);

int eGen_buscarPorId(eUsuario listado[] ,int limite, int id);
int eGen_modificacion(eUsuario listado[] ,int limite, int id);

int eGen_baja_usuario(eUsuario listado[] ,int limite, int id);
int eGen_baja_Productos_de_Usuario(int id_usuario,eProducto_Usuario prodXuser[], int cant_prodXuser);
int eGen_baja_Ventas_de_Usuario(int id_usuario,eVentas ventas_user[],int cant_ventas_user);
int eGen_baja_Usuario_productos_ventas(eUsuario usuarios[] ,int cant_usuario, int id_user_borrar, eProducto_Usuario prodXuser[], int cant_prodXuser,eVentas Ventas_User[],int cant_ventas_user);


int valida_password(char *validar,char *password);
int eGen_buscarLugarLibre_productos(eProducto_Usuario listado[],int limite);
int eGen_siguienteId_Producto(eProducto_Usuario listado[],int limite,int ID_User);
int eGen_Publicar_Producto(eUsuario usuarios[],int cant_usuarios,eProducto_Usuario prodXuser[],int Cant_ProdXuser);


int get_cantVendidos_Producto(int ID_User, int ID_Prod,eVentas listado[],int limite);
int eGen_Lista_Publicaciones_Usuario(int ID_User,eUsuario usuarios[],int cant_user,eVentas ventas[],int cant_ventas,eProducto_Usuario prodXuser[],int cant_prod);

int eGen_modificar_Publicacion(int ID_Usuario,int ID_Producto,eProducto_Usuario prodXuser[],int cant_prod ,eUsuario usuarios[],int cant_usuarios);

int eGen_cancelar_Publicacion(int ID_Usuario,int ID_Producto,eProducto_Usuario prodXuser[],int cant_prod ,eUsuario usuarios[],int cant_usuarios);

int eGen_Lista_Todas_Publicaciones(eUsuario usuarios[],int cant_usuarios,eVentas ventas[],int cant_ventas,eProducto_Usuario prodXuser[],int cant_prod);

