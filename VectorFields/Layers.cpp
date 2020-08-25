#include "Layers.h"

Layers::Layers(QWidget *parent, const Ui::MainWindowsClass& p_ui, const size_t& p_num)
	: QWidget(parent)
{
    Parent = parent;
    num = p_num;
    ui = p_ui;
    buffer_ = new unsigned char[4 * size.x * size.y];
    if(num == 0)
        scale = new Scale(ui.Scale0, ui);
    else
        scale = new Scale(ui.Scale1, ui);
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_StaticContents);
}

Layers::~Layers()
{
}

void Layers::clear()
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
    scale->clear();
}

size_t Layers::setFrame(VoxelBox* p_Box, const int& p_index)
{
    index = p_index;
    Box = p_Box;
    count = Box->getCount();
    countres = count;
    setSize();
    voxels = Box->getVoxels();
    setLayer(Box->currentLayer);
    if (index == 0) maxValue = Box->getMaxNum();
    if (index == 1) maxValue = Box->getMaxVariaton();
    position = 0;
    setScale(false);
    if (axis == 0) max = count.x;
    if (axis == 1) max = count.y;
    if (axis == 2) max = count.z;
    return max;
}

size_t Layers::setAxis(const size_t& p_axis)
{
    axis = p_axis;
    setSize();
    updateFrame(0);
    if (axis == 0) max = countres.x;
    if (axis == 1) max = countres.y;
    if (axis == 2) max = countres.z;
    return max;
}

void Layers::updateFrame(const size_t& pos)
{
    int multiply;
    if (color == 0) multiply = 255;
    if (color == 1) multiply = 300;
    position = pos;
    std::vector<std::vector<float>> values(
        size.x,
        std::vector<float>(size.y,0));
    size_t resx = 0;
    size_t resy = 0;
    if (axis == 0) { resx = countres.y; resy = countres.z; }
    if (axis == 1) { resx = countres.x; resy = countres.z; }
    if (axis == 2) { resx = countres.x; resy = countres.y; }

	for (size_t i = 0; i < size.x; i++)
	{
		size_t x = std::floor(i/(float)size.x*resx);
		for (size_t j = 0; j < size.y; j++)
		{
			size_t y = std::floor(j / (float)size.y * resy);
            size_t voxelNum;
            if (axis == 0) voxelNum = pos * countres.y * countres.z + x * countres.z + y;
            if (axis == 1) voxelNum = x * countres.y* countres.z + pos * countres.z + y;
            if (axis == 2) voxelNum = x * countres.y * countres.z + y * countres.z + pos;

            float intensity;
            if (voxels[layer-1].at(voxelNum) != nullptr) {
                if (index == 0) intensity = voxels[layer - 1].at(voxelNum)->getNumPoints() / maxValue;
                if (index == 1) intensity = voxels[layer - 1].at(voxelNum)->getSurfaceVariation() / maxValue;
            }
            else intensity = 0;

            if (inverse) intensity = 1 - intensity;
            if (!linear) intensity = pow(intensity, power);

            int value = int(intensity * multiply);

            if (color == 0) {
                buffer_[4 * int(j * size.x + i)] = value;
                buffer_[4 * int(j * size.x + i) + 1] = value;
                buffer_[4 * int(j * size.x + i) + 2] = value;
            }
            else if (color == 1) {
                QColor color;
                color.setHsv(value, 255, 255);
                color.toRgb();
                buffer_[4 * int(j * size.x + i)] = color.red();
                buffer_[4 * int(j * size.x + i) + 1] = color.green();
                buffer_[4 * int(j * size.x + i) + 2] = color.blue();
            }
        }
	}
    update();
}

void Layers::updateFrame()
{
    updateFrame(position);
}

void Layers::save(const QString& fileName)
{
    image.save(fileName, "JPG");
}

void Layers::setIndex(const int& p_index)
{
    index = p_index;
    if (index == 0) maxValue = Box->getMaxNum();
    if (index == 1) maxValue = Box->getMaxVariaton();
    setScale(ui.Inverse->isChecked());
}

void Layers::setScale(const bool& checked)
{
    inverse = checked;
    if(color == 0) scale->setGrey(checked, linear, power);
    if (color == 1) scale->setColor(checked, linear, power);

    auto TextMin = ui.Min0;
    auto TextMax = ui.Max0;
    if (num == 1) {
        TextMin = ui.Min1;
        TextMax = ui.Max1;
    }
    if (checked) { TextMin->setText(QString::number(maxValue)); TextMax->setText("0"); }
    else { TextMin->setText("0"); TextMax->setText(QString::number(maxValue)); }

    updateFrame(position);
}

void Layers::setColor(const int& p_color)
{
    color = p_color;
    setScale(inverse);
}

void Layers::setLinear(const bool& lin)
{
    linear = lin;
    updateFrame(position);
    setScale(inverse);
}

void Layers::setPower(const float& p_power)
{
    power = p_power;
    updateFrame(position);
    setScale(inverse);
}

size_t Layers::setLayer(const int& p_layer)
{
    layer = p_layer;
    countres = count / pow(2, Box->divisions - layer);
    setSize();
    if (axis == 0) max = countres.x;
    if (axis == 1) max = countres.y;
    if (axis == 2) max = countres.z;
    return max;
}

void Layers::setSize()
{
    delete buffer_;
    
    if (axis == 0) size = Vec3i(countres.y, countres.z, 0);
    if (axis == 1) size = Vec3i(countres.x, countres.z, 0);
    if (axis == 2) size = Vec3i(countres.x, countres.y, 0);

    buffer_ = new unsigned char[4 * size.x * size.y];
}

void Layers::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QSize renderSize = Parent->size();
    if (renderSize.height() < renderSize.width()) renderSize.setWidth(renderSize.height());
    else renderSize.setHeight(renderSize.width());

    image = QImage(buffer_, size.x, size.y, QImage::Format_RGB32).scaled(renderSize, Qt::IgnoreAspectRatio);
    
    painter.drawImage(QPoint(0, 0), image);
}

void Layers::mousePressEvent(QMouseEvent* event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    
    if (voxels.size() == 0) return;

    int sizex = image.size().width();
    int sizey = image.size().height();
    
    size_t xvox = 0;
    size_t yvox = 0;
    size_t zvox = 0;
    if (axis == 0) { yvox = std::floor(x / (float)sizex * countres.y); zvox = std::floor(y / (float)sizey * countres.z); xvox = position; }
    if (axis == 1) { xvox = std::floor(x / (float)sizex * countres.x); zvox = std::floor(y / (float)sizey * countres.z); yvox = position; }
    if (axis == 2) { xvox = std::floor(x / (float)sizex * countres.x); yvox = std::floor(y / (float)sizey * countres.y); zvox = position; }

    ui.voxx->setText(QString::number(xvox));
    ui.voxy->setText(QString::number(yvox));
    ui.voxz->setText(QString::number(zvox));
    if (voxels[layer - 1].at(xvox * countres.y * countres.z + yvox * countres.z + zvox) == nullptr)ui.num->setText(QString::number(0));
    else {
        if (index == 0)
            ui.num->setText(QString::number(voxels[layer - 1].at(xvox * countres.y * countres.z + yvox * countres.z + zvox)->getNumPoints()));
        if (index == 1)
            ui.num->setText(QString::number(voxels[layer - 1].at(xvox * countres.y * countres.z + yvox * countres.z + zvox)->getSurfaceVariation()));
    }
    if (num == 0) ui.num_7->setText("Points");
    else ui.num_7->setText("Variation");
}