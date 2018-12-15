# Bridge pattern example

**Цель**: получить практический опыт применения структурного паттерна bridge.

Необходимо реализовать простой визуализатор графов, используя два различных графических API.
Способ визуализации графа можно выбрать самостоятельно (например, рисовать вершины по кругу).
Приложение должно поддерживать две реализации графов: на списках ребер и матрице смежностей.

**Каркас классов**:

```java
public abstract class Graph {
    /**
    * Bridge to drawing api
    */
    private DrawingApi drawingApi;

    public Graph(DrawingApi drawingApi) {
        this.drawingApi = drawingApi;
    }

    public abstract void drawGraph();
}
```

```java
public interface DrawingApi {
    long getDrawingAreaWidth();

    long getDrawingAreaHeight();

    void drawCircle(...);

    void drawLine(...);
}
```

**Примечания**:
- выбор API и реализации графа должны задаваться через аргументы командной строки при запуске приложения
- каркас классов можно менять (добавлять новые поля, методы, параметры методов и т.д.)
- в качестве drawing api можно использовать java.awt и javafx (примеры: https://github.com/akirakozov/software-design/tree/master/java/graphics/)
- можно использовать любой язык и любые api для рисования (главное, чтобы они были принципиально разные).

**Реализация**:
Приложение позволяет визуализировать графы с помощью двух разных графических API: SDL и SFML. Также используется библиотека boost::program_options для разбора аргументов командной строки.

```bash
$> ./bridge_pattern --help

Program options:
  -h [ --help ]           Help screen
  -a [ --api ] arg (=sdl) Graphic API (sdl/sfml)
  -t [ --type ] arg       Graph data type (matrix/list)
  -f [ --file ] arg       Input file
```

```bash
$> ./bridge_pattern --api sfml --type list --file input/list.txt
```

![Screenshot](/examples/screenshot.png)