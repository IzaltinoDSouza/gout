#include <iostream>

//graphic 2d out
#include "../../gout.h"

void drawRectangle(const ids::rgb & color,
                   const ids::position & pos,
                   const ids::resolution & size)
{
    for(size_t y{pos.y};y < size.height;++y)
    {
        for(size_t x{pos.x};x < size.width;++x)
        {
            ids::gout << ids::position{x,y} << color;
        }
    }
}

int main()
{
    try{
        //create window
        ids::gout.window("Draw Blue Rectangle",
                         ids::resolution{.width=800,.height=600}
                        );
    
        drawRectangle(ids::rgb{0,0,0x45},
                      ids::position{.x=20,.y=20},
                      ids::resolution{.width=512,.height=512}
                     );
        
        //put pixels on the screen
        ids::gout.flush();
        
        //show pixels for 10 seconds
        ids::gout.delay(10s);
        
        //close window
        ids::gout.close();
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
}
