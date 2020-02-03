#pragma once

#include "glm/glm.hpp"

#include "Ayo/Math/Rotator.h"
#include "Ayo/Math/Vector3.h"

namespace Ayo
{

    class SceneComponent
    {
    public:
        SceneComponent();
        ~SceneComponent();

    private:
        /* Location of the component relative to its parent */
        Vector3 m_LocalLocation;

        /* Rotation of component relative to its parent */
        Rotator m_LocalRotation;

        /* Non-uniform scaling of the component relative to its parent. Applied in local space (no shearing)*/
        Vector3 m_LocalScale;

    public:

        /* Location functions */

        inline Vector3 GetLocalLocation() const { return m_LocalLocation; };
        void SetLocalLocation(Vector3 newLocation);
        void AddLocalLocation(Vector3 deltaLocation);

        //Vector3 GetWorldLocation() const;
        //void SetWorldLocation(Vector3 NewLocation);

        /* Rotation functions */

        inline Rotator GetLocalRotation() const { return m_LocalRotation; };
        void SetLocalRotation(Rotator newRotation);
        void AddLocalRotation(Rotator deltaRotation);

        //Rotator GetWorldRotation() const;
        //void SetWorldRotation(Rotator NewRotation);

        /* Scale functions */

        inline Vector3 GetLocalScale() const { return m_LocalScale; };
        void SetLocalScale(Vector3 newScale);
        void AddLocalScale(Vector3 deltaScale);

        //Vector3 GetWorldScale() const;
        //void SetWorldScale(Vector3 NewScale);

        /* Transform functions */

        /* todo: Transform after Transform class is made.
        inline Vector3 GetLocalTransform() const;
        void SetLocalTransform(Vector3 newTransform);
        void AddLocalTransform(Vector3 deltaTransform);

        Vector3 GetWorldTransform() const;
        void SetWorldTransform(Vector3 NewTransform);
        */

        /* Offset functions, takes component's direction into account */

        void AddLocalOffset(Vector3 DeltaLocation);

        /** Get the forward (X) unit direction vector from this component, in world space.  */
        Vector3 GetForwardVector() const;

        /** Get the up (Z) unit direction vector from this component, in world space.  */
        Vector3 GetUpVector() const;

        /** Get the right (Y) unit direction vector from this component, in world space.  */
        Vector3 GetRightVector() const;

        /**
         * Get transform based on this component's location, rotation, and scale
         */
        glm::mat4 GetRelativeTransform();

    };
}

