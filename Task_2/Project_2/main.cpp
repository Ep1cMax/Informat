#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 

void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);

        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {

    setlocale(LC_CTYPE, "rus");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Application for graphs display");

    sf::CircleShape userPoint(5);
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    sf::Font New_Font;
    if (!New_Font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(New_Font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);


    std::string zone;
    sf::Text ZoneText;
    ZoneText.setFont(New_Font);
    ZoneText.setCharacterSize(20);
    ZoneText.setFillColor(sf::Color::White);
    ZoneText.setPosition(10, 30);

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); 
    xAxis[0].color = sf::Color::White; 
    xAxis[1].position = sf::Vector2f(750, 300);
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50);
    yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 550);
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();



            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    float mathX = (mousePos.x - 400) / 30.0f; 
                    float mathY = -(mousePos.y - 300) / 100.0f; 

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; 

                    if ((mathY == -0.1 * mathX * mathX + 4 / 10.0f) or (mathY == abs(mathX))) { zone = "Edge"; }
                    else {
                        if ((mathY < -0.1 * mathX * mathX + 4 / 10.0f) and (mathY > abs(mathX))) { zone = "1"; }
                        else {
                            if ((mathY > -0.1 * mathX * mathX + 4 / 10.0f) and (mathY > abs(mathX))) { zone = "2"; }
                            else {
                                if ((mathY < -0.1 * mathX * mathX + 4 / 10.0f) and (mathY < abs(mathX))) { zone = "3"; }
                                else {
                                    if ((mathY > -0.1 * mathX * mathX + 4 / 10.0f) and (mathY < abs(mathX)) and (mathX < 0)) { zone = "4"; }
                                    else {
                                        if ((mathY > -0.1 * mathX * mathX + 4 / 10.0f) and (mathY < abs(mathX)) and (mathX > 0)) { zone = "5"; }
                                    }
                                }
                            }
                        }
                    }

                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ")");
                    ZoneText.setString("Zone: (" + (zone) + ")");
                }
            }
        }


        window.clear();


        window.draw(xAxis);
        window.draw(yAxis);



        drawGraph(window, [](float x) { return abs(x); }, -10, 10, 300, 1000, sf::Color::Blue);

        drawGraph(window, [](float x) { return -(0.1*pow(x, 2)) + 4 / 10.0f; }, -10, 10, 30, 100, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
            window.draw(ZoneText);
        }


        window.display();
    }

        return 0;
    
}