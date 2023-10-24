import json
from websockets.sync.client import connect
import requests

def move(text, username):
    if text in ['w', 'W', 'forward', 'в', 'вперед']:
        requests.get(f'http://192.168.1.90/Forward?q={username}')
    if text in ['s', 'S', 'backward', 'н', 'назад']:
        requests.get(f'http://192.168.1.90/Backward?q={username}')
    if text in ['a', 'A', 'left', 'л', 'лево']:
        requests.get(f'http://192.168.1.90/Left?q={username}')
    if text in ['d', 'D', 'right', 'п', 'право']:
        requests.get(f'http://192.168.1.90/Right?q={username}')


def hello():
    with connect("ws://localhost:8383/Chat") as websocket:
        while True:
            message = websocket.recv()
            js = json.loads(message)
            text = js.get('text_text')
            username = js.get('user')
            user_id = js.get('user_id')
            site = js.get('site_cut')
            try:
                # if username in ['ve5pi']:


                    text = text.strip().lower()
                    print(text)
                    username = js.get('user')
                    if len(text) == 2 and text[0] in ['w', 's', 'в', 'н']:
                        text, num = list(text)
                        num = int(num)
                        if 1 <= num <= 5:
                            for i in range(num):
                                move(text, username)
                    else:
                        move(text, username)

                    # if text == 'buzz':
                    #     requests.get(f'http://192.168.1.90/Buzz')

                    # if text == 'off':
                    #     requests.get(f'http://192.168.1.90/BlinkRightOff')
                    #     requests.get(f'http://192.168.1.90/BlinkLeftOff')
                    # if text == 'on':
                    #     requests.get(f'http://192.168.1.90/BlinkRightOn')
                    #     requests.get(f'http://192.168.1.90/BlinkLeftOn')
                    if text == 'e':
                        requests.get(f'http://192.168.1.90/Turn?q={0}')
                    if text == 'q':
                        requests.get(f'http://192.168.1.90/Turn?q={180}')
                    if text == 'rf':
                        requests.get(f'http://192.168.1.90/Turn?q={90}')
                    
            except:
                pass


hello()