#include <include/raylib.h>
#include <imgui/imgui.h>
#include <imgui/rlImGui.h>
#include <imgui/imgui_stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

const int screenWidth = 1280;
const int screenHeight = 800;

class Shape {
public:
    float x;
    float y;
    float velX;
    float velY;
    int colorR;
    int colorG;
    int colorB;
    bool active = true;
    std::string name;
    int scale = 1;

    
    Shape(float x, float y, float velX, float velY, int colorR, int colorG, int colorB, std::string name ): x(x), y(y),velX(velX), velY(velY), colorR(colorR),colorG(colorG),colorB(colorB), name(name){}

    void update(){
        x += velX;
        y += velY;
    }

    
 
};

class Circle : public Shape {
public:

    float radius;


   
    Circle(float x, float y, float velX, float velY, int colorR, int colorG, int colorB,std::string name, float radius):Shape(x,y,velX,velY,colorR,colorG,colorB,name), radius(radius) {}

   
    void circUpdate() {
         update();
         if (x - radius*scale <= 0.0f || x + radius*scale >= screenWidth) { //circle hits the left or right side
             velX = -velX;// flip direction of x velocity
         }
         if (y - radius*scale <= 0.0f || y + radius*scale >= screenHeight) { //circle hits the top or bottom
             velY = -velY; // flip direction of y velocity
         }

    }
    void render() {
        DrawCircle((int)x, (int)y, radius*scale, ColorFromNormalized({ (float)colorR,(float)colorG,(float)colorB,1.0f }));
    }

};

class Rect : public Shape {
public:
    
    float height;
    float width;

    
   
    Rect(float x, float y, float velX, float velY, int colorR, int colorG, int colorB,std::string name, float height, float width):Shape(x, y, velX, velY, colorR, colorG, colorB,name), height(height), width(width) {}
    

    void rectUpdate() {
        update();
        if (x <= 0.0 || x + width >= screenWidth) {
            velX = -velX;// flip direction of x velocity
        }
        if (y <= 0.0 || y + height >= screenHeight) {
            velY = -velY;// flip direction of x velocity
        }
    }
    void render() {
        DrawRectangle((int)x, (int)y, (int)width, (int)height, ColorFromNormalized({ (float)colorR,(float)colorG,(float)colorB,1.0f }));
    }
   

};
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Assignment 1 Starter Code");
    
    //initialize the raylib ImGui backend
    rlImGuiSetup(true);
    //increase ImGui item size to 2x
    ImGui::GetStyle().ScaleAllSizes(2);

    // Set raylib to target 60 frames-per-second (this does not mean it will actually RUN at 60 fps)
    SetTargetFPS(60);      
    
    //read in config file
    std::fstream configFile;
    configFile.open("assets / input.txt");


    while (configFile.eof()) {




    }

    // General variables
    //--------------------------------------------------------------------------------------

    //shape properties to draw on the screen (circle for this example)
    //units of size and speed are in pixels
    //color is from 0-1

   
    std::cout << "fgdfmklvmfdkl;mv" << std::endl;
    Circle circ1(50.0f,50.0f,1.0f,0.5f,0,0,1,"Circle",50);
    Rect rec1(50.0f, 50.0f, 1.0f, 0.5f, 0, 0, 1, "Rectangle",50.0f, 50.0f);

    bool isActive = true;
    
    std::vector<Shape*> container;
    container.push_back(&circ1);
    container.push_back(&rec1);

    
   
    


    //Let's draw some text to the screen too
    bool drawText=true;
    std::string strText= "Some Text";
    std::string newText= strText;

    //load a font (Raylib gives warning if font can't be found, then uses default as fallback)
    Font font = LoadFont("assets/Orbitron.ttf");

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        //move circle
       
        //circ1.update(circ1.x,circ1.y, circ1.velX, circ1.velY );


        circ1.circUpdate();
        rec1.rectUpdate();
        

      
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            //********** Raylib Drawing Content **********

            //draw the cricle (center x, center y, radius, color(r,g,b,a))
            if(isActive){
                circ1.render();
                rec1.render();
            }
           
                
            //draw the text
            if(drawText){
                //get the size (x and y) of the text object
                //(font,c string, font size, font spaceing)
                Vector2 textSize= MeasureTextEx(font, strText.c_str(), 18, 1);

                //draw the text (using the text size to help draw it in the corner
                //(font,c string, vector2, font size, font spaceing, color)
                DrawTextEx(font, strText.c_str(), { circ1.x - (textSize.x/2), circ1.y - (textSize.y/2)}, 18, 1, WHITE);
            }

            //********** ImGUI Content *********
            
            //Draw imgui stuff last so it is over the top of everything else
            rlImGuiBegin();

                //sets the next window to be at this position
                //also uses the imgui.ini that gets created at first run
                ImGui::SetNextWindowSize(ImVec2(350, 250));
                //creates a new window
                ImGui::Begin("My Window",NULL,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
                    ImGui::Text("The Window Text!");
                    //checkboxes, they directly modify the value (which is why we send a reference)
                    ImGui::Checkbox("Draw Cricle",&isActive);
                    ImGui::SameLine();
                    ImGui::Checkbox("Draw Text",&drawText);

                    //slider, again directly modifies the value and limites between 0 and 300 for this example
                    ImGui::SliderFloat("Radius",&circ1.radius,0.0f,300.0f);

                    //slider to adjust both x and y velocity
                    ImGui::SliderFloat("X Velocity",&circ1.velX, 0.0f, 300.0f);
                    ImGui::SliderFloat("Y Velocity", &circ1.velY, 0.0f, 300.0f);
                    
                    //color picker button, directly modifies the color (3 element float array)
                    //ImGui::ColorEdit3("Circle Color",color);
                    
                    //text input field, directly modifies the string
                    ImGui::InputText("Text",&newText);

                    //ImGui::BeginCombo("Objects", "circ",5);
                    //ImGui::Combo("objects", &container, container.size(), 5);

                    //ImGui::EndCombo();
                    
                    //buttons, returns true if clicked on this frame
                    if(ImGui::Button("Set Text")){
                        strText=newText;
                    }

                    //The next item will be on the same line as the previous one
                    ImGui::SameLine();

                    //Another button
                    if(ImGui::Button("Reset Circle")){
                        circ1.x=50.0;
                        circ1.y=50.0;
                        circ1.radius=50;
                        circ1.velX = 1.0f;
                        circ1.velY = 0.5f;
                    }
                    ImGui::SameLine();

                    if (ImGui::Button("Reset Square")) {
                        rec1.velX = 7.0f;
                        rec1.velY = 0.5f;
                        rec1.x = 50.0f;
                        rec1.y = 50.0f;
                    }
                //ends this window
                ImGui::End();

                //show ImGui Demo Content if you want to see it
                //bool open = true;
               // ImGui::ShowDemoWindow(&open);

            // end ImGui Content
            rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Clean Up
    //--------------------------------------------------------------------------------------
    rlImGuiShutdown();    // Shuts down the raylib ImGui backend
    UnloadFont(font);     // Remove font from memory
    CloseWindow();        // Close window and OpenGL context
    configFile.close();   // Close config file
    //--------------------------------------------------------------------------------------

    return 0;
}