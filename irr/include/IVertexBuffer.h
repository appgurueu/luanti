// Copyright (C) 2008-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include <array>

#include "IReferenceCounted.h"
#include "S3DVertex.h"
#include "HWBuffer.h"
#include "vector3d.h"
#include "SColor.h"

namespace scene
{

struct WeightBuffer;

// glTF tangent representation: Don't store the bitangent,
// instead compute it as tangent.W * cross(normal, tangent)
// HACK too lazy to introduce core::vector4d yet, so std::array it is.
using Tangents = std::array<f32, 4>;
using TangentBuffer = VectorBuffer<Tangents, HWBuffer::Type::TANGENT>;

using TexCoordBuffer2 = VectorBuffer<core::vector2df, HWBuffer::Type::TEXCOORD2>;
using ColorBuffer2 = VectorBuffer<video::SColor, HWBuffer::Type::COLOR2>;

// TODO merge interface and sole impl (CVertexBuffer.*)
class IVertexBuffer : public virtual IReferenceCounted, public HWBuffer
{
public:

	//! Get access to vertex data. The data is an array of vertices.
	/** Which vertex type is used can be determined by getVertexType().
	\return Pointer to array of vertices. */
	virtual const void *getData() const override = 0;

	//! Get access to vertex data. The data is an array of vertices.
	/** Which vertex type is used can be determined by getVertexType().
	\return Pointer to array of vertices. */
	virtual void *getData() = 0;

	virtual const video::S3DVertex *getVertices() const = 0;

	virtual video::S3DVertex *getVertices() = 0;

	virtual u32 getCount() const override = 0;

	//! returns position of vertex i
	virtual const core::vector3df &getPosition(u32 i) const = 0;

	//! returns position of vertex i
	virtual core::vector3df &getPosition(u32 i) = 0;

	//! returns normal of vertex i
	virtual const core::vector3df &getNormal(u32 i) const = 0;

	//! returns normal of vertex i
	virtual core::vector3df &getNormal(u32 i) = 0;

	//! returns texture coord of vertex i
	virtual const core::vector2df &getTCoords(u32 i) const = 0;

	//! returns texture coord of vertex i
	virtual core::vector2df &getTCoords(u32 i) = 0;

	//! returns tangent buffer (nullptr if absent)
	virtual TangentBuffer *getTangentBuffer() = 0;
	//! returns tangent buffer (nullptr if absent)
	virtual const TangentBuffer *getTangentBuffer() const = 0;

	//! returns second texcoord buffer (nullptr if absent)
	virtual TexCoordBuffer2 *getTexCoordBuffer2() = 0;
	//! returns second texcoord buffer (nullptr if absent)
	virtual const TexCoordBuffer2 *getTexCoordBuffer2() const = 0;

	//! returns second color buffer (nullptr if absent)
	virtual ColorBuffer2 *getColorBuffer2() = 0;
	//! returns second color buffer (nullptr if absent)
	virtual const ColorBuffer2 *getColorBuffer2() const = 0;

	//! Get weight buffer for upload to the GPU, if any
	virtual const WeightBuffer *getWeightBuffer() const = 0;
	//! Enable software skinning
	virtual void useSwSkinning() = 0;
};

} // end namespace scene
