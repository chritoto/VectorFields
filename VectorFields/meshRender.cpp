#include "meshRender.h"


meshRender::meshRender(Renderer* p_renderer, VoxelBox* p_Box, unsigned char ptype, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    renderer = p_renderer;
    Box = p_Box;
    type = ptype;

}

meshRender::~meshRender()
{
}

void meshRender::saveImage(const QString& fileName)
{
    QImage image = grabFrameBuffer();
    image.save(fileName, "JPG");
}

QSize meshRender::minimumSizeHint() const
{
	return QSize(50, 50);
}


void meshRender::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    
    
    
}

void meshRender::paintGL()
{
    Vec3f Camera = Vec3f(sin(renderer->angleCamphi * PI / 180) * cos(renderer->angleCamdelta * PI / 180), sin(renderer->angleCamphi * PI / 180) * sin(renderer->angleCamdelta * PI / 180), cos(renderer->angleCamphi * PI / 180)) * renderer->dist;
    Vec3f d = Camera.normalize();
    Vec3f dir = (d - renderer->offset).normalize();

    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    GLfloat lightPosition[4] = { 0, 0, 1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glTranslatef(0, 0, -renderer->dist);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    glRotatef(90 - renderer->angleCamphi, 0.0, 1.0, 0.0);
    glRotatef(-renderer->angleCamdelta, 0.0, 0.0, 1.0);
    glTranslatef(renderer->offset.x, renderer->offset.y, renderer->offset.z);
    draw();
}

void meshRender::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glFrustum(-1 / renderer->dscreen, +1 / renderer->dscreen, -1 / renderer->dscreen, +1 / renderer->dscreen, 1, 20000);
#else
    glFrustum(-0.5 / renderer->dscreen, +0.5 / renderer->dscreen, -0.5 / renderer->dscreen, +0.5 / renderer->dscreen, 1, 20000);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void meshRender::mousePressEvent(QMouseEvent* event)
{
    renderer->fromMesh = type; //Prevent from moving the light
    renderer->mousePressEventMesh(event);
    renderer->fromMesh = -1;
    updateGL();
}

void meshRender::mouseMoveEvent(QMouseEvent* event)
{
    renderer->mouseMoveEventMesh(event);
    updateGL();
}

void meshRender::wheelEvent(QWheelEvent* event)
{
    renderer->wheelEventMesh(event);
    updateGL();
}

void meshRender::draw()
{
    qglColor(Qt::red);

    if (type == 0) {
        for (int i = 0; i < Box->normalsMesh.size(); i++) {
            glBegin(GL_TRIANGLES);
            glNormal3f(Box->normalsMesh[i].x, Box->normalsMesh[i].y, Box->normalsMesh[i].z);
            glVertex3f(Box->indicesMesh[i][0].x, Box->indicesMesh[i][0].y, Box->indicesMesh[i][0].z);
            glVertex3f(Box->indicesMesh[i][1].x, Box->indicesMesh[i][1].y, Box->indicesMesh[i][1].z);
            glVertex3f(Box->indicesMesh[i][2].x, Box->indicesMesh[i][2].y, Box->indicesMesh[i][2].z);
            glEnd();
        }
    }
    else if (type == 1) {
        for (int i = 0; i < Box->normalsSpline.size(); i++) {
            glBegin(GL_TRIANGLES);
            glNormal3f(Box->normalsSpline[i].x, Box->normalsSpline[i].y, Box->normalsSpline[i].z);
            glVertex3f(Box->indicesSpline[i][0].x, Box->indicesSpline[i][0].y, Box->indicesSpline[i][0].z);
            glVertex3f(Box->indicesSpline[i][1].x, Box->indicesSpline[i][1].y, Box->indicesSpline[i][1].z);
            glVertex3f(Box->indicesSpline[i][2].x, Box->indicesSpline[i][2].y, Box->indicesSpline[i][2].z);
            glEnd();
        }
    }
}