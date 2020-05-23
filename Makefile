mac : main.cpp
	@echo "Compiling for $(UNAME_S)"
	touch a_smart_crow.out
	rm ./a_smart_crow.out
	g++ -o a_smart_crow.out -w main.cpp -framework GLUT -framework OpenGL
	@echo "a_smart_crow.out created"
Linux : main.cpp
	touch a_smart_crow.out
	rm ./a_smart_crow.out
	@echo "Compiling for $(UNAME_S)"
	g++ -o a_smart_crow.out -w main.cpp -lGL -lGLU -lglut -lm
	@echo "a_smart_crow.out created"
clean:
	@echo "There is an error in the program"