#include "Game/Game.h"



int main()
{
    App::Application* app = new App::Application();
    app->run();
    app->shutdown();
    delete app;
}