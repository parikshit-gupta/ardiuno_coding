import serial
import time

#creating serial object
ardiuno_data=serial.Serial('com5', 9600)
time.sleep(1)

while True:
    #waiting for ardiuno_data object to recive data from comport 
    while (ardiuno_data.in_waiting==0):
        pass

    #reading data from the comport
    datapacket = ardiuno_data.readline()

    # the data recived from the com port is utf8 encoded we need to covert it to a pyhton string to work on it
    datapacket = str(datapacket, 'utf-8')
    
    split_packet=datapacket.split(',')
    print(len(split_packet))
    i=0
    for i in range(0, len(split_packet)-1):
        print("the %d element of data recived is %f."%((i+1),(float(split_packet[i]))))

    
    





