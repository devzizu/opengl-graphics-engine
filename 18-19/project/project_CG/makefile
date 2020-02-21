generator:
	g++ -o gen alien.cpp generator.cpp "tinyxml/tinystr.cpp" "tinyxml/tinyxml.cpp" "tinyxml/tinyxmlerror.cpp" "tinyxml/tinyxmlparser.cpp"

engine:
	g++ -o eng alien.cpp main.cpp  -lm -lGL -lGLU -lglut "tinyxml/tinystr.cpp" "tinyxml/tinyxml.cpp" "tinyxml/tinyxmlerror.cpp" "tinyxml/tinyxmlparser.cpp"

alien:
	g++ -o alien alien.cpp "tinyxml/tinystr.cpp" "tinyxml/tinyxml.cpp" "tinyxml/tinyxmlerror.cpp" "tinyxml/tinyxmlparser.cpp"

clean:
	rm gen eng alien
