#include "Viewer.h"
#include <vector>
#include <set>
#include "Renderer.h"
#include "RefPtr.h"
#include "GraphicContext.h"
#include "Camera.h"


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
        std::set<GraphicContext*> contexts;
        for(auto& renderer : d->renderers){
            contexts.insert(renderer->getContext());
        }

        for(auto& renderer : d->renderers){
            contexts.insert(renderer->getContext());
        }
    }

    void Viewer::addRenderer(Renderer *renderer)
    {
        d->renderers.push_back(renderer);
    }
}