# Leet-tasks

## Описание репозитория

Данный репозиторий будет использоваться как для хранения решений задач из LeetCode, так и для прочих упражнений по разработке на C++ (например, практика работы с потоками).

Ветку `main` можно также использовать в качестве CMake-шаблона проекта на C++.

Упражнения будут разделены по отдельным веткам. Ветки будут иметь следующий формат: `<цель задачи>_<номер задачи>`.

Также, каждая ветка будет иметь описание задачи, описанном в данном файле в пункте, расположенном ниже.

## Описание задачи

[LeetCode 189. Rotate Array](https://leetcode.com/problems/rotate-array)

Здесь 3 решения:

1. Без памяти обычным сдвигом элементов (O(n log(n))/O(1) ... O(n2)/O(1))
2. С памятью (O(n)/O(n))
3. Без памяти за счёт инверсии элементов (O(n)/O(1))
