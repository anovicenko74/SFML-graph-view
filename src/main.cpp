#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <iomanip> 
#include <vector> 
using namespace std;

void drawArrow(sf::RenderWindow& window, const sf::Vector2f& start, const sf::Vector2f& end) {
    // ��������� ���� ����� ������ � ���� X
    float angle = std::atan2(end.y - start.y, end.x - start.x);

    // ������� ����������� ��� �������
    sf::ConvexShape arrowHead;
    arrowHead.setPointCount(3); // ����������� ����� 3 �������

    // ������������� ���������� ������������
    arrowHead.setPoint(0, sf::Vector2f(0, -10)); // ������ ����� �������
    arrowHead.setPoint(1, sf::Vector2f(-5, 5));  // ����� ���� ���������
    arrowHead.setPoint(2, sf::Vector2f(5, 5));   // ������ ���� ���������

    // ������������� ��������� ����
    srand(static_cast<unsigned>(time(nullptr))); // �������������� ��������� ��������� �����
    sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256);
    arrowHead.setFillColor(randomColor);

    // ������������� �����������
    arrowHead.setPosition(end);
    arrowHead.setOrigin(0, 0); // ����� ������������ � (0,0)

    // ������� ������� ��� �����
    arrowHead.setRotation(angle * 180 / 3.14159); // ������ ���� ��� �� ������ �����

    // ������ ����� �� ������ �� �����
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::Black),
        sf::Vertex(end, sf::Color::Black)
    };
    window.draw(line, 2, sf::Lines);

    // ������ �����������
    window.draw(arrowHead);
}

int main()
{
    class EdgeList {
        private:
            std::vector<std::vector<int>> table;

        
        public:
            EdgeList() {
               this->table = { {1, 2}, {1, 3}, {1, 5}, {2, 1}, {2, 3}, {3, 1}, {3, 2}, {3, 4}, {3, 5}, {4, 3}, {4, 5}, {5, 3}, {5, 4}};
            }

            void print() const {
                for (const auto& row : table) {
                    std::cout << "{ ";
                    for (const auto& value : row) {
                        std::cout << value << " ";
                    }
                    std::cout << "} ";
                }

                std::cout << std::endl;
            }
    };
    auto edgeList = new EdgeList();
    edgeList->print();
    std::cout << std::endl;

    class TableGraph {
    private:
        std::vector<std::vector<int>> table;


    public:
        TableGraph() {
            this->table = { {0, 1, 1, 0, 1}, {1, 0, 1, 0, 0}, {1, 1, 0, 1, 1}, {0, 0, 1, 0, 1}, {0, 0, 1, 1, 0} };
        }

        void print() const {
            std::cout << std::setw(3) << "1" << std::setw(2) << "2" << std::setw(2) << "3" << std::setw(2) << "4" << std::setw(2) << "5" << std::endl;
            int i = 0;
            for (const auto& row : table) {
                i++;
                std::cout << std::setw(1) << i << std::setw(2);
                for (const auto& value : row) {
                    std::cout << value << std::setw(2);
                }
                std::cout << std::endl;
            }
        }
    };
    auto tableGraph = new TableGraph();
    tableGraph->print();
    std::cout << std::endl;

    class ListGraph {
    private:
        std::vector<std::vector<int>> table;


    public:
        ListGraph() {
            this->table = { {2, 3, 5}, {1, 3}, {1, 2, 4, 5}, {3, 5}, {3, 4} };
        }

        void print() const {
            int i = 0;
            for (const auto& row : table) {
                i++;
                std::cout << std::setw(1) << i << std::setw(2);
                for (const auto& value : row) {
                    std::cout << value << std::setw(1);
                }
                std::cout << std::endl;
            }
        }
    };
    auto listGraph = new ListGraph();
    listGraph->print();
    std::cout << std::endl;

    

    class SfmlGraph {
    private:
        std::vector<std::vector<int>> table;


    public:
        SfmlGraph() {}

        void print() const {
            sf::RenderWindow window(sf::VideoMode(800, 600), "Graph with Arrows");

            // ������� ������ (������ �����)
            const int numVertices = 5;
            sf::Vector2f positions[numVertices] = {
                {200, 300},
                {400, 150},
                {600, 300},
                {400, 450},
                {300, 250}
            };

            // ��������� �����
            sf::Font font;
            if (!font.loadFromFile("tuffy.ttf")) {
               // ��������� ������, ���� ����� �� ����������
               return;
            }

            

            // �������� ���� ����������
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear(sf::Color::White);

                // ������ �����
                for (int i = 0; i < numVertices; ++i) {
                    sf::CircleShape circle(30); // ������ �����
                    circle.setFillColor(sf::Color::Blue);
                    circle.setOutlineThickness(5); // ������� �������
                    circle.setOutlineColor(sf::Color::Black); // ���� �������
                    circle.setPosition(positions[i].x - circle.getRadius(), positions[i].y - circle.getRadius());

                    window.draw(circle);

                    // ����� ��� ������ �����
                    sf::Text text;
                    // text.setFont(sf::Font());
                    text.setFont(font);
                    text.setString(std::to_string(i + 1)); // ����� �����
                    text.setCharacterSize(24); // ������ ������
                    text.setFillColor(sf::Color::White); // ���� ������
                    text.setPosition(
                        positions[i].x - text.getLocalBounds().width / 2,
                        positions[i].y - text.getLocalBounds().height / 2
                    );

                    window.draw(text); // ������ ����� �� �����
                }

                // ������ ������� ����� �������
                for (int i = 0; i < numVertices; ++i) {
                    int nextIndex = (i + 1) % numVertices; // ��������� ����� �� �����
                    drawArrow(window, positions[i], positions[nextIndex]);
                }

                window.display(); // ��������� ����
            }
        }
    };
    auto sfmlGrapgh = new SfmlGraph();
    sfmlGrapgh->print();
    std::cout << std::endl;
}