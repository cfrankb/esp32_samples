import max7219
from machine import Pin, SPI


# GRN  GRN BLACK
# VCC  5V  RED
# DIN  23  YELLOW
# CS   5   GREEN
# CLK  18  BLUE


def main():
    spi = SPI(
        1,
        sck=Pin(18),
        mosi=Pin(23))
    display = max7219.Matrix8x8(spi, Pin(5), 4)
    display.text('1234', 0, 0, 1)
    display.show()


main()
