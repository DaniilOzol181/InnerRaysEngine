
#-
# ==========================================================================
# Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
# rights reserved.
#
# The coded instructions, statements, computer programs, and/or related 
# material (collectively the "Data") in these files contain unpublished 
# information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
# licensors, which is protected by U.S. and Canadian federal copyright 
# law and by international treaties.
#
# The Data is provided for use exclusively by You. You have the right 
# to use, modify, and incorporate this Data into other products for 
# purposes authorized by the Autodesk software license agreement, 
# without fee.
#
# The copyright notices in the Software and this entire statement, 
# including the above license grant, this restriction and the 
# following disclaimer, must be included in all copies of the 
# Software, in whole or in part, and all derivative works of 
# the Software, unless such copies or derivative works are solely 
# in the form of machine-executable object code generated by a 
# source language processor.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
# AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
# WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
# NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
# PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
# TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
# BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
# DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
# AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
# OR PROBABILITY OF SUCH DAMAGES.
#
# ==========================================================================
#+

# import maya
# maya.cmds.loadPlugin("moveManip.py")

# maya.cmds.spMoveManipCtxCmd( 'spMoveManipContext1' )
# maya.cmds.setParent( 'Shelf1' )
# maya.cmds.toolButton( 'spMoveManip1', cl='toolCluster', t='spMoveManipContext1', i1="moveManip.xpm" )

import sys
import maya.OpenMaya as OpenMaya
import maya.OpenMayaUI as OpenMayaUI
import maya.OpenMayaMPx as OpenMayaMPx

moveManipId = OpenMaya.MTypeId(0x87009)
contextCmdName = "spMoveManipCtxCmd"
nodeName = "spMoveManip"

class moveManip(OpenMayaMPx.MPxManipContainer):
	fDistanceManip = OpenMaya.MDagPath()
	fFreePointManip = OpenMaya.MDagPath()
	
	def __init__(self):
		OpenMayaMPx.MPxManipContainer.__init__(self)
		
	def createChildren(self):
		self.fDistanceManip = self.addDistanceManip("distanceManip", "distance")
		distanceManipFn = OpenMayaUI.MFnDistanceManip(self.fDistanceManip)
		startPoint = OpenMaya.MPoint(0.0, 0.0, 0.0)
		direction = OpenMaya.MVector(0.0, 1.0, 0.0)
		distanceManipFn.setStartPoint(startPoint)
		distanceManipFn.setDirection(direction)
		self.fFreePointManip = self.addFreePointTriadManip("pointManip", "freePoint")

	def connectToDependNode(self, node):
		nodeFn = OpenMaya.MFnDependencyNode(node)
		
		try:
			syPlug = nodeFn.findPlug("scaleY")
			tPlug = nodeFn.findPlug("translate")
			distanceManipFn = OpenMayaUI.MFnDistanceManip(self.fDistanceManip)
			distanceManipFn.connectToDistancePlug(syPlug)
			freePointManipFn = OpenMayaUI.MFnFreePointTriadManip(self.fFreePointManip)
			freePointManipFn.connectToPointPlug(tPlug)
			OpenMayaMPx.MPxManipContainer.finishAddingManips(self)
			OpenMayaMPx.MPxManipContainer.connectToDependNode(self,node)
		except:
			sys.stderr.write( "Error finding and connecting plugs\n" )
			raise

def moveManipCreator():
	return OpenMayaMPx.asMPxPtr( moveManip() )
	
def moveManipInitialize():
	OpenMayaMPx.MPxManipContainer.initialize()
	
class moveManipContext(OpenMayaMPx.MPxSelectionContext):
	def __init__(self):
		OpenMayaMPx.MPxSelectionContext.__init__(self)

	def toolOnSetup(self,event):
		updateManipulators(self)
		OpenMaya.MModelMessage.addCallback(OpenMaya.MModelMessage.kActiveListModified, updateManipulators, self)


def updateManipulators(clientData):
	clientData.deleteManipulators()
	selectionList = OpenMaya.MSelectionList()

	OpenMaya.MGlobal.getActiveSelectionList(selectionList)
	selectionIter = OpenMaya.MItSelectionList(selectionList, OpenMaya.MFn.kInvalid)
	while not selectionIter.isDone():
		dependNode = OpenMaya.MObject()
		selectionIter.getDependNode(dependNode)
		if dependNode.isNull() or not dependNode.hasFn(OpenMaya.MFn.kDependencyNode):
			print "depend node is null"
			continue
		dependNodeFn = OpenMaya.MFnDependencyNode(dependNode)
		rPlug = dependNodeFn.findPlug("translate", False)
		sPlug = dependNodeFn.findPlug("scaleY", False)
		if rPlug.isNull() or sPlug.isNull():
			print "translate and/or scale plugs are null"			selectionIter.next()			continue
		manipObject = OpenMaya.MObject()
		manipulator = OpenMayaMPx.MPxManipContainer.newManipulator(nodeName, manipObject)
		if manipulator is not None:
			clientData.addManipulator(manipObject)
			manipulator.connectToDependNode(dependNode)
		selectionIter.next()
	

class moveManipCtxCmd(OpenMayaMPx.MPxContextCommand):
	def __init__(self):
		OpenMayaMPx.MPxContextCommand.__init__(self)

	def makeObj(self):
		return OpenMayaMPx.asMPxPtr( moveManipContext() )

def contextCmdCreator():
	return OpenMayaMPx.asMPxPtr( moveManipCtxCmd() )

# initialize the script plug-in
def initializePlugin(mobject):
	mplugin = OpenMayaMPx.MFnPlugin(mobject)
	
	try:
		mplugin.registerContextCommand( contextCmdName, contextCmdCreator )
	except:
		print "Failed to register context command: %s" % contextCmdName
		raise

	try:
		mplugin.registerNode(nodeName, moveManipId, moveManipCreator, moveManipInitialize, OpenMayaMPx.MPxNode.kManipContainer)
	except:
		print "Failed to register node: %s" % nodeName
		raise

# uninitialize the script plug-in
def uninitializePlugin(mobject):
	mplugin = OpenMayaMPx.MFnPlugin(mobject)
	
	try:
		mplugin.deregisterContextCommand(contextCmdName)
	except:
		print "Failed to deregister context command: %s" % contextCmdName
		raise

	try:
		mplugin.deregisterNode(moveManipId)
	except:
		print "Failed to deregister node: %s" % nodeName
		raise

