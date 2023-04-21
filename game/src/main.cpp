#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream configFile("config.txt");
    if (!configFile.is_open())
    {
        std::cerr << "Erreur: impossible d'ouvrir le fichier config.txt" << std::endl;
        return -1;
    }

    int width = 640, height = 480;
    bool fullscreen = false, vsync = false;
    int audio = 0;

    std::string line;
    while (std::getline(configFile, line))
    {
        if (line.substr(0, 11) == "resolution:")
        {
            std::sscanf(line.substr(11).c_str(), "%dx%d", &width, &height);
        }
        else if (line.substr(0, 11) == "fullscreen:")
        {
            fullscreen = (line.substr(11) == "true");
        }
        else if (line.substr(0, 6) == "vsync:")
        {
            vsync = (line.substr(6) == "true");
        }
        else if (line.substr(0, 6) == "audio:")
        {
            std::sscanf(line.substr(6).c_str(), "%d", &audio);
        }
    }

    configFile.close();

    if (!glfwInit())
    {
        std::cerr << "Erreur: impossible d'initialiser GLFW" << std::endl;
        return -1;
    }

    // Création de la fenêtre
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    if (fullscreen)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        width = mode->width;
        height = mode->height;
        window = glfwCreateWindow(width, height, "BladeBattles", monitor, NULL);
    }
    else
    {
        window = glfwCreateWindow(width, height, "BladeBattles", NULL, NULL);
    }

    if (!window)
    {
        glfwTerminate();
        std::cerr << "Erreur: impossible de créer la fenêtre GLFW" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Erreur: impossible d'initialiser GLEW" << std::endl;
        return -1;
    }

    if (vsync)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
