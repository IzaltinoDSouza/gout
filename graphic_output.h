#pragma once

#include <cstdint>
#include <thread>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "resolution.h"
#include "position.h"
#include "color.h"
#include "event/quit.h"
#include "event/keyboard.h"
#include "event/mouse.h"

using namespace std::chrono_literals;

namespace ids{
    class graphic_output{
       
        class SdlError : public std::exception{
        public:
            SdlError(const std::string& what_arg) : m_what_arg{what_arg.c_str()}{}
            SdlError(const char* what_arg) : m_what_arg{what_arg}{}
            const char * what() const noexcept override
            {
                return  m_what_arg;
            }
        private:
            const char *m_what_arg;
        };
        
    public:
        graphic_output() : 
            m_window{nullptr},
            m_surface{nullptr},
            m_offset{}
       
        {
            if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
                throw SdlError(SDL_GetError());
            }
        }
        
        ~graphic_output()
        {
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }
        
        void window(const std::string & title,const ids::resolution & res)
        {
            create_window(title,res);
            update_surface();
        }
        
        template <class Rep,class Period>
        void delay(const std::chrono::duration<Rep, Period> & time)
        {                
            const auto time_end = 
                std::chrono::high_resolution_clock::now() + time;
            
            bool is_running{true};
            
            while(std::chrono::high_resolution_clock::now() <= time_end && 
                  is_running
                  )
            {
                while(SDL_PollEvent(&m_event))
                {
                    if(m_event.type == SDL_QUIT)
                    {
                        is_running = false;
                        continue;                   
                    }
                }
                
                flush();
            }
        }
        void event(std::function<void(bool &,quit_event,keyboard,mouse)> callback)
        {
            bool is_running{true};
            while(true)
            {
                while(SDL_PollEvent(&m_event))
                {
                    switch(m_event.type){
                        case SDL_KEYDOWN:
                        {
                            keyboard kb{static_cast<keyboard::keys>(m_event.key.keysym.scancode),
                                        static_cast<keyboard::modifiers>(m_event.key.keysym.mod),
                                        static_cast<bool>(m_event.key.repeat),
                                        true};
                            callback(is_running,quit_event{},kb,mouse{});
                        }
                        break;
                        case SDL_KEYUP:
                        {
                            keyboard kb{static_cast<keyboard::keys>(m_event.key.keysym.scancode),
                                        static_cast<keyboard::modifiers>(m_event.key.keysym.mod),
                                        static_cast<bool>(m_event.key.repeat),
                                        false};
                            callback(is_running,quit_event{},kb,mouse{});
                        }
                        break;
                        case SDL_QUIT:
                            is_running = false;
                        break;
                        case SDL_MOUSEWHEEL:
                        {                           
                            int x = m_event.wheel.x;
                            int y = m_event.wheel.y;
                            
                            if(m_event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
                            {
                                x *= -1;
                                y *= -1;
                            }
                            mouse mouse{mouse::events::wheel,x,y,x,y};
                            callback(is_running,quit_event{},keyboard{},mouse);
                        }
                        break;
                        case SDL_MOUSEMOTION:
                        {                           
                            int x = m_event.motion.x;
                            int y = m_event.motion.y;
                            
                            mouse mouse{mouse::events::motion,x,y,x,y};
                            callback(is_running,quit_event{},keyboard{},mouse);
                        }
                        break;
                        case SDL_MOUSEBUTTONDOWN:
                        {
                            int x = m_event.button.x;
                            int y = m_event.button.y;
                            
                            auto click = static_cast<mouse::clicks>(m_event.button.clicks); 
                            
                            mouse mouse{mouse::events::pressed,x,y,x,y,click};
                            callback(is_running,quit_event{},keyboard{},mouse);
                        }
                        break;
                        
                        case SDL_MOUSEBUTTONUP:
                        {
                            int x = m_event.button.x;
                            int y = m_event.button.y;
                            
                            auto click = static_cast<mouse::clicks>(m_event.button.clicks); 
                            
                            mouse mouse{mouse::events::released,x,y,x,y,click};
                            callback(is_running,quit_event{},keyboard{},mouse);
                        }
                        break;
                        
                        default:
                        break;
                    }
                }
                if(!is_running)
                {
                    callback(is_running,quit_event{!is_running},keyboard{},mouse{});
                    break;
                }
            }
        }
        void flush()
        {
            SDL_UpdateWindowSurface(m_window);
        }
        
        void clear()
        {
            SDL_FillRect(m_surface, nullptr,
                         SDL_MapRGB(m_surface->format, 0, 0, 0));
        }
        
        void close()
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            m_surface = nullptr;
        }
        
        void set_resolution(const ids::resolution & res)
        {
            SDL_SetWindowSize(m_window,res.width,res.height);
        }
        
        ids::resolution get_resolution() const
        {
            int width{};
            int height{};
    
            SDL_GetWindowSize(m_window,&width,&height);
           
            return ids::resolution{static_cast<size_t>(width),
                                   static_cast<size_t>(height)
                                  };
        }
        
        void set_title(const std::string & title)
        {
            SDL_SetWindowTitle(m_window,title.c_str());
        }
        
        std::string get_title()
        {
            return SDL_GetWindowTitle(m_window);
        }
        
        size_t get_bpp() const
        {
            return m_surface->format->BitsPerPixel;
        }
        
        color_mask get_color_mask() const
        {
            return m_mask;
        }
        
        graphic_output & operator<<(const position & pos)
        {
            m_offset = calc_offset(pos);
            return *this;
        }
        
        graphic_output & operator<<(const uint32_t pixel)
        {            
            if(SDL_LockSurface(m_surface) < 0){
                throw SdlError(SDL_GetError());
            }else{
                uint32_t * buffer = (uint32_t*)((uint8_t*)
                                     m_surface->pixels + m_offset
                                    );

                *buffer = pixel;
                
                SDL_UnlockSurface(m_surface);
            }
            
            return *this;
        }
        graphic_output & operator<<(rgb color)
        {
            //will convert color mask into gout mask if needed
            color.set_mask(m_mask);
            
            *this << color.get_rgb();
            
            return *this;
        }
    private:        
        SDL_Window  * m_window;
        SDL_Surface * m_surface;
        SDL_Event     m_event;
        size_t        m_offset;
        color_mask    m_mask;
        
        size_t calc_offset(const position & pos) const
        { 
            return pos.y * m_surface->pitch + pos.x *
                   m_surface->format->BytesPerPixel;
        }
        
        void create_window(const std::string & title,
                           const ids::resolution & res)
        {
            if(m_window == nullptr)
            {
               m_window = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           res.width,
                                           res.height,
                                           SDL_WINDOW_SHOWN
                                          );
              
            }else
            {                
                set_title(title);
                set_resolution(res);
            }
            
             if(m_window == nullptr)
                throw SdlError(SDL_GetError());
        }
        void update_surface()
        {
            
            m_surface = SDL_GetWindowSurface(m_window);
           
                
            if(m_surface == nullptr)
                throw SdlError(SDL_GetError());
            
            
            m_mask = {m_surface->format->Rmask,
                      m_surface->format->Gmask,
                      m_surface->format->Bmask,
                      m_surface->format->Amask};
            
            m_offset = calc_offset(position{0,0});
        }     
    };
}
