# sudo python -m pip install pyserial
# sudo python -m pip install mysql-connector

import serial
import mysql.connector

dbConn = mysql.connector.connect(
	host = "127.0.0.1", # localhost mysql server (can be a remote server)
	user = "root", 
	passwd = "root", 
	database = "contador_acesso"
) or die("Coudn't connect to database")

dbCursor = dbConn.cursor()

serialPort = "/dev/ttyACM0" # Serial port used by Arduino board, it may change.

def clearData(data):
	data = data.replace("\\r\\n", '')
	return data.split(" ")
	pass

def getDataDate(data):
	return data[1] + " " + data[2]
	pass

def getDataDirection(data):
	return data[0]
	pass

def recordData(direction, date):
	print(direction, " ", date) #TODO database recording
	pass

def readSerial(serialDevice):
	try:
		serialData = arduinoBoard.readline()
		serialData = clearData(serialData)
		recordData(getDataDirection(serialData), getDataDate(serialData))
		return readSerial(serialDevice)
	except:
		print("Failed to read Serial data")
		return
	pass

def serialConnect(port):
	return serial.Serial(port, 9600)
	pass


try:
	print("Connecting on ",serialPort) 
	arduinoBoard = serialConnect(serialPort) 
	readSerial(arduinoBoard)
except: 
	print("Failed to connect on ", serialPort)

print("Aplication ended")
