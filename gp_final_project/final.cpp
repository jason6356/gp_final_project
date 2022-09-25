#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLU32.lib")

#define WINDOW_TITLE "Path_Finder"

// VARIABLES
// For Polygon
float angle = 0.0;
float PI = 3.142;
float x1_circle = 0.0, y1_circle = 0.0, x2_circle = 0.0, y2_circle = 0.0;

// FOR TEXTURE
BITMAP BMP;          // bitmap structure
HBITMAP hBMP = NULL; // bitmap handle

LPCSTR screenNames[] = {
    "Happy.bmp",
    "Sad.bmp",
    "Question mark.bmp",
    "Love.bmp",
    "KO.bmp",
    "Thumbs-up.bmp",
    "Glitched.bmp",
    "Exclamation.bmp",
    "Dead.bmp",
    "Blank.bmp",
    "Angry.bmp"
};

int screenIndex = 0;

GLuint loadTexture(LPCSTR filename);

// View Initialize
// For Ortho
bool isOrtho = true;
boolean isOrthoBack = false;
float OrthoN = -5.0, OrthoF = 1.0;
// For Persp
float perspN = 1.0, perspF = 17.0;
double xSpeed = 0, ySpeed = 0, zSpeed = 0, pSpeed = 0.5;

// Projection Translate and Rotate
float txP = 0.0, tyP = 0.0, tzP = 0.0;
float tSpeed = 0.5, rotateCamSpeed = 5.0;

// Movement Initialize
float rotation = 0.0, rSpeed1 = 0.01, moveSpeed = 10.0;
int forwardCount = 0;
int backwardCount = 0;

// Animation
int moveCount = 0;
int waveCount = 0;
int shakeHeadCount = 0;
double rWholeRobot = 0;
double rFly = 0;
float moveSpeed2 = 30.0;
float flySpeed = 0.1;
boolean shakeHeadNo = false;
boolean shakeHeadYes = false;
boolean swingSword = false;
boolean backFlip = false;
boolean fly = false;

// For Head
double rHeadtoLR = 0, rHeadtoUD = 0;
// For Upper Body
double rUpperBody = 0;
// For Arm
double rArmFrontBack = 0, rArmUpDown = 0;
// For Elbow
double rElbowFrontBack = 0, rElbowUpDown = 0;
// For Wrist and Fingers
double rFinger = 0, rWrist = 0;
// Move Robot
double moveToX = 0, moveToY = 0, moveToZ = 0;
double rLeg = 0, rLowerLeg;
double moveBodyUpDown = 0;

// Lighting
float xLight = 0.0f, yLight = 0.0f, zLight = 0.0f; // xLight, yLight, zLight;//
boolean changeLightType = false;
float dif[] = {1.0, 1.0, 1.0};
float amb[] = {1.0, 0.0, 0.0};
float difM[] = {1.0, 1.0, 0.0};
boolean isOnLight = false;

// Weapons
int weapons = 0;
double rGun = 0;
double shootOut = 0;
double shootSpeed = 0.2;
boolean bulletsOut = false;
boolean weapon3 = false;
boolean weaponOut = false;
boolean weaponShoot = false;

// Boolean
boolean jump = false;
boolean kneel = false;
boolean crouch = false;

boolean isOnOffTexture = true, isChangeTexture = false;
boolean isChangeSkyBox = false;

boolean moveForward = false, moveBackward = false;
boolean isRotateKneeChanged = false;
boolean waveHand = false;

// upper body
void drawRightArm();
void drawLeftArm();
void drawUpperArm();
void drawElbowSegment();
void drawHead();
void middleBody();
void RotateRightArm();
void RotateLeftArm();

void drawLeftHand();
void drawRightHand();

// lower body
void drawLeftLeg();
void drawRightLeg();
void drawBottomRightLeg();
void drawBottomLeftLeg();

// weapons
void drawWeaponSword();
void drawWeaponLaser();

// sky box
void skyBox(int types);


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        // Projection View Type (Ortho or Prespective)
        else if (wParam == 'O')
        { // Ortho
            isOrtho = true;
            tzP = 0.0;
            txP = 0.0;
            tyP = 0.0;
            xSpeed = 0.0;
            ySpeed = 0.0;
            moveToX = 0.0;
            moveToY = 0.0;
            moveToZ = 0.0;
            moveForward = false;
            changeLightType = false;
            isOnLight = false;
            isOnOffTexture = true;
            isChangeTexture = false;
            isChangeSkyBox = false;
        }
        else if (wParam == 'P')
        { // Presp
            isOrtho = false;
            tzP = 0.0;
            txP = 0.0;
            tyP = 0.0;
            xSpeed = 0.0;
            ySpeed = 0.0;
            moveToX = 0.0;
            moveToY = 0.0;
            moveToZ = 0.0;
            moveForward = false;
            changeLightType = false;
            isOnLight = false;
            isOnOffTexture = true;
            isChangeTexture = false;
            isChangeSkyBox = false;
            pSpeed = 0.5;
        }
        else if (wParam == VK_SPACE)
        { // Reset
            forwardCount = 0;
            tzP = 0.0;
            txP = 0.0;
            tyP = 0.0;
            xSpeed = 0.0;
            ySpeed = 0.0;
            moveToX = 0.0;
            moveToY = 0.0;
            moveToZ = 0.0;
            moveForward = false;
            moveBackward = false;
            changeLightType = false;
            isOnLight = false;
            isOnOffTexture = true;
            isChangeTexture = false;
            isChangeSkyBox = false;
            rSpeed1 = 0.0;
            jump = false;
            crouch = false;
            kneel = false;
            rLeg = 0.0;
            rLowerLeg = 0.0;
            moveBodyUpDown = 0.0;
            rElbowFrontBack = 0.0;
            moveSpeed = 10;
            rHeadtoLR = 0.0;
            rHeadtoUD = 0.0;
            rUpperBody = 0.0;
            rArmUpDown = 0.0;
            rElbowUpDown = 0.0;
            rFinger = 0.0;
            rFinger = 0.0;
            waveHand = false;
            shakeHeadNo = false;
            shakeHeadYes = false;
            weaponShoot = false;
            swingSword = false;
            weaponOut = false;
            weapons = 0;
            weapon3 = false;
            shootSpeed = 0.2;
            rArmFrontBack = 0.0;
            rWrist = 0.0;
            rGun = 0.0;
            shootOut = 0.0;
            isRotateKneeChanged = false;
            pSpeed = 0.5;
            backFlip = false;
            fly = false;
            rWholeRobot = 0;
            rFly = 0;
            moveSpeed2 = 30.0;
            flySpeed = 0.1;
        }
        // rotate camera
        if (wParam == VK_LEFT)
        { // prespective projection
            ySpeed += -rotateCamSpeed;
        }
        if (wParam == VK_RIGHT)
        { // prespective projection
            ySpeed += rotateCamSpeed;
        }
        if (wParam == VK_UP)
        { // prespective projection
            if (xSpeed < 90)
            {
                xSpeed += rotateCamSpeed;
            }
        }
        if (wParam == VK_DOWN)
        { // prespective projection
            if (xSpeed > -90)
            {
                xSpeed -= rotateCamSpeed;
            }
        }
        // Projection
        if (wParam == VK_INSERT)
        { // translate camera up
            if (isOrtho)
            {
                tyP -= tSpeed;
            }
            else if (tyP > -40)
                tyP -= pSpeed;
        }
        if (wParam == VK_DELETE)
        { // translate camera down
            if (isOrtho)
            {
                tyP += tSpeed;
            }
            else if (tyP < 40)
                tyP += pSpeed;
        }
        if (wParam == VK_HOME)
        { // translate camera forward
            if (isOrtho)
            {
                if (tzP < -8.0)
                    tzP -= tSpeed;
            }
            else if (tzP > perspN - 2.5) // fixed the view cannot overview
                tzP -= pSpeed;
        }
        if (wParam == VK_END)
        { // translate camera backward
            if (isOrtho)
            {
                if (tzP > 8.0)
                    tzP += tSpeed;
            }
            else if (tzP < 40)
                tzP += pSpeed;
        }
        if (wParam == 'L')
        { // translate camera to right
            if (isOrtho)
            {
                if (tzP < 8.0)
                    txP -= tSpeed;
            }
            else if (txP < 40)
                txP += pSpeed;
        }
        if (wParam == 'K')
        { // translate camera to left
            if (isOrtho)
            {
                if (tzP > -8.0)
                    txP += tSpeed;
            }
            else if (txP > -40)
                txP -= pSpeed;
        }
        // Move Robot
        else if (wParam == 'W')
        { 
            if (forwardCount < 1) {
                moveForward = true;
                forwardCount++;
            }
        }
        else if (wParam == 'A')
        { // turn left
            rSpeed1 -= moveSpeed;
        }
        else if (wParam == 'S')
        { 
            if (forwardCount > -1) {
                moveBackward = true;
                forwardCount--;
            }
        }
        else if (wParam == 'D')
        { // turn right
            rSpeed1 += moveSpeed;
        }
        else if (wParam == VK_CONTROL)
        { // jump
            jump = true;
        }
        else if (wParam == 'Z')
        { // crouch down
            crouch = true;
            if (rLeg < 120)
            {
                rLeg += moveSpeed;
                rLowerLeg += moveSpeed;
                moveBodyUpDown -= moveSpeed / 120;
                rElbowFrontBack += moveSpeed;
            }
        }
        else if (wParam == 'X')
        { // crouch up
            if (rLeg > 0)
            {
                rLeg -= moveSpeed;
                rLowerLeg -= moveSpeed;
                moveBodyUpDown += moveSpeed / 120;
                rElbowFrontBack -= moveSpeed;
            }
            if (rLeg == 0)
            {
                crouch = false;
            }
        }
        else if (wParam == 'C')
        { // kneel down
            kneel = true;
            if (rLeg < 90)
            {
                rLeg += moveSpeed;
                rLowerLeg += moveSpeed;
                rElbowFrontBack += 5;
                rElbowFrontBack += moveSpeed;
                moveBodyUpDown -= moveSpeed / 70;
            }
        }
        else if (wParam == 'V')
        { // kneel up
            if (rLeg > 0)
            {
                rLeg -= moveSpeed;
                rLowerLeg -= moveSpeed;
                rElbowFrontBack -= 5;
                rElbowFrontBack -= moveSpeed;
                moveBodyUpDown += moveSpeed / 70;
            }
            if (rLeg == 0)
            {
                kneel = false;
            }
        }

        // Background and Textures
        if (wParam == 'Y')
        { // change sky box texture
            isChangeSkyBox = !isChangeSkyBox;
        }
        if (wParam == 'U')
        { // change robot texture
            isChangeTexture = !isChangeTexture;
        }
        if (wParam == 'I')
        { // off texture
            isOnOffTexture = !isOnOffTexture;
        }

        // Head
        else if (wParam == VK_F1)
        { // move head to left
            if (rHeadtoLR > -60)
                rHeadtoLR -= moveSpeed;
        }
        else if (wParam == VK_F2)
        { // move head to right
            if (rHeadtoLR < 60)
                rHeadtoLR += moveSpeed;
        }
        else if (wParam == VK_F3)
        { // move head to up
            if (rHeadtoUD > -20)
                rHeadtoUD -= moveSpeed;
        }
        else if (wParam == VK_F4)
        { // move head to down
            if (rHeadtoUD < 15)
                rHeadtoUD += moveSpeed;
        }

        // Turn Upper Body
        else if (wParam == VK_F5)
        { // move upperbody to left
            if (rUpperBody > -60)
            {
                rUpperBody -= moveSpeed;
                rHeadtoLR -= moveSpeed;
            }
        }
        else if (wParam == VK_F6)
        { // move upperbody to right
            if (rUpperBody < 60)
            {
                rUpperBody += moveSpeed;
                rHeadtoLR += moveSpeed;
            }
        }

        // Arms
        else if (wParam == '1')
        { // move arm to front
            if (rArmFrontBack < 180)
                rArmFrontBack += moveSpeed;
        }
        else if (wParam == '2')
        { // move arm to back
            if (rArmFrontBack > 0)
                rArmFrontBack -= moveSpeed;
        }
        else if (wParam == '3')
        { // move arm to up
            if (rArmUpDown < 85)
            {
                rArmUpDown += fabs(moveSpeed) / 2;
            }
        }
        else if (wParam == '4')
        { // move arm to down
            if (rArmUpDown > 0)
            {
                rArmUpDown -= fabs(moveSpeed) / 2;
            }
        }
        else if (wParam == '5')
        { // move lower arm up
            if (rElbowFrontBack < 90)
            {
                rElbowFrontBack += fabs(moveSpeed) / 2;
            }
        }
        else if (wParam == '6')
        { // move lower arm down
            if (rElbowFrontBack > 0)
            {
                rElbowFrontBack -= fabs(moveSpeed) / 2;
            }
        }
        else if (wParam == '7')
        { // turn lower arm forward
            if (rElbowUpDown < 90)
            {
                rElbowUpDown += fabs(moveSpeed) / 2;
            }
        }
        else if (wParam == '8')
        { // turn lower arm forward
            if (rElbowUpDown > -90)
            {
                rElbowUpDown -= fabs(moveSpeed) / 2;
            }
        }

        // Palm and Fingers
        else if (wParam == '9')
        { // move wrist up
            if ((rWrist) < 65)
            {
                rWrist += fabs(moveSpeed);
            }
        }
        else if (wParam == '0')
        { // move wrist down
            if ((rWrist) > -15)
            {
                rWrist -= fabs(moveSpeed);
            }
        }
        else if (wParam == VK_BACK)
        { // move fingers in
            if ((rFinger < 90))
            {
                rFinger += fabs(moveSpeed);
            }
        }
        else if (wParam == VK_F11)
        { // move fingers out
            if ((rFinger) > 0)
            {
                rFinger -= fabs(moveSpeed);
            }
        }

        // Animation
        else if (wParam == 'R')
        {
            waveHand = true;
        }
        else if (wParam == 'E')
        { // move head to say no //animation
            shakeHeadNo = true;
        }
        else if (wParam == 'Q')
        { // move head to say yes //animation
            shakeHeadYes = true;
        }
        else if (wParam == VK_SHIFT)
        {
            weaponShoot = true;
        }
        else if (wParam == VK_TAB)
        {
            swingSword = true;
        }
        else if (wParam == VK_CAPITAL)
        {
            backFlip = true;
        }
        else if (wParam == VK_END)
        {
            fly = true;
        }

        // Weapons
        else if (wParam == VK_F7)
        { // display sword
            weaponOut = true;
            weapons = 1;
            rFinger = 90;
        }
        else if (wParam == VK_F8)
        { // display knife
            weaponOut = true;
            weapons = 2;
            rFinger = 90;
        }
        else if (wParam == VK_F9)
        { // display laser
            weapon3 = true;
            rFinger = 0;
            weapons = 3;
        }

        // Lighting
        if (wParam == 'T')
        { // on off light
            xLight = 0.0f;
            yLight = 0.0f;
            zLight = 0.0f;
            changeLightType = false;
            isOnLight = !isOnLight;
        }
        if (wParam == 'F')
        { // change light types
            changeLightType = !changeLightType;
            xLight = 0.0f;
            yLight = 0.0f;
            zLight = 0.0f;
        }
        if (wParam == 'G')
        { // Light at Top
            yLight += 2.0;
        }
        if (wParam == 'B')
        { // Light at Btm
            yLight -= 2.0;
        }
        if (wParam == 'J')
        { // Light at Right
            xLight -= 2.0;
        }
        if (wParam == 'H')
        { // Light at Left
            xLight += 2.0;
        }
        if (wParam == 'N')
        { // Light at Forward
            zLight += 2.0;
        }
        if (wParam == 'M')
        { // Light at Backward
            zLight -= 2.0;
        }
        if (wParam == 'G') {
            screenIndex = (screenIndex + 1) % 11;
        }
        break;
    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.cAlphaBits = 8;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 0;

    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;

    // choose pixel format returns the number most similar pixel format available
    int n = ChoosePixelFormat(hdc, &pfd);

    // set pixel format returns whether it sucessfully set the pixel format
    if (SetPixelFormat(hdc, n, &pfd))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------------


// GEOMETRIC PRIMITIVES
void drawCircle(float noOfSegment, float radiusCircle)
{
    glBegin(GL_TRIANGLE_FAN);
    for (angle = 0.0; angle < 2 * PI; angle += (2 * PI / noOfSegment))
    { // Draw Circle
        x1_circle = x2_circle + cos(angle) * radiusCircle;
        y1_circle = y2_circle + sin(angle) * radiusCircle;
        glVertex2f(x1_circle, y1_circle);
    }
    glEnd();
}

void drawSphere(float r, float slices, float stacks, GLuint texture)
{
    // Sphere
    GLUquadricObj *sphere = NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    // texture
    glBindTexture(GL_TEXTURE_2D, texture);
    gluQuadricTexture(sphere, GL_TRUE);
    // gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, r, slices, stacks);
    gluDeleteQuadric(sphere);
}

void drawCylinder(float br, float tr, float h, float slices, float stacks, GLuint texture)
{
    // Cylinder
    GLUquadricObj *cylinder = NULL;
    cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    // texture
    glBindTexture(GL_TEXTURE_2D, texture);
    gluQuadricTexture(cylinder, GL_TRUE);
    // gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder, br, tr, h, slices, stacks);
    gluDeleteQuadric(cylinder);
}

void drawQuads(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 1);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(1, 0);
    glVertex3f(x3, y3, z3);
    glTexCoord2f(0, 0);
    glVertex3f(x4, y4, z4);
    glEnd();
}

void drawCube(float length, float height, float width)
{
    float x = length / 2;
    float y = height / 2;
    float z = width / 2;
    drawQuads(-x, y, -z, x, y, -z, x, -y, -z, -x, -y, -z); // front side
    drawQuads(-x, y, z, x, y, z, x, -y, z, -x, -y, z);     // back side
    drawQuads(-x, y, z, -x, y, -z, -x, -y, -z, -x, -y, z); // left side
    drawQuads(x, y, -z, x, y, z, x, -y, z, x, -y, -z);     // right side
    drawQuads(-x, y, z, x, y, z, x, y, -z, -x, y, -z);     // top
    drawQuads(-x, -y, z, x, -y, z, x, -y, -z, -x, -y, -z); // btm
}

void draw5faceCuboid(float length, float height, float width)
{
    float x = length / 2;
    float y = height / 2;
    float z = width / 2;
    drawQuads(-x, y, -z, x, y, -z, x, -y, -z, -x, -y, -z); // front side
    drawQuads(-x, y, z, -x, y, -z, -x, -y, -z, -x, -y, z); // left side
    drawQuads(x, y, -z, x, y, z, x, -y, z, x, -y, -z);     // right side
    drawQuads(-x, y, z, x, y, z, x, y, -z, -x, y, -z);     // top
    drawQuads(-x, -y, z, x, -y, z, x, -y, -z, -x, -y, -z); // btm
}

void drawHemiSphereWithoutGLU(float radius)
{
    const float PI = 3.141592f;
    GLfloat x, y, z, sliceA, stackA;

    float sliceNo = 30.0, stackNo = 30.0;
    for (sliceA = 0.0; sliceA < PI; sliceA += PI / sliceNo)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (stackA = 0.0; stackA < PI; stackA += PI / stackNo)
        {
            x = radius * cos(stackA) * sin(sliceA);
            y = radius * sin(stackA) * sin(sliceA);
            z = radius * cos(sliceA);
            glVertex3f(x, y, z);
            x = radius * cos(stackA) * sin(sliceA + (PI / stackNo));
            y = radius * sin(stackA) * sin(sliceA + (PI / sliceNo));
            z = radius * cos(sliceA + (PI / sliceNo));
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void triangularPrism(float x, float y, float z)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(x, 0, z);
    glTexCoord2f(1, 1);
    glVertex3f(x, 0, -z);
    glTexCoord2f(1, 0);
    glVertex3f(-x, 0, -z);
    glTexCoord2f(0, 0);
    glVertex3f(-x, 0, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, 0, -z);
    glTexCoord2f(1, 1);
    glVertex3f(x, y, -z);
    glTexCoord2f(1, 0);
    glVertex3f(-x, y, -z);
    glTexCoord2f(0, 0);
    glVertex3f(-x, 0, -z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y, -z);
    glTexCoord2f(1, 1);
    glVertex3f(-x, y, -z);
    glTexCoord2f(1, 0);
    glVertex3f(-x, 0, z);
    glTexCoord2f(0, 0);
    glVertex3f(x, 0, z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0, 0);
    glVertex3f(x, 0, z);
    glTexCoord2f(1, 1);
    glVertex3f(x, y, -z);
    glTexCoord2f(1, 0);
    glVertex3f(x, 0, -z);

    glTexCoord2f(0, 0);
    glVertex3f(-x, 0, z);
    glTexCoord2f(1, 1);
    glVertex3f(-x, y, -z);
    glTexCoord2f(1, 0);
    glVertex3f(-x, 0, -z);
    glEnd();
}

// Texture
GLuint loadTexture(LPCSTR filename)
{
    // Take from step 1
    GLuint texture = 0; // texture name

    // Step 3: Initialize texture info
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Unpack bitmap file
    HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
                                      filename, IMAGE_BITMAP, 0, 0,
                                      LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(hBMP, sizeof(BMP), &BMP);

    // Step 4: Assign texture to polygon
    if (isOnOffTexture)
    {
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

    // Take from step 5
    DeleteObject(hBMP);
    return texture;
}

// UPPER BODY
// 56
void drawHead()
{
    GLuint texture, texture1;
    glColor3f(0.96, 0.93, 0.89);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }

    glPushMatrix();
    {
        glTranslatef(0.0, 0.0, 0.626); // head position

        glPushMatrix();
        {
            glTranslatef(0.0, 0.66, -0.626); // head position
            glRotatef(rHeadtoLR, 0, 1, 0);   // rotate head left right
            glRotatef(rHeadtoUD, 1, 0, 0);   // rotate head up down
            glTranslatef(0.0, -0.66, 0.626); // make it stick to a fixed position to rotate

            // head
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.0, 0.66, -0.626);
                glRotatef(10, 1, 0, 0);
                drawCube(0.11, 0.03, 0.15); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.65, -0.53);
                glRotatef(-33, 1, 0, 0);
                triangularPrism(0.04, 0.03, 0.025); // 5
            }
            glPopMatrix();

            glPushMatrix();
            {
                /*glColor3f(1, 1, 0);*/
                glTranslatef(0.0, 0.746, -0.684);
                glRotatef(9, 1, 0, 0);
                drawCylinder(0.06, 0.06, 0.18, 10, 10, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("shinyBlack.bmp");
            }

            glColor3f(0.83, 0.83, 0.83);
            glPushMatrix();
            {
                glLineWidth(6);
                glTranslatef(0.0, 0.72, -0.51);
                glRotatef(9, 1, 0, 0);
                drawCylinder(0.055, 0.04, 0.005, 10, 10, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            // face
            if (isChangeTexture)
            {
                texture1 = loadTexture("blueEye.bmp");
            }
            else
            {
                texture1 = loadTexture("yellowFace.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 1, 1);
                glTranslatef(0.0, 0.725, -0.51);
                glRotatef(9, 1, 0, 0);
                drawCircle(10, 0.048); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture1);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.05, 0.67, -0.616);
                glRotatef(-90, 0, 1, 0);
                glRotatef(-9, 0, 0, 1);
                glRotatef(1, 1, 0, 0);
                triangularPrism(0.085, 0.08, 0.006); // 5
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(-0.05, 0.67, -0.616);
                glRotatef(90, 0, 1, 0);
                glRotatef(9, 0, 0, 1);
                glRotatef(4, 1, 0, 0);
                triangularPrism(0.085, 0.08, 0.006); // 5
            }
            glPopMatrix();

            glPushMatrix();
            {
                /*glColor3f(0, 0, 1);*/
                glTranslatef(0, 0.745, -0.7);
                glRotatef(9, 1, 0, 0);
                drawCylinder(0.04, 0.06, 0.02, 10, 10, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            texture = loadTexture("backHead.bmp");
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(0, 0.745, -0.70);
                glRotatef(9, 1, 0, 0);
                drawCircle(8, 0.04); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.04, 0.69, -0.68);
                drawCube(0.03, 0.04, 0.03); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(-0.04, 0.69, -0.68);
                drawCube(0.03, 0.04, 0.03); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            texture = loadTexture("sideHead.bmp");
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(0.055, 0.712, -0.61);
                glRotatef(90, 0, 1, 0);
                drawCylinder(0.07, 0.05, 0.01, 15, 15, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.065, 0.712, -0.61);
                glRotatef(90, 0, 1, 0);
                drawCylinder(0.05, 0.07, 0.01, 15, 15, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            texture = loadTexture("sideHeadRadio.bmp");
            // ear circle
            glPushMatrix();
            {
                // glColor3f(1, 0, 1);
                glTranslatef(0.065, 0.712, -0.61);
                glRotatef(90, 0, 1, 0);
                drawCircle(15, 0.05); // 1
            }
            glPopMatrix();

            // ear circle
            glPushMatrix();
            {
                // glColor3f(1, 0, 1);
                glTranslatef(-0.065, 0.712, -0.61);
                glRotatef(90, 0, 1, 0);
                drawCircle(15, 0.05); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            texture = loadTexture("red.bmp");
            // right ear
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(0.05, 0.759, -0.665);
                glRotatef(-90, 0, 0, 1);
                drawHemiSphereWithoutGLU(0.02); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("shinyBlack.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            glPushMatrix();
            {
                glTranslatef(0.06, 0.825, -0.74);
                glRotatef(-50, 1, 0, 0);
                drawCube(0.003, 0.18, 0.03); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            // left ear
            texture = loadTexture("red.bmp");
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.05, 0.759, -0.665);
                glRotatef(90, 0, 0, 1);
                drawHemiSphereWithoutGLU(0.02); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("shinyBlack.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            glPushMatrix();
            {
                glTranslatef(-0.06, 0.825, -0.74);
                glRotatef(-50, 1, 0, 0);
                drawCube(0.003, 0.18, 0.03); // 6
            }
            glPopMatrix();
        }
        glPopMatrix(); // pop rotate head
    }
    glPopMatrix(); // pop translate position
    glDeleteTextures(1, &texture);

    middleBody(); // middle body
}

// 142
void middleBody()
{
    glPushMatrix();
    {
        glTranslatef(0.0, 0.0, 0.626); // body position

        glPushMatrix();
        {
            glTranslatef(0.0, 0.0, -0.66);        // set back to origin(rotate point)
            glRotatef(rUpperBody, 0.0, 1.0, 0.0); // rotate whole upper body
            glTranslatef(0.0, 0.0, 0.66);         // set back to origin(rotate point)

            glPushMatrix();
            {
                /*glTranslatef(0.0, 0.02, 0.0);*/
                RotateRightArm();
                RotateLeftArm();
            }
            glPopMatrix();

            GLuint texture;
            glColor3f(0.96, 0.93, 0.89);
            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }

            glColor3f(0.83, 0.83, 0.83);
            // neck
            glPushMatrix();
            {
                glTranslatef(0.0, 0.6195, -0.567);
                glRotatef(45, 1, 0, 0);
                triangularPrism(0.05, 0.02, 0.02); // 5
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.607, -0.675);
                glRotatef(180, 0, 1, 0);
                glRotatef(10, 1, 0, 0);
                triangularPrism(0.05, 0.06, 0.015); // 5
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.65, -0.626);
                glRotatef(180, 0, 1, 0);
                glRotatef(-23, 1, 0, 0);
                triangularPrism(0.05, 0.02, 0.0535); // 5
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.62, -0.623);
                drawCube(0.09, 0.07, 0.129); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            glColor3f(0.96, 0.93, 0.89);
            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            // back
            glPushMatrix();
            {
                // glColor3f(1, 1, 1);
                glTranslatef(0.0, 0.44, -0.77);
                glRotatef(45, 1, 0, 0);
                triangularPrism(0.15, 0.13, 0.06); // 5
            }
            glPopMatrix();

            // screen
            glPushMatrix();
            {
                glColor3f(1, 1, 1);
                glLineWidth(1);
                glTranslatef(0.0, 0.47, -0.52);
                draw5faceCuboid(0.28, 0.2, 0.03); // 5
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            texture = loadTexture(screenNames[screenIndex]);
            glPushMatrix();
            {
                /*glColor3f(1, 0, 0);*/
                glTranslatef(-0.13, 0.56, -0.52);
                glBegin(GL_QUAD_STRIP); // 1
                glTexCoord2f(0, 1);
                glVertex3f(0.0, 0.0, 0.0);
                glTexCoord2f(0, 0);
                glVertex3f(0.0, -0.18, 0.0);
                glTexCoord2f(1, 1);
                glVertex3f(0.26, 0.0, 0.0);
                glTexCoord2f(1, 0);
                glVertex3f(0.26, -0.18, 0.0);
                glEnd();
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // middlebody
            // middle cube
            glPushMatrix();
            {
                glColor3f(0.96, 0.93, 0.89);
                glTranslatef(0.0, 0.49, -0.629);
                drawCube(0.14, 0.23, 0.15); // 6
            }
            glPopMatrix();

            // RIGHT UPPER ARM
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.05, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.11, 0.11, 0.093, 10, 10, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(0, 1, 0);
                glTranslatef(0.15, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.1, 0.07, 0.02, 50, 50, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.173, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.068, 0.068, 0.01, 10, 10, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(0, 1, 0);
                glTranslatef(0.186, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.08, 0.08, 0.005, 10, 10, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.186, 0.46, -0.64);
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(50, 0.07); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(0, 0, 1);
                glTranslatef(0.193, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.08, 0.04, 0.06, 100, 100, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            glPushMatrix();
            {
                glColor3f(0.83, 0.83, 0.83);
                glTranslatef(0.248, 0.46, -0.64);
                drawSphere(0.05, 30, 30, texture); // 1
            }
            glPopMatrix();

            // LEFT UPPER ARM
            glPushMatrix();
            {
                glColor3f(0.96, 0.93, 0.89);
                glTranslatef(-0.145, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.11, 0.11, 0.093, 10, 10, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(0, 1, 0);
                glTranslatef(-0.17, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.07, 0.1, 0.02, 50, 50, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(-0.183, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.068, 0.068, 0.01, 10, 10, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(0, 1, 0);
                glTranslatef(-0.19, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.08, 0.08, 0.005, 10, 10, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(-0.192, 0.46, -0.64);
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(50, 0.07); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(0, 0, 1);
                glTranslatef(-0.252, 0.46, -0.64);
                glRotatef(90, 0.0, 0.5, 0.0);
                drawCylinder(0.04, 0.08, 0.06, 100, 100, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            glPushMatrix();
            {
                glColor3f(0.83, 0.83, 0.83);
                glTranslatef(-0.245, 0.46, -0.64);
                drawSphere(0.05, 30, 30, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // lower middle body (3 blocks below the screen)
            glPushMatrix();
            {
                glColor3f(0.83, 0.83, 0.83);
                glTranslatef(-0.088, 0.275, -0.56);
                glRotatef(20, 1, 0, 0);
                glRotatef(-10, 0, 1, 0);
                glRotatef(3, 0, 0, 1);
                drawCube(0.06, 0.15, 0.055); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.088, 0.235, -0.575);
                glRotatef(20, 1, 0, 0);
                glRotatef(-10, 0, 1, 0);
                glRotatef(3, 0, 0, 1);
                drawCube(0.07, 0.14, 0.075); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.0, 0.275, -0.56);
                glRotatef(20, 1, 0, 0);
                drawCube(0.06, 0.15, 0.065); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(0.0, 0.235, -0.575);
                glRotatef(20, 1, 0, 0);
                drawCube(0.07, 0.14, 0.075); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.088, 0.275, -0.56);
                glRotatef(20, 1, 0, 0);
                glRotatef(10, 0, 1, 0);
                glRotatef(-3, 0, 0, 1);
                drawCube(0.06, 0.15, 0.065); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(0.088, 0.235, -0.575);
                glRotatef(20, 1, 0, 0);
                glRotatef(10, 0, 1, 0);
                glRotatef(-3, 0, 0, 1);
                drawCube(0.07, 0.14, 0.075); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }

            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.088, 0.3, -0.558);
                glRotatef(-70, 1, 0, 0);
                drawCylinder(0.01, 0.01, 0.08, 100, 100, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.3, -0.558);
                glRotatef(-70, 1, 0, 0);
                drawCylinder(0.01, 0.01, 0.08, 100, 100, texture); // 1
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.088, 0.3, -0.558);
                glRotatef(-70, 1, 0, 0);
                drawCylinder(0.01, 0.01, 0.08, 100, 100, texture); // 1
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            // Inside the middle body
            glPushMatrix();
            {
                glColor3f(0.96, 0.93, 0.89);
                glTranslatef(0.0, 0.315, -0.63);
                glRotatef(20, 1, 0, 0);
                drawCube(0.09, 0.17, 0.05); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.2, -0.656);
                drawCube(0.09, 0.15, 0.05); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            texture = loadTexture("shinySilver.bmp");
            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(0.05, 0.25, -0.653);
                glRotatef(20, 1, 0, 0);
                drawCube(0.045, 0.15, 0.03); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.05, 0.25, -0.653);
                glRotatef(20, 1, 0, 0);
                drawCube(0.045, 0.15, 0.03); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(0, 1, 1);
                glTranslatef(0.0, 0.37, -0.7);
                drawCube(0.18, 0.05, 0.02); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 0, 1);
                glTranslatef(0.0, 0.3, -0.68);
                glRotatef(20, 1, 0, 0);
                drawCube(0.18, 0.12, 0.02); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("blueColor.bmp");
            }
            else
            {
                texture = loadTexture("orange.bmp");
            }
            glPushMatrix();
            {
                // glColor3f(1, 0, 0);
                glTranslatef(0.0, 0.3, -0.71);
                glRotatef(20, 1, 0, 0);
                drawCube(0.09, 0.12, 0.03); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.21, -0.69);
                glRotatef(-36, 1, 0, 0);
                drawCube(0.09, 0.12, 0.042); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);
        }
        glPopMatrix(); // pop rotate body
    }
    glPopMatrix(); // pop translate position
}

void RotateLeftArm()
{
    // left lower arm
    glPushMatrix();
    {
        glTranslatef(-0.49, 0, 0);
        glPushMatrix();
        {

            glTranslatef(0.0, 0.43, -0.64);

            if (moveForward)
            {
                glRotatef(-rArmFrontBack, 1.0, 0.0, 0.0);
            }
            else if (moveBackward || jump)
            {
                glRotatef(rArmFrontBack, 1.0, 0.0, 0.0);
            }
            else if (waveHand) {
                glRotatef(0.0, 1.0, 0.0, 0.0);
            }
            else
                glRotatef(-rArmFrontBack, 1.0, 0.0, 0.0);

            glTranslatef(0.0, -0.43, 0.64);
            glPushMatrix();
            {
                glTranslatef(0.26, 0.45, 0.0);

                if(!waveHand)
                    glRotatef(-rArmUpDown, 0.0, 0.0, 1.0);


                glTranslatef(-0.26, -0.45, 0.0);
                drawLeftArm();

                glPushMatrix();
                {
                    glTranslatef(0.0, 0.15, -0.64);
                    if(!waveHand)
                        glRotatef(-rElbowFrontBack, 1, 0, 0);
                    glTranslatef(0.0, -0.15, 0.64);

                    glPushMatrix();
                    {
                        glTranslatef(0.25, -0.6, -0.64);
                        if(!waveHand)
                            glRotatef(rElbowUpDown, 0, 1, 0);
                        glTranslatef(-0.25, 0.6, 0.64);
                        drawElbowSegment();

                        // Weapons
                        glPushMatrix();
                        {
                            switch (weapons)
                            {
                            case 1:
                                drawWeaponSword();
                                break;
                            case 3:
                                glPushMatrix();
                                {
                                    glTranslatef(0.5, 0.0, -0.8);
                                    drawWeaponLaser();
                                }
                                glPopMatrix();
                                break;

                            default:
                                break;
                            }
                        }
                        glPopMatrix();

                        glPushMatrix();
                        {
                            glTranslatef(0.25, -0.07, 0.0);
                            glRotatef(-rWrist, 0, 0, 1);
                            glTranslatef(-0.25, 0.07, 0.0);
                            drawLeftHand();
                        }
                        glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void RotateRightArm()
{
    // right lower arm
    glPushMatrix();
    {
        glTranslatef(0.0, 0.43, -0.64);
        if (!weaponShoot)
        {
            if (!swingSword)
            {
                if (!fly)
                {
                    if (moveForward)
                    {
                        glRotatef(rArmFrontBack, 1.0, 0.0, 0.0);
                    }
                    else if (moveBackward)
                    {
                        glRotatef(-rArmFrontBack, 1.0, 0.0, 0.0);
                    }
                    else
                        glRotatef(-rArmFrontBack, 1.0, 0.0, 0.0);
                }
            }
        }
        glTranslatef(0.0, -0.43, 0.64);
        glPushMatrix();
        {
            glTranslatef(0.23, 0.45, 0.0);
            glRotatef(rArmUpDown, 0.0, 0.0, 1.0);
            glTranslatef(-0.23, -0.45, 0.0);
            drawRightArm();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.15, -0.64);
                if (!swingSword)
                    glRotatef(-rElbowFrontBack, 1, 0, 0);
                glTranslatef(0.0, -0.15, 0.64);

                glPushMatrix();
                {
                    glTranslatef(0.25, -0.6, -0.64);
                    glRotatef(-rElbowUpDown, 0, 1, 0);
                    glTranslatef(-0.25, 0.6, 0.64);
                    drawElbowSegment();

                    glPushMatrix();
                    {
                        glTranslatef(0.25, -0.07, 0.0);
                        glRotatef(rWrist, 0, 0, 1);
                        glTranslatef(-0.25, 0.07, 0.0);
                        drawRightHand();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

// 33
void drawRightArm()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.23, 0.387, -0.64);
        drawCube(0.007, 0.02, 0.04); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.262, 0.393, -0.64);
        drawCube(0.007, 0.03, 0.04); // 6
    }
    glPopMatrix();
    // YELLOW
    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(0.222, 0.385, -0.64);
        drawCube(0.007, 0.014, 0.04); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(0.27, 0.385, -0.64);
        drawCube(0.007, 0.014, 0.04); // 6
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("shinySilver.bmp");
    // screw1
    // glPushMatrix();{
    // glColor3f(0, 0, 1);
    // glTranslatef(0.29, 0.385, -0.63);
    // glRotatef(90, 0.0, 1.0, 0.0);
    glPushMatrix();
    {
        glPointSize(4);
        glBegin(GL_POINTS); // 1
        glVertex3f(0.29, 0.385, -0.63);
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glPointSize(4);
        glBegin(GL_POINTS); // 1
        glVertex3f(0.29, 0.385, -0.65);
        glEnd();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(0.256, 0.385, -0.64);
        drawCube(0.05, 0.014, 0.04); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(0.25, 0.375, -0.645);
        glRotatef(90, 1.0, 0, 0);
        drawCylinder(0.035, 0.035, 0.01, 100, 100, texture); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    drawUpperArm();
}

// 33
void drawLeftArm()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }

    glPushMatrix();
    {
        glTranslatef(0.49, 0, 0);
        glPushMatrix();
        {
            // glColor3f(1, 0, 0);
            glTranslatef(-0.22, 0.387, -0.64);
            drawCube(0.007, 0.02, 0.04); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 0, 0);
            glTranslatef(-0.254, 0.393, -0.64);
            drawCube(0.007, 0.03, 0.04); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.212, 0.385, -0.64);
            drawCube(0.007, 0.014, 0.04); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.264, 0.385, -0.64);
            drawCube(0.007, 0.014, 0.04); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("shinySilver.bmp");
        glPushMatrix();
        {
            glPointSize(4);
            glBegin(GL_POINTS); // 1
            glVertex3f(-0.284, 0.385, -0.63);
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glPointSize(4);
            glBegin(GL_POINTS); // 1
            glVertex3f(-0.284, 0.385, -0.65);
            glEnd();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.235, 0.385, -0.64);
            drawCube(0.04, 0.014, 0.04); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.24, 0.375, -0.64);
            glRotatef(90, 1.0, 0, 0);
            drawCylinder(0.035, 0.035, 0.01, 100, 100, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    drawUpperArm();
}

// 77
void drawUpperArm()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.25, 0.298, -0.638);
        drawCube(0.075, 0.14, 0.08); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        /*glColor3f(0, 0, 1);*/
        glTranslatef(0.25, 0.361, -0.606);
        glRotatef(180, 0, 1.0, 0);
        triangularPrism(0.038, 0.02, 0.01); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.345, -0.688);
        glRotatef(180, 0, 1.0, 0);
        triangularPrism(0.038, 0.024, 0.011); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.25, 0.296, -0.689);
        drawCube(0.075, 0.1, 0.02); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.219, -0.618);
        glRotatef(90, 1.0, 0.0, 0);
        triangularPrism(0.038, 0.02, 0.01); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.228, -0.678);
        glRotatef(180, 0.0, 1.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0);
        triangularPrism(0.038, 0.02, 0.02); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.22, -0.648);
        drawCube(0.075, 0.02, 0.06); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(0.25, 0.20, -0.613);
        glRotatef(180, 0.0, 1.0, 0);
        triangularPrism(0.03, 0.03, 0.01); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.2, -0.685);
        triangularPrism(0.03, 0.04, 0.009); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.205, -0.649);
        drawCube(0.062, 0.01, 0.06); // 6
    }
    glPopMatrix();

    // right side cylinder
    glPushMatrix();
    {
        // glColor3f(0, 1, 1);
        glTranslatef(0.27, 0.164, -0.642);
        glRotatef(90, 0, 1, 0);
        drawCylinder(0.05, 0.05, 0.01, 100, 100, texture); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(0, 1, 1);
        glTranslatef(0.27, 0.162, -0.642);
        glRotatef(90, 0, 1, 0);
        drawCircle(100, 0.052); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        /*glColor3f(0, 1, 1);*/
        glTranslatef(0.273, 0.185, -0.692);
        glRotatef(90, 1, 0, 0);
        triangularPrism(0.006, 0.015, 0.015); // 5
    }
    glPopMatrix();

    // left side cylinder
    glPushMatrix();
    {
        // glColor3f(0, 1, 1);
        glTranslatef(0.222, 0.164, -0.642);
        glRotatef(90, 0, 1, 0);
        drawCylinder(0.05, 0.05, 0.01, 100, 100, texture); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(0, 1, 1);
        glTranslatef(0.222, 0.162, -0.642);
        glRotatef(90, 0, 1, 0);
        drawCircle(100, 0.052); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        /*glColor3f(0, 1, 1);*/
        glTranslatef(0.225, 0.185, -0.692);
        glRotatef(90, 1, 0, 0);
        triangularPrism(0.006, 0.015, 0.015); // 5
    }
    glPopMatrix();

    glPushMatrix();
    {
        /*glColor3f(1, 0, 1);*/
        glTranslatef(0.25, 0.18, -0.683);
        drawCube(0.035, 0.08, 0.02); // 6
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    glPushMatrix();
    {
        glColor3f(0.83, 0.83, 0.83);
        glTranslatef(0.233, 0.16, -0.63);
        glRotatef(90, 0, 1, 0);
        drawCylinder(0.04, 0.04, 0.034, 100, 100, texture); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.25, 0.16, -0.64);
        glRotatef(90, 1, 0, 0);
        glRotatef(270, 0, 0, 1);
        drawHemiSphereWithoutGLU(0.045); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.25, 0.16, -0.64);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 0, 1);
        drawHemiSphereWithoutGLU(0.045); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);
}

// 10
void drawElbowSegment()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }

    // ElbowSegment
    glPushMatrix();
    {
        // glColor3f(0, 1, 1);
        glTranslatef(0.25, 0.12, -0.66);
        drawCube(0.035, 0.045, 0.05); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(0.25, 0.098, -0.643);
        glRotatef(90, 1, 0, 0);
        drawCylinder(0.05, 0.05, 0.09, 100, 100, texture); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.25, 0.008, -0.643);
        glRotatef(90, 1, 0, 0);
        drawCylinder(0.05, 0.04, 0.02, 100, 100, texture); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("darkRed.bmp");
    }
    else
    {
        texture = loadTexture("earColor.bmp");
    }

    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(0.249, -0.015, -0.643);
        glRotatef(90, 1, 0, 0);
        drawCylinder(0.04, 0.035, 0.048, 100, 100, texture); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("darkRed.bmp");
    }
    else
    {
        texture = loadTexture("paintYellow.bmp");
    }

    glPushMatrix();
    {
        glColor3f(0.83, 0.83, 0.83);
        glTranslatef(0.25, -0.075, -0.643);
        drawSphere(0.03, 30, 30, texture); // 1
    }
    glPopMatrix();

    glDeleteTextures(1, &texture);
}

// 120
void drawLeftHand()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }

    glPushMatrix();
    {
        glTranslatef(0.25, -0.12, -0.64);
        glRotatef(270, 0.0, 1.0, 0.0);
        glScalef(0.15, 0.15, 0.15);

        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.3, 0.0, 0.0);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                triangularPrism(0.15, 0.2, 0.1); // 5
            }
            glPopMatrix();
        }
        glPopMatrix();

        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0, 0.1, 0.0);
            drawCube(0.4, 0.2, 0.3); // 6
        }
        glPopMatrix();

        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.3, 0.0, 0.0);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                triangularPrism(0.15, 0.2, 0.1); // 5
            }
            glPopMatrix();
        }
        glPopMatrix();

        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.25, 0.0);
            drawCube(0.8, 0.5, 0.3); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        // last finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);

        glPushMatrix();
        {
            glTranslatef(-0.3, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weapon3 || weaponOut)
                glRotatef(rFinger, 1, 0, 0);
            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(-0.3, -0.6, 0.0);
                drawCube(0.14, 0.1, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);

                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.3, -0.68, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();
            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(-0.3, -0.76, 0.0);
                drawCube(0.14, 0.1, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.3, -0.84, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weapon3 || weaponOut)
                        glRotatef((rFinger / 4), 1, 0, 0);
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(-0.3, -0.94, 0.0);
                        drawCube(0.14, 0.1, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        ////second last finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.1, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            //if is sword
            if (!weapon3 || weaponOut)
                glRotatef(rFinger, 1, 0, 0);


            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(-0.1, -0.62, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.1, -0.73, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(-0.1, -0.82, 0.0);
                drawCube(0.14, 0.12, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.1, -0.91, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weapon3 || weaponOut)
                        glRotatef((rFinger / 4), 1, 0, 0);
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(-0.1, -1.02, 0.0);
                        drawCube(0.14, 0.13, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // third last finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.1, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weapon3 || weaponOut)
                glRotatef(rFinger, 1, 0, 0);
            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(0.1, -0.62, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.1, -0.73, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.1, -0.84, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.1, -0.95, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weapon3 || weaponOut)
                        glRotatef((rFinger / 4), 1, 0, 0);
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(0.1, -1.07, 0.0);
                        drawCube(0.14, 0.15, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // second finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.3, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weapon3 || weaponOut)
                glRotatef(rFinger, 1, 0, 0);


            if (weaponShoot)
                glRotatef(-90, 1, 0, 0);

            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(0.3, -0.62, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);


                if (weaponShoot)
                    glRotatef(-90, 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.3, -0.73, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.3, -0.82, 0.0);
                drawCube(0.14, 0.12, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weapon3 || weaponOut)
                    glRotatef((rFinger / 2), 1, 0, 0);


                if (weaponShoot)
                    glRotatef(-90, 1, 0, 0);
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.3, -0.91, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weapon3 || weaponOut)
                        glRotatef((rFinger / 4), 1, 0, 0);
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(0.3, -1.02, 0.0);
                        drawCube(0.14, 0.13, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // thumb
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.43, -0.2, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.51, -0.27, 0.0);
            glRotatef(310, 0.0, 0.0, 1.0);
            drawCube(0.14, 0.13, 0.15); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.57, -0.34, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.58, -0.45, 0.0);
            drawCube(0.14, 0.13, 0.15); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);
    }
    glPopMatrix();
}

// 120
void drawRightHand()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }

    glPushMatrix();
    {
        glTranslatef(0.25, -0.12, -0.64);
        glRotatef(270, 0.0, 1.0, 0.0);
        glScalef(0.15, 0.15, 0.15);

        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.3, 0.0, 0.0);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                triangularPrism(0.15, 0.2, 0.1); // 5
            }
            glPopMatrix();
        }
        glPopMatrix();

        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0, 0.1, 0.0);
            drawCube(0.4, 0.2, 0.3); // 6
        }
        glPopMatrix();

        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.3, 0.0, 0.0);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                triangularPrism(0.15, 0.2, 0.1); // 5
            }
            glPopMatrix();
        }
        glPopMatrix();

        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.25, 0.0);
            drawCube(0.8, 0.5, 0.3); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        // last finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.3, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weaponOut)
            {
                if (!swingSword)
                {
                    if (!fly)
                        glRotatef(-rFinger, 1, 0, 0);
                }
            }
            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(-0.3, -0.6, 0.0);
                drawCube(0.14, 0.1, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.3, -0.68, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);

            glPushMatrix();
            {
                glTranslatef(-0.3, -0.76, 0.0);
                drawCube(0.14, 0.1, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly )
                            glRotatef((-rFinger / 2), 1, 0, 0);

                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.3, -0.84, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weaponOut)
                    {
                        if (!swingSword)
                        {
                            if (!fly)
                                glRotatef((-rFinger / 4), 1, 0, 0);
                        }
                    }
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(-0.3, -0.94, 0.0);
                        drawCube(0.14, 0.1, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // second last finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.1, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weaponOut)
            {
                if (!swingSword)
                {
                    if (!fly)
                        glRotatef(-rFinger, 1, 0, 0);

                }
            }
            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(-0.1, -0.62, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.1, -0.73, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(-0.1, -0.82, 0.0);
                drawCube(0.14, 0.12, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(-0.1, -0.91, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weaponOut)
                    {
                        if (!swingSword)
                        {
                            if (!fly)
                                glRotatef((-rFinger / 4), 1, 0, 0);
                        }
                    }
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(-0.1, -1.02, 0.0);
                        drawCube(0.14, 0.13, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // third last finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.1, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weaponOut)
            {
                if (!swingSword)
                {
                    if (!fly)
                        glRotatef(-rFinger, 1, 0, 0);
                }
            }
            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(0.1, -0.62, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.1, -0.73, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.1, -0.84, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.1, -0.95, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weaponOut)
                    {
                        if (!swingSword)
                        {
                            if (!fly)
                                glRotatef((-rFinger / 4), 1, 0, 0);
                        }
                    }
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(0.1, -1.07, 0.0);
                        drawCube(0.14, 0.15, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // second finger
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.3, -0.5, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.5, 0.0);
            if (!weaponOut)
            {
                if (!swingSword)
                {
                    if (!fly)
                        glRotatef(-rFinger, 1, 0, 0);
                }
            }
            glTranslatef(0.0, 0.5, -0.0);
            glPushMatrix();
            {
                glTranslatef(0.3, -0.62, 0.0);
                drawCube(0.14, 0.15, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.3, -0.73, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);
            }
            glPopMatrix();

            if (isChangeTexture)
            {
                texture = loadTexture("blueJoint.bmp");
            }
            else
            {
                texture = loadTexture("darkGrey.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.3, -0.82, 0.0);
                drawCube(0.14, 0.12, 0.15); // 6
            }
            glPopMatrix();
            glDeleteTextures(1, &texture);

            if (isChangeTexture)
            {
                texture = loadTexture("darkRed.bmp");
            }
            else
            {
                texture = loadTexture("earColor.bmp");
            }
            // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            {
                glTranslatef(0.0, -0.75, 0.0);
                if (!weaponOut)
                {
                    if (!swingSword)
                    {
                        if (!fly)
                            glRotatef((-rFinger / 2), 1, 0, 0);
                    }
                }
                glTranslatef(0.0, 0.75, -0.0);
                glPushMatrix();
                {
                    glTranslatef(0.3, -0.91, 0.0);
                    drawSphere(0.08, 30, 30, texture); // 1
                }
                glPopMatrix();
                glDeleteTextures(1, &texture);

                if (isChangeTexture)
                {
                    texture = loadTexture("blueJoint.bmp");
                }
                else
                {
                    texture = loadTexture("darkGrey.bmp");
                }
                // glColor3f(1.0, 1.0, 1.0)
                glPushMatrix();
                {
                    glTranslatef(0.0, -0.75, 0.0);
                    if (!weaponOut)
                    {
                        if (!swingSword)
                        {
                            if (!fly)
                                glRotatef((-rFinger / 4), 1, 0, 0);
                        }
                    }
                    glTranslatef(0.0, 0.75, -0.0);
                    glPushMatrix();
                    {
                        glTranslatef(0.3, -1.02, 0.0);
                        drawCube(0.14, 0.13, 0.15); // 6
                    }
                    glPopMatrix();
                    glDeleteTextures(1, &texture);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();

        // thumb
        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.43, -0.2, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.51, -0.27, 0.0);
            glRotatef(310, 0.0, 0.0, 1.0);
            drawCube(0.14, 0.13, 0.15); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("darkRed.bmp");
        }
        else
        {
            texture = loadTexture("earColor.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.57, -0.34, 0.0);
            drawSphere(0.08, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.58, -0.45, 0.0);
            drawCube(0.14, 0.13, 0.15); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);
    }
    glPopMatrix();
}

// LOWER BODY
// 63
void drawBtmButt()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    texture = loadTexture("backRect.bmp");

    glPushMatrix();
    {
        glTranslatef(0.0, 0.088, 0.85); // connect with upper body

        // bottom middle part //47 polygons
        // behind butt RECT box

        glPushMatrix();
        {
            // glColor3f(1.0, 1.0, 1.0);
            glTranslatef(0.0, 0.0, -1.0);
            drawCube(0.15, 0.09, 0.08); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // behind butt right SPHERE
        glPushMatrix();
        {
            glColor3f(0.83, 0.83, 0.83);
            glTranslatef(0.15, 0.0, -1.0);
            drawSphere(0.045, 30, 30, texture); // 1
        }
        glPopMatrix();

        // behind butt left SPHERE
        glPushMatrix();
        {
            glColor3f(0.83, 0.83, 0.83);
            glTranslatef(-0.15, 0.0, -1.0);
            drawSphere(0.045, 30, 30, texture); // 1
        }
        glPopMatrix();

        // behind butt right connect CYLINDER
        glPushMatrix();
        {
            glColor3f(0.96, 0.93, 0.89);
            glTranslatef(0.07, 0.0, -1.0);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.03, 0.03, 0.05, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // behind butt left connect CYLINDER
        glPushMatrix();
        {
            // glColor3f(1.0, 1.0, 1.0);
            glTranslatef(-0.125, 0.0, -1.0);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.03, 0.03, 0.05, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // bottom middle sphere
        glPushMatrix();
        {
            glColor3f(0.83, 0.83, 0.83);
            glTranslatef(0.0, 0.0, -0.85);
            drawSphere(0.07, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // bottom connect middle sphere to RECT box right //12
        glColor3f(0.96, 0.93, 0.89);
        glPushMatrix();
        {
            glTranslatef(0.03, -0.05, 0.0);
            // glColor3f(0.0, 1.0, 1.0);
            drawQuads(-0.01, 0.0, -0.9, -0.01, 0.02, -0.91, 0.01, 0.02, -0.91, 0.01, 0.0, -0.9);    // btm 1st btm front
            drawQuads(-0.01, 0.0, -0.92, -0.01, 0.02, -0.93, 0.01, 0.02, -0.93, 0.01, 0.0, -0.92);  // btm 1st btm back
            drawQuads(-0.01, 0.0, -0.92, -0.01, 0.02, -0.93, -0.01, 0.02, -0.91, -0.01, 0.0, -0.9); // btm 1st btm left side
            drawQuads(0.01, 0.02, -0.93, 0.01, 0.0, -0.92, 0.01, 0.0, -0.9, 0.01, 0.02, -0.91);     // btm 1st btm right side
            // glColor3f(0.0, 0.0, 1.0);
            drawQuads(-0.01, 0.02, -0.91, -0.01, 0.04, -0.93, 0.01, 0.04, -0.93, 0.01, 0.02, -0.91); // btm 2nd btm front
            drawQuads(-0.01, 0.02, -0.93, -0.01, 0.04, -0.95, 0.01, 0.04, -0.95, 0.01, 0.02, -0.93); // btm 2nd btm back
            drawQuads(-0.01, 0.02, -0.93, -0.01, 0.04, -0.95, 0.01, 0.04, -0.93, 0.01, 0.02, -0.91); // btm 2nd left side
            drawQuads(0.01, 0.04, -0.95, 0.01, 0.02, -0.93, 0.01, 0.02, -0.91, 0.01, 0.04, -0.93);   // btm 2nd right side

            // glColor3f(1.0, 0.0, 1.0);
            drawQuads(-0.01, 0.04, -0.94, -0.01, 0.06, -0.97, 0.01, 0.06, -0.97, 0.01, 0.04, -0.94);   // btm 3rd btm front
            drawQuads(-0.01, 0.04, -0.95, -0.01, 0.06, -0.98, 0.01, 0.06, -0.98, 0.01, 0.04, -0.95);   // btm 3rd btm back
            drawQuads(-0.01, 0.04, -0.95, -0.01, 0.06, -0.98, -0.01, 0.06, -0.97, -0.01, 0.04, -0.94); // btm 3rd left side
            drawQuads(0.01, 0.06, -0.97, 0.01, 0.04, -0.94, 0.01, 0.04, -0.95, 0.01, 0.06, -0.98);     // btm 3rd left side
        }
        glPopMatrix();

        // bottom connect middle sphere to RECT box left //12
        glPushMatrix();
        {
            glTranslatef(-0.03, -0.05, 0.0);
            // glColor3f(0.0, 1.0, 1.0);
            drawQuads(-0.01, 0.0, -0.9, -0.01, 0.02, -0.91, 0.01, 0.02, -0.91, 0.01, 0.0, -0.9);    // btm 1st btm front
            drawQuads(-0.01, 0.0, -0.92, -0.01, 0.02, -0.93, 0.01, 0.02, -0.93, 0.01, 0.0, -0.92);  // btm 1st btm back
            drawQuads(-0.01, 0.0, -0.92, -0.01, 0.02, -0.93, -0.01, 0.02, -0.91, -0.01, 0.0, -0.9); // btm 1st btm left side
            drawQuads(0.01, 0.02, -0.93, 0.01, 0.0, -0.92, 0.01, 0.0, -0.9, 0.01, 0.02, -0.91);     // btm 1st btm right side
            // glColor3f(0.0, 0.0, 1.0);
            drawQuads(-0.01, 0.02, -0.91, -0.01, 0.04, -0.93, 0.01, 0.04, -0.93, 0.01, 0.02, -0.91); // btm 2nd btm front
            drawQuads(-0.01, 0.02, -0.93, -0.01, 0.04, -0.95, 0.01, 0.04, -0.95, 0.01, 0.02, -0.93); // btm 2nd btm back
            drawQuads(-0.01, 0.02, -0.93, -0.01, 0.04, -0.95, 0.01, 0.04, -0.93, 0.01, 0.02, -0.91); // btm 2nd left side
            drawQuads(0.01, 0.04, -0.95, 0.01, 0.02, -0.93, 0.01, 0.02, -0.91, 0.01, 0.04, -0.93);   // btm 2nd right side

            // glColor3f(1.0, 0.0, 1.0);
            drawQuads(-0.01, 0.04, -0.94, -0.01, 0.06, -0.97, 0.01, 0.06, -0.97, 0.01, 0.04, -0.94);   // btm 3rd btm front
            drawQuads(-0.01, 0.04, -0.95, -0.01, 0.06, -0.98, 0.01, 0.06, -0.98, 0.01, 0.04, -0.95);   // btm 3rd btm back
            drawQuads(-0.01, 0.04, -0.95, -0.01, 0.06, -0.98, -0.01, 0.06, -0.97, -0.01, 0.04, -0.94); // btm 3rd left side
            drawQuads(0.01, 0.06, -0.97, 0.01, 0.04, -0.94, 0.01, 0.04, -0.95, 0.01, 0.06, -0.98);     // btm 3rd left side
        }
        glPopMatrix();

        // bottom after sphere triangle right (Using cube to draw)
        glPushMatrix();
        {
            // glColor3f(0.0, 1.0, 0.0);
            glTranslatef(0.035, -0.065, -0.85);
            drawCube(0.02, 0.06, 0.07); // 6
        }
        glPopMatrix();

        // bottom after sphere triangle left (Using cube to draw)
        glPushMatrix();
        {
            // glColor3f(0.0, 1.0, 0.0);
            glTranslatef(-0.035, -0.065, -0.85);
            drawCube(0.02, 0.06, 0.07); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("darkGrey.bmp");
        }
        else
        {
            texture = loadTexture("middleSphere.bmp");
        }

        // bottom after triangle //below sphere //8
        glPushMatrix();
        {
            glTranslatef(0.0, -0.07, -0.83);
            drawQuads(-0.045, 0.0, -0.045, -0.045, 0.0, 0.01, 0.045, 0.0, 0.01, 0.045, 0.0, -0.045);
            // glColor3f(0.0, 0.0, 1.0);
            drawQuads(-0.045, -0.045, -0.08, -0.045, 0.0, -0.045, 0.045, 0.0, -0.045, 0.045, -0.045, -0.08);
            // glColor3f(1.0, 0.0, 1.0);
            drawQuads(-0.045, -0.045, -0.08, 0.045, -0.045, -0.08, 0.045, -0.09, -0.08, -0.045, -0.09, -0.08);
            // glColor3f(1.0, 1.0, 0.0);
            drawQuads(-0.045, -0.09, -0.08, 0.045, -0.09, -0.08, 0.045, -0.135, -0.04, -0.045, -0.135, -0.04);
            // glColor3f(0.0, 1.0, 1.0);
            drawQuads(-0.045, -0.135, -0.04, 0.045, -0.135, -0.04, 0.045, -0.135, 0.01, -0.045, -0.135, 0.01);
            // glColor3f(1.0, 0.0, 0.0);
            drawQuads(0.045, -0.135, 0.01, -0.045, -0.135, 0.01, -0.045, -0.09, 0.04, 0.045, -0.09, 0.04);
            // glColor3f(1.0, 1.0, 1.0);
            drawQuads(0.045, -0.09, 0.04, -0.045, -0.09, 0.04, -0.045, -0.045, 0.04, 0.045, -0.045, 0.04);
            // glColor3f(0.0, 1.0, 1.0);
            drawQuads(0.045, -0.045, 0.04, -0.045, -0.045, 0.04, -0.045, 0.0, 0.01, 0.045, 0.0, 0.01);
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // bottom after triangle //below sphere left
        glPushMatrix();
        {
            glTranslatef(0.0, -0.07, -0.83);
            glBegin(GL_POLYGON); // 1
            glVertex3f(-0.045, 0.0, 0.01);
            glVertex3f(-0.045, 0.0, -0.045);
            glVertex3f(-0.045, -0.045, -0.08);
            glVertex3f(-0.045, -0.09, -0.08);
            glVertex3f(-0.045, -0.135, -0.04);
            glVertex3f(-0.045, -0.135, 0.01);
            glVertex3f(-0.045, -0.09, 0.04);
            glVertex3f(-0.045, -0.045, 0.04);
            glEnd();
        }
        glPopMatrix();

        // bottom after triangle //below sphere right
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.091, -0.07, -0.83);
            glBegin(GL_POLYGON); // 1
            glVertex3f(-0.045, 0.0, 0.01);
            glVertex3f(-0.045, 0.0, -0.045);
            glVertex3f(-0.045, -0.045, -0.08);
            glVertex3f(-0.045, -0.09, -0.08);
            glVertex3f(-0.045, -0.135, -0.04);
            glVertex3f(-0.045, -0.135, 0.01);
            glVertex3f(-0.045, -0.09, 0.04);
            glVertex3f(-0.045, -0.045, 0.04);
            glEnd();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("legMuscle.bmp");
        }
        // RIGHT LEG MUSCLE
        // right leg muscle //like cone
        glPushMatrix();
        {
            glTranslatef(0.045, -0.14, -0.85);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.051, 0.071, 0.076, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // right leg muscle cover circle small
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.045, -0.14, -0.85);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.051); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // right leg muscle cover circle large
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.12, -0.14, -0.85);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.071); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        // ROTATE RIGHT LEG FUNCTION
        // right LEG function
        glPushMatrix();
        {
            glTranslatef(0.0, -0.15, -0.85);
            if (moveForward || crouch)
            {
                glRotatef(-rLeg, 1, 0, 0);
            }
            else if (moveBackward || jump || kneel)
            {
                glRotatef(rLeg, 1, 0, 0);
            }
            else
                glRotatef(-rLeg, 1, 0, 0);
            glTranslatef(0.0, 0.15, 0.85);
            drawRightLeg();
        }
        glPopMatrix();

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("legMuscle.bmp");
        }

        // LEFT LEG MUSCLE
        // left leg muscle //like cone
        // glColor3f(0.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.045, -0.14, -0.85);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                drawCylinder(0.051, 0.071, 0.076, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // left leg muscle cover circle small
        glPushMatrix();
        {
            glTranslatef(-0.045, -0.14, -0.85);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                drawCircle(30, 0.051); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // left leg muscle cover circle large
        // glColor3f(1.0, 0.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.12, -0.14, -0.85);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                drawCircle(30, 0.071); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        // ROTATE LEFT LEG FUNCTION
        // left LEG Function
        glPushMatrix();
        {
            glTranslatef(0.0, -0.15, -0.85);

            if (moveForward)
            {
                glRotatef(rLeg, 1, 0, 0);
            }
            else if (moveBackward || crouch)
            {
                glRotatef(-rLeg, 1, 0, 0);
            }
            else
                glRotatef(-rLeg, 1, 0, 0);
            glTranslatef(0.0, 0.15, 0.85);
            drawLeftLeg();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

// 60
void drawRightLeg()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // right leg
    // upper cylinder leg
    // glColor3f(1.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.12, -0.14, -0.85);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.09, 0.09, 0.06, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("legMuscle.bmp");
    // upper cylinder leg cover //inside
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.12, -0.14, -0.85);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.09); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // upper cylinder leg cover //outside
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.181, -0.14, -0.85);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.09); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueDetails.bmp");
    }
    else
    {
        texture = loadTexture("legDetails.bmp");
    }
    // details
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.15, -0.15, -0.76);
        glPushMatrix();
        {
            glRotatef(350, 1.0, 0.0, 0.0);
            drawCube(0.05, 0.09, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.15, -0.15, -0.75);
        glPushMatrix();
        {
            glRotatef(350, 1.0, 0.0, 0.0);
            drawCube(0.03, 0.07, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // below cylinder leg (rectangular) //right
    glPushMatrix();
    {
        glTranslatef(0.15, -0.22, -0.81);
        glPushMatrix();
        {
            glRotatef(350, 1.0, 0.0, 0.0);
            // glColor3f(1.0, 0.0, 0.0);
            drawCube(0.06, 0.2, 0.12); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // curve leg //right //16
    glPushMatrix();
    {
        glTranslatef(-0.039, -0.02, -0.005);
        // glColor3f(0.0, 1.0, 0.0);
        drawQuads(0.16, -0.28, -0.725, 0.22, -0.28, -0.725, 0.19, -0.36, -0.73, 0.13, -0.36, -0.73); // front
        drawQuads(0.16, -0.28, -0.84, 0.22, -0.28, -0.84, 0.19, -0.36, -0.835, 0.13, -0.36, -0.835); // back
        drawQuads(0.16, -0.28, -0.725, 0.16, -0.28, -0.84, 0.13, -0.36, -0.835, 0.13, -0.36, -0.73); // left side
        drawQuads(0.22, -0.28, -0.725, 0.22, -0.28, -0.84, 0.19, -0.36, -0.835, 0.19, -0.36, -0.73); // right side

        // glColor3f(0.0, 0.0, 1.0);
        drawQuads(0.13, -0.36, -0.73, 0.19, -0.36, -0.73, 0.17, -0.42, -0.733, 0.11, -0.42, -0.733);   // front
        drawQuads(0.13, -0.36, -0.835, 0.19, -0.36, -0.835, 0.17, -0.42, -0.834, 0.11, -0.42, -0.834); // back
        drawQuads(0.13, -0.36, -0.73, 0.13, -0.36, -0.835, 0.11, -0.42, -0.834, 0.11, -0.42, -0.733);  // left side
        drawQuads(0.19, -0.36, -0.73, 0.19, -0.36, -0.835, 0.17, -0.42, -0.834, 0.17, -0.42, -0.733);  // right side

        // glColor3f(0.0, 1.0, 1.0);
        drawQuads(0.11, -0.42, -0.733, 0.17, -0.42, -0.733, 0.16, -0.46, -0.738, 0.10, -0.46, -0.738); // front
        drawQuads(0.11, -0.42, -0.833, 0.17, -0.42, -0.833, 0.16, -0.46, -0.828, 0.10, -0.46, -0.828); // back
        drawQuads(0.11, -0.42, -0.733, 0.11, -0.42, -0.833, 0.10, -0.46, -0.828, 0.10, -0.46, -0.733); // left side
        drawQuads(0.17, -0.42, -0.733, 0.17, -0.42, -0.833, 0.16, -0.46, -0.828, 0.16, -0.46, -0.738); // right side

        // glColor3f(1.0, 0.0, 1.0);
        drawQuads(0.16, -0.46, -0.735, 0.10, -0.46, -0.735, 0.10, -0.49, -0.738, 0.16, -0.49, -0.738); // front
        drawQuads(0.16, -0.46, -0.828, 0.10, -0.46, -0.828, 0.10, -0.49, -0.825, 0.16, -0.49, -0.825); // back
        drawQuads(0.16, -0.46, -0.735, 0.16, -0.46, -0.828, 0.16, -0.49, -0.825, 0.16, -0.49, -0.738); // left side
        drawQuads(0.10, -0.46, -0.735, 0.10, -0.46, -0.828, 0.10, -0.49, -0.825, 0.10, -0.49, -0.738); // right side
        glDeleteTextures(1, &texture);

        texture = loadTexture("red.bmp");
        // joint right leg
        glPushMatrix();
        {
            glTranslatef(0.1, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                glColor3f(0.83, 0.83, 0.83);
                drawCylinder(0.042, 0.042, 0.06, 30, 30, texture); // 1
            }
            glPopMatrix(); // pop rotate
        }
        glPopMatrix(); // pop translate
        glDeleteTextures(1, &texture);

        glColor3f(0.96, 0.93, 0.89);
        texture = loadTexture("jointLegCover.bmp");
        glPushMatrix();
        {
            glTranslatef(0.1, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.0435); // cover joint left //1
            }
            glPopMatrix(); // pop rotate
        }
        glPopMatrix(); // pop translate

        glPushMatrix();
        {
            glTranslatef(0.16, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                // glColor3f(1.0, 0.0, 1.0);
                drawCircle(30, 0.0435); // cover joint right //1
            }
            glPopMatrix(); // pop rotate
        }
        glPopMatrix(); // pop translate
        glDeleteTextures(1, &texture);

        texture = loadTexture("legMuscle.bmp");
        // details //4
        // connect joint with plat
        // glColor3f(1.0, 0.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.045, -0.04, 0.0);
            drawQuads(0.16, -0.46, -0.71, 0.19, -0.46, -0.71, 0.19, -0.50, -0.75, 0.16, -0.50, -0.75); // top
            drawQuads(0.16, -0.48, -0.71, 0.19, -0.48, -0.71, 0.19, -0.52, -0.75, 0.16, -0.52, -0.75); // btm
            drawQuads(0.19, -0.46, -0.71, 0.19, -0.50, -0.75, 0.19, -0.52, -0.75, 0.19, -0.48, -0.71); // right
            drawQuads(0.16, -0.46, -0.71, 0.16, -0.50, -0.75, 0.16, -0.52, -0.75, 0.16, -0.48, -0.71); // left
        }
        glPopMatrix();

        // front joint big
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.13, -0.52, -0.71);
            glPushMatrix();
            {
                glRotatef(10, 1.0, 0.0, 0.0);
                drawCube(0.07, 0.09, 0.015); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueDetails.bmp");
        }
        else
        {
            texture = loadTexture("legDetails.bmp");
        }
        // front joint small
        // glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.13, -0.52, -0.70);
            glPushMatrix();
            {
                glRotatef(10, 1.0, 0.0, 0.0);
                drawCube(0.05, 0.07, 0.015); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // joint side right
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.155, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.044, 0.03, 0.02, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("jointLegCover.bmp");
        // cover joint side right
        // glColor3f(1.0, 0.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.175, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.03); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // joint side left
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.105, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                drawCylinder(0.04, 0.03, 0.02, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("jointLegCover.bmp");
        // cover joint side left
        // glColor3f(0.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.086, -0.52, -0.77);
            glPushMatrix();
            {
                glRotatef(270, 0.0, 1.0, 0.0);
                drawCircle(30, 0.03); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix(); // pop translate
    glDeleteTextures(1, &texture);

    // ROTATE RIGHT BOTTOM LEG
    glPushMatrix();
    {
        glTranslatef(0, -0.55, -0.75);
        if (!kneel)
        {
            glRotatef(rLowerLeg, 1, 0, 0);
        }
        glTranslatef(0, 0.55, 0.75);
        drawBottomRightLeg();
    }
    glPopMatrix();
}

// 172
void drawBottomRightLeg()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // glPushMatrix();{
    // glTranslatef(-1.0, 0.0, 0.0);

    // glColor3f(0.0, 0.0, 1.0); //13
    drawQuads(0.062, -0.56, -0.738, 0.12, -0.56, -0.738, 0.12, -0.63, -0.765, 0.062, -0.63, -0.765);  // front
    drawQuads(0.062, -0.58, -0.84, 0.12, -0.58, -0.84, 0.12, -0.65, -0.845, 0.062, -0.65, -0.845);    // back
    drawQuads(0.062, -0.56, -0.738, 0.062, -0.58, -0.84, 0.062, -0.65, -0.845, 0.062, -0.63, -0.765); // left side
    drawQuads(0.12, -0.56, -0.738, 0.12, -0.58, -0.84, 0.12, -0.65, -0.845, 0.12, -0.63, -0.765);     // right side
    drawQuads(0.062, -0.56, -0.738, 0.12, -0.56, -0.738, 0.12, -0.56, -0.84, 0.062, -0.56, -0.84);    // top //cant see

    // glColor3f(1.0, 0.0, 1.0);//pink
    drawQuads(0.062, -0.63, -0.765, 0.12, -0.63, -0.765, 0.12, -0.725, -0.78, 0.062, -0.725, -0.78);  // front
    drawQuads(0.062, -0.65, -0.845, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.062, -0.71, -0.85);    // back
    drawQuads(0.062, -0.63, -0.765, 0.062, -0.65, -0.845, 0.062, -0.71, -0.85, 0.062, -0.725, -0.78); // left side
    drawQuads(0.12, -0.63, -0.765, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.12, -0.725, -0.78);     // right side

    // glColor3f(0.0, 1.0, 1.0);//clay
    drawQuads(0.062, -0.63, -0.765, 0.12, -0.63, -0.765, 0.12, -0.725, -0.78, 0.062, -0.725, -0.78);  // front
    drawQuads(0.062, -0.65, -0.845, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.062, -0.71, -0.85);    // back
    drawQuads(0.062, -0.63, -0.765, 0.062, -0.65, -0.845, 0.062, -0.71, -0.85, 0.062, -0.725, -0.78); // left side
    drawQuads(0.12, -0.63, -0.765, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.12, -0.725, -0.78);     // right side

    // glColor3f(0.0, 1.0, 1.0); //1
    drawQuads(0.062, -0.725, -0.78, 0.12, -0.725, -0.78, 0.12, -0.76, -0.785, 0.062, -0.76, -0.785); // front
    glBegin(GL_TRIANGLES);                                                                           // 1
    glVertex3f(0.062, -0.725, -0.78);
    glVertex3f(0.062, -0.71, -0.85);
    glVertex3f(0.062, -0.76, -0.785);
    glEnd();
    glBegin(GL_TRIANGLES); // 1
    glVertex3f(0.12, -0.725, -0.78);
    glVertex3f(0.12, -0.71, -0.85);
    glVertex3f(0.12, -0.76, -0.785);
    glEnd();                                                                                       // 1
    drawQuads(0.062, -0.76, -0.785, 0.12, -0.76, -0.785, 0.12, -0.71, -0.85, 0.062, -0.71, -0.85); // bottom

    // 1st front rect //left
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.77, -0.79);
        glPushMatrix();
        {
            glRotatef(10, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.03, 0.01); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // 2nd front rect //left
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.79, -0.79);
        drawCube(0.01, 0.02, 0.01); // 6
    }
    glPopMatrix();

    // 3rd front rect //left
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.81, -0.79);
        drawCube(0.01, 0.03, 0.01); // 6
    }
    glPopMatrix();

    // 1st back rect //left
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.73, -0.84);
        glPushMatrix();
        {
            glRotatef(5, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.06, 0.01); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // connect front to back rect //left side
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.778, -0.82);
        glPushMatrix();
        {
            glRotatef(30, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.01, 0.065); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // 2nd back rect //left
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.79, -0.84);
        glPushMatrix();
        {
            glRotatef(-5, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.06, 0.01); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // 1st front rect //right
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.77, -0.79);
        glPushMatrix();
        {
            glRotatef(10, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.03, 0.01); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // 2nd front rect //right
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.79, -0.79);
        drawCube(0.01, 0.02, 0.01); // 6
    }
    glPopMatrix();

    // 3rd front rect //right
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.81, -0.79);
        drawCube(0.01, 0.03, 0.01); // 6
    }
    glPopMatrix();

    // 1st back rect //left
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.73, -0.84);
        glPushMatrix();
        {
            glRotatef(5, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.06, 0.01); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // connect front to back rect //left side
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.778, -0.82);
        glPushMatrix();
        {
            glRotatef(30, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.01, 0.065); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // 2nd back rect //left
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.79, -0.84);
        glPushMatrix();
        {
            glRotatef(-5, 1.0, 0.0, 0.0);
            drawCube(0.01, 0.06, 0.01); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("shinySilver.bmp");
    // middle long cylinder //inside(between)
    glPushMatrix();
    {
        glTranslatef(0.092, -0.73, -0.88);
        glPushMatrix();
        {
            glRotatef(40, 1.0, 0.0, 0.0);
            drawCylinder(0.01, 0.01, 0.17, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    // behind middle long cylinder (Connect back to upper leg)
    glPushMatrix();
    {
        glTranslatef(0.092, -0.71, -0.90);
        glPushMatrix();
        {
            glRotatef(40, 1.0, 0.0, 0.0);
            drawCylinder(0.015, 0.015, 0.05, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // connect to upper leg
    // glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.09, -0.69, -0.85);
        glPushMatrix();
        {
            glRotatef(330, 1.0, 0.0, 0.0);
            drawCube(0.02, 0.013, 0.08); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    // bottom cylinder //front
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.84, -0.75);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.013, 0.013, 0.04, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // bottom cylinder //front// circle to cover cylinder //left
    // glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.84, -0.75);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.013); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // bottom cylinder //front// circle to cover cylinder //right
    // glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.11, -0.84, -0.75);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.013); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // right cover rect
    glPushMatrix();
    {
        glTranslatef(0.115, -0.81, -0.815);
        drawCube(0.01, 0.03, 0.053); // 6
    }
    glPopMatrix();

    // left cover rect
    glPushMatrix();
    {
        glTranslatef(0.0676, -0.81, -0.815);
        drawCube(0.01, 0.03, 0.053); // 6
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    // middle bottom cylinder
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.81, -0.81);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.01, 0.01, 0.04, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // right //after front cylinder
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.11, -0.86, -0.76);
        glPushMatrix();
        {
            glRotatef(30, 1.0, 0.0, 0.0);
            drawCube(0.003, 0.03, 0.025); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // left //after front cylinder
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.86, -0.76);
        glPushMatrix();
        {
            glRotatef(30, 1.0, 0.0, 0.0);
            drawCube(0.003, 0.03, 0.025); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // connect middle bottom cylinder to feet
    // glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.09, -0.85, -0.80);
        glPushMatrix();
        {
            glRotatef(340, 1.0, 0.0, 0.0);
            drawCube(0.02, 0.07, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // connect back angle to feet //first
    glPushMatrix();
    {
        glTranslatef(0.09, -0.81, -0.85);
        drawCube(0.02, 0.02, 0.03); // 6
    }
    glPopMatrix();

    // glColor3f(1.0, 1.0, 0.0);
    // connect back angle to feet //2nd
    glPushMatrix();
    {
        glTranslatef(0.09, -0.825, -0.87);
        glPushMatrix();
        {
            glRotatef(310, 1.0, 0.0, 0.0);
            drawCube(0.015, 0.015, 0.04); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // glColor3f(1.0, 0.0, 1.0);
    // connect back angle to feet //3nd
    glPushMatrix();
    {
        glTranslatef(0.09, -0.86, -0.87);
        glPushMatrix();
        {
            glRotatef(40, 1.0, 0.0, 0.0);
            drawCube(0.02, 0.02, 0.05); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // connect 2nd and 3rd cube //using cylinder
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.84, -0.89);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.01, 0.01, 0.045, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // connect 2nd and 3rd cube //cylinder cover //using circle cover left
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.84, -0.89);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.01); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // connect 2nd and 3rd cube //cylinder cover //using circle cover right
    // glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.84, -0.89);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.01); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    // feet sphere
    glColor3f(0.83, 0.83, 0.83);
    glPushMatrix();
    {
        glTranslatef(0.09, -0.88, -0.86);
        drawSphere(0.025, 30, 30, texture); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // feet sphere //cube
    glColor3f(0.96, 0.93, 0.89);
    glPushMatrix();
    {
        glTranslatef(0.09, -0.885, -0.83);
        drawCube(0.03, 0.015, 0.02); // 6
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    // feet sphere //cylinder
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.885, -0.81);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.01, 0.01, 0.04, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // feet sphere //cylinder cover// using circle //left
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.07, -0.885, -0.81);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.01); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // feet sphere //cylinder cover// using circle //right
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(0.115, -0.885, -0.81);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.01); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // feet sphere //cylinder
    // glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.09, -0.88, -0.81);
        drawCylinder(0.015, 0.016, 0.07, 30, 30, texture); // 1
    }
    glPopMatrix();

    // feet sphere //cylinder cover //back
    // glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.09, -0.88, -0.81);
        drawCircle(30, 0.015); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueJoint.bmp");
    }
    else
    {
        texture = loadTexture("darkGrey.bmp");
    }
    // feet sphere //cylinder cover //front
    glPushMatrix();
    {
        glTranslatef(0.09, -0.88, -0.74);
        drawCircle(30, 0.016); // 1
    }
    glPopMatrix();

    // feet sphere //cylinder //front
    glPushMatrix();
    {
        glTranslatef(0.09, -0.88, -0.745);
        glPushMatrix();
        {
            glRotatef(10, 1.0, 0.0, 0.0);
            drawCylinder(0.016, 0.01, 0.04, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();

    // feet cube //base
    // glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(0.089, -0.90, -0.725);
        drawCube(0.038, 0.01, 0.036); // 6
    }
    glPopMatrix();

    glDeleteTextures(1, &texture);
    //}glPopMatrix();
}

// 60
void drawLeftLeg()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // left leg
    // upper cylinder leg
    glPushMatrix();
    {
        glTranslatef(-0.18, -0.14, -0.85);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.09, 0.09, 0.06, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueDetails.bmp");
    }
    else
    {
        texture = loadTexture("legDetails.bmp");
    }
    // details
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(-0.15, -0.15, -0.76);
        glPushMatrix();
        {
            glRotatef(350, 1.0, 0.0, 0.0);
            drawCube(0.05, 0.09, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();

    // glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(-0.15, -0.15, -0.75);
        glPushMatrix();
        {
            glRotatef(350, 1.0, 0.0, 0.0);
            drawCube(0.03, 0.07, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // upper cylinder leg cover outside
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(-0.181, -0.14, -0.85);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.09); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("legMuscle.bmp");
    // upper cylinder leg cover inside
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(-0.12, -0.14, -0.85);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.09); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    //(Need Translate again)
    glPushMatrix();
    {
        glTranslatef(-0.3, 0.0, 0.0);

        // below cylinder leg (rectangular) //left
        glPushMatrix();
        {
            glTranslatef(0.15, -0.22, -0.81);
            glPushMatrix();
            {
                glRotatef(350, 1.0, 0.0, 0.0);
                // glColor3f(1.0, 0.0, 0.0);
                drawCube(0.06, 0.2, 0.12); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // curve leg //left //16
        glPushMatrix();
        {
            glTranslatef(0.34, -0.02, -0.005);
            // glColor3f(0.0, 1.0, 0.0);
            drawQuads(-0.16, -0.28, -0.725, -0.22, -0.28, -0.725, -0.19, -0.36, -0.73, -0.13, -0.36, -0.73); // front
            drawQuads(-0.16, -0.28, -0.84, -0.22, -0.28, -0.84, -0.19, -0.36, -0.835, -0.13, -0.36, -0.835); // back
            drawQuads(-0.16, -0.28, -0.725, -0.16, -0.28, -0.84, -0.13, -0.36, -0.835, -0.13, -0.36, -0.73); // left side
            drawQuads(-0.22, -0.28, -0.725, -0.22, -0.28, -0.84, -0.19, -0.36, -0.835, -0.19, -0.36, -0.73); // right side

            // glColor3f(0.0, 0.0, 1.0);
            drawQuads(-0.13, -0.36, -0.73, -0.19, -0.36, -0.73, -0.17, -0.42, -0.733, -0.11, -0.42, -0.733);   // front
            drawQuads(-0.13, -0.36, -0.835, -0.19, -0.36, -0.835, -0.17, -0.42, -0.834, -0.11, -0.42, -0.834); // back
            drawQuads(-0.13, -0.36, -0.73, -0.13, -0.36, -0.835, -0.11, -0.42, -0.834, -0.11, -0.42, -0.733);  // left side
            drawQuads(-0.19, -0.36, -0.73, -0.19, -0.36, -0.835, -0.17, -0.42, -0.834, -0.17, -0.42, -0.733);  // right side

            // glColor3f(0.0, 1.0, 1.0);
            drawQuads(-0.11, -0.42, -0.733, -0.17, -0.42, -0.733, -0.16, -0.46, -0.738, -0.10, -0.46, -0.738); // front
            drawQuads(-0.11, -0.42, -0.833, -0.17, -0.42, -0.833, -0.16, -0.46, -0.828, -0.10, -0.46, -0.828); // back
            drawQuads(-0.11, -0.42, -0.733, -0.11, -0.42, -0.833, -0.10, -0.46, -0.828, -0.10, -0.46, -0.733); // left side
            drawQuads(-0.17, -0.42, -0.733, -0.17, -0.42, -0.833, -0.16, -0.46, -0.828, -0.16, -0.46, -0.738); // right side

            // glColor3f(1.0, 0.0, 1.0);
            drawQuads(-0.16, -0.46, -0.735, -0.10, -0.46, -0.735, -0.10, -0.49, -0.738, -0.16, -0.49, -0.738); // front
            drawQuads(-0.16, -0.46, -0.828, -0.10, -0.46, -0.828, -0.10, -0.49, -0.825, -0.16, -0.49, -0.825); // back
            drawQuads(-0.16, -0.46, -0.735, -0.16, -0.46, -0.828, -0.16, -0.49, -0.825, -0.16, -0.49, -0.738); // left side
            drawQuads(-0.10, -0.46, -0.735, -0.10, -0.46, -0.828, -0.10, -0.49, -0.825, -0.10, -0.49, -0.738); // right side
        }
        glPopMatrix(); // pop translate whole leg
        glDeleteTextures(1, &texture);

        texture = loadTexture("red.bmp");
        //(Need Translate again)
        glPushMatrix();
        {
            glTranslatef(0.08, -0.02, 0.0);

            // joint left leg
            glPushMatrix();
            {
                glTranslatef(0.1, -0.52, -0.77);
                glPushMatrix();
                {
                    glRotatef(90, 0.0, 1.0, 0.0);
                    glColor3f(0.83, 0.83, 0.83);
                    drawCylinder(0.042, 0.042, 0.06, 30, 30, texture); // 1
                }
                glPopMatrix(); // pop rotate
            }
            glPopMatrix(); // pop translate
            glDeleteTextures(1, &texture);

            glColor3f(0.96, 0.93, 0.89);
            texture = loadTexture("jointLegCover.bmp");
            glPushMatrix();
            {
                glTranslatef(0.1, -0.52, -0.77);
                glPushMatrix();
                {
                    glRotatef(90, 0.0, 1.0, 0.0);
                    drawCircle(30, 0.0435); // 1 //cover joint left
                }
                glPopMatrix(); // pop rotate
            }
            glPopMatrix(); // pop translate

            glPushMatrix();
            {
                glTranslatef(0.16, -0.52, -0.77);
                glPushMatrix();
                {
                    glRotatef(90, 0.0, 1.0, 0.0);
                    // glColor3f(0.0, 1.0, 1.0);
                    drawCircle(30, 0.0435); // 1 //cover joint right
                }
                glPopMatrix(); // pop rotate
            }
            glPopMatrix(); // pop translate
        }
        glPopMatrix(); // pop translate
    }
    glPopMatrix(); // pop translate //glTranslatef(0.34, -0.02, -0.005);
    glDeleteTextures(1, &texture);

    texture = loadTexture("legMuscle.bmp");
    // details //4
    // connect joint with plat
    // glColor3f(1.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(-0.27, -0.06, 0.0);
        drawQuads(0.16, -0.46, -0.71, 0.19, -0.46, -0.71, 0.19, -0.50, -0.75, 0.16, -0.50, -0.75); // top
        drawQuads(0.16, -0.48, -0.71, 0.19, -0.48, -0.71, 0.19, -0.52, -0.75, 0.16, -0.52, -0.75); // btm
        drawQuads(0.19, -0.46, -0.71, 0.19, -0.50, -0.75, 0.19, -0.52, -0.75, 0.19, -0.48, -0.71); // right
        drawQuads(0.16, -0.46, -0.71, 0.16, -0.50, -0.75, 0.16, -0.52, -0.75, 0.16, -0.48, -0.71); // left
    }
    glPopMatrix();

    // front joint big
    // glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(-0.09, -0.54, -0.71);
        glPushMatrix();
        {
            glRotatef(10, 1.0, 0.0, 0.0);
            drawCube(0.07, 0.09, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueDetails.bmp");
    }
    else
    {
        texture = loadTexture("legDetails.bmp");
    }
    // front joint small
    // glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(-0.09, -0.54, -0.70);
        glPushMatrix();
        {
            glRotatef(10, 1.0, 0.0, 0.0);
            drawCube(0.05, 0.07, 0.015); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // joint side right
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(-0.065, -0.54, -0.77);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCylinder(0.044, 0.03, 0.02, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("jointLegCover.bmp");
    // cover joint side right
    // glColor3f(1.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(-0.045, -0.54, -0.77);
        glPushMatrix();
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCircle(30, 0.03); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    // joint side left
    // glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    {
        glTranslatef(-0.115, -0.54, -0.77);
        glPushMatrix();
        {
            glRotatef(270, 0.0, 1.0, 0.0);
            drawCylinder(0.04, 0.03, 0.02, 30, 30, texture); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("jointLegCover.bmp");
    // cover joint side left
    // glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    {
        glTranslatef(-0.137, -0.54, -0.77);
        glPushMatrix();
        {
            glRotatef(270, 0.0, 1.0, 0.0);
            drawCircle(30, 0.03); // 1
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    // ROTATE LOWER LEFT LEG
    glPushMatrix();
    {
        glTranslatef(0, -0.55, -0.75);
        glRotatef(rLowerLeg, 1, 0, 0);
        glTranslatef(0, 0.55, 0.75);
        drawBottomLeftLeg();
    }
    glPopMatrix();
}

// 172
void drawBottomLeftLeg()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    glPushMatrix();
    { // 13
        glTranslatef(-0.182, 0.0, 0.0);

        drawQuads(0.062, -0.56, -0.738, 0.12, -0.56, -0.738, 0.12, -0.63, -0.765, 0.062, -0.63, -0.765);  // front
        drawQuads(0.062, -0.58, -0.84, 0.12, -0.58, -0.84, 0.12, -0.65, -0.845, 0.062, -0.65, -0.845);    // back
        drawQuads(0.062, -0.56, -0.738, 0.062, -0.58, -0.84, 0.062, -0.65, -0.845, 0.062, -0.63, -0.765); // left side
        drawQuads(0.12, -0.56, -0.738, 0.12, -0.58, -0.84, 0.12, -0.65, -0.845, 0.12, -0.63, -0.765);     // right side
        drawQuads(0.062, -0.56, -0.738, 0.12, -0.56, -0.738, 0.12, -0.56, -0.84, 0.062, -0.56, -0.84);    // top //cant see

        // glColor3f(1.0, 0.0, 1.0);//pink
        drawQuads(0.062, -0.63, -0.765, 0.12, -0.63, -0.765, 0.12, -0.725, -0.78, 0.062, -0.725, -0.78);  // front
        drawQuads(0.062, -0.65, -0.845, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.062, -0.71, -0.85);    // back
        drawQuads(0.062, -0.63, -0.765, 0.062, -0.65, -0.845, 0.062, -0.71, -0.85, 0.062, -0.725, -0.78); // left side
        drawQuads(0.12, -0.63, -0.765, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.12, -0.725, -0.78);     // right side

        // glColor3f(0.0, 1.0, 1.0);//clay
        drawQuads(0.062, -0.63, -0.765, 0.12, -0.63, -0.765, 0.12, -0.725, -0.78, 0.062, -0.725, -0.78);  // front
        drawQuads(0.062, -0.65, -0.845, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.062, -0.71, -0.85);    // back
        drawQuads(0.062, -0.63, -0.765, 0.062, -0.65, -0.845, 0.062, -0.71, -0.85, 0.062, -0.725, -0.78); // left side
        drawQuads(0.12, -0.63, -0.765, 0.12, -0.65, -0.845, 0.12, -0.71, -0.85, 0.12, -0.725, -0.78);     // right side //13

        // glColor3f(0.0, 1.0, 1.0); //1
        drawQuads(0.062, -0.725, -0.78, 0.12, -0.725, -0.78, 0.12, -0.76, -0.785, 0.062, -0.76, -0.785); // front
        glBegin(GL_TRIANGLES);                                                                           // 1
        glVertex3f(0.062, -0.725, -0.78);
        glVertex3f(0.062, -0.71, -0.85);
        glVertex3f(0.062, -0.76, -0.785);
        glEnd();
        glBegin(GL_TRIANGLES); // 1
        glVertex3f(0.12, -0.725, -0.78);
        glVertex3f(0.12, -0.71, -0.85);
        glVertex3f(0.12, -0.76, -0.785);
        glEnd();                                                                                       // 1
        drawQuads(0.062, -0.76, -0.785, 0.12, -0.76, -0.785, 0.12, -0.71, -0.85, 0.062, -0.71, -0.85); // bottom

        // 1st front rect //left
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.77, -0.79);
            glPushMatrix();
            {
                glRotatef(10, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.03, 0.01); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // 2nd front rect //left
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.79, -0.79);
            drawCube(0.01, 0.02, 0.01); // 6
        }
        glPopMatrix();

        // 3rd front rect //left
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.81, -0.79);
            drawCube(0.01, 0.03, 0.01); // 6
        }
        glPopMatrix();

        // 1st back rect //left
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.73, -0.84);
            glPushMatrix();
            {
                glRotatef(5, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.06, 0.01); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // connect front to back rect //left side
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.778, -0.82);
            glPushMatrix();
            {
                glRotatef(30, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.01, 0.065); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // 2nd back rect //left
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.79, -0.84);
            glPushMatrix();
            {
                glRotatef(-5, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.06, 0.01); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // 1st front rect //right
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.77, -0.79);
            glPushMatrix();
            {
                glRotatef(10, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.03, 0.01); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // 2nd front rect //right
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.79, -0.79);
            drawCube(0.01, 0.02, 0.01); // 6
        }
        glPopMatrix();

        // 3rd front rect //right
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.81, -0.79);
            drawCube(0.01, 0.03, 0.01); // 6
        }
        glPopMatrix();

        // 1st back rect //left
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.73, -0.84);
            glPushMatrix();
            {
                glRotatef(5, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.06, 0.01); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // connect front to back rect //left side
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.778, -0.82);
            glPushMatrix();
            {
                glRotatef(30, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.01, 0.065); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // 2nd back rect //left
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.79, -0.84);
            glPushMatrix();
            {
                glRotatef(-5, 1.0, 0.0, 0.0);
                drawCube(0.01, 0.06, 0.01); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("shinySilver.bmp");
        // middle long cylinder //inside(between)
        glPushMatrix();
        {
            glTranslatef(0.092, -0.73, -0.88);
            glPushMatrix();
            {
                glRotatef(40, 1.0, 0.0, 0.0);
                drawCylinder(0.01, 0.01, 0.17, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // behind middle long cylinder (Connect back to upper leg)
        glPushMatrix();
        {
            glTranslatef(0.092, -0.71, -0.90);
            glPushMatrix();
            {
                glRotatef(40, 1.0, 0.0, 0.0);
                drawCylinder(0.015, 0.015, 0.05, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // connect to upper leg
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.69, -0.85);
            glPushMatrix();
            {
                glRotatef(330, 1.0, 0.0, 0.0);
                drawCube(0.02, 0.013, 0.08); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // bottom cylinder //front
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.84, -0.75);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.013, 0.013, 0.04, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // bottom cylinder //front// circle to cover cylinder //left
        // glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.84, -0.75);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.013); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // bottom cylinder //front// circle to cover cylinder //right
        // glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.11, -0.84, -0.75);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.013); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // right cover rect
        glPushMatrix();
        {
            glTranslatef(0.115, -0.81, -0.815);
            drawCube(0.01, 0.03, 0.053); // 6
        }
        glPopMatrix();

        // left cover rect
        glPushMatrix();
        {
            glTranslatef(0.0676, -0.81, -0.815);
            drawCube(0.01, 0.03, 0.053); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // middle bottom cylinder
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.81, -0.81);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.01, 0.01, 0.04, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // right //after front cylinder
        // glColor3f(0.0, 0.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.11, -0.86, -0.76);
            glPushMatrix();
            {
                glRotatef(30, 1.0, 0.0, 0.0);
                drawCube(0.003, 0.03, 0.025); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // left //after front cylinder
        // glColor3f(0.0, 0.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.86, -0.76);
            glPushMatrix();
            {
                glRotatef(30, 1.0, 0.0, 0.0);
                drawCube(0.003, 0.03, 0.025); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // connect middle bottom cylinder to feet
        // glColor3f(0.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.85, -0.80);
            glPushMatrix();
            {
                glRotatef(340, 1.0, 0.0, 0.0);
                drawCube(0.02, 0.07, 0.015); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // connect back angle to feet //first
        glPushMatrix();
        {
            glTranslatef(0.09, -0.81, -0.85);
            drawCube(0.02, 0.02, 0.03); // 6
        }
        glPopMatrix();

        // glColor3f(1.0, 1.0, 0.0);
        // connect back angle to feet //2nd
        glPushMatrix();
        {
            glTranslatef(0.09, -0.825, -0.87);
            glPushMatrix();
            {
                glRotatef(310, 1.0, 0.0, 0.0);
                drawCube(0.015, 0.015, 0.04); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // glColor3f(1.0, 0.0, 1.0);
        // connect back angle to feet //3nd
        glPushMatrix();
        {
            glTranslatef(0.09, -0.86, -0.87);
            glPushMatrix();
            {
                glRotatef(40, 1.0, 0.0, 0.0);
                drawCube(0.02, 0.02, 0.05); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        // connect 2nd and 3rd cube //using cylinder
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.84, -0.89);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.01, 0.01, 0.045, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // connect 2nd and 3rd cube //cylinder cover //using circle cover left
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.84, -0.89);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.01); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // connect 2nd and 3rd cube //cylinder cover //using circle cover right
        // glColor3f(0.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.84, -0.89);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.01); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // feet sphere
        glColor3f(0.83, 0.83, 0.83);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.88, -0.86);
            drawSphere(0.025, 30, 30, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // feet sphere //cube
        // glColor3f(1.0, 1.0, 0.0);
        glColor3f(0.96, 0.93, 0.89);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.885, -0.83);
            drawCube(0.03, 0.015, 0.02); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // feet sphere //cylinder
        // glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.885, -0.81);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(0.01, 0.01, 0.04, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // feet sphere //cylinder cover// using circle //left
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.07, -0.885, -0.81);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.01); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // feet sphere //cylinder cover// using circle //right
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.115, -0.885, -0.81);
            glPushMatrix();
            {
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCircle(30, 0.01); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }
        // feet sphere //cylinder
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.88, -0.81);
            drawCylinder(0.015, 0.016, 0.07, 30, 30, texture); // 1
        }
        glPopMatrix();

        // feet sphere //cylinder cover //back
        // glColor3f(0.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.88, -0.81);
            drawCircle(30, 0.015); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueJoint.bmp");
        }
        else
        {
            texture = loadTexture("darkGrey.bmp");
        }
        // feet sphere //cylinder cover //front
        // glColor3f(1.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.88, -0.74);
            drawCircle(30, 0.016); // 1
        }
        glPopMatrix();

        // feet sphere //cylinder //front
        // glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.09, -0.88, -0.745);
            glPushMatrix();
            {
                glRotatef(10, 1.0, 0.0, 0.0);
                drawCylinder(0.016, 0.01, 0.04, 30, 30, texture); // 1
            }
            glPopMatrix();
        }
        glPopMatrix();

        // feet cube //base
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.089, -0.90, -0.725);
            drawCube(0.038, 0.01, 0.036); // 6
        }
        glPopMatrix();

        glDeleteTextures(1, &texture);
    }
    glPopMatrix();
}

// WEAPONS
// 104
void drawWeaponSword()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    texture = loadTexture("redWeapon.bmp");

    glPushMatrix();
    {
        glTranslatef(0.3, -0.08, -0.42);
        glRotatef(90, 0, 1, 0);
        glRotatef(70, 0, 0, 1);
        glScalef(0.7, 0.7, 0.7);

        // top weapon blade
        // glColor3f(0.0, 1.0, 0.0);
        // front
        glBegin(GL_POLYGON); // 1
        glTexCoord2f(0, 1);
        glVertex3f(-0.08, 0.4, 0.0);
        glTexCoord2f(1, 1);
        glVertex3f(0.0, 0.4, 0.0);
        glVertex3f(0.0, 0.65, 0.0);
        glTexCoord2f(1, 0);
        glVertex3f(-0.12, 0.55, 0.0);
        glVertex3f(-0.12, 0.46, 0.0);
        glEnd();

        // back
        glBegin(GL_POLYGON); // 1
        glTexCoord2f(0, 1);
        glVertex3f(-0.08, 0.4, -0.05);
        glTexCoord2f(1, 1);
        glVertex3f(0.0, 0.4, -0.05);
        glVertex3f(0.0, 0.65, -0.05);
        glTexCoord2f(1, 0);
        glVertex3f(-0.12, 0.55, -0.05);
        glVertex3f(-0.12, 0.46, -0.05);
        glEnd();

        // glColor3f(0.0, 1.0, 1.0);
        // left side //3
        drawQuads(0.0, 0.65, 0.0, 0.0, 0.65, -0.05, -0.12, 0.55, -0.05, -0.12, 0.55, 0.0);
        drawQuads(-0.12, 0.55, 0.0, -0.12, 0.55, -0.05, -0.12, 0.46, -0.05, -0.12, 0.46, 0.0);
        drawQuads(-0.12, 0.46, 0.0, -0.12, 0.46, -0.05, -0.08, 0.4, -0.05, -0.08, 0.4, 0.0);

        // right side
        // glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_POLYGON); // 1
        glTexCoord2f(0, 1);
        glVertex3f(0.0, 0.4, 0.0);
        glTexCoord2f(1, 1);
        glVertex3f(0.0, 0.4, -0.05);
        glTexCoord2f(1, 0);
        glVertex3f(0.0, 0.65, -0.05);
        glTexCoord2f(0, 0);
        glVertex3f(0.0, 0.65, 0.0);
        glEnd();
        glDeleteTextures(1, &texture);

        texture = loadTexture("silverWeapon.bmp");
        // decorate for blade //12
        // top
        drawQuads(-0.01, 0.60, 0.01, -0.01, 0.58, 0.01, -0.1, 0.51, 0.01, -0.1, 0.53, 0.01);     // front
        drawQuads(-0.01, 0.60, -0.06, -0.01, 0.58, -0.06, -0.1, 0.51, -0.06, -0.1, 0.53, -0.06); // back
        drawQuads(-0.01, 0.60, 0.01, -0.1, 0.53, 0.01, -0.1, 0.53, -0.06, -0.01, 0.60, -0.06);   // top
        drawQuads(-0.01, 0.58, 0.01, -0.1, 0.51, 0.01, -0.1, 0.51, -0.06, -0.01, 0.58, -0.06);   // btm
        drawQuads(-0.1, 0.51, 0.01, -0.1, 0.53, 0.01, -0.1, 0.53, -0.06, -0.1, 0.51, -0.06);     // left side
        drawQuads(-0.01, 0.60, 0.01, -0.01, 0.60, -0.06, -0.01, 0.58, -0.06, -0.01, 0.58, 0.01); // right side
        // btm
        // glColor3f(1.0, 1.0, 1.0);
        drawQuads(-0.1, 0.51, 0.01, -0.07, 0.54, 0.01, -0.07, 0.44, 0.01, -0.1, 0.47, 0.01);     // front
        drawQuads(-0.1, 0.51, -0.06, -0.07, 0.54, -0.06, -0.07, 0.44, -0.06, -0.1, 0.47, -0.06); // back
        drawQuads(-0.1, 0.51, 0.01, -0.1, 0.51, -0.06, -0.07, 0.54, -0.06, -0.07, 0.54, 0.01);   // top
        drawQuads(-0.1, 0.51, 0.01, -0.1, 0.51, -0.06, -0.1, 0.47, -0.06, -0.1, 0.47, 0.01);     // left side
        drawQuads(-0.07, 0.54, 0.01, -0.07, 0.54, -0.06, -0.07, 0.44, -0.06, -0.07, 0.44, 0.01); // right side
        drawQuads(-0.1, 0.47, 0.01, -0.1, 0.47, -0.06, -0.07, 0.44, -0.06, -0.07, 0.44, 0.01);   // btm
        // right
        glPushMatrix();
        {
            // glColor3f(0.0, 1.0, 1.0);
            glTranslatef(-0.04, 0.5, -0.06);
            drawCylinder(0.02, 0.02, 0.07, 30, 30, texture); // 1
        }
        glPopMatrix();
        // right (Front circle cover)
        glPushMatrix();
        {
            // glColor3f(0.0, 0.0, 1.0);
            glTranslatef(-0.04, 0.5, -0.06);
            drawCircle(30, 0.02); // 1
        }
        glPopMatrix();
        // right (Back circle cover)
        glPushMatrix();
        {
            // glColor3f(0.0, 0.0, 1.0);
            glTranslatef(-0.04, 0.5, 0.01);
            drawCircle(30, 0.02); // 1
        }
        glPopMatrix();
        // end for decoration
        glDeleteTextures(1, &texture);

        texture = loadTexture("redWeapon.bmp");
        // below blade (knife) //4
        // glColor3f(1.0, 1.0, 0.0);
        drawQuads(-0.08, 0.4, 0.0, 0.0, 0.4, 0.0, 0.0, -0.1, 0.0, -0.08, -0.1, 0.0);         // front
        drawQuads(-0.08, 0.4, -0.05, 0.0, 0.4, -0.05, 0.0, -0.1, -0.05, -0.08, -0.1, -0.05); // back
        drawQuads(-0.08, 0.4, 0.0, -0.08, 0.4, -0.05, -0.08, -0.1, -0.05, -0.08, -0.1, 0.0); // right
        drawQuads(0.0, 0.4, 0.0, 0.0, 0.4, -0.05, 0.0, -0.1, -0.05, 0.0, -0.1, 0.0);         // left
        glDeleteTextures(1, &texture);

        texture = loadTexture("silverWeapon.bmp");
        // decoration for knife
        // left
        // glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON); // front //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.09, -0.02, -0.01);
        glVertex3f(-0.11, -0.05, -0.01);
        glTexCoord2f(1, 1);
        glVertex3f(-0.09, -0.08, -0.01);
        glVertex3f(-0.065, -0.06, -0.01);
        glTexCoord2f(1, 0);
        glVertex3f(-0.065, 0.33, -0.01);
        glVertex3f(-0.09, 0.35, -0.01);
        glTexCoord2f(0, 0);
        glVertex3f(-0.11, 0.33, -0.01);
        glVertex3f(-0.09, 0.29, -0.01);
        glEnd();

        glBegin(GL_POLYGON); // back //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.09, -0.02, -0.04);
        glVertex3f(-0.11, -0.05, -0.04);
        glTexCoord2f(1, 1);
        glVertex3f(-0.09, -0.08, -0.04);
        glVertex3f(-0.065, -0.06, -0.04);
        glTexCoord2f(1, 0);
        glVertex3f(-0.065, 0.33, -0.04);
        glVertex3f(-0.09, 0.35, -0.04);
        glTexCoord2f(0, 0);
        glVertex3f(-0.11, 0.33, -0.04);
        glVertex3f(-0.09, 0.29, -0.04);
        glEnd();

        // cover //24
        // glColor3f(0.0, 0.0, 0.0);
        drawQuads(-0.09, 0.35, -0.01, -0.09, 0.35, -0.04, -0.11, 0.33, -0.04, -0.11, 0.33, -0.01);       // top inside
        drawQuads(-0.11, 0.33, -0.01, -0.11, 0.33, -0.04, -0.09, -0.02, -0.04, -0.09, -0.02, -0.01);     // middle outside
        drawQuads(-0.09, -0.02, -0.01, -0.09, -0.02, -0.04, -0.11, -0.05, -0.04, -0.11, -0.05, -0.01);   // below outside
        drawQuads(-0.11, -0.05, -0.01, -0.11, -0.05, -0.04, -0.09, -0.08, -0.04, -0.09, -0.08, -0.01);   // below below outside
        drawQuads(-0.09, -0.08, -0.01, -0.09, -0.08, -0.04, -0.065, -0.06, -0.04, -0.065, -0.06, -0.01); // btm inside
        glDeleteTextures(1, &texture);

        texture = loadTexture("blackWeapon.bmp");
        // right knife dec
        drawQuads(-0.03, -0.04, 0.015, -0.03, -0.07, 0.015, 0.03, -0.05, 0.015, 0.03, -0.03, 0.015);     // front
        drawQuads(-0.03, -0.04, -0.065, -0.03, -0.07, -0.065, 0.03, -0.05, -0.065, 0.03, -0.03, -0.065); // back
        drawQuads(-0.03, -0.04, 0.015, -0.03, -0.04, -0.065, -0.03, -0.07, -0.065, -0.03, -0.07, 0.015); // left side
        drawQuads(0.03, -0.03, 0.015, 0.03, -0.03, -0.065, 0.03, -0.05, -0.065, 0.03, -0.05, 0.015);     // right side
        drawQuads(-0.03, -0.07, 0.015, -0.03, -0.07, -0.065, 0.03, -0.05, -0.065, 0.03, -0.05, 0.015);   // btm

        // up //go top
        drawQuads(-0.01, -0.04, 0.015, 0.02, -0.04, 0.015, 0.02, 0.42, 0.015, -0.01, 0.42, 0.015);     // front
        drawQuads(-0.01, -0.04, -0.065, 0.02, -0.04, -0.065, 0.02, 0.42, -0.065, -0.01, 0.42, -0.065); // back
        drawQuads(-0.01, 0.42, 0.015, -0.01, 0.42, -0.065, 0.02, 0.42, -0.065, 0.02, 0.42, 0.015);     // top //not coming out
        drawQuads(0.02, -0.04, 0.015, 0.02, -0.04, -0.065, 0.02, 0.42, -0.065, 0.02, 0.42, 0.015);     // right
        drawQuads(-0.01, -0.04, 0.015, -0.01, -0.04, -0.065, -0.01, 0.42, -0.065, -0.01, 0.42, 0.015); // left
        glDeleteTextures(1, &texture);

        texture = loadTexture("silverWeapon.bmp");
        // up // go top //ontop this
        // glColor3f(1.0, 0.0, 0.0);
        drawQuads(-0.03, -0.065, -0.015, -0.03, -0.095, -0.015, 0.045, -0.075, -0.015, 0.045, -0.055, -0.015); // front
        drawQuads(-0.03, -0.065, -0.035, -0.03, -0.095, -0.035, 0.045, -0.075, -0.035, 0.045, -0.055, -0.035); // back
        drawQuads(0.03, -0.055, -0.015, 0.03, -0.075, -0.015, 0.045, -0.075, -0.035, 0.045, -0.055, -0.035);   // right
        drawQuads(-0.03, -0.095, -0.015, -0.03, -0.095, -0.035, 0.045, -0.075, -0.035, 0.045, -0.075, -0.015); // btm

        // go up
        drawQuads(0.033, -0.056, -0.015, 0.033, -0.056, -0.035, 0.033, 0.44, -0.035, 0.033, 0.44, -0.015); // left
        drawQuads(0.045, -0.056, -0.015, 0.045, -0.056, -0.035, 0.045, 0.45, -0.035, 0.045, 0.45, -0.015); // right
        drawQuads(0.033, 0.44, -0.015, 0.045, 0.45, -0.015, 0.045, 0.45, -0.035, 0.033, 0.44, -0.035);     // top
        drawQuads(0.033, -0.056, -0.015, 0.045, -0.056, -0.015, 0.045, 0.45, -0.015, 0.033, 0.44, -0.015); // front
        drawQuads(0.033, -0.056, -0.035, 0.045, -0.056, -0.035, 0.045, 0.45, -0.035, 0.033, 0.44, -0.035); // back
        // end of decoration for knife
        glDeleteTextures(1, &texture);

        texture = loadTexture("redWeapon.bmp");
        // below knife (Connect knife to holder)
        glPushMatrix();
        {
            // glColor3f(0.0, 1.0, 1.0);
            glTranslatef(-0.039, -0.11, -0.025);
            drawCube(0.07, 0.02, 0.04); // 6
        }
        glPopMatrix();
        glPushMatrix();
        {
            // glColor3f(1.0, 1.0, 0.0);
            glTranslatef(-0.039, -0.13, -0.025);
            drawCube(0.07, 0.02, 0.04); // 6
        }
        glPopMatrix();
        glPushMatrix();
        {
            // glColor3f(0.0, 1.0, 0.0);
            glTranslatef(-0.039, -0.15, -0.025);
            drawCube(0.07, 0.02, 0.04); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("blackWeapon.bmp");
        // decorate for (Connect knife to holder)
        glBegin(GL_POLYGON); // front //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.06, -0.12, 0.01);
        glVertex3f(-0.02, -0.12, 0.01);
        glTexCoord2f(1, 1);
        glVertex3f(-0.01, -0.14, 0.01);
        glVertex3f(-0.01, -0.16, 0.01);
        glTexCoord2f(1, 0);
        glVertex3f(-0.02, -0.18, 0.01);
        glVertex3f(-0.06, -0.18, 0.01);
        glTexCoord2f(0, 0);
        glVertex3f(-0.07, -0.16, 0.01);
        glVertex3f(-0.07, -0.14, 0.01);
        glEnd();

        glBegin(GL_POLYGON); // back //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.06, -0.12, -0.06);
        glVertex3f(-0.02, -0.12, -0.06);
        glTexCoord2f(1, 1);
        glVertex3f(-0.01, -0.14, -0.06);
        glVertex3f(-0.01, -0.16, -0.06);
        glTexCoord2f(1, 0);
        glVertex3f(-0.02, -0.18, -0.06);
        glVertex3f(-0.06, -0.18, -0.06);
        glTexCoord2f(0, 0);
        glVertex3f(-0.07, -0.16, -0.06);
        glVertex3f(-0.07, -0.14, -0.06);
        glEnd();

        // cover for decoration for (Connect knife to holder) //8
        drawQuads(-0.06, -0.12, 0.01, -0.06, -0.12, -0.06, -0.07, -0.14, -0.06, -0.07, -0.14, 0.01);
        drawQuads(-0.07, -0.14, 0.01, -0.07, -0.14, -0.06, -0.07, -0.16, -0.06, -0.07, -0.16, 0.01);
        drawQuads(-0.07, -0.16, 0.01, -0.07, -0.16, -0.06, -0.06, -0.18, -0.06, -0.06, -0.18, 0.01);
        drawQuads(-0.06, -0.18, 0.01, -0.06, -0.18, -0.06, -0.02, -0.18, -0.06, -0.02, -0.18, 0.01);
        drawQuads(-0.02, -0.18, 0.01, -0.02, -0.18, -0.06, -0.01, -0.16, -0.06, -0.01, -0.16, 0.01);
        drawQuads(-0.01, -0.16, 0.01, -0.01, -0.16, -0.06, -0.01, -0.14, -0.06, -0.01, -0.14, 0.01);
        drawQuads(-0.01, -0.14, 0.01, -0.01, -0.14, -0.06, -0.02, -0.12, -0.06, -0.02, -0.12, 0.01);
        drawQuads(-0.02, -0.12, 0.01, -0.02, -0.12, -0.06, -0.06, -0.12, -0.06, -0.06, -0.12, 0.01);
        glDeleteTextures(1, &texture);

        texture = loadTexture("silverWeapon.bmp");
        // decoration on holder
        // glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES); // front //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.08, -0.17, 0.02);
        glTexCoord2f(1, 1);
        glVertex3f(0.01, -0.15, 0.02);
        glTexCoord2f(0.5, 1);
        glVertex3f(-0.07, -0.24, 0.02);
        glEnd();
        glBegin(GL_TRIANGLES); // back //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.08, -0.17, -0.07);
        glTexCoord2f(1, 1);
        glVertex3f(0.01, -0.15, -0.07);
        glTexCoord2f(0.5, 1);
        glVertex3f(-0.07, -0.24, -0.07);
        glEnd();                                                                                     // 3
        drawQuads(-0.08, -0.17, 0.02, -0.07, -0.24, 0.02, -0.07, -0.24, -0.07, -0.08, -0.17, -0.07); // left
        drawQuads(0.01, -0.15, 0.02, -0.07, -0.24, 0.02, -0.07, -0.24, -0.07, 0.01, -0.15, -0.07);   // right
        drawQuads(-0.08, -0.17, 0.02, 0.01, -0.15, 0.02, 0.01, -0.15, -0.07, -0.08, -0.17, -0.07);   // top

        // glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES); // front //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.04, -0.17, -0.01);
        glTexCoord2f(1, 1);
        glVertex3f(0.0, -0.15, -0.01);
        glTexCoord2f(0.5, 1);
        glVertex3f(0.015, -0.24, -0.01);
        glEnd();
        glBegin(GL_TRIANGLES); // back //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.04, -0.17, -0.05);
        glTexCoord2f(1, 1);
        glVertex3f(0.0, -0.15, -0.05);
        glTexCoord2f(0.5, 1);
        glVertex3f(0.015, -0.24, -0.05);
        glEnd();                                                                                       // 2
        drawQuads(-0.04, -0.17, -0.01, 0.015, -0.24, -0.01, 0.015, -0.24, -0.05, -0.04, -0.17, -0.05); // left
        drawQuads(0.0, -0.15, -0.01, 0.015, -0.24, -0.01, 0.015, -0.24, -0.05, 0.0, -0.15, -0.05);     // right

        // glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES); // front //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.05, -0.12, 0.0);
        glTexCoord2f(1, 1);
        glVertex3f(-0.03, -0.14, 0.0);
        glTexCoord2f(0.5, 1);
        glVertex3f(-0.1, -0.24, 0.0);
        glEnd();
        glBegin(GL_TRIANGLES); // back //1
        glTexCoord2f(0, 1);
        glVertex3f(-0.05, -0.12, -0.04);
        glTexCoord2f(1, 1);
        glVertex3f(-0.03, -0.14, -0.04);
        glTexCoord2f(0.5, 1);
        glVertex3f(-0.1, -0.24, -0.04);
        glEnd();                                                                                 // 2
        drawQuads(-0.05, -0.12, 0.0, -0.1, -0.24, 0.0, -0.1, -0.24, -0.04, -0.05, -0.12, -0.04); // left
        drawQuads(-0.03, -0.14, 0.0, -0.1, -0.24, 0.0, -0.1, -0.24, -0.04, -0.03, -0.14, -0.04); // right
        glDeleteTextures(1, &texture);
        // end of decoration on holder

        texture = loadTexture("blackWeapon.bmp");
        // holder
        // glColor3f(0.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(-0.039, -0.3, -0.025);
            drawCube(0.02, 0.35, 0.02); // 6
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("silverWeapon.bmp");
        // below holder (Most Bottom) //6
        drawQuads(-0.06, -0.47, 0.0, -0.01, -0.45, 0.0, -0.01, -0.52, 0.0, -0.06, -0.55, 0.0);         // front
        drawQuads(-0.06, -0.47, -0.05, -0.01, -0.45, -0.05, -0.01, -0.52, -0.05, -0.06, -0.55, -0.05); // back
        drawQuads(-0.06, -0.47, 0.0, -0.06, -0.47, -0.05, -0.01, -0.45, -0.05, -0.01, -0.45, 0.0);     // top
        drawQuads(-0.06, -0.55, 0.0, -0.06, -0.55, -0.05, -0.01, -0.52, -0.05, -0.01, -0.52, 0.0);     // btm
        drawQuads(-0.06, -0.47, 0.0, -0.06, -0.47, -0.05, -0.06, -0.55, -0.05, -0.06, -0.55, 0.0);     // left side
        drawQuads(-0.01, -0.45, 0.0, -0.01, -0.45, -0.05, -0.01, -0.52, -0.05, -0.01, -0.52, 0.0);     // right side
        glDeleteTextures(1, &texture);
    }
    glPopMatrix();
}

// 68
void drawWeaponKnife()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    texture = loadTexture("goldWeapon.bmp");
    glPushMatrix();
    {
        glTranslatef(0.3, -0.12, -0.48);
        glRotatef(90, 0, 1, 0);
        glRotatef(70, 0, 0, 1);
        glScalef(0.8, 0.8, 0.8);

        // glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES); // front //1
        glTexCoord2f(0.5, 1);
        glVertex3f(0.0, 0.7, 0.0);
        glTexCoord2f(1, 0);
        glVertex3f(-0.08, 0.2, 0.0);
        glTexCoord2f(0, 0);
        glVertex3f(0.08, 0.2, 0.0);
        glEnd();
        glBegin(GL_TRIANGLES); // back //1
        glTexCoord2f(0.5, 1);
        glVertex3f(0.0, 0.7, -0.05);
        glTexCoord2f(1, 0);
        glVertex3f(-0.08, 0.2, -0.05);
        glTexCoord2f(0, 0);
        glVertex3f(0.08, 0.2, -0.05);
        glEnd();                                                                       // 10
        drawQuads(0.0, 0.7, 0.0, -0.08, 0.2, 0.0, -0.08, 0.2, -0.05, 0.0, 0.7, -0.05); // left
        drawQuads(0.0, 0.7, 0.0, 0.08, 0.2, 0.0, 0.08, 0.2, -0.05, 0.0, 0.7, -0.05);   // right

        drawQuads(-0.08, 0.2, 0.0, 0.08, 0.2, 0.0, 0.06, 0.1, 0.0, -0.06, 0.1, 0.0);         // front
        drawQuads(-0.08, 0.2, -0.05, 0.08, 0.2, -0.05, 0.06, 0.1, -0.05, -0.06, 0.1, -0.05); // back
        drawQuads(-0.08, 0.2, 0.0, -0.06, 0.1, 0.0, -0.06, 0.1, -0.05, -0.08, 0.2, -0.05);   // left
        drawQuads(0.08, 0.2, 0.0, 0.06, 0.1, 0.0, 0.06, 0.1, -0.05, 0.08, 0.2, -0.05);       // right

        drawQuads(-0.06, 0.1, 0.0, 0.06, 0.1, 0.0, 0.04, 0.03, 0.0, -0.04, 0.03, 0.0);         // front
        drawQuads(-0.06, 0.1, -0.05, 0.06, 0.1, -0.05, 0.04, 0.03, -0.05, -0.04, 0.03, -0.05); // back
        drawQuads(-0.06, 0.1, 0.0, -0.04, 0.03, 0.0, -0.04, 0.03, -0.05, -0.06, 0.1, -0.05);   // left
        drawQuads(0.06, 0.1, 0.0, 0.04, 0.03, 0.0, 0.04, 0.03, -0.05, 0.06, 0.1, -0.05);       // right

        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        { // front
            glTranslatef(0.0, 0.1, 0.005);
            drawCircle(30, 0.04); // 1
        }
        glPopMatrix();
        glPushMatrix();
        { // front
            glTranslatef(0.0, 0.1, 0.0);
            drawSphere(0.03, 30, 30, texture); // 1
        }
        glPopMatrix();
        glPushMatrix();
        { // back
            glTranslatef(0.0, 0.1, -0.055);
            drawCircle(30, 0.04); // 1
        }
        glPopMatrix();
        glPushMatrix();
        { // back
            glTranslatef(0.0, 0.1, -0.05);
            drawSphere(0.03, 30, 30, texture); // 1
        }
        glPopMatrix();

        glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        { // front
            glTranslatef(0.0, 0.1, 0.0);
            drawCylinder(0.04, 0.055, 0.01, 30, 30, texture); // 1
        }
        glPopMatrix();
        glPushMatrix();
        { // back
            glTranslatef(0.0, 0.1, -0.06);
            drawCylinder(0.055, 0.04, 0.01, 30, 30, texture); // 1
        }
        glPopMatrix();

        // right side decorate //12
        drawQuads(0.04, 0.13, 0.005, 0.08, 0.13, 0.005, 0.11, 0.08, 0.005, 0.05, 0.07, 0.005);     // front
        drawQuads(0.04, 0.13, -0.055, 0.08, 0.13, -0.055, 0.11, 0.08, -0.055, 0.05, 0.07, -0.055); // back
        drawQuads(0.04, 0.13, 0.005, 0.08, 0.13, 0.005, 0.08, 0.13, -0.055, 0.04, 0.13, -0.055);   // top
        drawQuads(0.05, 0.07, 0.005, 0.11, 0.08, 0.005, 0.11, 0.08, -0.055, 0.05, 0.07, -0.055);   // btm
        glColor3f(0.0, 0.0, 1.0);
        drawQuads(0.08, 0.13, 0.005, 0.11, 0.08, 0.005, 0.14, 0.12, 0.005, 0.12, 0.15, 0.005);     // front
        drawQuads(0.08, 0.13, -0.055, 0.11, 0.08, -0.055, 0.14, 0.12, -0.055, 0.12, 0.15, -0.055); // back
        drawQuads(0.08, 0.13, 0.005, 0.12, 0.15, 0.005, 0.12, 0.15, -0.055, 0.08, 0.13, -0.055);   // top
        drawQuads(0.11, 0.08, 0.005, 0.14, 0.12, 0.005, 0.14, 0.12, -0.055, 0.11, 0.08, -0.055);   // btm
        glColor3f(1.0, 0.0, 1.0);
        drawQuads(0.12, 0.15, 0.005, 0.14, 0.12, 0.005, 0.17, 0.12, 0.005, 0.15, 0.15, 0.005);     // front
        drawQuads(0.12, 0.15, -0.055, 0.14, 0.12, -0.055, 0.17, 0.12, -0.055, 0.15, 0.15, -0.055); // back
        drawQuads(0.12, 0.15, 0.005, 0.15, 0.15, 0.005, 0.15, 0.15, -0.055, 0.12, 0.15, -0.055);   // top
        drawQuads(0.14, 0.12, 0.005, 0.17, 0.12, 0.005, 0.17, 0.12, -0.055, 0.14, 0.12, -0.055);   // btm
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES); // front //1
        glTexCoord2f(0.5, 1);
        glVertex3f(0.15, 0.15, 0.005);
        glTexCoord2f(1, 0);
        glVertex3f(0.17, 0.12, 0.005);
        glTexCoord2f(0, 0);
        glVertex3f(0.18, 0.16, 0.005);
        glEnd();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES); // back //1
        glTexCoord2f(0.5, 1);
        glVertex3f(0.15, 0.15, -0.055);
        glTexCoord2f(1, 0);
        glVertex3f(0.17, 0.12, -0.055);
        glTexCoord2f(0, 0);
        glVertex3f(0.18, 0.16, -0.055);
        glEnd();                                                                                 // 2
        drawQuads(0.15, 0.15, 0.005, 0.18, 0.16, 0.005, 0.18, 0.16, -0.055, 0.15, 0.15, -0.055); // top
        drawQuads(0.15, 0.15, 0.005, 0.17, 0.12, 0.005, 0.17, 0.12, -0.055, 0.15, 0.15, -0.055); // btm
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES); // front //1
        glTexCoord2f(0.5, 1);
        glVertex3f(0.17, 0.12, 0.005);
        glTexCoord2f(1, 0);
        glVertex3f(0.18, 0.16, 0.005);
        glTexCoord2f(0, 0);
        glVertex3f(0.23, 0.20, 0.005);
        glEnd();
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES); // back //1
        glVertex3f(0.17, 0.12, -0.055);
        glTexCoord2f(1, 0);
        glVertex3f(0.18, 0.16, -0.055);
        glTexCoord2f(0, 0);
        glVertex3f(0.23, 0.20, -0.055);
        glEnd();                                                                                 // 2
        drawQuads(0.17, 0.12, 0.005, 0.23, 0.20, 0.005, 0.23, 0.20, -0.055, 0.17, 0.12, -0.055); // top
        drawQuads(0.23, 0.20, 0.005, 0.18, 0.16, 0.005, 0.18, 0.16, -0.055, 0.23, 0.20, -0.055); // btm
        // left side decorate //12
        glPushMatrix();
        {
            glTranslatef(0.0, 0.0, -0.05);
            glPushMatrix();
            {
                glRotatef(180, 0.0, 1.0, 0.0);
                drawQuads(0.04, 0.13, 0.005, 0.08, 0.13, 0.005, 0.11, 0.08, 0.005, 0.05, 0.07, 0.005);     // front
                drawQuads(0.04, 0.13, -0.055, 0.08, 0.13, -0.055, 0.11, 0.08, -0.055, 0.05, 0.07, -0.055); // back
                drawQuads(0.04, 0.13, 0.005, 0.08, 0.13, 0.005, 0.08, 0.13, -0.055, 0.04, 0.13, -0.055);   // top
                drawQuads(0.05, 0.07, 0.005, 0.11, 0.08, 0.005, 0.11, 0.08, -0.055, 0.05, 0.07, -0.055);   // btm
                glColor3f(0.0, 0.0, 1.0);
                drawQuads(0.08, 0.13, 0.005, 0.11, 0.08, 0.005, 0.14, 0.12, 0.005, 0.12, 0.15, 0.005);     // front
                drawQuads(0.08, 0.13, -0.055, 0.11, 0.08, -0.055, 0.14, 0.12, -0.055, 0.12, 0.15, -0.055); // back
                drawQuads(0.08, 0.13, 0.005, 0.12, 0.15, 0.005, 0.12, 0.15, -0.055, 0.08, 0.13, -0.055);   // top
                drawQuads(0.11, 0.08, 0.005, 0.14, 0.12, 0.005, 0.14, 0.12, -0.055, 0.11, 0.08, -0.055);   // btm
                glColor3f(1.0, 0.0, 1.0);
                drawQuads(0.12, 0.15, 0.005, 0.14, 0.12, 0.005, 0.17, 0.12, 0.005, 0.15, 0.15, 0.005);     // front
                drawQuads(0.12, 0.15, -0.055, 0.14, 0.12, -0.055, 0.17, 0.12, -0.055, 0.15, 0.15, -0.055); // back
                drawQuads(0.12, 0.15, 0.005, 0.15, 0.15, 0.005, 0.15, 0.15, -0.055, 0.12, 0.15, -0.055);   // top
                drawQuads(0.14, 0.12, 0.005, 0.17, 0.12, 0.005, 0.17, 0.12, -0.055, 0.14, 0.12, -0.055);   // btm
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_TRIANGLES); // front //1
                glTexCoord2f(0.5, 1);
                glVertex3f(0.15, 0.15, 0.005);
                glTexCoord2f(1, 0);
                glVertex3f(0.17, 0.12, 0.005);
                glTexCoord2f(0, 0);
                glVertex3f(0.18, 0.16, 0.005);
                glEnd();
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_TRIANGLES); // back //1
                glTexCoord2f(0.5, 1);
                glVertex3f(0.15, 0.15, -0.055);
                glTexCoord2f(1, 0);
                glVertex3f(0.17, 0.12, -0.055);
                glTexCoord2f(0, 0);
                glVertex3f(0.18, 0.16, -0.055);
                glEnd();                                                                                 // 2
                drawQuads(0.15, 0.15, 0.005, 0.18, 0.16, 0.005, 0.18, 0.16, -0.055, 0.15, 0.15, -0.055); // top
                drawQuads(0.15, 0.15, 0.005, 0.17, 0.12, 0.005, 0.17, 0.12, -0.055, 0.15, 0.15, -0.055); // btm
                glColor3f(0.0, 1.0, 1.0);
                glBegin(GL_TRIANGLES); // front //1
                glTexCoord2f(0.5, 1);
                glVertex3f(0.17, 0.12, 0.005);
                glTexCoord2f(1, 0);
                glVertex3f(0.18, 0.16, 0.005);
                glTexCoord2f(0, 0);
                glVertex3f(0.23, 0.20, 0.005);
                glEnd();
                glColor3f(0.0, 1.0, 1.0);
                glBegin(GL_TRIANGLES); // back //1
                glTexCoord2f(0.5, 1);
                glVertex3f(0.17, 0.12, -0.055);
                glTexCoord2f(1, 0);
                glVertex3f(0.18, 0.16, -0.055);
                glTexCoord2f(0, 0);
                glVertex3f(0.23, 0.20, -0.055);
                glEnd();                                                                                 // 2
                drawQuads(0.17, 0.12, 0.005, 0.23, 0.20, 0.005, 0.23, 0.20, -0.055, 0.17, 0.12, -0.055); // top
                drawQuads(0.23, 0.20, 0.005, 0.18, 0.16, 0.005, 0.18, 0.16, -0.055, 0.23, 0.20, -0.055); // btm
            }
            glPopMatrix();
        }
        glPopMatrix();

        // holder
        glPushMatrix();
        {
            glTranslatef(0.0, -0.15, -0.022);
            drawCube(0.05, 0.4, 0.03); // 6
        }
        glPopMatrix();

        // handle
        // glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        {
            glTranslatef(0.0, -0.34, -0.022);
            glPushMatrix();
            {
                glRotatef(10, 0.0, 0.0, 1.0);
                drawCube(0.08, 0.08, 0.06); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();

        glDeleteTextures(1, &texture);
    }
    glPopMatrix();
}

// 65
void drawWeaponLaser()
{
    GLuint texture;
    glColor3f(0.96, 0.93, 0.89);
    if (isChangeTexture)
    {
        texture = loadTexture("blueColor.bmp");
    }
    else
    {
        texture = loadTexture("orange.bmp");
    }
    glPushMatrix();
    {
        glTranslatef(0.16, -0.28, -0.23);
        glRotatef(70, 1, 0, 0);
        glPushMatrix();
        {
            // glColor3f(1, 0, 0);
            glTranslatef(-0.5, 0.5, -0.5);
            drawCylinder(0.04, 0.04, 0.2, 100, 100, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("legMuscle.bmp");
        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.5, 0.502, -0.51);
            drawCylinder(0.035, 0.035, 0.03, 100, 100, texture); // 1
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.5, 0.502, -0.32);
            drawCylinder(0.035, 0.035, 0.03, 100, 100, texture); // 1
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 0, 0);
            glTranslatef(-0.5, 0.5, -0.29);
            drawCylinder(0.04, 0.02, 0.03, 100, 100, texture); // 1
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 0, 0);
            glTranslatef(-0.5, 0.5, -0.54);
            drawCylinder(0.02, 0.04, 0.03, 100, 100, texture); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        texture = loadTexture("legMuscle.bmp");
        glPushMatrix();
        {
            // glColor3f(1, 1, 1);
            glTranslatef(-0.5, 0.5, -0.535);
            drawCircle(100, 0.022); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (weaponShoot)
        {
            texture = loadTexture("red.bmp");
        }
        else
        {
            texture = loadTexture("legMuscle.bmp");
        }
        glPushMatrix();
        {
            // glColor3f(1, 1, 1);
            glTranslatef(-0.5, 0.5, -0.26);
            drawCircle(100, 0.022); // 1
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
            if (weaponShoot)
            {
                texture = loadTexture("orange.bmp");
            }
        }
        else
        {
            texture = loadTexture("orange.bmp");
            if (weaponShoot)
            {
                texture = loadTexture("blueColor.bmp");
            }
        }
        // cuboid at front and back of the gun
        // front
        glPushMatrix();
        {
            glTranslatef(-0.5, 0.5, -0.0);
            glRotatef(rGun, 0, 0, 1);
            glTranslatef(0.5, -0.5, 0.0);

            glPushMatrix();
            {
                /*glColor3f(1, 1, 0);*/
                glTranslatef(-0.5, 0.527, -0.275);
                drawCube(0.03, 0.03, 0.02); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.532, 0.505, -0.275);
                glRotatef(90, 0, 0, 1);
                drawCube(0.03, 0.03, 0.02); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.5, 0.474, -0.275);
                // glRotatef(-45, 0, 0, 1);
                drawCube(0.03, 0.03, 0.02); // 6
            }
            glPopMatrix();

            glPushMatrix();
            {
                // glColor3f(1, 1, 0);
                glTranslatef(-0.468, 0.505, -0.275);
                glRotatef(-90, 0, 0, 1);
                drawCube(0.03, 0.03, 0.02); // 6
            }
            glPopMatrix();
        }
        glPopMatrix();
        glDeleteTextures(1, &texture);

        if (isChangeTexture)
        {
            texture = loadTexture("blueColor.bmp");
        }
        else
        {
            texture = loadTexture("orange.bmp");
        }

        // back
        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.5, 0.527, -0.52);
            drawCube(0.03, 0.03, 0.02); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.532, 0.505, -0.52);
            glRotatef(90, 0, 0, 1);
            drawCube(0.03, 0.03, 0.02); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.5, 0.474, -0.52);
            // glRotatef(-45, 0, 0, 1);
            drawCube(0.03, 0.03, 0.02); // 6
        }
        glPopMatrix();

        glPushMatrix();
        {
            // glColor3f(1, 1, 0);
            glTranslatef(-0.468, 0.505, -0.52);
            glRotatef(-90, 0, 0, 1);
            drawCube(0.03, 0.03, 0.02); // 6
        }
        glPopMatrix();
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    texture = loadTexture("legMuscle.bmp");
    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(-0.34, 0.27, 0.14);
        glRotatef(-30, 1, 0, 0);
        drawCylinder(0.02, 0.02, 0.05, 100, 100, texture); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-0.34, 0.29, 0.18);
        glRotatef(-30, 1, 0, 0);
        drawCircle(100, 0.02); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(0, 1, 1);
        glTranslatef(-0.32, 0.282, 0.17);
        glRotatef(-30, 1, 0, 0);
        drawCube(0.05, 0.09, 0.05); // 6
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 1, 0);
        glTranslatef(-0.32, 0.282, 0.125);
        glRotatef(90, 0, 1, 0);
        drawCylinder(0.02, 0.02, 0.05, 100, 100, texture); // 1
    }
    glPopMatrix();

    glPushMatrix();
    {
        // glColor3f(1, 0, 0);
        glTranslatef(-0.32, 0.282, 0.185);
        glRotatef(90, 0, 1, 0);
        drawCylinder(0.01, 0.01, 0.05, 100, 100, texture); // 1
    }
    glPopMatrix();
    glDeleteTextures(1, &texture);

    // BULLETS
    if (bulletsOut)
    {
        glPushMatrix();
        {
            glColor3f(1, 0, 0);
            glTranslatef(-0.34, 0.2, 0.13);
            glTranslatef(0, shootOut, 0);
            glRotatef(70, 1, 0, 0);
            drawSphere(0.03, 100, 100, texture); // 1
        }
        glPopMatrix();
    }
}

void skyBox(int types)
{
    GLuint texture;
    glScalef(50.0, 50.0, 50.0);

    if (types == 1)
    {
        texture = loadTexture("skyBack.bmp");
        drawQuads(-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0); // back
        glDeleteTextures(1, &texture);

        texture = loadTexture("skyLeft.bmp");
        drawQuads(-1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0); // left
        glDeleteTextures(1, &texture);

        texture = loadTexture("skyRight.bmp");
        drawQuads(1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0); // right
        glDeleteTextures(1, &texture);

        texture = loadTexture("skyFront.bmp");
        drawQuads(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0); // front
        glDeleteTextures(1, &texture);

        texture = loadTexture("skyTop.bmp");
        drawQuads(-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0); // top
        glDeleteTextures(1, &texture);

        texture = loadTexture("skyBtm.bmp");
        drawQuads(-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0); // btm
        glDeleteTextures(1, &texture);
    }

    if (types == 2)
    {
        texture = loadTexture("buildBack.bmp");
        drawQuads(-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0); // back
        glDeleteTextures(1, &texture);

        texture = loadTexture("buildLeft.bmp");
        drawQuads(-1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0); // left
        glDeleteTextures(1, &texture);

        texture = loadTexture("buildRight.bmp");
        drawQuads(1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0); // right
        glDeleteTextures(1, &texture);

        texture = loadTexture("buildFront.bmp");
        drawQuads(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0); // front
        glDeleteTextures(1, &texture);

        glPushMatrix();
        {
            glRotatef(180, 0.0, 1.0, 0.0);
            texture = loadTexture("buildSky.bmp");
            drawQuads(-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0); // top
            glDeleteTextures(1, &texture);
        }
        glPopMatrix();

        texture = loadTexture("buildBtm.bmp");
        drawQuads(-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0); // btm
        glDeleteTextures(1, &texture);
    }
}

void orthoBack()
{
    GLuint texture;
    glScalef(40.0, 40.0, 2.0);
    texture = loadTexture("skyFront.bmp");
    drawQuads(-1.0, 1.0, -2.0, 1.0, 1.0, -2.0, 1.0, -1.0, -2.0, -1.0, -1.0, -2.0); // front
    glDeleteTextures(1, &texture);
}

void projection()
{
    glMatrixMode(GL_PROJECTION); // refer to projection matrix
    glLoadIdentity();            // reset the projection matrix

    if (isOrtho)
    {
        glTranslatef(txP, tyP, 0.0); // Translate projection view
    }
    glRotatef(180, 0.0, 1.0, 0.0);
    if (isOrtho)
    {
        glOrtho(-2.0, 2.0, -2.0, 2.0, OrthoN, OrthoF); // ortho view -2.0, 2.0, -2.0, 2.0, OrthoN, OrthoF
    }
    else
    {
        gluPerspective(16, 1.0, -1.0, 1.0);              // aspect = 300/300
        glFrustum(-8.0, 8.0, -8.0, 8.0, perspN, perspF); // zfar = bottom+top+zNear
    }
}

void lighting()
{
    if (isOnLight)
    {
        glEnable(GL_LIGHTING);

        if (changeLightType)
        {
            glEnable(GL_LIGHT1);
            glDisable(GL_LIGHT0);
        }
        else
        {
            glEnable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
        }
    }
    else
    {
        glDisable(GL_LIGHTING);

        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }

    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif); // diffuse

    glLightfv(GL_LIGHT1, GL_AMBIENT, amb); // ambient

    glMaterialfv(GL_FRONT, GL_DIFFUSE, difM); // green color material
}

void display()
{
    glClearColor(0.16f, 0.16f, 0.16f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    lighting();
    GLfloat posD[] = {xLight, yLight, zLight, 0.0}; // w directional source
    glLightfv(GL_LIGHT0, GL_POSITION, posD);        // position of light

    glPushMatrix();
    {
        {
            if (isOrtho == true)
            {
                if (isOnLight)
                {
                    isOrthoBack = false;
                }
                else
                {
                    isOrthoBack = true;
                }
                glTranslatef(0, 0, 2);
                glRotatef(-xSpeed, 1, 0, 0);
                glRotatef(-ySpeed, 0, 1, 0);
                glTranslatef(0, 0, -2);
            }
            else
            {
                isOrthoBack = false;
                glRotatef(xSpeed, 1, 0, 0);
                glRotatef(ySpeed, 0, 1, 0);
            }
            projection();
            glMatrixMode(GL_MODELVIEW);
            if (isOrtho == false)
            {
                glScalef(3, 3, 3);
            }
            glTranslatef(0, 0.0, 2.0);
            glTranslatef(txP, tyP, tzP);
            glRotatef(180.0, 0.0, 1.0, 0.0);
            glPushMatrix();
            {
                {
                    glPushMatrix();
                    {
                        {
                            glTranslatef(0, moveBodyUpDown, 0);
                            glTranslatef(moveToX, moveToY, moveToZ);
                            glRotatef(rSpeed1, 0.0, 1.0, 0.0); // rotate whole robot

                            // Upper Body
                            glPushMatrix();
                            {
                                {
                                    if (backFlip)
                                    {
                                        glRotatef(-rWholeRobot, 1, 0, 0);
                                    }
                                    else
                                        glRotatef(rWholeRobot, 1, 0, 0);
                                    glTranslatef(0, rFly, 0);
                                    drawHead();    // include draw upperbody
                                    drawBtmButt(); // LOWER PART BODY
                                }
                            }
                            glPopMatrix();
                        }
                    }
                    glPopMatrix(); // pop ROTATE WHOLE ROBOT
                }
            }
            glPopMatrix();

            // SKY BOX Changes
            glPushMatrix();
            {
                {
                    glColor3f(1.0, 1.0, 1.0);
                    if (isChangeSkyBox)
                    {
                        skyBox(2);
                    }
                    else
                    {
                        skyBox(1);
                    }
                }
            }
            glPopMatrix();

            // Animations
            // WALKING
            if (moveForward || moveBackward)
            {
                if (moveCount < 2)
                {
                    rLeg += moveSpeed / 4;
                    rArmFrontBack += moveSpeed / 4;
                    if (isRotateKneeChanged)
                    {
                        rLowerLeg -= moveSpeed / 4;
                        rElbowFrontBack -= moveSpeed / 4;
                    }
                    else
                    {
                        rLowerLeg += moveSpeed / 4;
                        rElbowFrontBack += moveSpeed / 4;
                    }

                    if (rLeg == 0)
                    {
                        isRotateKneeChanged = !isRotateKneeChanged;
                    }

                    if (moveSpeed < 0 && rLeg == -45)
                    {
                        moveSpeed = fabs(moveSpeed);
                        moveCount++;
                    }
                    else if (moveSpeed > 0 && rLeg == 45)
                    {
                        moveSpeed = -fabs(moveSpeed);
                        moveCount++;
                    }
                }
                else if (moveCount == 2)
                {
                    rLeg += moveSpeed / 4;
                    rArmFrontBack += moveSpeed / 4;
                    if (isRotateKneeChanged)
                    {
                        rElbowFrontBack -= moveSpeed / 4;
                        rLowerLeg -= moveSpeed / 4;
                    }
                    else
                    {
                        rElbowFrontBack += moveSpeed / 4;
                        rLowerLeg += moveSpeed / 4;
                    }
                    if (rLeg == 0 && rLowerLeg == 0)
                    {
                        moveCount++;
                    }
                }
                else
                {
                    moveForward = false;
                    moveBackward = false;
                    moveSpeed = fabs(moveSpeed);
                    moveCount = 0;
                    isRotateKneeChanged = false;
                }
                if (moveForward)
                {
                    if (moveToX < 90)
                        moveToX += 0.03 * cos((double)((double)rSpeed1 - 90) / 180 * PI);
                    if (moveToZ < 90)
                        moveToZ += 0.03 * sin((double)((double)rSpeed1 + 90) / 180 * PI);
                    if (moveToX > 90)
                        moveToX -= 0.03 * cos((double)((double)rSpeed1 - 90) / 180 * PI);
                    if (moveToZ > 90)
                        moveToZ -= 0.03 * sin((double)((double)rSpeed1 + 90) / 180 * PI);
                }
                else
                {
                    if (moveToX < 90)
                        moveToX -= 0.03 * cos((double)((double)rSpeed1 - 90) / 180 * PI);
                    if (moveToZ < 90)
                        moveToZ -= 0.03 * sin((double)((double)rSpeed1 + 90) / 180 * PI);
                    if (moveToX > 90)
                        moveToX += 0.03 * cos((double)((double)rSpeed1 - 90) / 180 * PI);
                    if (moveToZ > 90)
                        moveToZ += 0.03 * sin((double)((double)rSpeed1 + 90) / 180 * PI);
                }
            }

            // JUMP
            if (jump)
            {
                rLeg += moveSpeed;
                rLowerLeg += moveSpeed;
                rArmFrontBack += moveSpeed;
                moveBodyUpDown += moveSpeed / 100;
                if (rLeg == 70)
                {
                    moveSpeed = -moveSpeed;
                }
                if (rLeg == 0)
                {
                    jump = false;
                    moveSpeed = fabs(moveSpeed);
                    moveBodyUpDown = 0;
                }
            }

            // BACKFLIP
            if (backFlip)
            {
                if ((rElbowFrontBack < 90 && moveSpeed2 > 0) || (rElbowFrontBack > 0 && moveSpeed2 < 0))
                    rElbowFrontBack += moveSpeed2;
                if ((rArmFrontBack < 30 && moveSpeed2 > 0) || (rArmFrontBack > 0 && moveSpeed2 < 0))
                    rArmFrontBack += moveSpeed2;
                if ((rLeg < 70 && moveSpeed2 > 0) || (rLeg > 0 && moveSpeed2 < 0))
                    rLeg += moveSpeed2;
                if ((rLowerLeg < 70 && moveSpeed2 > 0) || (rLowerLeg > 0 && moveSpeed2 < 0))
                    rLowerLeg += moveSpeed2;
                if ((moveBodyUpDown < 30 && moveSpeed2 > 0) || (moveBodyUpDown > 0))
                    moveBodyUpDown += moveSpeed2 / 5040;

                if (rElbowFrontBack == 90)
                {
                    rWholeRobot += moveSpeed2;
                    rFinger += moveSpeed2;
                    if (rWholeRobot == 360)
                    {
                        moveSpeed2 = -fabs(moveSpeed2);
                    }
                }
                if (rElbowFrontBack == 0)
                {
                    moveSpeed2 = fabs(moveSpeed2);
                    backFlip = false;
                    rWholeRobot = 0;
                    moveBodyUpDown = 0;
                    rFinger = 0;
                }
            }

            // WAVE HAND
            if (waveHand)
            {
                if ((rArmFrontBack < 140 && moveSpeed > 0) || (rArmFrontBack > 0 && moveSpeed < 0))
                    rArmFrontBack += moveSpeed;
                if ((rElbowFrontBack < 50 && moveSpeed > 0) || (rElbowFrontBack > 0 && moveSpeed < 0))
                    rElbowFrontBack += moveSpeed;
                if ((rElbowUpDown < 90 && moveSpeed > 0) || (rElbowUpDown > 0 && moveSpeed < 0))
                    rElbowUpDown += moveSpeed;

                if (waveCount < 10)
                {
                    if (rArmFrontBack == 140)
                    {
                        rArmUpDown += moveSpeed;
                        if (rArmUpDown == 30)
                        {
                            waveCount++;
                            rArmUpDown -= 30;
                            if (waveCount == 9)
                            {
                                rArmUpDown = 0;
                                if (rArmUpDown == 0)
                                {
                                    moveSpeed = -fabs(moveSpeed);
                                }
                            }
                        }
                    }
                }
                if (rArmFrontBack == 0)
                {
                    waveHand = false;
                    moveSpeed = fabs(moveSpeed);
                    waveCount = 0;
                }
            }

            // NOD HEAD
            if (shakeHeadYes)
            {
                if (shakeHeadCount < 5)
                {
                    rHeadtoUD += moveSpeed;
                    if (rHeadtoUD == 30)
                    {
                        moveSpeed = -fabs(moveSpeed);
                        shakeHeadCount++;
                    }
                    if (rHeadtoUD == -20)
                    {
                        moveSpeed = fabs(moveSpeed);
                        shakeHeadCount++;
                    }

                    if (shakeHeadCount == 4)
                    {
                        rHeadtoUD = 0;
                        shakeHeadYes = false;
                        moveSpeed = fabs(moveSpeed);
                        shakeHeadCount = 0;
                    }
                }
            }

            // SHAKE HEAD
            if (shakeHeadNo)
            {
                if (shakeHeadCount < 8)
                {
                    if (rHeadtoLR == 60)
                    {
                        rHeadtoLR = 20;
                    }
                    else if (rHeadtoLR == -60)
                    {
                        rHeadtoLR += moveSpeed;

                        if (rHeadtoLR == 30)
                        {
                            moveSpeed = -fabs(moveSpeed);
                            shakeHeadCount++;
                        }
                        if (rHeadtoLR == -30)
                        {
                            moveSpeed = fabs(moveSpeed);
                            shakeHeadCount++;
                        }
                        if (shakeHeadCount == 7)
                        {
                            rHeadtoLR = 0;
                            shakeHeadNo = false;
                            moveSpeed = fabs(moveSpeed);
                            shakeHeadCount = 0;
                        }
                    }
                    else
                    {
                        rHeadtoLR += moveSpeed;

                        if (rHeadtoLR == 30)
                        {
                            moveSpeed = -fabs(moveSpeed);
                            shakeHeadCount++;
                        }
                        if (rHeadtoLR == -30)
                        {
                            moveSpeed = fabs(moveSpeed);
                            shakeHeadCount++;
                        }
                        if (shakeHeadCount == 7)
                        {
                            rHeadtoLR = 0;
                            shakeHeadNo = false;
                            moveSpeed = fabs(moveSpeed);
                            shakeHeadCount = 0;
                        }
                    }
                }
            }

            // SHOOT WEAPON
            if (weaponShoot)
            {
                rFinger = 90;
                weapons = 3;
                if ((rArmFrontBack < 90 && moveSpeed > 0) || (rArmFrontBack > 0 && moveSpeed < 0))
                    rArmFrontBack += moveSpeed;
                if (rArmFrontBack == 90)
                {
                    bulletsOut = true;
                    rGun += moveSpeed;
                    shootOut -= shootSpeed;
                    if (shootOut < -4.0)
                    {
                        moveSpeed = -fabs(moveSpeed);
                    }
                }
                if (rArmFrontBack == 0)
                {
                    rFinger = 0;
                    shootOut = 0;
                    weaponShoot = false;
                    bulletsOut = false;
                    moveSpeed = fabs(moveSpeed);
                }
            }

            // SWING SWORD
            if (swingSword)
            {
                if ((rElbowFrontBack < 90 && moveSpeed > 0) || (rElbowFrontBack > 0 && moveSpeed < 0))
                    rElbowFrontBack += moveSpeed;
                if ((rArmFrontBack < 140 && moveSpeed > 0) || (rArmFrontBack > 0 && moveSpeed < 0))
                    rArmFrontBack += moveSpeed;
                rFinger += moveSpeed;

                if (rArmFrontBack == 140)
                {
                    moveSpeed = -fabs(moveSpeed);
                }
                if (rArmFrontBack == 0)
                {
                    moveSpeed = fabs(moveSpeed);
                    swingSword = false;
                }
            }

            // FLY
            if (fly)
            {
                if ((rArmFrontBack < 180 && moveSpeed > 0) || (rArmFrontBack > 0 && moveSpeed < 0))
                    rArmFrontBack += moveSpeed;
                if ((rWholeRobot < 30 && moveSpeed > 0) || (rWholeRobot > 0 && moveSpeed < 0))
                    rWholeRobot += moveSpeed;

                if (rArmFrontBack == 180)
                {
                    rFinger += moveSpeed;
                    rFly += flySpeed;
                    if (rFly > 5.0)
                        moveSpeed = -fabs(moveSpeed);
                }
                if (rArmFrontBack == 0)
                {
                    rFly = 0;
                    fly = false;
                    flySpeed = fabs(flySpeed);
                    moveSpeed = fabs(moveSpeed);
                    rFinger = 0;
                }
            }
        }
    }
    glPopMatrix(); // pop camera rotate

    if (isOrthoBack)
    {
        glPushMatrix();
        {
            {
                glTranslatef(0.0, 0.0, 8.0);
                orthoBack();
            }
        }
        glPopMatrix();
    }
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WindowProcedure;
    wc.lpszClassName = WINDOW_TITLE;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wc))
        return false;

    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
                             NULL, NULL, wc.hInstance, NULL);

    //--------------------------------
    //	Initialize window for OpenGL
    //--------------------------------

    HDC hdc = GetDC(hWnd);

    //	initialize pixel format for the window
    initPixelFormat(hdc);

    //	get an openGL context
    HGLRC hglrc = wglCreateContext(hdc);

    //	make context current
    if (!wglMakeCurrent(hdc, hglrc))
        return false;

    //--------------------------------
    //	End initialization
    //--------------------------------

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        display();

        SwapBuffers(hdc);
    }

    UnregisterClass(WINDOW_TITLE, wc.hInstance);

    return true;
}
//--------------------------------------------------------------------