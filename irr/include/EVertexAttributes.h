#pragma once

namespace video
{

//! Enumeration for all vertex attributes there are.
enum E_VERTEX_ATTRIBUTES
{
	EVA_POSITION = 0,
	EVA_NORMAL,
	EVA_COLOR0,
	EVA_AUX,
	EVA_TCOORD0,
	EVA_TCOORD1,
	EVA_COLOR1, // TODO reorder?
	EVA_TANGENT,
	EVA_WEIGHTS,
	EVA_JOINT_IDS,
	EVA_COUNT
};

//! Array holding the built in vertex attribute names
//! @note must match attributes prepended in shader.cpp
const char *const sBuiltInVertexAttributeNames[] = {
		"inVertexPosition",
		"inVertexNormal",
		"inVertexColor_raw", // (BGRA <-> RGBA swapped)
		"inVertexAux",
		"inTexCoord0",
		"inTexCoord1",
		"inVertexColor1", // (BGRA <-> RGBA swapped)
		"inVertexTangent",
		"inVertexWeights",
		"inVertexJointIDs",
		0,
	};

} // end namespace video
