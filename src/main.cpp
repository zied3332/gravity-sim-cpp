#include "raylib.h"
#include <vector>
#include <cmath>

struct Body {
    Vector2 position;
    Vector2 velocity;
    float mass;
    float radius;
    Color color;
};

float distance(Vector2 a, Vector2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Gravity Simulation - C++");
    SetTargetFPS(60);

    const float G = 0.4f;

    std::vector<Body> bodies = {
        {{500, 350}, {0, 0}, 9000, 25, YELLOW},
        {{300, 350}, {0, -3.0f}, 20, 8, BLUE},
        {{700, 350}, {0, 3.0f}, 20, 8, RED},
        {{500, 150}, {3.2f, 0}, 15, 7, GREEN}
    };

    bool paused = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) paused = !paused;

        if (IsKeyPressed(KEY_R)) {
            bodies = {
                {{500, 350}, {0, 0}, 9000, 25, YELLOW},
                {{300, 350}, {0, -3.0f}, 20, 8, BLUE},
                {{700, 350}, {0, 3.0f}, 20, 8, RED},
                {{500, 150}, {3.2f, 0}, 15, 7, GREEN}
            };
        }

        if (!paused) {
            for (int i = 0; i < bodies.size(); i++) {
                Vector2 force = {0, 0};

                for (int j = 0; j < bodies.size(); j++) {
                    if (i == j) continue;

                    Vector2 direction = {
                        bodies[j].position.x - bodies[i].position.x,
                        bodies[j].position.y - bodies[i].position.y
                    };

                    float dist = distance(bodies[i].position, bodies[j].position);
                    if (dist < 10) dist = 10;

                    float strength = (G * bodies[i].mass * bodies[j].mass) / (dist * dist);

                    direction.x /= dist;
                    direction.y /= dist;

                    force.x += direction.x * strength;
                    force.y += direction.y * strength;
                }

                Vector2 acceleration = {
                    force.x / bodies[i].mass,
                    force.y / bodies[i].mass
                };

                bodies[i].velocity.x += acceleration.x;
                bodies[i].velocity.y += acceleration.y;
            }

            for (auto& body : bodies) {
                body.position.x += body.velocity.x;
                body.position.y += body.velocity.y;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Gravity Simulation", 20, 20, 28, WHITE);
        DrawText("SPACE: Pause | R: Reset | ESC: Exit", 20, 60, 18, GRAY);

        for (const auto& body : bodies) {
            DrawCircleV(body.position, body.radius, body.color);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}