from machine import Pin, PWM
import time

beeper = PWM(Pin(12), freq=440, duty=512)
time.sleep(0.25)
beeper.deinit()
