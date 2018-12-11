import json
import serial
import mysql.connector
import time
import os

def writeLogs(message):
    timestamp = str(time.time()).split('.')[0]
    f = open('logs/%s.log' % timestamp, 'w')
    f.write(message)
    f.close()
    print('written logs on %s\\logs\\%s.log' % (os.getcwd(), timestamp))
    pass

try:
    dbConn = mysql.connector.connect(
        host = "127.0.0.1", # Localhost mysql server (can be a remote server)
        user = "root", # Set server username
        passwd = "root", # Set server user password
        database = "bibliotecaDB" # Set database name
    )
        
    dbCursor = dbConn.cursor()
except Exception as e:
    writeLogs("Couldn't connect to the database\n%s" % e)



serialPort = "COM4" # Serial port used by Arduino board, it may change.

def clearString(data):
    return json.loads(data[data.index("{") : data.index("}") + 1])
    pass

def recordData(data):
    
    queryStr = "INSERT INTO movimento ( movimento, data_hora, quantidade) VALUES ( %s, %s, %s )"
    queryData = (data["direction"], data["date"] + " " + data["time"], data["quantity"])
    dbCursor.execute(queryStr, queryData)
    dbConn.commit()
    pass

def readSerial(serialDevice):
    try:
        serialData = str(arduinoBoard.readline())
        serialData = clearString(serialData)
        recordData(serialData)
        
        return readSerial(serialDevice)
    except Exception as e:
        writeLogs("Failed to read Serial data\n%s" % e)
        return
    pass    

def serialConnect(port):
    return serial.Serial(port, 9600)
    pass


try:
    print("Connecting on ",serialPort,"...") 
    arduinoBoard = serialConnect(serialPort)
    print("Reading ",serialPort,"...")
    readSerial(arduinoBoard)
except Exception as e: 
    writeLogs("Failed processing the application\n%s" % e)
    
dbCursor.close()
dbConn.close()
input("Press ENTER to quit\n")
print("\nAplication ended")

