#include "Editor_Dock.h"

namespace MX
{
  Editor_Dock::Editor_Dock()
    : m_opt_fullscreen(false)
  { }

  void Editor_Dock::initialize()
  {
    m_name = "Dockspace";
  }

  void Editor_Dock::update()
  {
    // ImGui_Window::update();
  }

  void Editor_Dock::render()
  {
    static bool opt_fullscreen_persistent = true;
    m_opt_fullscreen = opt_fullscreen_persistent;

    window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (m_opt_fullscreen)
    {
      ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::SetNextWindowSize(viewport->Size);
      ImGui::SetNextWindowViewport(viewport->ID);

      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

      window_flags |=
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dock_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(m_name, &p_open, window_flags);
    ImGui::PopStyleVar();

    if (m_opt_fullscreen)
      ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("EditorDockspace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dock_flags);
    }

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("Docking"))
      {
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::End();
  }
}