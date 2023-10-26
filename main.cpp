#define GLEW_STATIC

#include "common.h"
#include "src/scene/BaseScene.h"
#include "src/scene/SceneTriangle.h"
#include <iostream>


BaseScene* mCurrentScene = nullptr;
void changeScene(BaseScene* newScene) {
    if(mCurrentScene) {
        mCurrentScene ->OnExit();
    }

    newScene->OnEnter();

    BaseScene* ptr = mCurrentScene;
    mCurrentScene = newScene;
    delete ptr;
}

double previous_x = 0.0f;
double previous_y = 0.0f;

void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        return;
    }
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
//    std::cout << "left drag x = " << x << ", y = " << y << std::endl;
    if(mCurrentScene && mCurrentScene->CanDraw()) {
        MouseDragDirection dirX = DIR_NONE;
        if(previous_x - x > 0) {
            dirX = DIR_RIGHT;
        } else {
            dirX = DIR_LEFT;
        }
        previous_x = x;
        MouseDragDirection dirY = DIR_NONE;
        if(previous_y - y > 0) {
            dirY = DIR_DOWN;
        } else {
            dirY = DIR_UP;
        }
        previous_y = y;

        mCurrentScene->OnMouseDrag(dirX, dirY);
    }
}

void addButton1() {
    if (ImGui::Button("Triangle")) {
        BaseScene * scene = new SceneTriangle();
        changeScene(scene);
    }
}


int main() {

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // core profile,   需要手动bind VAO
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Study", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

//    std::cout << "sizeof(Vertex::Pos) = " << Vertex::getTextCordSize() << std::endl;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // important!!! 在Opengl context初始化后才能初始化glew
    if (glewInit() != GLEW_OK) {
        std::cout << " GLEW Init Failed" << std::endl;
    } else {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }
    // 设置刷新频率
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(window, mouse_cursor_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
    const char* glsl_version = "#version 130";
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    double currentTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {

        GLCall(glClearColor(0.2f, 0.2f, 0.4f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("OpenGL SubEntries");

        addButton1();

        double deltaTime = glfwGetTime() - currentTime;
        currentTime = glfwGetTime();
        if(mCurrentScene && mCurrentScene->CanDraw()) {
            mCurrentScene->Draw(deltaTime);
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
