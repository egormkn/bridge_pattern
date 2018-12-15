#ifndef DRAWINGAPI_H
#define DRAWINGAPI_H


class DrawingApi {
private:
    unsigned width, height;

public:
    DrawingApi(unsigned width, unsigned height);

    unsigned getWidth();

    unsigned getHeight();

    virtual void drawCircle(int x, int y, int radius) = 0;

    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;

    virtual void setDrawColor(int r, int g, int b) = 0;

    virtual void show() = 0;

    virtual void clear() = 0;
};

#endif // DRAWINGAPI_H
