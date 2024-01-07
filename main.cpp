#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cstring>
#include <string>

int32_t readInt(sf::FileInputStream &stream) {
    int32_t symb = 0;
    while ( !('0' <= symb && symb <= '9') ) {
        if (stream.read(&symb, 1) == -1) {
            return 0;
        }
    }
    int32_t ans = symb - '0';
    while (stream.read(&symb, 1) != -1 && '0' <= symb && symb <= '9') {
        ans *= 10;
        ans += symb - '0';
    }
    return ans;
}

int32_t readLetter(sf::FileInputStream &stream) {
    int32_t symb = 0;
    while (symb == '\n' || symb == '\r' || symb == '\0') {
        if (stream.read(&symb, 1) == -1) {
            return 0;
        }
    }
    return symb;
}

class ADTool {
private:
    size_t cnt_cadrs, h_cadr, w_cadr;
    std::vector< std::vector<char> > table;
public:
    ADTool(sf::FileInputStream &stream) {
        cnt_cadrs = readInt(stream);
        h_cadr = readInt(stream);
        w_cadr = readInt(stream);
        table.assign(h_cadr, std::vector<char>(w_cadr));
        for (std::vector<char> &row : table) {
            for (char &symb : row) {
                symb = readLetter(stream);
            }
        }
    }
    void start() {
        sf::Font font;
        font.loadFromFile("src\\times.ttf");
        sf::Text text;
        text.setFont(font);
        std::string s;
        for (std::vector<char> &row : table) {
            for (char &symb : row) {
                s += symb;
            }
            s += '\n';
        }
        text.setString(s);
        text.setCharacterSize(50);
        text.setPosition(10, 10);
        text.setFillColor(sf::Color::Black);
        sf::RenderWindow window(sf::VideoMode(800, 800), "ADTool");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
    }
};

int main() {
    std::cout << "Input path:" << std::endl;
    std::string path = "src\\input.txt";
    // std::cin >> path;
    sf::FileInputStream stream;
    if (!stream.open(path)) {
        std::cerr << "bad";
        return -1;
    }

    ADTool adt(stream);
    adt.start();
}