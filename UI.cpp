#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "./UI.hpp"
#include "./Window.hpp"
#include "./Terrain.hpp"
#include "./Globals.hpp"

void UI::init(Window &window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window.getWindowPointer(), true);
    ImGui_ImplOpenGL3_Init();
}

void UI::render(Terrain &terrain)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("Terrain", nullptr, ImGuiWindowFlags_None))
    {
        ImGui::Separator();
        ImGui::Text("TERRAIN DATA");
        ImGui::Separator();

        ImGui::Text("Terrain vertices: %li", terrain.vertices.size());
        ImGui::Text("Terrain indices: %li", terrain.indices.size());

        // terrain gen controls
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::Text("PERLIN NOISE");
        ImGui::Separator();

        // height scale: vertical exaggeration of terrain
        if (ImGui::SliderFloat("Height Scale", &terrain.perlinParameters.heightScale, 0.0f, 200.0f, "%.2f"))
        {
            terrain.setPerlinNoiseHeightValues();
            terrain.updateBuffers();
        }

        // amplitude: strength of the base noise layer
        if (ImGui::SliderFloat("Amplitude", &terrain.perlinParameters.amplitude, 0.1f, 50.0f, "%.2f"))
        {
            terrain.setPerlinNoiseHeightValues();
            terrain.updateBuffers();
        }

        // frequency: how dense the noise pattern is (smaller = wider hills)
        if (ImGui::SliderFloat("Frequency", &terrain.perlinParameters.frequency, 0.1f, 10.0f, "%.2f"))
        {
            terrain.setPerlinNoiseHeightValues();
            terrain.updateBuffers();
        }

        // scale: how zoomed-in the noise looks (lower = broader features)
        if (ImGui::SliderFloat("Scale", &terrain.perlinParameters.scale, 0.01f, 1.0f, "%.3f"))
        {
            terrain.setPerlinNoiseHeightValues();
            terrain.updateBuffers();
        }

        // persistence: amplitude decay per octave (controls roughness)
        if (ImGui::SliderFloat("Persistence", &terrain.perlinParameters.persistence, 0.1f, 1.0f, "%.2f"))
        {
            terrain.setPerlinNoiseHeightValues();
            terrain.updateBuffers();
        }

        // octaves: number of noise layers (higher = more fine detail)
        if (ImGui::SliderInt("Octaves", &terrain.perlinParameters.octaves, 1, 12))
        {
            terrain.setPerlinNoiseHeightValues();
            terrain.updateBuffers();
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