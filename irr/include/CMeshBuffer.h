// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include <vector>
#include "EPrimitiveTypes.h"
#include "IMeshBuffer.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "S3DVertex.h"

namespace scene
{

class CMeshBuffer final : public IMeshBuffer
{
public:
	//! Default constructor for empty meshbuffer
	CMeshBuffer() : Vertices(new SVertexBuffer()), Indices(new SIndexBuffer())
	{}

	//! Get material of this meshbuffer
	/** \return Material of this buffer */
	const video::SMaterial &getMaterial() const override
	{
		return Material;
	}

	//! Get material of this meshbuffer
	/** \return Material of this buffer */
	video::SMaterial &getMaterial() override
	{
		return Material;
	}

	const scene::IVertexBuffer *getVertexBuffer() const override
	{
		return Vertices.get();
	}

	scene::IVertexBuffer *getVertexBuffer() override
	{
		return Vertices.get();
	}

	const scene::IIndexBuffer *getIndexBuffer() const override
	{
		return Indices.get();
	}

	scene::IIndexBuffer *getIndexBuffer() override
	{
		return Indices.get();
	}

	//! Get the axis aligned bounding box
	/** \return Axis aligned bounding box of this buffer. */
	const core::aabbox3d<f32> &getBoundingBox() const override
	{
		return BoundingBox;
	}

	//! Set the axis aligned bounding box
	/** \param box New axis aligned bounding box for this buffer. */
	//! set user axis aligned bounding box
	void setBoundingBox(const core::aabbox3df &box) override
	{
		BoundingBox = box;
	}

	//! Recalculate the bounding box.
	/** should be called if the mesh changed. */
	void recalculateBoundingBox() override
	{
		if (Vertices->getCount()) {
			BoundingBox.reset(Vertices->getPosition(0));
			const u32 vsize = Vertices->getCount();
			for (u32 i = 1; i < vsize; ++i)
				BoundingBox.addInternalPoint(Vertices->getPosition(i));
		} else
			BoundingBox.reset(0, 0, 0);
	}

	//! Append the vertices and indices to the current buffer
	void append(const video::S3DVertex *const vertices, u32 numVertices, const u16 *const indices, u32 numIndices) override
	{
		if (vertices == getVertices())
			return;

		const u32 vertexCount = getVertexCount();
		const u32 indexCount = getIndexCount();

		Vertices->Data.insert(Vertices->Data.end(), vertices, vertices + numVertices);
		for (u32 i = vertexCount; i < getVertexCount(); i++)
			BoundingBox.addInternalPoint(Vertices->getPosition(i));

		Indices->Data.insert(Indices->Data.end(), indices, indices + numIndices);
		if (vertexCount != 0) {
			for (u32 i = indexCount; i < getIndexCount(); i++)
				Indices->Data[i] += vertexCount;
		}
	}

	//! Describe what kind of primitive geometry is used by the meshbuffer
	void setPrimitiveType(E_PRIMITIVE_TYPE type) override
	{
		PrimitiveType = type;
	}

	//! Get the kind of primitive geometry which is used by the meshbuffer
	E_PRIMITIVE_TYPE getPrimitiveType() const override
	{
		return PrimitiveType;
	}

	//! Material for this meshbuffer.
	video::SMaterial Material;
	//! Vertex buffer
	irr_ptr<SVertexBuffer> Vertices;
	//! Index buffer
	irr_ptr<SIndexBuffer> Indices;
	//! Bounding box of this meshbuffer.
	core::aabbox3d<f32> BoundingBox{{0, 0, 0}};
	//! Primitive type used for rendering (triangles, lines, ...)
	E_PRIMITIVE_TYPE PrimitiveType = EPT_TRIANGLES;
};

using SMeshBuffer = CMeshBuffer; // TODO rename
} // end namespace scene
