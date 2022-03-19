/*****************************************************************************
*	昆明畅博科技公司 Copyright (c) 2014-2022
*	Copyright (c) 2014-2022, Kunming Changbo Technology Co., Ltd.
*	www.kuncb.cn
*	作者：黑哥
*
*	QT5 常用工具
*****************************************************************************/

#ifndef KC_81C119C5_767B_2248_BDFF_8873C6575924
#define KC_81C119C5_767B_2248_BDFF_8873C6575924

/*****************************************************************************
*	自定义函数返回值定义
*****************************************************************************/
#ifndef KC_OK
#define KC_OK		((int32_t)0)
#endif

#ifndef KC_FAIL
#define KC_FAIL		((int32_t)1)
#endif

/*****************************************************************************
*	C多国语言函数
*****************************************************************************/
#define _TR(x) gettext(x)

/*****************************************************************************
*	安全释放C++对象
*****************************************************************************/
#define KC_SAFE_DELETE(ptr) do {\
	if (NULL !=  (ptr)) {\
		delete (ptr);  (ptr) = NULL;\
	}\
} while (0)

/*****************************************************************************
*	安全释放QSharedMemory对象
*****************************************************************************/
#define KC_SAFE_QSHAREDMEMORY_DELETE(ptr) do {\
	if (NULL !=  (ptr)) { \
        (ptr)->destroyed(); \
		delete (ptr);  (ptr) = NULL;\
	}\
} while (0)

/*****************************************************************************
*	安全释放QAPPLICATION对象
*****************************************************************************/
#define KC_SAFE_QAPPLICATION_DELETE(ptr) do {\
	if (NULL !=  (ptr)) { \
         (ptr)->exit(); \
		delete (ptr);  (ptr) = NULL;\
	}\
} while (0)



/*****************************************************************************
*   检查分配内存是否成功
*****************************************************************************/
#define KC_CHECK_MALLOC(ptr,str) do{\
	if (NULL == (ptr) ){\
		resetStringBuffer((str));\
		appendStringBuffer((str),("out of memory.(%s:%d)"),__FILE__,__LINE__);\
		goto KC_ERROR_CLEAR;\
	}\
}while (0)
/*****************************************************************************
*   直接跳转换至异常
*****************************************************************************/
#define KC_GOTOERR(str,format, ...) do{\
		resetStringBuffer((str));\
		appendStringBuffer((str),(format), ##__VA_ARGS__);\
		goto KC_ERROR_CLEAR;\
}while (0)
/*****************************************************************************
*   检查标准函数返回代码是否正确,如果不正确直接跳转至异常
*****************************************************************************/
#define KC_CHECK_RCV1(rc,funname,str) do{\
	if ((rc)){\
		resetStringBuffer((str));\
		appendStringBuffer((str),("call function \"%s\" fail.(%s:%d)"),(funname),__FILE__,__LINE__);\
		goto KC_ERROR_CLEAR;\
	}\
}while (0)
/*****************************************************************************
*   检查自定义函数返回代码是否正确,如果不正确直接跳转至异常
*****************************************************************************/
#define KC_CHECK_RCV2(rc) do{\
	if ( KC_OK!=(rc))\
		goto KC_ERROR_CLEAR;\
}while (0)

#endif	/*KC_81C119C5_767B_2248_BDFF_8873C6575924*/
