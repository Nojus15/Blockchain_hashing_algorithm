#include "Application.h"

Application::Application(int argc, char **argv)
{
    if (argc > 1)
    {
        this->argc = argc;
        this->argv = argv;
    }
}
void Application::run()
{
    try
    {
        findMode();
        processMode();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void Application::processMode()
{
    switch (this->mode)
    {
    case AppMode::GenFile:
        if (this->argc != 4)
            throw std::invalid_argument("Invalid argument: --genFile used incorrectly");
        Generator gen;
        gen.genFile(argv[2], std::atoi(argv[3]));
        break;
    case AppMode::HashFile:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --hashFile used incorrectly");
        this->text = file.readFile(argv[2]).str();
        cout << hasher.hashString(this->text, true) << endl;
        break;
    case AppMode::HashLine:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --hashLine used incorrectly");
        this->text = argv[2];
        cout << hasher.hashString(this->text, true) << endl;
        break;
    case AppMode::TestCollisions:
        if (this->argc != 5)
            throw std::invalid_argument("Invalid argument: --testCollisions used incorrectly");
        {
            int count = std::atoi(this->argv[2]);
            int symbolCount = std::atoi(this->argv[3]);
            string resFileName = this->argv[4];
            tester.runCollisionTest(count, symbolCount, resFileName);
        }
        break;
    case AppMode::TestSpeed:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --testSpeed used incorrectly");
        {
            int symbolCount = std::atoi(this->argv[2]);
            tester.runSpeedTest(symbolCount);
        }
        break;
    case AppMode::TestCollisionsByPairs:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --testCollisionsByPairs used incorrectly");
        {
            string resFileName = this->argv[2];
            tester.runCollisionTestByPairs(resFileName);
        }
        break;
    default:
        break;
    }
}

void Application::findMode()
{
    string modeArg = argv[1];
    if (modeArg == "")
    {
        throw std::invalid_argument("Invalid command line argument");
        return;
    }

    if (modeArg == "--genFile")
    {
        this->mode = AppMode::GenFile;
        return;
    }

    if (modeArg == "--hashFile")
    {
        this->mode = AppMode::HashFile;
        return;
    }
    if (modeArg == "--hashLine")
    {
        this->mode = AppMode::HashLine;
        return;
    }
    if (modeArg == "--testCollisions")
    {
        this->mode = AppMode::TestCollisions;
        return;
    }
    if (modeArg == "--testSpeed")
    {
        this->mode = AppMode::TestSpeed;
        return;
    }
    if (modeArg == "--testCollisionsByPairs")
    {
        this->mode = AppMode::TestCollisionsByPairs;
        return;
    }
    throw std::invalid_argument("Mode not found");
}

// std::getline(my_buffer, line);