Förutsättningar
För att bygga och köra dessa program behöver du:

GCC eller en annan C-kompilator
En Unix-baserad miljö

Intstruktioner
Kör makefile med make
starta programmet med ./mysim [parametrar]

parametrar
./mysim 20 0.2 0.2 10 2



/**********GAMLA MAKEFILE**********/

src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = --std=c11 -g

sim: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(obj) sim

/********************************/
