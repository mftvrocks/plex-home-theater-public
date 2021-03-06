//
//  PlexAutoUpdateMac.mm
//  Plex
//
//  Created by Tobias Hieta <tobias@plexapp.com> on 2012-10-22.
//  Copyright 2012 Plex Inc. All rights reserved.
//

#define BOOL XBMC_BOOL
#include "PlexAutoUpdateMac.h"
#undef BOOL

#import <Foundation/Foundation.h>

#import <CoreServices/CoreServices.h>
#import <Security/Security.h>
#import <AppKit/NSApplication.h>

bool
CPlexAutoUpdateInstallerMac::InstallUpdate(const std::string &file, std::string& unpackPath)
{
  @autoreleasepool
  {
    NSString *fileUrl = [NSString stringWithUTF8String:file.c_str()];
    [[NSWorkspace sharedWorkspace] selectFile:fileUrl inFileViewerRootedAtPath:nil];  
  }

  m_functions->TerminateApplication();
  
  return true;
}
