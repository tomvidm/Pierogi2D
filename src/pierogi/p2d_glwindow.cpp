#include "p2d_glwindow.hpp"

namespace p2d {
    // TODO: Break up into smaller functions
    // TODO: Fix error handling
    GLWindow::GLWindow() {
        ;
    } // RenderWindow

    GLWindow::~GLWindow() {
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_Quit();
    } // ~RenderWindow

    bool GLWindow::initSDL() {
        std::cout << "SDL_Init" << std::endl;
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }
        glewExperimental = GL_TRUE;
        return true;
    } // initSDL

    bool GLWindow::initWindow() {
        std::cout << "SDL_CreateWindow" << std::endl;
        sdlWindowPtr = SDL_CreateWindow(
            "Default Window",
            500, 100,
            800, 600,
            SDL_WINDOW_OPENGL
        ); // SDL_CreateWindow

        if (sdlWindowPtr == nullptr) {
            SDL_DestroyWindow(sdlWindowPtr);
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        } // if
        return true;
    } // initWindow

    bool GLWindow::initOpenGL() {
        std::cout << "Init opengl..." << std::endl;
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_CreateContext(sdlWindowPtr);
        glewInit();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( 0.0, 800, 600, 0.0, 1.0, -1.0 );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        glClearColor(0.5, 1.0, 0.5, 1.0);
        glClear ( GL_COLOR_BUFFER_BIT );
        flip();
        GLenum error = glGetError();
        if( error != GL_NO_ERROR )
        {
            printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
            return false;
        }
        return true;
    } // initOpenGL

    void GLWindow::flip() const {
        SDL_GL_SwapWindow(sdlWindowPtr);
    } // flip

    void GLWindow::render() const {
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(800.0/2.0, 600.0 / 2.0, 0.0);

        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f ); glVertex2f( -50.f, -50.f );
            glColor3f( 0.f, 1.f, 0.f ); glVertex2f(  50.f, -50.f );
            glColor3f( 0.f, 0.f, 1.f ); glVertex2f(  50.f,  50.f );
            glColor3f( 1.f, 0.f, 1.f ); glVertex2f( -50.f,  50.f );
        glEnd();

        flip();
    }
} // namespace p2d