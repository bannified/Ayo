#pragma once

// General
#include <memory>
#include <utility>
#include <functional>
#include <stdlib.h>

// I/O
#include <iostream>
#include <ostream>
#include <fstream>
#include <stdio.h>
#include <filesystem>

// String
#include <sstream>
#include <string>

// data structures
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>

// Self
#include "Ayo/Log.h"

#ifdef AYO_PLATFORM_WINDOWS 
	#include <Windows.h>

	#ifdef _WIN32
	// networking
	#else
	/* Assuming POSIX */
	// networking
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
	#endif
#endif