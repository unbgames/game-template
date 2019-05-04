#include "sdl2include.h"
#include "log.h"
#include "sdl_log.h"

#include "config.h"

#ifdef _WIN32
int WinMain(int, char**)
#else
int main(int, char**)
#endif
{
    INFO("Assest como from: " << GAME_ASSETS_FOLDER);

    // ===== Init dependencies =====
    INFO("Init dependencies");

    INFO("Init sdl");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_ERROR("Could not initialize video or audio");
        std::exit(EXIT_FAILURE);
    }

    INFO("Init sdl image");
    int img_flags = IMG_INIT_PNG;
    if(!(IMG_Init(img_flags) & img_flags))
    {
        SDL_IMG_ERROR("Could not initialize sdl image");
        std::exit(EXIT_FAILURE);
    }

    INFO("Initialize SDL_ttf");
    if( TTF_Init() == -1 )
    {
        SDL_TTF_ERROR( "SDL_ttf could not initialize!");
        std::exit(EXIT_FAILURE);
    }

    INFO("Initialize SDL_mixer");
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        SDL_MIX_ERROR( "SDL_mixer could not initialize!");
        std::exit(EXIT_FAILURE);
    }


    // ===== Create Window and Canvas =====

    INFO("Create Window");
    SDL_Window * window = SDL_CreateWindow(
        "Game",                 // Title
        SDL_WINDOWPOS_CENTERED, // Position x. SDL_WINDOWPOS_UNDEFINED
        SDL_WINDOWPOS_CENTERED, // Position y. SDL_WINDOWPOS_UNDEFINED
        400,                    // width
        400,                    // height
        SDL_WINDOW_SHOWN        // Window flags, SDL_WindowFlags for more
    );

    if (window == NULL)
    {
        SDL_ERROR("Could not create window");
        std::exit(EXIT_FAILURE);
    }

    INFO("Create canvas");
    SDL_Renderer * canvas = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (canvas == NULL)
    {
        SDL_ERROR("Could not create canvas");
        std::exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(canvas, 200, 200, 200, 0xff);


    // ===== Load Texture =====

    INFO("Load Texture");
    SDL_Texture * play_button_texture = NULL;

    SDL_Surface * image = NULL;
    image = IMG_Load(ASSETS_PATH("/sprites/image.png"));

    if (image == NULL)
    {
        SDL_IMG_ERROR("Can't load sprite");
        std::exit(EXIT_FAILURE);
    }

    play_button_texture = SDL_CreateTextureFromSurface(canvas, image);

    if (play_button_texture == NULL)
    {
        SDL_ERROR("Can't create texture from image");
        std::exit(EXIT_FAILURE);
    }

    int play_button_w = image->w;
    int play_button_h = image->h;

    SDL_FreeSurface(image);
    image = NULL;

    // ===== Font and Text =====

    TTF_Font * font = NULL;

    font = TTF_OpenFont(ASSETS_PATH("/fonts/font.ttf"), 28);
    if(font == NULL)
    {
        SDL_TTF_ERROR("Could not load font.ttf");
        std::exit(EXIT_FAILURE);
    }

    SDL_Texture * text_texture = NULL;
    SDL_Color text_color = {0, 0, 0, 255};

    int text_w = 0, text_h = 0;
    SDL_Surface * text_surface = TTF_RenderText_Solid(font, "IJE - FGA",
                                                      text_color);

    if( text_surface == NULL )
    {
        SDL_TTF_ERROR("Could not render text!");
    }
    else
    {
        text_texture = SDL_CreateTextureFromSurface(canvas, text_surface);
        if( text_texture == NULL )
        {
            SDL_ERROR("Unable to create texture from rendered text!");
        }

        text_w = text_surface->w;
        text_h = text_surface->h;

        SDL_FreeSurface(text_surface);
    }

    // ===== Music =====

    Mix_Music * music = Mix_LoadMUS(ASSETS_PATH("/sounds/music.ogg"));

    if(music == NULL)
    {
        SDL_MIX_ERROR( "Failed to load beat music!");
        std::exit(EXIT_FAILURE);
    }

    Mix_PlayMusic(music, -1);

    // ===== Main Loop =====

    INFO("Game Loop: START");
    bool close_game = false;

    while(!close_game)
    {
        // Read Input
        SDL_Event evt;
        while(SDL_PollEvent(&evt) != 0)
        {
            if (evt.type == SDL_QUIT)
                close_game = true;
        }

        // Draw
        SDL_RenderClear(canvas);

        SDL_Rect renderQuad = {112, 122, play_button_w, play_button_h};
        SDL_RenderCopy(canvas, play_button_texture, NULL, &renderQuad);

        SDL_Rect renderQuad2 = {150, 300, text_w, text_h};
        SDL_RenderCopy(canvas, text_texture, NULL, &renderQuad2);

        SDL_RenderPresent(canvas);
    }

    INFO("Game Loop: END");


    // ===== Shutdown =====

    INFO("Shutdown");

    INFO("Destroy texture");
    SDL_DestroyTexture(play_button_texture);
    play_button_texture = NULL;

    INFO("Destroy text");
    SDL_DestroyTexture(text_texture);
    text_texture = NULL;

    INFO("Close font");
    TTF_CloseFont(font);
    font = NULL;

    INFO("Destroy Music")
    Mix_FreeMusic(music);
    music = NULL;

    INFO("Destroy canvas");
    SDL_DestroyRenderer(canvas);
    canvas = NULL;

    INFO("Destroy window");
    SDL_DestroyWindow(window);
    window = NULL;

    INFO("Quit MIX");
    Mix_Quit();
    INFO("Quit TTF");
    TTF_Quit();
    INFO("Quit IMG");
    IMG_Quit();
    INFO("Quit SDL");
    SDL_Quit();

    return 0;
}
