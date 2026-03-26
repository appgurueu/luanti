// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include <vector>
#include "EHardwareBufferFlags.h"
#include "HWBuffer.h"
#include "IVertexBuffer.h"
#include "S3DVertex.h"
#include "WeightBuffer.h"
#include "irr_ptr.h"
#include "vector3d.h"

namespace scene
{

struct CVertexBuffer final : public IVertexBuffer
{
	//! Default constructor for empty buffer
	CVertexBuffer() {}

	HWBuffer::Type getBufferType() const override
	{ return HWBuffer::Type::VERTEX; }

	u32 getElementSize() const override
	{ return sizeof(video::S3DVertex); }

	const void *getData() const override
	{ return Data.data(); }

	void *getData() override
	{ return Data.data(); }

	u32 getCount() const override
	{ return static_cast<u32>(Data.size()); }

	const video::S3DVertex *getVertices() const override
	{ return Data.data(); }

	video::S3DVertex *getVertices() override
	{ return Data.data(); }

	const core::vector3df &getPosition(u32 i) const override
	{ return Data[i].Pos; }

	core::vector3df &getPosition(u32 i) override
	{ return Data[i].Pos; }

	const core::vector3df &getNormal(u32 i) const override
	{ return Data[i].Normal; }

	core::vector3df &getNormal(u32 i) override
	{ return Data[i].Normal; }

	const core::vector2df &getTCoords(u32 i) const override
	{ return Data[i].TCoords; }

	core::vector2df &getTCoords(u32 i) override
	{ return Data[i].TCoords; }

	const WeightBuffer *getWeightBuffer() const override
	{ return UseSwSkinning ? nullptr : Weights.get(); }

	const TangentBuffer *getTangentBuffer() const override
	{ return Tangents.get(); }

	TangentBuffer *getTangentBuffer() override
	{ return Tangents.get(); }

	void useSwSkinning() override
	{
		if (!Weights || UseSwSkinning)
			return;
		UseSwSkinning = true;
		MappingHint = EHM_STREAM;
		Weights->updateStaticPose(this);
	}

	//! Vertices of this buffer
	std::vector<video::S3DVertex> Data;

	//! Optional weights for skinning
	irr_ptr<WeightBuffer> Weights;
	//! Optional tangents
	irr_ptr<TangentBuffer> Tangents;

	bool UseSwSkinning = false;
};

using SVertexBuffer = CVertexBuffer; // TODO rename

} // end namespace scene
