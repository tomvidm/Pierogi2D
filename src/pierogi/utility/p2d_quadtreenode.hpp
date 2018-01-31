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
        QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage, uint newDepth, uint capacity, QuadTreeNode<T>* parentQuadNode);
        QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage);

        void setQuadRectCoverage(const p2d::utility::Rect<float>& quadCoverage);
        void setContainerCapacity(const uint cap);

        void insert(const std::shared_ptr<T>& objPtr);
        void insertObject(const std::shared_ptr<T>& objPtr);
        void remove(const std::shared_ptr<T>& objPtr);
        void removeObject(const std::shared_ptr<T>& objPtr);
        void moveObject(const std::shared_ptr<T>& objPtr, const p2d::math::Vector2f& dest);

        std::shared_ptr<QuadTreeNode<T>> findNextQuadContaining(const p2d::math::Vector2f& position);
        std::shared_ptr<QuadTreeNode<T>> findSmallestQuadContaining(const p2d::math::Vector2f& position);

        void subdivByPosition(const p2d::math::Vector2f& position);
        void desubdivByPosition(const p2d::math::Vector2f& position);

        inline bool isLeafNode() const { return isLeafNode_; }
        inline bool containsPoint(const p2d::math::Vector2f& position) const { return coverage.contains(position); }

        uint getNumContainedObjects() const;

        void draw(SDL_Renderer* renderer) const;
    protected:
        uint containerSoftCapacity;

    private:
        Rect<float> coverage;

        std::shared_ptr<QuadTreeNode<T>> subnodes[NUM_SUBQUADS];
                        QuadTreeNode<T>* parentPtr;
        std::vector<std::shared_ptr<T>>     container;
        uint containerNumObjects;

        bool isLeafNode_;
        uint depth;

    private:
        void distributeContentToSubnodes();
        void sendObjectCountToRoot(int c);
        void subdiv();
        void desubdiv();
    }; // QuadTreeNode

    template <typename T>
    QuadTreeNode<T>::QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage, uint newDepth, uint capacity, QuadTreeNode<T>* parentQuadNode) 
    : coverage(quadCoverage),
      parentPtr(parentQuadNode),
      containerSoftCapacity(capacity),
      containerNumObjects(0),
      isLeafNode_(true),
      depth(newDepth) {;} // Dele

    template <typename T>
    QuadTreeNode<T>::QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage) 
    : QuadTreeNode<T>(quadCoverage, 0, 1, nullptr) {;} // Delegating constructor

    template <typename T>
    void QuadTreeNode<T>::insert(const std::shared_ptr<T>& objPtr) {
        findSmallestQuadContaining(objPtr->getPosition())->insertObject(objPtr);
    }

    template <typename T>
    void QuadTreeNode<T>::setQuadRectCoverage(const p2d::utility::Rect<float>& quadCoverage) {
        coverage = quadCoverage;
    }

    template <typename T>
    void QuadTreeNode<T>::setContainerCapacity(const uint cap) {
        containerSoftCapacity = cap;
    }

/*
    This function blindly pushes the object to the quad, and selection
    should be delegated to a public interface.
*/

    template <typename T>
    void QuadTreeNode<T>::insertObject(const std::shared_ptr<T>& objPtr) {
        if (container.size() < containerSoftCapacity) {
            container.push_back(objPtr);
        } else {
            subdiv();
            distributeContentToSubnodes();
            insert(objPtr);
        } // if else

        sendObjectCountToRoot(1);
    } // insert

    template <typename T>
    void QuadTreeNode<T>::remove(const std::shared_ptr<T>& objPtr) {
        std::shared_ptr<QuadTreeNode<T>> quadPtr = findSmallestQuadContaining(objPtr);
        if (quadPtr != nullptr) {
            quadPtr->removeObject(objPtr);
        }
    } // removeObject

    template <typename T>
    void QuadTreeNode<T>::removeObject(const std::shared_ptr<T>& objPtr) {
        std::vector<std::shared_ptr<T>> newContainer;
        for (auto containerObjPtr : container){
            if (objPtr.get() != containerObjPtr.get()) {
                newContainer.push_back(containerObjPtr);
            } // if
        } // for
        container = newContainer;
        quadPtr->sendObjectCountToRoot(-1);
        
    } // removeObject

    template <typename T>
    void QuadTreeNode<T>::moveObject(const std::shared_ptr<T>& objPtr, const p2d::math::Vector2f& dest) {
        std::shared_ptr<QuadTreeNode<T>> oldQuadPtr = findSmallestQuadContaining(objPtr->getPosition());
        std::shared_ptr<QuadTreeNode<T>> newQuadPtr = findSmallestQuadContaining(dest);

        oldQuadPtr->removeObject(objPtr);
        newQuadPtr->insertObject(objPtr);
    } // moveObject

    template <typename T>
    void QuadTreeNode<T>::distributeContentToSubnodes() {
        for (auto objPtr : container) {
            insert(objPtr);
        }

        container.clear();
    }

    template <typename T>
    void QuadTreeNode<T>::sendObjectCountToRoot(int c) {
        containerNumObjects += c;
        if (parentPtr != nullptr) {
            parentPtr->sendObjectCountToRoot(c);
        }
    }

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
            subnodes[0] = std::make_shared<QuadTreeNode>(coverage * 0.5f, depth + 1, containerNumObjects, this);
            subnodes[1] = std::make_shared<QuadTreeNode>(coverage * 0.5f + coverage.getSize().getVectorX() * 0.5f, depth + 1, containerNumObjects, this);
            subnodes[2] = std::make_shared<QuadTreeNode>(coverage * 0.5f + coverage.getSize().getVectorY() * 0.5f, depth + 1, containerNumObjects, this);
            subnodes[3] = std::make_shared<QuadTreeNode>(coverage * 0.5f + coverage.getSize() * 0.5f, depth + 1, containerNumObjects, this);
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

    /*
        Simple and recursive, but should be replaced by a bookkeeping scheme
        to avoid having to recurse through the whole tree just to get a simple number.
    */
    template <typename T>
    uint QuadTreeNode<T>::getNumContainedObjects() const {
        if (isLeafNode()) {
            return container.size();
        } else {
            uint result = 0;
            for (uint q = 0; q < NUM_SUBQUADS; q++) {
                result += subnodes[q]->getNumContainedObjects();
            }
            return result;
        } 
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