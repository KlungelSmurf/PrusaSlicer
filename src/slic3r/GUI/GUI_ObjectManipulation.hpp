#ifndef slic3r_GUI_ObjectManipulation_hpp_
#define slic3r_GUI_ObjectManipulation_hpp_

#include <memory>

#include <wx/panel.h>

#include "Preset.hpp"
#include "GLCanvas3D.hpp"

class wxBoxSizer;

namespace Slic3r {
namespace GUI {
class ConfigOptionsGroup;

class OG_Settings
{
protected:
    std::shared_ptr<ConfigOptionsGroup> m_og;
public:
    OG_Settings(wxWindow* parent, const bool staticbox);
    ~OG_Settings() {}

    wxSizer*            get_sizer();
    ConfigOptionsGroup* get_og() { return m_og.get(); }
};


class ObjectManipulation : public OG_Settings
{
    bool        m_is_percent_scale = false;         // true  -> percentage scale unit  
                                                    // false -> uniform scale unit  
    bool        m_is_uniform_scale = false;         // It indicates if scale is uniform
    // sizer for extra Object/Part's settings
    wxBoxSizer* m_settings_list_sizer{ nullptr };  
    // option groups for settings
    std::vector <std::shared_ptr<ConfigOptionsGroup>> m_og_settings;

public:
    ObjectManipulation(wxWindow* parent);
    ~ObjectManipulation() {}

    int ol_selection();
    void update_settings_list();

    void update_settings_value(const GLCanvas3D::Selection& selection);
    void reset_settings_value();
    void reset_position_value();
    void reset_rotation_value();
    void reset_scale_value();

    void update_values();
    // update position values displacements or "gizmos"
    void update_position_values();
    void update_position_value(const Vec3d& position);
    // update scale values after scale unit changing or "gizmos"
    void update_scale_values();
    void update_scale_value(const Vec3d& scaling_factor);
    // update rotation values object selection changing
    void update_rotation_values();
    // update rotation value after "gizmos"
    void update_rotation_value(double angle, Axis axis);
    void update_rotation_value(const Vec3d& rotation);

    void set_uniform_scaling(const bool uniform_scale) { m_is_uniform_scale = uniform_scale; }

    void show_object_name(bool show);
    void show_manipulation_og(const bool show);
};

}}

#endif // slic3r_GUI_ObjectManipulation_hpp_