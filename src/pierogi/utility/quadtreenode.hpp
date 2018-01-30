#ifndef QUADTREENODE_HPP
#define QUADTREENODE_HPP

#include "SDL.h"

#include <memory>
#include <vector>
#include <string>

#include "p2d_rect.hpp"
#include "p2d_math.hpp"

#define NUM_SUBQUADS 4

namespace p2d { namespace utility {
    typedef unsigned int uint;

    template <typename T>
    class QuadTreeNode : public std::enable_shared_from_this<QuadTreeNode<T>> {
    public:
        QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage, uint newDepth, QuadTreeNode<T>* parentQuadNode);
        QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage);

        void insertObject(const std::shared_ptr<T>& objPtr, const p2d::math::Vector2f& position);

        std::shared_ptr<QuadTreeNode<T>> findNextQuadContaining(const p2d::math::Vector2f& position);
        std::shared_ptr<QuadTreeNode<T>> findSmallestQuadContaining(const p2d::math::Vector2f& position);

        void subdivByPosition(const p2d::math::Vector2f& position);
        void desubdivByPosition(const p2d::math::Vector2f& position);

        inline bool isLeafNode() const { return isLeafNode_; }
        inline bool containsPoint(const p2d::math::Vector2f& position) const { return coverage.contains(position); }

        void draw(SDL_Renderer* renderer) const;
    private:
        Rect<float> coverage;

        std::shared_ptr<QuadTreeNode<T>> subnodes[NUM_SUBQUADS];
                        QuadTreeNode<T>* parentPtr;
        std::vector<std::shared_ptr<T>>     container;
        uint containerSoftCapacity;
        uint containerNumObjects;

        bool isLeafNode_;
        uint depth;

    public:
        void subdiv();
        void desubdiv();
    }; // QuadTreeNode

    template <typename T>
    QuadTreeNode<T>::QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage, uint newDepth, QuadTreeNode<T>* parentQuadNode) 
    : coverage(quadCoverage),
      parentPtr(parentQuadNode),
      containerSoftCapacity(1),
      containerNumObjects(0),
      isLeafNode_(true),
      depth(newDepth) {;} // Dele

    template <typename T>
    QuadTreeNode<T>::QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage) 
    : QuadTreeNode<T>(quadCoverage, 0, nullptr) {;} // Delegating constructor

    template <typename T>
    void QuadTreeNode<T>::insertObject(const std::shared_ptr<T>& objPtr, const p2d::math::Vector2f& position) {
        std::shared_ptr<QuadTreeNode<T>> quadPtr = findNextQuadContaining(position);
        if (quadPtr == nullptr) {
            return;
        } else {
            ;
        }
        containerNumObjects++;
    } // insert

    template <typename T>
    std::shared_ptr<QuadTreeNode<T>> QuadTreeNode<T>::findNextQuadContaining(const p2d::math::Vector2f& position) {
        if (containsPoint(position)) {
            if (isLeafNode()) {
                return shared_from_this();
            }   else {
                for (uint q = 0; q < NUM_SUBQUADS; q++) {
                    if (subnodes[q]->containsPoint(position)) {
                        return subnodes[q];
                    } // if
                } // for
                return nullptr;
            } // if else
        }   else {
            return nullptr;
        } // if else
    } // findQuad

    template <typename T>
    std::shared_ptr<QuadTreeNode<T>> QuadTreeNode<T>::findSmallestQuadContaining(const p2d::math::Vector2f& position) {
        if (containsPoint(position)) {
            if (isLeafNode()) {
                return shared_from_this();
            }   else {
                for (uint q = 0; q < NUM_SUBQUADS; q++) {
                    if (subnodes[q]->containsPoint(position)) {
                        return subnodes[q]->findSmallestQuadContaining(position);
                    } // if
                } // for
                return nullptr;
            } // if else
        }   else {
            return nullptr;
        } // if else
    } // findQuad

    template <typename T>
    void QuadTreeNode<T>::subdivByPosition(const p2d::math::Vector2f& position){
        findSmallestQuadContaining(position)->subdiv();   
    }

    template <typename T>
    void QuadTreeNode<T>::desubdivByPosition(const p2d::math::Vector2f& position){
        findSmallestQuadContaining(position)->desubdiv();   
    }


    template <typename T>
    void QuadTreeNode<T>::subdiv() {
        if (isLeafNode()) {
            isLeafNode_ = false;
            subnodes[0] = std::make_shared<QuadTreeNode>(coverage * 0.5f, depth + 1, this);
            subnodes[1] = std::make_shared<QuadTreeNode>(coverage * 0.5f + coverage.getSize().getVectorX() * 0.5f, depth + 1, this);
            subnodes[2] = std::make_shared<QuadTreeNode>(coverage * 0.5f + coverage.getSize().getVectorY() * 0.5f, depth + 1, this);
            subnodes[3] = std::make_shared<QuadTreeNode>(coverage * 0.5f + coverage.getSize() * 0.5f, depth + 1, this);
        } else {
            // Throw exception
            return;
        } // if else
    } // subdiv

    template <typename T>
    void QuadTreeNode<T>::desubdiv() {
        if (isLeafNode() && !(parentPtr == nullptr)) {
            parentPtr->desubdiv();
        } else {
            isLeafNode_ = true;
            for (uint q = 0; q < NUM_SUBQUADS; q++) {
                // Collect all objects here!
                subnodes[q].reset();
            } // for
        } // if else
    }

    template <typename T>
    void QuadTreeNode<T>::draw(SDL_Renderer* renderer) const {
        SDL_RenderDrawRect(renderer, &coverage.getSDLRect());
        if (isLeafNode()) {
            return;
        } else {
            for (uint q = 0; q < NUM_SUBQUADS; q++) {
            subnodes[q]->draw(renderer);
            }// for
        } // if else
    } // draw
} // namespace utility
} // namespace p2d

#endif