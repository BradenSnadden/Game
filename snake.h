#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
enum class Direction{ None, Up, Down, Left, Right };
struct snakeSegment{
    snakeSegment(int x, int y) : position(x,y){}
    sf::Vector2i position;
};

class snake
{
private:

    void CheckCollision(); // Checking for collisions.
    std::vector<snakeSegment> m_snakeBody; // Segment vector.
    int m_size; // Size of the graphics.
    Direction m_dir; // Current direction.
    int m_speed; // Speed of the snake.
    int m_lives; // Lives.
    int m_score; // Score.
    bool m_lost; // Losing state.
    sf::RectangleShape m_bodyRect; // Shape used in rendering.
    
public:
    snake(int blockSize);
    ~snake();

    void SetDirection(Direction l_currentD);
    Direction GetDirection();
    int GetSpeed();
    sf::Vector2i GetPosition();
    int GetLives();
    int GetScore();
    void IncreaseScore();
    bool HasLost();
    void Lose(); // Handle losing here.
    void ToggleLost();
    void Extend(); // Grow the snake.
    void Reset(); // Reset to starting position.
    void Move(); // Movement method.
    void Tick(); // Update method.
    void Cut(int l_segments); // Method for cutting snake.
    void Render(sf::RenderWindow& l_window);
};

snake::snake(int blockSize){
    m_size = blockSize;
    m_bodyRect.setSize(sf::Vector2f(m_size-1, m_size-1));
    Reset();
}

snake::~snake()
{
}

void snake::SetDirection(Direction l_currentD){
    m_dir = l_currentD;
}

Direction snake::GetDirection(){
    return m_dir;
}
int snake::GetSpeed(){
    return m_speed;
}
sf::Vector2i snake::GetPosition(){
    return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1,1));
}
int snake::GetLives(){
    return m_lives;
}
int snake::GetScore(){
    return m_score;
}
void snake::IncreaseScore(){
    m_score++;
}
bool snake::HasLost(){
    return m_lost;
}
void snake::Lose(){
    m_lost = true;
} // Handle losing here.
void snake::ToggleLost(){
    m_lost = !m_lost;
}
void snake::Extend(){
    if (m_snakeBody.empty()){return;}
        snakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];
    if(m_snakeBody.size() > 1){
        snakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];
        if(tail_head.position.x == tail_bone.position.x){
            if(tail_head.position.y > tail_bone.position.y){
                m_snakeBody.push_back(snakeSegment(tail_head.position.x, tail_head.position.y + 1));
            } else {
                m_snakeBody.push_back(snakeSegment(tail_head.position.x, tail_head.position.y - 1));
            }
        }else if(tail_head.position.y == tail_bone.position.y){
            if(tail_head.position.x > tail_bone.position.x){
                m_snakeBody.push_back(snakeSegment(tail_head.position.x + 1, tail_head.position.y));
            } else {
                m_snakeBody.push_back(snakeSegment(tail_head.position.x - 1, tail_head.position.y));
            }
        }   
    } else {
        if(m_dir == Direction::Up){
            m_snakeBody.push_back(snakeSegment(tail_head.position.x, tail_head.position.y + 1));
        } else if (m_dir == Direction::Down){
            m_snakeBody.push_back(snakeSegment(tail_head.position.x, tail_head.position.y - 1));
        } else if (m_dir == Direction::Left){
            m_snakeBody.push_back(snakeSegment(tail_head.position.x + 1, tail_head.position.y));
        } else if (m_dir == Direction::Right){
            m_snakeBody.push_back(snakeSegment(tail_head.position.x - 1, tail_head.position.y));
    } 
}
}
void snake::Reset(){
    m_snakeBody.clear();
    m_snakeBody.push_back(snakeSegment(5,7));
    m_snakeBody.push_back(snakeSegment(5,6));
    m_snakeBody.push_back(snakeSegment(5,5));
    SetDirection(Direction::None); // Start off still.
    m_speed = 15;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
} // Reset to starting position.
void snake::Move(){
    for (int i = m_snakeBody.size() - 1; i > 0; --i){
        m_snakeBody[i].position = m_snakeBody[i - 1].position;
    }
    if (m_dir == Direction::Left){
        --m_snakeBody[0].position.x;
    } else if (m_dir == Direction::Right){
        ++m_snakeBody[0].position.x;
    } else if (m_dir == Direction::Up){
        --m_snakeBody[0].position.y;
    } else if (m_dir == Direction::Down){
        ++m_snakeBody[0].position.y;
}
} // Movement method.
void snake::Tick(){
    if (m_snakeBody.empty()){ return; }
        if (m_dir == Direction::None){ return; }
        Move();
        CheckCollision();
}
void snake::CheckCollision(){
    if(m_snakeBody.size() < 5){return;}

    for(auto itr = m_snakeBody.begin(); itr != m_snakeBody.end(); ++itr){
        if(itr->position == m_snakeBody.front().position){
            int segments = std::distance(m_snakeBody.end(),itr);
            Cut(segments);
            break;
        }
    }
}
void snake::Cut(int l_segments){
    for (int i = 0; i < l_segments; ++i){
        m_snakeBody.pop_back();
    }
    --m_lives;
        if (!m_lives){ Lose(); return; }
    }
void snake::Render(sf::RenderWindow& l_window){
    if (m_snakeBody.empty()){ return; }
    auto head = m_snakeBody.begin();
    m_bodyRect.setFillColor(sf::Color::White);
    m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
    l_window.draw(m_bodyRect);
    m_bodyRect.setFillColor(sf::Color::Green);
    for(auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr){
        m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
        l_window.draw(m_bodyRect);
    }
}
