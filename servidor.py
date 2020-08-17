# Importamos la libreria de PySerial y mensaje
import math
import serial
from mensaje import *
# Abrimos el puerto del arduino a 115200
PuertoSerie = abrirPort('COM3')
while True: # Creamos un buble sin fin
         print("Esperando....")
         trama = receiveMensaje(PuertoSerie)
         print( 'Respuesta recibida: ', trama )
        
         # ENVÍO EL RESULTADO AL NODE PARA QUE LO MUESTRE POR LA lCD AL CLIENTE
         sendMensaje(PuertoSerie,str(resultado))
        
         # Espera mensaje de confirmación
         r1 = receiveMensaje(PuertoSerie)
         print( 'Respuesta recibida segunda: ', r1 )
