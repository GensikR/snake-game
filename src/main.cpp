#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#define INITIAL_HEIGHT 25
#define INITIAL_LENGTH 100
#define SCREEN_WIDTH 1080u
#define SCREEN_HEIGHT 1920u
#define INITIAL_X (SCREEN_WIDTH / 2)
#define INITIAL_Y (SCREEN_HEIGHT / 2)
#define FOOD_HEIGHT 25
#define FOOD_LENGTH 25
#define RIGHT 0
#define LEFT 1
#define UP 3
#define DOWN 2

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Snake Game");
    window.setFramerateLimit(60);

    sf::Vector2f snake_pos(INITIAL_X, INITIAL_Y);
    sf::Vector2f initial_size(INITIAL_LENGTH, INITIAL_HEIGHT);
    sf::RectangleShape snake(initial_size);
    snake.setPosition(snake_pos);

    sf::Vector2i directions[] = 
    {
        {1, 0}, //right
        {-1, 0},//left
        {0, 1}, //up
        {0, -1} //down
    };
    int curr_dir = 0;
    int snake_speed = 1;

    srand(static_cast<unsigned>(time(0)));
    int food_x_pos = rand() % SCREEN_WIDTH;
    int food_y_pos = rand() % SCREEN_HEIGHT;  // Fix: should use SCREEN_HEIGHT
    sf::Vector2f food_pos(food_x_pos, food_y_pos);
    sf::Vector2f food_size(FOOD_LENGTH, FOOD_HEIGHT);
    sf::RectangleShape food(food_size);
    food.setPosition(food_pos);

    while (window.isOpen())
    {
        // Event loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Update snake position
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) curr_dir = UP;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) curr_dir = DOWN;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) curr_dir = RIGHT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) curr_dir = LEFT;
        snake_pos.x += directions[curr_dir].x * snake_speed;
        snake_pos.y += directions[curr_dir].y * snake_speed;
        snake.setPosition(snake_pos);

        // Render everything
        window.clear();
        window.draw(snake);
        window.draw(food);
        window.display();
    }
}
