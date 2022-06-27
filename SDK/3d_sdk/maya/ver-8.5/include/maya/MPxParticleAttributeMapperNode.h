#ifndef _MPxParticleAttributeMapperNode
#define _MPxParticleAttributeMapperNode
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MPxParticleAttributeMapperNode
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MPxParticleAttributeMapperNode)
// 
//  MPxParticleAttributeMapperNode is the parent class of all user defined per particle
//	attribute mapping nodes. This class extends Maya's internal 'arrayMapper' node,
//	inheriting its attributes and default behaviour.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MTypes.h>
#include <maya/MPxNode.h>


// *****************************************************************************

// CLASS DECLARATION (MPxParticleAttributeMapperNode)

/// User defined per particle attribute mapping nodes. (OpenMayaFX) (OpenMayaMPx.py)
/**
	Create user defined particle attribute nodes.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAFX_EXPORT MPxParticleAttributeMapperNode : public MPxNode  
{
public:

	///
	MPxParticleAttributeMapperNode();
	///
	virtual ~MPxParticleAttributeMapperNode();
    	///               
	virtual MPxNode::Type type() const;
	///
	virtual MStatus	compute(const MPlug& plug, MDataBlock& dataBlock);

	//
    // Inherited attributes
	//

	/// Input node used to compute output values
	static MObject computeNode;

	/// The U component of an array of sample positions.
	static MObject uCoordPP;

	/// The V component of an array of sample positions.
	static MObject vCoordPP;

	/// The minimum limit on the output attribute outValuePP
	static MObject outMinValue;

	/// The maximum limit on the output attribute outValuePP
	static MObject outMaxValue;

	/// This attribute allows the propagation of any changes to the
	// computeNode's outColor through the arrayMapper and onto the attribute
	// that the particleAttributeNode is driving.
	static MObject computeNodeColor;

	/// The R component of the computeNodeColor
	static MObject computeNodeColorR;

	/// The G component of the computeNodeColor
	static MObject computeNodeColorG;

	/// The B component of the computeNodeColor
	static MObject computeNodeColorB;

	/// This attribute holds the value for time (in seconds)
	static MObject time;

	/// The outputColor vector per-particle attribute
	static MObject outColorPP;

	/// The outputValue vector per-particle attribute
	static MObject outValuePP;

private:
	static void				initialSetup();
	static const char*	    className();

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MPxParticleAttributeMapperNode */
