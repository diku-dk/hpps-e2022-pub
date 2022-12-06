CC=gcc
CFLAGS=-Wall -Wextra -pedantic -pthread -lm -O3 -fopenmp
EXECUTABLES=mandelbrot

all: $(EXECUTABLES)

mandelbrot: mandelbrot.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

IMGWIDTH=1000
IMGHEIGHT=1000

preset0.ppm: mandelbrot
	./mandelbrot $@ $(IMGWIDTH) $(IMGHEIGHT) 100 16 -0.7 0.0 3.067
preset1.ppm: mandelbrot
	./mandelbrot $@ $(IMGWIDTH) $(IMGHEIGHT) 629 256 0.20508818500545423 0.5634322291469464 6.375321937544527e-6
preset2.ppm: mandelbrot
	./mandelbrot $@ $(IMGWIDTH) $(IMGHEIGHT) 399 4 0.4510757067879078 0.38400832516911865 7.632248223018773e-5
preset3.ppm: mandelbrot
	./mandelbrot $@ $(IMGWIDTH) $(IMGHEIGHT) 505 1048576 0.3469337523117071 0.42914692940048277 3.508380713647269e-5


clean:
	rm -f *.o $(EXECUTABLES) *.ppm
