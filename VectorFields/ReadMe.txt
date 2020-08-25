Vector Field visualization application.

Start here to get a global idea of the functioning of the program
Files and classes:

** BEFORE running the program ***
VectorFields(the project)>propreties>All configuration:
	-VC++ Directories> Include>  make sure it points to the right folder on your system (where Eigen is located)
	-Qt project settings>Set the Qt installation to your Qt installation
*********************************

** Main.cpp **
-Launches the main window
**************

** MainWindows **
-Interacts with the application's main window and processes the actions
-Initiatse and manages the objects
*****************

** PointCloud **
-Import points from STL or PLY files (using stl_reader.h and tinyply.h)
-Transformation on the points (shift, rotate)
-Provides the bounds of the points on each axis
****************

** Voxel **
-Data structure of one Voxel
-Has a center and dimensions
-Computes the normal, surface variation and vector of the closest point from a given series of points falling in the Voxel
***********

** VoxelBox **
-Data structure of all the Voxels of the object
-Contains std::vector of pointers to the Voxels which are accessed as [x * count.y * count.z + y * count.z + z]
-One main functions:
	-Construction
		-Computes the center of each voxel and the points of the pointcloud falling in each
		-Create each voxels
		-Determines surface type of each voxel
-Can be initialized with an octree structure
***************

** RendererThread **
-QtWidget creating an image
-Is linked to a VoxelBox
-Sets the camera origin and direction
-Computes the direction of the ray for each pixel and calls RayCaster for the value
-Uses mouse input
**************

** RayCaster **
-Rendering surface:
	-Input direction and origin of ray and light orientation
	-Travel through the voxels to determine the surface observed
	-Outputs intensity value
-Rendering surface type
	-Input direction and origin of ray and light orientation
	-Travel through the voxels to determine the surface observed
	-Outputs surface type
******************

** MeshRenderer **
-Creates an openGL window
-Geometry from the VoxelBox variables:
	-For the marchingcubes
		-indicesMesh
		-normalsMesh
	-For the spline:
		-indicesSpline
		-normalsSpline
******************

** Layers **
-QtWidget creating an image
-Is linked to a VoxelBox
-Displays a cross-section of the VoxelBox
-Can display multiple attributes of each Voxel
-Uses checkboxes and a slider interfaced through the main window to decide the cross-section layer displayed
-The color of the display is linked to its scale
************

** Scale **
-QtWidget creating an image
-Created a gradient image coresponding to the colors of its linked layer
-Can be linear or non- linear and tint or grey-scale
***********

** DisplayOptions **
-A window to set theparameters of the renderer
-Is linked to Renderer object and VoxelBox object through the main window
********************

** OctreeOptions **
-A window to further set octree parameters before the generation of the data
*******************

** newWindow **
-Serves to copy a widget of the main window to a new window
-Used to display renderer and histogram in full screen
***************

** FullScreenIcon **
-QtWidget of a fullscreen icon
-Used to create a newWindow
-Needs to be a class to display a custom image over other widgets
********************

** qcustomplot **
-QtWidget used to create an histogram
-https://www.qcustomplot.com
*****************

** Vec3 **
-Essential Vector structure used to store points, vectors and other 3x1 vectors
-Dot and cross product (*, %)
-Specialized functions for particular cases
**********

** Util **
-File working with tinyPLY to define structs
-Also used to include further useful files
**********