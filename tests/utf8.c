#include "../include/utf8.h"

/* Criterion testing framework */
#include <criterion/criterion.h>


/* English sample strings */


#define SAMPLE_EN_1     "Jim quickly realized that the beautiful gowns" \
                        " are expensive."

#define SAMPLE_EN_2     "Jackie will budget for the most expensive" \
                        " zoology equipment."

#define LEN_EN_1    strlen(SAMPLE_EN_1)

#define LEN_EN_2    strlen(SAMPLE_EN_2)


/* Greek sample strings */


#define SAMPLE_EL_1     "Θέλει αρετή και τόλμη η ελευθερία. (Ανδρέας Κάλβος)."

#define SAMPLE_EL_2     "Ο καλύμνιος σφουγγαράς ψιθύρισε πως θα βουτήξει" \
                        " χωρίς να διστάζει."

#define LEN_EL_1    52

#define LEN_EL_2    66


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
      cr_expect(cy_utf8_empty(s));

      cr_expect(cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s));
      cr_expect(cy_utf8_sz(s) >= 1);

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
      cr_expect(!cy_utf8_empty(s));

      cr_expect(cy_utf8_eq(s, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_2));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s) == LEN_EN_1);
      cr_expect(cy_utf8_sz(s) >= LEN_EN_1 + 1);

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
      cr_expect(!cy_utf8_empty(s));

      cr_expect(cy_utf8_eq(s, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_2));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s) == LEN_EL_1);
      cr_expect(cy_utf8_sz(s) >= LEN_EL_1 + 1);

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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1);
      cr_expect(cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(cy_utf8_sz(s1) >= 1);

      cr_expect(cy_utf8_refc(s) == 2);
      cr_expect(cy_utf8_refc(s1) == 2);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EN_1 + 1);

      cr_expect(cy_utf8_refc(s) == 2);
      cr_expect(cy_utf8_refc(s1) == 2);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EL_1 + 1);

      cr_expect(cy_utf8_refc(s) == 2);
      cr_expect(cy_utf8_refc(s1) == 2);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1 == s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(cy_utf8_empty(s1));
      cr_expect(cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_2));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(!cy_utf8_len(s2));

      cr_expect(cy_utf8_sz(s1) >= 1);
      cr_expect(cy_utf8_sz(s2) >= 1);

      cr_expect(cy_utf8_refc(s) == 3);
      cr_expect(cy_utf8_refc(s1) == 3);
      cr_expect(cy_utf8_refc(s2) == 3);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_copy(s1);

      cr_expect(s == s1);
      cr_expect(s1 == s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_2);
      cr_expect(cy_utf8_len(s2) == LEN_EN_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EN_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EN_2 + 1);

      cr_expect(cy_utf8_refc(s) == 3);
      cr_expect(cy_utf8_refc(s1) == 3);
      cr_expect(cy_utf8_refc(s2) == 3);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_copy(s1);

      cr_expect(s == s1);
      cr_expect(s1 == s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EL_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_2);
      cr_expect(cy_utf8_len(s2) == LEN_EL_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EL_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EL_2 + 1);

      cr_expect(cy_utf8_refc(s) == 3);
      cr_expect(cy_utf8_refc(s1) == 3);
      cr_expect(cy_utf8_refc(s2) == 3);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1);
      cr_expect(cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(cy_utf8_sz(s1) >= 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EN_1 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EL_1 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1 != s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(cy_utf8_empty(s1));
      cr_expect(cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_2));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(!cy_utf8_len(s2));

      cr_expect(cy_utf8_sz(s1) >= 1);
      cr_expect(cy_utf8_sz(s2) >= 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_clone(s1);

      cr_expect(s != s1);
      cr_expect(s1 != s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_2);
      cr_expect(cy_utf8_len(s2) == LEN_EN_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EN_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EN_2 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);
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
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_clone(s1);

      cr_expect(s != s1);
      cr_expect(s1 != s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EL_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_2);
      cr_expect(cy_utf8_len(s2) == LEN_EL_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EL_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EL_2 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);
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
      cy_utf8_t *s = NULL;
      cy_utf8_free(&s);
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
      cy_utf8_t *s = cy_utf8_new("");
      cy_utf8_free(&s);
      cr_expect(!s);
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
