# Задания по параллельному программированию на C++
__________________________________________________________

### OMP

1.Написать программу где каждый поток печатает свой идентификатор, количество потоков всего  и  строчку  «HelloWorld».  Запустить  программу с  8  потоками.  Всегда  ли  вывод идентичен? Почему?

2.Написать программу, в которой определить две параллельные области, выполнение которых зависит от условного оператора #pragma omp parallel if(...), если заданное значение числа нитей  больше  1,  параллельная  область  выполняется,  иначе  не  выполняется.Число  нитей перед  первой  областью  задать  равным  3,  перед  второй –равным  1. Внутри  параллельных областей  определить  количество  нитей  и  номер  каждой  нити,  результат  выдать  на  экран.Убедиться в правильности работы программы.

3.Написать программу, в которой объявить и присвоить начальные значения целочисленным переменным: a и b,  определить  две  параллельные  области, первая – с  числом нитей 2,вторая – с числом нитей 4. Для первой области переменные a и b объявить защищенными, с режимом доступа  privateи firstprivate соответственно,  внутри области определить номер нити  и  выполнить  увеличение  значения  переменных  на  это  величину.  Выдать  на  экран значения  переменных  до  входа  в  параллельную  область,  внутри  параллельной  области  и после  выхода  из  параллельной  области. Для  второй области  переменную a объявить общей, переменную b объявить защищенной, с режимом доступа private, определить номер нити  и  выполнить  уменьшение  значения  переменных  на  это  величину.  Выдать  на  экран значения  переменных  до  входа  в  параллельную  область,  внутри  параллельной  области и после выхода из параллельной области.

4.Написать программу, в которой объявить и присвоить начальные значения целочисленным массивам a[10] и b[10], определить параллельную область, количество нитей задать равным 2,выделить  код  для  основной  (номер  0)  и  нити  с  номером  1.  Основная  нить  должна выполнять поиск min значения элементов массива a, нить с номером 1 -поиск max значения элементов массива b.Результат выдать на экран.

5.Написать  программу,  в  которой  объявить  и  присвоить  начальные  значения  элементам двумерного массива d[6][8], для инициализации значений использовать генератор случайных чисел.Используя  конструкцию  директивы sections...section определить  три  секции  для выполнения следующих операций: 
	* первая  секция выполняет  вычисление  среднего  арифметического  значения элементов двумерного массива, 
	* втораясекция выполняет  вычисление минимального  и  максимального  значений элементов двумерного массива, 
	* третья секция выполняет вычисление количества элементов массива, числовые значения которых кратны 3.
В  каждой  секции определить и  выдать  на  экран  номер исполняющей нити и результат выполнения вычислений.Конструкции разделения работ итерационноготипа.

6.Написать программу, в которой объявить и присвоить начальные значения целочисленныммассивам a[10] и b[10].Используя конструкцию parallel for и reduction вычислить средние арифметические значения элементов  массивов a и b,сравнить  полученные  значения, результат выдать на экран.

7.Написать программу, в которой определить две параллельные области, каждая из которых содержит  итерационную  конструкцию forвыполняющую  инициализацию  элементов одномерных массивов целых чиселa[12], b[12] и c[12].Число нитей перед первой областью задать  равным  3,  перед  второй – равным  4.   Первая параллельная область выполняет инициализацию  элементов  массивов a и b с  использованием  статического  распределения итераций, размер  порции  итераций  выбрать  самостоятельно,вторая  параллельная область выполняет инициализацию элементов массива cпо следующему правилу c[i]  = a[i]  + b[i], с использованием  динамического  распределения  итераций, размер  порции итераций  выбрать самостоятельно.В каждой области определитьи выдать на экран количество нитей, номер нитии результат выполнения цикла.Убедиться в правильности работы программы.

8.Используя  возможности OpenMP, написать  программу  умножения  матрицы  на  вектор. Сравнить время выполнения последовательной и параллельных программ.

9.Написать  программу,  в  которой объявить  и  присвоить  начальные  значения  элементам двумерного массива d[6][8], для инициализации значений использовать генератор случайных чисел.  Используя  конструкцию  директивы omp parallel for и omp critical определить минимальное  и  максимальное  значения  элементов  двумерного  массива.  Количество  нитей задать самостоятельно. Результат выдать на экран.

10.Написать программу,  в которой объявить и присвоить начальные значения массиву целых чиселa[30], для  инициализации  значений  использовать  генератор  случайных  чисел. Используя  конструкцию omp parallel for и omp atomic вычислить  количество  элементов массива,  числовые  значения  которых  кратны 9.Количество  нитей  задать  самостоятельно. Результат выдать на экран.

11.Написать программу, в которой, объявить и заполнить случайными значениями массив целых чисел.  Используя возможности OpenMP найти максимальное числовое значение элементов массива,  кратное  7.  Длину  массива  и  количество  потоков  определить  самостоятельно. Результат выдать на экран. Для синхронизации числовых значений максимума используется механизм критических секций.  

12.Модифицируйте  задачу  1  так,  что бы  потоки  распечатывали  свои  идентификаторы  в обратном порядке. Существует как минимум 5 способов решения. Постарайтесь найти как можно больше.

13.На нулевом процессе задан массив целых чисел, который является двоичным представлением десятичного  числа.  Написать  параллельную  программу  вычисления  десятичного  числа  из заданного двоичного представления.int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1}; Число  x  может  быть  представлено  в  системе  с  основанием  p,  как x=an*pn+an-1*pn-1+ a1*p1+a0*p0, где an ... a0 -цифры в представлении данного числа.

14.Написать  параллельную  программу  возведения  числа  210  в  квадрат    без  операции умножения. Пояснение: Квадрат натурального числа N равен сумме первых N нечетных чисел. Например, 32 = 9  это  1+3+5=9;    52 = 25  это  1+3+5+7+9=25;  

15.Написать программу, в которой, используя возможности OpenMP найти все простые числа в заданном  с  клавиатуры  диапазоне.  Количество  потоков  определить  самостоятельно. Результат выдать на экран. 
__________________________________________________________

### MPI

1.1.Написать mpi программу, печатающую "Hello, World!". Запустить программу на 4 процессах. 

1.2.Написать    программу,  печатающую  номер  процесса  и  общее  количество процессов в коммуникаторе MPI_COMM_WORLD. 

1.3.Написать  программу, запустить  ее  на  2-х  процессах.  На  нулевом  процессе задать массив а из 10 элементов, значения сгенерировать случайным образом. Переслать  этот  массив  целиком  первому  процессу  с  помощью  функции MPI_Send. Распечатать на первом процессе принятый массив. 

1.4.Используя  блокирующую  операцию  передачи  сообщений  (MPI_Send  и MPI_Recv) выполнить пересылку данных одномерного массива, из процесса с номером  1  на  остальные  процессы  группы.  На  процессах  получателях  до выставления  функции  приема  (MPI_Recv)  определить  количество принятых данных  (MPI_Probe).  Выделить  память  под  размер  приемного  буфера,  после чего вызвать функцию MPI_Recv. Полученное сообщение выдать на экран. 

1.5.Написать программу, вычисляющую элементы вектора по формуле .  Векторы задаются  на  нулевом  процессе  и  равными  блоками пересылаются остальным процессам, --заданные числа. Пересылка данных осуществляется функцией MPI_Send. Все процессы по формуле вычисляют свои элементы  массива. Каждый  процесс  отправляет  на  нулевой  процесс подсчитанные элементы.

2.1.Написать программу, вычисляющую элементы вектора по формуле .  Векторы задаются  на  нулевом  процессе  и  равными  блоками пересылаются  остальным  процессам.Пересылка  данных  осуществляется функцией  MPI_Send.  Все  процессы  по  формуле  вычисляют  свои  элементы массива. Каждый  процесс  отправляет  на  нулевой  процесс  подсчитанные элементы.

2.2.Написать  программу,которая  меняет  местами  элементы  векторов . Векторы задаются на нулевом процессе и равными блоками пересылаются остальным процессам.Пересылка данных осуществляется функцией MPI_Send. Каждый процесс отправляет на нулевой процесс подсчитанные элементы.

2.3.В программе реализовать поэлементное  умножение матриц (1 балл)

2.4.В программе реализовать умножение матриц (1 балл)

2.5.В программе реализовать транспонирование матрицы (1 балл)

3.1.Написать  программу  вычисления  нормывектора , Для  распределения  элементов вектора  x  по процессам использовать функцию MPI_Scatter. Для получения итоговой суммы на нулевом процессе использовать функцию MPI_Reduce с операцией MPI_Sum.

3.2.Написать   программу   вычисления   скалярного   произведения   двух векторов. Для распределения элементов вектора x по процессам использовать функцию MPI_Scatter. Для получения итоговой суммы на нулевом процессе использовать функцию MPI_Reduce с операцией MPI_Sum.

3.3.Написать  программу  умножения  матрицы  на  вектор .  Распределить матрицу равномерно вдоль строк, вектор передать всем процессам. После выполнения  операции  умножения  на  каждом из процессов необходимо выполнить  сбор  полученных  локальных частей  результирующего  вектора  на один процесс(с номером 0). Использовать функцию MPI_Bcast для  рассылки вектора для  распределения  элементов  матрицы  использовать  функцию MPI_Scatter,  для  сбора  локальных  частей  результирующего  вектора  в глобальный вектор использовать функцию MPI_Gather.

3.4.Написать  программу  вычисления  нормы  матрицы по  формуле где матрица.Для  распределения элементов  матрицы  А  по  процессам  использовать  функцию  MPI_Scatter.  Для получения итогового значения использовать функцию MPI_Reduce с операцией MPI_MAX.

3.5.Написать программу вычисления поэлементного умножения матриц (). Использовать  функции  MPI_Scatter  для  распределения элементов  матриц  A  и  B,  и  MPI_Gather  для  сбора  вычисленных  данных  в матрицу C.

4.1.Пусть  матрицы  вещественных  чисел  A,  B  заданы  на  нулевом  процессе. Написать программу, в которой матрицы равными кусками с нулевого процесса пересылаются  остальным  процессам.  Пересылка  данных  осуществляется функцией  MPI_Send.  Все  процессы  по  формуле  вычисляют  свои  элементы искомых   матриц.   Каждый   процесс   отправляет   на   нулевой   процесс подсчитанные элементы матриц.Реализовать приведение матрицы к нижнему треугольному виду методом исключения Гаусса(1балл). 

4.2.Написать программу и запустить ее на p(= 2, 3, 4, 6, 8) процессах. На нулевом процессе  объявить  и  задать  массив  из  12  элементов.  С  помощью  функции MPI_Send  разослать  блоки  массива  на  остальные  процессы.  Размер  блока массива  (12/p)+1.  В  результате  на  нулевом  процессе  должны  быть  элементы массива с 0 до 12/p, на первом процессе с 12/p+1 до 2×(12/p), на 3м процессе с 2×(12/p)+1  до  3×(12/p)  и т.д.  Вывести  элементы  массива  на  экран  на  каждом процессе.  Обратите  внимание,  что  не  на  все  процессы  хватит  элементов. (1 балл)

4.3.Разработать  программу,  в  которой  два  процесса  многократно  обмениваются сообщениями длиной n байт. Выполнить эксперименты и оценить зависимость времени выполнения операции от длины сообщения. Рассмотреть два варианта обмена сообщениями: PingPong   -двунаправленная передача:Выполняется передача  данных  от  одного  процесса  другому  с  последующим  возвратом переданных данных в исходный процесс. Время выполнение замеряется после получения   обратного   ответа   на   исходном   процессе.PingPing - однонаправленная  передача: Два  процесса  одновременно  выполняют передачу  данных  друг  другу.  Время  выполнение  замеряется  после  получения сообщения каждым процессом.(1балла)

5.1.На  процессе  с  номером  0  объявить  и  заполнить  значениями  матрицу  a[8][8]. Создать новый тип данных для рассылки нечетных строк матрицы а в матрицу b[4][8],  и  для  рассылки  четных  строк  матрицы  в  матрицу  c[4][8],  используя функцию MPI_Type_vector.

5.2.Создать тип данных с помощью функции MPI_Type_create_structи выполнить рассылку строк матрицы a[8][8] на 4 процесса в матрицу d[2][8] по следующей схеме:○на нулевой процесс строки 0 и 4,○на первый процесс строки 1 и 5,○на второй процесс строки 2 и 6,○на третий процесс строки 3 и 7.

5.3.Создать  новую  группу  из  процессов  с  номерами  8,  3,  9,  1,  6.  Используя конструктор MPI_Comm_create(...), создать коммуникатор группы. На нулевом процессе  созданной  группы  объявить  и  заполнить  числовыми  значениями одномерный  массив  вещественных  чисел  и  вывестиего  на  экран.  Используя функцию  MPI_Bcast  передать  массив  всем  процессам  созданной  группы. Полученные  массивы  вывести  на  экран.  Передать  полученный  массив  из последнего  процесса  новой  группы  на  нулевой  процесс  исходной  группы. Выполнить программу на 10 процессах.

__________________________________________________________

### Merge Sort последовательное выполнение, OMP (через sections) и MPI

![1](https://github.com/Elina-19/parallel-programming/tree/master/Merge%20Sort/mpi%20графики/1.png)

![2](https://github.com/Elina-19/parallel-programming/tree/master/Merge%20Sort/mpi%20графики/2.png)

![3](https://github.com/Elina-19/parallel-programming/tree/master/Merge%20Sort/mpi%20графики/3.png)

![4](https://github.com/Elina-19/parallel-programming/tree/master/Merge%20Sort/mpi%20графики/4.png)
