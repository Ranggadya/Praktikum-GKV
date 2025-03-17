#include <GL/glut.h>

// Current angles
static int shoulder = 0, elbow = 0, wrist_pitch = 0, wrist_yaw = 0;

// Finger joint angles (proximal, middle, distal for each finger)
static int thumb_base = 0, thumb_proximal = 0;
static int index_proximal = 0, index_middle = 0, index_distal = 0;
static int middle_proximal = 0, middle_middle = 0, middle_distal = 0;
static int ring_proximal = 0, ring_middle = 0, ring_distal = 0;
static int pinky_proximal = 0, pinky_middle = 0, pinky_distal = 0;

// Finger curling state (for realistic finger movement)
static int finger_curl = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    // Enable depth testing for proper 3D rendering
    glEnable(GL_DEPTH_TEST);
}

// Function to draw a single finger segment
void drawFingerSegment(float length, float width, float height) {
    glPushMatrix();
    glScalef(length, width, height);
    glutWireCube(1.0);
    glPopMatrix();
}

// Draw finger with multiple joints
void drawFinger(int proximal_angle, int middle_angle, int distal_angle, 
                float length, float z_pos, float y_offset) {
    // Base position
    glPushMatrix();
    glTranslatef(0.0, y_offset, z_pos);
    
    // Proximal phalanx
    glRotatef((GLfloat)proximal_angle, 0.0, 0.0, 1.0);
    glTranslatef(length/2, 0.0, 0.0);
    drawFingerSegment(length, 0.15, 0.12);
    
    // Middle phalanx
    glTranslatef(length/2, 0.0, 0.0);
    glRotatef((GLfloat)middle_angle, 0.0, 0.0, 1.0);
    glTranslatef(length*0.4/2, 0.0, 0.0);
    drawFingerSegment(length*0.4, 0.14, 0.11);
    
    // Distal phalanx
    glTranslatef(length*0.4/2, 0.0, 0.0);
    glRotatef((GLfloat)distal_angle, 0.0, 0.0, 1.0);
    glTranslatef(length*0.25/2, 0.0, 0.0);
    drawFingerSegment(length*0.25, 0.13, 0.10);
    
    glPopMatrix();
}

// Draw thumb with special orientation
void drawThumb(int base_angle, int proximal_angle) {
    glPushMatrix();
    
    // Position at thumb base
    glTranslatef(-0.1, -0.15, 0.15);
    
    // Base joint rotation (for opposition movement)
    glRotatef((GLfloat)base_angle, 0.0, 1.0, 0.0);
    glRotatef(-30.0, 1.0, 0.0, 0.0);  // Thumb natural position
    glRotatef(30.0, 0.0, 0.0, 1.0);   // Angle with palm
    
    // Proximal phalanx
    glTranslatef(0.15, 0.0, 0.0);
    drawFingerSegment(0.3, 0.17, 0.14);
    
    // Distal phalanx
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)proximal_angle, 0.0, 0.0, 1.0);
    glTranslatef(0.12, 0.0, 0.0);
    drawFingerSegment(0.25, 0.16, 0.13);
    
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    // Shoulder transformation
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Draw upper arm
    glPushMatrix();
    glScalef(2.0, 0.5, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Elbow transformation
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Draw forearm
    glPushMatrix();
    glScalef(2.0, 0.4, 0.4);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Wrist transformations
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist_pitch, 0.0, 0.0, 1.0);  // Up-down motion
    glRotatef((GLfloat)wrist_yaw, 0.0, 1.0, 0.0);    // Side to side
    glTranslatef(0.3, 0.0, 0.0);
    
    // Draw palm
    glPushMatrix();
    glScalef(0.6, 0.5, 0.7);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Draw thumb
    drawThumb(thumb_base, thumb_proximal);
    
    // Position for drawing fingers
    glTranslatef(0.3, 0.0, 0.0);
    
    // Draw index finger
    drawFinger(index_proximal, index_middle, index_distal, 0.4, 0.2, 0.15);
    
    // Draw middle finger (slightly longer)
    drawFinger(middle_proximal, middle_middle, middle_distal, 0.45, 0.0, 0.17);
    
    // Draw ring finger
    drawFinger(ring_proximal, ring_middle, ring_distal, 0.4, -0.2, 0.15);
    
    // Draw pinky finger (shorter)
    drawFinger(pinky_proximal, pinky_middle, pinky_distal, 0.3, -0.4, 0.1);
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -6.0);
}

// Function for realistic finger curling
void curlFingers(int amount) {
    // Base curl ratio: proximal:middle:distal is roughly 3:4:2
    index_proximal = middle_proximal = ring_proximal = pinky_proximal = amount * 0.3;
    index_middle = middle_middle = ring_middle = pinky_middle = amount * 0.4;
    index_distal = middle_distal = ring_distal = pinky_distal = amount * 0.2;
    
    // Thumb has different curl mechanics
    thumb_proximal = amount * 0.5;
    
    // Add natural variation between fingers
    middle_proximal -= 5;
    ring_proximal -= 10;
    pinky_proximal -= 15;
    
    finger_curl = amount;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Arm controls
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        
        // Wrist controls
        case 'w': wrist_pitch = (wrist_pitch + 5) % 360; break;
        case 'W': wrist_pitch = (wrist_pitch - 5) % 360; break;
        case 'a': wrist_yaw = (wrist_yaw + 5) % 360; break;
        case 'A': wrist_yaw = (wrist_yaw - 5) % 360; break;
        
        // Finger curling (realistic group movement)
        case 'f': 
            finger_curl = (finger_curl + 10) % 100;
            curlFingers(finger_curl);
            break;
        case 'F': 
            finger_curl = (finger_curl - 10) % 100;
            if (finger_curl < 0) finger_curl += 100;
            curlFingers(finger_curl);
            break;
            
        // Thumb specific controls
        case 't': thumb_base = (thumb_base + 5) % 90; break;
        case 'T': thumb_base = (thumb_base - 5) % 90; break;
        
        // Individual finger controls (for fine adjustments)
        case '1': index_proximal = (index_proximal + 5) % 90; break;
        case '2': middle_proximal = (middle_proximal + 5) % 90; break;
        case '3': ring_proximal = (ring_proximal + 5) % 90; break;
        case '4': pinky_proximal = (pinky_proximal + 5) % 90; break;
        
        // Preset gestures
        case 'g': // Grip gesture
            thumb_base = 40;
            thumb_proximal = 45;
            curlFingers(70);
            break;
        case 'p': // Point gesture
            thumb_base = 15;
            thumb_proximal = 5;
            index_proximal = 0;
            index_middle = 0;
            index_distal = 0;
            curlFingers(80);
            middle_proximal = 80;
            middle_middle = 95;
            middle_distal = 45;
            break;
        case 'o': // Open hand
            thumb_base = 0;
            thumb_proximal = 0;
            curlFingers(0);
            break;
            
        case 27: exit(0); break;  // ESC key
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
