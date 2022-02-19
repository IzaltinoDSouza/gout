//graphic 2d out
#include "../../gout.h"

#include <iostream>

int main()
{
    try{
    
        //create window 
        ids::gout.window("Keyboard Event",ids::resolution{.width=800,.height=600});
    
        ids::gout.event([](bool & is_running,quit_event quit,keyboard kb,mouse mouse){
        
            kb.on_pressed([&is_running](keyboard::keys key,
                                        keyboard::modifiers mod,
                                        bool repeat){
                
                //stop event loop
                if(key == keyboard::keys::esc)
                {
                    is_running = false;
                }
            });
            
            //quit event
            quit.on_quit([](){
                std::clog << "goodbye world\n";
            });
            
        });
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
