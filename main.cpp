#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
    Túlio Caique Faria Cota
    Computação Gráfica - 2019
*/

GLint ciclo = 6;

GLfloat corAleatoria() {
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

void insereTriangulo(GLfloat x1, GLfloat x2, GLfloat x3, GLfloat y1, GLfloat y2, GLfloat y3, GLint ciclo){
    if(ciclo > 0){
        if(ciclo == 1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBegin(GL_POLYGON);
            glColor3f(corAleatoria(), corAleatoria(), corAleatoria());
            glVertex2f(x1, y1);
            glColor3f(corAleatoria(), corAleatoria(), corAleatoria());
            glVertex2f(x2, y2);
            glColor3f(corAleatoria(), corAleatoria(), corAleatoria());
            glVertex2f(x3, y3);
        glEnd();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        ciclo--;
        insereTriangulo(x1 + 10, x2 - 10, x3, y1 + 5, y2 + 5, y3 - 5, ciclo);
    }
}

void insereTrianguloCentral(GLfloat x1, GLfloat x2, GLfloat x3, GLfloat y1, GLfloat y2, GLfloat y3, GLint ciclo){
    if(ciclo > 0){
        glBegin(GL_POLYGON);
            glColor3f(corAleatoria(), corAleatoria(), corAleatoria());
            glVertex2f(x1, y1);
            glColor3f(corAleatoria(), corAleatoria(), corAleatoria());
            glVertex2f(x2, y2);
            glColor3f(corAleatoria(), corAleatoria(), corAleatoria());
            glVertex2f(x3, y3);

        glEnd();
        ciclo--;
        insereTrianguloCentral(x1, x2 - 10, x3 +10, y1 + 5, y2 - 5, y3 - 5, ciclo);
    }
}

void triangulo(GLfloat x1, GLfloat x2, GLfloat x3, GLfloat y1, GLfloat y2, GLfloat y3){
    GLfloat pontoMedioY1 = (y1 + y2) / 2;
    GLfloat pontoMedioY2 = (y2 + y3) / 2;
    GLfloat pontoMedioY3 = (y3 + y1) / 2;

    GLfloat pontoMedioX1 = (x1 + x2) / 2;
    GLfloat pontoMedioX2 = (x2 + x3) / 2;
    GLfloat pontoMedioX3 = (x3 + x1) / 2;

    insereTrianguloCentral(pontoMedioX2, pontoMedioX1, pontoMedioX3, pontoMedioY2, pontoMedioY1, pontoMedioY3, ciclo);
    insereTriangulo(x3, pontoMedioX2, pontoMedioX3, y3, pontoMedioY2, pontoMedioY3, ciclo);
    insereTriangulo(pontoMedioX2, x2, pontoMedioX1, pontoMedioY2, y2, pontoMedioY1, ciclo);
    insereTriangulo(pontoMedioX3, pontoMedioX1, x1, pontoMedioY3, pontoMedioY1, y1, ciclo);

}

void construtorTriangulo(){
    glClearColor(0.0,0.0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1);
    glPointSize(15);
    triangulo(130, 260, 0, 130, 0, 0);
    glFlush();
}

void resize(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-50, 300, 300, -50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Fractal - Computação Gráfica 2019 - Túlio Faria");
    glutDisplayFunc(construtorTriangulo);
    glutReshapeFunc(resize);
    glutMainLoop();

    return EXIT_SUCCESS;
}
