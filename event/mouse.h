#pragma once

#include <functional>

class mouse
{
public: 
    enum class events{
        none,
        wheel,
        motion,
        pressed,
        released
    }m_event;
    
    enum class clicks
    {
        none = 0,
        single_click = 1,
        double_click = 2
    };
    
    mouse() : m_event{events::none} {}
    
    mouse(events event,int x,int y,int xrel,int yrel,clicks click = clicks::none)
    : m_event{event},
      m_x{x},
      m_y{y},
      m_xrel{xrel},
      m_yrel{yrel},
      m_clicks{click}{}
  
    
    using wheel_callback = std::function<void(int,int)>;
    void on_wheel(wheel_callback callback)
    {
        if(m_event == events::wheel)
            callback(m_x,m_y);
    }
    
    using motion_callback = std::function<void(int,int,int,int)>;
    void on_motion(motion_callback callback)
    {
        if(m_event == events::motion)
            callback(m_x,m_y,m_xrel,m_yrel);
    }
    using button_callback = std::function<void(size_t,size_t,clicks)>;
    void on_pressed(button_callback callback)
    {            
        if(m_event == events::pressed)
            callback(m_x,m_y,m_clicks);
    }
    void on_released(button_callback callback)
    {
        if(m_event == events::released)
            callback(m_x,m_y,m_clicks);
    }
    
private:
    int     m_x;
    int     m_y;
    int     m_xrel;
    int     m_yrel;
    clicks  m_clicks;
};
