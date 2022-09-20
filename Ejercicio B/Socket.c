#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int Lee_Socket (int fd, char *Datos, int Longitud){
	int Leido = 0;
	int Aux = 0;

	/*
	* Si los datos son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud){
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0){
			
			Leido = Leido + Aux;
		}else{
			if (Aux == 0)  //Se cerró el socket
				return Leido;
			if (Aux == -1){
				switch (errno){
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}
	return Leido;
}


int Escribe_Socket (int fd, char *Datos, int Longitud){
	int Escrito = 0;
	int Aux = 0;

	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	
	while (Escrito < Longitud){
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0){
			Escrito = Escrito + Aux;
		}else{
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}
	return Escrito;
}
