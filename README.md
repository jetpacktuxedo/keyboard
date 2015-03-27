This repo is really basic firmware for testing a custom mechanical keyboard. Right now it is configured for my 7x4 matrix, but that is defined only by the ROWS and COLS constants at the top and the defined pins. It should theoretically work for any size layout.

Furthermore, it may require pulldown resistors connecting the rows to ground. Before adding those I was having issues involving pins spontaneously reading high when they shouldn't. It may not be neccesarry, but if you don't use them and have issues, try adding them.

For development, I used a teensy 3.0, although it should run identially on a 3.1 and should run (possibly with minor modifications) on a 2.0 as well.
