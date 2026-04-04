// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include "EPrimitiveTypes.h"
#include "IMeshBuffer.h"
#include "VertexBuffer.h"
#include "CIndexBuffer.h"
#include "WeightBuffer.h"
#include "S3DVertex.h"
#include "vector3d.h"
#include <cassert>

namespace scene
{

//! A mesh buffer which additionally manages a bounding box
// TODO appears to be redundant with CMeshBuffer except for the transformation?
struct SSkinMeshBuffer final : public IMeshBuffer
{
	//! Default constructor
	SSkinMeshBuffer() : Vertices(new VertexBuffer()), Indices(new SIndexBuffer())
	{}

	SSkinMeshBuffer(irr_ptr<VertexBuffer> &&vertices, irr_ptr<SIndexBuffer> &&indices) :
			Vertices(std::move(vertices)), Indices(std::move(indices))
	{}

	//! Constructor for standard vertices
	SSkinMeshBuffer(std::vector<video::S3DVertex> &&vertices, std::vector<u16> &&indices) :
			SSkinMeshBuffer()
	{
		Vertices->Data = std::move(vertices);
		Indices->Data = std::move(indices);
	}

	//! Get Material of this buffer.
	const video::SMaterial &getMaterial() const override
	{
		return Material;
	}

	//! Get Material of this buffer.
	video::SMaterial &getMaterial() override
	{
		return Material;
	}

	const scene::VertexBuffer *getVertexBuffer() const override
	{
		return Vertices.get();
	}

	scene::VertexBuffer *getVertexBuffer() override
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

	//! Get standard vertex at given index
	video::S3DVertex *getVertex(u32 index)
	{
		return &Vertices->Data[index];
	}

	//! Get bounding box
	const core::aabbox3d<f32> &getBoundingBox() const override
	{
		return BoundingBox;
	}

	//! Set bounding box
	void setBoundingBox(const core::aabbox3df &box) override
	{
		BoundingBox = box;
	}

	//! Recalculate bounding box
	void recalculateBoundingBox() override
	{
		if (!BoundingBoxNeedsRecalculated)
			return;

		BoundingBoxNeedsRecalculated = false;

		if (!Vertices->getCount()) {
			BoundingBox.reset(0, 0, 0);
		} else {
			auto &vertices = Vertices->Data;
			BoundingBox.reset(vertices[0].Pos);
			for (size_t i = 1; i < vertices.size(); ++i)
				BoundingBox.addInternalPoint(vertices[i].Pos);
		}
	}

	//! append the vertices and indices to the current buffer
	void append(const video::S3DVertex *const vertices, u32 numVertices, const u16 *const indices, u32 numIndices) override
	{
		assert(false);
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

	//! Call this after changing the positions of any vertex.
	void boundingBoxNeedsRecalculated()
	{
		BoundingBoxNeedsRecalculated = true;
	}

	WeightBuffer *getWeights()
	{
		return Vertices->Weights.get();
	}

	void addWeightBuffer()
	{
		Vertices->Weights.reset(new WeightBuffer(getVertexCount()));
	}

	const WeightBuffer *getWeights() const
	{
		return const_cast<SSkinMeshBuffer*>(this)->getWeights();
	}

	irr_ptr<VertexBuffer> Vertices;
	irr_ptr<SIndexBuffer> Indices;

	core::matrix4 Transformation;

	video::SMaterial Material;

	core::aabbox3d<f32> BoundingBox{{0, 0, 0}};

	//! Primitive type used for rendering (triangles, lines, ...)
	E_PRIMITIVE_TYPE PrimitiveType = EPT_TRIANGLES;

	bool BoundingBoxNeedsRecalculated = true;
};

} // end namespace scene
