/*
    file: main.cpp
    written by Elias Geiger
*/

#include "Application.h"

int main(int argc, char **argv)
{
    Core::Application app;

    // pass cmd arguments to application class
    for(int i = 1; i < argc; i++) {
        std::string cmd_arg;
        cmd_arg.assign(argv[i], argv[i] + strlen(argv[i]));
        app.AddLaunchArgument(cmd_arg);
    }

    bool result = app.Init();
    if(!result) {
        std::cout << "Initialization failed! Exit now. \n";
        return EXIT_FAILURE;
    }

    std::cout << "Initialization complete. Start main loop ... \n";

    app.Run();

    std::cout << "Exit now \n";

    return EXIT_SUCCESS;
}