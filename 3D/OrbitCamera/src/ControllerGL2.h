///////////////////////////////////////////////////////////////////////////////
// ControllerGL2.h
// ===============
// Derived Controller class for OpenGL window
// It is the controller of OpenGL rendering window. It initializes DC and RC,
// when WM_CREATE called, then, start new thread for OpenGL rendering loop.
//
// When this class is constructed, it gets the pointers to model and view
// components.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gamil.com)
// CREATED: 2016-05-29
// UPDATED: 2021-03-10
///////////////////////////////////////////////////////////////////////////////

#ifndef WIN_CONTROLLER_GL_2_H
#define WIN_CONTROLLER_GL_2_H

#include "Controller.h"
#include "ViewGL.h"
#include "ModelGL.h"


namespace Win
{
    class ControllerGL2 : public Controller
    {
    public:
        ControllerGL2(ModelGL* model, ViewGL* view);
        ~ControllerGL2() {};

        void setRC(HGLRC rc, int pixelFormat)       { hglrc = rc; this->pixelFormat = pixelFormat; }

        LRESULT destroy();                              // for WM_DESTROY
        LRESULT create();                               // create RC for OpenGL window and start new thread for rendering
        LRESULT paint();
        LRESULT size(int w, int h, WPARAM wParam);      // for WM_SIZE: width, height, type(SIZE_MAXIMIZED...)

    private:
        ModelGL* model;                             // pointer to model component
        ViewGL* view;                               // pointer to view component
        HGLRC hglrc;
        int pixelFormat;
    };
}

#endif
