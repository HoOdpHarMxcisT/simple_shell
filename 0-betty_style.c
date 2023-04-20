#include <stdio.h>

#define MAX_NUM 100

typedef struct {
    int x;
    int y;
} Point;

void print_point(Point p) {
    printf("(%d, %d)\n", p.x, p.y);
}

int main() {
    Point points[MAX_NUM];

    for (int i = 0; i < MAX_NUM; i++) {
        points[i].x = i;
        points[i].y = i * 2;
    }

    for (int i = 0; i < MAX_NUM; i++) {
        print_point(points[i]);
    }

    return 0;
}
