/**
 * APICloud Modules
 * Copyright (c) 2014-2018 by APICloud, Inc. All Rights Reserved.
 * Licensed under the terms of the The MIT License (MIT).
 * Please see the license.html included with this distribution for details.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Photos/Photos.h>

@class PhotoStoreConfiguraion;

NS_ASSUME_NONNULL_BEGIN

NS_AVAILABLE_IOS(8_0) @interface PhotoStore : NSObject<PHPhotoLibraryChangeObserver>

/// @brief 配置类，用来设置相册的类
@property (nonatomic, strong, readonly)PhotoStoreConfiguraion * config;
@property (nonatomic,strong)NSString *opentype;

//构造方法
- (instancetype)initWithConfiguration:(PhotoStoreConfiguraion *)configuration;
+ (instancetype)storeWithConfiguration:(PhotoStoreConfiguraion *)configuration;


/// 获取photos提供的所有的智能分类相册组
- (void)fetchAlbumRegularGroups:(void(^)(NSArray <PHAssetCollection *> *))complete;
/// 获取的将'胶卷相册'放在第一位
//- (void)fetchAlbumRegularGroupsByUserLibrary:(void(^)(NSArray <PHAssetCollection *> *))complete;

/// 权限检测
+ (void)authorizationStatusAllow:(void(^)(void))allowHander denied:(void(^)(void))deniedHander;
/// 权限通过进行的handler
+ (void)handlerWithAuthorizationAllow:(void(^)(void))hander;
#pragma mark - 相册组

/** 获取photos提供的所有的智能分类相册组，与config属性无关 */
- (void)fetchPhotosGroup:(void(^)(NSArray <PHAssetCollection *> *)) groups;


/**
 *  根据photos提供的智能分类相册组
 *  根据config中的groupNamesConfig属性进行筛别
 */
//- (void)fetchDefaultPhotosGroup:(void(^)(NSArray <PHAssetCollection *> *)) groups;


/**
 *  根据photos提供的智能分类相册组
 *  根据config中的groupNamesConfig属性进行筛别 并添加上其他在手机中创建的相册
 */
- (void)fetchDefaultAllPhotosGroup:(void(^)(NSArray <PHAssetCollection *> * , PHFetchResult *)) groups;


#pragma mark - 处理相册的方法
/**
 获取某个相册的所有照片的简便方法

 */
+ (PHFetchResult *)fetchPhotos:(PHAssetCollection *)group;

#pragma mark - 发生变化的Block

/// @brief 相册发生变化进行的回调block - 目前还未想到如何实现 = =
@property (nullable, nonatomic, copy)void(^photoStoreHasChanged)(PHChange * changeInstance);


@end








NS_CLASS_DEPRECATED_IOS(8_0, 10_0,"Use PhotoRequestStore instead. see PhotoRequestStore.h") @interface YPPhotoStoreHandleClass : NSObject

/// 根据size以及图片状态获取资源转化后的图片对象数组
+ (void)imagesWithAssets:(NSArray <PHAsset *> *)assets status:(NSArray <NSNumber *> *)status Size:(CGSize)size complete:(void (^)(NSArray <UIImage *> *))imagesBlock __deprecated_msg("Use PhotoRequestStore instead. see PhotoRequestStore.h");


/// 根据资源以及状态获取资源转化后的data
+ (void)dataWithAssets:(NSArray <PHAsset *> *)assets status:(NSArray <NSNumber *> *)status complete:(void (^)(NSArray <NSData *> *))dataBlock __deprecated_msg("Use PhotoRequestStore instead. see PhotoRequestStore.h");

@end









/// 操作相册组类目
@interface PhotoStore (Group)

/// 新增一个title的相册
- (void)addCustomGroupWithTitle:(NSString *)title completionHandler:(void(^)(void)) successBlock failture:(void(^)(NSString * error)) failtureBlock;


/// 新增一个title的相册，并添加资源对象
- (void)addCustomGroupWithTitle:(NSString *)title assets:(NSArray <PHAsset *> *)assets completionHandler:(void (^)(void))successBlock failture:(void (^)(NSString *))failtureBlock;


/// 检测是否存在同名相册,如果存在返回第一个同名相册
- (void)checkGroupExist:(NSString *)title result:(void(^)(BOOL isExist,PHAssetCollection * __nullable)) resultBlock;

@end









/// 操作资源对象类目
@interface PhotoStore (Asset)

/// 将图片对象写入对应相册
- (void)addCustomAsset:(UIImage *)image collection:(PHAssetCollection *)collection completionHandler:(void(^)(void)) successBlock failture:(void(^)(NSString * error)) failtureBlock;


/// 将图片路径写入对应相册
- (void)addCustomAssetPath:(NSString *)imagePath collection:(PHAssetCollection *)collection completionHandler:(void(^)(void)) successBlock failture:(void(^)(NSString * error)) failtureBlock;

@end












@interface PhotoStore (NSDeprecated)

/** 获取某个相册的所有照片的简便方法 */
- (PHFetchResult *)fetchPhotos:(PHAssetCollection *)group __deprecated_msg("Use +fetchPhotos: instead.");

@end


NS_ASSUME_NONNULL_END

