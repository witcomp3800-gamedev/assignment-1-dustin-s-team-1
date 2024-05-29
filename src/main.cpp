#include <include/raylib.h>
#include <imgui/imgui.h>
#include <imgui/rlImGui.h>
#include <imgui/imgui_stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

 int screenWidth=50;
 int screenHeight=50;

class Shape {
public:
    float x;
    float y;
    float velX;
    float velY;
    float color[3];
    bool active = true;
    std::string name;
    float scale = 1;

    
    Shape(float x, float y, float velX, float velY, int colorR, int colorG, int colorB, std::string name ): x(x), y(y),velX(velX), velY(velY), name(name) {
        color[0] = colorR;
        color[1] = colorG;
        color[2] = colorB;
    }

    virtual void update(){}

    virtual void render(){}

    virtual void renderText(Font font,int fontSize,float fontRed, float fontGreen, float fontBlue) {

        //get the size (x and y) of the text object
        //(font,c string, font size, font spaceing)
        Vector2 textSize = MeasureTextEx(font, this->name.c_str(), fontSize, 1);

        //draw the text (using the text size to help draw it in the corner
        //(font,c string, vector2, font size, font spaceing, color)
        DrawTextEx(font, this->name.c_str(), { this->x - (textSize.x / 2), this->y - (textSize.y / 2) }, fontSize, 1, ColorFromNormalized({ fontRed,fontGreen,fontBlue,1.0f }));
    }

    
 
};

class Circle : public Shape {
public:

    float radius;

    Circle(float x, float y, float velX, float velY, int colorR, int colorG, int colorB,std::string name, float radius):Shape(x,y,velX,velY,colorR,colorG,colorB,name), radius(radius) {}

    void update() override{
        x += velX;
        y += velY;
         if (x - radius*scale <= 0.0f || x + radius*scale >= screenWidth) { //circle hits the left or right side
             velX = -velX;// flip direction of x velocity
         }
         if (y - radius*scale <= 0.0f || y + radius*scale >= screenHeight) { //circle hits the top or bottom
             velY = -velY; // flip direction of y velocity
         }

    }
    void render() override{
        DrawCircle((int)x, (int)y, radius*scale, ColorFromNormalized({ color[0],color[1],color[2],1.0f}));
    }

};

class Rect : public Shape {
public:
    
    float height;
    float width;

    Rect(float x, float y, float velX, float velY, int colorR, int colorG, int colorB,std::string name, float height, float width):Shape(x, y, velX, velY, colorR, colorG, colorB,name), height(height), width(width) {}
    

    void update() override {
        x += velX;
        y += velY;
        if (x <= 0.0 || x + width*scale >= screenWidth) {
            velX = -velX;// flip direction of x velocity
        }
        if (y <= 0.0 || y + height*scale >= screenHeight) {
            velY = -velY;// flip direction of x velocity
        }
    }
    void render()override {
        DrawRectangle((int)x, (int)y, (int)width * scale, (int)height * scale, ColorFromNormalized({ color[0],color[1],color[2], 1.0f }));
    }
   
    void renderText(Font font, int fontSize, float fontRed, float fontGreen, float fontBlue) {

        //get the size (x and y) of the text object
        //(font,c string, font size, font spaceing)
        Vector2 textSize = MeasureTextEx(font, this->name.c_str(), fontSize, 1);

        //draw the text (using the text size to help draw it in the corner
        //(font,c string, vector2, font size, font spaceing, color)
        DrawTextEx(font, this->name.c_str(), { this->x - (textSize.x / 2) + (width/2), this->y - (textSize.y / 2)+(height/2)}, fontSize, 1, ColorFromNormalized({fontRed,fontGreen,fontBlue,1.0f}));
    }

};
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    std::string windowName = "default";
    std::string fontFile;

    int fontSize;
    float fontRed;
    float fontGreen;
    float fontBlue;

    std::fstream configFile;
    configFile.open("assets/input.txt");

    std::vector<Shape*> container;
    std::string input;

    
    while (!configFile.eof()) {
        configFile >> input;

        if (input == "Window") {
            configFile >> windowName;

            configFile >> input;
            screenWidth = atoi(input.c_str());

            configFile >> input;
            screenHeight = atoi(input.c_str());
        }

        if (input == "Font") {
            configFile >> fontFile;
            configFile >> input;
            fontSize = atoi(input.c_str());

            configFile >> input;
            fontRed = atof(input.c_str());

            configFile >> input;
            fontGreen = atof(input.c_str());

            configFile >> input;
            fontBlue = atof(input.c_str());
        }

        if (input == "Circle") {
            float x, y, velX, velY, radius;
            int colorR, colorG, colorB;
            std::string name;
            configFile >> name;

            configFile >> input;
            x = atof(input.c_str());

            configFile >> input;
            y = atof(input.c_str());

            configFile >> input;
            velX = atof(input.c_str());

            configFile >> input;
            velY = atof(input.c_str());

            configFile >> input;
            colorR = atoi(input.c_str());

            configFile >> input;
            colorG = atoi(input.c_str()); 

            configFile >> input;
            colorB = atoi(input.c_str());

            configFile >> input;
            radius = atof(input.c_str());

            Circle* c = new Circle(x, y, velX, velY, colorR, colorG, colorB, name, radius);

            container.push_back(c);
        }
        if (input == "Rectangle") {
            float x, y, velX, velY, width,height;
            int colorR, colorG, colorB;
            std::string name;
            configFile >> name;

            configFile >> input;
            x = atof(input.c_str());

            configFile >> input;
            y = atof(input.c_str());

            configFile >> input;
            velX = atof(input.c_str());

            configFile >> input;
            velY = atof(input.c_str());

            configFile >> input;
            colorR = atoi(input.c_str());

            configFile >> input;
            colorG = atoi(input.c_str());

            configFile >> input;
            colorB = atoi(input.c_str());

            configFile >> input;
            width = atof(input.c_str());

            configFile >> input;
            height = atof(input.c_str());

            Rect* r = new Rect(x, y, velX, velY, colorR, colorG, colorB, name, width,height);

            container.push_back(r);
        }
    }
    configFile.close();   // Close config file

    
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, windowName.c_str());
    
    //initialize the raylib ImGui backend
    rlImGuiSetup(true);
    //increase ImGui item size to 2x
    ImGui::GetStyle().ScaleAllSizes(2);

    // Set raylib to target 60 frames-per-second (this does not mean it will actually RUN at 60 fps)
    SetTargetFPS(60);      
    
    //read in config file
   

    // General variables
    //--------------------------------------------------------------------------------------

    //shape properties to draw on the screen (circle for this example)
    //units of size and speed are in pixels
    //color is from 0-1

    int current = 0;
    bool isActive = true;
    
   
    std::vector<const char*> names;
    for (Shape* shape : container) {
        
        names.push_back((shape->name).c_str());
        std::cout << shape->name << std::endl;
    }
    

    
    //Let's draw some text to the screen too
    bool drawText=true;
    std::string strText= "Some Text";
    std::string newText= strText;

    //load a font (Raylib gives warning if font can't be found, then uses default as fallback)
    Font font = LoadFont(fontFile.c_str());

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        //move circle
       
        //circ1.update(circ1.x,circ1.y, circ1.velX, circ1.velY );

        for (auto shape : container) {
            
                shape->update();
          
      }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            //********** Raylib Drawing Content **********

            //draw the cricle (center x, center y, radius, color(r,g,b,a))
            if(isActive){
                for (auto shape : container) {
                    shape->render();
             }
            }

           
                
            //draw the text
            if(drawText){
                for (auto shape : container) {
                    shape->renderText(font,fontSize,fontRed,fontGreen,fontBlue);
                }
                
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
                    ImGui::Checkbox("Draw Shapes",&isActive);
                    ImGui::SameLine();
                    ImGui::Checkbox("Draw Text",&drawText);

                    //slider, again directly modifies the value and limites between 0 and 300 for this example
                    ImGui::SliderFloat("Scale", &container.at(current)->scale,1.0f,25.0f);

                    //slider to adjust both x and y velocity
                    ImGui::SliderFloat("X Velocity",&container.at(current)->velX, 0.0f, 300.0f);
                    ImGui::SliderFloat("Y Velocity",&container.at(current)->velY, 0.0f, 300.0f);
                    
                    //color picker button, directly modifies the color (3 element float array)
                    ImGui::ColorEdit3("Color",container.at(current)->color);
                    
                    //text input field, directly modifies the string
                    ImGui::InputText("Text",&newText);


                    ImGui::Combo("Shape", &current, names.data(), names.size());
         
                    //buttons, returns true if clicked on this frame
                    if(ImGui::Button("Set Text")){
                        container.at(current)->name = newText;
                    }

                    //The next item will be on the same line as the previous one
                    ImGui::SameLine();

                    //Another button
                    if(ImGui::Button("Reset")){
                        container.at(current)->x=50.0;
                        container.at(current)->y=50.0;
                        container.at(current)->scale=1;
                        container.at(current)->velX = 1.0f;
                        container.at(current)->velY = 0.5f;
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
   
    //--------------------------------------------------------------------------------------

    return 0;
}