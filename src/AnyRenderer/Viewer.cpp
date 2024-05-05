#include "Viewer.h"
#include <vector>
#include <map>
#include "Renderer.h"
#include "RefPtr.h"
#include "GraphicContext.h"
#include "Camera.h"
#include "CameraManipulator.h"

namespace AnyRenderer
{
    struct Viewer::Data
    {
        std::vector<RefPtr<Renderer>> renderers;
    };

    Viewer::Viewer() : d(new Data())
    {
    }

    void Viewer::frame()
    {
        std::map<GraphicContext*, std::vector<Renderer*>> ctxs;
        for (auto &renderer : d->renderers)
        {
            auto ctx = renderer->getContext();
            auto& rs = ctxs[ctx];
            rs.push_back(renderer.get());
        }
        
        for(auto& kv : ctxs){
            auto ctx = kv.first;
            auto renderers = kv.second;
            auto events = ctx->getEventQueue();
            auto s= events->size();
            if(s > 1){
                printf("\n%i", s);
            }
            while (auto e = events->pop())
            {
                for(auto r : renderers){
                    auto cm = r->getCameraManipulator();
                    if(cm){
                        cm->handleEvent(e);
                    }
                }
            }
        }

        for (auto &renderer : d->renderers)
        {
            renderer->render();
        }
    }

    void Viewer::addRenderer(Renderer *renderer)
    {
        d->renderers.push_back(renderer);
    }

    int Viewer::getNbRenderers() const
    {
        return d->renderers.size();
    }

    Renderer *Viewer::getRendererAt(int idx) const
    {
        return d->renderers.at(idx).get();
    }
}