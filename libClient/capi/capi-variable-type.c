#include "string.h"
#include "capi-variable-type.h"


/*
 * Function Name: GVar2CtsgwVar
 * 
 * Description:    Cast the Gvariant * type to CtSgwVariant_t * type
 *         
 * Parameter:
 *    v <IN>:    A pointer to GVariant type parameter
 *
 * Return: A pointer to CtSgwVariant_t variable come from v
 *
 */
CtSgwVariant_t* GVar2CtSgwVar (GVariant* v)
{
    g_return_val_if_fail ((v != NULL), NULL);

    return ( (CtSgwVariant_t *)v );
}

/*
 * Function Name: CtsgwVar2GVar
 *
 * Description: Cast the CtSgwVariant_t * type to GVariant * type
 *
 * Parameter:
 *    inst <IN>:    A pointer to CtSgwVariant_t type parameter
 *
 * Return: A pointer to GVariant variable come from v
 *
 */
GVariant* CtSgwVar2GVar (CtSgwVariant_t* v)
{
    g_return_val_if_fail ((v != NULL), NULL);

    return ( (GVariant *)v );
}

/*
 * Function Name: CtSgwVariantRef
 *
 * Description: Increases the reference count of v
 *
 * Parameter:
 *    v <IN>:    A pointer to CtSgwVariant_t type parameter
 *
 * Return: The same v
 *
 */
CtSgwVariant_t* CtSgwVariantRef (CtSgwVariant_t *v)
{
    GVariant *retVal = NULL;

    g_return_val_if_fail ((v != NULL), NULL);

    retVal = g_variant_ref ((GVariant *)v);
    
    return ((CtSgwVariant_t *)retVal);
}

/*
 * Function Name: CtSgwVariantUnRef
 *
 * Description: Decreases the reference count of v. When its reference count 
 *              drops to 0, the memory used by the variant is freed
 *
 * Parameter:
 *    v <IN>:  A pointer to CtSgwVariant_t type parameter
 *
 * Return:
 *
 */
void CtSgwVariantUnRef (CtSgwVariant_t *v)
{
    g_return_if_fail(v != NULL);

    g_variant_unref ((GVariant *)v);
}

/************************************************************
 *                                                          *
 * Private Function                                         *
 *                                                          *
 ************************************************************/
static gboolean
ctsgw_g_variant_format_string_scan (const gchar  *string,
                                    const gchar  *limit,
                                    const gchar **endptr)
{
#define next_char() (string == limit ? '\0' : *string++)
#define peek_char() (string == limit ? '\0' : *string)
    char c;

    switch (next_char())
    {
        case 'b': case 'y': case 'n': case 'q': case 'i': case 'u':
        case 'x': case 't': case 'h': case 'd': case 's': case 'o':
        case 'g': case 'v': case '*': case '?': case 'r':
            break;

        case 'm':
            return ctsgw_g_variant_format_string_scan (string, limit, endptr);

        case 'a':
        case '@':
            return g_variant_type_string_scan (string, limit, endptr);

        case '(':
            while (peek_char() != ')')
                if (!ctsgw_g_variant_format_string_scan (string, limit, &string))
                    return FALSE;

            next_char(); /* consume ')' */
            break;

        case '{':
            c = next_char();

            if (c == '&')
            {
                c = next_char ();

                if (c != 's' && c != 'o' && c != 'g')
                    return FALSE;
            }
            else
            {
                if (c == '@')
                c = next_char ();

                /* ISO/IEC 9899:1999 (C99) §7.21.5.2:
                *    The terminating null character is considered to be
                *    part of the string.
                */
                if (c != '\0' && strchr ("bynqiuxthdsog?", c) == NULL)
                    return FALSE;
            }

            if (!ctsgw_g_variant_format_string_scan (string, limit, &string))
                return FALSE;

            if (next_char() != '}')
                return FALSE;

            break;

        case '^':
            if ((c = next_char()) == 'a')
            {
                if ((c = next_char()) == '&')
                {
                    if ((c = next_char()) == 'a')
                    {
                        if ((c = next_char()) == 'y')
                            break;      /* '^a&ay' */
                    }

                    else if (c == 's' || c == 'o')
                        break;          /* '^a&s', '^a&o' */
                }

                else if (c == 'a')
                {
                    if ((c = next_char()) == 'y')
                        break;          /* '^aay' */
                }

                else if (c == 's' || c == 'o')
                    break;              /* '^as', '^ao' */

                else if (c == 'y')
                    break;              /* '^ay' */
            }
            else if (c == '&')
            {
                if ((c = next_char()) == 'a')
                {
                    if ((c = next_char()) == 'y')
                        break;          /* '^&ay' */
                }
            }

            return FALSE;

        case '&':
            c = next_char();

            if (c != 's' && c != 'o' && c != 'g')
                return FALSE;

            break;

        default:
            return FALSE;
    }

    if (endptr != NULL)
        *endptr = string;

#undef next_char
#undef peek_char

    return TRUE;
}

static GVariantType *
ctsgw_g_variant_format_string_scan_type (const gchar  *string,
                                   const gchar  *limit,
                                   const gchar **endptr)
{
    const gchar *my_end;
    gchar *dest;
    gchar *new;

    if (endptr == NULL)
        endptr = &my_end;

    if (!ctsgw_g_variant_format_string_scan (string, limit, endptr))
        return NULL;

    dest = new = g_malloc (*endptr - string + 1);
    while (string != *endptr)
    {
        if (*string != '@' && *string != '&' && *string != '^')
            *dest++ = *string;
        string++;
    }
    *dest = '\0';

    return (GVariantType *) G_VARIANT_TYPE (new);
}

static gboolean
ctsgw_valid_format_string (const gchar *format_string,
                           gboolean     single,
                           GVariant    *value)
{
    const gchar *endptr;
    GVariantType *type;

    type = ctsgw_g_variant_format_string_scan_type (format_string, NULL, &endptr);

    if G_UNLIKELY (type == NULL || (single && *endptr != '\0'))
    {
        if (single)
            g_critical ("'%s' is not a valid GVariant format string",
                        format_string);
        else
            g_critical ("'%s' does not have a valid GVariant format "
                        "string as a prefix", format_string);

        if (type != NULL)
            g_variant_type_free (type);

        return FALSE;
    }

    if G_UNLIKELY (value && !g_variant_is_of_type (value, type))
    {
        gchar *fragment;
        gchar *typestr;

        fragment = g_strndup (format_string, endptr - format_string);
        typestr = g_variant_type_dup_string (type);

        g_critical ("the GVariant format string '%s' has a type of "
                    "'%s' but the given value has a type of '%s'",
                    fragment, typestr, g_variant_get_type_string (value));

        g_variant_type_free (type);
        g_free (fragment);
        g_free (typestr);

        return FALSE;
    }

    g_variant_type_free (type);

    return TRUE;
}
/************************************************************
 *                                                          *
 * End of Private Function                                  *
 *                                                          *
 ************************************************************/



/*
 * Function Name: CtSgwVariantNew
 *
 * Description: Creates a new CtSgwVariant_t instance
 *
 * Parameter:
 *   format_string <IN>:    A GVariant format string
 *
 * Return:    A new floating CtSgwVariant_t instance
 *
 */
CtSgwVariant_t *CtSgwVariantNew (const char *format, ...)
{
    GVariant *value;
    va_list ap;
    
    g_return_val_if_fail (ctsgw_valid_format_string (format, TRUE, NULL) &&
                          format[0] != '?' && format[0] != '@' &&
                          format[0] != '*' && format[0] != 'r',
                          NULL);
    
    va_start (ap, format);
    value = g_variant_new_va (format, NULL, &ap);
    va_end (ap);
    
    return ((CtSgwVariant_t *)value);
}

/*
 * Function Name: CtSgwVariantNewArray
 *
 * Description: Creates a new CtSgwVariant_t arry from children
 *
 * Parameter:
 *      children <IN>:    the element type of the new array.
 *    n_children <IN>:    the length of children
 *
 * Return:    A floating reference to a new CtSgwVariant_t array
 *
 */
CtSgwVariant_t* CtSgwVariantNewArray (CtSgwVariant_t* const *children, uint32_t n_children)
{
    GVariant *retVal = NULL;

    g_return_val_if_fail ((children != NULL) && (n_children != 0), NULL);

    retVal = g_variant_new_array(NULL, (GVariant * const *)children, n_children);

    return ((CtSgwVariant_t *)retVal);
}

/*
 * Function Name: CtSgwVariantNewTuple
 *
 * Description: Creates a new tuple CtSgwVariant_t out of items in children.
 *              The type is determined from the types of children, No entry
 *              in the children array may be NULL
 *
 * Parameter:
 *      children <IN>:   the items to make the tuple out of.
 *    n_children <IN>:   the length of children
 *
 * Return:    A floating reference to a new CtSgwVariant_t tuple
 *
 */
CtSgwVariant_t* CtSgwVariantNewTuple (CtSgwVariant_t * const * children, uint32_t n_children)
{
    GVariant *retVal = NULL;

    g_return_val_if_fail ((children != NULL) && (n_children != 0), NULL);

    retVal = g_variant_new_tuple ((GVariant * const *)children, n_children);

    return ((CtSgwVariant_t *)retVal);
}

/*
 * Function Name: CtSgwVariantNewDictEntry
 *
 * Description: Creates a new dictionary entry CtSgwVariant_t.
 *              key and value must be non-NULL. key must be a
 *              value of basic type (ie: not a container)
 *
 * Parameter:
 *      key <IN>:   a basic CtSgwVariant, the key.
 *    value <IN>:   a CtSgwVariant_t, the value
 *
 * Return:    A floating reference to a new dictionary entry CtSgwVariant_t
 *
 */
CtSgwVariant_t *CtSgwVariantNewDictEntry (CtSgwVariant_t *key, CtSgwVariant_t *value)
{
    const GVariantType *type = NULL;
    GVariant *retVal = NULL;

    g_return_val_if_fail ((key != NULL) && (value != NULL), NULL);

    type = g_variant_get_type((GVariant *)key);
    if ( !g_variant_type_is_basic ( type ))
        return NULL;

    retVal = g_variant_new_dict_entry (key, value);

    return retVal;
}

/*
 * Function Name: CtSgwVariantGet
 *
 * Description: Deconstructs a CtSgwVariant_t instance.
 *
 * Parameter:
 *         v <IN>:    A CtSgwVariant_t instance
 *    format <IN>:    A CtSgwVariant_t format string
 *
 * Return:
 *
 */
void CtSgwVariantGet (CtSgwVariant_t *v, const char *format, ...)
{
    va_list ap;
    
    g_return_if_fail (ctsgw_valid_format_string (format, TRUE, v));
    
    /* if any direct-pointer-access formats are in use, flatten first */
    if (strchr (format, '&'))
        g_variant_get_data (v);
    
    va_start (ap, format);
    g_variant_get_va (v, format, NULL, &ap);
    va_end (ap);

}

/*
 * Function Name: CtSgwVariantGetVa
 *
 * Description: This function is intended to be used by libraries based on CtSgwVariant_t that
 *              want to provide CtSgwVariantGet()-like functionality to their user.
 *
 * Parameter:
 *         v <IN>:  A CtSgwVariant_t
 *    format <IN>:  A string that is prefixed with a format string
 *    endptr <IN>:  Location to store the end pointer, or NULL
 *       app <IN>:  A pointer to a va_list.
 *
 * Return:
 *
 */
void CtSgwVariantGetVa (CtSgwVariant *v, const char *format, const char **endptr, va_list *app)
{
    g_variant_get_va ((GVariant *)v, format, endptr, app);
}

/*
 * Function Name: CtSgwVariantChildNum
 *
 * Description: Determines the number of children in a container CtSgwVariant_t instance.
 *              This includes variants, maybes, arrays, tuples and dictionary entries.
 *
 * Parameter:
 *    v <IN>:    A container CtSgwVariant_t
 *
 * Return:    The number of children in the container
 *
 */
uint32_t CtSgwVariantChildNum ( CtSgwVariant_t *v)
{
    g_return_val_if_fail ((v != NULL), 0);

    return (g_variant_n_children( (GVariant *)v ));
}

/*
 * Function Name: CtSgwVariantGetChildVal
 *
 * Description: Determines the number of children in a container CtSgwVariant_t instance.
 *              This includes variants, maybes, arrays, tuples and dictionary entries.
 *
 * Parameter:
 *      v <IN>:    A container CtSgwVariant_t
 *
 * Return:    The number of children in the container
 *
 */
CtSgwVariant_t *CtSgwVariantGetChildVal (CtSgwVariant_t *v, uint32_t index)
{
    GVariant *retVal = NULL;

    retVal = g_variant_get_child_value ((GVariant *)v, index);

    return ((CtSgwVariant_t *)retVal);
}

/*
 * Function Name: CtSgwVariantGetChild
 *
 * Description: Reads a child item out of a container CtSgwVariant_t
 *              instance and deconstructs it according to format
 *
 * Parameter:
 *        v <IN>:   A container CtSgwVariant_t
 *    index <IN>:   The index of the child to deconstruct
 *   format <IN>:   A CtSgwVariant_t format string
 *
 * Return:    
 *
 */
void CtSgwVariantGetChild ( CtSgwVariant_t *v, uint32_t index, const char *format, ...)
{
    GVariant *child;
    va_list ap;

    /* if any direct-pointer-access formats are in use, flatten first */
    if (strchr (format, '&'))
        g_variant_get_data (v);

    child = g_variant_get_child_value (v, index);
    g_return_if_fail (ctsgw_valid_format_string (format, TRUE, child));

    va_start (ap, format);
    g_variant_get_va (child, format, NULL, &ap);
    va_end (ap);

    g_variant_unref (child);

}

/*
 * Function Name: CtSgwVariantLookupValue
 *
 * Description: Looks up a value in a dictionary CtSgwVariant_t
 *
 * Parameter:
 *       dict <IN>:   A dictionary CtSgwVariant_t
 *        key <IN>:   The key to lookup in the dictionary
 *    typestr <IN>:   a GVariantType, or NULL
 *
 * Return:    the value of the dictionary key, or NULL
 *
 */
CtSgwVariant_t *CtSgwVariantLookupValue( CtSgwVariant_t *dict, const char *key, const char *typestr)
{
    GVariant *retVal = NULL;

    retVal = g_variant_lookup_value ((GVariant *)dict, key,  G_VARIANT_TYPE(typestr));

    return ((CtSgwVariant_t *)retVal);
}

/*
 * Function Name: CtSgwVariantLookup
 *
 * Description: Looks up a value in a dictionary CtSgwVariant_t
 *
 * Parameter:
 *    dict <IN>:   A dictionary CtSgwVariant_t
 *     key <IN>:   The key to lookup in the dictionary
 *  format <IN>:   a CtSgwVariant_t format string
 *
 * Return:    TRUE if a value was unpacked
 *
 */
boolean CtSgwVariantLookup (CtSgwVariant_t *dict, const char *key, const char *format, ...)
{
    GVariantType *type;
    GVariant *value;

    /* flatten */
    g_variant_get_data (dict);

    type = ctsgw_g_variant_format_string_scan_type (format, NULL, NULL);
    value = g_variant_lookup_value (dict, key, type);
    g_variant_type_free (type);

    if (value)
    {
        va_list ap;

        va_start (ap, format);
        g_variant_get_va (value, format, NULL, &ap);
        g_variant_unref (value);
        va_end (ap);

        return TRUE;
    }

    else
        return FALSE;
}

/*
 * Function Name: CtSgwVariantPrint
 *
 * Description: Pretty-prints v in the format understood by g_variant_parse
 *
 * Parameter:
 *    v <IN>:    A CtSgwVariant_t
 *
 * Return:    a newly-allocated string holding the result.
 *
 */
char *CtSgwVariantPrint (CtSgwVariant_t *v)
{
    g_return_val_if_fail ((v != NULL), NULL);

    return (g_variant_print ((GVariant *)v, TRUE));
}
