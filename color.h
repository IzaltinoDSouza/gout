#pragma once

#include <cstdint>
#include <iostream>
#include <bitset>

namespace ids
{   
    struct color_mask{
        uint32_t r;
        uint32_t g;
        uint32_t b;
        uint32_t a;
        
        bool operator==(const color_mask & mask)
        {
            return r == mask.r &&
                   g == mask.g &&
                   b == mask.b &&
                   a == mask.a;
        }
        bool operator!=(const color_mask & mask)
        {
            return !(*this == mask);
        }        
    };
    
    namespace default_mask
    {
        static const color_mask argb{.r=0x00ff0000,
                                     .g=0x0000ff00,
                                     .b=0x000000ff,
                                     .a=0xff000000};
                                      
        static const color_mask rgba{.r=0x00ff0000,
                                     .g=0x0000ff00,
                                     .b=0x000000ff,
                                     .a=0x000000ff}; 
                                      
        static const color_mask rgb{.r=0xff000000,
                                    .g=0x00ff0000,
                                    .b=0x0000ff00,
                                    .a=0x00000000};       
    }
    class rgb{
        public:
            rgb() = default;
            rgb(color_mask mask) : m_mask{mask} {}
            
            rgb(uint8_t r,uint8_t g,uint8_t b, uint8_t a = 0,
                color_mask mask = default_mask::argb) : m_mask{mask}
            {
                m_color = to_rgb(r,g,b,a);
            }            
            void set_rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0)
            {
                m_color = to_rgb(r,g,b,a);
            }
            uint32_t get_rgb() const
            {
                return m_color;
            }
            
            void set_red(uint8_t r)
            {
                m_color &= ~ left_shift_mask(255 , m_mask.r);
                m_color |=   left_shift_mask(r , m_mask.r);
            }
            void set_green(uint8_t g)
            {
                m_color &= ~ left_shift_mask(255 , m_mask.g);
                m_color |=   left_shift_mask(g , m_mask.g);
            }
            void set_blue(uint8_t b)
            {
                m_color &= ~ left_shift_mask(255 , m_mask.b);
                m_color |=   left_shift_mask(b , m_mask.b);
            }
            void set_alpha(uint8_t a)
            {
                m_color &= ~ left_shift_mask(255 , m_mask.a);
                m_color |=   left_shift_mask(a , m_mask.a);
            }
            
            uint8_t get_red() const 
            {
                return right_shift_mask(m_color , m_mask.r) & 0xff;
            }
            uint8_t get_green() const
            {
                return right_shift_mask(m_color , m_mask.g) & 0xff;
            }
            uint8_t get_blue() const
            {
                return right_shift_mask(m_color , m_mask.b) & 0xff;
            }
            uint8_t get_alpha() const
            {
                return right_shift_mask(m_color , m_mask.a) & 0xff;
            }
            
            void set_mask(const color_mask & mask)
            {
                if(m_mask != mask)
                {
                    const uint8_t r = get_red();
                    const uint8_t g = get_green();
                    const uint8_t b = get_blue();
                    const uint8_t a = get_alpha();
                    
                    m_mask = mask;
                    
                    m_color = to_rgb(r,g,b,a);
                }
            }
            
            color_mask get_mask() const
            {
                return m_mask;
            }
        private:
            uint32_t    m_color;
            color_mask m_mask{default_mask::argb};       
            
            uint32_t left_shift_mask(uint32_t color,uint32_t mask) const
            {
                if(mask & 0xff000000)   
                    color <<= 24;
                else if(mask & 0x00ff0000)  
                    color <<= 16;
                else if(mask & 0x0000ff00)  
                    color <<= 8;
                else if(mask & 0x000000ff)
                    color <<= 0;
                return color;
            }
            
            uint32_t right_shift_mask(uint32_t color,uint32_t mask) const
            {
                if(mask & 0xff000000)   
                    color >>= 24;
                else if(mask & 0x00ff0000)  
                    color >>= 16;
                else if(mask & 0x0000ff00)  
                    color >>= 8;
                else if(mask & 0x000000ff)
                    color >>= 0;               
                return color;
            }
            
            uint32_t to_rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0) const
            {
                uint32_t color{left_shift_mask(r , m_mask.r)  |
                               left_shift_mask(g , m_mask.g)  |
                               left_shift_mask(b , m_mask.b)  |
                               left_shift_mask(a , m_mask.a)};
                
                return color;
            }
    };
}
