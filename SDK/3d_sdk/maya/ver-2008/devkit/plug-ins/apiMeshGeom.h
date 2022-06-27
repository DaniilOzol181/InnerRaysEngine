//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors, which is protected by U.S. and Canadian federal copyright 
// law and by international treaties.
//
// The Data is provided for use exclusively by You. You have the right 
// to use, modify, and incorporate this Data into other products for 
// purposes authorized by the Autodesk software license agreement, 
// without fee.
//
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the 
// following disclaimer, must be included in all copies of the 
// Software, in whole or in part, and all derivative works of 
// the Software, unless such copies or derivative works are solely 
// in the form of machine-executable object code generated by a 
// source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
// PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
// TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
// BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
// DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
// AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
// OR PROBABILITY OF SUCH DAMAGES.
//
// ==========================================================================
//+

#ifndef _apiMeshGeom
#define _apiMeshGeom

////////////////////////////////////////////////////////////////////////////////
//
// This class holds the underlying geometry for the shape or data.
// This is where geometry specific data and methods should go.
//
////////////////////////////////////////////////////////////////////////////////

#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MFloatArray.h> 
#include <maya/MVectorArray.h>

class apiMeshGeomUV; 

class apiMeshGeomUV { 
  public: 
	apiMeshGeomUV() { reset(); } 
	~apiMeshGeomUV() {} 

	int					uvId( int faceVertexIndex ) const;
	void				getUV( int uvId, float &u, float &v ) const; 
	float				u( int uvId ) const; 
	float				v( int uvId ) const; 
	int					uvcount() const; 
	void				append_uv( float u, float v ); 
	void				reset(); 
	
	MIntArray			faceVertexIndex; 
	MFloatArray			ucoord; 
	MFloatArray			vcoord; 
};

inline void apiMeshGeomUV::reset()
{
	ucoord.clear(); vcoord.clear(); faceVertexIndex.clear(); 
}

inline void apiMeshGeomUV::append_uv( float u, float v )
{
	ucoord.append( u ); 
	vcoord.append( v ); 
}

inline int apiMeshGeomUV::uvId( int fvi ) const
{
	return faceVertexIndex[fvi]; 
}

inline void apiMeshGeomUV::getUV( int uvId, float &u, float &v ) const
{
	u = ucoord[uvId]; 
	v = vcoord[uvId]; 
}

inline float apiMeshGeomUV::u( int uvId ) const
{
	return ucoord[uvId]; 
}

inline float apiMeshGeomUV::v( int uvId ) const
{
	return vcoord[uvId]; 
}

inline int apiMeshGeomUV::uvcount( ) const 
{
	return ucoord.length(); 
}


class apiMeshGeom
{
public:
	apiMeshGeom();
	~apiMeshGeom();
	apiMeshGeom& operator=( const apiMeshGeom& );

public:
    MPointArray	  vertices;
    MIntArray	  face_counts;
    MIntArray	  face_connects;
    MVectorArray  normals;
	apiMeshGeomUV uvcoords; 
    int			  faceCount;
};

#endif /* _apiMeshGeom */
