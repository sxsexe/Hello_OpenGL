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

    BaseScene* ptr = mCurrentScene;
    mCurrentScene = newScene;
    mCurrentScene->OnEnter();

    delete ptr;
}

void buildSubEntries() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("OpenGL SubEntries");

    if (ImGui::Button("Triangle")) {
        BaseScene * scene = new SceneTriangle();
        changeScene(scene);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

        buildSubEntries();

        double deltaTime = glfwGetTime() - currentTime;
        currentTime = glfwGetTime();

        if(mCurrentScene && mCurrentScene->CanDraw()) {
            mCurrentScene->Draw(deltaTime);
        }

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
