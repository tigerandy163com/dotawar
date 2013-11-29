//
//  MyXMLParser.h
//  三国war
//
//  Created by chunyu.wang on 13-11-28.
//
//

#ifndef ____war__MyXMLParser__
#define ____war__MyXMLParser__

#include <iostream>


#include "cocos2d.h"
#include "CCSAXParser.h"
USING_NS_CC;
class MyXMLParser:public CCObject,public CCSAXDelegator
{
public:
    MyXMLParser();
    ~MyXMLParser();
    static MyXMLParser * parserWithFile(const char *tmxFile);
    
    bool initMyXmlParse(const char* xmlName);
    void startElement(void *ctx, const char *name, const char **atts);
     void endElement(void *ctx, const char *name);
     void textHandler(void *ctx, const char *s, int len);
     CCDictionary* dataDictionary;
    std::string root_name;
    bool isJumpHeadData;
private:
    CCTexture2D *cache;
    std::string startXmlElement;//用来记录每个key前字段
    
    std::string endXmlElement;//用来记录每个key后字段
    
    std::string currString;//记录每个value的值

};
#endif /* defined(____war__MyXMLParser__) */