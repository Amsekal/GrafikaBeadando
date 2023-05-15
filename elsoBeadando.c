#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 640

#define M 100
#define N 100

GLuint vao, vao2, vbo, vbo2, vao3, vbo3, vao4, vbo4;

GLfloat HermiteCurve2[3 * M];

GLfloat HermiteCurve[3 * N];

GLfloat HermiteCurve3[3 * N];

GLfloat points[24] = { 0.25f, 0.75f, 0.0f,
0.1f,0.9f,0.0f,
-0.75f, 0.85f, 0.0f,
-0.9f, -0.1f, 0.0f,
-0.55f, -0.1f, 0.0f,
-0.25f,-0.6f,0.0f,
-0.2f, -0.1f, 0.0f,
0.15f,0.6f,0.0f };

GLint dragged = -1;
GLfloat step2 = 1.0f / (M - 1); // t \in [0,1]
GLfloat step = 1.0f / (N - 1); // t \in [0,1]
GLint i;
GLfloat t;


GLfloat dist2_2d(GLfloat P1x, GLfloat P1y, GLfloat P2x, GLfloat P2y) {

    GLfloat dx = P1x - P2x;
    GLfloat dy = P1y - P2y;
    return dx * dx + dy * dy;
}

GLint getActivePoint(GLfloat* p, GLfloat sensitivity, GLfloat x, GLfloat y) {

    GLfloat		s = sensitivity * sensitivity;
    GLfloat		xNorm = -1 + x / (WIDTH / 2);//"WIDTH/2" megmondja, hogy 1 lépés menyni pixel. Tehát 640/2=320 -1->0 
    GLfloat		yNorm = -1 + (HEIGHT - y) / (HEIGHT / 2);// "HEIGHT-y" a helycsere miatt van, hogy lentrõl fel számoljon, ne fentrõl le

    for (GLint i = 0; i < 8; i++)
        if (dist2_2d(p[i * 3], p[i * 3 + 1], xNorm, yNorm) < s) //visszaadja az adott indexet, a legelsõt amit megtalál, nem a felsõt ha ugyna azon a helyen vannak
            return i;

    return -1;
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {

    if (dragged >= 0) {

        GLfloat		xNorm = -1 + x / (WIDTH / 2);
        GLfloat		yNorm = -1 + (HEIGHT - y) / (HEIGHT / 2);
        if (xNorm > -1 && xNorm < 1 && yNorm > -1 && yNorm < 1) {
            points[3 * dragged] = xNorm;  // x coord
            points[3 * dragged + 1] = yNorm;  // y coord


            GLfloat P1x = points[0];
            GLfloat P1y = points[1];

            GLfloat P2x = points[3];
            GLfloat P2y = points[4];

            GLfloat P3x = points[6];
            GLfloat P3y = points[7];

            GLfloat P4x = points[9];
            GLfloat P4y = points[10];

            GLfloat P5x = points[12];
            GLfloat P5y = points[13];

            GLfloat P6x = points[15];
            GLfloat P6y = points[16];

            GLfloat P7x = points[18];
            GLfloat P7y = points[19];

            GLfloat P8x = points[21];
            GLfloat P8y = points[22];

            GLfloat vec1x = P2x - P1x;
            GLfloat vec1y = P2y - P1y;

            GLfloat vec2x = P4x - P3x;
            GLfloat vec2y = P4y - P3y;

            GLfloat vec3x = P6x - P5x;
            GLfloat vec3y = P6y - P5y;

            GLfloat vec4x = P8x - P7x;
            GLfloat vec4y = P8y - P7y;

            HermiteCurve3[0] = P5x;
            HermiteCurve3[1] = P5y;
            HermiteCurve3[2] = 0.0f;

            for (i = 1; i < (N - 1); i++) {
                t = i * step;
                HermiteCurve3[i * 3] = P5x * (2 * t * t * t - 3 * t * t + 1) + P7x * (-2 * t * t * t + 3 * t * t) + vec3x * (t * t * t - 2 * t * t + t) + vec4x * (t * t * t - t * t);
                HermiteCurve3[i * 3 + 1] = P5y * (2 * t * t * t - 3 * t * t + 1) + P7y * (-2 * t * t * t + 3 * t * t) + vec3y * (t * t * t - 2 * t * t + t) + vec4y * (t * t * t - t * t);
                HermiteCurve3[i * 3 + 2] = 0.0f;
            }


            HermiteCurve3[(3 * N) - 3] = P7x;
            HermiteCurve3[(3 * N) - 2] = P7y;
            HermiteCurve3[(3 * N) - 1] = 0.0f;

            HermiteCurve[0] = P3x;
            HermiteCurve[1] = P3y;
            HermiteCurve[2] = 0.0f;

            for (i = 1; i < (N - 1); i++) {
                t = i * step;
                HermiteCurve[i * 3] = P3x * (2 * t * t * t - 3 * t * t + 1) + P5x * (-2 * t * t * t + 3 * t * t) + vec2x * (t * t * t - 2 * t * t + t) + vec3x * (t * t * t - t * t);
                HermiteCurve[i * 3 + 1] = P3y * (2 * t * t * t - 3 * t * t + 1) + P5y * (-2 * t * t * t + 3 * t * t) + vec2y * (t * t * t - 2 * t * t + t) + vec3y * (t * t * t - t * t);
                HermiteCurve[i * 3 + 2] = 0.0f;
            }


            HermiteCurve[(3 * N) - 3] = P5x;
            HermiteCurve[(3 * N) - 2] = P5y;
            HermiteCurve[(3 * N) - 1] = 0.0f;


            HermiteCurve2[0] = P1x;
            HermiteCurve2[1] = P1y;
            HermiteCurve2[2] = 0.0f;

            for (i = 1; i < (M - 1); i++) {
                t = i * step2;
                HermiteCurve2[i * 3] = P1x * (2 * t * t * t - 3 * t * t + 1) + P3x * (-2 * t * t * t + 3 * t * t) + vec1x * (t * t * t - 2 * t * t + t) + vec2x * (t * t * t - t * t);
                HermiteCurve2[i * 3 + 1] = P1y * (2 * t * t * t - 3 * t * t + 1) + P3y * (-2 * t * t * t + 3 * t * t) + vec1y * (t * t * t - 2 * t * t + t) + vec2y * (t * t * t - t * t);
                HermiteCurve2[i * 3 + 2] = 0.0f;
            }

            HermiteCurve2[(3 * M) - 3] = P3x;
            HermiteCurve2[(3 * M) - 2] = P3y;
            HermiteCurve2[(3 * M) - 1] = 0.0f;
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), points, GL_STATIC_DRAW);



            glBindBuffer(GL_ARRAY_BUFFER, vbo2);
            glBufferData(GL_ARRAY_BUFFER, (3 * M) * sizeof(GLfloat), HermiteCurve2, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo3);
            glBufferData(GL_ARRAY_BUFFER, (3 * M) * sizeof(GLfloat), HermiteCurve, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo4);
            glBufferData(GL_ARRAY_BUFFER, (3 * M) * sizeof(GLfloat), HermiteCurve3, GL_STATIC_DRAW);

        }
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double	x, y;

        glfwGetCursorPos(window, &x, &y);
        dragged = getActivePoint(points, 0.1f, x, y);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        dragged = -1;
}

int main() {



    GLFWwindow* window = NULL;
    const GLubyte* renderer;
    const GLubyte* version;

    const char* vertex_shader =
        "#version 330\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4(vp, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "  frag_colour = vec4(1.0, 1.0, 0.0, 1.0);"
        "}";

    const char* vertex_shader2 =
        "#version 410\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4(vp, 1.0);"
        "}";

    const char* fragment_shader2 =
        "#version 410\n"
        "out vec4 frag_colour;"
        "void main () {"
        "  frag_colour = vec4(1.0, 0.0, 0.0, 1.0);"
        "}";


    const char* vertex_shader3 =
        "#version 410\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4(vp, 1.0);"
        "}";

    const char* fragment_shader3 =
        "#version 410\n"
        "out vec4 frag_colour;"
        "void main () {"
        "  frag_colour = vec4(0.0, 0.0, 1.0, 1.0);"
        "}";


    GLuint vert_shader, frag_shader;
    GLuint shader_programme;

    GLuint vert_shader2, frag_shader2;
    GLuint shader_programme2;

    GLuint vert_shader3, frag_shader3;
    GLuint shader_programme3;



    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Drag&Drop", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLfloat P1x = points[0];
    GLfloat P1y = points[1];

    GLfloat P2x = points[3];
    GLfloat P2y = points[4];

    GLfloat P3x = points[6];
    GLfloat P3y = points[7];

    GLfloat P4x = points[9];
    GLfloat P4y = points[10];

    GLfloat P5x = points[12];
    GLfloat P5y = points[13];

    GLfloat P6x = points[15];
    GLfloat P6y = points[16];

    GLfloat P7x = points[18];
    GLfloat P7y = points[19];

    GLfloat P8x = points[21];
    GLfloat P8y = points[22];

    GLfloat vec1x = P2x - P1x;
    GLfloat vec1y = P2y - P1y;

    GLfloat vec2x = P4x - P3x;
    GLfloat vec2y = P4y - P3y;

    GLfloat vec3x = P6x - P5x;
    GLfloat vec3y = P6y - P5y;

    GLfloat vec4x = P8x - P7x;
    GLfloat vec4y = P8y - P7y;

    HermiteCurve3[0] = P5x;
    HermiteCurve3[1] = P5y;
    HermiteCurve3[2] = 0.0f;

    for (i = 1; i < (N - 1); i++) {
        t = i * step;
        HermiteCurve3[i * 3] = P5x * (2 * t * t * t - 3 * t * t + 1) + P7x * (-2 * t * t * t + 3 * t * t) + vec3x * (t * t * t - 2 * t * t + t) + vec4x * (t * t * t - t * t);
        HermiteCurve3[i * 3 + 1] = P5y * (2 * t * t * t - 3 * t * t + 1) + P7y * (-2 * t * t * t + 3 * t * t) + vec3y * (t * t * t - 2 * t * t + t) + vec4y * (t * t * t - t * t);
        HermiteCurve3[i * 3 + 2] = 0.0f;
    }


    HermiteCurve3[(3 * N) - 3] = P7x;
    HermiteCurve3[(3 * N) - 2] = P7y;
    HermiteCurve3[(3 * N) - 1] = 0.0f;

    HermiteCurve[0] = P3x;
    HermiteCurve[1] = P3y;
    HermiteCurve[2] = 0.0f;

    for (i = 1; i < (N - 1); i++) {
        t = i * step;
        HermiteCurve[i * 3] = P3x * (2 * t * t * t - 3 * t * t + 1) + P5x * (-2 * t * t * t + 3 * t * t) + vec2x * (t * t * t - 2 * t * t + t) + vec3x * (t * t * t - t * t);
        HermiteCurve[i * 3 + 1] = P3y * (2 * t * t * t - 3 * t * t + 1) + P5y * (-2 * t * t * t + 3 * t * t) + vec2y * (t * t * t - 2 * t * t + t) + vec3y * (t * t * t - t * t);
        HermiteCurve[i * 3 + 2] = 0.0f;
    }


    HermiteCurve[(3 * N) - 3] = P5x;
    HermiteCurve[(3 * N) - 2] = P5y;
    HermiteCurve[(3 * N) - 1] = 0.0f;

    HermiteCurve2[0] = P1x;
    HermiteCurve2[1] = P1y;
    HermiteCurve2[2] = 0.0f;

    for (i = 1; i < (M - 1); i++) {
        t = i * step2;
        HermiteCurve2[i * 3] = P1x * (2 * t * t * t - 3 * t * t + 1) + P3x * (-2 * t * t * t + 3 * t * t) + vec1x * (t * t * t - 2 * t * t + t) +vec2x * (t * t * t - t * t);
        HermiteCurve2[i * 3 + 1] = P1y * (2 * t * t * t - 3 * t * t + 1) + P3y * (-2 * t * t * t + 3 * t * t) + vec1y * (t * t * t - 2 * t * t + t) + vec2y * (t * t * t - t * t);
        HermiteCurve2[i * 3 + 2] = 0.0f;
    }


    HermiteCurve2[(3 * M) - 3] = P3x;
    HermiteCurve2[(3 * M) - 2] = P3y;
    HermiteCurve2[(3 * M) - 1] = 0.0f;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), points, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, (3 * M) * sizeof(GLfloat), HermiteCurve2, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo3);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBufferData(GL_ARRAY_BUFFER, (3 * M) * sizeof(GLfloat), HermiteCurve, GL_STATIC_DRAW);


    glGenBuffers(1, &vbo4);
    glBindBuffer(GL_ARRAY_BUFFER, vbo4);
    glBufferData(GL_ARRAY_BUFFER, (3 * M) * sizeof(GLfloat), HermiteCurve3, GL_STATIC_DRAW);



    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenVertexArrays(1, &vao3);
    glBindVertexArray(vao3);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenVertexArrays(1, &vao4);
    glBindVertexArray(vao4);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo4);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);



    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vertex_shader, NULL);
    glCompileShader(vert_shader);

    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &fragment_shader, NULL);
    glCompileShader(frag_shader);

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, frag_shader);
    glAttachShader(shader_programme, vert_shader);
    glLinkProgram(shader_programme);

    vert_shader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader2, 1, &vertex_shader2, NULL);
    glCompileShader(vert_shader2);

    frag_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader2, 1, &fragment_shader2, NULL);
    glCompileShader(frag_shader2);

    shader_programme2 = glCreateProgram();
    glAttachShader(shader_programme2, frag_shader2);
    glAttachShader(shader_programme2, vert_shader2);
    glLinkProgram(shader_programme2);

    vert_shader3 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader3, 1, &vertex_shader3, NULL);
    glCompileShader(vert_shader3);

    frag_shader3 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader3, 1, &fragment_shader3, NULL);
    glCompileShader(frag_shader3);

    shader_programme3 = glCreateProgram();
    glAttachShader(shader_programme3, frag_shader3);
    glAttachShader(shader_programme3, vert_shader3);
    glLinkProgram(shader_programme3);

    glPointSize(5.0f);

    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glPointSize(15.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, 8);
        glDrawArrays(GL_LINES, 0, 8);
        glUseProgram(shader_programme3);
        //glDrawArrays(GL_LINES, 0, 1);
        glUseProgram(shader_programme2);
        glBindVertexArray(vao2);
        glDrawArrays(GL_LINE_STRIP, 0, M - 1);

        glBindVertexArray(vao3);
        glDrawArrays(GL_LINE_STRIP, 0, M - 1);

        glBindVertexArray(vao4);
        glDrawArrays(GL_LINE_STRIP, 0, M - 1);




        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
