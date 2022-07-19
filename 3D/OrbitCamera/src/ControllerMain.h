///////////////////////////////////////////////////////////////////////////////
// ControllerMain.h
// ================
// Derived Controller class for main window
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2016-05-28
// UPDATED: 2021-03-10
///////////////////////////////////////////////////////////////////////////////

#ifndef WIN_CONTROLLER_MAIN_H
#define WIN_CONTROLLER_MAIN_H

#include "Controller.h"

namespace Win
{
    class ControllerMain :public Controller
    {
    public:
        ControllerMain();
        ~ControllerMain() {};

        void setGLHandles(HWND h1, HWND h2)         { glHandle1 = h1; glHandle2 = h2; }
        void setFormHandle(HWND handle)             { formHandle = handle; }

        LRESULT command(int id, int cmd, LPARAM msg);   // for WM_COMMAND
        LRESULT close();                                // for WM_CLOSE
        LRESULT create();                               // for WM_CRERATE
        LRESULT destroy();                              // for WM_DESTROY
        LRESULT size(int w, int h, WPARAM wParam);      // for WM_SIZE: width, height, type(SIZE_MAXIMIZED...)

    private:
        HWND glHandle1;                             // handle of gl window #1
        HWND glHandle2;                             // handle of gl window #2
        HWND formHandle;                            // handle of form dialog

    };
}

#endif
