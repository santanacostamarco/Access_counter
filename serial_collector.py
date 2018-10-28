# sudo python -m pip install pyserial
# sudo python -m pip install mysql-connector

import serial
import mysql.connector

def readSerial(serialDevice):
	try:
		serialData = arduinoBoard.readline()
		print serialData
		return readSerial(serialDevice)
	except:
		print "Failed to read Serial data"
		return

dbConn = mysql.connector.connect(
	host = "127.0.0.1", # localhost mysql server (can be a remote server)
	user = "root", 
	passwd = "root", 
	database = "contador_acesso"
) or die("Coudn't connect to database")

dbCursor = dbConn.cursor()

serialPort = "/dev/ttyACM0" # Serial port used by Arduino board, it chages.

try:
	print "Trying...",serialPort 
	arduinoBoard = serial.Serial(serialPort, 9600) 
except: 
	print "Failed to connect on",serialPort

readSerial(arduinoBoard)

