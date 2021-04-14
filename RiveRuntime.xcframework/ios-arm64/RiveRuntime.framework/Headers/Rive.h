//
//  RiveFile.h
//  RiveRuntime
//
//  Created by Matt Sullivan on 8/30/20.
//  Copyright © 2020 Rive. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

// Different fits for rendering a Rive animation in a View
typedef NS_ENUM(NSInteger, Fit) {
    Fill,
    Contain,
    Cover,
    FitHeight,
    FitWidth,
    ScaleDown,
    None
};

// Different alignments for rendering a Rive animation in a View
typedef NS_ENUM(NSInteger, Alignment) {
    TopLeft,
    TopCenter,
    TopRight,
    CenterLeft,
    Center,
    CenterRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

// Result of file importing
typedef NS_ENUM(NSInteger, ImportResult) {
    success,
    unsupportedVersion,
    malformed
};

@class RiveArtboard;
@class RiveLinearAnimation;

// Linear animation instance wrapper
@interface RiveLinearAnimationInstance : NSObject

-(float) time;
-(void) setTime:(float) time;
-(RiveLinearAnimation *) animation;
-(void) applyTo:(RiveArtboard*) artboard;
-(void) advanceBy:(double)elapsedSeconds;

@end

// Linear animation wrapper
@interface RiveLinearAnimation : NSObject

-(NSString *) name;
-(RiveLinearAnimationInstance *) instance;
-(NSInteger) workStart;
-(NSInteger) workEnd;
-(NSInteger) duration;
-(NSInteger) fps;
-(void) apply:(float) time to:(RiveArtboard *) artboard;

@end

// Render wrapper
@interface RiveRenderer : NSObject

-(instancetype) initWithContext:(nonnull CGContextRef) context;
-(void) alignWithRect:(CGRect)rect withContentRect:(CGRect)contentRect withAlignment:(Alignment)alignment withFit:(Fit)fit;

@end

// Artboard wrapper
@interface RiveArtboard : NSObject

-(NSString *) name;
-(CGRect) bounds;
-(NSInteger) animationCount;
-(RiveLinearAnimation *) animationAt:(NSInteger)index;
-(void) advanceBy:(double)elapsedSeconds;
-(void) draw:(RiveRenderer *)renderer;

@end

// File wrapper
@interface RiveFile : NSObject

@property (class, readonly) uint majorVersion;
@property (class, readonly) uint minorVersion;

-(nullable instancetype) initWithBytes:(UInt8 *)bytes byteLength:(UInt64)length;

// Wraps: Artboard* artboard() const;
-(RiveArtboard *) artboard;
@end

NS_ASSUME_NONNULL_END
