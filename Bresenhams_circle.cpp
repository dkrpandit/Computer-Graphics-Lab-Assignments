#include <GL/glut.h>
#include <cmath>

int windowWidth = 800;
int windowHeight = 800;

bool mousePressedBefore = false;
int x, y;

void drawPoint(double x, double y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawPointInAllQuadrants(double x, double y, double Cx, double Cy) {
    drawPoint(x + Cx, y + Cy);
    drawPoint(y + Cx, x + Cy);
    drawPoint(-x + Cx, y + Cy);
    drawPoint(-y + Cx, x + Cy);
    drawPoint(-x + Cx, -y + Cy);
    drawPoint(-y + Cx, -x + Cy);
    drawPoint(x + Cx, -y + Cy);
    drawPoint(y + Cx, -x + Cy);
}

void BresenhamCircleDrawingAlgo(double Cx, double Cy, double radius) {
    double pk = 3 - (2 * radius);
    double x = 0, y = radius;

    while (x <= y) {
        if (pk < 0) {
            x++;
            pk += (4 * x) + 6;
        }
        else {
            x++;
            y--;
            pk += 4 * (x - y) + 10;
        }

        drawPointInAllQuadrants(x, y, Cx, Cy);
    }
}

void drawCoordinateAxes() {
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
    glVertex2i(0, windowHeight / 2);
    glVertex2i(0, -windowHeight / 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(windowWidth / 2, 0);
    glVertex2i(-windowWidth / 2, 0);
    glEnd();
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCoordinateAxes();
    glColor3f(1.0, 0.0, 0.0);
    glFlush();
}

void Init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);
}

double distBetween2Points(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void mouseFunc(int button, int state, int xMouse, int yMouse) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!mousePressedBefore) {
            x = xMouse;
            y = yMouse;
            mousePressedBefore = true;
        }
        else {
            double radius = distBetween2Points(xMouse, yMouse, x, y);
            BresenhamCircleDrawingAlgo(x - windowWidth / 2, windowHeight / 2 - y, radius);
            mousePressedBefore = false;
        }
        glFlush();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Assignment3");

    Init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouseFunc);

    glutMainLoop();

    return 0;
}
