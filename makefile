assign5: assign5.o
	gcc assign5.o -o assign5
assign5.o: assign5.c assign5.h
	gcc -c assign5.c -o assign5.o
clean:
	rm -rf *.o
