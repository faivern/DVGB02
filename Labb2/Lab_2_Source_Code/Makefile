mysim: Host_A.o Host_B.o Sim_Engine.o checkSum.o
	$(CC) $(CFLAGS) -o mysim Host_A.o Host_B.o Sim_Engine.o checkSum.o -lm

checkSum.o: checkSum.c checkSum.h
	$(CC) $(CFLAGS) -c checkSum.c
clean:
	rm -f *.o mysim mysim