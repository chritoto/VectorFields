#pragma once

#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QSize>

#include "VoxelBox.h"
#include "RendererThread.h"

class meshRender : public QGLWidget
{
	Q_OBJECT

public:
	meshRender(Renderer* p_renderer, VoxelBox* p_Box, unsigned char ptype, QWidget *parent=0);
	~meshRender();
    void saveImage(const QString& fileName);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    void draw();

    Renderer* renderer;
    VoxelBox* Box;

    unsigned char type; //0 if mesh, 1 if spline
};
