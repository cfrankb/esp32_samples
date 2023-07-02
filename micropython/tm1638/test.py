def main():

    # Wemos D1 Mini / ESP8266
    # https://github.com/mcauser/micropython-tm1638
    import tm1638
    from machine import Pin
    tm = tm1638.TM1638(stb=Pin(21), clk=Pin(22), dio=Pin(23))
    
    # STB GREEN     21
    # CLK BLUE      22
    # DIO PURPLE    23
    
    tm.leds(0b01010101)
    tm.show('abcdefgh')
    
    while True:
        a = tm.keys()
        tm.leds(a)
        if a:
            print(a)


def dummy():

    # every 2nd LED on
    tm.leds(0b01010101)

    # all LEDs off
    tm.leds(0)

    # segments
    tm.show('cool')
    tm.show('abcdefgh')
    tm.number(-1234567)
    tm.number(1234)
    tm.number(5678, 4)
    tm.hex(0xdeadbeef)

    # dim both LEDs and segments
    tm.brightness(0)

    # all LEDs and segments off
    tm.clear()

    # get which buttons are pressed
    tm.keys()


main()
