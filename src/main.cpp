#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 2 * WINDOW_HEIGHT

double RADIUS = 10;
double YZ_ANGLE = M_PI / 4;
double ZX_ANGLE = M_PI / 6;

GLfloat VERTICES[][3] = {
    {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};

GLfloat COLORS[][3] = {{0.78, 0.12, 0.0}, {0.5, 0.3, 0.2}, {1.0, 0.23, 0.3}, {0.4, 0.3, 0.7}, {0.79, 0.4, 1.0}, {0.0, 0.5, 0.9}};

void init();
void resize(int, int);
void display();
void resize(int, int);

void Task1();
void Task2();

double getXEye();
double getYEye();
double getZEye();

void setCameraPosition();
void OnKeyboard(int, int, int);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Lab4");

  glutSpecialFunc(OnKeyboard);

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();
  return 0;
}

void init()
{
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void resize(int width, int height) {}

void setCameraPosition()
{
  double a = cos(YZ_ANGLE);
  gluLookAt(getXEye(), getYEye(), getZEye(), 0, 0, 0, 0,
            YZ_ANGLE < 0 || YZ_ANGLE > M_PI ? -1 : 1, 0);
}

double getXEye() { return RADIUS * sin(YZ_ANGLE) * sin(ZX_ANGLE); }

double getYEye() { return RADIUS * cos(YZ_ANGLE); }

double getZEye() { return RADIUS * sin(YZ_ANGLE) * cos(ZX_ANGLE); }

void OnKeyboard(int key, int x, int y)
{
  if (key == GLUT_KEY_UP)
  {
    YZ_ANGLE -= M_PI / 10;
  }

  if (key == GLUT_KEY_DOWN)
  {
    YZ_ANGLE += M_PI / 10;
  }

  if (key == GLUT_KEY_LEFT)
  {
    ZX_ANGLE -= M_PI / 10;
  }

  if (key == GLUT_KEY_RIGHT)
  {
    ZX_ANGLE += M_PI / 10;
  }

  if (YZ_ANGLE > M_PI)
  {
    YZ_ANGLE = -M_PI;
  }

  if (YZ_ANGLE < -M_PI)
  {
    YZ_ANGLE = M_PI;
  }

  if (YZ_ANGLE == 0)
  {
    YZ_ANGLE -= 0.001;
  }

  if (ZX_ANGLE > M_PI * 2)
  {
    ZX_ANGLE -= M_PI * 2;
  }

  if (ZX_ANGLE < -M_PI * 2)
  {
    ZX_ANGLE *= -1;
  }
}

void polygon(int a, int b, int c, int d, int color)
{
  glColor3fv(COLORS[color]);

  glBegin(GL_POLYGON);

  glVertex3fv(VERTICES[a]);

  glVertex3fv(VERTICES[b]);

  glVertex3fv(VERTICES[c]);

  glVertex3fv(VERTICES[d]);

  glEnd();
}

void colorcube()
{
  polygon(0, 3, 2, 1, 0);
  polygon(2, 3, 7, 6, 1);
  polygon(0, 4, 7, 3, 2);
  polygon(1, 2, 6, 5, 3);
  polygon(4, 5, 6, 7, 4);
  polygon(0, 1, 5, 4, 5);
}

void Task1()
{
  // левый верхний

  glViewport(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3, 3, -3, 3, 2, 20);
  gluLookAt(RADIUS, 0, 0, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  colorcube();

  //

  // правый верхний

  glViewport(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 4,
             WINDOW_HEIGHT / 2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3, 3, -3, 3, 2, 20);
  gluLookAt(RADIUS, RADIUS, RADIUS, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  colorcube();

  // левый нижний

  glViewport(0, 0, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3, 3, -3, 3, 2, 20);
  gluLookAt(0, 0, RADIUS, 0, 0, 0, 0, 1, 0);
  glRotated(20.705, 1, 0, 0);
  glRotated(22.208, 0, 1, 0);
  // glRotated(-45, 1, 0, 0);
  // glRotated(35.3, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);

  colorcube();

  // правый нижний

  glViewport(WINDOW_WIDTH / 4, 0, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 6, 35);

  gluLookAt(RADIUS, RADIUS, RADIUS, 0, 0, 0, 0, 1, 0);
  gluPerspective(0, 0, 1, 2);
  glMatrixMode(GL_MODELVIEW);
  colorcube();
}

void Task2()
{
  glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 2, 20);
  setCameraPosition();
  glMatrixMode(GL_MODELVIEW);

  colorcube();

  glutSwapBuffers();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Task1();
  Task2();
}
