#include "window.h"

int runWindow(vector<vector<Ponto>> vvp, vector<vector<Triangulo>> vt){
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // Handle initialization error
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1280, 720,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // Handle window creation error
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        // Handle renderer creation error
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Sample vector of points
    vector<vector<SDL_Point>> points;
    vector<SDL_Point> pontos, pontos_null;
    for(int k = 0; k < vvp.size(); k++){
        for (int i = 0; i < vvp[k].size(); i++){
            int y = static_cast<int>((1 + vvp[k][i].x) * 160);
            int x = static_cast<int>((4 + vvp[k][i].y) * 160); 
            pontos.push_back(SDL_Point{ x, y });
        }
        points.push_back(pontos);
        pontos = pontos_null;
    }

    // Sample vector of triangles
    vector<vector<SDL_Point>> pp_triangle;
    vector<SDL_Point> points_triangle;
    for(int k = 0; k < vt.size(); k++){
        for (int i = 0; i < vt[k].size(); i++){
                int y = static_cast<int>((1 + vt[k][i].p1.x) * 160);
                int x = static_cast<int>((4 + vt[k][i].p1.y) * 160); 
                points_triangle.push_back(SDL_Point{ x, y });
                y = static_cast<int>((1 + vt[k][i].p2.x) * 160);
                x = static_cast<int>((4 + vt[k][i].p2.y) * 160); 
                points_triangle.push_back(SDL_Point{ x, y });
                y = static_cast<int>((1 + vt[k][i].p3.x) * 160);
                x = static_cast<int>((4 + vt[k][i].p3.y) * 160); 
                points_triangle.push_back(SDL_Point{ x, y });
            }
        pp_triangle.push_back(points_triangle);
        points_triangle = pontos_null;
    }

    // Main event loop 
    bool quit = false;
    SDL_Event event;

    int counter = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        cout << counter << endl;
        counter++;

        // Set the background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Grayish color

        // Clear the window with the background color
        SDL_RenderClear(renderer);

        // Set the color for the points
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Black color

        // Loop through each point in the vector
        for (int i = 0; i < points.size(); i++){
            for (int j = 0; j < points[i].size(); j++){
                SDL_RenderDrawPoint(renderer,points[i][j].x, points[i][j].y);
            }
        }

        // Set the color for the lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Black color

        // Loop through each point in the vector (except the last one)
        //for (int i = 0; i < points.size(); i++){
        //    for (size_t j = 0; j < points[i].size() - 1; ++j) {
        //       // Draw a line between the current point and the next point
        //        SDL_RenderDrawLine(renderer, points[i][j].x, points[i][j].y, points[i][j + 1].x, points[i][j + 1].y);
        //    }
        //}
//
        //// Draw a line between the last point and the first point to close the loop
        //for (int i = 0; i < points.size(); i++){
        //    SDL_RenderDrawLine(renderer, points[i].back().x, points[i].back().y, points[i].front().x, points[i].front().y);
        //}

        for (int k = 0; k < pp_triangle.size(); k++){
            for (int i = 0; i < pp_triangle[k].size() ; i++){
                if (300*k + 60*i < counter)
                    if ((i+1)%3 != 0)
                        SDL_RenderDrawLine(renderer, pp_triangle[k][i].x, pp_triangle[k][i].y, pp_triangle[k][i+1].x, pp_triangle[k][i+1].y);
                    else 
                        SDL_RenderDrawLine(renderer, pp_triangle[k][i].x, pp_triangle[k][i].y, pp_triangle[k][i-2].x, pp_triangle[k][i-2].y);
            }
        }


        // Update the window
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
