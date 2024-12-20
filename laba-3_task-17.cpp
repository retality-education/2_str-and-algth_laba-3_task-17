﻿// 17. Дано Trie-дерево. Посчитать количество слов, содержащих заданную подстроку.
#include "Trie_Tree.h"
#include <Windows.h>
#include <string>


/*Решение
* В find_substr мы ищем в дереве строки, в которых есть подстрока substring
* Саму текущую строку мы не держим, т.к. нам не нужно итоговое слово, а только кол-во
* Мы держим кол-во символов совпадающих с подстрокой, если оно равно длине подстроки, то
* запускаем рекурсию, которая просто считает все слова, т.к. все слова уже имеют эту подстроку,
* засунули это в if т.к. мы уже пройдем все слова от слова с подстрокой, следовательно не надо смотреть туда больше
* if в цикле проверяет будет ли новый символ соответствовать текущему продолжению подстроки
* если не удовлетворяет, то сбрасываем до нуля, но если новый символ был началом подстроки, то сбрасываем до 1 и след. рекурсия проверит уже на 2й символ
*/

int cnt_of_words(ttree::ptrNODE t, std::string word) {
    int res = 0;
    if (t->eow) {

        res = 1;
    }

    for (int i = 0; i < 26; i++)
        if (t->ptrs[i])
            res += cnt_of_words(t->ptrs[i], word + char(i + 'a'));
    return res;
}

int find_substr(ttree::ptrNODE current, int len_of_cur_word, const std::string& substring, ttree::ptrNODE start, std::string word) {
    int res = 0;

    if (len_of_cur_word == substring.length())
        res = cnt_of_words(current, "");
    else {
        for (int i = 0; i < 26; i++) {
            if (current->ptrs[i]) {
                
                if (char(i + 'a') == substring[len_of_cur_word]) {
                    if (len_of_cur_word == 0) {
                        start = current->ptrs[i];
                    }
                    res += find_substr(current->ptrs[i], ++len_of_cur_word, substring, start, word + char(i + 'a'));
                }
                else {
                    if (len_of_cur_word != 0) {
                        std::cout << word << "zxc";
                        res += find_substr(start, 0, substring, nullptr, "");
                    }
                    else {
                        
                        res += find_substr(current->ptrs[i], 0, substring, nullptr, "");
                    }
                }
            }
        }
    }
    return res;
}



int main() {
    SetConsoleOutputCP(1251);

    ttree::TTREE trie("test1.txt");
    trie.print(true);

    std::string word{};
    std::cout << "Задайте необходимое вам слово: ";
    std::cin >> word;
    
    std::cout << "Кол-во слов содержащих подстроку:" << word << " =";
    std::cout << find_substr(trie.get_root(), 0, word, nullptr, "");

    return 0;
}

// функция которая, как только нашла совпадение подстроки запускается для уменьшения потребления ресурсов.



// собираем слово если дошли до eow то возвращаем 0
// собираем подстроку