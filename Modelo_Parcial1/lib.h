#ifndef ESTRUCTURAGENERICA_H_INCLUDED
#define ESTRUCTURAGENERICA_H_INCLUDED
typedef struct
{
    int id;
    char nombre[50];
    char password[10];
    int estado;
}eUsuario;

typedef struct
{
    int id_producto;
    int id_usuario;
    float precio;
    int stock;
}eProducto_Usuario;

typedef struct
{
    int id_venta;
    int id_producto;
    int id_usuario_compra;
    int cantVendidos;
    float clasificacion;
}eVentas;

#endif // ESTRUCTURAGENERICA_H_INCLUDED

//#----- GENERICAS ----#
void menu(char *opciones);
char *get_char(char *sms,int LongitudCadena);
int get_int(char *sms);
void sms_error(int mensaje,int Error);

//#----- ESTRUCTURAS ---#
void inicializa_usuarios( eUsuario listado[],int limite);
void inicializa_user_Prod(eProducto_Usuario listado[],int limite);
void inicializa_Ventas(eVentas listado[],int limite);

int eGen_buscarLugarLibre(eUsuario listado[],int limite);
int eGen_siguienteId(eUsuario listado[],int limite);
int eGen_alta_usuario(eUsuario  listado[],int limite);

float get_PromedioClasificacion_usuario(int id_usuario);
int eGen_mostrarUno(eUsuario record);
int eGen_mostrarUsuarios(eUsuario listado[],int limite);

int eGen_buscarPorId(eUsuario listado[] ,int limite, int id);
int eGen_modificacion(eUsuario listado[] ,int limite, int id);

int eGen_baja_usuario(eUsuario listado[] ,int limite, int id);
int eGen_baja_ProductosXUsuarios(eUsuario usuarios[] ,int cant_usuario, int id_usuario, eProducto_Usuario prodXuser, int cant_prodXuser );


//#--- SIN REVIZAR ---#


