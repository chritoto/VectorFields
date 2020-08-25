#include "MainWindows.h"

MainWindows::MainWindows(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.points->setVisible(false);

	renderer = new Renderer(ui.renderer, ui);
	connect(renderer, SIGNAL(viewChanged(int)),
		this, SLOT(reloadOpenGL(int)));
	
	layers1 = new Layers(ui.Layer1, ui, 0);
	layers2 = new Layers(ui.Layer2, ui, 1);

	//Link UI actions to functions
	connect(ui.Slider, SIGNAL(valueChanged(int)),
		this, SLOT(slider(int)));
	connect(ui.Color, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setColor(int)));
	connect(ui.power, SIGNAL(valueChanged(double)),
		this, SLOT(setPower(double)));
	connect(ui.layerSelect, SIGNAL(valueChanged(int)),
		this, SLOT(setLayer(int)));
	connect(ui.splitter, SIGNAL(splitterMoved(int, int)),
		this, SLOT(splitter(int, int)));
	connect(ui.segType, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setSegType(int)));


	//Set the splitter (slider) between the renderer and the layers to center
	ui.splitter->setSizes(QList<int>() << 150 << 200);
	
	ui.customPlot->setBackground(this->palette().background().color());
	ui.customPlot->setVisible(false);

	ui.GroupSlider->setVisible(false);
	ui.layoutIsolate->setVisible(false);
	connect(ui.GroupSlider, SIGNAL(valueChanged(int)),
		this, SLOT(sliderGroup(int)));
	
	//Initialize legend for types
	legendWidget = new QWidget();
	legend = new QGridLayout();
	legendLabels[0] = new QLabel("Undetermined", this);
	legendLabels[1] = new QLabel("Peak", this);
	legendLabels[2] = new QLabel("Planar", this);
	legendLabels[3] = new QLabel("Ridge", this);
	legendLabels[4] = new QLabel("Pit", this);
	legendLabels[5] = new QLabel("Saddle", this);
	legendLabels[6] = new QLabel("Valley", this);

	for (int i = 0; i < 7; i++) {
		QPixmap pixMap(10, 10);
		pixMap.fill(colors[renderer->colorMap[i]]);
		legendColors[i] = new QLabel();
		legendColors[i]->setPixmap(pixMap);
		legend->addWidget(legendColors[i], i, 0);
		legend->addWidget(legendLabels[i], i, 1);
	}

	legendWidget->setLayout(legend);
	ui.gridRenderer->addWidget(legendWidget, 0, 0, Qt::AlignBottom | Qt::AlignRight);
	legendWidget->setVisible(false);
}

//FileDialog to select a PLY file
void MainWindows::on_ImportPLY_clicked()
{
	QFileInfo filename = QFileDialog::getOpenFileName(this, "Import ply file", QString(), tr("PLY (*.ply)"));
	if (filename.exists())
	{
		path = filename.filePath();
		ui.FileName->setText(filename.fileName());
		ui.Generate->setEnabled(true);
	}
	else
	{
		QMessageBox::warning(this, "Error", "Error with file");
		return;
	}
}

//FileDialog to select a STL file
void MainWindows::on_ImportSTL_clicked()
{
	QFileInfo filename = QFileDialog::getOpenFileName(this, "Import stl file", QString(), tr("STL (*.stl)"));
	if (filename.exists())
	{
		path = filename.filePath();
		ui.FileName->setText(filename.fileName());
		ui.Generate->setEnabled(true);
	}
	else
	{
		QMessageBox::warning(this, "Error", "Error with file");
		return;
	}
}

void MainWindows::on_action_ply_triggered()
{
	on_ImportPLY_clicked();
}
void MainWindows::on_action_stl_triggered()
{
	on_ImportSTL_clicked();
}

//Save image of renderer
void MainWindows::on_actionRenderer_triggered()
{
	QString initialPath = QDir::currentPath() + "/untitled.jpg";

	// Get selected file from dialog
	// Add the proper file formats and extensions
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("JPG Files (*.jpg);;PNG Files(*.png);;All Files (*)"));

	// If no file do nothing
	if (fileName.isEmpty()) {
		return;
	}
	else {
		renderer->save(fileName);

		return;
	}
}

//Save image of layer view of number of points
void MainWindows::on_action_Points_triggered()
{
	QString initialPath = QDir::currentPath() + "/untitled.jpg";

	// Get selected file from dialog
	// Add the proper file formats and extensions
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("JPG Files (*.jpg);;All Files (*)"));

	// If no file do nothing
	if (fileName.isEmpty()) {
		return;
	}
	else {
		layers1->save(fileName);

		return;
	}
}

//Save image of layer view of surface variation
void MainWindows::on_actionSurface_Variation_triggered()
{
	QString initialPath = QDir::currentPath() + "/untitled.jpg";

	// Get selected file from dialog
	// Add the proper file formats and extensions
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("JPG Files (*.jpg);;All Files (*)"));

	// If no file do nothing
	if (fileName.isEmpty()) {
		return;
	}
	else {
		layers2->save(fileName);

		return;
	}
}

void MainWindows::on_actionQuit_triggered()
{
	QApplication::quit();
}

//Save the generatred file OBSOLETE FOR NOW
void MainWindows::on_actionSave_triggered()
{
	if (Voxels == nullptr) {
		QMessageBox::information(this, tr("Error"), tr("No model generated"));
		return;
	}

	// Define path, name and default file type
	QString initialPath = QDir::currentPath() + "/untitled.lvsn";

	// Get selected file from dialog
	// Add the proper file formats and extensions
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("LVSN Files (*.lvsn);;All Files (*)"));

	// If no file do nothing
	if (fileName.isEmpty()) {
		return;
	}
	else {
		QFile f(fileName);
		if (!f.open(QIODevice::ReadWrite))
			return;
		QDataStream out(&f);
		
		out << *Voxels;

		f.close();

		return;
	}
}

//Open the generatred file NEEDS WORK
void MainWindows::on_actionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), QDir::currentPath(), tr("LVSN Files (*.lvsn);;All Files (*)"));

	// If we have a file name load the image and place
	if (!fileName.isEmpty())
	{

		QFile f(fileName);
		if (!f.open(QIODevice::ReadOnly)) {
			QMessageBox::information(this, tr("Unable to open file"),
				f.errorString());
			return;
		}
		
		QDataStream in(&f);

		if(Voxels != nullptr) delete Voxels;
		Voxels = new VoxelBox();
		in >> *Voxels;

		ui.doubleSpinBox->setValue(Voxels->getDims().x);
		ui.doubleSpinBox_2->setValue(Voxels->getDims().y);
		ui.doubleSpinBox_3->setValue(Voxels->getDims().z);
		ui.spinBox->setValue(Voxels->getCount().x);
		ui.spinBox_2->setValue(Voxels->getCount().y);
		ui.spinBox_3->setValue(Voxels->getCount().z);

		if (Voxels->root != nullptr) {
			ui.spinBox_4->setValue(Voxels->divisions);
			ui.layerSelect->setEnabled(true);
			ui.layerSelect->setRange(1, Voxels->divisions);
			Voxels->currentLayer = Voxels->divisions;
		}

		initiateView();
	}
}

//Clear the objects
void MainWindows::on_actionNew_triggered()
{
	renderer->clear();
	layers1->clear();
	layers2->clear();

	ui.customPlot->setVisible(false);
	ui.points->setVisible(false);
	ui.numPoints->setText("");


	delete Voxels;

	ui.layerBox->setEnabled(false);
	ui.renderBox->setEnabled(false);

	for (auto Icon = FSicons.begin(); Icon != FSicons.end(); ++Icon) delete *Icon;

	path = "";
	ui.FileName->setText("");
	ui.Generate->setEnabled(false);
	ui.Spline->setEnabled(false);
	ui.Mesh->setEnabled(false);
}

//Sets the cross-section layer
void MainWindows::slider(int value)
{
	ui.label_layer->setText(QString::number(value));
	layers1->updateFrame(value - 1);
	layers2->updateFrame(value - 1);
	renderer->setLayer(value - 1);
}

//Set Tint or grey-scale display of layers
void MainWindows::setColor(int color)
{
	layers1->setColor(color);
	layers2->setColor(color);
}

//Set the cross-section Axis
void MainWindows::on_layerx_clicked()
{
	size_t slidermax = layers1->setAxis(0);
	layers2->setAxis(0);
	ui.Slider->setMaximum(slidermax);
	renderer->setAxis(0);
}
void MainWindows::on_layery_clicked()
{
	size_t slidermax = layers1->setAxis(1);
	layers2->setAxis(1);
	ui.Slider->setMaximum(slidermax);
	renderer->setAxis(1);
}
void MainWindows::on_layerz_clicked()
{
	size_t slidermax = layers1->setAxis(2);
	layers2->setAxis(2);
	ui.Slider->setMaximum(slidermax);
	renderer->setAxis(2);
}

//Enable the display of the cross-section plane in the renderer
void MainWindows::on_Enable_clicked()
{
	if (ui.Enable->isChecked()) { ui.LayerFrame->setEnabled(true); renderer->setEnable(true); }
	else { ui.LayerFrame->setEnabled(false); renderer->setEnable(false); }
}

//Inverse the scale of the layer view
void MainWindows::on_Inverse_clicked() {
	layers1->setPower(1 / ui.power->value());
	layers2->setPower(1 / ui.power->value());
	ui.power->setValue(1 / ui.power->value());

	layers1->setScale(ui.Inverse->isChecked());
	layers2->setScale(ui.Inverse->isChecked());
}

//Sets the scale of the layer view to be linear
void MainWindows::on_linear_clicked()
{
	ui.labelpower->setEnabled(false);
	ui.power->setEnabled(false);
	layers1->setLinear(true);
	layers2->setLinear(true);
}

//Sets the scale of the layer view to be non-linear
void MainWindows::on_non_linear_clicked()
{
	ui.labelpower->setEnabled(true);
	ui.power->setEnabled(true);
	layers1->setLinear(false);
	layers2->setLinear(false);
}

//Sets the power of the non-linear scale
void MainWindows::setPower(double power)
{
	layers1->setPower(power);
	layers2->setPower(power);
}

//The Octree level displayed in the layerView
void MainWindows::setLayer(int newLayer)
{
	Voxels->currentLayer = newLayer;

	size_t slidermax = layers1->setLayer(newLayer);
	layers2->setLayer(newLayer);
	ui.Slider->setMaximum(slidermax);
	layers1->setIndex(0);
	layers2->setIndex(1);
	
	layers1->updateFrame();
	layers2->updateFrame();
	renderer->updateFrame();
}

//When the full screen icon for the histogram is clicked
void MainWindows::histogramClicked()
{
	QCustomPlot* hist = new QCustomPlot();
	QCPBars* data = new QCPBars(hist->xAxis, hist->yAxis);

	data->setPen(Qt::NoPen);
	data->setBrush(QColor(100, 180, 110));

	hist->xAxis->setLabel("# Points");
	hist->yAxis->setLabel("# Voxels");

	hist->xAxis->setRange(ui.customPlot->xAxis->range());
	hist->yAxis->setRange(ui.customPlot->yAxis->range());

	data->setWidthType(QCPBars::wtAbsolute);
	data->setWidth(3);
	data->setData(histogram->data());

	hist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	hist->resize(1000, 700);
	hist->show();
	hist->setAttribute(Qt::WA_QuitOnClose, false);
}

//When the full screen icon for the renderer is clicked
void MainWindows::rendererClicked()
{
	if (renderer->linked == nullptr) {
		newWindow* nw = new newWindow();
		nw->setAttribute(Qt::WA_DeleteOnClose);
		nw->resize(1000, 700);

		Renderer* rendererwindow = new Renderer(nw, *renderer);
		nw->renderer = rendererwindow;

		nw->show();
		nw->setAttribute(Qt::WA_QuitOnClose, false);
	}

}

void MainWindows::ExportMesh(QAction* action)
{
	//Export MarchingCube geometry
	if (action->text() == ".obj") {
		QString initialPath = QDir::currentPath() + "/mesh_";
		int count = 1;
		QFileInfo check_file(initialPath + QString::number(count) + ".obj");
		while (check_file.exists()) {
			count++;
			check_file = QFileInfo(initialPath + QString::number(count) + ".obj");
		}
		initialPath = initialPath + QString::number(count) + ".obj";

		// Get selected file from dialog
		// Add the proper file formats and extensions
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
			initialPath,
			tr("OBJ Files (*.obj);;All Files (*)"));
		// If no file do nothing
		if (fileName.isEmpty()) {
			return;
		}
		else {
			Voxels->SaveOBJ(fileName, 0);
		}
	}
	else {
		QString initialPath = QDir::currentPath() + "/meshRender.jpg";

		QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
			initialPath,
			tr("JPG Files (*.jpg);;All Files (*)"));
		// If no file do nothing
		if (fileName.isEmpty()) {
			return;
		}
		else {
			meshwindow->saveImage(fileName);
		}
	}
}

void MainWindows::ExportSpline(QAction* action)
{
	//Export Spline Geometry
	if (action->text() == ".obj") {
		QString initialPath = QDir::currentPath() + "/mesh_";
		int count = 1;
		QFileInfo check_file(initialPath + QString::number(count) + ".obj");
		while (check_file.exists()) {
			count++;
			check_file = QFileInfo(initialPath + QString::number(count) + ".obj");
		}
		initialPath = initialPath + QString::number(count) + ".obj";

		// Get selected file from dialog
		// Add the proper file formats and extensions
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
			initialPath,
			tr("OBJ Files (*.obj);;All Files (*)"));
		// If no file do nothing
		if (fileName.isEmpty()) {
			return;
		}
		else {
			Voxels->SaveOBJ(fileName, 1);
		}
	}
	else {
		QString initialPath = QDir::currentPath() + "/meshRender.jpg";

		QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
			initialPath,
			tr("JPG Files (*.jpg);;All Files (*)"));
		// If no file do nothing
		if (fileName.isEmpty()) {
			return;
		}
		else {
			meshSplinewindow->saveImage(fileName);
		}
	}
}

void MainWindows::reloadOpenGL(int value)
{
	if (value == 0) { //Comes from meshWindow
		if (meshSplinewindow != nullptr) meshSplinewindow->updateGL();
	}
	else if (value == 1) { //Comes from meshSplineWindow
		if (meshwindow != nullptr) meshwindow->updateGL();
	}
	else {
		if (meshSplinewindow != nullptr) meshSplinewindow->updateGL();
		if (meshwindow != nullptr) meshwindow->updateGL();
	}
}


//Resize the views when the splitter (slider) between the renderer and the layer views is moved
void MainWindows::splitter(int pos, int index)
{
	layers1->resize(ui.Layer1->size());
	layers2->resize(ui.Layer2->size());
	layers1->scale->resize(ui.Scale0->size());
	layers2->scale->resize(ui.Scale1->size());
	renderer->resize(ui.renderer->size());
}

//When the window is resized
void MainWindows::resizeEvent(QResizeEvent* event)
{
	layers1->resize(ui.Layer1->size());
	layers2->resize(ui.Layer2->size());
	layers1->scale->resize(ui.Scale0->size());
	layers2->scale->resize(ui.Scale1->size());
	renderer->resize(ui.renderer->size());
}

//Resize when the window is changed by the OS (full-screen, minimized...)
void MainWindows::showEvent(QShowEvent* event)
{
	layers1->resize(ui.Layer1->size());
	layers2->resize(ui.Layer2->size());
	layers1->scale->resize(ui.Scale0->size());
	layers2->scale->resize(ui.Scale1->size());
	renderer->resize(ui.renderer->size());
}

void MainWindows::initiateView()
{
	//Initialize the renderer
	renderer->setFrame(Voxels);
	ui.renderBox->setEnabled(true);

	//Initialize fullscreen icon
	FullScreenIcon* FS = new FullScreenIcon(this);
	FS->setMaximumHeight(20);
	ui.gridRenderer->addWidget(FS, 0, 0, Qt::AlignTop | Qt::AlignRight);
	FSicons.push_back(FS);

	connect(FS, SIGNAL(clicked()),
		this, SLOT(rendererClicked()));


	//Intialiaze layer view
	size_t slidermax = layers1->setFrame(Voxels, 0);
	layers2->setFrame(Voxels, 1);
	ui.Slider->setMaximum(slidermax);
	ui.Slider->setEnabled(true);
	ui.Enable->setEnabled(true);
	ui.layerBox->setEnabled(true);
	ui.layerSelect->setValue(Voxels->divisions);

	ui.labelpower->setEnabled(true); //Otherwise they stay disabled (??)
	ui.power->setEnabled(true);

	ui.Segmentation->setEnabled(false);
	ui.Isolate->setEnabled(false);
	ui.segType->setEnabled(false);

	ui.Spline->setEnabled(true);
	ui.Mesh->setEnabled(true);

	createHistogram();
}

//Creates the histogram
void MainWindows::createHistogram()
{
	if(histogram==nullptr) histogram = new QCPBars(ui.customPlot->xAxis, ui.customPlot->yAxis);
	ui.customPlot->setVisible(true);
	histogram->setPen(Qt::NoPen);
	histogram->setBrush(QColor(100, 180, 110));

	std::vector<Voxel*> cells = Voxels->getVoxels()[Voxels->divisions - 1];

	std::vector<double> data = std::vector<double>(1, 0); //QCustomPlot requires double

	//Iterate over each voxel to determine the number of voxels having each number of points
	for (auto cell = cells.begin(); cell != cells.end(); ++cell)
	{
		if ((*cell) == nullptr)
			data[0]++;
		else {
			if ((*cell)->getNumPoints() > data.size() - 1) data.resize((*cell)->getNumPoints() + 1, 0);
			data[(*cell)->getNumPoints()]++;
		}
	}

	std::vector<double> x = std::vector<double>(data.size());
	size_t maxnum = 0;

	//Rescale the histogram to the max value
	for (size_t i = 0; i < data.size(); i++) {
		x[i] = i;
		if (i > 0 && data[i] > maxnum) maxnum = data[i];
	}
	
	
	// give the axes some labels:
	ui.customPlot->xAxis->setLabel("# Points");
	ui.customPlot->yAxis->setLabel("# Voxels");
	// set axes ranges, so we see all data:
	ui.customPlot->xAxis->setRange(0, x.size());
	ui.customPlot->yAxis->setRange(0, maxnum);
	histogram->setWidthType(QCPBars::wtAbsolute);
	histogram->setWidth(3);

	QVector<double> Qdata = QVector<double>::fromStdVector(data);
	QVector<double> Qx = QVector<double>::fromStdVector(x);

	histogram->setData(Qx, Qdata, true);
	
	ui.customPlot->replot();

	//Initialize the fullscreen icon
	FullScreenIcon* FS = new FullScreenIcon(this);
	FS->setMaximumHeight(20);
	ui.gridHistogram->addWidget(FS, 0, 0, Qt::AlignTop | Qt::AlignRight);
	FSicons.push_back(FS);

	connect(FS, SIGNAL(clicked()),
		this, SLOT(histogramClicked()));
}

//When the display options buttonis clicked
void MainWindows::on_DisplayOptions_clicked()
{
	//gather the present parameters
	float background;
	float ambient;
	size_t levels;
	size_t max = 2;
	if (Voxels != nullptr) { 
		background = Voxels->background;  
		levels = Voxels->levelsRen; 
		if (Voxels->divisions != 0)  max = Voxels->divisions;
		ambient = Voxels->ambientLight;
	}
	else { background = 0.5; levels = 1; }
	std::vector<size_t> indexes(renderer->colorMap, renderer->colorMap + 8);
	//Create a display options window with the current parameters
	DisplayOptions* options = new DisplayOptions(this, renderer->lightFollow, renderer->angleView, renderer->size, background, ambient, levels, max, renderer->Box->planarThresh, indexes);
	options->exec();
	
	//If there were a change in the settings, modify them in the data structures
	if (options->change) {
		if (Voxels != nullptr) {
			Voxels->background = options->ui.background->value();
			Voxels->ambientLight = options->ui.ambient->value();
			Voxels->levelsRen = options->ui.Levels->value();
			Voxels->layer.resize(options->ui.Levels->value());
		}
		renderer->angleView = options->ui.angle->value();
		renderer->size = Vec3f(options->ui.width->value(), options->ui.height->value(), 0);
		renderer->lightFollow = options->ui.follow->isChecked();

		if (1 / (float)options->ui.planthresh->value() != renderer->Box->planarThresh) {
			renderer->Box->planarThresh = 1 / (float)options->ui.planthresh->value();
			Voxels->setSurfaceType();
		}

		QComboBox* boxes[7] = { options->ui.comboBox_1,options->ui.comboBox_2,options->ui.comboBox_3,options->ui.comboBox_4,options->ui.comboBox_5,options->ui.comboBox_6,options->ui.comboBox_7 };
		for (int i = 0; i < 7; i++) {
			renderer->colorMap[i] = boxes[i]->currentIndex();
		}
		
		renderer->setParameters();
	}
}

//Change the renderer to display the surface or the surface type
void MainWindows::on_surfaceType_clicked()
{
	ui.LayerFrame->setEnabled(false); 
	renderer->setEnable(false);
	if (renderer->surfaceType) { 
		ui.surfaceType->setText("Enable Surface Type"); 
		ui.Segmentation->setEnabled(false); 
		ui.segType->setEnabled(false);
		renderer->renderSeg = false;
		Voxels->renderSeg = false;
		legendWidget->setVisible(false);
		ui.GroupSlider->setVisible(false);
		ui.layoutIsolate->setVisible(false);
		ui.Isolate->setEnabled(false);
		Voxels->renderIsolate = false;
		ui.Segmentation->setChecked(false);
		ui.Isolate->setChecked(false);
	}
	else { 
		ui.surfaceType->setText("Disable Surface Type"); 
		ui.Segmentation->setEnabled(true); 
		legendWidget->setVisible(true);
	}
	renderer->setSurfaceType(!renderer->surfaceType);
	ui.Enable->setEnabled(!ui.Enable->isEnabled());
	ui.Enable->setChecked(false);
	
}

void MainWindows::on_Segmentation_clicked()
{
	if (ui.Segmentation->isChecked()) {
		ui.segType->setEnabled(true);
		legendWidget->setVisible(false);
		ui.Isolate->setEnabled(true);
	}
	else {
		ui.segType->setEnabled(false);
		legendWidget->setVisible(true);
		ui.Isolate->setEnabled(false);
		ui.Isolate->setChecked(false);
		ui.GroupSlider->setVisible(false);
		Voxels->renderIsolate = false;
	}
	
	renderer->renderSeg = ui.Segmentation->isChecked();
	Voxels->renderSeg = ui.Segmentation->isChecked();
	renderer->updateFrame();
}

void MainWindows::on_Isolate_clicked()
{
	if (ui.Isolate->isChecked()) {
		ui.GroupSlider->setVisible(true);
		ui.layoutIsolate->setVisible(true);
		ui.layoutIsolate->setEnabled(true);
		sliderGroup(0);
	}
	else {
		ui.GroupSlider->setVisible(false);
		ui.layoutIsolate->setVisible(false);
	}

	ui.GroupSlider->setMaximum(Voxels->groupsVoxels[Voxels->segType].size()-1);
	ui.GroupSlider->setValue(0);
	ui.sectionsType->setText(QString::number(Voxels->groupsVoxels[Voxels->segType].size()));
	Voxels->renderIsolate = ui.Isolate->isChecked();
	Voxels->renderGroup = 0;
	renderer->updateFrame();
}

void MainWindows::sliderGroup(int value) {
	Voxels->renderGroup = value;
	ui.voxelsSection->setText(QString::number(Voxels->groupsVoxels[Voxels->segType][value].size()));
	renderer->updateFrame();
}

void MainWindows::setSegType(int type)
{
	Voxels->segType = type + 1;
	if (ui.Isolate->isChecked()) {
		ui.sectionsType->setText(QString::number(Voxels->groupsVoxels[Voxels->segType].size()));
		ui.GroupSlider->setMaximum(Voxels->groupsVoxels[Voxels->segType].size() - 1);
		ui.GroupSlider->setValue(0);
		sliderGroup(0);
	}
	renderer->updateFrame();
}

//Options for the octrees
void MainWindows::on_OctreeOptions_clicked()
{

	OctreeOptions* options = new OctreeOptions(this, surfaceThreshold);
	options->exec();
	if (options->change) {
		surfaceThreshold = options->ui.variation->value();
	}
}


//When the Generate button is clicked
void MainWindows::on_Generate_clicked()
{
	if (path == "")
	{
		QMessageBox::warning(this, "Error", "Select file first");
		return;
	}

	QProgressDialog* progressBar = new QProgressDialog();
	
	progressBar->setMinimumDuration(0);
	progressBar->setRange(0, 100);
	progressBar->setCancelButton(false);
	progressBar->setWindowModality(Qt::WindowModal);
	progressBar->setValue(0);
	QLabel* label = new QLabel();
	label->setText("Extracting points from file");
	progressBar->setLabel(label);
	QCoreApplication::processEvents();

	if (Voxels != nullptr) delete Voxels;

	float x;
	float y;
	float z;
	//Create the PointCloud from the object file
	points = PointCloud(path.toStdString());
	ui.numPoints->setText(QString::number(points.numVertices));
	ui.points->setVisible(true);

	//Generate based on size
	if (ui.Size->isChecked())
	{
		x = ui.doubleSpinBox->value();
		y = ui.doubleSpinBox_2->value();
		z = ui.doubleSpinBox_3->value();
		//Create VoxelBox object
		Voxels = new VoxelBox(points, ui.MinPoints->value(), Vec3f(x, y, z), false, progressBar);
		ui.spinBox->setValue(Voxels->getCount().x);
		ui.spinBox_2->setValue(Voxels->getCount().y);
		ui.spinBox_3->setValue(Voxels->getCount().z);
		ui.layerSelect->setEnabled(false);
	}
	//Generate based on count
	if (ui.Count->isChecked())
	{
		x = ui.spinBox->value();
		y = ui.spinBox_2->value();
		z = ui.spinBox_3->value();
		//Create VoxelBox object
		Voxels = new VoxelBox(points, ui.MinPoints->value(), Vec3f(x, y, z), true, progressBar);
		ui.doubleSpinBox->setValue(Voxels->getDims().x);
		ui.doubleSpinBox_2->setValue(Voxels->getDims().y);
		ui.doubleSpinBox_3->setValue(Voxels->getDims().z);
		ui.layerSelect->setEnabled(false);
	}
	//Generate based on octrees
	if (ui.Octree->isChecked())
	{
		x = ui.spinBox_4->value();
		//Create VoxelBox object
		Voxels = new VoxelBox(points, ui.MinPoints->value(), x, surfaceThreshold, progressBar);
		ui.doubleSpinBox->setValue(Voxels->getDims().x);
		ui.doubleSpinBox_2->setValue(Voxels->getDims().y);
		ui.doubleSpinBox_3->setValue(Voxels->getDims().z);
		ui.spinBox->setValue(Voxels->getCount().x);
		ui.spinBox_2->setValue(Voxels->getCount().y);
		ui.spinBox_3->setValue(Voxels->getCount().z);
		ui.layerSelect->setEnabled(true);
		ui.layerSelect->setRange(1, Voxels->divisions);
		Voxels->currentLayer = Voxels->divisions;
	}
	initiateView();
}

void MainWindows::on_Spline_clicked()
{
	
	QDialog dialog(this);
	// Use a layout allowing to have a label next to each field
	QFormLayout form(&dialog);

	// Add some text above the fields
	form.addRow(new QLabel("Parameters"));


	QDoubleSpinBox* r = new QDoubleSpinBox(&dialog);
	r->setRange(0.0001, 0.1);
	r->setSingleStep(0.01);
	r->setDecimals(4);
	r->setValue(0.01);
	QString labelr = QString("r:");
	form.addRow(labelr, r);

	QSpinBox* N = new QSpinBox(&dialog);
	N->setRange(1, 100);
	N->setSingleStep(1);
	N->setValue(20);
	QString labelN = QString("N:");
	form.addRow(labelN, N);

	QDoubleSpinBox* step = new QDoubleSpinBox(&dialog);
	step->setRange(0.0001, 0.1);
	step->setSingleStep(0.01);
	step->setDecimals(4);
	step->setValue(0.03);
	QString labelstep = QString("Render step:");
	form.addRow(labelstep, step);

	QDoubleSpinBox* R = new QDoubleSpinBox(&dialog);
	R->setRange(0.1, 100);
	R->setSingleStep(1);
	R->setDecimals(1);
	R->setValue(2);
	QString labelL = QString("R (/Count.x):");
	form.addRow(labelL, R);

	// Add some standard buttons (Cancel/Ok) at the bottom of the dialog
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

	// Show the dialog as modal
	if (dialog.exec() == QDialog::Accepted) {
		// If the user didn't dismiss the dialog, do something with the fields
		Voxels->BSpline(N->value(), r->value(), R->value(), step->value());
		displayMesh(1);
	}
}

void MainWindows::on_Mesh_clicked()
{
	Voxels->MarchingCubes();

	displayMesh(0);
}

void MainWindows::displayMesh(unsigned char type) 
{
	QWidget* wdg = new QWidget;
	QVBoxLayout* boxLayout = new QVBoxLayout(wdg); // Main layout of widget

	QMenuBar* menuBar = new QMenuBar();
	QMenu* fileMenu = new QMenu("Export");
	menuBar->addMenu(fileMenu);
	fileMenu->addAction(".obj");
	fileMenu->addAction("Capture .jpg");
	if (type == 0)
		connect(fileMenu, SIGNAL(triggered(QAction*))
			, SLOT(ExportMesh(QAction*)));
	else if (type == 1)
		connect(fileMenu, SIGNAL(triggered(QAction*))
			, SLOT(ExportSpline(QAction*)));

	wdg->layout()->setMenuBar(menuBar);

	if (type == 0) {
		if (meshwindow != nullptr)delete meshwindow;
		meshwindow = new meshRender(renderer, Voxels, 0);
		wdg->layout()->addWidget(meshwindow);
	}
	else if (type == 1) {
		if (meshSplinewindow != nullptr)delete meshSplinewindow;
		meshSplinewindow = new meshRender(renderer, Voxels, 1);
		wdg->layout()->addWidget(meshSplinewindow);
	}


	
	wdg->resize(500, 500);
	wdg->show();
	wdg->setAttribute(Qt::WA_QuitOnClose, false);
}
