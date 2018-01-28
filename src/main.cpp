#include <iostream>

// #include "GL/glew.h"
#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::utility::QuadTreeNode<p2d::Object, 2> rootNode;
    rootNode.setRectCoverage(p2d::utility::Rect<float>(0.f, 0.f, 100.f, 100.f));
    p2d::Object obj1;
    p2d::Object obj2;
    p2d::Object obj3;
    obj1.setPosition(p2d::math::Vector2f(20.f, 20.f));
    obj2.setPosition(p2d::math::Vector2f(20.f, 25.f));
    rootNode.insert(obj1);
    rootNode.insert(obj2);
    std::cout << rootNode.generateDebugString();
    obj3.setPosition(p2d::math::Vector2f(30.f, 35.f));
    rootNode.insert(obj3);
    std::cout << rootNode.generateDebugString();

    p2d::Instance instance;

    return 0;
} // int main