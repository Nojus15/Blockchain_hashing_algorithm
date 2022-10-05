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
            throw std::invalid_argument("Invalid argument: --gf used incorrectly");
        Generator gen;
        gen.genFile(argv[2], std::atoi(argv[3]));
        break;
    case AppMode::HashFile:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --hf used incorrectly");
        this->text = file.readFile(argv[2]).str();
        cout << hasher.hashString(this->text, true) << endl;
        break;
    case AppMode::HashLine:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --hl used incorrectly");
        this->text = argv[2];
        cout << hasher.hashString(this->text, true) << endl;
        break;
    case AppMode::TestCollisions:
        if (this->argc != 5)
            throw std::invalid_argument("Invalid argument: --tc used incorrectly");
        {
            int count = std::atoi(this->argv[2]);
            int symbolCount = std::atoi(this->argv[3]);
            string resFileName = this->argv[4];
            tester.runCollisionTest(count, symbolCount, resFileName);
        }
        break;
    case AppMode::TestSpeed:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --ts used incorrectly");
        {
            int symbolCount = std::atoi(this->argv[2]);
            tester.runSpeedTest(symbolCount);
        }
        break;
    case AppMode::TestCollisionsByPairs:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --tcp used incorrectly");
        {
            string resFileName = this->argv[2];
            tester.runCollisionTestByPairs(resFileName);
        }
        break;
    case AppMode::TestKonstitucija:
        if (this->argc != 2)
            throw std::invalid_argument("Invalid argument: --tk used incorrectly");
        tester.testKonstitucija();
        break;
    case AppMode::TestAvalanche:
        if (this->argc != 2)
            throw std::invalid_argument("Invalid argument: --ta used incorrectly");
        tester.testAvalanche();
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

    if (modeArg == "--gf")
    {
        this->mode = AppMode::GenFile;
        return;
    }

    if (modeArg == "--hf")
    {
        this->mode = AppMode::HashFile;
        return;
    }
    if (modeArg == "--hl")
    {
        this->mode = AppMode::HashLine;
        return;
    }
    if (modeArg == "--tc")
    {
        this->mode = AppMode::TestCollisions;
        return;
    }
    if (modeArg == "--ts")
    {
        this->mode = AppMode::TestSpeed;
        return;
    }
    if (modeArg == "--tcp")
    {
        this->mode = AppMode::TestCollisionsByPairs;
        return;
    }
    if (modeArg == "--tk")
    {
        this->mode = AppMode::TestKonstitucija;
        return;
    }
    if (modeArg == "--ta")
    {
        this->mode = AppMode::TestAvalanche;
        return;
    }
    throw std::invalid_argument("Mode not found");
}

// std::getline(my_buffer, line);