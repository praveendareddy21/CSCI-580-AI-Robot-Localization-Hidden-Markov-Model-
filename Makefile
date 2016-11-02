main: robot.o main.o matrix.o
	g++ -g robot.o main.o matrix.o -o main

main.o: main.cpp robot.h
	g++ -g -c main.cpp

robot.o: robot.cpp robot.h matrix.h
	g++ -g -c robot.cpp

matrix.o: matrix.cpp matrix.h
	g++ -g -c matrix.cpp

clean:
	rm -f *.o main
