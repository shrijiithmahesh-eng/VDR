//Note: compile this to ./EDITOR
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

typedef uint32_t u32;
#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 1026
#define SCREEN_HEIGHT 576

// Function to save the buffer
void SaveFile(const char *filename, const char *content) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fprintf(f, "%s", content);
    fclose(f);
    printf("\n[SUCCESS] Saved to: %s\n", filename);
}

int main(int argc, char *argv[]) {
    char currentFilename[256] = "unnamed.osp";
    char title[300];

    // Capture filename from command line
    if (argc > 1) {
        strncpy(currentFilename, argv[1], 255);
    }
    sprintf(title, "OSDPLTE - Editing: %s", currentFilename);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        printf("SDL/TTF Init Failed!\n");
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("font.ttf", 24); 
    if (!font) {
        printf("Font Error: font.ttf not found in current folder!\n");
        return 1;
    }

    char text[5000] = ""; 
    SDL_Color white = {255, 255, 255, 255};
    SDL_StartTextInput();

    int running = TRUE;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = FALSE;
            } 
            else if (e.type == SDL_KEYDOWN) {
                // Backspace logic
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0) {
                    text[strlen(text) - 1] = '\0';
                }
                // Save logic: Ctrl + S
                if (e.key.keysym.sym == SDLK_s && (SDL_GetModState() & KMOD_CTRL)) {
                    SaveFile(currentFilename, text);
                }
              //enter logic
              if (e.key.keysym.sym == SDLK_RETURN) {
    strcat(text, "\n");
}
            }
            else if (e.type == SDL_TEXTINPUT) {
                if (strlen(text) < 4999) {
                    strcat(text, e.text.text);
                }
            }
        }

        // Render Background
        SDL_SetRenderDrawColor(ren, 20, 20, 25, 255);
        SDL_RenderClear(ren);

        // Render Text
        if (strlen(text) > 0) {
            SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font, text, white, SCREEN_WIDTH - 40);
            if (surf) {
                SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
                SDL_Rect dest = { 20, 20, surf->w, surf->h };
                SDL_RenderCopy(ren, tex, NULL, &dest);
                SDL_FreeSurface(surf);
                SDL_DestroyTexture(tex);
            }
        }

        SDL_RenderPresent(ren);
    }

    // Cleanup
    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
