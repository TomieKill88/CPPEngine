# From https://www.fontspace.com/category/ttf?p=2
#--------------------------------------------------------------------------
# Resources
#--------------------------------------------------------------------------
list(APPEND resources  #sources
						AovelSans.ttf)

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(FILES ${resources}
		DESTINATION ${INSTALL_BINDIR}/resources
)

