#include "Application/Game.h"


int main()
{
    App::Application* app = new App::Application;
    app->run();
    delete app;
}