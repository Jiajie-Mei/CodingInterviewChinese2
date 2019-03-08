/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// ����ָOffer�����������Թپ������ͱ���⡷����
// ���ߣ��κ���
//==================================================================

// ������3�����������޸������ҳ��ظ�������
// ��Ŀ����һ������Ϊn+1����������������ֶ���1��n�ķ�Χ�ڣ�������������
// ����һ���������ظ��ġ����ҳ�����������һ���ظ������֣��������޸������
// ���顣���磬������볤��Ϊ8������{2, 3, 5, 4, 3, 2, 6, 7}����ô��Ӧ��
// ������ظ�������2����3��

#include <iostream>

int countRange(const int *numbers, int length, int start, int end);

// ����:
//        numbers:     һ����������
//        length:      ����ĳ���
// ����ֵ:
//        ����  - ������Ч�����������д����ظ������֣�����ֵΪ�ظ�������
//        ����  - ������Ч������������û���ظ�������

bool check_input(const int *numbers, int length)
{
    if (numbers == nullptr || length < 2)
        return false;
    for (int i = 0; i < length; i++)
        if (numbers[i] < 1 || numbers[i] > length - 1)
            return false;
    return true;
}

int copy_based(const int *numbers, int length)
{
    if (!check_input(numbers, length))
        return -1;

    int *new_numbers = new int[length];
    for (int i = 0; i < length; i++)
        new_numbers[i] = -1;
    for (int i = 0; i < length; i++)
    {
        if (new_numbers[numbers[i]] != -1)
            return numbers[i];
        new_numbers[numbers[i]] = numbers[i];
    }
    return -1;
}

int count(const int *numbers, int start, int end, int length)
{
    int total = 0;
    for (int i = 0; i < length; i++)
        if (numbers[i] >= start && numbers[i] <= end)
            total++;
    return total;
}

int binary_search(const int *numbers, int length)
{
    if (!check_input(numbers, length))
        return -1;

    int start = 1, end = length - 1;

    while (start <= end)
    {
        int middle = (end - start) / 2 + start;
        int counter = count(numbers, start, middle, length);

        if (counter > middle - start + 1) {
            if(middle == start)
                return start;  // this is assured to be executed.
            end = middle;
        } else
            start = middle + 1;
    }
}

int (*getDuplication)(const int *, int) = binary_search;

int true_getDuplication(const int *numbers, int length)
{
    if (numbers == nullptr || length <= 0)
        return -1;

    int start = 1;
    int end = length - 1;
    while (end >= start)
    {
        int middle = ((end - start) >> 1) + start;
        int count = countRange(numbers, length, start, middle);
        if (end == start)
        {
            if (count > 1)
                return start;
            else
                break;
        }

        if (count > (middle - start + 1))
            end = middle;
        else
            start = middle + 1;
    }
    return -1;
}

int countRange(const int *numbers, int length, int start, int end)
{
    if (numbers == nullptr)
        return 0;

    int count = 0;
    for (int i = 0; i < length; i++)
        if (numbers[i] >= start && numbers[i] <= end)
            ++count;
    return count;
}

// ====================���Դ���====================
void test(const char *testName, int *numbers, int length, int *duplications, int dupLength)
{
    int result = getDuplication(numbers, length);
    for (int i = 0; i < dupLength; ++i)
    {
        if (result == duplications[i])
        {
            std::cout << testName << " passed." << std::endl;
            return;
        }
    }
    std::cout << testName << " FAILED." << std::endl;
}

// ����ظ�������
void test1()
{
    int numbers[] = {2, 3, 5, 4, 3, 2, 6, 7};
    int duplications[] = {2, 3};
    test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// һ���ظ�������
void test2()
{
    int numbers[] = {3, 2, 1, 4, 4, 5, 6, 7};
    int duplications[] = {4};
    test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// �ظ�����������������С������
void test3()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 1, 8};
    int duplications[] = {1};
    test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// �ظ�����������������������
void test4()
{
    int numbers[] = {1, 7, 3, 4, 5, 6, 8, 2, 8};
    int duplications[] = {8};
    test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// ������ֻ����������
void test5()
{
    int numbers[] = {1, 1};
    int duplications[] = {1};
    test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// �ظ�������λ�����鵱��
void test6()
{
    int numbers[] = {3, 2, 1, 3, 4, 5, 6, 7};
    int duplications[] = {3};
    test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// ����ظ�������
void test7()
{
    int numbers[] = {1, 2, 2, 6, 4, 5, 6};
    int duplications[] = {2, 6};
    test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// һ�������ظ�����
void test8()
{
    int numbers[] = {1, 2, 2, 6, 4, 5, 2};
    int duplications[] = {2};
    test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// û���ظ�������
void test9()
{
    int numbers[] = {1, 2, 6, 4, 5, 3};
    int duplications[] = {-1};
    test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// ��Ч������
void test10()
{
    int *numbers = nullptr;
    int duplications[] = {-1};
    test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
}