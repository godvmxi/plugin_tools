/*
 * base64.h
 *
 *  Created on: 2016-2-21
 *      Author: dan
 */

#ifndef __BASE64_H__
#define __BASE64_H__

int base64_decode( const char * base64, unsigned char * bindata );
char *base64_encode( const unsigned char * bindata, char * base64, int binlength );

#endif /* BASE64_H_ */
