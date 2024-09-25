pio run && sudo avrdude -p m328pb -C ~/avrdude_gpio.conf -c pi_1 -v -U flash:w:.pio/build/nanoatmega328/firmware.hex:i
