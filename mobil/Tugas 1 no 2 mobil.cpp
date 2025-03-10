#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)segments;
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawWheel(float x, float y, float radius) {
    glPushMatrix();
    
    glTranslatef(x, y, 0.0);
    
    glColor3f(0.1, 0.1, 0.1);
    drawCircle(0, 0, radius, 32);
    
    glColor3f(0.8, 0.8, 0.8);
    drawCircle(0, 0, radius * 0.7, 32);
    
    glColor3f(0.5, 0.5, 0.5);
    drawCircle(0, 0, radius * 0.3, 32);
    
    glColor3f(0.6, 0.6, 0.6);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float angle = i * 3.14159 / 4.0;
        glVertex2f(0, 0);
        glVertex2f(radius * 0.65 * cos(angle), radius * 0.65 * sin(angle));
    }
    glEnd();
    
    glPopMatrix();
}

void drawCarBody() {
    glPushMatrix();
    
    glTranslatef(0.0, 0.0, 0.0);
    
    glColor3f(0.8, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 10.0);
    glVertex2f(50.0, 10.0);
    glVertex2f(50.0, 20.0);
    glVertex2f(0.0, 20.0);
    glEnd();
    
    glColor3f(0.7, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(10.0, 20.0);
    glVertex2f(40.0, 20.0);
    glVertex2f(35.0, 30.0);
    glVertex2f(15.0, 30.0);
    glEnd();
    
    glColor3f(0.6, 0.8, 1.0);
    
    glBegin(GL_POLYGON);
    glVertex2f(15.0, 20.5);
    glVertex2f(25.0, 20.5);
    glVertex2f(25.0, 29.0);
    glVertex2f(15.5, 29.0);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(26.0, 20.5);
    glVertex2f(35.0, 20.5);
    glVertex2f(34.5, 29.0);
    glVertex2f(26.0, 29.0);
    glEnd();
    
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(5.0, 15.0, 3.0, 20);
    
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(45.0, 15.0, 2.5, 20);
    
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(3.0);
    
    glBegin(GL_LINES);
    glVertex2f(-2.0, 8.0);
    glVertex2f(7.0, 8.0);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(43.0, 8.0);
    glVertex2f(52.0, 8.0);
    glEnd();
    
    drawWheel(10.0, 5.0, 7.0);
    drawWheel(40.0, 5.0, 7.0);
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(43.0, 12.0);
    glVertex2f(49.0, 12.0);
    glVertex2f(49.0, 16.0);
    glVertex2f(43.0, 16.0);
    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(44.0, 13.0);
    glVertex2f(44.0, 15.0);
    glVertex2f(44.0, 15.0);
    glVertex2f(46.0, 15.0);
    glVertex2f(46.0, 15.0);
    glVertex2f(46.0, 14.0);
    glVertex2f(46.0, 14.0);
    glVertex2f(45.0, 14.0);
    glVertex2f(47.0, 13.0);
    glVertex2f(47.0, 15.0);
    glVertex2f(47.0, 13.0);
    glVertex2f(48.0, 13.0);
    glEnd();
    
    glColor3f(0.6, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(20.0, 10.5);
    glVertex2f(30.0, 10.5);
    glVertex2f(30.0, 19.5);
    glVertex2f(20.0, 19.5);
    glEnd();
    
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_LINES);
    glVertex2f(24.0, 15.0);
    glVertex2f(28.0, 15.0);
    glEnd();
    
    glPopMatrix();
}

void drawBackground() {
    glColor3f(0.4, 0.7, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-100.0, 0.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(100.0, 100.0);
    glVertex2f(-100.0, 100.0);
    glEnd();
    
    glColor3f(1.0, 0.9, 0.0);
    drawCircle(70.0, 80.0, 10.0, 32);
    
    glColor3f(0.0, 0.7, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-100.0, -50.0);
    glVertex2f(100.0, -50.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(-100.0, 0.0);
    glEnd();
    
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(-100.0, -20.0);
    glVertex2f(100.0, -20.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(-100.0, 0.0);
    glEnd();
    
    glColor3f(1.0, 1.0, 1.0);
    for (int i = -100; i < 100; i += 20) {
        glBegin(GL_POLYGON);
        glVertex2f(i, -10.0);
        glVertex2f(i + 10.0, -10.0);
        glVertex2f(i + 10.0, -9.0);
        glVertex2f(i, -9.0);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    
    drawBackground();
    
    drawCarBody();
    
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -50.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple 2D Car with OpenGL");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
