
#define WEBGPU_CPP_IMPLEMENTATION

#include <stdio.h>
#include <iostream>
#include <vector>
#include <webgpu/webgpu.hpp>
#include "./src/Application.h"
#include "./src/ComputeConsoleApplication.h"


//#define RENDER_APP = 1;
int main(int, char**) {
#ifdef RENDER_APP
    Application *app = Application::GetInstance();
    if (!app->Initialize())
    {
        return 1;
    }

    while(app->IsRunning())
    {
        app->MainLoop();
    }
#else
    ComputeConsoleApplication * app = ComputeConsoleApplication::GetInstance();
    if (!app->Initialize()) 
    {
        return 1;
    }
    app->MainCompute();
#endif
    return 0;
};
