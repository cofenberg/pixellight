##################################################
## Execute hhc.exe and ignore error code
##################################################
execute_process(
  COMMAND ${HTML_HELP_COMPILER} ${SRC}
  WORKING_DIRECTORY ${DIR}
)
