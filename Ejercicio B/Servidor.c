
#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open sockets
#include <unistd.h> // for close sockets
#include <arpa/inet.h>

int main (){
	
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena[100];
	int Numero=0;
	int castRed;

	/*
	* Se abre el socket servidor, con el servicio "cpp_java" dado de
	* alta en el archivo de /etc/services.
	*/
	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1){
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}

	
	Socket_Cliente = Acepta_Conexion_Cliente (Socket_Servidor);
	if (Socket_Servidor == -1){
		printf ("No se puede abrir el socket del cliente\n");
		exit (-1);
	}

	while(1){
				
			Lee_Socket (Socket_Cliente, (char *)&castRed,sizeof(int));
			Numero=ntohl(castRed);

			printf ("Hola, soy el Servidor, dato recibido : %d\n", Numero);
			Numero=Numero+1;
			

			castRed=htonl(Numero);
			Escribe_Socket (Socket_Cliente, (char *)&castRed,sizeof(Numero));
			printf ("Hola, soy el Servidor, dato enviado : %d\n\n", Numero);

			if(Numero==1){
				break;
			}
	}

	close (Socket_Cliente);
	close (Socket_Servidor);
}
