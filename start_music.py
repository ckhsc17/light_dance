# 使用方法: 
# source light_dance_env/bin/activate && python start_music.py

import paho.mqtt.client as mqtt
import os

MQTT_BROKER = "192.168.31.209" # 記得檢查 IP 是否正確
MQTT_PORT = 1883
MQTT_TOPIC = "LED_TOPIC"

# 播放音樂（請替換成你音樂檔案的絕對路徑）
def play_music():
    music_path = "light_whatMYB.mp3"
    os.system(f'afplay "{music_path}" &')  # 用 & 背景播放

# 停止音樂（afplay 沒有 native 停止，但可以透過 killall 停掉）
def stop_music():
    os.system("killall afplay")

def on_connect(client, userdata, flags, rc):
    print("🔌 Connected with result code " + str(rc))
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    print(f"📨 Received: {msg.payload.decode()}")
    if msg.payload.decode() == "ON":
        play_music()
    elif msg.payload.decode() == "OFF":
        stop_music()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_BROKER, MQTT_PORT, 60)
client.loop_forever()