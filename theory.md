# Теоретическая часть 

## Условие задачи

На некоторой местности расположено несколько объектов, между которыми необходимо проложить дороги. Необходимо построить алгоритм, который принимает на вход расположение этих объектов и вычисляет такую карту дорог, в которой общая протяженность дорожного полотна минимальна.

## Подходы к решению задачи

Каждый объект будет однозначно задаваться двумя координатами в декартовой декартовой системе координат. Тогда можно вычислить расстояние от каждого объекта до всех других очевидным способом.

Также не сказано, что нельзя ставить дополнительные точки, помогающие уменьшить суммарную протяжённость дорого
### Формальная постановка задачи

Таким образом, задача сводится к задаче Штейнера на евклидовой плоскости.
* Евклидова задача Штейнера (ЕЗШ): произвольное множество точек (вершин) евклидовой плоскости требуется соединить непрерывными линиями (рёбрами) так, чтобы любые две точки были связаны либо непосредственно соединяющей их линией, либо через другие точки и соединяющие их линии, чтобы сумма длин линий была минимальной.

Доказано, что данная задача является ***NP-трудной***. Доказательство можно провести сведением задачи "Exact cover by 3-Sets(X3C)", лежащей в классе ***NPC***, к задаче Штейнера на графах.
* Задача Штейнера на графах: пусть дан взвешенный граф G = (V, Е), где множество вершин V состоит из непересекающихся множеств, множества терминалов А и множества точек Штейнера S. Задача состоит в нахождении такого подграфа G', который является деревом, покрывающим все терминальные вершины, и имеет минимальную длину среди всех подобных подграфов. 

Условие Х3С:

**Дано**: Конечное множество *Х = {х<sub>1</sub>,..., х<sub>3q</sub>}, |Х| = 3q*, набор *C = {C<sub>1</sub>,..., C<sub>n</sub>}* из 3-элементых подмножеств множества *Х*.

**Вопрос**: Содержит ли *С* точное покрытие *Х*, т.е набор подмножеств *С'* такой, что каждый элемент из *Х* содержится ровно в одном элементе из *С'*? Элементы множества *С'* формируют разбиение *Х*.

Построим граф для задачи Штейнера по условию X3C:

<img width="141" alt="Граф по X3C" src="https://user-images.githubusercontent.com/47656959/97813563-09ce7a00-1c9a-11eb-85a0-2ab578da8ed3.png">

Вершина C<sub>i</sub> соединяется с теми иксами, которые она содержит. Обозначив терминальными вершинами V и х<sub>1</sub>,..., х<sub>3q</sub> и дав всем ребрам вес 1, получим классическую задачу Штейнера на графах. 

Мы построили за полиномиальное время по условию задачи X3C условие для задачи Штейнера. И если теперь поставить вопрос в задаче Штейнера "существует ли дерево Штейнера весом не больше чем 4q", очевидно, что если ответ на X3C "да", то ответ на поставленный вопрос аналогичен. Таким образом, задача Штейнера на графах в форме распознавания лежит в ***NPC***. Однако без этого "сужения" задача представлена в форме оптимизации и соответственно является ***NP-трудной***. Здача Штейнера на графах в свою очередь сводится к ЕЗШ, следовательно, и она является ***NP-трудной***.

Дополнительная сложность нашей задачи заключается в том, что заданы только терминальные вершины и связи между ними, то есть необходимо перебрать все комбинации дополнительных точек, называемых точками Штейнера.
Свойства деревьев Штейнера:
* угол между любыми двумя ребрами >= 120, т. к. иначе можно поставить точку Штейнера, которая улучшит суммарный вес дерева;
* степень всех вершин <=3, а степень точек Штейнера = 3 (следовательно, инцидентные им ребра образуют угол 120);
* их количество <= количество терминальных точек - 2, что вытекает из предыдущих свойств;

Доказательство этих свойств см. в [1].
 
### Точные алгоритмы

**Общие черты алгоритмов**. Точные алгоритмы, такие как, например, алгоритмы Мэлзака[2] и Смита[3] используют деление на более мелкие подзадачи с меньшим числом вершин. В каждой подзадаче строится полное дерево Штейнера (содержит n-2 дополнительных точек при n исходных точках), а затем дерья объединяются в минимальньное дерево Штейнера для данной топологии. Если в какой-то подзадаче невозможно построить полное дерево Штейнера, то такое разбиение является тупиковым и отбрасывается. Алгоритм проверяет все возможные топологии и среди полученных локальных минимумов выбирает лучший результат.

**Оценка сложности**. Хоть и нахождение полного дерева Штейнера возможно выполнить за линнейное время от числа вершин, количество топологий, которые необходимо рассмотреть, представляет собой сверхэкспоненциальное число. Существуют усовершенствованные алгоритмы, которые позволяют отбрасывать многие топологии, однако сложности по времени и по памяти остаются экспоненциальными.

### Алгоритм, основанный на минимальном остовном дереве

**Описание алгоритма**. Будем строить минимальное остовное дерево с помощью алгоритма Прима, который наиболее эффективен для полных графов. Сначала берётся произвольная вершина и находится ребро, инцидентное данной вершине и обладающее наименьшей стоимостью. Найденное ребро и соединяемые им две вершины образуют дерево. Затем, рассматриваются рёбра графа, один конец которых — уже принадлежащая дереву вершина, а другой — нет; из этих рёбер выбирается ребро наименьшей стоимости. Выбираемое на каждом шаге ребро присоединяется к дереву. Рост дерева происходит до тех пор, пока не будут исчерпаны все вершины исходного графа.

**Оценка временной сложности**. Если хранить для каждой ещё не выбранной вершины минимальное ребро до дерева, полученного на данной итерации, то выбор нового ребра можно произвести из данных минимальных, что выполняется за ***O(V)***. Теперь для ещё не выбранных вершин надо выбрать минимальное ребро до полученного дерева. Так как мы храним минимальные ребра до дерева, которое было получено на предыдущем шаге, то на данном шаге либо останется то же ребро, либо ребро до последней добавленной вершины, если оно меньше по весу. Сложность этого этапа - ***O(V)***. Очевидно, что количество итераций - ***O(V)***. Таким образом, получаем, что сложность всего алгоритма алгоритма - ***O(V<sup>2</sup>)***.

**Оценка использования памяти**. Данный алгоритм требует хранения матрицы смежности, размер которой равен ***V<sup>2</sup>***, также нужно хранить массивы использованных вершин, минимальных рёбер до уже построенного дерева, что будет иметь порядок ***O(V)***. Тогда суммарное использование памяти ***O(V<sup>2</sup>)***.

**Оценка точности**. Понятно, что данный алгоритм не ялвяется точным, так как не добавляет промежуточных точек, однако опытным путём доказано, что длина минимального остовного дерева менее чем, на 16% больше, чем длина минимального дерева Штейнера. В среднем же отличие составляет около 6%.

### Алгоритм, основанный на физических аналогиях [4]

Используя механические аналогии, дерево можно интерпретировать как механическую систему, потенциальная энергия которой равна сумме расстояний между смежными вершинами. Положение устойчивого равновесия такой механической системы соответствует дереву, имеющему относительно минимальную длину. В такой модели рёбра представляют собой упругие нити, натяжение которых не зависит от того, насколько они натянуты. Исходные вершины закреплены, а точки Штейнера могут свободно перемещаться. Усттойчивое положение этих точек и есть относительно минимальное дерево Штейнера.

**Описание алгоритма**. 
1. Строится триангуляция Делоне, которая разбивает плоскость на не менее чем V - 2 треугольника. Для V - 2 треугольников, выбранных произвольно из полученных, строятся начальные положения точек Штейнера. Учитывая механическую аналогию координаты этих точек несложно считаются по формулам.

* *Триангуляция Делоне* для набора точек *V* - разбиение плоскости на непересекающиеся треугольники с вершинами из *V* таким образом, что все точки из *V* принадлежат хотя бы одному треугольнику, и для любого треугольника *t* выполняется критерий Делоне: никакая точка из *V* не лежит строго внутри окружности, описанной вокруг *t*.

2. Выполняется итерационная процедура пересчёта координат точек Штейнера, которая использует в своей основе всё ту же механическую аналогию, причём чем больше раз вызвать функцию пересчёта, тем точнее будет решение.

3. По полученному множеству вершин, строится полный граф, а затем ищется его минимальное остовное дерево с помощью алгоритма Прима. В случае, когда точка Штейнера в этом дереве имеет более 3 инцидентных рёбер, вершина удаляется и строится новое минимальное остовное дерево. Проверив таким образом все дополнительно построенные точки, получаем ответ.

**Оценка временной сложности**. Триангуляция Делоне можно построить за ***O(Vlog(V))***, например, с помощью метода заметающей прямой. Построение каждой изначальной точки Штеёнера выполняется за ***O(1)***, т. е. суммарно за ***O(V)***. Функция пересчёта требует ***O((V - 2)(V - 3))*** времени, а алгоритм Прима для полного графа выполняется за ***O(V<sup>2</sup>)***. Таким образом, суммарная сложность составит ***O(V<sup>2</sup>)*** с довольно большим коэффициентом.

**Оценка использования памяти**. Основную часть памяти здесь вновь займет матрица смежности, порядок которая не превзойдет ***O(V<sup>2</sup>)***, однако будет больше, чем в предыдущем алгоритме.

**Оценка точности**. В ходе экспериментов было показано, что в среднем данный алгорим даёт результат, которые хуже оптимального на 4,5%.

## Выбор алгоритма
Так как **точные алгоритмы** для сколько-нибудь большого числа точек будут искать решение невообразимо долго, то лучше выбрать один из приближенных алгоритмов. **Алгоритм, основанный на нахождении минимального остовного дерева** уступает в точности **алгоритму, основанному на физических аналогиях**, всего лишь на 1,5%, однако работает быстрее и проще для понимания, поэтому выберем первый.


### Источники
[1] https://www.maths.dur.ac.uk/Ug/projects/highlights/CM3/Soothill_Steiner_report.pdf

[2] A. Z. Melzak. On the problem of Steiner. Canadian Mathematical Bulletin., 4:143–148, 1961.

[3] W. D. Smith. How to find Steiner minimal trees in Euclidean d-space. Algorithmica, 7(2-3):137–177, 1992

[4] https://cyberleninka.ru/article/n/mehanicheskie-analogii-v-zadache-shteynera





