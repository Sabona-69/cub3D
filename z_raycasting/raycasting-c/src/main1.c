#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mlx.h"

#define FALSE 0
#define TRUE 1

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define MAP_NUM_ROWS 12
#define MAP_NUM_COLS 28

#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

#define FPS 120

char *map[MAP_NUM_ROWS] = {
    "1111111111111111111111111111",
    "1000000000000000000000000001",
    "1000000000000000000000000001",
    "1010101010000000000000000001",
    "1000000000000000000000000001",
    "1000000000000000000000000001",
    "1000000000000000000000000001",
    "1000000000000000000000000001",
    "1011111110000000000000000001",
    "1000000000000000000000000001",
    "1000000000000000000000000001",
    "1111111111111111111111111111"
};

struct Player {
    float x;
    float y;
    float rotationAngle;
    float walkSpeed; // Speed is now the step size for movement
    float turnSpeed;
    int turnDirection; // -1 for left, +1 for right
    int walkDirection; // -1 for back, +1 for front
};

struct Game {
    void *mlx_ptr;
    void *win_ptr;
    struct Player player;
    int isGameRunning;
    clock_t lastFrameTime;
};

int initializeWindow(struct Game *game) {
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr) {
        fprintf(stderr, "Error initializing MLX.\n");
        return 0;
    }
    game->win_ptr = mlx_new_window(game->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Game Window");
    if (!game->win_ptr) {
        fprintf(stderr, "Error creating MLX window.\n");
        return 0;
    }
    return 1;
}

void destroyWindow(struct Game *game) {
    if (game->win_ptr) {
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
        game->win_ptr = NULL;
    }
}

void setup(struct Game *game) {
    game->player.x = WINDOW_WIDTH / 2;
    game->player.y = WINDOW_HEIGHT / 2;
    game->player.rotationAngle = 0; // Start facing right
    game->player.walkSpeed = 100.0; // Set the speed to 2 pixels per movement
    game->player.turnSpeed = 20 * (PI / 180); // Turn speed (5 degrees per frame)
    game->player.walkDirection = 0; // Initialize walk direction to 0
    game->player.turnDirection = 0; // Initialize turn direction to 0
    game->isGameRunning = 1; // Initialize game state
    game->lastFrameTime = clock(); // Initialize last frame time
}

int mapHasWallAt(float x, float y) {
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = (int)(x / TILE_SIZE);
    int mapGridIndexY = (int)(y / TILE_SIZE);

    return map[mapGridIndexY][mapGridIndexX] == '1'; // Check for wall (1)
}

void movePlayer(struct Game *game, float deltaTime) {
    // Gradually turn the player based on turnDirection
    game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed;

    // Normalize the angle to be between 0 and 2*PI
    if (game->player.rotationAngle < 0) game->player.rotationAngle += TWO_PI;
    if (game->player.rotationAngle > TWO_PI) game->player.rotationAngle -= TWO_PI;

    // Only move the player if there is a walk direction
    if (game->player.walkDirection != 0) {
        // Calculate movement based on walkSpeed
        float moveStep = game->player.walkSpeed * game->player.walkDirection * deltaTime; // Use walkSpeed for movement

        // Calculate new player position
        float newPlayerX = game->player.x + cos(game->player.rotationAngle) * moveStep;
        float newPlayerY = game->player.y + sin(game->player.rotationAngle) * moveStep;

        // Check for walls before updating position
        if (!mapHasWallAt(newPlayerX, newPlayerY)) {
            game->player.x = newPlayerX;
            game->player.y = newPlayerY;
        }
    }
}

void renderMap(struct Game *game) {
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            int tileColor = map[i][j] == '1' ? 0xFFFFFF : 0x000000; // White for walls, black for empty

            // Draw the tile
            for (int x = 0; x < TILE_SIZE; x++) {
                for (int y = 0; y < TILE_SIZE; y++) {
                    mlx_pixel_put(game->mlx_ptr, game->win_ptr, tileX + x, tileY + y, tileColor);
                }
            }
        }
    }
}

void renderPlayer(struct Game *game) {
    // Player color
    int playerColor = 0xFF0000; // Red color for the player
    int directionColor = 0x00FF00; // Green color for the direction line

    // Draw player as a circle
    int playerSize = 5; // Size of the player (5x5 square)

    // Draw a circle representing the player
    for (int x = -playerSize; x <= playerSize; x++) {
        for (int y = -playerSize; y <= playerSize; y++) {
            if (x * x + y * y <= playerSize * playerSize) { // Circle condition
                mlx_pixel_put(game->mlx_ptr, game->win_ptr, (int)(game->player.x) + x, (int)(game->player.y) + y, playerColor);
            }
        }
    }

    // Draw direction line
    for (int i = 0; i < 40; i++) { // Length of the direction line
        int lineX = (int)(game->player.x + cos(game->player.rotationAngle) * i);
        int lineY = (int)(game->player.y + sin(game->player.rotationAngle) * i);
        mlx_pixel_put(game->mlx_ptr, game->win_ptr, lineX, lineY, 0xFFFFFF);
    }
}

int handleKeyPress(int keycode, struct Game *game) {
    if (keycode == 53) { // ESC key
        game->isGameRunning = 0;
    }
    if (keycode == 13) { // W key
        game->player.walkDirection = +1;
    }
    if (keycode == 1) { // S key
        game->player.walkDirection = -1;
    }
    if (keycode == 2) { // D key
        game->player.turnDirection = +1; // Turn right
    }
    if (keycode == 0) { // A key
        game->player.turnDirection = -1; // Turn left
    }
    return 0;
}

int handleKeyRelease(int keycode, struct Game *game) {
    if (keycode == 13 || keycode == 1) { // W or S key released
        game->player.walkDirection = 0;
    }
    if (keycode == 2 || keycode == 0) { // D or A key released
        game->player.turnDirection = 0;
    }
    return 0;
}

void update(struct Game *game) {
    clock_t currentTime = clock();
    float deltaTime = (float)(currentTime - game->lastFrameTime) / CLOCKS_PER_SEC;
    game->lastFrameTime = currentTime;

    movePlayer(game, deltaTime);
}

void render(struct Game *game) {
    mlx_clear_window(game->mlx_ptr, game->win_ptr);
    renderMap(game);
    renderPlayer(game);
}

int main() {
    struct Game game;
    
    if (!initializeWindow(&game)) {
        return 1; // Exit if window initialization fails
    }
    setup(&game);

    // Hook for both key press and release events
    mlx_hook(game.win_ptr, 2, 1L << 0, (int (*)())handleKeyPress, &game);    // Key press
    mlx_hook(game.win_ptr, 3, 1L << 1, (int (*)())handleKeyRelease, &game);  // Key release

    while (game.isGameRunning) {
        update(&game);
        render(&game);
        mlx_do_sync(game.mlx_ptr);
    }
    destroyWindow(&game);
    return 0;
}
