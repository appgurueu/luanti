// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include <vector>
#include "EHardwareBufferFlags.h"
#include "HWBuffer.h"
#include "IReferenceCounted.h"
#include "S3DVertex.h"
#include "irr_ptr.h"
#include "vector3d.h"
#include "WeightBuffer.h"

namespace scene
{

// glTF tangent representation: Don't store the bitangent,
// instead compute it as tangent.W * cross(normal, tangent)
// HACK too lazy to introduce core::vector4d yet, so std::array it is.
using Tangents = std::array<f32, 4>;
using TangentBuffer = VectorBuffer<Tangents, HWBuffer::Type::TANGENT>;

using TexCoordBuffer2 = VectorBuffer<core::vector2df, HWBuffer::Type::TEXCOORD2>;
using ColorBuffer2 = VectorBuffer<video::SColor, HWBuffer::Type::COLOR2>;

struct VertexBuffer final : public virtual IReferenceCounted, public HWBuffer
{
	//! Default constructor for empty buffer
	VertexBuffer() {}

	HWBuffer::Type getBufferType() const override
	{ return HWBuffer::Type::VERTEX; }

	u32 getElementSize() const override
	{ return sizeof(video::S3DVertex); }

	const void *getData() const override
	{ return Data.data(); }

	u32 getCount() const override
	{ return static_cast<u32>(Data.size()); }

	void *getData()
	{ return Data.data(); }

	const video::S3DVertex *getVertices() const
	{ return Data.data(); }

	video::S3DVertex *getVertices()
	{ return Data.data(); }

	const core::vector3df &getPosition(u32 i) const
	{ return Data[i].Pos; }

	core::vector3df &getPosition(u32 i)
	{ return Data[i].Pos; }

	const core::vector3df &getNormal(u32 i) const
	{ return Data[i].Normal; }

	core::vector3df &getNormal(u32 i)
	{ return Data[i].Normal; }

	const core::vector2df &getTCoords(u32 i) const
	{ return Data[i].TCoords; }

	core::vector2df &getTCoords(u32 i)
	{ return Data[i].TCoords; }

	const WeightBuffer *getWeightBuffer() const
	{ return UseSwSkinning ? nullptr : Weights.get(); }

	const TangentBuffer *getTangentBuffer() const
	{ return Tangents.get(); }

	TangentBuffer *getTangentBuffer()
	{ return Tangents.get(); }

	const TexCoordBuffer2 *getTexCoordBuffer2() const
	{ return TexCoords2.get(); }

	TexCoordBuffer2 *getTexCoordBuffer2()
	{ return TexCoords2.get(); }

	const ColorBuffer2 *getColorBuffer2() const
	{ return Colors2.get(); }

	ColorBuffer2 *getColorBuffer2()
	{ return Colors2.get(); }

	void useSwSkinning()
	{
		if (!Weights || UseSwSkinning)
			return;
		UseSwSkinning = true;
		MappingHint = EHM_STREAM;
		Weights->updateStaticPose(this);
	}

	//! Vertices of this buffer
	std::vector<video::S3DVertex> Data;

	//! Optional tangents
	irr_ptr<TangentBuffer> Tangents;
	//! Optional second set of texture coordinates
	irr_ptr<TexCoordBuffer2> TexCoords2;
	//! Optional second set of colors
	irr_ptr<ColorBuffer2> Colors2;

	//! Optional weights for skinning
	irr_ptr<WeightBuffer> Weights;
	//! Whether to use software skinning, only relevant if weights are present
	bool UseSwSkinning = false;
};

} // end namespace scene
