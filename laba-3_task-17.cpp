// 17. Дано Trie-дерево. Посчитать количество слов, содержащих заданную подстроку.
#include "Trie_Tree.h"
#include <Windows.h>
#include <string>
// Функция для проверки чередования гласных и согласных

const std::string gl = "eyuioa";

class my_str {
public:
    std::string str;
    int size;
};
my_str operator+(my_str lhs, const char c) {
    lhs.str += c;
    ++lhs.size;
    return lhs;
}
int cnt_alternating_words(ttree::ptrNODE t, my_str word, const my_str& substring) {
    std::cout << word.str << " ";
    if (word.size >= substring.size) {
        bool fg = true;
        int i = 0;
        while (i < substring.size && fg) {
            if (word.str[word.size - substring.size + i] != substring.str[i])
                fg = false;
            ++i;
        }
        if (t->eow || fg)
            return fg;
    }
    else
        if (t->eow) {
            return 0;
        }

    int res = 0;
    for (int i = 0; i < 26; i++)
        if (t->ptrs[i])
            res += cnt_alternating_words(t->ptrs[i], word + char(i + 'a'), substring);
    return res;
}


std::istream& operator >> (std::istream& in, my_str& my_string)
{
    std::string s;
    in >> s;
    my_string.str = s;
    my_string.size = s.length();
    return in;
}
// Пример использования
int main() {
    SetConsoleOutputCP(1251);

    ttree::TTREE trie("data.txt");
    trie.print(true);
    my_str word{}, start{};
    std::cout << "Задайте необходимое вам слово: ";
    std::cin >> word;
    std::cout << "Кол-во слов содержащих подстроку:" << word.str << "\n";
    std::cout << cnt_alternating_words(trie.get_root(), start , word);

    return 0;
}