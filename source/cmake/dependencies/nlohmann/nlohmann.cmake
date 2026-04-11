# https://json.nlohmann.me/integration/cmake/#supporting-both
#--------------------------------------------------------------------------
# Fetch Package
#--------------------------------------------------------------------------
FetchContent_Declare(json 
	URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz	)

FetchContent_MakeAvailable(json)	