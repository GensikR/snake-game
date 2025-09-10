#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <queue>

#define INITIAL_HEIGHT 25
#define INITIAL_LENGTH 100
#define SCREEN_WIDTH 720u
#define SCREEN_HEIGHT 720u
#define INITIAL_X (SCREEN_WIDTH / 2)
#define INITIAL_Y (SCREEN_HEIGHT / 2)
#define FOOD_HEIGHT 25
#define FOOD_LENGTH 25
#define RIGHT 0
#define LEFT 1
#define UP 3
#define DOWN 2
#define SNAKE_BODY_LENGHT 20
#define SNAKE_BODY_HEIGHT 20


class Snake
{
public:
    struct SnakeBlock
    {
        sf::RectangleShape snake_rect;
        sf::Vector2f block_pos;
    };

private:
    std::deque<SnakeBlock> body_parts; // front = head, back = tail
    int snake_length;
    SnakeBlock template_block; // template for new blocks

public:
    // Constructors
    Snake(int length)
    {
        setSnakeLength(length);
        setTemplateBlock();
        for (int i = 0; i < length; i++)
            body_parts.push_back(template_block);
    }

    Snake()
    {
        setSnakeLength(4);
        setTemplateBlock();
        body_parts.push_back(template_block);
    }

    // Set snake length
    void setSnakeLength(int length)
    {
        snake_length = length;
    }

    // Initialize template block
    void setTemplateBlock()
    {
        template_block.snake_rect.setSize(sf::Vector2f(SNAKE_BODY_LENGHT, SNAKE_BODY_HEIGHT));
        template_block.block_pos = sf::Vector2f(0, 0);
    }

    // Add a new head block at front
    void addHeadBlock(sf::Vector2f pos)
    {
        SnakeBlock new_block = template_block;
        new_block.block_pos = pos;
        new_block.snake_rect.setPosition(pos);
        body_parts.push_front(new_block);
    }

    // Increase length by adding blocks to the tail
    void increaseLength(int n)
    {
        snake_length += n;
        for (int i = 0; i < n; i++)
            body_parts.push_back(template_block);
    }

    // Access head and tail
    SnakeBlock& getHead()
    {
        return body_parts.front(); // head = front
    }

    SnakeBlock& getTail()
    {
        return body_parts.back();  // tail = back
    }

};




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
    int snake_speed = 4;

    srand(static_cast<unsigned>(time(0)));
    int food_x_pos = rand() % SCREEN_WIDTH;
    int food_y_pos = rand() % SCREEN_HEIGHT; 
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

        //Move Food if snake eats it
        auto snake_food_intersect = snake.getGlobalBounds().findIntersection(food.getGlobalBounds());
        if(snake_food_intersect)
        {
            food_x_pos = rand() % (SCREEN_WIDTH - 100);
            food_y_pos = rand() % (SCREEN_HEIGHT - 100);
            food_pos.x = food_x_pos;
            food_pos.y = food_y_pos;
            food.setPosition(food_pos);
        }

        // Render everything
        window.clear();
        window.draw(snake);
        window.draw(food);
        window.display();
    }
}
