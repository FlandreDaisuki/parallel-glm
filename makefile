SHELL := /bin/bash
CC = clang
LIBS = -lGL -lGLU -lGLEW -lglut -lm -lpng -lpthread
SOURCE = main.c glm/glm.c glm/glmimg_png.c glm/glmimg.c glm/glm_util.c glm_helper.c
OUTNAME = ./a.out
THR = 4

all: obj-buddha clean

obj-rungholt: build
	$(OUTNAME) rungholt/rungholt.obj 2>/dev/null

obj-buddha: build
	$(OUTNAME) buddha/buddha.obj 2>/dev/null

obj-sibenik: build
	$(OUTNAME) sibenik/sibenik.obj 2>/dev/null

obj-sponza: build
	$(OUTNAME) sponza/sponza.obj 2>/dev/null

time-rungholt: build-noinfo
	time $(OUTNAME) rungholt/rungholt.obj -t 2>/dev/null

time-buddha: build-noinfo
	time $(OUTNAME) buddha/buddha.obj -t 2>/dev/null

time-sibenik: build-noinfo
	time $(OUTNAME) sibenik/sibenik.obj -t 2>/dev/null

time-sponza: build-noinfo
	time $(OUTNAME) sponza/sponza.obj -t 2>/dev/null

perf-rungholt: build-noinfo
	perf record $(OUTNAME) rungholt/rungholt.obj -t 2>/dev/null
	perf report

perf-buddha: build-noinfo
	perf record $(OUTNAME) buddha/buddha.obj -t 2>/dev/null
	perf report

perf-sibenik: build-noinfo
	perf record $(OUTNAME) sibenik/sibenik.obj -t 2>/dev/null
	perf report

perf-sponza: build-noinfo
	perf record $(OUTNAME) sponza/sponza.obj -t 2>/dev/null
	perf report

build:
	$(CC) $(SOURCE) $(LIBS) -O2 -D "THREAD_COUNT = $(THR)" -o $(OUTNAME)

build-noinfo:
	$(CC) $(SOURCE) $(LIBS) -O2 -D RETURN_AFTER_INIT -D "THREAD_COUNT = $(THR)" -o $(OUTNAME)

build-gdb:
	$(CC) $(SOURCE) $(LIBS) -g -Wall -o $(OUTNAME)

%.o: glm/%.c
	$(CC) -c -o $@ $<

clean:
	rm $(GLM) $(OUTNAME)

install-GL:
	sudo apt-get update
	sudo apt-get install -y build-essential make g++-5 clang libgl1-mesa-dev freeglut3 freeglut3-dev libglew-dev libpng16*
	sudo apt-get install -y linux-tools-common

download-objs:
	curl -sS http://graphics.cs.williams.edu/data/meshes/rungholt.zip > rungholt.zip
	curl -sS http://graphics.cs.williams.edu/data/meshes/buddha.zip > buddha.zip
	curl -sS http://graphics.cs.williams.edu/data/meshes/sibenik.zip > sibenik.zip
	curl -sS http://graphics.cs.williams.edu/data/meshes/crytek-sponza.zip > sponza.zip
	ls *.zip | awk -F'.zip' '{print "unzip "$$0" -d "$$1}' | sh
	rm *.zip
	find . -type f -name "*.mtl" -exec sed -i 's/\\/\//g' {} +

glinfo:
	glxinfo | grep OpenGL > glinfo.txt
