#pragma once

#include "src/perspectiveCamera.h"

/**
 * A node in a linked list of PerspectiveCamera objects.
 */
class CameraNode {
private:
   /**
    * Pointer to the PerspectiveCamera object stored in the node.
    */
   PerspectiveCamera* m_camera;

   /**
    * Pointer to the next CameraNode in the list.
    */
   CameraNode* m_next;

public:
   /**
    * Constructs a CameraNode with the given camera and next node.
    * @param camera Pointer to the PerspectiveCamera object to be stored in the node.
    * @param next Pointer to the next CameraNode in the list.
    */
   CameraNode(PerspectiveCamera* camera, CameraNode* next);

   /**
    * Deleted copy constructor.
    */
   CameraNode(const CameraNode& o) = delete;

   /**
    * Deleted copy assignment operator.
    */
   CameraNode& operator=(const CameraNode& o) = delete;

   /**
    * Destructor.
    */
   ~CameraNode();

   /**
    * Returns a pointer to the next CameraNode in the list.
    * @return Pointer to the next CameraNode in the list.
    */
   CameraNode* getNext();

   /**
    * Returns a pointer to the PerspectiveCamera object
    * @return Pointer to the PerspectiveCamera object stored in the node.
    */
   PerspectiveCamera* getCamera();

   /**
   * Sets the next CameraNode in the list.
   * @param next Pointer to the next CameraNode in the list.
   */
   void setNext(CameraNode* next);

};