#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h> /* offsetof */
#include <GL/glew.h>
#include <GL/glut.h>

#include "glm/glm.h"
#include "glm_helper.h"

void init(void);
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);

GLMmodel *objModel;
float eye[] = {0.0, 3.0, 1.2};
float delta = 0.0;
char namebuf[150] = {0};

int RETURN_AFTER_INIT = 0;
/* usage:
 * 		./a.out objpath [options]
 * 
 * options:
 * 		-t : return after init()
 */
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[1]);
	strcpy(namebuf, argv[1]);
	glutReshapeWindow(720, 720);
	for(int i=1; i<argc;++i) {
		char *arg = argv[i];
		if(arg[0] == '-' && arg[1] =='t') {
			RETURN_AFTER_INIT = 1;
		}
	}
	glewInit();

	init();
	if(RETURN_AFTER_INIT)
	{
		return 0;
	}
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	glmDelete(objModel);
	return 0;
}

void init(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	objModel = glmReadOBJ(namebuf);

	glmUnitize(objModel);
	glmFacetNormals(objModel);
	glmVertexNormals(objModel, 90.0, GL_FALSE);
	
	if(RETURN_AFTER_INIT == 0)
	{
		print_model_info(objModel);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	eye[0], eye[1], eye[2],
	            0.0, 0.0, 0.0,
	            0.0, 1.0, 0.0);

	glRotatef(delta, 0.0, 1.0, 0.0);
	if (objModel->numtexcoords) {
		glmDraw(objModel, GLM_SMOOTH | GLM_TEXTURE);
	} else {
		glmDraw(objModel, GLM_SMOOTH);
	}
	
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, width/height, 1e-3, 1e3);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
	{	//ESC
		exit(0);
		break;
	}
	case 'd':
	{
		eye[0] += 0.1;
		break;
	}
	case 'a':
	{
		eye[0] -= 0.1;
		break;
	}
	case 'r':
	{
		eye[1] += 0.1;
		break;
	}
	case 'f':
	{
		eye[1] -= 0.1;
		break;
	}
	case 's':
	{
		eye[2] += 0.1;
		break;
	}
	case 'w':
	{
		eye[2] -= 0.1;
		break;
	}
	default:
	{
		break;
	}
	}
}

void idle(void)
{
	glutPostRedisplay();
	delta += 1;
}