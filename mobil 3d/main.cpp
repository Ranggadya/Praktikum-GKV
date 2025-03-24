#include <GL/glut.h>
#include <math.h>

// Global variables for rotation and animation
float carAngle = 0.0f;
float wheelRotation = 0.0f;

// Function to draw a wheel
void drawWheel() {
    // Tire (black)
    glColor3f(0.2f, 0.2f, 0.2f);
    glutSolidTorus(0.1f, 0.3f, 20, 20);
    
    // Wheel rim (silver)
    glColor3f(0.8f, 0.8f, 0.8f);
    glutSolidTorus(0.05f, 0.2f, 16, 16);
    
    // Spokes
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float angle = i * M_PI / 4.0f;
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.25f * cos(angle), 0.25f * sin(angle), 0.0f);
    }
    glEnd();
}

// Function to draw the car body
void drawCarBody() {
    // Main body (red)
    glColor3f(0.8f, 0.1f, 0.1f);
    
    // Lower part (chassis)
    glPushMatrix();
    glScalef(2.0f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Upper part (cabin)
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glScalef(1.2f, 0.4f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Front windshield
    glColor3f(0.6f, 0.8f, 0.9f);
    glPushMatrix();
    glTranslatef(0.45f, 0.4f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.3f, 0.3f, 0.79f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Headlights
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(1.0f, 0.1f, 0.4f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.0f, 0.1f, -0.4f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();
    
    // Taillights
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-1.0f, 0.1f, 0.4f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.0f, 0.1f, -0.4f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();
}

// Function to draw the entire car
void drawCar() {
    // Draw the car body
    drawCarBody();
    
    // Draw wheels
    glPushMatrix();
    glTranslatef(0.7f, -0.3f, 0.6f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    drawWheel();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.7f, -0.3f, -0.6f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    drawWheel();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.7f, -0.3f, 0.6f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    drawWheel();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.7f, -0.3f, -0.6f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    drawWheel();
    glPopMatrix();
}

// Function to draw the ground (road and grass)
void drawGround() {
    // Road (asphalt)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-15.0f, -0.5f, -2.0f);
    glVertex3f(15.0f, -0.5f, -2.0f);
    glVertex3f(15.0f, -0.5f, 2.0f);
    glVertex3f(-15.0f, -0.5f, 2.0f);
    glEnd();
    
    // Road markings
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = -14; i < 15; i += 2) {
        glVertex3f(i, -0.49f, -0.1f);
        glVertex3f(i + 1, -0.49f, -0.1f);
        glVertex3f(i + 1, -0.49f, 0.1f);
        glVertex3f(i, -0.49f, 0.1f);
    }
    glEnd();
    
    // Grass (left side)
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-15.0f, -0.5f, -15.0f);
    glVertex3f(15.0f, -0.5f, -15.0f);
    glVertex3f(15.0f, -0.5f, -2.0f);
    glVertex3f(-15.0f, -0.5f, -2.0f);
    glEnd();
    
    // Grass (right side)
    glBegin(GL_QUADS);
    glVertex3f(-15.0f, -0.5f, 2.0f);
    glVertex3f(15.0f, -0.5f, 2.0f);
    glVertex3f(15.0f, -0.5f, 15.0f);
    glVertex3f(-15.0f, -0.5f, 15.0f);
    glEnd();
}

// Function to draw the sky
void drawSky() {
    glColor3f(0.4f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-15.0f, -0.5f, -15.0f);
    glVertex3f(15.0f, -0.5f, -15.0f);
    glVertex3f(15.0f, 15.0f, -15.0f);
    glVertex3f(-15.0f, 15.0f, -15.0f);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(
        5.0f, 3.0f, 5.0f,  // Eye position
        0.0f, 0.0f, 0.0f,  // Look at position
        0.0f, 1.0f, 0.0f   // Up vector
    );
    
    // Add ambient light
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    // Add directional light (sun)
    GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat position[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    // Draw the sky
    drawSky();
    
    // Draw the ground
    drawGround();
    
    // Draw the car
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(carAngle, 0.0f, 1.0f, 0.0f);
    drawCar();
    glPopMatrix();
    
    glutSwapBuffers();
}

// Reshape function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Animation function
void animate(int value) {
    carAngle += 1.0f;
    if (carAngle > 360.0f) {
        carAngle -= 360.0f;
    }
    
    wheelRotation += 5.0f;
    if (wheelRotation > 360.0f) {
        wheelRotation -= 360.0f;
    }
    
    glutPostRedisplay();
    glutTimerFunc(20, animate, 0);
}

// Initialization function
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Car with GLUT");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(20, animate, 0);
    
    glutMainLoop();
    return 0;
}
