#ifndef PRECOMP_H
#define PRECOMP_H

#ifdef _DEBUG
#define _DPF
#define _DPF_COM
#endif

#pragma warning( disable : 4035 )
#pragma warning( disable : 4068 )

#pragma comment( lib, "advapi32.lib" )

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string.h>
#include <search.h>
#include <windows.h>
#if _MSC_VER > 1200
#include <iostream>
#endif
#include <algorithm>
#include <string>
#include <vector>
#include "trie.h"
#include "..\nvidia\nvdpf.h"
#include "aspera.h"

#endif
