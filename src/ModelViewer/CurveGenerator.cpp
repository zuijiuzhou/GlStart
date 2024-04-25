
#include "CurveGenerator.h"
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Point>

#include <Standard_Handle.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_HArray1OfVec.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <TColStd_HArray1OfReal.hxx>

namespace ModelViewer
{
    osg::MatrixTransform *createBSpline(std::vector<osg::Vec3d> &ctrl_points, std::vector<osg::Vec3d> &tangents)
    {
        auto geod = new osg::Geode();
        Handle(TColgp_HArray1OfPnt) pnts = new TColgp_HArray1OfPnt(1, ctrl_points.size());
        Handle(TColStd_HArray1OfReal) pnt_params = new TColStd_HArray1OfReal(1, ctrl_points.size());
        Handle(TColgp_HArray1OfVec) tans = new TColgp_HArray1OfVec(1, tangents.size());
        Handle(TColStd_HArray1OfBoolean) tan_flags = new TColStd_HArray1OfBoolean(1, tangents.size());

        for (int i = 1; i <= ctrl_points.size(); i++)
        {
            auto &pt = ctrl_points[i - 1];
            (*pnts).SetValue(i, gp_Pnt(pt.x(), pt.y(), pt.z()));
            (*pnt_params).SetValue(i, i - 1);
        }

        for (int i = 1; i <= tangents.size(); i++)
        {
            auto &tan = tangents[i - 1];
            (*tans).SetValue(i, gp_Vec(tan.x(), tan.y(), tan.z()));
            (*tan_flags).SetValue(i, true);
        }
        GeomAPI_Interpolate interpolate(pnts, pnt_params, false, 0.01);
        if (ctrl_points.size() == tangents.size())
        {
            interpolate.Load(*tans, tan_flags, false);
        }
        else if (tangents.size() == 2)
        {
            interpolate.Load(tans->First(), tans->Last(), false);
        }
        interpolate.Perform();
        if (interpolate.IsDone())
        {
            auto curve = interpolate.Curve();
            GeomAdaptor_Curve adaptor(curve, curve->FirstParameter(), curve->LastParameter());
            GCPnts_UniformAbscissa spliter(adaptor, 1.);

            auto nb_pnts = spliter.NbPoints();
            auto vertices = new osg::Vec3Array();
            vertices->reserve(nb_pnts);
            for (int i = 1; i <= nb_pnts; i++)
            {
                auto param = spliter.Parameter(i);
                gp_Pnt posi;
                gp_Vec tangent;
                adaptor.D1(param, posi, tangent);
                vertices->push_back(osg::Vec3(posi.X(), posi.Y(), posi.Z()));
            }
            auto colors = new osg::Vec4Array();
            {
                colors->push_back(osg::Vec4(1, 0, 0, 1));
            }
            auto geom = new osg::Geometry();
            geom->setVertexArray(vertices);
            geom->setColorArray(colors, osg::Array::BIND_OVERALL);
            geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, nb_pnts));
            geod->addDrawable(geom);
        }

        {
            auto vertices = new osg::Vec3Array();
            for(auto& pt : ctrl_points){
                vertices->push_back(pt);
            }
            auto colors = new osg::Vec4Array();
            {
                colors->push_back(osg::Vec4(1, 1, 0, 1));
            }
            auto geom = new osg::Geometry();
            geom->setVertexArray(vertices);
            geom->setColorArray(colors, osg::Array::BIND_OVERALL);
            geom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, ctrl_points.size()));
            geom->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(4));
            geod->addDrawable(geom);
        }

        auto model = new osg::MatrixTransform();
        model->addChild(geod);
        model->getOrCreateStateSet()->setMode(GL_LIGHTING, 0);
        return model;
    }
}