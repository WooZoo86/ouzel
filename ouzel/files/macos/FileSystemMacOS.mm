// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include <Foundation/Foundation.h>
#include "FileSystemMacOS.hpp"
#include "utils/Log.hpp"

extern std::string DEVELOPER_NAME;
extern std::string APPLICATION_NAME;

namespace ouzel
{
    FileSystemMacOS::FileSystemMacOS()
    {
        NSBundle* bundle = [NSBundle mainBundle];
        NSString* path = [bundle resourcePath];

        appPath = [path UTF8String];
    }

    std::string FileSystemMacOS::getStorageDirectory(bool user) const
    {
        NSFileManager* fileManager = [NSFileManager defaultManager];

        NSError* error;
        NSURL* applicationSupportDirectory = [fileManager URLForDirectory:NSApplicationSupportDirectory inDomain:user ? NSUserDomainMask : NSLocalDomainMask appropriateForURL:nil create:YES error:&error];

        if (!applicationSupportDirectory)
        {
            Log(Log::Level::ERR) << "Failed to get application support directory";
            return "";
        }

        NSString* identifier = [[NSBundle mainBundle] bundleIdentifier];

        if (!identifier)
        {
            identifier = [NSString stringWithFormat:@"%s.%s", DEVELOPER_NAME.c_str(), APPLICATION_NAME.c_str()];
        }

        NSURL* path = [applicationSupportDirectory URLByAppendingPathComponent:identifier];

        [fileManager createDirectoryAtURL:path withIntermediateDirectories:YES attributes:nil error:nil];

        return [[path path] UTF8String];
    }

    std::string FileSystemMacOS::getTempDirectory() const
    {
        NSString* temporaryDirectory = NSTemporaryDirectory();
        return [temporaryDirectory UTF8String];
    }
}
