#ifndef _CORE_EXCEPT_DEFINE_H_
#define _CORE_EXCEPT_DEFINE_H_

#include "gsharedptr.h"
#include "gstring.h"

#define GTRY() \
    gsystem::GSharedPtr<gsystem::GException> exception; \
    gsystem::GString stackParams; \
    try \
    { \

#define GCATCH(methodName) \
    } \
    catch (gsystem::GException *ex) \
    { \
        exception.Reset(ex); \
        exception->AddStackTraceInfo(methodName, stackParams, GLINE, GFILE); \
    } \
    catch (std::exception &ex) \
    { \
        exception = gsystem::gsystemException::Create(e, methodName, GLINE, GFILE); \
    } \
    catch (...) \
    { \
        exception.Reset(new gsystem::GUnclassifiedException(methodName, GLINE, GFILE, GNULL, "", GNULL)); \
    } \

#define GTHROW() \
    if (exception != NULL) \
    { \
        (*exception).Add(); \
        exception->Raise(); \
    } \

#define G_CATCH_AND_THROW(methodName) \
    GCATCH(methodName) \
    GTHROW()

#define G_CATCH_AND_RELEASE() \
    } \
    catch (gsystem::GException *e) \
    { \
        exception.Reset(e); \
    } \
    catch (...) \
    { \
    } \

#define G_THROW_EXCEPTION(exceptionClass, methodName, whatArguments, whyMessageId, whyArguments) \
    throw new exceptionClass(methodName, GLINE, GFILE, whatArguments, whyMessageId, whyArguments) \


#endif // _CORE_EXCEPT_DEFINE_H_
