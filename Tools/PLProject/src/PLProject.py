#!/usr/bin/python


# [TODO] Add verbose command line option
# [TODO] Write the current PixelLight version into the XML plugin file
# [TODO] Change "PLProject V1.0 (Python)" into "PLProject <PixelLight version> (Python)" (e.g. "PLProject PixelLight 0.9.9-R1 (Python)")
# [TODO] Add "Delayed" option within the resulting XML plugin file (currently always set to "0")
# [TODO] Add RTTI class metadata within the resulting XML plugin file


import sys
import os
#import io
import getopt
import re
import glob

# Setup regular expressions
reModule			= re.compile(r"^\s*pl_module\(\s*\"(?P<name>\w*)\"\s*\)\s*$")
reModulePlugin		= re.compile(r"^\s*pl_module_plugin\(\s*\"(?P<name>\w*)\"\s*\)\s*$")
reVendor			= re.compile(r"^\s*pl_module_vendor\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reLicense			= re.compile(r"^\s*pl_module_license\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDescription		= re.compile(r"^\s*pl_module_description\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reVersion			= re.compile(r"^\s*pl_module_version\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDepsWin32Release	= re.compile(r"^\s*pl_module_dependencies_win32_release\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDepsWin32Debug	= re.compile(r"^\s*pl_module_dependencies_win32_debug\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDepsWin64Release	= re.compile(r"^\s*pl_module_dependencies_win64_release\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDepsWin64Debug	= re.compile(r"^\s*pl_module_dependencies_win64_debug\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDepsLinuxRelease	= re.compile(r"^\s*pl_module_dependencies_linux_release\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reDepsLinuxDebug	= re.compile(r"^\s*pl_module_dependencies_linux_debug\s*\(\s*(?P<text>\".*\")\s*\)\s*$", re.IGNORECASE)
reActive			= re.compile(r"^\s*pl_module_active\s*\((?P<num>\d)\)\s*$")

# Project data type
class Project(object):
	def __init__(self):
		self.path				= ""
		self.name				= ""
		self.suffix				= ""
		self.moduleName			= ""
		self.moduleVersion		= ""
		self.moduleVendor		= ""
		self.moduleLicense		= ""
		self.moduleDescription	= ""
		self.modulePlugin		= False
		self.moduleActive		= False
		self.libWin32Release	= ""
		self.libWin32Debug		= ""
		self.libWin64Release	= ""
		self.libWin64Debug		= ""
		self.libLinuxRelease	= ""
		self.libLinuxDebug		= ""
		self.dependWin32Release = ""
		self.dependWin32Debug	= ""
		self.dependWin64Release = ""
		self.dependWin64Debug	= ""
		self.dependLinuxRelease = ""
		self.dependLinuxDebug	= ""
		self.mainSrc			= ""
		self.sourcePath			= ""
		self.includePath		= ""
		self.outputPath			= ""
		self.outputPlugin		= ""

# Print debug message (debug mode)
def PrintDebug(message):
	global debug
	if debug:
		print(message)
	return
	
# Print a list (debug mode)
def PrintList(list, prefix):
	global debug
	if debug:
		for item in list:
			print(prefix + "'" + item + "'")
	return

# Find files
def Find(path, pattern, recursive):
	# Find files
	if recursive:
		filenames = glob.glob(path + '/*/' + pattern)
	else:
		filenames = glob.glob(path + '/' + pattern)

	# Return files
	return filenames

# Get quoted string
def GetQuotedString(text):
	result = ""
	if text[0] == '"' and text[-1] == '"':
		result = text[1:-1]
	return result

# Get boolean is string
def BoolToString(bool):
	if bool:
		return "1"
	else:
		return "0"

# Parse all files of a project
def ParseFile(project, files):
	return True

# Parse module definition
def ParseModule(project):
	# Parse main source file
	mainSrc = project.mainSrc
	print("Parsing main source file at '" + mainSrc + "'")

	# Open file
	try:                                
		file = open(mainSrc)
	except getopt.GetoptError:
		print("ERROR: Could not open file '" + mainSrc + "'!")
		return False

	# Parse file
	for line in file:
		# [DEBUG]
		PrintDebug(line)

		# Check for pl_module
		match = reModule.match(line)
		if match:
			project.moduleName   = match.group("name")
			project.modulePlugin = False
			print("Module name = '" + project.moduleName + "'")

		# Check for pl_module_plugin
		match = reModulePlugin.match(line)
		if match:
			project.moduleName   = match.group("name")
			project.modulePlugin = True
			print("Module name = '" + project.moduleName + "'")
			print("This module is a plugin")

		# Check for pl_module_vendor
		match = reVendor.match(line)
		if match:
			project.moduleVendor = GetQuotedString(match.group("text"))
			print("Vendor name = '" + project.moduleVendor + "'")

		# Check for pl_module_license
		match = reLicense.match(line)
		if match:
			project.moduleLicense = GetQuotedString(match.group("text"))
			print("License = '" + project.moduleLicense + "'")

		# Check for pl_module_description
		match = reDescription.match(line)
		if match:
			project.moduleDescription = GetQuotedString(match.group("text"))
			print("Description = '" + project.moduleDescription + "'")

		# Check for pl_module_version
		match = reVersion.match(line)
		if match:
			project.moduleVersion = GetQuotedString(match.group("text"))
			print("Version = '" + project.moduleVersion + "'")

		# Check for pl_module_dependencies_win32_release
		match = reDepsWin32Release.match(line)
		if match:
			project.dependWin32Release = GetQuotedString(match.group("text"))
			print("Win32 release dependencies = '" + project.dependWin32Release + "'")

		# Check for pl_module_dependencies_win32_debug
		match = reDepsWin32Debug.match(line)
		if match:
			project.dependWin32Debug = GetQuotedString(match.group("text"))
			print("Win32 debug dependencies = '" + project.dependWin32Debug + "'")

		# Check for pl_module_dependencies_win64_release
		match = reDepsWin64Release.match(line)
		if match:
			project.dependWin64Release = GetQuotedString(match.group("text"))
			print("Win64 release dependencies = '" + project.dependWin64Release + "'")

		# Check for pl_module_dependencies_win64_debug
		match = reDepsWin64Debug.match(line)
		if match:
			project.dependWin64Debug = GetQuotedString(match.group("text"))
			print("Win64 debug dependencies = '" + project.dependWin64Debug + "'")

		# Check for pl_module_dependencies_linux_release
		match = reDepsLinuxRelease.match(line)
		if match:
			project.dependLinuxRelease = GetQuotedString(match.group("text"))
			print("Linux release dependencies = '" + project.dependLinuxRelease + "'")

		# Check for pl_module_dependencies_linux_debug
		match = reDepsLinuxDebug.match(line)
		if match:
			project.dependLinuxDebug = GetQuotedString(match.group("text"))
			print("Linux debug dependencies = '" + project.dependLinuxDebug + "'")

		# Check for pl_module_active
		match = reActive.match(line)
		if match:
			active = match.group("num")
			project.moduleActive = (active == "1")
			if project.moduleActive:
				print("Active = 'yes'")
			else:
				print("Active = 'no'")

	# Close file
	file.close()

	# Compose library names
	if project.modulePlugin:
		# Compose file names
		project.libWin32Release	= project.name + project.suffix + ".dll"
		project.libWin32Debug	= project.name + project.suffix + "D.dll"
		project.libWin64Release	= project.name + project.suffix + "64.dll"
		project.libWin64Debug	= project.name + project.suffix + "D64.dll"
		project.libLinuxRelease	= "lib" + project.name + project.suffix + ".so"
		project.libLinuxDebug	= "lib" + project.name + project.suffix + "D.so"

		# Output file names
		print("Win32 release library = '" + project.libWin32Release)
		print("Win32 debug   library = '" + project.libWin32Debug)
		print("Win64 release library = '" + project.libWin64Release)
		print("Win64 debug   library = '" + project.libWin64Debug)
		print("Linux release library = '" + project.libLinuxRelease)
		print("Linux debug   library = '" + project.libLinuxDebug)

	# Done
	return True

# Parse a project source tree
def ParseProject(project):
	# Parse project
	path = project.path
	print("Parsing project at '" + path + "'")

	# Find VC projects
	print("Looking for project files")
	projects = Find(path, "*.vcxproj", False)
	PrintList(projects, "found ")

	# Find out name of project
	name = ""
	for filename in projects:
		# [DEBUG]
		PrintDebug("Project '" + filename + "'")

		# Check file
		if filename.find("Stat") > -1:
			# Ignore static libs
			PrintDebug("This is a static lib version, ignoring ...")
		elif filename.find("Internal") > -1:
			# Ignore internal projects
			PrintDebug("This is an internal project file, ignoring ...")
		else:
			# Cut extension (.vcxproj)
			fpath, fname = os.path.split(filename)
			name, fext = os.path.splitext(fname)
			PrintDebug("Taking '" + name + "' as project name")

	# Recognize suffix
	if project.suffix != "":
		print("Using project suffix '" + project.suffix + "'")

	# Check if a project name has been found
	if name != "":
		print("Found project '" + name + "'")
		project.name = name
	else:
		print("ERROR: Could not determine project name!")
		return False

	# Find main source file
	mainSrc = path + "/src/" + name + ".cpp"
	if os.path.exists(mainSrc):
		print("Found main source file '" + mainSrc + "'")
		project.mainSrc = mainSrc
	else:
		print("ERROR: Could not determine main source file! " + mainSrc)
		return False

	# Parse module file
	if not ParseModule(project):
		# Error parsing module file
		return False

	# Find source files
	sourcePath = path + "/src"
	if os.path.exists(sourcePath) and os.path.isdir(sourcePath):
		print("Found source files at '" + sourcePath + "'")
		project.sourcePath = sourcePath
	else:
		print("ERROR: Could not find source files in '" + sourcePath + "' - ")
		if not os.path.exists(sourcePath):
			print("ERROR: " "File does not exist!")
		else:
			print("ERROR: " "File is not a directory!")
		return False

	# Find include files
	includePath = path + "/include"
	if os.path.exists(includePath) and os.path.isdir(includePath):
		print("Found include files at '" + includePath + "'")
	else:
		print("Could not find include files, taking '" + sourcePath + "'")
		project.includePath = sourcePath

	# Add all source, header and inline files
	files = Find(sourcePath, "*.cpp", True)
	files = files + Find(includePath, "*.h", True)
	files = files + Find(includePath, "*.inl", True)
	PrintList(files, "- Found file ")

	# And now, parse all these files :-)
	if not ParseFile(project, files):
		# Error parsing files
		return False

	# Done
	return True

# Create plugin file for a project
def CreatePluginFile(project):
	# Compose output filename
	project.outputPlugin = project.outputPath + "/" + project.name + project.suffix + ".plugin"
	print("Writing plugin file '" + project.outputPlugin + "'")

	# Open plugin file
#	if (cFile.Open(File::FileCreate | File::FileWrite | File::FileText)) {
	try:                                
		file = open(project.outputPlugin, 'w')
	except getopt.GetoptError:
		# Could not open file
		print("ERROR: Could not write to file '" + project.outputPlugin + "'!")
		return False

	# Write plugin file
	file.write(u"<?xml version=\"1.0\" ?>\n")
	file.write(u"<Plugin Version=\"1\">\n")
	file.write(u"\t<Active>" + BoolToString(project.moduleActive) + "</Active>\n")
	file.write(u"\t<Delayed>0</Delayed>\n")
	file.write(u"\t<Name>" + project.moduleName + "</Name>\n")
	file.write(u"\t<Version>" + project.moduleVersion + "</Version>\n")

	# Vendor
	if project.moduleVendor != "":
		file.write(u"\t<Vendor>" + project.moduleVendor + "</Vendor>\n")

	# License
	if project.moduleLicense != "":
		file.write(u"\t<License>" + project.moduleLicense + "</License>\n")

	# Description
	if project.moduleDescription != "":
		file.write(u"\t<Description>" + project.moduleDescription + "</Description>\n")

	# Platform: Win32
	file.write(u"\t<Platform Name=\"Win32\">\n")

	# Library: Release
	if project.dependWin32Release != "":
		file.write(u"\t\t<Library Type=\"Release\" Dependency=\"" + project.dependWin32Release + "\">" + project.libWin32Release + "</Library>\n")
	else:
		file.write(u"\t\t<Library Type=\"Release\">" + project.libWin32Release + "</Library>\n")

	# Library: Debug
	if project.dependWin32Debug != "":
		file.write(u"\t\t<Library Type=\"Debug\" Dependency=\"" + project.dependWin32Debug + "\">" + project.libWin32Debug + "</Library>\n")
	else:
		file.write(u"\t\t<Library Type=\"Debug\">" + project.libWin32Debug + "</Library>\n")

	# Platform end tag
	file.write(u"\t</Platform>\n")

	# Platform: Win64
	file.write(u"\t<Platform Name=\"Win64\">\n")

	# Library: Release
	if project.dependWin64Release != "":
		file.write(u"\t\t<Library Type=\"Release\" Dependency=\"" + project.dependWin64Release + "\">" + project.libWin64Release + "</Library>\n")
	else:
		file.write(u"\t\t<Library Type=\"Release\">" + project.libWin64Release + "</Library>\n")

	# Library: Debug
	if project.dependWin64Debug != "":
		file.write(u"\t\t<Library Type=\"Debug\" Dependency=\"" + project.dependWin64Debug + "\">" + project.libWin64Debug + "</Library>\n")
	else:
		file.write(u"\t\t<Library Type=\"Debug\">" + project.libWin64Debug + "</Library>\n")

	# Platform end tag
	file.write(u"\t</Platform>\n")

	# Platform: Linux
	file.write(u"\t<Platform Name=\"Linux\">\n")

	# Library: Release
	if project.dependLinuxRelease != "":
		file.write(u"\t\t<Library Type=\"Release\" Dependency=\"" + project.dependLinuxRelease + "\">" + project.libLinuxRelease + "</Library>\n")
	else:
		file.write(u"\t\t<Library Type=\"Release\">" + project.libLinuxRelease + "</Library>\n")

	# Library: Debug
	if project.dependLinuxDebug != "":
		file.write(u"\t\t<Library Type=\"Debug\" Dependency=\"" + project.dependLinuxDebug + "\">" + project.libLinuxDebug + "</Library>\n")
	else:
		file.write(u"\t\t<Library Type=\"Debug\">" + project.libLinuxDebug + "</Library>\n")

	# Platform end tag
	file.write(u"\t</Platform>\n")

	# Plugin end tag
	file.write(u"</Plugin>\n")

	# Done
	file.close()
	return True


# Print help
def help():
	print("Usage:")
	print("  PLProject <path> [--write-plugin] [--output-path <filename>] [--suffix <suffix>] [--debug]")
	return

# Main function
def main(argv):
	# Init
	global debug
	debug = False

	# Output startup info
	print("PLProject V1.0 (Python)")
	print("Current dir is '" + os.getcwd() + "'")

	# Parse command line
	path		 = argv[0]
	output_path	 = "."
	suffix		 = ""
	write_plugin = False
	try:                                
		opts, args = getopt.getopt(argv[1:], "hds:o:w", ["help", "debug", "suffix=", "output-path=", "write-plugin"])
		for opt, arg in opts:
			if opt in ("-h", "--help"):
				help()
				sys.exit()
			elif opt in ("-d", "--debug"):
				debug = True
			elif opt in ("-w", "--write-plugin"):
				write_plugin = True
			elif opt in ("-s", "--suffix"):
				suffix = arg
			elif opt in ("-o", "--output-path"):
				if arg[-1] == '\\' or arg[-1] == '/':
					output_path = arg[:-1]
				else:
					output_path = arg

	except getopt.GetoptError:
		help()
		sys.exit(2)                     

	# Parse project
	project = Project()
	project.path		 = path
	project.suffix		 = suffix
	project.modulePlugin = False
	project.moduleActive = True
	if ParseProject(project):
		# Write plugin file
		if write_plugin:
			project.outputPath = output_path
			if not CreatePluginFile(project):
				print("Could not write out plugin file!")
				sys.exit(1)
	else:
		print("Could not parse project!")
		sys.exit(1)
	return

# Call main
main(sys.argv[1:])
