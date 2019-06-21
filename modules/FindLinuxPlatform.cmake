# Detect Redhat or Debian platform
# The following variable will be set
# $PLATFORM		Debian	Redhat		none
# $DIST_NAME	 deb	rhel	fc	none
# $BIT_MODE		32|64

if (NOT WINDOWS)
	if (${CMAKE_SYSTEM_PROCESSOR} MATCHES i386|i586|i686)
		set(BIT_MODE "32")
	else ()
		set(BIT_MODE "64")
	endif ()

	if (EXISTS "/etc/debian_version")
		set(IS_DEBIAN ON)
	endif (EXISTS "/etc/debian_version")

	if (EXISTS "/etc/redhat-release")
		set(IS_REDHAT ON)
	endif (EXISTS "/etc/redhat-release")
endif (NOT WINDOWS)