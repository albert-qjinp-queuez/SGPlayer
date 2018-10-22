//
//  SGSession.h
//  SGPlayer
//
//  Created by Single on 2018/1/16.
//  Copyright © 2018年 single. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SGSessionConfiguration.h"
#import "SGDefines.h"

typedef NS_ENUM(NSUInteger, SGSessionState)
{
    SGSessionStateNone,
    SGSessionStateOpening,
    SGSessionStateOpened,
    SGSessionStateReading,
    SGSessionStateClosed,
    SGSessionStateFinished,
    SGSessionStateFailed,
};

@class SGSession;

@protocol SGSessionDelegate <NSObject>

- (void)sessionDidChangeState:(SGSession *)session;
- (void)sessionDidChangeCapacity:(SGSession *)session;

@end

@interface SGSession : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithConfiguration:(SGSessionConfiguration *)configuration;

@property (nonatomic, weak) id <SGSessionDelegate> delegate;

@property (nonatomic, assign, readonly) SGSessionState state;
@property (nonatomic, assign, readonly) CMTime duration;
@property (nonatomic, copy, readonly) NSError * error;
@property (nonatomic, copy, readonly) NSDictionary * metadata;

- (BOOL)empty;
- (BOOL)emptyWithMainMediaType:(SGMediaType)mainMediaType;

- (CMTime)loadedDuration;       // Main media type is Audio.
- (CMTime)loadedDurationWithMainMediaType:(SGMediaType)mainMediaType;

- (long long)loadedSize;        // Main media type is Audio.
- (long long)loadedSizeWithMainMediaType:(SGMediaType)mainMediaType;

/**
 *  Audio.
 */
@property (nonatomic, assign, readonly) BOOL audioEnable;
@property (nonatomic, assign, readonly) BOOL audioEmpty;
@property (nonatomic, assign, readonly) CMTime audioLoadedDuration;
@property (nonatomic, assign, readonly) long long audioLoadedSize;

/**
 *  Video.
 */
@property (nonatomic, assign, readonly) BOOL videoEnable;
@property (nonatomic, assign, readonly) BOOL videoEmpty;
@property (nonatomic, assign, readonly) CMTime videoLoadedDuration;
@property (nonatomic, assign, readonly) long long videoLoadedSize;

/**
 *  Streams.
 */
- (void)open;
- (void)start;
- (void)close;

/**
 *  Seek.
 */
- (BOOL)seeking;
- (BOOL)seekable;
- (BOOL)seekToTime:(CMTime)time completionHandler:(void(^)(CMTime time, NSError * error))completionHandler;

@end
