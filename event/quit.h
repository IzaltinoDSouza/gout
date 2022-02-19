#pragma once

#include <functional>

class quit_event
{
public:
    quit_event(bool quit = false) : m_quit{quit} {}
    
    using quit_callback = std::function<void()>;
    void on_quit(quit_callback callback)
    {
        if(m_quit)
            callback();
    }
private:
    bool m_quit;
};
