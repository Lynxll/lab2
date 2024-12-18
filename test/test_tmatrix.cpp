#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

//TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(m1); // Копируем матрицу

    EXPECT_TRUE(m1 == m2);
}

//TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(m1);
    m2[0][0] = 100; // Меняем копию

    EXPECT_NE(m1[0][0], m2[0][0]); // Оригинал не должен измениться
}

//TEST(TDynamicMatrix, can_get_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, can_get_size) {
    TDynamicMatrix<int> m(3);

    EXPECT_EQ(3, m.size());
}


//TEST(TDynamicMatrix, can_set_and_get_element)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, can_set_and_get_element) {
    TDynamicMatrix<int> m(2);
    m[0][1] = 42;

    EXPECT_EQ(42, m[0][1]);
}


//TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) {
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m.at(-1).at(0));
    ASSERT_ANY_THROW(m[0].at(-1));
}


TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) {
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m.at(3).at(0)); // Индекс строки за границей
    ASSERT_ANY_THROW(m[0].at(3));    // Индекс столбца за границей
}


TEST(TDynamicMatrix, can_assign_matrix_to_itself) {
    TDynamicMatrix<int> m(3);
    m[0][0] = 1; m[1][1] = 2; m[2][2] = 3;

    ASSERT_NO_THROW(m = m); // Самоприсваивание не должно приводить к ошибкам

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 2);
    EXPECT_EQ(m[2][2], 3);
}


TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) {
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    ASSERT_NO_THROW(m2 = m1); // Присваиваем матрицу
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);
}


TEST(TDynamicMatrix, assign_operator_change_matrix_size) {
    TDynamicMatrix<int> m1(2), m2(3);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2 = m1;

    EXPECT_EQ(m2.size(), 2); // Размер должен измениться
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);
}


//TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, can_assign_matrices_of_different_size) {
    TDynamicMatrix<int> m1(2), m2(3);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    ASSERT_NO_THROW(m2 = m1); // Присваивание матрицы

    EXPECT_EQ(m2.size(), 2); // Размер должен измениться
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);
}

//TEST(TDynamicMatrix, compare_equal_matrices_return_true)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, compare_equal_matrices_return_true) {
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    EXPECT_TRUE(m1 == m2);
}


//TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 5; m[0][1] = 10;
    m[1][0] = 15; m[1][1] = 20;

    EXPECT_TRUE(m == m);
}

//TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {
    TDynamicMatrix<int> m1(2), m2(2), result(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 10; m2[0][1] = 20;
    m2[1][0] = 30; m2[1][1] = 40;

    result = m1 + m2;

    EXPECT_EQ(result[0][0], 11);
    EXPECT_EQ(result[0][1], 22);
    EXPECT_EQ(result[1][0], 33);
    EXPECT_EQ(result[1][1], 44);
}


//TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW(m1 + m2);
}


//TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) {
    TDynamicMatrix<int> m1(2), m2(2), result(2);
    m1[0][0] = 10; m1[0][1] = 20;
    m1[1][0] = 30; m1[1][1] = 40;

    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    result = m1 - m2;

    EXPECT_EQ(result[0][0], 9);
    EXPECT_EQ(result[0][1], 18);
    EXPECT_EQ(result[1][0], 27);
    EXPECT_EQ(result[1][1], 36);
}


//TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
//{
//  ADD_FAILURE();
//}
TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW(m1 - m2);
}


