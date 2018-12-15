#include "DrawingApi.h"

DrawingApi::DrawingApi(unsigned width, unsigned height) : width(width), height(height) {}

unsigned DrawingApi::getWidth() {
    return width;
}

unsigned DrawingApi::getHeight() {
    return height;
}
