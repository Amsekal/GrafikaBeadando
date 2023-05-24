#include "gl_utils.h"
#include "maths_funcs.h"
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define GL_LOG_FILE "gl.log"

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width       = 800;
int g_gl_height      = 800;
GLFWwindow* g_window = NULL;

int main() {
  restart_gl_log();

  start_gl();


  GLfloat points_f[] = { -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f };
  GLfloat colours_f[] = { 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f };

  GLfloat points_b[] = { 0.5f, -0.5f, -0.5f,-0.5f, -0.5f, -0.5f,-0.5f, 0.5f, -0.5f, -0.5f,0.5f,-0.5f ,0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f };
  GLfloat colours_b[] = { 0.5f, 0.9f, 0.3f,
      0.5f, 0.9f, 0.3f,
      0.5f, 0.9f, 0.3f,
      0.5f, 0.9f, 0.3f,
      0.5f, 0.9f, 0.3f,
      0.5f, 0.9f, 0.3f };

  GLfloat points_l[] = { -0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f };
  GLfloat colours_l[] = { 0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f };

  GLfloat points_r[] = { 0.5f,0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f };
  GLfloat colours_r[] = { 1.0f, 0.7f, 0.3f,
      1.0f, 0.7f, 0.3f,
      1.0f, 0.7f, 0.3f,
      1.0f, 0.7f, 0.3f,
      1.0f, 0.7f, 0.3f,
      1.0f, 0.7f, 0.3f };

  GLfloat points_bottom[] = { -0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f };
  GLfloat colours_bottom[] = { 0.33f, 1.0f, 0.31415f,
      0.33f, 1.0f, 0.31415f,
      0.33f, 1.0f, 0.31415f,
      0.33f, 1.0f, 0.31415f,
      0.33f, 1.0f, 0.31415f,
      0.33f, 1.0f, 0.31415f };

  GLfloat points_t[] = { -0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f };
  GLfloat colours_t[] = { 1.0f,0.5f,0.0f,
      1.0f,0.5f,0.0f,
      1.0f,0.5f,0.0f,
      1.0f,0.5f,0.0f,
      1.0f,0.5f,0.0f,
      1.0f,0.5f,0.0f };

  GLfloat points_negyzet[] = { -0.1f,0.6f,0.0f,
      0.1f,0.6f,0.0f,
      0.1f,0.8f,0.0f,
      0.1f,0.8f,0.0f,
      -0.1f,0.8f,0.0f,
      -0.1f,0.6f,0.0f };
  GLfloat colours_negyzet[] = { 1.0f,0.0f,0.0f,
      0.0f,1.0f,0.0f,
      0.0f,0.0f,1.0f,
      0.0f,0.0f,1.0f,
      0.0f,1.0f,0.0f,
      1.0f,0.0f,0.0f }; 
  



  GLuint points_vbo;
  glGenBuffers(1, &points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_f, GL_STATIC_DRAW);

  GLuint colours_vbo;
  glGenBuffers(1, &colours_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_f, GL_STATIC_DRAW);

  GLuint points_vbo_back;
  glGenBuffers(1, &points_vbo_back);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_back);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_b, GL_STATIC_DRAW);

  GLuint colours_vbo_back;
  glGenBuffers(1, &colours_vbo_back);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_back);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_b, GL_STATIC_DRAW);

  GLuint points_vbo_left;
  glGenBuffers(1, &points_vbo_left);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_left);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_l, GL_STATIC_DRAW);

  GLuint colours_vbo_left;
  glGenBuffers(1, &colours_vbo_left);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_left);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_l, GL_STATIC_DRAW);

  GLuint points_vbo_right;
  glGenBuffers(1, &points_vbo_right);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_right);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_r, GL_STATIC_DRAW);

  GLuint colours_vbo_right;
  glGenBuffers(1, &colours_vbo_right);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_right);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_r, GL_STATIC_DRAW);

  GLuint points_vbo_bottom;
  glGenBuffers(1, &points_vbo_bottom);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_bottom);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_bottom, GL_STATIC_DRAW);

  GLuint colours_vbo_bottom;
  glGenBuffers(1, &colours_vbo_bottom);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_bottom);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_bottom, GL_STATIC_DRAW);

  GLuint points_vbo_top;
  glGenBuffers(1, &points_vbo_top);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_top);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_t, GL_STATIC_DRAW);

  GLuint colours_vbo_top;
  glGenBuffers(1, &colours_vbo_top);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_top);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_t, GL_STATIC_DRAW);

  GLuint points_vbo_single;
  glGenBuffers(1, &points_vbo_single);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_single);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points_negyzet, GL_STATIC_DRAW);

  GLuint colours_vbo_single;
  glGenBuffers(1, &colours_vbo_single);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_single);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colours_negyzet, GL_STATIC_DRAW);




  GLuint vao, vao2, vao3, vao4, vao5, vao6,vao7;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glGenVertexArrays(1, &vao2);
  glBindVertexArray(vao2);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_back);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_back);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glGenVertexArrays(1, &vao3);
  glBindVertexArray(vao3);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_left);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_left);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glGenVertexArrays(1, &vao4);
  glBindVertexArray(vao4);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_right);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_right);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glGenVertexArrays(1, &vao5);
  glBindVertexArray(vao5);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_bottom);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_bottom);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glGenVertexArrays(1, &vao6);
  glBindVertexArray(vao6);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_top);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_top);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glGenVertexArrays(1, &vao7);
  glBindVertexArray(vao7);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo_single);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_single);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);





  const char* vertex_shader =
      "#version 410\n"
      "layout(location = 0) in vec3 vertex_position;"
      "layout(location = 1) in vec3 vertex_colour;"
      "uniform mat4 view, proj,matrix;"
      "out vec3 colour;"
      "void main () {"
      " 	colour = vertex_colour;"
      "gl_Position = proj * view * matrix * vec4(vertex_position, 1.0);"
      "}";
  const char* fragment_shader =
      "#version 410\n"
      "in vec3 colour;"
      "out vec4 frag_colour;"
      "void main () {"
      "  frag_colour = vec4(colour, 1.0);"
      "}";

  const char* vertex_shader2 =
      "#version 410\n"
      "layout(location = 0) in vec3 vertex_position;"
      "layout(location = 1) in vec3 vertex_colour;"
      "uniform mat4 view, proj,matrix2;"
      "out vec3 colour;"
      "void main () {"
      " 	colour = vertex_colour;"
      "gl_Position = proj * view * matrix2 * vec4(vertex_position, 1.0);"
      "}";
  const char* fragment_shader2 =
      "#version 410\n"
      "in vec3 colour;"
      "out vec4 frag_colour;"
      "void main () {"
      "  frag_colour = vec4(colour, 1.0);"
      "}";
  const char* vertex_shader3 =
      "#version 410\n"
      "layout(location = 0) in vec3 vertex_position;"
      "layout(location = 1) in vec3 vertex_colour;"
      "uniform mat4 view, proj;"
      "out vec3 colour;"
      "void main () {"
      " 	colour = vertex_colour;"
      "gl_Position = proj*view*vec4(vertex_position, 1.0);"
      "}";
  const char* fragment_shader3 =
      "#version 410\n"
      "in vec3 colour;"
      "out vec4 frag_colour;"
      "void main () {"
      "  frag_colour = vec4(colour, 1.0);"
      "}";


  GLuint vert_shader,vert_shader2,vert_shader3,frag_shader, frag_shader2,frag_shader3;
  GLuint shader_programme,shader_programme2,shader_programme3;


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


  GLfloat matrix[] = {
          1.0f,0.0f,0.0f,0.0f,
          0.0f,1.0f,0.0f,0.0f,
          0.0f,0.0f,1.0f,0.0f,
          0.0f,0.0f,0.0f,1.0f
  };


  GLfloat matrix2[] = {
          1.0f,0.0f,0.0f,0.0f,
          0.0f,1.0f,0.0f,0.0f,
          0.0f,0.0f,1.0f,0.0f,
          0.0f,0.0f,0.0f,1.0f
  };

  GLint matrix_location = glGetUniformLocation(shader_programme, "matrix");
  glUseProgram(shader_programme);
  glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);

  GLint matrix_location2 = glGetUniformLocation(shader_programme2, "matrix2");
  glUseProgram(shader_programme2);
  glUniformMatrix4fv(matrix_location2, 1, GL_FALSE, matrix2);


  float speed = 1.0f; // move at 1 unit per second
  float last_position = 0.0f;
  float last_position2 = 0.0f;


  /*--------------------------create camera matrices----------------------------*/
  /* create PROJECTION MATRIX */
  // input variables
  float near   = 0.1f;                                   // clipping plane
  float far    = 100.0f;                                 // clipping plane
  float fov    = 67.0f * ONE_DEG_IN_RAD;                 // convert 67 degrees to radians
  float aspect = (float)g_gl_width / (float)g_gl_height; // aspect ratio
  // matrix components
  float inverse_range = 1.0f / tan( fov * 1.0f );
  float Sx            = inverse_range / aspect;
  float Sy            = inverse_range;
  float Sz            = -( far + near ) / ( far - near );
  float Pz            = -( 2.0f * far * near ) / ( far - near );
  GLfloat proj_mat[]  = { Sx, 0.0f, 0.0f, 0.0f, 0.0f, Sy, 0.0f, 0.0f, 0.0f, 0.0f, Sz, -1.0f, 0.0f, 0.0f, Pz, 0.0f };

  /* create VIEW MATRIX */
  float cam_speed     = 1.0f;                 // 1 unit per second
  float cam_yaw_speed = 10.0f;                // 10 degrees per second
  float cam_pos[]     = { 0.0f, 0.0f, 2.0f }; // don't start at zero, or we will be too close
  float cam_yaw       = 0.0f;                 // y-rotation in degrees
  mat4 T              = translate( identity_mat4(), vec3( -cam_pos[0], -cam_pos[1], -cam_pos[2] ) );
  mat4 R              = rotate_y_deg( identity_mat4(), -cam_yaw );
  mat4 view_mat       = R * T;

  /* get location numbers of matrices in shader programme */
  GLint view_mat_location = glGetUniformLocation( shader_programme, "view" );
  GLint proj_mat_location = glGetUniformLocation( shader_programme, "proj" );

  GLint view_mat_location2 = glGetUniformLocation(shader_programme2, "view");
  GLint proj_mat_location2 = glGetUniformLocation(shader_programme2, "proj");

  GLint view_mat_location3 = glGetUniformLocation(shader_programme3, "view");
  GLint proj_mat_location3 = glGetUniformLocation(shader_programme3, "proj");

  /* use program (make current in state machine) and set default matrix values*/
  glUseProgram( shader_programme );
  glUniformMatrix4fv( view_mat_location, 1, GL_FALSE, view_mat.m );
  glUniformMatrix4fv( proj_mat_location, 1, GL_FALSE, proj_mat );

  glUseProgram(shader_programme2);
  glUniformMatrix4fv(view_mat_location2, 1, GL_FALSE, view_mat.m);
  glUniformMatrix4fv(proj_mat_location2, 1, GL_FALSE, proj_mat);
  glUseProgram(shader_programme);
  glUseProgram(shader_programme3);
  glUniformMatrix4fv(view_mat_location3, 1, GL_FALSE, view_mat.m);
  glUniformMatrix4fv(proj_mat_location3, 1, GL_FALSE, proj_mat);
  glUseProgram(shader_programme);



  glEnable(GL_DEPTH_TEST);

  while ( !glfwWindowShouldClose( g_window ) ) {
    static double previous_seconds = glfwGetTime();
    double current_seconds         = glfwGetTime();
    double elapsed_seconds         = current_seconds - previous_seconds;
    previous_seconds               = current_seconds;

    _update_fps_counter( g_window );
    // wipe the drawing surface clear
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport( 0, 0, g_gl_width, g_gl_height );

    glUseProgram( shader_programme );
    glBindVertexArray( vao );
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(vao2);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(vao3);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(vao4);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(vao5);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(vao6);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUseProgram(shader_programme3);
    glUseProgram(shader_programme2);
    glUniformMatrix4fv(matrix_location2, 1, GL_FALSE, matrix2);
    glBindVertexArray(vao7);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwPollEvents();
    glUseProgram(shader_programme);
    GLfloat theta = elapsed_seconds * speed + last_position;

    
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
    matrix[0] = cos(glfwGetTime()*5);
    matrix[2] = -sin(glfwGetTime()*5);
    matrix[8] = sin(glfwGetTime()*5);
    matrix[10] = cos(glfwGetTime()*5);
    matrix[13] = theta;
    glUseProgram(shader_programme2);
    glUniformMatrix4fv(matrix_location2, 1, GL_FALSE, matrix2);
    matrix2[0] = cos(glfwGetTime());
    matrix2[2] = sin(glfwGetTime());
    matrix2[8] = -sin(glfwGetTime());
    matrix2[10] = cos(glfwGetTime());
    matrix2[13] = theta;
    glUseProgram(shader_programme);
  
    last_position = theta;

    if (fabs(last_position) > 1.0) { speed = -speed; }
    //
    // Note: this call is related to the most recently 'used' shader programme
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);

    
    /*-----------------------------move camera here-------------------------------*/
    // control keys
    bool cam_moved = false;
    if ( glfwGetKey( g_window, GLFW_KEY_D ) ) {
      cam_pos[0] -= cam_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_A ) ) {
      cam_pos[0] += cam_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_PAGE_DOWN ) ) {
      cam_pos[1] += cam_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_PAGE_UP ) ) {
      cam_pos[1] -= cam_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_W ) ) {
      cam_pos[2] -= cam_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_S ) ) {
      cam_pos[2] += cam_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_LEFT ) ) {
      cam_yaw += cam_yaw_speed * elapsed_seconds;
      cam_moved = true;
    }
    if ( glfwGetKey( g_window, GLFW_KEY_RIGHT ) ) {
      cam_yaw -= cam_yaw_speed * elapsed_seconds;
      cam_moved = true;
    }
    /* update view matrix */
    if ( cam_moved ) {
      mat4 T        = translate( identity_mat4(), vec3( -cam_pos[0], -cam_pos[1],
                                             -cam_pos[2] ) ); // cam translation
      mat4 R        = rotate_y_deg( identity_mat4(), -cam_yaw );     //
      mat4 view_mat = R * T;
      glUniformMatrix4fv( view_mat_location, 1, GL_FALSE, view_mat.m );
      glUseProgram(shader_programme2);
      glUniformMatrix4fv(view_mat_location2, 1, GL_FALSE, view_mat.m);
    }

    if ( GLFW_PRESS == glfwGetKey( g_window, GLFW_KEY_ESCAPE ) ) { glfwSetWindowShouldClose( g_window, 1 ); }
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers( g_window );
}
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}