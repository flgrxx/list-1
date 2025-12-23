#include "pch.h"

#include <string>
#include "list1.h"

// 1. Базовый тест конструктора и isEmpty
TEST(ListTest, DefaultConstructorCreatesEmptyList) {
    List<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
}

// 2. Проверка push_front/pop_front
TEST(ListTest, PushFrontAndPopFrontWork) {
    List<int> list;
    list.push_front(10);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.front(), 10);

    list.push_front(20);
    EXPECT_EQ(list.front(), 20);

    list.pop_front();
    EXPECT_EQ(list.front(), 10);

    list.pop_front();
    EXPECT_TRUE(list.isEmpty());
}

// 3. Проверка push_back/pop_back
TEST(ListTest, PushBackAndPopBackWork) {
    List<int> list;
    list.push_back(10);
    EXPECT_EQ(list.back(), 10);
    EXPECT_EQ(list.front(), 10);

    list.push_back(20);
    EXPECT_EQ(list.back(), 20);
    EXPECT_EQ(list.front(), 10);

    list.pop_back();
    EXPECT_EQ(list.back(), 10);

    list.pop_back();
    EXPECT_TRUE(list.isEmpty());
}

// 4. Проверка вставки по индексу
TEST(ListTest, InsertAtIndexWorks) {
    List<int> list;

    // В начало
    list.insert(0, 10);
    EXPECT_EQ(list.front(), 10);

    // В конец
    list.insert(1, 30);
    EXPECT_EQ(list.back(), 30);

    // В середину
    list.insert(1, 20);

    // Проверяем порядок: 10, 20, 30
    EXPECT_EQ(list.front(), 10);
    list.pop_front();
    EXPECT_EQ(list.front(), 20);
    list.pop_front();
    EXPECT_EQ(list.front(), 30);
}

// 5. Проверка удаления по индексу
TEST(ListTest, EraseAtIndexWorks) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Удаляем середину
    list.erase(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);

    // Удаляем начало
    list.erase(0);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 30);

    // Удаляем конец (единственный элемент)
    list.erase(0);
    EXPECT_TRUE(list.isEmpty());
}

// 6. Проверка find
TEST(ListTest, FindWorksCorrectly) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* node = list.find(20);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->value, 20);

    node = list.find(40);
    EXPECT_EQ(node, nullptr);
}

// 7. Проверка итераторов
TEST(ListTest, IteratorsWork) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int sum = 0;
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
        count++;
    }

    EXPECT_EQ(count, 3);
    EXPECT_EQ(sum, 60);

    // Range-based for тоже должен работать
    sum = 0;
    for (int val : list) {
        sum += val;
    }
    EXPECT_EQ(sum, 60);
}

// 8. Проверка clear
TEST(ListTest, ClearEmptiesList) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_FALSE(list.isEmpty());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
}

// 9. Проверка копирования
TEST(ListTest, CopyConstructorWorks) {
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    List<int> list2(list1); // копирование

    EXPECT_EQ(list2.size(), 3);

    // Проверяем, что это разные объекты
    list2.pop_front();
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list1.size(), 3); // оригинал не изменился

    // Проверяем содержимое копии
    EXPECT_EQ(list2.front(), 20);
    list2.pop_front();
    EXPECT_EQ(list2.front(), 30);
}

// 10. Проверка оператора присваивания
TEST(ListTest, AssignmentOperatorWorks) {
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    List<int> list2;
    list2.push_back(30);
    list2.push_back(40);
    list2.push_back(50);

    list2 = list1; // присваивание

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 10);
    EXPECT_EQ(list2.back(), 20);
}

// 11. Проверка работы со строками
TEST(ListTest, WorksWithStrings) {
    List<std::string> list;
    list.push_back("hello");
    list.push_back("world");

    EXPECT_EQ(list.front(), "hello");
    EXPECT_EQ(list.back(), "world");

    list.pop_front();
    EXPECT_EQ(list.front(), "world");
}

// 12. Проверка исключений
TEST(ListTest, ThrowsExceptionsOnInvalidOperations) {
    List<int> list;

    // Доступ к front/back пустого списка
    EXPECT_THROW(list.front(), std::runtime_error);
    EXPECT_THROW(list.back(), std::runtime_error);

    // Неверная позиция для insert
    EXPECT_THROW(list.insert(5, 10), std::out_of_range);

    // Неверная позиция для erase
    list.push_back(10);
    EXPECT_THROW(list.erase(5), std::out_of_range);
}

// 13. Проверка insert через указатель на узел
TEST(ListTest, InsertViaNodePointerWorks) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);

    Node<int>* node = list.find(10);
    ASSERT_NE(node, nullptr);

    list.insert(node, 20); // вставляем после 10

    // Должно быть: 10, 20, 30
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 10);

    list.pop_front(); // убираем 10
    EXPECT_EQ(list.front(), 20);

    list.pop_front(); // убираем 20
    EXPECT_EQ(list.front(), 30);
}

// 14. Проверка erase через указатель на узел
TEST(ListTest, EraseViaNodePointerWorks) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* node = list.find(20);
    ASSERT_NE(node, nullptr);

    list.erase(node); // удаляем 20

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}