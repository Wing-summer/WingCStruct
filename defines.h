/*==============================================================================
** Copyright (C) 2024-2027 WingSummer
**
** This program is free software: you can redistribute it and/or modify it under
** the terms of the GNU Affero General Public License as published by the Free
** Software Foundation, version 3.
**
** This program is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
** details.
**
** You should have received a copy of the GNU Affero General Public License
** along with this program. If not, see <https://www.gnu.org/licenses/>.
** =============================================================================
*/

#ifndef _COMMON_DEFINES_H_
#define _COMMON_DEFINES_H_

#include <QString>

/// @beief Struct for variable declaration
///
/// A variable declaration may contain 4 parts
/// (take this statement as example: char* argv[2]):
///    - data_type:     char
///    - var_name:      argv
///    - array_size:    2
///    - is_pointer:    true
/// @note Only one-demension array is supported here, but it's easy to extend
/// with this awareness
///
typedef struct {
    QString data_type;    ///< name of a data type, either basic type or
                          ///< user-defined type
    QString var_name;     ///< variable name
    qsizetype offset;     ///< member offset in struct: 0 for non-struct
    qsizetype array_size; ///< array size: 0 for non-array
    bool is_pointer;      ///< true when it's a pointer
    qsizetype var_size;   ///< size in bytes
} VariableDeclaration;

/// @enum type for token types
enum TokenTypes {
    kUnresolvedToken,

    // keywords
    kStructKeyword,
    kUnionKeyword,
    kEnumKeyword,
    kTypedefKeyword,

    kBasicDataType,
    kAbstractType,
    kComplexType,
    kQualifier,

    // user-defined tokens
    kStructName,
    kUnionName,
    kEnumName,

};

/// @enum type for sigle character tokens
enum SingleToken : char {
    kBlockStart = '{',
    kBlockEnd = '}',
    kPoundSign = '#',

    kComma = ',',
    kSemicolon = ';',
    kEqual = '=',
    kSlash = '/',
    kAsterisk = '*',
    kQuotation = '\"',
};

// definations under Windows

typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef float FLOAT;

typedef int INT;
typedef unsigned int UINT;

typedef unsigned long ULONG;
typedef unsigned short USHORT;
typedef unsigned char UCHAR;

using byte = unsigned char;

#endif // _COMMON_DEFINES_H_
