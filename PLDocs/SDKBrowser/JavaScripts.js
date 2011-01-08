//Create the chmfile object for this HTML page
var chmfile = new Object();
chmfile.fullname = "";
chmfile.name = "";
chmfile.path = "";
chmfile.page = "";
getchmfile();

// Get the path and name of the CHM file and assign object values
function getchmfile() {
	var ra, sl, a, X, Y, Z;
	ra = /:/;
	a = location.href.search(ra);
	sl = "::";
	Y = location.href.lastIndexOf(sl);
	if (a == 4) { // file: or http:
		Y = location.href.lastIndexOf("/");
		chmfile.page = unescape(location.href.substring(Y+1));
		if (location.href.substring(0,4) == "file") {
			chmfile.path = unescape(location.href.substring(8, Y+1));
		}
	} else {
		if (a == 2) X = 14; // mk:@MSITStore:
		if (a == 7) X = 7; // ms-its:
		chmfile.fullname = unescape(location.href.substring(X, Y));
		Z = chmfile.fullname.lastIndexOf("\\");
		chmfile.path = unescape(chmfile.fullname.substring(0, Z+1));
		chmfile.name = unescape(chmfile.fullname.substring(Z+1));
		chmfile.page = unescape(location.href.substring(Y+3));
	}
	/*
	alert(location.href+"\n\n"+"fullname="+chmfile.fullname+"\n"+"path="+chmfile.path+"\n"+"name="+chmfile.name+"\n"+"page="+chmfile.page);
	*/
}

// Write hidden shortcut link object in JavaScript
function shortcut(shortcut_id, shortcut_path) {
	document.write('<OBJECT id='+shortcut_id+' type="application/x-oleobject"');
	document.write(' classid="clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11"');
	document.write(' codebase="hhctrl.ocx"');
	document.write(' >');
	document.write(' <PARAM name="Command" value="ShortCut">');
	document.write(' <PARAM name="Item1" value=",'+'&quot;'+chmfile.path+shortcut_path+'&quot;'+',">');
	document.write('</OBJECT>');
}

function text_shortcut(shortcut_id, shortcut_path) {
	document.write('<OBJECT id='+shortcut_id+' type="application/x-oleobject"');
	document.write(' classid="clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11"');
	document.write(' codebase="hhctrl.ocx"');
	document.write(' >');
	document.write(' <PARAM name="Command" value="ShortCut">');
	document.write(' <PARAM name="Item1" value=",WordPad.exe,'+'&quot;'+chmfile.path+shortcut_path+'&quot;'+'">');
	document.write('</OBJECT>');
}

function scene_exe_shortcut(shortcut_id, shortcut_path) {
	var exe = chmfile.path+"Tools\\PLViewer\\PLViewer.exe";
	var scene = '&quot;'+chmfile.path+shortcut_path+'&quot;';
	document.write('<OBJECT id='+shortcut_id+' type="application/x-oleobject"');
	document.write(' classid="clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11"');
	document.write(' codebase="hhctrl.ocx"');
	document.write(' >');
	document.write(' <PARAM name="Command" value="ShortCut">');
	document.write(' <PARAM name="Item1" value=",'+exe+','+scene+'">');
	document.write('</OBJECT>');
}


// License text shortcuts
text_shortcut("License_gpl30", "gpl-3.0.txt");
text_shortcut("License_lgpl30", "lgpl-3.0.txt");
text_shortcut("License_cc_by_nc_sa_3", "cc-by-nc-sa-3.txt");


// Documentation shortcuts
shortcut("Doc_CodingConventions", "Doc\\CodingConventions.pdf");
shortcut("Doc_ReleaseNotes", "ReleaseNotes.txt");
shortcut("Doc_PLFeatures", "Doc\\PLFeatures.pdf");
shortcut("Doc_PLGeneral", "Doc\\PLGeneral.pdf");
shortcut("Doc_PLCore", "Doc\\PLCore.pdf");
shortcut("Doc_PLMath", "Doc\\PLMath.pdf");
shortcut("Doc_PLGraphics", "Doc\\PLGraphics.pdf");
shortcut("Doc_PLNetwork", "Doc\\PLNetwork.pdf");
shortcut("Doc_PLDatabase", "Doc\\PLDatabase.pdf");
shortcut("Doc_PLGui", "Doc\\PLGui.pdf");
shortcut("Doc_PLInput", "Doc\\PLInput.pdf");
shortcut("Doc_PLRenderer", "Doc\\PLRenderer.pdf");
shortcut("Doc_PLMesh", "Doc\\PLMesh.pdf");
shortcut("Doc_PLScene", "Doc\\PLScene.pdf");
shortcut("Doc_PLCompositing", "Doc\\PLCompositing.pdf");
shortcut("Doc_PLSound", "Doc\\PLSound.pdf");
shortcut("Doc_PLPhysics", "Doc\\PLPhysics.pdf");
shortcut("Doc_PLEngine", "Doc\\PLEngine.pdf");
shortcut("Doc_PixelLightAPI", "Doc\\PixelLightAPI.chm");
shortcut("Doc_PL3dsMaxSceneExport", "Doc\\PL3dsMaxSceneExport.pdf");
shortcut("Doc_PL3dsMaxModelExport", "Doc\\PL3dsMaxModelExport.pdf");


// Directory shortcuts
// Misc
shortcut("Dir_Doc", "Doc\\");
shortcut("Dir_Lib", "Lib\\");
shortcut("Dir_Runtime", "Runtime\\");
shortcut("Dir_BrowserPlugins", "BrowserPlugins\\");
shortcut("Dir_VC2010_Redistributable", "VC2010_Redistributable\\");
// Tools
shortcut("Dir_Tools", "Tools\\");
shortcut("Dir_Tools_PLViewer", "Tools\\PLViewer\\");
shortcut("Dir_3dsMax", "Tools\\3dsMax\\");
// include
shortcut("Dir_Include", "Include\\");
shortcut("Dir_PLGeneral", "include\\PLGeneral\\");
shortcut("Dir_PLCore", "include\\PLCore\\");
shortcut("Dir_PLMath", "include\\PLMath\\");
shortcut("Dir_PLGraphics", "include\\PLGraphics\\");
shortcut("Dir_PLDatabase", "include\\PLDatabase\\");
shortcut("Dir_PLNetwork", "include\\PLNetwork\\");
shortcut("Dir_PLIRC", "include\\PLIRC\\");
shortcut("Dir_PLJabber", "include\\PLJabber\\");
shortcut("Dir_PLGui", "include\\PLGui\\");
shortcut("Dir_PLInput", "include\\PLInput\\");
shortcut("Dir_PLSound", "include\\PLSound\\");
shortcut("Dir_PLRenderer", "include\\PLRenderer\\");
shortcut("Dir_PLMesh", "include\\PLMesh\\");
shortcut("Dir_PLScene", "include\\PLScene\\");
shortcut("Dir_PLPhysics", "include\\PLPhysics\\");
shortcut("Dir_PLEngine", "include\\PLEngine\\");
shortcut("Dir_PLParticleGroups", "include\\PLParticleGroups\\");
// Demos
shortcut("Dir_Demos", "Demos\\");
shortcut("Dir_Demos_Bin", "Demos\\Bin\\");
shortcut("Dir_Demo_Scenes", "Demos\\Bin\\Data\\Scenes\\");
shortcut("Dir_PLDemoRendererTriangle", "Demos\\PLDemoRendererTriangle\\");
shortcut("Dir_PLDemoRendererTexturing", "Demos\\PLDemoRendererTexturing\\");
shortcut("Dir_PLDemoMeshTeapot", "Demos\\PLDemoMeshTeapot\\");
shortcut("Dir_PLDemoRendererRTT", "Demos\\PLDemoRendererRTT\\");
shortcut("Dir_PLDemoRendererMultiView", "Demos\\PLDemoRendererMultiView\\");
shortcut("Dir_PLDemoSimpleScene", "Demos\\PLDemoSimpleScene\\");
shortcut("Dir_PLDemoPhysicsBasic", "Demos\\PLDemoPhysicsBasic\\");
shortcut("Dir_PLDemoPhysicsRagdoll", "Demos\\PLDemoPhysicsRagdoll\\");
shortcut("Dir_PLDemoNetworkChat", "Demos\\PLDemoNetworkChat\\");
shortcut("Dir_PLDemoSoundBasic", "Demos\\PLDemoSoundBasic\\");
shortcut("Dir_PLDemoPostProcess", "Demos\\PLDemoPostProcess\\");
shortcut("Dir_PLDemo2DGame", "Demos\\PLDemo2DGame\\");
shortcut("Dir_PLDemoIngameGUI", "Demos\\PLDemoIngameGUI\\");
// Samples
shortcut("Dir_Samples", "Samples\\");


// Executable shortcuts
// Demos
shortcut("Exe_PLDemoRendererTriangle", "Demos\\Bin\\PLDemoRendererTriangle.exe");
shortcut("Exe_PLDemoRendererTexturing", "Demos\\Bin\\PLDemoRendererTexturing.exe");
shortcut("Exe_PLDemoMeshTeapot", "Demos\\Bin\\PLDemoMeshTeapot.exe");
shortcut("Exe_PLDemoRendererRTT", "Demos\\Bin\\PLDemoRendererRTT.exe");
shortcut("Exe_PLDemoRendererMultiView", "Demos\\Bin\\PLDemoRendererMultiView.exe");
shortcut("Exe_PLDemoSimpleScene", "Demos\\Bin\\PLDemoSimpleScene.exe");
shortcut("Exe_PLDemoPhysicsBasic", "Demos\\Bin\\PLDemoPhysicsBasic.exe");
shortcut("Exe_PLDemoPhysicsRagdoll", "Demos\\Bin\\PLDemoPhysicsRagdoll.exe");
shortcut("Exe_PLDemoNetworkChat", "Demos\\Bin\\PLDemoNetworkChat.exe");
shortcut("Exe_PLDemoSoundBasic", "Demos\\Bin\\PLDemoSoundBasic.exe");
shortcut("Exe_PLDemoPostProcess", "Demos\\Bin\\PLDemoPostProcess.exe");
shortcut("Exe_PLDemo2DGame", "Demos\\Bin\\PLDemo2DGame.exe");
shortcut("Exe_PLDemoIngameGUI", "Demos\\Bin\\PLDemoIngameGUI.exe");
// Tools
shortcut("Exe_PLViewer", "Tools\\Bin\\PLViewer\PLViewer.exe");


// Scene text shortcuts
text_shortcut("Scene_AnchorCamera", "Demos\\Bin\\Data\\Scenes\\AnchorCamera.scene");
text_shortcut("Scene_AutomaticMeshes", "Demos\\Bin\\Data\\Scenes\\AutomaticMeshes.scene");
text_shortcut("Scene_AutomaticTextures", "Demos\\Bin\\Data\\Scenes\\AutomaticTextures.scene");
text_shortcut("Scene_CameraMoveController", "Demos\\Bin\\Data\\Scenes\\CameraMoveController.scene");
text_shortcut("Scene_MoveController", "Demos\\Bin\\Data\\Scenes\\MoveController.scene");
text_shortcut("Scene_CharacterAnimation", "Demos\\Bin\\Data\\Scenes\\CharacterAnimation.scene");
text_shortcut("Scene_MultiCameras", "Demos\\Bin\\Data\\Scenes\\MultiCameras.scene");
text_shortcut("Scene_NormalMapping", "Demos\\Bin\\Data\\Scenes\\NormalMapping.scene");
text_shortcut("Scene_OrbiterCamera", "Demos\\Bin\\Data\\Scenes\\OrbiterCamera.scene");
text_shortcut("Scene_PhysicsCharacterController", "Demos\\Bin\\Data\\Scenes\\PhysicsCharacterController.scene");
text_shortcut("Scene_PhysicsFirstPersonController", "Demos\\Bin\\Data\\Scenes\\PhysicsFirstPersonController.scene");
text_shortcut("Scene_PhysicsJoints", "Demos\\Bin\\Data\\Scenes\\PhysicsJoints.scene");
text_shortcut("Scene_PhysicsManiacMarble", "Demos\\Bin\\Data\\Scenes\\PhysicsManiacMarble.scene");
text_shortcut("Scene_PhysicsMouseInteraction", "Demos\\Bin\\Data\\Scenes\\PhysicsMouseInteraction.scene");
text_shortcut("Scene_PLParticleGroups", "Demos\\Bin\\Data\\Scenes\\PLParticleGroups.scene");
text_shortcut("Scene_Mipmaps", "Demos\\Bin\\Data\\Scenes\\Mipmaps.scene");
text_shortcut("Scene_ReflectionCubeMap", "Demos\\Bin\\Data\\Scenes\\ReflectionCubeMap.scene");
text_shortcut("Scene_SceneNodeModifiers", "Demos\\Bin\\Data\\Scenes\\SceneNodeModifiers.scene");


// Scene exe shortcuts
scene_exe_shortcut("SceneExe_AnchorCamera", "Demos\\Bin\\Data\\Scenes\\AnchorCamera.scene");
scene_exe_shortcut("SceneExe_AutomaticMeshes", "Demos\\Bin\\Data\\Scenes\\AutomaticMeshes.scene");
scene_exe_shortcut("SceneExe_AutomaticTextures", "Demos\\Bin\\Data\\Scenes\\AutomaticTextures.scene");
scene_exe_shortcut("SceneExe_CameraMoveController", "Demos\\Bin\\Data\\Scenes\\CameraMoveController.scene");
scene_exe_shortcut("SceneExe_CharacterAnimation", "Demos\\Bin\\Data\\Scenes\\CharacterAnimation.scene");
scene_exe_shortcut("SceneExe_MoveController", "Demos\\Bin\\Data\\Scenes\\MoveController.scene");
scene_exe_shortcut("SceneExe_MultiCameras", "Demos\\Bin\\Data\\Scenes\\MultiCameras.scene");
scene_exe_shortcut("SceneExe_NormalMapping", "Demos\\Bin\\Data\\Scenes\\NormalMapping.scene");
scene_exe_shortcut("SceneExe_OrbiterCamera", "Demos\\Bin\\Data\\Scenes\\OrbiterCamera.scene");
scene_exe_shortcut("SceneExe_PhysicsCharacterController", "Demos\\Bin\\Data\\Scenes\\PhysicsCharacterController.scene");
scene_exe_shortcut("SceneExe_PhysicsFirstPersonController", "Demos\\Bin\\Data\\Scenes\\PhysicsFirstPersonController.scene");
scene_exe_shortcut("SceneExe_PhysicsJoints", "Demos\\Bin\\Data\\Scenes\\PhysicsJoints.scene");
scene_exe_shortcut("SceneExe_PhysicsManiacMarble", "Demos\\Bin\\Data\\Scenes\\PhysicsManiacMarble.scene");
scene_exe_shortcut("SceneExe_PhysicsMouseInteraction", "Demos\\Bin\\Data\\Scenes\\PhysicsMouseInteraction.scene");
scene_exe_shortcut("SceneExe_PLParticleGroups", "Demos\\Bin\\Data\\Scenes\\PLParticleGroups.scene");
scene_exe_shortcut("SceneExe_Mipmaps", "Demos\\Bin\\Data\\Scenes\\Mipmaps.scene");
scene_exe_shortcut("SceneExe_ReflectionCubeMap", "Demos\\Bin\\Data\\Scenes\\ReflectionCubeMap.scene");
scene_exe_shortcut("SceneExe_SceneNodeModifiers", "Demos\\Bin\\Data\\Scenes\\SceneNodeModifiers.scene");
