/*****************************************************************************
 * VLCMediaList.h: VLCKit.framework VLCMediaList header
 *****************************************************************************
 * Copyright (C) 2007 Pierre d'Herbemont
 * Copyright (C) 2015 Felix Paul Kühne
 * Copyright (C) 2007, 2015 VLC authors and VideoLAN
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License.
 *****************************************************************************/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Notifications

FOUNDATION_EXPORT NSNotificationName const VLCMediaListItemAddedNotification NS_SWIFT_NAME(VLCMediaList.itemAddedNotification);
FOUNDATION_EXPORT NSNotificationName const VLCMediaListItemDeletedNotification NS_SWIFT_NAME(VLCMediaList.itemDeletedNotification);
FOUNDATION_EXPORT NSNotificationName const VLCMediaListItemMovedNotification NS_SWIFT_NAME(VLCMediaList.itemMovedNotification);

@class VLCMedia;
@class VLCMediaList;

#pragma mark - Delegate Protocol

@protocol VLCMediaListDelegate <NSObject>
@optional
- (void)mediaList:(VLCMediaList *)aMediaList mediaAdded:(VLCMedia *)media atIndex:(NSUInteger)index;
- (void)mediaList:(VLCMediaList *)aMediaList mediaRemovedAtIndex:(NSUInteger)index;
- (void)mediaList:(VLCMediaList *)aMediaList mediaMoved:(VLCMedia *)media fromIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex;
@end

#pragma mark - VLCMediaList Interface

OBJC_VISIBLE
@interface VLCMediaList : NSObject

#pragma mark - Initialization

- (instancetype)initWithArray:(nullable NSArray<VLCMedia *> *)array NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;

#pragma mark - Thread Safety

- (void)lock;
- (void)unlock;

#pragma mark - Media Operations

- (NSUInteger)addMedia:(VLCMedia *)media;
- (void)insertMedia:(VLCMedia *)media atIndex:(NSUInteger)index;
- (BOOL)removeMediaAtIndex:(NSUInteger)index;
- (nullable VLCMedia *)mediaAtIndex:(NSUInteger)index;
- (NSUInteger)indexOfMedia:(VLCMedia *)media;

/// Move media from one index to another
- (BOOL)moveMediaAtIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex;

#pragma mark - Query & Properties

@property (readonly) NSInteger count;
@property (weak, nonatomic, nullable) id<VLCMediaListDelegate> delegate;
@property (readonly, getter=isReadOnly) BOOL readOnly;
@property (readonly, getter=isEmpty) BOOL empty;

#pragma mark - Convenience Methods

/// Returns all media objects as an NSArray (safe copy)
- (NSArray<VLCMedia *> *)allMedia;

/// Shuffle media list randomly
- (void)shuffle;

/// Sort media list with a comparator block
- (void)sortUsingComparator:(NSComparator)comparator;

/// Clear all media items
- (void)clear;

@end

NS_ASSUME_NONNULL_END
