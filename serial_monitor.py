import json
import serial
import mysql.connector

try:
    dbConn = mysql.connector.connect(
        host = "127.0.0.1", # localhost mysql server (can be a remote server)
        user = "root", 
        passwd = "root", 
        database = "bibliotecaDB"
    )
        
    dbCursor = dbConn.cursor()
except Exception as e:
    print("Couldn't connect to the database\n",e)



serialPort = "COM4" # Serial port used by Arduino board, it may change.

def clearString(data):
    return json.loads(data[data.index("{") : data.index("}") + 1])
    pass

def recordData(data):
    #TODO database recording
    queryStr = "INSERT INTO movimento ( movimento, data_hora, quantidade) VALUES ( %s, %s, %s )"
    queryData = (data["direction"], data["date"] + " " + data["time"], data["quantity"])
    dbCursor.execute(queryStr, queryData)
    dbConn.commit()
    print(queryData)
    pass

def readSerial(serialDevice):
    try:
        serialData = str(arduinoBoard.readline())
        serialData = clearString(serialData)
        recordData(serialData)
        
        return readSerial(serialDevice)
    except Exception as e:
        print("Failed to read Serial data\n",e)
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
    print("Failed process the application\n",e)
    
dbCursor.close()
dbConn.close()
print("\nAplication ended")

