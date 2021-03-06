//
//  edn_objc.h
//  edn-objc
//
//  Created by Ben Mosher on 8/24/13.
//  Copyright (c) 2013 Ben Mosher. All rights reserved.
//

#import <Foundation/Foundation.h>

// thanks, http://nshipster.com/ns_enum-ns_options/
typedef NS_OPTIONS(NSUInteger, BMOEDNReadingOptions) {
    BMOEDNReadingMultipleObjects = (1UL << 0),
    // lazy parsing implies multiple objects
    BMOEDNReadingLazyParsing = (1UL << 1),
};

@interface BMOEDNSerialization : NSObject

#pragma mark - NSData reading methods

/**
 If BMOEDNReadingMultipleObjects is asserted, returned object
 is id<NSFastEnumeration>. Else, the first valid EDN object in
 the data is returned, or nil if no valid data.
 */
+(id)ednObjectWithData:(NSData *)data
               options:(BMOEDNReadingOptions)options
                 error:(NSError **)error;
/**
 @param transmogrifiers: a dictionary of ednSymbols to BMOEDNTransmogrifier
 blocks that turn the provided edn tagged element into some native object.
 */
+(id)ednObjectWithData:(NSData *)data
       transmogrifiers:(NSDictionary *)transmogrifiers
               options:(BMOEDNReadingOptions)options
                 error:(NSError **)error;

#pragma mark - NSInputStream reading methods

/**
 If BMOEDNReadingMultipleObjects is asserted, returned object
 is id<NSFastEnumeration>. Else, the first valid EDN object in
 the data is returned, or nil if no valid data.
 
 If lazy reading is not specified, this method may block until a full
 valid object is returned, the stream is closed, or an error is encountered.
 */
+(id)ednObjectWithStream:(NSInputStream *)data
                 options:(BMOEDNReadingOptions)options
                   error:(NSError **)error;
/**
 @param transmogrifiers: a dictionary of ednSymbols to BMOEDNTransmogrifier
 blocks that turn the provided edn tagged element into some native object.
 */
+(id)ednObjectWithStream:(NSInputStream *)data
         transmogrifiers:(NSDictionary *)transmogrifiers
                 options:(BMOEDNReadingOptions)options
                   error:(NSError **)error;

#pragma mark - NSData writing methods

+(NSData *)dataWithEdnObject:(id)obj error:(NSError **)error;
+(NSData *)dataWithEdnObject:(id)obj
             transmogrifiers:(NSDictionary *)transmogrifiers
                       error:(NSError **)error;

+(NSString *)stringWithEdnObject:(id)obj error:(NSError **)error;
+(NSString *)stringWithEdnObject:(id)obj
                 transmogrifiers:(NSDictionary *)transmogrifiers
                           error:(NSError **)error;

#pragma mark - NSStream writing methods

+(void)writeEdnObject:(id)obj
             toStream:(NSOutputStream *)stream
                error:(NSError **)error;

+(void)writeEdnObject:(id)obj
             toStream:(NSOutputStream *)stream
      transmogrifiers:(NSDictionary *)transmogrifiers
                error:(NSError **)error;
@end
