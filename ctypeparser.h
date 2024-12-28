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

#ifndef _CTYPE_PARSER_H_
#define _CTYPE_PARSER_H_

#include <QFile>
#include <QHash>
#include <QList>
#include <QPair> // QPair
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "defines.h"

class CTypeParser {
public:
    explicit CTypeParser();
    virtual ~CTypeParser();

public:
    void parseFiles();

    void setIncludePaths(const QStringList &paths);
    QStringList includePaths() const;

    void dumpTypeDefs() const;

    qsizetype padAlignment() const;
    void setPadAlignment(qsizetype newKAlignment);

    QHash<QString, QList<VariableDeclaration>> structDefs() const;

    QHash<QString, QList<QPair<QString, int>>> enumDefs() const;

    QHash<QString, long> constDefs() const;

    QHash<QString, QList<VariableDeclaration>> unionDefs() const;

private:
    void parseFile(const QString &file);
    void parseSource(const QString &src);

    QString mergeAllLines(const QStringList &lines) const;
    bool getNextToken(QString src, qsizetype &pos, QString &token,
                      bool cross_line = true) const;
    bool getNextLine(QString src, qsizetype &pos, QString &line) const;
    bool getRestLine(const QString &src, qsizetype &pos, QString &line) const;
    void skipCurrentLine(const QString &src, qsizetype &pos,
                         QString &line) const;
    qsizetype splitLineIntoTokens(QString line, QStringList &tokens) const;

    bool parseDeclaration(const QString &line, VariableDeclaration &decl) const;
    bool parseEnumDeclaration(const QString &line, int &last_value,
                              QPair<QString, int> &decl,
                              bool &is_last_member) const;
    bool parseAssignExpression(const QString &line);

    void parsePreProcDirective(const QString &src, qsizetype &pos);
    bool parseStructUnion(const bool is_struct, const bool is_typedef,
                          const QString &src, qsizetype &pos,
                          VariableDeclaration &var_decl, bool &is_decl);
    bool parseEnum(const bool is_typedef, const QString &src, qsizetype &pos,
                   VariableDeclaration &var_decl, bool &is_decl);

    VariableDeclaration makePadField(const qsizetype size) const;
    qsizetype padStructMembers(QList<VariableDeclaration> &members);
    qsizetype calcUnionSize(const QList<VariableDeclaration> &members) const;

    void storeStructUnionDef(const bool is_struct, const QString &type_name,
                             QList<VariableDeclaration> &members);

private:
    /// read in basic data such as keywords/qualifiers, and basic data type
    /// sizes
    void initialize();

    void findHeaderFiles(const QString &path);
    QString getFile(QString &filename) const;

    // pre-processing
    QString preprocess(QFile &ifs) const;
    void stripComments(QStringList &lines) const;
    void wrapLines(QStringList &lines) const;

    // utility functions
    QString getNextToken(const QString &line, qsizetype &pos) const;
    bool isIgnorable(const QString &token) const;
    TokenTypes getTokenType(const QString &token) const;
    bool isNumericToken(const QString &token, long &number) const;
    int getTypeSize(const QString &data_type) const;

    /// class members
private:
    static const char EOL =
        '$'; ///< end of line, used to delimit the source lines within a string

    qsizetype kAlignment_ = 4; ///< alignment
    static const qsizetype kWordSize_ =
        4; ///< size of a machine word on a 32-bit system

    static const QString kAnonymousTypePrefix;
    static const QRegularExpression kTokenDelimiters;
    static const QString kPaddingFieldName;

private:
    /// external input
    QStringList include_paths_;

    QStringList qualifiers_;
    QHash<QString, TokenTypes> keywords_;

    /// header files to parse
    /// key     - filename with relative/absolute path
    /// bool    - whether the file is parsed
    QHash<QString, bool> header_files_;

    /// Size of C data types and also user-defined struct/union types
    /// @note All enum types have fixed size, so they're not stored
    QHash<QString, qsizetype> type_sizes_;

    /// Parsing result - extracted type definitions
    /// for below 3 maps:
    /// key     - type name
    /// value   - type members

    /// struct definitions
    QHash<QString, QList<VariableDeclaration>> struct_defs_;

    /// union definitions
    QHash<QString, QList<VariableDeclaration>> union_defs_;

    /// enum definitions
    QHash<QString, QList<QPair<QString, int>>> enum_defs_;

    /// constants and macros that have integer values
    /// key     - constant/macro name
    /// value   - an integer (all types of number are cast to long type for
    /// convenience)
    QHash<QString, long> const_defs_;
};

#endif // _TYPE_PARSER_H_
