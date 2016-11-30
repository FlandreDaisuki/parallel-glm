CC = gcc
LIBS = -lGL -lGLU -lGLEW -lglut -lm -lpng
SOURCE = main.c glm/glm.c glm/glmimg_png.c glm/glmimg.c glm/glm_util.c glm_helper.c

all: obj-buddha clean

obj-rungholt: build
	./a.out rungholt/rungholt.obj 2>/dev/null

obj-buddha: build
	./a.out buddha/buddha.obj 2>/dev/null

obj-sibenik: build
	./a.out sibenik/sibenik.obj 2>/dev/null

obj-sponza: build
	./a.out sponza/sponza.obj 2>/dev/null

build:
	$(CC) $(SOURCE) $(LIBS)

%.o: glm/%.c
	$(CC) -c -o $@ $<

clean:
	rm $(GLM) ./a.out

install-GL:
	sudo apt-get install -y build-essential make g++-5 libgl1-mesa-dev freeglut3 freeglut3-dev libglew-dev libpng16*

download-objs:
	curl -sS http://graphics.cs.williams.edu/data/meshes/rungholt.zip > rungholt.zip
	curl -sS http://graphics.cs.williams.edu/data/meshes/buddha.zip > buddha.zip
	curl -sS http://graphics.cs.williams.edu/data/meshes/sibenik.zip > sibenik.zip
	curl -sS http://graphics.cs.williams.edu/data/meshes/crytek-sponza.zip > sponza.zip
	ls *.zip | awk -F'.zip' '{print "unzip "$0" -d "$1}' | sh
	rm *.zip

glinfo:
	glxinfo | grep OpenGL > glinfo.txt