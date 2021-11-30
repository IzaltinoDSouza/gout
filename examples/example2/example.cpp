//graphic 2d out
#include "../../gout.h"

//font8x8_basic
#include "font8x8.h"

#include <iostream>

void drawText(const std::string &text,
              const ids::rgb foreground,
              const ids::rgb background)
{
    const size_t fontSize{8}; 
    ids::position currentPos{0,0};
        
    for(const char c : text){
    
        if(c == '\n'){
            //next line
            currentPos.y += fontSize;
            currentPos.x  = 0;
            continue;
        }
            
        for(size_t y = 0;y < fontSize;++y){
            for(size_t x = 0;x < fontSize;++x){
                
                //get position characters need to be screen
                ids::position pos{currentPos.x + x, currentPos.y + y};  
                            
                if(font8x8_basic[c][y] >> x & 0x1){     //c get character
                                                        //y get shape,
                                                        // >> x & 0x1  get piece of shape
                                                        
                    //add foreground in the framebuffer at the (x,y) position
                    ids::gout << pos << foreground;     
                }else{
                    //add background in the framebuffer at the (x,y) position
                    ids::gout << pos << background;     
                }
                
            }
        }
        
        //space beetween characters
        currentPos.x += fontSize;
    }
    
    //put pixels on the screen
    ids::gout.flush();
    
    //show pixels for 25 seconds
    ids::gout.delay(25s);
    
}
int main()
{
    try{
    
        //create window 
        ids::gout.window("Draw Text",ids::resolution{.width=800,.height=600});
    
        std::string text{
R"(                    Alice's Adventures in Wonderland
                              by Lewis Carroll
                                    
                                 Contents

                    CHAPTER I.     Down the Rabbit-Hole
                    CHAPTER II.    The Pool of Tears
                    CHAPTER III.   A Caucus-Race and a Long Tale
                    CHAPTER IV.    The Rabbit Sends in a Little Bill
                    CHAPTER V.     Advice from a Caterpillar
                    CHAPTER VI.    Pig and Pepper
                    CHAPTER VII.   A Mad Tea-Party
                    CHAPTER VIII.  The Queen's Croquet-Ground
                    CHAPTER IX.    The Mock Turtle’s Story
                    CHAPTER X.     The Lobster Quadrille
                    CHAPTER XI.    Who Stole the Tarts?
                    CHAPTER XII.   Alice's Evidence)"};
        
        ids::rgb foreground{255,255,255};
        ids::rgb background{0,0,0};

        drawText(text,foreground,background);
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
