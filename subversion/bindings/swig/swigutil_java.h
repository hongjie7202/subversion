/*
 * swigutil_java.h :  utility functions and stuff for the SWIG Java bindings
 *
 * ====================================================================
 * Copyright (c) 2002 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 */


#ifndef SVN_SWIG_SWIGUTIL_JAVA_H
#define SVN_SWIG_SWIGUTIL_JAVA_H

#include <jni.h>

#include <apr.h>
#include <apr_pools.h>
#include <apr_strings.h>
#include <apr_hash.h>
#include <apr_tables.h>

#include "svn_types.h"
#include "svn_string.h"
#include "svn_delta.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* If this file is being included outside of a wrapper file, then need to
   create stubs for some of the SWIG types. */

/* if SWIGEXPORT is defined, then we're in a wrapper. otherwise, we need
   the prototypes and type definitions. */
#ifndef SWIGEXPORT
#define SVN_NEED_SWIG_TYPES
#endif

#ifdef SVN_NEED_SWIG_TYPES

typedef struct _unnamed swig_type_info;
jobject *SWIG_NewPointerObj(JNIEnv *jenv, void *, swig_type_info *, int own);
swig_type_info *SWIG_TypeQuery(JNIEnv *jenv, const char *name);

#endif /* SVN_NEED_SWIG_TYPES */


/* helper function to convert an apr_hash_t* (char* -> svnstring_t*) to
   a Java Map */
jobject svn_swig_java_prophash_to_dict(JNIEnv *jenv, apr_hash_t *hash);

/* convert a hash of 'const char *' -> TYPE into a Java Map */
jobject svn_swig_java_convert_hash(JNIEnv *jenv, apr_hash_t *hash,
                                   swig_type_info *type);

/* helper function to convert a 'char **' into a Java List of String
   objects */
jobject svn_swig_java_c_strings_to_list(JNIEnv *jenv, char **strings);

/* helper function to convert an array of 'const char *' to a Java List of
   String objects */
jobject svn_swig_java_array_to_list(JNIEnv *jenv,
                                    const apr_array_header_t *strings);

/* helper function to convert a Java List of String objects into an
   'apr_array_header_t *' of 'const char *' objects.  Note that the
   objects must remain alive -- the values are not copied. This is
   appropriate for incoming arguments which are defined to last the
   duration of the function's execution.  */
const apr_array_header_t *svn_swig_java_strings_to_array(JNIEnv *jenv,
                                                         jobject source,
                                                         apr_pool_t *pool);

/* make a editor that "thunks" from C callbacks up to Java */
void svn_swig_java_make_editor(JNIEnv *jenv,
                               const svn_delta_editor_t **editor,
                               void **edit_baton,
                               jobject java_editor,
                               apr_pool_t *pool);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* SVN_SWIG_SWIGUTIL_JAVA_H */
