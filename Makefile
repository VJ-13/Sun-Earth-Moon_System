demo: demo.o
	c++ -o demo demo.o -ltrapfpe -lpgplot -lcpgplot -lX11 -lm 

demo.o: demo.cpp
	c++ -c demo.cpp

project: project.o
	c++ -o project project.o -ltrapfpe -lpgplot -lcpgplot -lX11 -lm 

project.o: project.cpp
	c++ -c project.cpp