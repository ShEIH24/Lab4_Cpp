#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // Для UTF-8 вывода в консоли

using namespace std;

// Интерфейс для форматирования
class IFormattable {
public:
    virtual ~IFormattable() = default;
    virtual std::string format() const = 0;
};

// Масти карт
enum Suit {
    Spades,   // Пики
    Hearts,   // Черви
    Diamonds, // Бубны
    Clubs     // Крести
};

// Класс карты (из предыдущего задания)
class Card {
private:
    std::string rank;
    Suit suit;
public:
    Card(const std::string& rank, Suit suit) : rank(rank), suit(suit) {}

    std::string getRank() const { return rank; }
    Suit getSuit() const { return suit; }

    // Метод для получения символа масти
    std::string getSuitSymbol() const {
        switch (suit) {
        case Spades: return "\u2660";   // Пики
        case Hearts: return "\u2665";   // Черви
        case Diamonds: return "\u2666"; // Бубны
        case Clubs: return "\u2663";    // Крести
        default: return "?";
        }
    }
};

// Адаптер класса (Class Adapter)

class ClassAdapter : public Card, public IFormattable {
public:
    ClassAdapter(const std::string& rank, Suit suit) : Card(rank, suit) {}

    // Реализация интерфейса IFormattable
    std::string format() const override {
        return "Карта: " + getRank() + getSuitSymbol();
    }
};

// Адаптер объекта (Object Adapter)

class ObjectAdapter : public IFormattable {
private:
    const Card& card; // Ссылка на адаптируемый объект
public:
    ObjectAdapter(const Card& c) : card(c) {}

    // Реализация интерфейса IFormattable
    std::string format() const override {
        return "Карта: " + card.getRank() + card.getSuitSymbol();
    }
};

// Функция для вывода в отформатированном виде

void prettyPrint(const IFormattable& object) {
    cout << object.format() << endl;
}

// Тестирование адаптеров

int main() {
    setlocale(LC_ALL, "");
    // Устанавливаем UTF-8 кодировку для корректного вывода
    SetConsoleOutputCP(CP_UTF8);

    // Пример карт
    Card card1("2", Spades);
    Card card2("Q", Diamonds);

    // Класс-адаптер
    ClassAdapter classAdapter("A", Hearts);

    // Объект-адаптер
    ObjectAdapter objectAdapter(card1);

    // Вывод с помощью функции prettyPrint
    cout << "Используем адаптер класса:\n";
    prettyPrint(classAdapter); // Карта: A♥

    cout << "\nИспользуем адаптер объекта:\n";
    prettyPrint(objectAdapter); // Карта: 2♠

    // Можно создать адаптер объекта для другой карты
    ObjectAdapter objectAdapter2(card2);
    prettyPrint(objectAdapter2); // Карта: Q♦

    return 0;
}