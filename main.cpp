#include <iostream>
#include "./application.h"

int main(int argc, char **argv)
{
    Application *app = new Application(argc, argv);
    app->run();
    return 0;
}