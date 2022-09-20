import java.net.*;
import java.io.*;

public class SocketServidor
{    
    public static void main (String [] args){
      new SocketServidor();
    }
    
    public SocketServidor(){
        try{
     
          ServerSocket socket = new ServerSocket (15557);
          System.out.println (" ++++ Esperando conexion del cliente ++++");
            
          Socket cliente = socket.accept();
          System.out.println ("Conectado con cliente: " + cliente.getInetAddress());
          System.out.println ("El puerto de Conexion es: 15557");
          cliente.setSoLinger (true, 10);

          //Enviamos el datp
          DatoSocket dato = new DatoSocket("Hola Cliente");

          DataOutputStream bufferSalida = new DataOutputStream (cliente.getOutputStream());
          dato.writeObject (bufferSalida);
          
          System.out.println ("Se envió el mensaje y su longitud: " + dato.toString());

            //Leemos los datos del cliente
          DataInputStream bufferEntrada = new DataInputStream (cliente.getInputStream());

          DatoSocket aux = new DatoSocket("");
          aux.readObject (bufferEntrada);
          System.out.println ("Mensaje recibido por parte del cliente y su longitud: " + aux.toString());
            
       
            cliente.close();
            socket.close();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
