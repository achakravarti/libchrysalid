#include "../include/utf8.h"

/* Criterion testing framework */
#include <criterion/criterion.h>


/* English sample strings */


#define SAMPLE_EN_1     "Jim quickly realized that the beautiful gowns" \
                        " are expensive."

#define SAMPLE_EN_2     "Jackie will budget for the most expensive" \
                        " zoology equipment."

/* Greek sample strings */


#define SAMPLE_EL_1     "Θέλει αρετή και τόλμη η ελευθερία. (Ανδρέας Κάλβος)."

#define SAMPLE_EL_2     "Ο καλύμνιος σφουγγαράς ψιθύρισε πως θα βουτήξει" \
                        " χωρίς να διστάζει."


/* Tests for cy_utf8_new() */


/*                                                       %test:cy_utf8_new:empty
 * __SCENARIO__
 *      {{cy_utf8_new()}} returns a valid empty string if passed an empty
 *      {{char}} string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_new, empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      cr_expect(s);

      cr_expect(!*s);
      cr_expect(cy_utf8_eq(s, ""));

      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s));

      cr_expect(cy_utf8_refc(s) == 1);
}


/*                                                          %test:cy_utf8_new:en
 * __SCENARIO__
 *      {{cy_utf8_new()}} returns a valid English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_new, en)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      cr_expect(s);

      cr_expect(*s);
      cr_expect(cy_utf8_eq(s, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_2));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s) == strlen(SAMPLE_EN_1));

      cr_expect(cy_utf8_refc(s) == 1);
}


/*                                                          %test:cy_utf8_new:el
 * __SCENARIO__
 *      {{cy_utf8_new()}} returns a valid Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_new, el)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      cr_expect(s);

      cr_expect(*s);
      cr_expect(cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(!cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_2));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s) == 52);

      cr_expect(cy_utf8_refc(s) == 1);
}


/* Tests for cy_utf8_copy() */


/*                                               %test:cy_utf8_copy:single_empty
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates a shallow copy of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, single_empty)
{
}


/*                                                  %test:cy_utf8_copy:single_en
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates a shallow copy of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, single_en)
{
}


/*                                                  %test:cy_utf8_copy:single_el
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates a shallow copy of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, single_el)
{
}


/*                                             %test:cy_utf8_copy:multiple_empty
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates multiple shallow copies of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, multiple_empty)
{
}


/*                                                %test:cy_utf8_copy:multiple_en
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates multiple shallow copies of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, multiple_en)
{
}


/*                                                %test:cy_utf8_copy:multiple_el
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates multiple shallow copies of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, multiple_el)
{
}



/* Tests for cy_utf8_clone() */


/*                                              %test:cy_utf8_clone:single_empty
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates a deep copy of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, single_empty)
{
}


/*                                                 %test:cy_utf8_clone:single_en
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates a deep copy of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, single_en)
{
}


/*                                                 %test:cy_utf8_clone:single_el
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates a deep copy of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, single_el)
{
}


/*                                            %test:cy_utf8_clone:multiple_empty
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates multiple deep copies of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, multiple_empty)
{
}


/*                                               %test:cy_utf8_clone:multiple_en
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates multiple deep copies of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, multiple_en)
{
}


/*                                               %test:cy_utf8_clone:multiple_el
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates multiple deep copies of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, multiple_el)
{
}


/* Tests for cy_utf8_free() */


/*                                                       %test:cy_utf8_free:null
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a handle to NULL
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, null)
{
}


/*                                               %test:cy_utf8_free:single_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a single empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_empty)
{
}


/*                                                  %test:cy_utf8_free:single_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a single English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_en)
{
}


/*                                                  %test:cy_utf8_free:single_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a single Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_el)
{
}


/*                                          %test:cy_utf8_free:single_copy_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a copy of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_copy_empty)
{
}


/*                                             %test:cy_utf8_free:single_copy_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a copy of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_copy_en)
{
}


/*                                             %test:cy_utf8_free:single_copy_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a copy of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_copy_el)
{
}


/*                                        %test:cy_utf8_free:multiple_copy_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on copies of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_copy_empty)
{
}


/*                                           %test:cy_utf8_free:multiple_copy_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on copies of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_copy_en)
{
}


/*                                           %test:cy_utf8_free:multiple_copy_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on copies of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_copy_el)
{
}


/*                                         %test:cy_utf8_free:single_clone_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a clone of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_clone_empty)
{
}


/*                                            %test:cy_utf8_free:single_clone_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a clone of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_clone_en)
{
}


/*                                            %test:cy_utf8_free:single_clone_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a clone of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_clone_el)
{
}


/*                                         %test:cy_utf8_free:single_clone_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on clones of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_clone_empty)
{
}


/*                                          %test:cy_utf8_free:multiple_clone_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on clones of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_clone_en)
{
}


/*                                          %test:cy_utf8_free:multiple_clone_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on clones of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_clone_el)
{
}


/* Tests for cy_utf8_match() */


/*                                               %test:cy_utf8_match:empty_empty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on empty string with empty pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, empty_empty)
{
}


/*                                            %test:cy_utf8_match:empty_nonempty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on empty string with valid pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, empty_nonempty)
{
}


/*                                                  %test:cy_utf8_match:en_empty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on English string with empty pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, en_empty)
{
}


/*                                                  %test:cy_utf8_match:en_match
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on English string with matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, en_match)
{
}


/*                                                %test:cy_utf8_match:en_nomatch
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on English string with non-matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, en_nomatch)
{
}


/*                                                  %test:cy_utf8_match:el_empty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on Greek string with empty pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, el_empty)
{
}


/*                                                  %test:cy_utf8_match:el_match
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on Greek string with matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, el_match)
{
}


/*                                                %test:cy_utf8_match:el_nomatch
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on Greek string with non-matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, el_nomatch)
{
}
