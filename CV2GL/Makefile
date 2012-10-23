LDLIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lpthread -lm
TARGETS = ex
OBJECTS = main.o glview.o
INC = -I/usr/X11R6/include
OPENCV = `pkg-config --cflags --libs opencv`

$(TARGETS): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OPENCV) $(OBJECTS) $(INC) $(LDLIBS)

main.o: glview.h
glview.o: glview.h

clean:
	-rm -f $(TARGETS) *.o *~
