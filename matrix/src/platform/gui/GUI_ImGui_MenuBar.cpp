#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"

namespace MX
{
  void GUI_ImGui::renderMenuBar()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginMainMenuBar())
    {     
      if (ImGui::BeginMenu("File"))
      {
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Edit"))
      {
        if (ImGui::MenuItem("Undo", "CTRL+Z", false, false)) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Settings"))
      {
        if (ImGui::MenuItem("toggle fullscreen", "CTRL+F"))
        {
          if (Application::get().m_Window->m_Props.m_FullScreen == 0)
          {
            WindowResized event(1920, 1080);
            event.handle();
            LOGEVENT(event);
            Application::get().m_Window->m_Props.m_FullScreen = 1;
          }
          else
          {
            WindowResized event(initial_window_width, initial_window_height);
            event.handle();
            LOGEVENT(event);
            Application::get().m_Window->m_Props.m_FullScreen = 0;
          }
        }
        if (ImGui::MenuItem("set resolution"))
        {
          input_window_title = "Info";
          input_window_message = "Please enter a resolution";
          set_show_input_window(1);
          currentInputType = mx_resolution;
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Help"))
      {
        if (ImGui::MenuItem("About"))
        {
          if (ImGui::MenuItem("about"))
          {
            event_window_title = "About";
            event_window_message = "Waehlt die Partei,\ndenn sie ist sehr gut!";
            event_window_button = "Yes";
            set_show_event_window(1);
          }
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  #endif
  }
}