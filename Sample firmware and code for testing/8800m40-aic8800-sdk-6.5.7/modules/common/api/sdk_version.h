/**
 ****************************************************************************************
 *
 * @file sdk_version.h
 *
 * @brief Definition of version macros.
 *
 * This file should be included if any version related macro is needed.
 * It is modified automatically by build tool, and should seldom be
 * touched manually.
 *
 ****************************************************************************************
 */
#ifndef _SDK_VERSION_H_
#define _SDK_VERSION_H_

/**
 ****************************************************************************************
 * @addtogroup SDK
 * @brief Versioning
 * @{
 ****************************************************************************************
 */

// Version has the form Major.minor.release.patch
// The version string is "vMM.mm.rr.pp"
// Each number should fit in a 8 bits unsigned (0 to 255)
/// Major version number
#define SDK_VERSION_MAJ     6
/// Minor version number
#define SDK_VERSION_MIN     5
/// Release number
#define SDK_VERSION_REL     7
/// Patch number
#define SDK_VERSION_PAT     4

/// Version word
#define SDK_VERSION        ((SDK_VERSION_MAJ << 24) | (SDK_VERSION_MIN << 16) |             \
                           (SDK_VERSION_REL << 8) | SDK_VERSION_PAT)

/// Version string (global variable defined in co_version.c)
extern const char sdk_version_str[];
/// Macro for previous variable. Do not use!
#define SDK_VERSION_STR     "v6.5.7.4"

/// Macro for git revsion & build command
#define GIT_VERSION_STR     XNSTR(CFG_CUR_GIT_REV)
#define BUILD_COMMAND_STR   XNSTR(CFG_BUILD_CMD)

/// Date at which the sdk is built (defined in co_version.c)
extern const char sdk_build_date[];

/// Command at which the sdk is built (defined in co_version.c)
extern const char sdk_build_cmd[];

/// Date at which the system is built (defined in build_version.c)
extern const char usr_build_date[];

/// @}

#endif // _SDK_VERSION_H_
