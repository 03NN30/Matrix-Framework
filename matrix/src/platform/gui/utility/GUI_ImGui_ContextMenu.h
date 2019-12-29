#ifndef GUI_IMGUI_CONTEXTMENU_H
#define GUI_IMGUI_CONTEXTMENU_H

#include "stdafx.h"

namespace MX
{
  enum Action
  {
    E_LEFT_CLICK, E_RIGHT_CLICK, E_DOUBLE_CLICK, E_NONE
  };

  // call object of this class right after the imgui item that you want to bind a context menu to
  class ImGui_ContextMenu
  {
  public:
    MX_API ImGui_ContextMenu(
      const char* name,
      ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar, 
      const Action& action = E_RIGHT_CLICK
    );

    MX_API bool begin();
    MX_API bool begin(bool& show);
    MX_API void end();

  private:
    MX_API bool is_clicked();

    ImGuiWindowFlags m_flags;
    Action m_action;
    bool m_update_mouse;
    bool m_show;
    ImVec2 m_mouse_pos;
    const char* m_name;
    bool m_invoked_begin;
    bool m_force_focus;
    bool m_set_pos;


  };
}

#endif // GUI_IMGUI_CONTEXTMENU_H