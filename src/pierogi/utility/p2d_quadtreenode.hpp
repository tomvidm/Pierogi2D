#ifndef P2D_QUADTREENODE_HPP
#define P2D_QUADTREENODE_HPP

#include <vector>
#include <memory>
#include <string>
#include <set>

#include "SDL.h"
#include "p2d_rect.hpp"

#include "p2d_stringutils.hpp"

#include "../p2d_object.hpp"
#include "../debug/p2d_logger.hpp"

namespace p2d { namespace utility {
    typedef unsigned int IntMask;
    typedef unsigned int uint;

    enum SubQuad { 
        ROOT = -1,
        NW = 0, 
        NE = 1, 
        SE = 2, 
        SW = 3
    };

    /*
    QuadTreeNode
    Holds N objects of type T and some info about its place in the quadtree.

    REQUIRES:
    The container holds pointers to objects of type T. For the algorithms to work,
    T must have an interface which 
    */
    template <uint N>
    class QuadTreeNode {
    public:
        QuadTreeNode(const SubQuad& quadHeading, const Rect<float>& rectCoverage);
        ~QuadTreeNode();

        void remove(p2d::Object* objPtr);

        bool isLeafNode() const;

        void insert(p2d::Object* obj);
        void insert(p2d::Object& obj);
        void insert(std::shared_ptr<Object> objPtr);

        inline Rect<float> getCoverage() const { return coverage; }
        void setRectCoverage(const Rect<float>& rect);
        bool coversPoint(const p2d::math::Vector2f& point) const;

        QuadTreeNode* findNodeContaining(const p2d::math::Vector2f& point);
        QuadTreeNode* getNorth();
        QuadTreeNode* getEast();
        QuadTreeNode* getSouth();
        QuadTreeNode* getWest();
        std::set<p2d::Object*> containedObjects();

        QuadTreeNode* get(const SubQuad& which);

        void draw(SDL_Renderer* renderer) const;

    protected:
        void setParent(QuadTreeNode* newParentPtr);
        void setHeading(const SubQuad& heading);

        void decrementObjectCount();
        
        void subdivide();
        void unsubdivide();
    private:
        bool isLeafNode_ = true;
        uint treeDepth = 0;
        uint numObjectsContained = 0;
        const unsigned int capacity;
        std::set<p2d::Object*> container;
        Rect<float> coverage;

        QuadTreeNode* parentPtr = nullptr;
        QuadTreeNode* quadNW;
        QuadTreeNode* quadSW;
        QuadTreeNode* quadNE;
        QuadTreeNode* quadSE;
        SubQuad heading;

        void distributeRectCoverageToSubnodes();
        void setParentOfSubnodes();
        void setSubnodeHeading();
        void setDepth(uint depth = 0);
        void distributeObjectsToSubnodes();

        p2d::debug::Logger* logger;
    }; // QuadTreeTree

    template <uint N>
    QuadTreeNode<N>::QuadTreeNode(const SubQuad& quadHeading, const Rect<float>& rectCoverage)
    : capacity(N), heading(quadHeading), coverage(rectCoverage) {
        logger = p2d::debug::Logger::getInstancePtr();
        //logger->log("QuadTreeNode constructed...", p2d::debug::LogLevel::DEBUG);
    } // constructor

    template <uint N>
    QuadTreeNode<N>::~QuadTreeNode() {
        if (!isLeafNode()) {
            delete quadNW;
            delete quadSW;
            delete quadNE;
            delete quadSE;
        } // if
        // Memory access error when deleting
    }

    template <uint N>
    void QuadTreeNode<N>::subdivide() {
        std::cout << "\t Subdividing lead node into quadtreenodes at ";
        if (isLeafNode()) {
            Rect<float> newCoverage = coverage * 0.5f;
            quadNW = new QuadTreeNode<N>(SubQuad::NW, newCoverage);
            quadSW = new QuadTreeNode<N>(SubQuad::SW, newCoverage + newCoverage.getSize().getVectorY());
            quadNE = new QuadTreeNode<N>(SubQuad::NE, newCoverage + newCoverage.getSize().getVectorX());
            quadSE = new QuadTreeNode<N>(SubQuad::SE, newCoverage + newCoverage.getSize());
            std::cout << quadNW << ", " << quadSW << ", " << quadNE << ", " << quadSE << std::endl;
            isLeafNode_ = false;
            setParentOfSubnodes();
            setDepth();
        } // if
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::unsubdivide() {
        if (numObjectsContained <= capacity && !isLeafNode()) {
            container = containedObjects();
            delete quadNW;
            delete quadNE;
            delete quadSW;
            delete quadSE;
            isLeafNode_ = true;
            parentPtr->unsubdivide();
        } // if
    } // unsubdivide

    template <uint N>
    void QuadTreeNode<N>::remove(p2d::Object* objPtr) {
        auto objPtrIter = container.find(objPtr);
        if (objPtrIter != container.end()) {
            container.erase(objPtrIter);
            decrementObjectCount();
            parentPtr->unsubdivide();
        } // if
    } // update

    template <uint N>
    void QuadTreeNode<N>::decrementObjectCount() {
        numObjectsContained--;
        if (parentPtr != nullptr) {
            parentPtr->decrementObjectCount();
        } // if
    } // decrementObjectCount

    template <uint N>
    bool QuadTreeNode<N>::isLeafNode() const {
        return isLeafNode_;
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::insert(p2d::Object* objPtr) {
        if (isLeafNode()) {
            if (container.size() < capacity) {
                std::cout << "Inserting object at " << objPtr << " into leaf node " << this << std::endl;
                container.insert(objPtr);
            } else {
                std::cout << "Container capacity reached. Time for S U B D I V I S I O N" << std::endl;
                subdivide();
                findNodeContaining(objPtr->getPosition())->insert(objPtr);
                distributeObjectsToSubnodes();
            } // if else
        } else {
            findNodeContaining(objPtr->getPosition())->insert(objPtr);
        } // if else
        objPtr->setQuad(this);
        numObjectsContained++;
    } // insert

    template <uint N>
    void QuadTreeNode<N>::insert(p2d::Object& obj) {
        insert(&obj);
    } // insert

    template <uint N>
    void QuadTreeNode<N>::insert(std::shared_ptr<Object> objPtr) {
        insert(objPtr.get());
    }

    template <uint N>
    void QuadTreeNode<N>::setParent(QuadTreeNode* newParentPtr) {
        parentPtr = newParentPtr;
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::setHeading(const SubQuad& subnodeHeading) {
        heading = subnodeHeading;
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::setRectCoverage(const Rect<float>& rect) {
        coverage = rect;
    } // setRectCoverage

    template <uint N>
    bool QuadTreeNode<N>::coversPoint(const p2d::math::Vector2f& point) const {
        return coverage.contains(point);
    } // coversPoint

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::findNodeContaining(const p2d::math::Vector2f& point) {
        if (quadNW->coversPoint(point)) {
            if (quadNW->isLeafNode()) {
                return quadNW;
            } else {
                return quadNW->findNodeContaining(point);
            } // if else
        } // if
        if (quadSW->coversPoint(point)) {
            if (quadSW->isLeafNode()) {
                return quadSW;
            } else {
                return quadSW->findNodeContaining(point);
            } // if else
        } // if
        if (quadNE->coversPoint(point)) {
            if (quadNE->isLeafNode()) {
                return quadNE;
            } else {
                return quadNE->findNodeContaining(point);
            } // if else
        } // if
        if (quadSE->coversPoint(point)) {
            if (quadSE->isLeafNode()) {
                return quadSE;
            } else {
                return quadSE->findNodeContaining(point);
            } // if else
        } // if
        return this;
    } // findNodeContaining

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::getNorth() {
        if (heading == SubQuad::SW) {
            return parentPtr->get(SubQuad::NW);
        } else if (heading == SubQuad::SE) {
            return parentPtr->get(SubQuad::NE);
        } else if (heading == SubQuad::NW || heading == SubQuad::NE) {
            return this; // Need to develop a good way to do this
        }
    }

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::getEast() {
        if (heading == SubQuad::NW) {
            return parentPtr->get(SubQuad::NE);
        } else if (heading == SubQuad::SW) {
            return parentPtr->get(SubQuad::SE);
        } else if (heading == SubQuad::NE || heading == SubQuad::SE) {
            return this; // Need to develop a good way to do this
        }
    }

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::getSouth() {
        if (heading == SubQuad::NW) {
            return parentPtr->get(SubQuad::SW);
        } else if (heading == SubQuad::NE) {
            return parentPtr->get(SubQuad::SE);
        } else if (heading == SubQuad::SW || heading == SubQuad::SE) {
            return this; // Need to develop a good way to do this
        }
    }

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::getWest() {
        if (heading == SubQuad::NE) {
            return parentPtr->get(SubQuad::NW);
        } else if (heading == SubQuad::SE) {
            return parentPtr->get(SubQuad::SW);
        } else if (heading == SubQuad::NE || heading == SubQuad::SE) {
            return this; // Need to develop a good way to do this
        }
    }

    template <uint N>
    std::set<p2d::Object*> QuadTreeNode<N>::containedObjects() {
        if (isLeafNode()) {
            return container;
        } else {
            std::set<p2d::Object*> result;
            std::set<p2d::Object*> collected;

            collected = quadNW->containedObjects();
            result.insert(collected.begin(), collected.end());
            collected = quadNE->containedObjects();
            result.insert(collected.begin(), collected.end());
            collected = quadSW->containedObjects();
            result.insert(collected.begin(), collected.end());
            collected = quadSE->containedObjects();
            result.insert(collected.begin(), collected.end());

            return result;
        } // if else
    } // containedObjects

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::get(const SubQuad& which) {
        if (which == SubQuad::NW) {
            return quadNW;
        } else if (which == SubQuad::SW) {
            return quadSW;
        } else if (which == SubQuad::NE) {
            return quadNE;
        } else (which == SubQuad::SE) {
            return quadSE;
        }
    } // get

    template <uint N>
    void QuadTreeNode<N>::setParentOfSubnodes() {
        quadNW->setParent(this);
        quadSW->setParent(this);
        quadNE->setParent(this);
        quadSE->setParent(this);
    } // distributeRectCoverageToSubnodes

    template <uint N>
    void QuadTreeNode<N>::setDepth(uint depth) {
        treeDepth = depth;
        if (!isLeafNode()) {
            quadNW->setDepth(treeDepth + 1);
            quadSW->setDepth(treeDepth + 1);
            quadNE->setDepth(treeDepth + 1);
            quadSE->setDepth(treeDepth + 1);
        } // if 
    } // setDepth

    template <uint N>
    void QuadTreeNode<N>::distributeObjectsToSubnodes() {
        std::cout << container.size() << std::endl;
        for (auto objIter : container) {
            findNodeContaining(objIter->getPosition())->insert(objIter);
        } // for
        container.clear();
        std::cout << container.size() << std::endl;
    } // distributePObjectsToSubnodes

    template <uint N>
    void QuadTreeNode<N>::draw(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &coverage.getSDLRect());
        if (!isLeafNode()) {
            quadNW->draw(renderer);
            quadSW->draw(renderer);
            quadNE->draw(renderer);
            quadSE->draw(renderer);
        } // if
    } // draw
} // utility
} // p2d

#endif