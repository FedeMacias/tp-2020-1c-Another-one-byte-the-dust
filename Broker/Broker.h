#ifndef BROKER_BROKER_H_
#define BROKER_BROKER_H_

#include <stdio.h>
#include <stdlib.h>
#include "../Serializacion/Serializacion.h"
#include <commons/log.h>
#include <commons/config.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/collections/list.h>
#include <string.h>
#include <pthread.h>

//Estructuras
//Las presentes estructuras no son definitivas.

/*
typedef struct
{
    int socket_suscriptor;
    //t_list *colasALasQueEstaSuscrito;
}t_suscriptor;
*/

typedef struct
{
	uint32_t ID_mensaje;
	uint32_t ID_correlativo;
	void *paquete;
	t_list *suscriptoresQueRecibieronMensaje;
} t_mensaje;


//Variables

uint32_t contadorID = 0;
t_log *logger;
t_config *config;
char *ip;
char *puerto;
char *algoritmo_memoria;
char *algoritmo_reemplazo;
char *algoritmo_particion_libre;
int socket_servidor;
int socket_cliente;
int tamanio_memoria;
int tamanio_minimo_particion;
int frecuencia_compactacion;
t_list *NEW_POKEMON;
t_list *suscriptores_NEW_POKEMON;
t_list *APPEARED_POKEMON;
t_list *suscriptores_APPEARED_POKEMON;
t_list *CATCH_POKEMON;
t_list *suscriptores_CATCH_POKEMON;
t_list *CAUGHT_POKEMON;
t_list *suscriptores_CAUGHT_POKEMON;
t_list *GET_POKEMON;
t_list *suscriptores_GET_POKEMON;
t_list *LOCALIZED_POKEMON;
t_list *suscriptores_LOCALIZED_POKEMON;
pthread_t hiloAtencionCliente;
pthread_mutex_t semaforoID;


//Funciones
t_log *crearLogger();
t_config *crearConfig();
int iniciar_servidor(char *, char *);
int esperar_cliente(int);
void atender_cliente(int *);
void procesar_solicitud(Header,int);
void setearValores(t_config *);
void agregarMensajeACola(t_mensaje *,t_list *,char *);
void inicializarColas();
void destruirColas();
void enviarMensajeASuscriptor(void *);
void suscribirProceso(char *,int *,t_operacion);
t_mensaje *crearMensaje(void *,int);
uint32_t asignarID();
void enviarMensaje(int cliente_fd, const void* paquete, uint32_t tamPaquete, t_operacion operacion,t_mensaje *mensaje);
void inicializarListasSuscriptores();
void destruirListasSuscriptores();
void enviarMensajeASuscriptor(void *);
void enviarMensajeRecibidoASuscriptores(t_list *,void(*)(void*));
void validarRecepcionMensaje(int, t_mensaje *);

#endif
