#include "Editor_Dock.h"
#include "Application.h"

namespace MX
{
  Editor_Dock::Editor_Dock()
    : m_opt_fullscreen(false) { }

  Editor_Dock::Editor_Dock(const std::string& name, ImGuiWindowFlags flags)
    : m_opt_fullscreen(false)
  {
    initialize(name, flags);
  }

  std::pair<std::string, bool*> Editor_Dock::visibilty()
  {
    auto temp = ImGui_Window::visibilty();
    // ensure dock is always visible
    *temp.second = true;
    return temp;
  }

  void Editor_Dock::set_visibilities(std::initializer_list<std::pair<std::string, bool*>> list)
  {
    for (auto &it : list)
      m_visibilities.push_back(it);
  }

  void Editor_Dock::set_visibilities(std::pair<std::string, bool*> item)
  {
    m_visibilities.push_back(item);
  }

  bool Editor_Dock::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Dock::update()
  {
    return true;
  }

  void Editor_Dock::render()
  {
    static bool render_demo = false;
    if (render_demo)
      ImGui::ShowDemoWindow();

    static bool opt_fullscreen_persistent = true;
    m_opt_fullscreen = opt_fullscreen_persistent;

    if (m_opt_fullscreen)
    {
      ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::SetNextWindowSize(viewport->Size);
      ImGui::SetNextWindowViewport(viewport->ID);

      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

      add_flags(
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus
      );
    }

    if (dock_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      add_flags(ImGuiWindowFlags_NoBackground);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui_Window::begin();

    ImGui::PopStyleVar();

    if (m_opt_fullscreen)
      ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dock_flags);
    }

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("Save"))
        {
          Application::get().m_World.m_ActiveScene->save();
        }

        if (ImGui::MenuItem("Open"))
        {

        }

        if (ImGui::MenuItem("Delete"))
        {
          Application::get().m_World.m_ActiveScene->remove();
        }

        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Window"))
      {
        for (auto &it : m_visibilities)
        {
          if (ImGui::MenuItem(it.first.c_str(), NULL, it.second))
          {
            if (it.second)
              MX_INFO_LOG("MX: Editor: Dock: " + it.first + " closed");
            else
              MX_INFO_LOG("MX: Editor: Dock: " + it.first + " opened");
          }
        }

        if (ImGui::BeginMenu("Layout"))
        {
          if (ImGui::MenuItem("Default"))
          {
            // reset layout by loading ini
          }

          ImGui::EndMenu();
        }

        ImGui::EndMenu();
      }

      if (ImGui::MenuItem("Demo"))
          render_demo = !render_demo;

      ImGui::EndMenuBar();
    }

    ImGui_Window::end();
  }
}
