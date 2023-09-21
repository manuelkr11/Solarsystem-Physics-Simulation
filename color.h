#pragma once

struct Color {
    int r;
    int g;
    int b;
    Color(int r, int g, int b) : r(r), g(g), b(b) {} 
    void set(int r, int g, int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};