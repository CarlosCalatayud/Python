#creo este archivo para no copiar este trozo de codigo en cliente y en servidor
#Desde cliente y desde servidor voy a importar(from mensaje import *) todo lo que tenga mensaje
import serial
def abrirPort(p):
    return serial.Serial(
    port = p,
    baudrate = 115200,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS)

def sendMensaje(ps,s):
    ps.write( s.encode('utf-8') )
    
#LA SIGUIENTE FUNCION SOLO SE UTILIZARIA EN LA PRACTICA 2
#def reciveMensaje(ps):
 #   r = ps.readline()           
  #  return r.decode()[0:-1]

def receiveMensaje(ps):
    r = 'chg_'
    while r[0:4]=='chg_': # Elimina mensajes de sincronización del nodeMCU
        r = ps.readline().decode()[0:-2]
    return r