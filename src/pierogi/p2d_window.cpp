#include "p2d_window.hpp"

namespace p2d {
    // TODO: Break up into smaller functions
    // TODO: Fix error handling
    RenderWindow::RenderWindow() {
        initSDL();
        initWindow();
        initGLContext();
        initGL();
    } // RenderWindow

    RenderWindow::~RenderWindow() {
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_Quit();
    } // ~RenderWindow

    bool RenderWindow::initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    } // initSDL

    bool RenderWindow::initWindow() {
        sdlWindowPtr = SDL_CreateWindow(
            "Default Window",
            900, 100,
            640, 480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );

        if (sdlWindowPtr == nullptr) {
            SDL_DestroyWindow(sdlWindowPtr);
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        } else {
            if (SDL_GL_SetSwapInterval(1) < 0) {
                std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
            }
        }
        return true;
    } // initWindow

    bool RenderWindow::initGLContext() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        // SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        glContext = SDL_GL_CreateContext(sdlWindowPtr);
        if (glContext == NULL) {
            std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        }
        glewInit();
        return true;
    } // initGLContext

    bool RenderWindow::initGL() {
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        glClearColor( 0.f, 0.f, 0.f, 0.5f );

        return true;
    } // initGL

    void RenderWindow::renderDummy() {
        glClear( GL_COLOR_BUFFER_BIT );
        glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f( 0.5f, -0.5f );
        glVertex2f( 0.5f, 0.5f );
        glVertex2f( -0.5f, 0.5f );
        glEnd();
    }

} // namespace p2d