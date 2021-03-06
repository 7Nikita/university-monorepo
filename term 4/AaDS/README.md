1. [Добавление](#добавление)
2. [Простая задача](#простая-задача)
3. [Максимальнео K-ое произведение](#максимальнео-k-ое-произведение)
4. [Путешествие с конем](#путешествие-с-конем)
5. [Кратчайший путь](#кратчайший-путь)
6. [RMQ наоборот](#rmq-наоборот)
7. [Шахматная игра](#шахматная-игра)
8. [Максимальный неподпалиндром](#максимальный-неподпалиндром)
9. [Инвертирование](#инвертирование)
10. [Количество различных строк](#количество-различных-строк)
11. [Сумма на дереве](#сумма-на-дереве)
12. [Большой куш](#большой-куш)
13. [Удаление](#удаление)
14. [Количество способов](#количество-способов)
15. [Выравнивание](#выравнивание)
16. [Следующее](#следующее)
17. [1087388483](#1087388483)
18. [Високосный](#високосный)
19. [Инверсии](#инверсии)
20. [Рельефная местность](#рельефная-местность)
21. [Паросочетание на дереве](#паросочетание-на-дереве)
22. [Не содержащие строки](#не-содержащие-строки)

# Добавление
Дан неориентированный граф. 
Определить минимальное количество ребер, после добавлениякоторых граф станет связным. 
Вывести -1 если ответа не существует.

# Простая задача
Дана последовательность целых чисел.
Найти максимальное число, которое может быть получено путем перемножения двух любых чисел последовательности.

# Максимальнео K-ое произведение
Дана последовательность N целых чисел (1 ⩽ N ⩽ 105, |Ai| ⩽ 2 · 109) и число K (1 ⩽ K ⩽ N).
Найти K чисел последовательности, произведение которых максимально.

# Путешествие с конем
Размеры прямоугольной размеченной квадратами доски n × m. 
В нижнем левом квадрате дос-ки (1, 1) находится шахматный конь. 
Конь может ходить только согласно шахматным правилам – движение может быть двумя квадратами горизонтально
и затем одним вертикально, или двумя квадратами вертикально и одним горизонтально. 
Например, если n = 4 и m = 3, и конь находится в квадрате (2, 1), то следующим может быть ход (1, 3) или (3, 3) или (4, 2).
Для заданных положительных целых значений n, m, i и j требуется определить минимальное необходимое количество ходов
коня для перемещения из начальной позиции (1, 1) в квадрат (i, j).

# Кратчайший путь
Задан связный неориентированный взвешенный граф G. 
В графе возможно наличие нескольких ребер между одной и той же парой вершин. 
Найдите вес кратчайшего пути между двумя заданными вершинами A и B.

# RMQ наоборот
Дано M троек чисел Li, Ri, Vi. 
Необходимо найти такую последовательность Ai, состоящую из N целых чисел, 
у которой минимум на отрезке \[Lj , Rj\], будет равен Vj (для всех 1 ⩽ j ⩽ M).

# Шахматная игра
Дано поле N × M. 
На нем расположены две ладьи, координаты каждой (X1, Y1) и (X2, Y2) соответственно.
Ладья ходит по классическим правилам шахмат: за один ход может переместиться
в любую клетку, расположенную на одной вертикали либо горизонтали. 
Одна ладья может сбить другую, если та находится с ней на одной горизонтали либо вертикали.
Основное отличие от классических правил: ладья не может переместиться в клетку, если во
время передвижения к ней она станет на клетку, которая находится под боем другой ладьи.
У первого игрока в распоряжении первая ладья, а у второго — вторая. 
Игроки ходят по очереди, ход пропускать нельзя. 
Первым ходит первый игрок. Проигрывает тот, кому некуда ходить (куда бы нипошел — собьют). 
Определите кто победит при оптимальной игре обоих.

# Максимальный неподпалиндром
В заданной строке S найти максимальную по длине подстроку, которая не является палиндромом.

# Инвертирование
Дана строка S и Q запросов. 
Запрос представляет собой пару чисел L и R — промежуток строки S, на котором нужно инвертировать регистр символов. 
Требутеся найти строку S после выполнения всех запросов.

# Количество различных строк
Для заданной строки S требуется найти количество различных подстрок в ней.

# Сумма на дереве
Дано дерево. Определить сумму весов всех кратчайших расстояний между каждой парой вершин.

# Большой куш
Известный фокусник Донни разбогател на очень простой игре. 
Он играл в нее на деньги с самыми богатыми и знаменитыми личностями, но никто ни разу не смог его обхитрить. 
И тут очередь дошла до вас. 
Вы белорусский бизнесмен и хотите удвоить свое состояние. 
Обыграйте Донни и сорвите куш!
Так же вы можете отказаться от игры, если, при виде начальной позиции, на вас нападет плохое предчувствие.
Правила игры следующие: Изначально дано число X. 
За один ход разрешается отнять от числа X любую цифру, кроме 0, которая входит в число X. 
Проигрывает тот, кто не может ходить, то есть когда будет получено число 0.

# Удаление
Дан неориентированный граф. 
Определить минимальное количество ребер, 
после удаления которых между каждой парой вершин будет существовать только один маршрут (без повторений в нем ребер). 
Вывести -1, если ответа не существует.

# Количество способов
Дан неориентированный граф. 
Определить количество маршрутов (по ребрам можно перемещаться несколько раз) длиной L между вершинами U и V .

# Выравнивание
Дана последовательность Ai, состоящая из N целых чисел. 
За одно действие можно зафиксировать произвольный промежуток одинаковых элементов последовательности и увеличить все
элементы этого промежутка на 1. 
Необходимо за минимальное количество действий уравнять все элементы.

# Следующее
Дано число X. 
Надо найти наименьшее число большее, чем X, которое может быть получено из X перестановкой цифр.

# 1087388483
Дана последовательность из N целых положительных чисел. 
Требуется определить можно ли путем перемножения некоторых чисел последовательности получить число 1087388483.

# Високосный
Високосный год — год в юлианском и григорианском календарях, продолжительность которого равна 366 дням — 
на одни сутки больше продолжительности обычного, невисокосного года. 
В юлианском календаре високосным годом является каждый четвёртый год, 
в григорианском календаре из этого правила есть исключения. 
Год в григорианском календаре является високосным, если он кратен 4 и при этом не кратен 100, либо кратен 400. 
Определите, является ли заданный год високосным в григорианском календаре.

# Инверсии
Перестановкой чисел 1, 2, 3 ... N назовем такую последовательность длины N, что 1 ⩽ Ai ⩽ N,
и все числа последовательности различны.
Инверсией в пeрестановке A размера N называется всякая пара индексов (i, j) такая, что i < j и Ai > Aj.

# Рельефная местность
Дана рельефная местность. 
Местность разделена на N ×M квадратов и описывается двумерной матрицей A, где Aij высота в квадрате (i, j).
Определить максимальный объем воды, который может остаться после дождя. 
Вода распространяется на небОльшую по высоте местность в четырех направлениях (по вертикали и горизонтали). 
Считается, что за край местности может утечь сколь угодно много воды.

# Паросочетание на дереве
Дерево — это связный ациклический граф. 
Паросочетанием в графе называется множество ребер, попарно не имеющих общих вершин. 
Требуется найти максимальное по размеру паросочетание в дереве.

# Не содержащие строки
Определить количеcтво строк длины M из строчных букв латинского алфавита, в которых не
содержится ни одна из заданной строки Wi.
