#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*b2,*character,*character2,*character3,*character4, *my_image;
SDL_Rect rect_background,rect_b2,rect_character,rect_character2,rect_character3,rect_character4, my_rect;
int screen_width = 500;
int screen_height = 250;
bool estaColisionando(SDL_Rect a, SDL_Rect b)
{
    a= rect_character3;
    b= rect_character4;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}
int main( int argc, char* args[] )
{
    int i=0;
//Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
//Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }

//SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }
    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;
    b2 = IMG_LoadTexture(renderer,"fondo2.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_b2.x = 1200;
    rect_b2.y = 0;
    rect_b2.w = 1200;
    rect_b2.h = 600;
    character3 = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character3.x = 0;
    rect_character3.y = 300;
    rect_character3.w = 200;
    rect_character3.h = 300;
    character2 = IMG_LoadTexture(renderer, "algo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character2.x = 0;
    rect_character2.y = 0;
    rect_character2.w = 400;
    rect_character2.h = 200;
    character = IMG_LoadTexture(renderer, "suelo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 500;
    rect_character.w = 1200;
    rect_character.h = 200;
    character4 = IMG_LoadTexture(renderer, "cerebro.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character4.x = 1000;
    rect_character4.y = 530;
    rect_character4.w = 50;
    rect_character4.h = 50;
    my_image = IMG_LoadTexture(renderer, "image.png");
    my_rect.x = 1200;
    my_rect.y = 600;
    my_rect.w = 50;
    my_rect.h = 50;
    int velocidad = 5;
//Main Loop
    char orien= 'r';
    bool game_over = false;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            i++;
//mover background
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_background.x--;
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_character4.x--;
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_b2.x--;
                if(Event.key.keysym.sym == SDLK_LEFT)
                    rect_background.x++;
                if(Event.key.keysym.sym == SDLK_LEFT)
                    rect_b2.x++;
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
// zombie y energy
        if( currentKeyStates[ SDL_SCANCODE_UP ] )
        {
            rect_character3.y--;
        }
        if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
        {
            rect_character3.y++;
        }
        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            rect_character3.x--;
        }
        if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        {
            rect_character3.x++;
        }
//mover y regresar
        if(rect_character2.x>400)
        {
            orien='l';
        }
        if(rect_character2.x<200)
        {
            orien='r';
        }
        if(orien == 'r')
        {
            rect_character2.x+=2;
        }
        if(orien == 'l')
        {
            rect_character2.x-=2;
        }
        int x_anterior = rect_character.x;
        if(estaColisionando(rect_character,my_rect))
        {
            rect_character3.x = x_anterior;
        }
        if(estaColisionando(rect_character,my_rect)==true)
        {

        }
        SDL_Delay(10);
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, b2, NULL, &rect_b2);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderCopy(renderer, character2, NULL, &rect_character2);
        SDL_RenderCopy(renderer, character3, NULL, &rect_character3);
        SDL_RenderCopy(renderer, character4, NULL, &rect_character4);
        SDL_RenderCopy(renderer, my_image, NULL, &my_rect);
        SDL_RenderPresent(renderer);
    }
    return 0;
}
