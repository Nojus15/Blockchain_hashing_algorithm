main : compile
	g++ -o HashApp *.o -O3
	del *.o
compile :
	g++ -c main.cpp Application/Application.cpp Generator/Generator.cpp Hasher/Hasher.cpp Tester/Tester.cpp Timer/Timer.cpp -O3
clean :
	del *.exe *.o

# mingw32-make