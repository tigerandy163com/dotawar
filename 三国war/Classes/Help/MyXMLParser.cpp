//
//  MyXMLParser.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-28.
//
//

#include "MyXMLParser.h"

MyXMLParser::MyXMLParser()
{
    dataDictionary =NULL;
}
MyXMLParser::~MyXMLParser()
{
    CC_SAFE_RELEASE_NULL(dataDictionary);
}

MyXMLParser * MyXMLParser::parserWithFile(const char *tmxFile)
{
    MyXMLParser *pRet = new MyXMLParser();
    if(pRet->initMyXmlParse(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool MyXMLParser::initMyXmlParse(const char* xmlName)

{
    if (dataDictionary==NULL) {
        dataDictionary = CCDictionary::create();
        dataDictionary->retain();
    }
    std::string imageN = (char*)xmlName;
    imageN = imageN.append(".png");
    cache = CCTextureCache::sharedTextureCache()->addImage(imageN.c_str());
    if (cache) {
        
    CCSAXParser _par;
    
    if (false == _par.init("UTF-8") )
        
    {
        CCLog("-----请使用utf-8格式!");
        return false;
    }
    _par.setDelegator(this);
    
    std::string xmlname = (char*)xmlName;
    xmlname = xmlname.append(".xml");
    return _par.parse(xmlname.c_str());
}
    return false;
}

//回调函数

void MyXMLParser::startElement(void *ctx, const char *name, const char **atts)

{
    
    CC_UNUSED_PARAM(ctx);
    
    startXmlElement = (char*)name;
    if(!isJumpHeadData){//跳过数据头
        CCLog("------跳过root name");
        isJumpHeadData=true;
        root_name=startXmlElement;
        return;
    }

    if (atts && atts[0])
    {
        CCRect rec;
        CCString* name;
        for(int i = 0; atts[i]; i += 2)
        {
            std::string key = (char*)atts[i];
            CCString* value = CCString::create((char*)atts[i+1]);
           // dataDictionary->setObject(value, key);
            if (key.compare("name")==0) {
                name = value;
            }else if (key.compare("x")==0)
            {
                rec.origin.x =value->floatValue();
            }else if (key.compare("y")==0)
            {
                rec.origin.y =value->floatValue();
            }else if (key.compare("width")==0)
            {
                rec.size.width =value->floatValue();
            }else if (key.compare("height")==0)
            {
                rec.size.height=value->floatValue();
            }
          //  CCLOG("key:%s,value:%s",key.c_str(),value->getCString());
        }
        CCSpriteFrame* SF = CCSpriteFrame::createWithTexture(cache, rec);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(SF, name->getCString());
    }
}

void MyXMLParser::endElement(void *ctx, const char *name)

{
    CC_UNUSED_PARAM(ctx);
    
    endXmlElement = (char*)name;
    if(endXmlElement==root_name){//数据尾
        CCLog("读取xml结束");
        isJumpHeadData=false;
        root_name="";
        return;
    }
    
    //    CCLog("-endElement----%s",endXmlElement.c_str());
}
//键值对的结束字段
void MyXMLParser::textHandler(void *ctx, const char *ch, int len)
{
    
    CC_UNUSED_PARAM(ctx);
    currString=std::string((char*)ch,0,len);
    CCString *ccStr = CCString::create(currString.c_str());
    if(root_name!=""){
        dataDictionary->setObject(ccStr,startXmlElement);
       // CCLog("-----key:%s, value:%s",startXmlElement.c_str(),((CCString*)dataDictionary->objectForKey(startXmlElement))->m_sString.c_str());
    }
    
       // CCLog("-textHandler----%s",currString.c_str());
    
}
