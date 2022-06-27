
#ifndef _MAnimCurveClipboardItem
#define _MAnimCurveClipboardItem

//
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
// CLASS:    MAnimCurveClipboardItem
//
//
//******************************************************************************
//
// CLASS DESCRIPTION (MAnimCurveClipboardItem)
//
//  This class provides a wrapper to the clipboard item used to hold
//  on to cut/copy/paste information
//
//******************************************************************************

#if defined __cplusplus

//******************************************************************************
// INCLUDED HEADER HILES
//******************************************************************************


#include <maya/MFnAnimCurve.h>
#include <maya/MObject.h>


//******************************************************************************
// DECLARATIONS
//******************************************************************************

//	CLASS DECLARATION (MAnimCurveClipboardItem)

///	Wrapper for a clipboard item. (OpenMayaAnim) (OpenMayaAnim.py)
/**
	This class provides a wrapper to the clipboard item used to hold
	on to cut/copy/paste information
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAANIM_EXPORT MAnimCurveClipboardItem
{
public:
	///
					MAnimCurveClipboardItem();
	///
					MAnimCurveClipboardItem( const MAnimCurveClipboardItem &r);
	///
					~MAnimCurveClipboardItem();

	///
	const MObject		animCurve( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus				getAddressingInfo( unsigned int &rowCount,
										   unsigned int &childCount,
										   unsigned int &attributeCount) const;
	///
	const MString &		fullAttributeName( MStatus * ReturnStatus=NULL ) const;
	///
	const MString &		leafAttributeName( MStatus * ReturnStatus=NULL ) const;
	///
	const MString &		nodeName( MStatus * ReturnStatus=NULL ) const;
	///
	MFnAnimCurve::AnimCurveType	animCurveType( MStatus
												* ReturnStatus=NULL ) const;
	///
	MStatus				setAnimCurve( const MObject & curve );
	///
	MStatus				setAddressingInfo( unsigned int rowCount,
										   unsigned int childCount,
										   unsigned int attributeCount );
	///
	MStatus				setNameInfo( const MString & nodeName,
									 const MString & fullName,
									 const MString & leafName );
	///
	MAnimCurveClipboardItem &operator =  (const MAnimCurveClipboardItem &from);
	///
	bool	 				operator == (const MAnimCurveClipboardItem &rhs) const;

protected:
// No protected members

private:
	void *							fCurve;
	MFnAnimCurve::AnimCurveType		fAnimCurveType;

	unsigned int						fRowCount;
	unsigned int						fChildCount;
	unsigned int						fAttrCount;
	MString							fFullAttrName;
	MString							fLeafAttrName;
	MString							fNodeName;
	static const char*				className();
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

//******************************************************************************
#endif /* __cplusplus */
#endif /* _MAnimCurveClipboardItem */
