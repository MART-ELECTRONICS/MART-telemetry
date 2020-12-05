"""Python script to listen on GPIO port 15. If button is pressed, the log cpp
script is launched. If the button is pressed again, the log process is killed."""

import subprocess
import RPi.GPIO as GPIO
import time
import signal
import os

# Pin set (input and pull down)
GPIO.setmode(GPIO.BCM)
GPIO.setup(15, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
running = 0

# log script
writing_script = "/home/pi/Desktop/test_arduino"

while True:
    """ listening loop"""
    pressed = GPIO.input(15)
    if pressed and not running:
        p = subprocess.Popen(writing_script, shell=True, preexec_fn=os.setsid)
        print(f"{writing_script} initialized")
        time.sleep(1)
        running = True
    pressed = GPIO.input(15)
    if pressed and running:
        os.killpg(p.pid, signal.SIGTERM)
        print(f"{writing_script} killed")
        time.sleep(1)
        running = False
