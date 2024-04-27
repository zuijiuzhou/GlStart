#include "SdlViewer.h"
#include <iostream>
#include <functional>
#include <memory>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "Renderer.h"
#include "Camera.h"
#include "CameraManipulator.h"
#include "UIEvent.h"
#include "RefPtr.h"
#include "RenderContext.h"

namespace AnyRenderer
{
    namespace
    {
        class SdlRenderContext : public RenderContext
        {
        public:
            SdlRenderContext(SDL_Window *wnd, SDL_GLContext ctx, Camera *cam) : RenderContext(cam), sdl_wnd_(wnd), sdl_ctx_(ctx)
            {

                sdl_wnd_ = wnd;
                sdl_ctx_ = ctx;
            }

        public:
            virtual void makeCurrent() override
            {
                SDL_GL_MakeCurrent(sdl_wnd_, sdl_ctx_);
            }

        private:
            SDL_Window *sdl_wnd_;
            SDL_GLContext sdl_ctx_;
        };
    }

    struct SdlViewer::Data
    {
        RefPtr<Renderer> renderer;
        RefPtr<CameraManipulator> cm;
        RefPtr<RenderContext> ctx;
        SDL_Window *sdl_wnd = nullptr;
        SDL_GLContext sdl_ctx = nullptr;
        glm::vec2 cursor_pt;
        bool is_initialized = false;
    };

    SdlViewer::SdlViewer() : d(new Data())
    {
    }

    SdlViewer::~SdlViewer()
    {
        delete d;
    }

    void SdlViewer::initialize()
    {
        if (d->is_initialized)
            return;
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw std::exception("SDL init failed");
        }

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        auto w = 800, h = 600;

        auto *sdl_wnd = SDL_CreateWindow("SdlViewer", 0, 0, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (sdl_wnd == NULL)
        {
            throw std::exception("Unable to create SDL window");
        }

        SDL_SysWMinfo sdlInfo;
        SDL_VERSION(&sdlInfo.version);
        SDL_GetWindowWMInfo(sdl_wnd, &sdlInfo);

        auto sdl_ctx = SDL_GL_CreateContext(sdl_wnd);
        if (sdl_ctx == NULL)
        {
            SDL_DestroyWindow(sdl_wnd);
            SDL_Quit();
            throw std::exception("Unable to create SDL context");
        }

        SDL_GL_SetSwapInterval(0);
        SDL_GL_MakeCurrent(sdl_wnd, sdl_ctx);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            SDL_GL_DeleteContext(sdl_ctx);
            SDL_DestroyWindow(sdl_wnd);
            SDL_Quit();
            throw std::exception("GLAD init failed");
        }


        auto renderer = new Renderer();
        auto cam = renderer->getCamera();
        auto cm = new StandardCameraManipulator(cam);
        auto ctx = new SdlRenderContext(sdl_wnd, sdl_ctx, cam);
        renderer->setContext(ctx);

        cam->setViewport(0., 0., w, h);
        cam->setClearDepth(1.0);
        cam->setClearStencil(1);
        cam->setClearColor(glm::vec4(0., 0., 0., 1.));
        cam->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_PROGRAM_POINT_SIZE);
        // glEnable(GL_CULL_FACE);
        glDisable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glDepthFunc(GL_LESS);

        renderer->initialize();

        d->renderer = renderer;
        d->cm = cm;
        d->sdl_wnd = sdl_wnd;
        d->sdl_ctx = sdl_ctx;
        d->ctx = ctx;
        d->is_initialized = true;
    }

    bool SdlViewer::isInitialized() const
    {
        return d->is_initialized;
    }

    Renderer *SdlViewer::getRenderer() const
    {
        return d->renderer.get();
    }

    void SdlViewer::run()
    {
        SDL_ShowWindow(d->sdl_wnd);
        SDL_GL_MakeCurrent(d->sdl_wnd, d->sdl_ctx);
        while (true)
        {
            d->renderer->frame();
             
            SDL_GL_SwapWindow(d->sdl_wnd);
        }
    }
}