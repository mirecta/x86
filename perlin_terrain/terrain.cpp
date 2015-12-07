
#include <GL/glut.h>
#include "perlin.h"

//./terrain 50  4 5 5 7

double		as=50.,bs=8.,cs=2.,ds=2.,F=8,H=2;
int			es=2,scalx=4,scalz=4;
double       heigh[256][256],uhol=0;

bool quads = true;
bool rot = true;



void renderScene(void) {

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity();
    gluLookAt(1400,1400,1400,0,0,0,0,1,0);
    //glLoadIdentity();
    //glPointSize(0.5);
    //	glLoadIdentity();
    //glTranslatef(128,0,128);
    glRotatef(uhol,0,1,0);
    glPushMatrix();
    glColor3f(0, 1, 0);         
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPushMatrix();
    //glLoadIdentity();
    //glScalef(1/100,1/100,1/100);
    if(quads)glBegin(GL_QUADS);
    else glBegin(GL_POINTS);

    for(int x = -127; x < 128; x += scalx)
    {
        if(x > 128)break;
        for(int z = -127; z < 127; z += scalz)
        {
            if( z > 127)break;

            glVertex3f(F*(x+scalx),  H*heigh[x+scalx+128][z+128],    F*z);
            glVertex3f(F*x,		 H*heigh[x+128][z+128],		 F*z);
            glVertex3f(F*x,      H*heigh[x+128][z+scalz+128],    F*(z+scalz));
            glVertex3f(F*(x+scalx),  H*heigh[x+scalx+128][z+scalz+128],  F*(z+scalz));
        }
    }
    glEnd();

    glPopMatrix();

    if(rot)uhol+=0.1;

    glutSwapBuffers();
}

int main(int argc, char **argv) {

    // init GLUT and create Window
    glutInit(&argc, argv);
    double _as, _bs, _cs, _ds, _es; 
    if(argc ==  6){
        _as = atof(argv[1]);
        _bs = atof(argv[2]);
        _cs = atof(argv[3]);
        _ds = atof(argv[4]);
        _es = atof(argv[5]);

        if (_as != 0) as = _as;
        if (_bs != 0) bs = _bs;
        if (_cs != 0) cs = _cs;
        if (_ds != 0) ds = _ds;
        if (_es != 0) es = _es;
    }

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,500);
    glutCreateWindow("miro terrain");


    double c;  

    //compute noise
    init();
    for(int x=0; x<=255; x++)
    {
        for(int y=0; y<=255; y++)
        {
            c=(128./2)*(1 + sin( x / as + bs * perlinNoise2D( x / 80., y / 80., cs, ds, es)));
            heigh[(int)x][(int)y]=c;
        }
    }





    // register callbacks
    glutDisplayFunc(renderScene);

    glMatrixMode( GL_PROJECTION );
    gluPerspective(45.0, 1., -50., 1000. );
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_DEPTH_TEST);
    glPointSize(0.01);


    glutIdleFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
