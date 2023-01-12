import paho.mqtt.client as paho
import pymysql
import sys

def onMessage(client,userdata,msg):
    print("message :"+msg.payload.decode())

client = paho.Client()
client.on_message = onMessage

if client.connect("192.168.4.99",1883,60)!=0:
    print("cant connect")
    sys.exit(-1)

client.subscribe("MY_TOPIC")

try:
     print("ctrl+c")
     client.loop_forever()
except:
    print("disconnect")

client.disconnect()