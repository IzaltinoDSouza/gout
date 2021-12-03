# <p align="center"> gout </p>
**<p align="center"> Graphic 2d Output for C++</p>**

## About
ids::gout is library to put pixels on the screen.

it's very easy to use!
```cpp
//resolution  : width and height
const auto resolution = ids::resolution{.width=800,.height=600};

//configure the window
ids::gout.window("put single pixel on screen",resolution);

//add pixel in the framebuffer
ids::gout << ids::position{0,0}
          << ids::rgb{0,0,255};

//put pixels on the screen
ids::gout.flush();

//show pixels for 10 seconds
ids::gout.delay(10s);

//close window
ids::gout.close();
```

**Dependencies**
* __SDL2__
    * [Download](https://www.libsdl.org/download-2.0.php) or [Git](https://github.com/libsdl-org/SDL)

## [Example]

![Example](https://github.com/IzaltinoDSouza/gout/blob/main/screenshots/example.jpg)

```cpp
#include <iostream>

//graphic 2d out
#include "../../gout.h"

//resolution  : width and height
const auto res = ids::resolution{.width=800,.height=600};

void drawRectangle(const ids::rgb &color)
{
   for(size_t y{0};y < res.height;++y)
    {
        for(size_t x{0};x < res.width;++x)
        {
            //add color on screen at x,y position 
            ids::gout << ids::position{x,y}
                      << color;
        }
    }
}
int main()
{
    try{
        //create window
        ids::gout.window("Draw Blue Rectangle",res);
    
        drawRectangle(ids::rgb blue{0,0,255});
        
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
        return 1;
    }
}

```

**Compilation**
* **clang**
    ```
    clang++ example.cpp -lSDL2main -lSDL2 -o example
    ```
* **gcc**
    ```
    g++ example.cpp -lSDL2main -lSDL2 -o example  
    ```

## Author

* **IzaltinoDSouza**

## License

See the [LICENSE](https://github.com/IzaltinoDSouza/gout/blob/main/LICENSE) file for details.
