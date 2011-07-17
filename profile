# This script can be used to set the path to the local (not installed)
# PixelLight runtime, which is stored in the environment variable
# PL_RUNTIME. If that variable is set, it will be preffered by the
# PixelLight runtime and used instead of searching for an installed
# runtime in /usr/ or /usr/local/.
# 
# Please note that this script must be 'sources' rather than invoked directly,
# in order to export the variables to the current shell. Also make sure that
# the current directory is the root directory of the PixelLight source
# tree, otherwise the path will be wrong.
#
# Execute this script:
#   source ./profile     (OR:)
#   . ./profile
export PL_RUNTIME="$PWD/Bin-Linux/Runtime"
echo "Setting PixelLight runtime variable:"
echo "  PL_RUNTIME = '$PL_RUNTIME'"
