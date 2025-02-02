#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>

// Structure to represent a mosquito
struct Mosquito {
    float x, y;       // Position
    float dx, dy;     // Direction of movement7
    float size;       // Size of the mosquito
};

const int NUM_MOSQUITOES = 15; // Number of mosquitoes
Mosquito mosquitoes[NUM_MOSQUITOES];

// Variables for pond, water bowl, and spray
bool waterBowlVisible = false;
bool spraying = false;
float sprayX = 0.0f, sprayY = 0.0f, sprayRadius = 0.02f;
float waterBowlX = -0.4f, waterBowlY = -0.9f, waterBowlRadius = 0.05f;

// Function to initialize mosquitoes with random positions and directions
void initializeMosquitoes() {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < NUM_MOSQUITOES; i++) {
        mosquitoes[i].x = ((rand() % 200) / 100.0f) - 1.0f; // Random x position (-1 to 1)
        mosquitoes[i].y = ((rand() % 200) / 100.0f) - 1.0f; // Random y position (-1 to 1)
        mosquitoes[i].dx = ((rand() % 50) / 10000.0f) - 0.005f; // Slow random x direction
        mosquitoes[i].dy = ((rand() % 50) / 10000.0f) - 0.005f; // Slow random y direction
        mosquitoes[i].size = 0.05f; // Fixed small size
    }
}

// Function to draw a small mosquito
void drawMosquito(float x, float y, float size) {
    // Body
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_LINES);
    glVertex2f(x - size / 2, y);
    glVertex2f(x + size / 2, y); // Body line
    glEnd();

    // Head
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x - size / 2 - size / 4, y);
    for (int i = 0; i <= 360; i++) {
        float angle = i * (3.14159f / 180.0f);
        glVertex2f(x - size / 2 - size / 4 + (size / 4) * cos(angle),
            y + (size / 4) * sin(angle));
    }
    glEnd();

    // Wings
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x - size * 1.5f, y + size);
    glVertex2f(x - size / 2, y); // Left wing
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + size * 1.5f, y + size);
    glVertex2f(x + size / 2, y); // Right wing
    glEnd();

    // Proboscis
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x - size / 2 - size / 4, y);
    glVertex2f(x - size / 2 - size / 2, y); // Proboscis
    glEnd();
}

// Function to draw a house
void drawHouse(float x, float y, float width, float height) {
    // Base of the house
    glColor3f(0.55f, 0.27f, 0.07f); // Dark brown
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Roof of the house
    glColor3f(0.0f, 0.0f, 0.5f); // Dark blue
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + height);
    glVertex2f(x + width / 2, y + height + height / 2);
    glVertex2f(x + width, y + height);
    glEnd();
}

// Function to draw a tree
void drawTree(float x, float y) {
    // Tree trunk
    glColor3f(0.54f, 0.27f, 0.07f); // Brown
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x + 0.05f, y + 0.3f);
    glVertex2f(x, y + 0.3f);
    glEnd();

    // Tree leaves
    glColor3f(0.0f, 0.5f, 0.0f); // Green
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.1f, y + 0.3f);
    glVertex2f(x + 0.15f, y + 0.5f);
    glVertex2f(x + 0.3f, y + 0.3f); // Top triangle
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.1f, y + 0.45f);
    glVertex2f(x + 0.15f, y + 0.7f);
    glVertex2f(x + 0.3f, y + 0.45f); // Bottom triangle
    glEnd();
}

// Function to draw a pond
void drawPond() {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for water
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(0.7f + 0.3f * cos(angle), -0.85f + 0.2f * sin(angle)); // Pond shape
    }
    glEnd();
}

// Function to update mosquito positions
void updateMosquitoes() {
    for (int i = 0; i < NUM_MOSQUITOES; i++) {
        mosquitoes[i].x += mosquitoes[i].dx;
        mosquitoes[i].y += mosquitoes[i].dy;

        // Reverse direction if mosquito hits a boundary
        if (mosquitoes[i].x < -1.0f || mosquitoes[i].x > 1.0f)
            mosquitoes[i].dx = -mosquitoes[i].dx;
        if (mosquitoes[i].y < -1.0f || mosquitoes[i].y > 1.0f)
            mosquitoes[i].dy = -mosquitoes[i].dy;
    }
}

// Function to display text on the screen
void displayText(const char* text, float x, float y) {
    glColor3f(0.0f, 0.0f, 0.0f); // Black text
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// // Function to draw a bowl with water inside
// void drawBowlWithWater(float x, float y, float radius) {
//     // Draw the bowl (brown color)
//     glColor3f(0.55f, 0.27f, 0.07f); // Brown color for the bowl
//     glBegin(GL_POLYGON);
//     for (int i = 0; i < 360; i++) {
//         float angle = i * 3.14159f / 180.0f;
//         glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
//     }
//     glEnd();

//     // Draw the water inside the bowl (sky blue color)
//     glColor3f(0.53f, 0.81f, 0.92f); // Sky blue color for the water
//     glBegin(GL_POLYGON);
//     for (int i = 0; i < 360; i++) {
//         float angle = i * 3.14159f / 180.0f;
//         glVertex2f(x + radius * 0.8f * cos(angle), y + radius * 0.8f * sin(angle));
//     }
//     glEnd();
// }

// Function to display instructions
void displayInstructions() {
    // Define the multiple lines of text
    const char* instructions[] = {
        "Please Press :",
        " S: Start Spray Effect",
        " R: Remove Water from the Bowl",
        "",
        "Instructions:",
        "1. Keep water clean,",
        "2. cover containers,",
        "3. wear protective clothes."

    };

    float yPos = 0.9f;
    for (int i = 0; i < 8; i++) {
        displayText(instructions[i], 0.3f, yPos);
        yPos -= 0.05f;  // Move to the next line
    }
}

// Function to draw clouds in the sky
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 0.1f * cos(angle), y + 0.1f * sin(angle));
    }
    glEnd();
}
// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    glColor3f(0.53f, 0.81f, 0.92f); // Sky blue
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Draw clouds
    drawCloud(-0.8f, 0.6f);
    drawCloud(0.2f, 0.8f);
    drawCloud(0.6f, 0.5f);

    // Draw houses
    drawHouse(-0.9f, -0.8f, 0.3f, 0.3f); // House 1
    drawHouse(-0.5f, -0.8f, 0.4f, 0.4f); // House 2
    drawHouse(0.0f, -0.8f, 0.25f, 0.25f); // House 3

    // Draw trees
    drawTree(-0.9f, -0.5f);
    drawTree(-0.6f, -0.6f);

    drawTree(0.8f, -0.7f);

    // Draw pond
    drawPond();

    // Draw mosquitoes
    for (int i = 0; i < NUM_MOSQUITOES; i++) {
        drawMosquito(mosquitoes[i].x, mosquitoes[i].y, mosquitoes[i].size);
    }

    // Draw water bowl if visible
    if (!waterBowlVisible) {
        glColor3f(0.0f, 0.0f, 1.0f);  // Blue water bowl
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(waterBowlX + waterBowlRadius * cos(angle), waterBowlY + waterBowlRadius * sin(angle));
        }
        glEnd();
    }

    // Draw spray effect if active
    if (spraying) {
        glColor3f(0.1f, 0.5f, 1.0f);  // Light blue spray
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(sprayX, sprayY);
        for (int i = 0; i <= 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(sprayX + sprayRadius * cos(angle), sprayY + sprayRadius * sin(angle));
        }
        glEnd();
        sprayRadius += 0.01f;
        if (sprayRadius > 0.1f) {
            spraying = false;
        }
    }

    // Display text
    displayText("Dengue Awareness: Mosquitoes", -0.9f, 0.9f);

    // Display instructions
    displayInstructions();

    glutSwapBuffers();
}

// Timer function for animation
void timer(int value) {
    updateMosquitoes();      // Update positions
    glutPostRedisplay();     // Redraw the scene
    glutTimerFunc(50, timer, 0); // Approx 20 FPS
}

// Keyboard function7
void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        // Start spraying
        sprayX = (rand() % 200 - 100) / 100.0f;
        sprayY = (rand() % 200 - 100) / 100.0f;
        sprayRadius = 0.02f;
        spraying = true;
    }

    if (key == 'r' || key == 'R') {
        // Remove water bowl
        waterBowlVisible = true;
    }
}

// Initialization
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 2D orthographic projection
    initializeMosquitoes();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Slowly Moving Dengue Mosquitoes with Background, Houses, Trees, Pond, Water Bowl, and Text");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(50, timer, 0); // Start timer with 50ms interval
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
