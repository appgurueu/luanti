// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include "vector3d.h"
#include "vector2d.h"
#include "SColor.h"

namespace video
{

//! Base vertex, storing attributes which most vertex types need
struct S3DVertex
{
	//! default constructor
	constexpr S3DVertex() :
			Color(0xffffffff), Aux(0) {}

	//! constructor
	constexpr S3DVertex(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, SColor c, f32 tu, f32 tv, u16 a = 0) :
			Pos(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv), Aux(a) {}

	//! constructor
	constexpr S3DVertex(const core::vector3df &pos, const core::vector3df &normal,
			SColor color, const core::vector2df &tcoords, u16 aux = 0) :
			Pos(pos),
			Normal(normal), Color(color), TCoords(tcoords), Aux(aux) {}

	//! Position
	core::vector3df Pos;

	//! Normal vector
	core::vector3df Normal;

	//! Color
	SColor Color;

	//! Texture coordinates
	core::vector2df TCoords;

	//! Auxiliary value (free to use)
	u16 Aux;

	constexpr bool operator==(const S3DVertex &other) const
	{
		return ((Pos == other.Pos) && (Normal == other.Normal) &&
				(Color == other.Color) && (TCoords == other.TCoords) &&
				(Aux == other.Aux));
	}

	constexpr bool operator!=(const S3DVertex &other) const
	{
		return ((Pos != other.Pos) || (Normal != other.Normal) ||
				(Color != other.Color) || (TCoords != other.TCoords) ||
				(Aux != other.Aux));
	}

	constexpr bool operator<(const S3DVertex &other) const
	{
		if (Pos < other.Pos)
			return true;
		if (Pos != other.Pos)
			return false;
		if (Normal < other.Normal)
			return true;
		if (Normal != other.Normal)
			return false;
		if (Color < other.Color)
			return true;
		if (Color != other.Color)
			return false;
		if (TCoords < other.TCoords)
			return true;
		if (TCoords != other.TCoords)
			return false;
		return Aux < other.Aux;
	}

	//\param d d=0 returns other, d=1 returns this, values between interpolate.
	S3DVertex getInterpolated(const S3DVertex &other, f32 d)
	{
		d = core::clamp(d, 0.0f, 1.0f);
		return S3DVertex(Pos.getInterpolated(other.Pos, d),
				Normal.getInterpolated(other.Normal, d),
				Color.getInterpolated(other.Color, d),
				TCoords.getInterpolated(other.TCoords, d),
				d == 0.0f ? other.Aux : Aux);
	}
};

} // end namespace video
