#pragma once

#include <cstdint>
#include <thread>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "resolution.h"
#include "position.h"
#include "color.h"

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
            
            bool running{true};
            
            while(std::chrono::high_resolution_clock::now() <= time_end && 
                  running
                  )
            {
                while(SDL_PollEvent(&m_event))
                {
                    if(m_event.type == SDL_QUIT)
                    {
                        running = false;
                        continue;                   
                    }
                }
                
                flush();
            }
        }
        
        void flush()
        {
            SDL_UpdateWindowSurface(m_window);
        }
        
        void clear()
        {
            SDL_FillRect(m_surface, nullptr,
                         SDL_MapRGB(m_surface->format, 0, 0, 0)
                        );
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
