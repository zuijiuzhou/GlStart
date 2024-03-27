#include "BrepLoader.h"
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/PolygonMode>
#include <osg/PolygonOffset>
#include <osgUtil/SmoothingVisitor>

#include <STEPControl_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <TopTools.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>

#include "ModelDefs.h"

namespace ModelViewer{
    osg::MatrixTransform* BrepLoader::loadStpFile(const std::string& file){
        STEPControl_Reader reader;
        auto status = reader.ReadFile(file.data());
        if(status != IFSelect_RetDone) return nullptr;
        reader.TransferRoots();
        TopoDS_Shape shape;
        if(reader.NbShapes() > 1){
            BRep_Builder builder;
            TopoDS_Compound compound;
            builder.MakeCompound(compound);
            for(int i = 0; i < reader.NbShapes(); i++){
                builder.Add(compound, reader.Shape(i));
            }
            shape = compound;
        }
        else shape = reader.OneShape();

        std::set<int> face_edge_hashes;
        std::set<int> all_edge_indices;

        TopTools_IndexedMapOfShape face_map;
        TopTools_IndexedMapOfShape edge_map;

        TopExp::MapShapes(shape, TopAbs_FACE, face_map);
        TopExp::MapShapes(shape, TopAbs_EDGE, edge_map);

        for(int i = 1; i <= face_map.Extent(); i++){
            TopExp_Explorer exp;
            for(exp.Init(face_map(i), TopAbs_EDGE); exp.More(); exp.Next()){
                face_edge_hashes.insert(exp.Current().HashCode(INT_MAX));
            }
        }
        for(int i = 1; i <= edge_map.Extent(); i++){
            all_edge_indices.insert(i);
        }

        auto face_geod = new osg::Geode();
        auto edge_geod = new osg::Geode();
        auto face_colors = new osg::Vec4Array();
        auto edge_colors = new osg::Vec4Array();
        face_colors->push_back(osg::Vec4(0.88f, 0.88f, 0.88f, 1.f));
        edge_colors->push_back(osg::Vec4(0.36f, 0.36f, 0.36f, 1.f));

        IMeshTools_Parameters params;
        params.Angle = 0.52;
        params.MinSize = 1e-4;
        params.InParallel = true;
        params.Relative = true;
        params.InternalVerticesMode = true;
        params.ControlSurfaceDeflection = true;
        params.ForceFaceDeflection = false;
        params.CleanModel = true;
        params.AllowQualityDecrease = true;
        params.AdjustMinSize = true;

        BRepMesh_IncrementalMesh im(shape, params);
        im.Perform();

        for(int i = 1; i <= face_map.Extent(); i++){
            auto& face = TopoDS::Face(face_map(i));
            TopLoc_Location loc;
            auto mesh = BRep_Tool::Triangulation(face, loc);
            if(mesh.IsNull()) continue;

            auto vertices = new osg::Vec3Array();
            auto indices = new osg::DrawElementsUInt(GL_TRIANGLES);

            for(auto i = 1; i <= mesh->NbNodes(); i++){
                auto pnt = mesh->Node(i);
                pnt.Transform(loc.Transformation());
                vertices->push_back(osg::Vec3(pnt.X(), pnt.Y(), pnt.Z()));
            }
            for(auto i = 1; i <= mesh->NbTriangles(); i++){
                Standard_Integer v1, v2, v3;
                const auto& tri = mesh->Triangle(i);
                tri.Get(v1, v2, v3);
                if(face.Orientation() == TopAbs_REVERSED) 
                    std::swap(v1, v2);
                indices->push_back(v1 - 1);
                indices->push_back(v2 - 1);
                indices->push_back(v3 - 1);
            }

            auto face_geom = new osg::Geometry();
            face_geom->setColorArray(face_colors, osg::Array::BIND_OVERALL);
            face_geom->setVertexArray(vertices);
            face_geom->addPrimitiveSet(indices);
            osgUtil::SmoothingVisitor().smooth(*face_geom);
            face_geod->addDrawable(face_geom);

            TopExp_Explorer exp(face, TopAbs_EDGE);
            for(;exp.More(); exp.Next()){
                auto edge = TopoDS::Edge(exp.Current());
                auto edge_index = edge_map.FindIndex(edge);
                if(!all_edge_indices.contains(edge_index))
                    continue;
                all_edge_indices.erase(edge_index);
                auto polygon = BRep_Tool::PolygonOnTriangulation(edge, mesh, loc);
                if(polygon.IsNull()) 
                    continue;
                auto& nodes = polygon->Nodes();
                auto edge_geom = new osg::Geometry();

                #if true
                vertices = new osg::Vec3Array();
                for(int i = nodes.Lower(); i <= nodes.Upper(); i++){
                    auto pnt = mesh->Node(nodes(i));
                    pnt.Transform(loc.Transformation());
                    vertices->push_back(osg::Vec3(pnt.X(), pnt.Y(), pnt.Z()));
                }
                edge_geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vertices->size()));
                #else
                // 有问题
                indices = new osg::DrawElementsUInt(GL_LINE_STRIP);
                for(auto i : nodes){
                    indices->push_back(i);
                }
                edge_geom->addPrimitiveSet(indices);
                #endif
                
                edge_geom->setVertexArray(vertices);
                edge_geom->setColorArray(edge_colors, osg::Array::BIND_OVERALL);
                edge_geod->addDrawable(edge_geom);
            }
        }
        
        edge_geod->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(1.0f), 1);
        edge_geod->getOrCreateStateSet()->setMode(GL_LIGHTING, 0);
        face_geod->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonOffset(2.f, 2.f), 1);

        auto root = new osg::MatrixTransform();
        root->addChild(face_geod);
        root->addChild(edge_geod);

        setPipelineMask(edge_geod, PM_FixedShading);
        setPipelineMask(face_geod, PM_DeferredScene);
        // setPipelineMask(root, PM_DeferredScene);

        return root;
    }
}
