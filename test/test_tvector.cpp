#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

//TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, copied_vector_is_equal_to_source_one) {
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TDynamicVector<int> v2(v1);

    EXPECT_TRUE(v1 == v2);
}


//TEST(TDynamicVector, copied_vector_has_its_own_memory)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, copied_vector_has_its_own_memory) {
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TDynamicVector<int> v2(v1);
    v2[0] = 100;

    EXPECT_NE(v1[0], v2[0]); // Значения должны отличаться
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    std::cout << "Test for v.size(): " << v.size() << std::endl; // Добавлен вывод
    EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

//TEST(TDynamicVector, throws_when_set_element_with_negative_index)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, throws_when_set_element_with_negative_index) {
    TDynamicVector<int> v(3);
    ASSERT_ANY_THROW(v.at(-1));
}


//TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, throws_when_set_element_with_too_large_index) {
    TDynamicVector<int> v(3);
    ASSERT_ANY_THROW(v.at(3)); // Индексы: 0, 1, 2 -> индекс 3 некорректен
}

//TEST(TDynamicVector, can_assign_vector_to_itself)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, can_assign_vector_to_itself) {
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    ASSERT_NO_THROW(v = v);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

//TEST(TDynamicVector, can_assign_vectors_of_equal_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, can_assign_vectors_of_equal_size) {
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    ASSERT_NO_THROW(v2 = v1);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

//TEST(TDynamicVector, assign_operator_change_vector_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, assign_operator_change_vector_size) {
    TDynamicVector<int> v1(3), v2(5);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    v2 = v1;

    EXPECT_EQ(v2.size(), 3); // Размер должен измениться
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

//TEST(TDynamicVector, can_assign_vectors_of_different_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, can_assign_vectors_of_different_size) {
    TDynamicVector<int> v1(3), v2(5);
    v1[0] = 10; v1[1] = 20; v1[2] = 30;

    ASSERT_NO_THROW(v2 = v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v2[1], 20);
    EXPECT_EQ(v2[2], 30);
}

//TEST(TDynamicVector, compare_equal_vectors_return_true)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, compare_equal_vectors_return_true) {
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 5; v1[1] = 10; v1[2] = 15;
    v2[0] = 5; v2[1] = 10; v2[2] = 15;

    EXPECT_TRUE(v1 == v2);
}

//TEST(TDynamicVector, compare_vector_with_itself_return_true)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, compare_vector_with_itself_return_true) {
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    EXPECT_TRUE(v == v);
}

//TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, vectors_with_different_size_are_not_equal) {
    TDynamicVector<int> v1(3), v2(4);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 1; v2[1] = 2; v2[2] = 3; v2[3] = 4;

    EXPECT_FALSE(v1 == v2);
}


TEST(TDynamicVector, can_add_scalar_to_vector) {
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> result = v + 2;

    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 5);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) {
    TDynamicVector<int> v(3);
    v[0] = 5; v[1] = 7; v[2] = 9;

    TDynamicVector<int> result = v - 2;

    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 7);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector) {
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> result = v * 3;

    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 9);
}


//TEST(TDynamicVector, can_add_scalar_to_vector)
//{
//  ADD_FAILURE();
//}

//TEST(TDynamicVector, can_subtract_scalar_from_vector)
//{
//  ADD_FAILURE();
//}
//
//TEST(TDynamicVector, can_multiply_scalar_by_vector)
//{
//  ADD_FAILURE();
//}

//TEST(TDynamicVector, can_add_vectors_with_equal_size)
//{
//  ADD_FAILURE();
//}
//
//TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
//{
//  ADD_FAILURE();
//}
//
//TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
//{
//  ADD_FAILURE();
//}
//
//TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
//{
//  ADD_FAILURE();
//}
//
//TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
//{
//  ADD_FAILURE();
//}

//TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(3), v2(4);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6; v2[3] = 7;

    ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, manual_test_for_operator_equal) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);

    for (size_t i = 0; i < 4; i++) {
        v1[i] = i;
        v2[i] = i;
    }

    EXPECT_TRUE(v1 == v2) << "Equal vectors comparison failed";

    TDynamicVector<int> v3(5);
    EXPECT_FALSE(v1 == v3) << "Vectors with different sizes are not equal";
}
TEST(TDynamicVector, manual_test_for_scalar_operations) {
    TDynamicVector<int> v(3);
    for (size_t i = 0; i < 3; i++) v[i] = i; // Заполняем вектор значениями 0, 1, 2

    std::cout << "Original vector: ";
    for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
    std::cout << std::endl;

    // Тестируем оператор +
    TDynamicVector<int> v_add = v + 2;
    std::cout << "After +2: ";
    for (size_t i = 0; i < v_add.size(); i++) std::cout << v_add[i] << " ";
    std::cout << std::endl;

    // Тестируем оператор -
    TDynamicVector<int> v_sub = v - 1;
    std::cout << "After -1: ";
    for (size_t i = 0; i < v_sub.size(); i++) std::cout << v_sub[i] << " ";
    std::cout << std::endl;

    // Тестируем оператор *
    TDynamicVector<int> v_mul = v * 3;
    std::cout << "After *3: ";
    for (size_t i = 0; i < v_mul.size(); i++) std::cout << v_mul[i] << " ";
    std::cout << std::endl;
}
//test
TEST(TDynamicVector, can_add_vectors_with_equal_size) {
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    TDynamicVector<int> res = v1 + v2;

    EXPECT_EQ(res[0], 5);
    EXPECT_EQ(res[1], 7);
    EXPECT_EQ(res[2], 9);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(3), v2(4);
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) {
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 5; v1[1] = 7; v1[2] = 9;
    v2[0] = 1; v2[1] = 2; v2[2] = 3;

    TDynamicVector<int> res = v1 - v2;

    EXPECT_EQ(res[0], 4);
    EXPECT_EQ(res[1], 5);
    EXPECT_EQ(res[2], 6);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) {
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    int result = v1 * v2;
    EXPECT_EQ(result, 32); // 1*4 + 2*5 + 3*6 = 32
}
