'''------------------------------------------------------
Program Name: 	FBXExporter.py
Author: 		Matt Traynar
Date: 			November 2015

Institution: 	Bournemouth University
Course: 		Level 5 BA-CVA Student

Purpose:		This program can be used to export
				objects so that they areready to be 
				imported into Unreal Engine. The GUI
				is fairly self-explanatory but allows
				the user to select objects and add 
				them to a list, reset the pivots (to
				avoid errors in UE4), specify an 
				export path and name and finally 
				export the object in the '.fbx' format
				
				ALL WORK IS MY OWN
-------------------------------------------------------'''

import maya.cmds as cmds

#Function for calculating the lowest vertex of a shape
def lowestPoint(shape):
	#Create a variable, set it unreasonably high to avoid errors
	lowestY=500000
	
	#Find how many vertices the shape has
	numIndices=cmds.polyEvaluate([shape],vertex=True)
	
	#Cycle through each vertex, find the lowest Y translation and return it
	for i in range(0,numIndices):
		currentVertex=cmds.xform(str(shape)+".pnts["+str(i)+"]",query=True,translation=True,worldSpace=True)
		if(currentVertex[1]<lowestY):
			lowestY=currentVertex[1]
			
	return lowestY

#Function for reseting pivot points	
def resetPivots():
	#Get the names of the objects from the GUI
	selected=cmds.textScrollList("Objects",q=True,ai=True)
	
	#Cycle through each object
	for poly in selected:
		scalePiv=str(poly)+".scalePivot"
		rotPiv=str(poly)+".rotatePivot"
		
		#Get the pivot translation of the poly
		pivot=cmds.xform(scalePiv,query=True,translation=True,ws=True)
		
		#Set the Y translation to the translation of the lowest vertex
		pivot[1]=lowestPoint(poly)
		
		#Finally move the scale and rotation pivots
		cmds.xform([scalePiv,rotPiv],t=pivot,ws=True)

#Function for finding a file path
def filePath():
	#Write a new string for later use
	fbxFile="FBX Files (*.fbx)"
	
	#Create a dialog box which asks the user to specify a file path and
	#return this file path to a variable
	USER_filePath=cmds.fileDialog2(fileFilter=fbxFile, dialogStyle=2,rf=True, okc="Select")	
	
	#Edit the File Path text field to display the user chosen file path (but only
	#do this if the user chose a file destination
	if USER_filePath is not None:
		cmds.textFieldButtonGrp("File_Path",e=True,text=USER_filePath[0])
	
#Function which exports to .fbx
def exportFBX():
	#Get the file path chosen by the user
	FilePath=cmds.textFieldButtonGrp("File_Path",q=True,text=True)
	
	#Save the selected objects as .fbx and tell the user
	cmds.file(FilePath,force=True, options="v=0", type="FBX export", pr=True, es=True)
	print("File exported to ",FilePath)
	
#Function which adds selected objects to the GUI list
def selectObjects():
	#Get the names of the selected objects
	selected=cmds.ls(sl=True)
	
	#Get the list of objects which the user has already added
	alreadyAdded = cmds.textScrollList("Objects",q=True,ai=True)

	#Create a new list
	newList=[]
	
	#Cycle through the selected objects
	for item in selected:
		
		#If there are already objects in the GUI list check for duplicates
		if alreadyAdded is not None:
			
			#If there is a duplicate tell the user
			if item in alreadyAdded:
				cmds.confirmDialog(title="Duplicate",m="Some items have already been added",b="Confirm",db="Confirm",icn="information")
				
			#Otherwise add the item name to the list
			else:
				newList.append(item)
		else:
			newList.append(item)
	
	#Edit the GUI list to include the new object names
	cmds.textScrollList("Objects",e=True,numberOfRows=(len(selected)+5),allowMultiSelection=True,append=newList)

#Function to clear the GUI list					
def clearList():
	cmds.textScrollList("Objects",e=True,ra=True)

#Main GUI function		
def GUI():
	#Set the window name as a variable for easy use
	windowName = "Unreal Exporter"
	
	#Check for pre-existing GUIs and delete them
	if(cmds.window(windowName,exists=True)):
		print("Window already exists, deleting it")
		cmds.deleteUI(windowName)
	
	#Make a GUI window which cannot be resized by the user
	GUIWindow=cmds.window(windowName,title=windowName,w=300,h=300,s=False)
	
	cmds.columnLayout(adj=True,rowSpacing=10,columnWidth=250)
	
	#Create a scroll list to store objects in
	objectList = cmds.textScrollList("Objects")
	
	cmds.rowLayout("Object Buttons",numberOfColumns=4,columnWidth2=(90,80))
	
	#This button is purely for aesthetic purposes
	cmds.button(vis=False,w=35)
	
	#Three buttons which all run various functions
	clearObjectButton = cmds.button(l="Clear List",c="clearList()",w=100,rs=True)
	importObjectButton = cmds.button(l="Import Object",c="selectObjects()",rs=True,w=100)
	resetPivotButton = cmds.button(l="Reset Pivots",c="resetPivots()",rs=True,w=100)
	cmds.setParent("..")
	
	#Change the layout and add in some whitespace
	cmds.columnLayout(cat=["left",20])
	cmds.separator(style="none",w=200)

	#Another aesthetic button
	cmds.button(vis=False,w=50)
	
	#Add a text field/button item which will prompt the user for a file path
	fileButton = cmds.textFieldButtonGrp("File_Path",bl="Choose File Path",pht="Where Do You Want To Export To?",ed=False, bc="filePath()",ct2=["Both","Both"])
	cmds.separator(style="none",w=200,h=10)
	
	#Change the layout and include another aesthetic button
	cmds.rowLayout(numberOfColumns=3)
	cmds.button(vis=False,w=65)
	
	#Create a large button which will export the selected objects to the specified file path
	exportButton = cmds.button(l="Export Objects",c="exportFBX()",rs=True,w=200,h=50)
	
	#Finally show the window
	cmds.showWindow(GUIWindow)
	
GUI()
