SOURCES=$(wildcard src/**/*.c src/*.c)
EXECUTABLE=main
TARGET=bin
CFLAGS= 
LDLIBS= `pkg-config --libs gtk+-3.0` 
CPPFLAGS= `pkg-config --cflags gtk+-3.0`

#gcc `pkg-config --cflags gtk+-3.0` -o main2  main2.c `pkg-config --libs gtk+-3.0`

all: clean $(EXECUTABLE)

build:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(SOURCES) 
	mv *.o src/ 
	cp src/ui/guiGTK.glade $(TARGET)
	mkdir $(TARGET)/beamerFiles
	mkdir $(TARGET)/output
	cp -a src/beamerFiles/. $(TARGET)/beamerFiles

$(EXECUTABLE): $(TARGET) build
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) -o $(TARGET)/$(EXECUTABLE) -lm $(LDLIBS)

$(TARGET):
	mkdir bin/

clean:
	rm -f $(OBJECTS)  
	rm -rf $(TARGET)
install:
	apt-get install texlive-full
	apt-get install libgtk-3-dev 