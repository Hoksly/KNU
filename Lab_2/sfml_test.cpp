#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const float POINT_RADIUS = 2.f;

struct Point
{
    int x;
    int y;
};


void swp(std::vector<int> &mas, int n1, int n2)
{
    int t;
    t = mas[n1];
    mas[n1] = mas[n2];
    mas[n2] = t;
    //delete &t;

}

double is_right(Point A, Point B, Point C)
{
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);

}

std::vector<Point> ballon(std::vector<Point> &A)
{

    std::vector<int> P(A.size());
    //bool deleted[len_a];

    for(int i = 0; i < A.size(); i++)
        P[i] = i;
    

    for (int i = 1; i < A.size(); i++)
    {
        if(A[P[i]].x < A[P[0]].x)
            swp(P, 0, i);
    }

    std::vector<int> H;
   
    H.push_back(P[0]);
    int right;
    int c = 0;
    do
    {   
        //cout << "HERER1" << endl;
        right = 0;
        for (int i = 1; i < P.size(); i++)
        {
            if(is_right(A[H[H.size()-1]], A[P[right]], A[P[i]]) <= 0)
                {right = i; c++;}
            
        }
        
        //std::cout << right << std::endl;
       
        
        if(P[right] == H[0])
        {
            //cout << "HERE" << H[0] << endl;
            break;
        }
            
        else
        {

            H.push_back(P[right]);
            P.erase(P.begin() + right);
        }
        //pr_vector(H);
        //pr_vector(P);
    }while (true);

    std::vector<Point> ret;
    for (int i = 0; i < H.size(); i++)
    {
        ret.push_back(A[H[i]]);
    }
    //std::cout << c << std::endl;
    return ret;

}

void pr_vector(std::vector<Point> A)
{
    std::cout << std::endl << A.size() << std::endl;
    for(int i = 0; i < A.size(); i++)
    {
        std::cout << '(' << A[i].x << ", " << A[i].y << ')' << std::endl;
    }
}




void draw_lines(sf:: RenderWindow &window)
{


    sf:: Vector2u a = window.getSize();
    //std::cout << a.x << ' ' << a.y << std::endl;


    sf::Vertex line1[] =
    {
        sf::Vertex(sf::Vector2f(0, HEIGHT/2)),
        sf::Vertex(sf::Vector2f(WIDTH, HEIGHT/2))
    };


    sf::Vertex line2[] =
    {
        sf::Vertex(sf::Vector2f(WIDTH/2, 0)),
        sf::Vertex(sf::Vector2f(WIDTH/2, HEIGHT))
    };
    //std::cout << a.x/2 << a.y << std::endl;


    line1[0].color = sf::Color::Black;
    line1[1].color = sf::Color::Black;

    line2[0].color = sf::Color::Black;
    line2[1].color = sf::Color::Black;

    window.draw(line1, 2, sf::Lines);
    window.draw(line2, 2, sf::Lines);
    
}

void draw_line(sf::RenderWindow &window, Point a, Point b)
{

    sf::Vertex line1[] =
    {
        sf::Vertex(sf::Vector2f(a.x, a.y)),
        sf::Vertex(sf::Vector2f(b.x, b.y))
    };


    line1[0].color = sf::Color::Black;
    line1[1].color = sf::Color::Black;

    window.draw(line1, 2, sf::Lines);

}

void draw_balloon(sf::RenderWindow &window, std::vector<Point> &A)
{
    std::cout << "drawing" << '\n'; 
    for(int i = 1; i < A.size(); i++)
        draw_line(window, A[i-1], A[i]);

    draw_line(window, A[0], A[A.size()-1]);

}


void draw_point(sf::RenderWindow &window, int x, int y)
{
    sf::CircleShape circle(POINT_RADIUS);
    circle.setFillColor(sf::Color::Black);
    circle.move(x, y);
    window.draw(circle);
}

void draw_points(sf::RenderWindow &window, std::vector<Point> P)
{
    for(int i = 0; i < P.size(); i++)
        draw_point(window, P[i].x, P[i].y);

}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
    
    window.setPosition(sf::Vector2i(50, 50));
    window.setFramerateLimit(30);

    sf::Vertex point(sf::Vector2f(15, 15), sf::Color::Black);

    std::vector<Point> points;

    bool drawing_balloon = false;
    int pr_vect_size = 0;


    

    
    

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    Point a;
                    a.x = event.mouseButton.x;a.y = event.mouseButton.y;
                    points.push_back(a);
                    //std::cout << "the right button was pressed" << std::endl;
                    //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    //std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                    {std::cout << "Pressed lest" << std::endl; drawing_balloon = !drawing_balloon;}
            }
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...
        // window.draw(...);
     
        //draw_lines(window);
        //draw_point(window, 10.0f, 10.0f);   
        draw_points(window, points);
        if(drawing_balloon)
            {std::vector<Point> a = ballon(points);
                draw_balloon(window, a);}


        // end the current frame
        window.display();
    }

    return 0;
}