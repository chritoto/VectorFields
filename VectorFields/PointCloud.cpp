#include "PointCloud.h"

#define TINYPLY_IMPLEMENTATION
#include "tinyply.h"
#include "stl_reader.h"

PointCloud::PointCloud(const std::string& filepath) 
{
    if(filepath.compare(filepath.length() - 3, 3, "ply")==0)
        read_ply_file(filepath);
    else if(filepath.compare(filepath.length() - 3, 3, "stl") == 0)
        read_stl_file(filepath);
    else
        return;

    shift_to_origin();
    Rectify();
}

//Based on tinyPLY example files
void PointCloud::read_ply_file(const std::string& filepath)
{

    std::unique_ptr<std::istream> file_stream;
    std::vector<uint8_t> byte_buffer;

    try
    {
       
        byte_buffer = read_file_binary(filepath);
        file_stream.reset(new memory_stream((char*)byte_buffer.data(), byte_buffer.size()));
         
        if (!file_stream || file_stream->fail()) throw std::runtime_error("file_stream failed to open " + filepath);

        file_stream->seekg(0, std::ios::end);
        const float size_mb = file_stream->tellg() * float(1e-6);
        file_stream->seekg(0, std::ios::beg);
        
        tinyply::PlyFile file;
        file.parse_header(*file_stream);

        std::cout << "\t[ply_header] Type: " << (file.is_binary_file() ? "binary" : "ascii") << std::endl;
        for (const auto& c : file.get_comments()) std::cout << "\t[ply_header] Comment: " << c << std::endl;
        for (const auto& c : file.get_info()) std::cout << "\t[ply_header] Info: " << c << std::endl;

        for (const auto& e : file.get_elements())
        {
            std::cout << "\t[ply_header] element: " << e.name << " (" << e.size << ")" << std::endl;
            for (const auto& p : e.properties)
            {
                std::cout << "\t[ply_header] \tproperty: " << p.name << " (type=" << tinyply::PropertyTable[p.propertyType].str << ")";
                if (p.isList) std::cout << " (list_type=" << tinyply::PropertyTable[p.listType].str << ")";
                std::cout << std::endl;
            }
        }
        
        // Because most people have their own mesh types, tinyply treats parsed data as structured/typed byte buffers. 
        // See examples below on how to marry your own application-specific data structures with this one. 
        std::shared_ptr<tinyply::PlyData> vertices, normals, colors, texcoords, faces, tripstrip;

        // The header information can be used to programmatically extract properties on elements
        // known to exist in the header prior to reading the data. For brevity of this sample, properties 
        // like vertex position are hard-coded: 
        try { vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        file.read(*file_stream);
        

        // Example One: converting to your own application types
        
        const size_t numVerticesBytes = vertices->buffer.size_bytes();
        std::vector<float3> verts(vertices->count);
        std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);
        for (auto point = verts.begin(); point != verts.end(); ++point) //iterate to assign points
        {
            points.push_back(Vec3f(*point));
        }

        if (vertices)   qDebug() << "Read" << vertices->count << "vertices" ;
        numVertices = vertices->count;
        

    }
    catch (const std::exception & e)
    {
        std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
    }
}

//Based on stl_reader example file
void PointCloud::read_stl_file(const std::string& filepath)
{
    try
    {

        stl_reader::StlMesh <float, unsigned int> mesh(filepath);

        numVertices = mesh.num_vrts();
        const float* coords = mesh.raw_coords();

        for (int i = 0; i < numVertices; i++)
        {
            points.push_back(Vec3f(coords[i * 3], coords[i * 3 + 1], coords[i * 3 + 2]));
        }

        qDebug() << "Read" << numVertices << "vertices";


    }
    catch (std::exception & e) 
    {
        std::cout << e.what() << std::endl;
    }
}

//bring centroid to origin
int PointCloud::shift_to_origin()
{
    //if no points
    if (points.size() == 0) return 1;

    //initialize
    min_x = min_y = min_z = max_x = max_y = max_z = 0;
    double sum_x = 0, sum_y = 0, sum_z = 0;
    float x, y, z;

    for (auto point = points.begin(); point != points.end(); ++point) //iterate to find average and min max
    {
        x = point->x;
        y = point->y;
        z = point->z;
        sum_x += x;
        sum_y += y;
        sum_z += z;

        if (x < min_x) min_x = x;
        if (y < min_y) min_y = y;
        if (z < min_z) min_z = z;

        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
        if (z > max_z) max_z = z;
    }

    average_x = sum_x / points.size();
    average_y = sum_y / points.size();
    average_z = sum_z / points.size();
        
    for (auto point = points.begin(); point != points.end(); ++point) //iterate to shift min to 0
    {
        point->x = point->x - average_x;
        point->y = point->y - average_y;
        point->z = point->z - average_z;
    }

    return 0;
}

//returns the bound of the points on each axis [min,max]
std::vector<Vec3f> PointCloud::getBounds()
{
    min_x = min_y = min_z = max_x = max_y = max_z = 0;
    for (auto point = points.begin(); point != points.end(); ++point) //iterate to find min max
    {

        if (point->x < min_x) min_x = point->x;
        if (point->y < min_y) min_y = point->y;
        if (point->z < min_z) min_z = point->z;

        if (point->x > max_x) max_x = point->x;
        if (point->y > max_y) max_y = point->y;
        if (point->z > max_z) max_z = point->z;
    }
    if (abs(min_x) < abs(max_x))absMax_x = abs(min_x);
    else absMax_x = abs(max_x);
    if (abs(min_y) < abs(max_y))absMax_y = abs(min_y);
    else absMax_y = abs(max_y);
    if (abs(min_z) < abs(max_z))absMax_z = abs(min_z);
    else absMax_z = abs(max_z);
    std::vector<Vec3f> bounds;
    bounds.push_back(Vec3f( min_x-0.0001, min_y - 0.0001, min_z - 0.0001)); //substract to avoid precison issues
    bounds.push_back(Vec3f( max_x, max_y, max_z ));
    return bounds;
}

//Rotate the points based on the principal variation axis
void PointCloud::Rectify()
{
    Eigen::MatrixXd sumPoints = Eigen::MatrixXd::Zero(3, 3);
    Eigen::MatrixXd Covariance = Eigen::MatrixXd::Zero(3, 3);
    Vec3f sum(0, 0, 0);
    for (auto point = points.begin(); point != points.end(); ++point) 
    {
        sumPoints += point->MulTranspose();
        sum += *point;
    }
    Vec3f averagePoints = sum / points.size();

    Covariance = sumPoints / points.size() - averagePoints.MulTranspose();
    Eigen::EigenSolver<Eigen::MatrixXd> es(Covariance);

    Eigen::MatrixXd V = es.eigenvectors().real();

    for (auto point = points.begin(); point != points.end(); ++point)
    {
        Vec3f newpoint = point->Mul(V);
        point->x = newpoint.x;
        point->y = newpoint.y;
        point->z = newpoint.z;
    }
}

//Make sure every point falls inside the most extreme voxels' centers (for marching cubes)
void PointCloud::WhiteSpace(const Vec3f& p_dims)
{
    
    float maxDim = p_dims.x;
    float max = absMax_x;
    if (p_dims.y > maxDim) { maxDim = p_dims.y; max = absMax_y; }
    if (p_dims.z > maxDim) { maxDim = p_dims.z; max = absMax_z; }

    for (auto point = points.begin(); point != points.end(); ++point)
    {
        *point *= (max - maxDim) / max;
    }
    
}
