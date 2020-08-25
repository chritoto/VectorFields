#include "RendererThread.h"


Renderer::Renderer(QWidget *parent, Ui::MainWindowsClass& p_ui)
	:QWidget(parent)
{
    Parent = parent;
    ui = &p_ui;
    buffer_ = new unsigned char[4 * size.x * size.y];
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_StaticContents);
    dscreen = 2 / tan(angleView / 2 * PI / 180);
    setMouseTracking(true);
}

Renderer::Renderer(QWidget* parent, Renderer& renderer)
    :QWidget(parent) 
{
    Parent = parent;

    linked = &renderer;
    linked->linked = this;

    angleView = renderer.angleView;
    size = renderer.size;

    Box = renderer.Box;
    angleCamdelta = renderer.angleCamdelta;
    angleCamphi = renderer.angleCamphi;
    dist = renderer.dist;
    offset = renderer.offset;
    dscreen = renderer.dscreen;
    maxBound = renderer.maxBound;
    light = renderer.light;
    voxelDims = renderer.voxelDims;

    buffer_ = new unsigned char[4 * size.x * size.y];
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_StaticContents);
    dscreen = 2 / tan(angleView / 2 * PI / 180);
    setMouseTracking(true);

    updateFrame();
}

Renderer::~Renderer()
{
    if (linked != nullptr) linked->linked = nullptr;
}

void Renderer::clear()
{
    for (size_t x = 0; x < size.x; x++)
    {
        for (size_t y = 0; y < size.y; y++)
        {
            buffer_[4 * int(y * size.x + x)] = 0;
            buffer_[4 * int(y * size.x + x) + 1] = 0;
            buffer_[4 * int(y * size.x + x) + 2] = 0;
        }
    }
}


void Renderer::setFrame(VoxelBox* p_Box)
{
    Box = p_Box;
    Box->surfaceRender = surfaceType;
    maxBound = Box->getMaxBound();
    dist = maxBound * 3;
    voxelDims = Box->getDims();
    
    updateFrame();
}

void Renderer::updateFrame()
{
    t1 = Clock::now();
    //Computes cam position
    Camera = Vec3f(sin(angleCamphi * PI / 180) * cos(angleCamdelta * PI / 180), sin(angleCamphi * PI / 180) * sin(angleCamdelta * PI / 180), cos(angleCamphi * PI / 180)) * dist;
    d = Camera.normalize();
    if (lightFollow) { light = d; angleLightdelta = angleCamdelta; angleLightphi = angleCamphi; }
    xdir = Vec3f(d.y, -d.x, 0).normalize();
    ydir = (xdir % d).normalize();
    Camera = Camera - offset;
    
    //Set Background
    int background = int(Box->background * 255);
    for (size_t x = 0; x < size.x; x++) 
    {
        for (size_t y = 0; y < size.y; y++)
        {
            buffer_[4 * int(y * size.x + x)] = background;
            buffer_[4 * int(y * size.x + x) + 1] = background;
            buffer_[4 * int(y * size.x + x) + 2] = background;
            buffer_[4 * int(y * size.x + x) + 3] = 255;
        }
    }

    //Determine if light behind or in front of object
    bool before = false;
    Vec3f poslight = (light * maxBound * 1.5) + offset;
    Vec3f lightdif = (Camera - (poslight-offset));
    zlight = lightdif.norm();
    bool disp = (lightdif * d) >= 0;
    if (zlight > dist) before = true;
    lightSize = (2 * voxelDims[0] / zlight * dscreen) * size.x;

    //Display farther light
    if (!lightFollow && before && disp)
    {
        float x = -poslight * xdir;
        float y = -poslight * ydir / aspectRatio;
        posx = int(x / zlight * dscreen * size.x) + size.x / 2;
        posy = int(y / zlight * dscreen * size.y) + size.y / 2;

        for (int x = -lightSize; x <= lightSize; x++) {
            for (int y = -lightSize; y <= lightSize; y++) {
                int indexx = posx + x;
                int indexy = posy + y;
                if (indexx >= 0 && indexx < size.x && indexy >= 0 && indexy < size.y)
                {
                    buffer_[4 * int(indexy * size.x + indexx)] = lightcolor[2];
                    buffer_[4 * int(indexy * size.x + indexx) + 1] = lightcolor[1];
                    buffer_[4 * int(indexy * size.x + indexx) + 2] = lightcolor[0];
                }
            }
        }
        
    }
    
    //Create threads for rayCasting
    std::vector<QFuture<void>> future;
    rayCaster = RayCaster(Box, buffer_, size, colors, colorMap);
    for (size_t x = 0; x < size.x/rowPerThread; x++)
    {
        future.push_back(QtConcurrent::run(this, &Renderer::threadRow, x));
    }
    for (auto fut = future.begin(); fut != future.end(); ++fut) fut->waitForFinished(); //Wait all threads done


    //Display closer light
    if (!lightFollow && !before && disp)
    {
        float x = -poslight * xdir;
        float y = -poslight * ydir / aspectRatio;
        posx = int(x / zlight * dscreen * size.x) + size.x / 2;
        posy = int(y / zlight * dscreen * size.y) + size.y / 2;

        for (int x = -lightSize; x <= lightSize; x++) {
            for (int y = -lightSize; y <= lightSize; y++) {
                int indexx = posx + x;
                int indexy = posy + y;
                if (indexx >= 0 && indexx < size.x && indexy >= 0 && indexy < size.y)
                {
                    buffer_[4 * int(indexy * size.x + indexx)] = lightcolor[2];
                    buffer_[4 * int(indexy * size.x + indexx) + 1] = lightcolor[1];
                    buffer_[4 * int(indexy * size.x + indexx) + 2] = lightcolor[0];
                }
            }
        }

    }


    update();
}


void Renderer::save(const QString& fileName)
{
    if (fileName.toStdString().compare(fileName.size() - 3, 3, "jpg") == 0)
        image.save(fileName, "JPG");

    else if (fileName.toStdString().compare(fileName.size() - 3, 3, "png") == 0) {
        //Recompute frame without background
        Camera = Vec3f(sin(angleCamphi * PI / 180) * cos(angleCamdelta * PI / 180), sin(angleCamphi * PI / 180) * sin(angleCamdelta * PI / 180), cos(angleCamphi * PI / 180)) * dist;
        d = Camera.normalize();
        if (lightFollow) { light = d; angleLightdelta = angleCamdelta; angleLightphi = angleCamphi; }
        xdir = Vec3f(d.y, -d.x, 0).normalize();
        ydir = (xdir % d).normalize();
        Camera = Camera - offset;

        rayCaster.alpha = true;
        for (size_t x = 0; x < size.x; x++)
        {
            for (size_t y = 0; y < size.y; y++)
            {
                buffer_[4 * int(y * size.x + x) + 3] = 0;
            }
        }
        std::vector<QFuture<void>> future;
        rayCaster = RayCaster(Box, buffer_, size, colors, colorMap);
        for (size_t x = 0; x < size.x / rowPerThread; x++)
        {
            future.push_back(QtConcurrent::run(this, &Renderer::threadRow, x));
        }
        for (auto fut = future.begin(); fut != future.end(); ++fut) fut->waitForFinished(); //Wait all threads done

        rayCaster.alpha = false;

        image = QImage(buffer_, size.x, size.y, QImage::Format_ARGB32);

        origin = QPoint(0, 0);
        if (Parent->size().width() > Parent->size().height()) {
            origin = QPoint((Parent->size().width() - Parent->size().height()) / 2, 0);
        }

        image = image.scaled(Parent->size(), Qt::KeepAspectRatio);
        image.save(fileName, "PNG");
    }
    updateFrame();
}

void Renderer::setAxis(const size_t& p_Axis)
{
    //When The layer view axis is changed
    offset = Vec3f(0, 0, 0);
    if (p_Axis == 0) {
        angleCamdelta = 0;
        angleCamphi = 90;
        Box->Axis = 0;
    }
    else if (p_Axis == 1) {
        angleCamdelta = 90;
        angleCamphi = 90;
        Box->Axis = 1;
    }
    else {
        angleCamdelta = 90;
        angleCamphi = 1;
        Box->Axis = 2;
    }
    updateFrame();
}

void Renderer::setEnable(const bool& val)
{
    //Enables display of cross-section
    Box->layer_enabled = val;
    updateFrame();
}

void Renderer::setLayer(const int& val)
{
    Box->layer[0] = val;
    updateFrame();
}

void Renderer::setParameters()
{
    //Computes parameters after the DisplayOptions is done
    delete buffer_;
    buffer_ = new unsigned char[4 * size.x * size.y];
    dscreen = 2 / tan(angleView / 2 * PI / 180);
    aspectRatio = size.y / size.x;
    if (linked != nullptr) {
        linked->angleView = angleView;
        linked->size = size;
        delete linked->buffer_;
        linked->buffer_ = new unsigned char[4 * size.x * size.y];
        linked->dscreen = dscreen;
        linked->aspectRatio = aspectRatio;
        linked->updateFrame();
    }
    if (Box != nullptr) updateFrame();
}

void Renderer::setSurfaceType(const bool& surface)
{
    surfaceType = surface;
    Box->surfaceRender = surface;
    updateFrame();
}

void Renderer::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Right)
    {
        angleCamdelta = (int)(angleCamdelta + 5) % 360;
        updateFrame();
    }
    if (event->key() == Qt::Key_Left)
    {
        angleCamdelta = (int)(angleCamdelta - 5) % 360;
        updateFrame();
    }
    if (event->key() == Qt::Key_Up)
    {
        angleCamphi -= 5;
        if (angleCamphi < 5)angleCamphi = 5;
        updateFrame();
    }
    if (event->key() == Qt::Key_Down)
    {
        angleCamphi += 5;
        if (angleCamphi > 175)angleCamphi = 175;
        updateFrame();
    }
    if (event->key() == Qt::Key_Space)
    {
        lightFollow = !lightFollow;
        updateFrame();
        if (linked != nullptr) {
            linked->lightFollow = lightFollow;
            linked->updateFrame();
        }
    }
}

void Renderer::mouseMoveEvent(QMouseEvent* event)
{
    float dx = event->x() - lastPos[0];
    float dy = event->y() - lastPos[1];
    float speed = 0.5;

    if (event->buttons() & Qt::LeftButton) {
        if (clicked) {
            if (!clickedLight) {
                angleCamdelta = (int)(angleCamdelta - speed * dx) % 360;
                angleCamphi -= speed * dy;

                if (angleCamphi < 1)angleCamphi = 1;
                if (angleCamphi > 179)angleCamphi = 179;
            }
            else {
                //Keeps the light on a sphere
                light = light * maxBound * 1.5;
                dx = dx / (float)image.size().width() / dscreen * zlight;
                dy = dy / (float)image.size().height() / dscreen * zlight;
                light -= (xdir * dx + ydir * dy);
                if (sqrt(pow(light * xdir, 2) + pow(light * ydir, 2)) < maxBound * 1.5) { //Checks if outside circle
                    float z = sqrt(pow(maxBound * 1.5, 2) - pow(light * xdir, 2) - pow(light * ydir, 2)); // add z component to make it a sphere
                    light -= d * (light * d - z);
                }
                
                light = light.normalize();
            }

            lastPos[0] = event->pos().x();
            lastPos[1] = event->pos().y();
            updateFrame();
        }
        else {
            clicked = true;
            lastPos[0] = event->x();
            lastPos[1] = event->y();
        }
    }
    else if (event->buttons() & Qt::RightButton) {
        if (clicked) {
            offset -= (xdir * dx + ydir * dy)*dist/1000;

            lastPos[0] = event->pos().x();
            lastPos[1] = event->pos().y();
            updateFrame();
        }
        else {
            clicked = true;
            lastPos[0] = event->x();
            lastPos[1] = event->y();
        }
    }
    else {
        clicked = false;
    }
    if (linked != nullptr) {
        linked->angleCamdelta = angleCamdelta;
        linked->angleCamphi = angleCamphi;
        linked->light = light;
        linked->offset = offset;
        linked->updateFrame();
    }
    
}

void Renderer::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::RightButton) {
        clicked = true;
        lastPos[0] = event->x();
        lastPos[1] = event->y();
        clickedLight = false;
    }
    else if (event->buttons() & Qt::LeftButton) {
        clicked = true;
        size_t distance = sqrt(pow(posy - event->y() / (float)image.size().height() * size.y, 2) + pow(posx - (event->x()-origin.x()) / (float)image.size().width() * size.x, 2));
        if (distance <= 2 * lightSize && fromMesh==-1) { //Checks if user clicks within twice the light size
            clickedLight = true;
        }
        else clickedLight = false;
        lastPos[0] = event->x();
        lastPos[1] = event->y();
    }
}

void Renderer::wheelEvent(QWheelEvent* event) {
    int degrees = event->delta() / 8;
    
    dist -= dist * degrees / 100;
    if (dist < maxBound/4) dist = maxBound/4;
    if (dist > 20000) dist = 20000;
    updateFrame();
    if (linked != nullptr) {
        linked->dist = dist;
        linked->updateFrame();
    }
}

void Renderer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    
    image = QImage(buffer_, size.x, size.y, QImage::Format_ARGB32);

    origin = QPoint(0, 0);
    if (Parent->size().width() > Parent->size().height()) {
        origin = QPoint((Parent->size().width() - Parent->size().height()) / 2, 0);
    }
    
    image = image.scaled(Parent->size(), Qt::KeepAspectRatio);
    painter.drawImage(origin, image);

    emit viewChanged(fromMesh); //updates the view in the open openGl windows

    std::this_thread::sleep_for(std::chrono::nanoseconds(int(delay * 1000000000))); //Limits to 60fps
    t2 = Clock::now();
    float fps = 1 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() * 1000000000;
    delay = 1/60.0 - 1/fps + delay;
    delay = delay * (delay > 0);
    if(ui != nullptr)ui->FPS->setText(QString::number(int(fps)));
}


void Renderer::threadRow(const size_t& p_x)
{

    //Raycasting function for each thread
    Vec3f xangle;
    Vec3f yangle;

    for (size_t row = 0; row < rowPerThread; row++) {
        size_t x = p_x * rowPerThread + row;
        if (x < size.x) {

            xangle = xdir * ((size.x / 2 - x) / size.x / dscreen);

            for (size_t y = 0; y < size.y; y++)
            {

                yangle = ydir * ((size.y / 2 - y) / size.y / dscreen * aspectRatio);
                Vec3f dir = (-d + xangle + yangle).normalize();

                if (surfaceType)
                {
                    rayCaster.renderType(x, y, Camera+dir, dir, light);
                }
                else
                {
                    rayCaster.render(x, y, Camera + dir, dir, light);
                }

            }
        }
    }
}
