#!/usr/bin/env python3
#allows Alexa to command Model 4 to dance

import serial
import time
import threading

from flask import Flask
from flask_ask import Ask, statement, audio, current_stream
from robot_chat_client import RobotChatClient
import facerec

app = Flask(__name__)
ask = Ask(app, '/')

@ask.intent('DanceTime')
def dance():
    speech_text = "Model 4 says it's lit"
    stream_url = 'https://archive.org/download/mc_hammer_202012_202012/mc_hammer.mp3'
    ser.write(b'd')
    #return statement(speech_text).simple_card('Model 4', speech_text)
    return audio(speech_text).play(stream_url)

@ask.intent('EveryoneDance')
def e_dance():
    speech_text = "Model 4 says it's a dance party!"
    stream_url = 'https://archive.org/download/mc_hammer_202012_202012/mc_hammer.mp3'
    ser.write(b'd')
    client.send({'type': 'dance',
                 'foo': [1, 2, 3, 4, 5]})
    #return statement(speech_text).simple_card('Model 4', speech_text)
    return audio(speech_text).play(stream_url)

@ask.intent('stopping')
def chill():
    speech_text = "Model 4 says I'm chillin"
    ser.write(b's')
    return statement(speech_text).simple_card('Model 4', speech_text)

@ask.intent('EveryoneStop')
def e_stop():
    speech_text = "Model 4 says okay"
    ser.write(b's')
    client.send({'type': 'stop',
                 'foo': [1, 2, 3, 4, 5]})
    return statement(speech_text).simple_card('Model 4', speech_text)

@ask.intent('AvoidObstacles')
def roam_freely():
    speech_text = "Model 4 says will do"
    ser.write(b'o')
    return statement(speech_text).simple_card('Model 4', speech_text)

@ask.intent('EveryoneRoam')
def e_roam():
    speech_text = "Model 4 says Autobots roll out!"
    ser.write(b'o')
    client.send({'type': 'roam',
                 'foo': [1, 2, 3, 4, 5]})
    return statement(speech_text).simple_card('Model 4', speech_text)

@ask.intent('VerifyIdentity')
def verify_identity():
    if facerec.condition == 0:
        time.sleep(2)
    output = facerec.name
    speech_text = 'Model 4 says your identity is ' + output
    client.send({'type': 'verify',
                 'foo': [1, 2, 3, 4, 5]})
    return statement(speech_text).simple_card('Model 4', speech_text)


def test_callback(message_dict):
    print('Received dictionary {}'.format(message_dict))
    print('The message is type {}'.format(message_dict['type']))

    if message_dict['type'] == 'dance':
        print("It's dance time!")
        ser.write(b'd') 

    if message_dict['type'] == 'stop':
        print("STOPPING")
        ser.write(b's') 

    if message_dict['type'] == 'roam':
        print("Avoiding Obstacles")
        ser.write(b'o') 

    if message_dict['type'] == 'users':
        print('Number of users: {}'.format(message_dict['count']))
        

if __name__ == '__main__':
    ser = serial.Serial("/dev/ttyUSB0", 9600)
    time.sleep(2)
    x = threading.Thread(target=facerec.face_rec, daemon=True)
    x.start()
    client = RobotChatClient('ws://localhost:5001', callback=test_callback)
    app.run()