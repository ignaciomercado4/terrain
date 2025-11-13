#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "./UI.hpp"
#include "../Graphics/Window.hpp"
#include "../Misc/Globals.hpp"

void UI::init(Window &window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavNoCaptureKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window.getWindowPointer(), true);
    ImGui_ImplOpenGL3_Init();
}

void UI::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("Terrain", nullptr, ImGuiWindowFlags_None))
    {
        ImGui::Separator();
        ImGui::Text("TERRAIN DATA");
        ImGui::Separator();

        ImGui::Text("Terrain vertices: %li", Globals::terrain->vertices.size());
        ImGui::Text("Terrain indices: %li", Globals::terrain->indices.size());


        ImGui::Separator();
        ImGui::Text("CAMERA POSITION");
        ImGui::Separator();
        ImGui::Text("x = %f y = %f z = %f", Globals::camera.getEye().x, Globals::camera.getEye().y, Globals::camera.getEye().z);

        // terrain gen controls
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::Text("PERLIN NOISE");
        ImGui::Separator();

        // height scale: vertical exaggeration of terrain
        if (ImGui::SliderFloat("Height Scale", &Globals::terrain->perlinParameters.heightScale, 0.0f, 200.0f, "%.2f"))
        {
            Globals::terrain->setPerlinNoiseHeightValues();
        }

        // amplitude: strength of the base noise layer
        if (ImGui::SliderFloat("Amplitude", &Globals::terrain->perlinParameters.amplitude, 0.1f, 50.0f, "%.2f"))
        {
            Globals::terrain->setPerlinNoiseHeightValues();
        }

        // frequency: how dense the noise pattern is (smaller = wider hills)
        if (ImGui::SliderFloat("Frequency", &Globals::terrain->perlinParameters.frequency, 0.1f, 10.0f, "%.2f"))
        {
            Globals::terrain->setPerlinNoiseHeightValues();
        }

        // scale: how zoomed-in the noise looks (lower = broader features)
        if (ImGui::SliderFloat("Scale", &Globals::terrain->perlinParameters.scale, 0.01f, 1.0f, "%.3f"))
        {
            Globals::terrain->setPerlinNoiseHeightValues();
        }

        // persistence: amplitude decay per octave (controls roughness)
        if (ImGui::SliderFloat("Persistence", &Globals::terrain->perlinParameters.persistence, 0.1f, 1.0f, "%.2f"))
        {
            Globals::terrain->setPerlinNoiseHeightValues();
        }

        // octaves: number of noise layers (higher = more fine detail)
        if (ImGui::SliderInt("Octaves", &Globals::terrain->perlinParameters.octaves, 1, 12))
        {
            Globals::terrain->setPerlinNoiseHeightValues();
        }

        // render wireframe
        ImGui::Checkbox("Render wireframe", &Globals::isWireframe);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}